//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSchedule.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSchedule.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Assert.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Tile.h"
#include "ObjectRegistry.h"

#include "skill/EffectVampirePortal.h"

#include "Gpackets/GCAddVampirePortal.h"


//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleWork member methods
//////////////////////////////////////////////////////////////////////////////

EffectScheduleWork::EffectScheduleWork()
	
{
	__BEGIN_TRY

	m_Code = WORKCODE_MAX;

	__END_CATCH
}

EffectScheduleWork::~EffectScheduleWork()
	
{
	__BEGIN_TRY

	//SAFE_DELETE(m_pData);
	
	// 코드에 따라서, void* m_pData를 캐스팅해서, 
	// 알맞게 지워줘야 한다.
	if (m_Code == WORKCODE_ADD_VAMPIRE_PORTAL)
	{
		Assert(m_pData == NULL);
	}
	else if (m_Code == WORKCODE_DELETE)
	{
		Assert(m_pData == NULL);
	}
	else
	{
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class EffectSchedule member methods
//////////////////////////////////////////////////////////////////////////////

EffectSchedule::EffectSchedule()
	
{
	__BEGIN_TRY

	m_pEffect = NULL;

	__END_CATCH
}

EffectSchedule::~EffectSchedule()
	
{
	__BEGIN_TRY

	while (!m_WorkList.empty())
	{
		EffectScheduleWork* pWork = getFrontWork();
		SAFE_DELETE(pWork);
	}

	__END_CATCH
}

void EffectSchedule::addWork(int WorkCode, void* pData) 
	
{
	__BEGIN_TRY

	Assert(WorkCode < WORKCODE_MAX);

	EffectScheduleWork* pWork = new EffectScheduleWork();
	pWork->setCode(WorkCode);
	pWork->setData(pData);
	m_WorkList.push_back(pWork);

	__END_CATCH
}

EffectScheduleWork* EffectSchedule::getFrontWork(void) 
	
{
	__BEGIN_TRY

	if (!m_WorkList.empty())
	{
		EffectScheduleWork* pWork = m_WorkList.front();
		m_WorkList.pop_front();
		return pWork;
	}

	return NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleManager member methods
//////////////////////////////////////////////////////////////////////////////

EffectScheduleManager::EffectScheduleManager()
	
{
	__BEGIN_TRY
	__END_CATCH
}

EffectScheduleManager::~EffectScheduleManager()
	
{
	__BEGIN_TRY

	while (!m_EffectScheduleList.empty())
	{
		EffectSchedule* pSchedule = m_EffectScheduleList.front();
		m_EffectScheduleList.pop_front();
		SAFE_DELETE(pSchedule);
	}

	__END_CATCH
}

void EffectScheduleManager::addEffectSchedule(EffectSchedule* pEffectSchedule) 
	
{
	__BEGIN_TRY

	Assert(pEffectSchedule != NULL);

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_EffectScheduleList.push_back(pEffectSchedule);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void EffectScheduleManager::heartbeat(void)
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// 모든 스케쥴을 처리할 때까지...
	while (!m_EffectScheduleList.empty())
	{
		EffectSchedule* pEffectSchedule = m_EffectScheduleList.front();
		Assert(pEffectSchedule != NULL);

		Effect* pEffect = pEffectSchedule->getEffect();

		// 작업 대상이 되는 이펙트가 아직 존재한다면, 작업에 들어간다.
		if (pEffect != NULL)
		{
			// 모든 일을 처리할 때까지...
			while (true)
			{
				EffectScheduleWork* pWork = pEffectSchedule->getFrontWork();

				// 모든 일을 끝냈다면 브레이크
				if (pWork == NULL) break;

				int   WorkCode = pWork->getCode();
				//void* pData    = pWork->getData();

				// 각 작업 코드에 따라서 일을 처리한다.
				if (WorkCode == WORKCODE_ADD_VAMPIRE_PORTAL)
				{
					Assert(pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL);

					EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
					Assert(pEffectVampirePortal != NULL);

					// 현재 이펙트 내부에 있는 좌표는 제일 처음에 가고자 했던 좌표다.
					// 그 타일에 같은 이펙트가 있거나 하는 이유로 좌표는 수정될 수 있다.
					Zone* pZone = pEffectVampirePortal->getZone();
					ZoneCoord_t cx = pEffectVampirePortal->getX();
					ZoneCoord_t cy = pEffectVampirePortal->getY();
					ZONE_COORD ZoneCoord = pEffectVampirePortal->getZoneCoord();

					TPOINT pt = findSuitablePositionForEffect(pZone, cx, cy, Effect::EFFECT_CLASS_VAMPIRE_PORTAL);

					if (pt.x != -1)
					{
						// 좌표가 수정되었을 지도 모르니, 좌표를 수정해준다.
						pEffectVampirePortal->setX(pt.x);
						pEffectVampirePortal->setY(pt.y);

						// OID를 등록받아야 find라든지 하는 작업을 실행할 수 있다.
						ObjectRegistry& OR = pZone->getObjectRegistry();
						OR.registerObject(pEffectVampirePortal);

						// 타일 및 뱀파이어 포탈 매니저에 등록한다.
						Tile& rTile = pZone->getTile(pt.x, pt.y);
						rTile.addEffect(pEffectVampirePortal);

						EffectManager* pVampirePortalManager = pZone->getVampirePortalManager();
						pVampirePortalManager->addEffect(pEffectVampirePortal);

						// 타일에 이펙트가 붙었으니, 브로드캐스팅을 해준다.
						GCAddVampirePortal gcAddVampirePortal;
						gcAddVampirePortal.setObjectID(pEffectVampirePortal->getObjectID());
						gcAddVampirePortal.setOwnerID(pEffectVampirePortal->getOwnerID());
						gcAddVampirePortal.setX(pt.x);
						gcAddVampirePortal.setY(pt.y);
						gcAddVampirePortal.setTargetZoneID(ZoneCoord.id);
						gcAddVampirePortal.setTargetX(ZoneCoord.x);
						gcAddVampirePortal.setTargetY(ZoneCoord.y);
						gcAddVampirePortal.setDuration(pEffectVampirePortal->getRemainDuration());
						gcAddVampirePortal.setCreateFlag(1);

						pZone->broadcastPacket(pt.x, pt.y, &gcAddVampirePortal);
					}
					else
					{
						SAFE_DELETE(pEffectVampirePortal);
					}
				}
				else if (WorkCode == WORKCODE_DELETE)
				{
					pEffect->setDeadline(0);
				}
				else
				{
					Assert(false);
				}
			}
		}

		m_EffectScheduleList.pop_front();
		SAFE_DELETE(pEffectSchedule);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


