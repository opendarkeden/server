//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectManager.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectManager.h"
#include "EffectInfo.h"
#include "EffectEnemyErase.h"
#include "Assert1.h"
#include "Creature.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "GCAddEffect.h"

#include "Profile.h"

//#define __PROFILE_EM__

#ifdef __PROFILE_EM__
	#define __BEGIN_PROFILE_EM(name)	beginProfileEx(name);
	#define __END_PROFILE_EM(name)		endProfileEx(name);
#else
	#define __BEGIN_PROFILE_EM(name)	((void)0);
	#define __END_PROFILE_EM(name)		((void)0);
#endif



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class isSameEffectClass 
{
public:
	isSameEffectClass(Effect::EffectClass EClass) : m_EClass(EClass) {}
	bool operator () (Effect* pEffect) throw()
	{
		return pEffect->getEffectClass() == m_EClass;
	}
	
private:
	Effect::EffectClass m_EClass;
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectManager::EffectManager () 
    throw(Error)
{
	__BEGIN_TRY

	Assert(m_Effects.empty());

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectManager::~EffectManager () 
    throw()
{
	__BEGIN_TRY
		
	// 정식으로 deleteEffects() 가 호출되지 않았다면, 
	// 각 effect에 대해서 unaffect()를 호출할 필요가 없다.
	// 단지 객체만 삭제해주면 된다.
	while (!m_Effects.empty()) 
	{
		// effect 객체를 삭제한다.
		SAFE_DELETE(m_Effects.front());
		m_Effects.pop_front();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectManager::save(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	list<Effect*>::const_iterator itr = m_Effects.begin();
	for(; itr != m_Effects.end(); itr++) 
		(*itr)->save(ownerID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool EffectManager::isEffect(Effect::EffectClass EClass)
	throw()
{
	__BEGIN_TRY

	list<Effect*>::const_iterator itr = find_if (m_Effects.begin(), m_Effects.end(), isSameEffectClass(EClass)); 
	if (itr != m_Effects.end()) return true;
	return false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectManager::deleteEffect(ObjectID_t effectID)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	list<Effect*>::iterator current = m_Effects.begin();

	int i = 0;

	if (effectID == 0 )
	{
		for(current = m_Effects.begin(); current != m_Effects.end(); current++)
		{
			Effect* pEffect = *current;

			pEffect->unaffect();
			SAFE_DELETE(pEffect);

			i++;
		}

		m_Effects.clear();
	}
	else
	{
		for(current = m_Effects.begin(); current != m_Effects.end(); current++)
		{
			Effect* pEffect = *current;

			if (pEffect->getObjectID() == effectID)
			{
				m_Effects.erase(current);
				pEffect->unaffect();
				SAFE_DELETE(pEffect);
				return;
			}

			i++;
		}

		//cerr << "EffectManager::deleteEffect에서 effect를 찾지 못했습니다."<<endl;
		filelog("EffectManagerBug.txt", "there is no effect with effect id %d", effectID);
		Assert(false);
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectManager::deleteEffect(Effect::EffectClass EClass)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	list<Effect*>::iterator itr = find_if (m_Effects.begin(), m_Effects.end(), isSameEffectClass(EClass)); 
	if (itr != m_Effects.end()) 
	{
		Effect* pEffect = *itr;
		m_Effects.erase(itr);
		//pEffect->unaffect(); // 이거 하면 왜 안될까?
		SAFE_DELETE(pEffect);
	}
	else
	{
		//cerr << "EffectManager::deleteEffect에서 effect를 찾지 못했습니다."<<endl;
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectManager::deleteEffect(Creature* pCreature, Effect::EffectClass EClass)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	list<Effect*>::iterator itr = find_if (m_Effects.begin(), m_Effects.end(), isSameEffectClass(EClass)); 
	if (itr != m_Effects.end()) 
	{
		Effect* pEffect = *itr;

		m_Effects.erase(itr);

		if (pCreature)
		{
			if (pCreature->isFlag(EClass)) 
				pCreature->removeFlag(EClass);

			pEffect->destroy(pCreature->getName());
		}

		//pEffect->unaffect(); // 이거하면 안되네
		SAFE_DELETE(pEffect);
	}
	else
	{
		//cerr << "EffectManager::deleteEffect에서 effect를 찾지 못했습니다."<<endl;
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Effect* EffectManager::findEffect(Effect::EffectClass EClass) const
	throw()
{
	__BEGIN_TRY

	list<Effect*>::const_iterator itr = find_if (m_Effects.begin(), m_Effects.end(), isSameEffectClass(EClass)); 
	if (itr == m_Effects.end()) 
	{
		return NULL;
	}
	return *itr;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Effect* EffectManager::findEffect(ObjectID_t ObjectID) const
	throw()
{
	__BEGIN_TRY

	list<Effect*>::const_iterator itr = m_Effects.begin();
	for (; itr != m_Effects.end(); itr++)
	{
		Effect* pEffect = *itr;
		if (pEffect->getObjectID() == ObjectID) return pEffect;
	}

	return NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Effect* EffectManager::findEffect(Effect::EffectClass EClass, string EnemyName) const
	throw()
{
	__BEGIN_TRY

	list<Effect*>::const_iterator itr = m_Effects.begin();

	for(; itr != m_Effects.end(); itr++) 
	{
		if ((*itr)->getEffectClass() == EClass && EClass == Effect::EFFECT_CLASS_ENEMY_ERASE) {
			if (((EffectEnemyErase *)(*itr))->getEnemyName() == EnemyName) return *itr;
		}
	}

	return NULL;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectInfo* EffectManager::getEffectInfo()
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	EffectInfo* pEffectInfo;

	__BEGIN_PROFILE_EM("EM_GETEFFECTINFO");
	
	__BEGIN_PROFILE_EM("EM_NEW_EFFECTINFO");
	pEffectInfo = new EffectInfo();
	__END_PROFILE_EM("EM_NEW_EFFECTINFO");

	BYTE ListNum = 0;

	Timeval currentTime;

	__BEGIN_PROFILE_EM("EM_GETTIME");
	getCurrentTime(currentTime);
	__END_PROFILE_EM("EM_GETTIME");

	// 이펙트 정보 구성.
	for(list<Effect*>::const_iterator itr = m_Effects.begin(); itr != m_Effects.end(); itr++) 
	{
		Effect* pEffect = *itr;
		EffectID_t EffectID = pEffect->getSendEffectClass();

		/*
		bool bSend = true;
		
		switch (EffectID)
		{
			// 이 이펙트들은 서버에서만 쓰는 이펙트이기 때문에
			// 클라이언트에게 날려주지 않는다.
			case Effect::EFFECT_CLASS_AFTERMATH:
			case Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY:
			case Effect::EFFECT_CLASS_ENEMY_ERASE:
			case Effect::EFFECT_CLASS_RESTORE:
				bSend = false;
				break;
			default:
				break;
		}
		*/
		
		// 각 Effect의 constructor에서 client로 보낼 effect인지 아닌지를 결정한다.
		// by sigi. 2002.11.14
		bool bSend = pEffect->isBroadcastingEffect();

		if (bSend)
		{
			Timeval DeadLine;
			Turn_t Duration;

			__BEGIN_PROFILE_EM("EM_COMPUTE_TIME" )
			// 데드라인과 현재 시간을 빼서 남은 시간을 날려줘야 한다.
			DeadLine = (*itr)->getDeadline();
			Duration = DeadLine.tv_sec - currentTime.tv_sec;
			__END_PROFILE_EM("EM_COMPUTE_TIME" )

			if (EffectID == Effect::EFFECT_CLASS_BLOOD_DRAIN || EffectID == Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR) 
			{
				// Duration 날아가는 것이 WORD 형으로 날아가는데,
				// 2바이트라서 흡혈 시간 같은 경우에는 너무 길어
				// 오버플로우가 일어나게 된다.
				// 그래서 다른 이펙트 같은 경우에는 10을 곱해서 날리지만, 
				// 흡혈 이펙트는 10을 곱해서 날리지 않는다.
				pEffectInfo->addListElement(EffectID, Duration);
			} 
			else 
			{
				pEffectInfo->addListElement(EffectID, Duration * 10);
			}

			ListNum++;
		}
	}

	pEffectInfo->setListNum(ListNum);

	__END_PROFILE_EM("EM_GETEFFECTINFO");

	return pEffectInfo;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//
// sendEffectInfo
//
//////////////////////////////////////////////////////////////////////////////
// Effect 정보를 broadcasting한다.
// by sigi. 2002.11.14
//////////////////////////////////////////////////////////////////////////////
void EffectManager::sendEffectInfo(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	__BEGIN_PROFILE_EM("SEND_EFFECT_INFO");

	Assert(pCreature!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));
	
	Timeval currentTime;

	getCurrentTime(currentTime);

	// 주위에 뿌려준다.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pCreature->getObjectID());

	for(list<Effect*>::const_iterator itr = m_Effects.begin(); itr != m_Effects.end(); itr++) 
	{
		Effect* pEffect = *itr;

		if (pEffect->isBroadcastingEffect())
		{
			EffectID_t EffectID = pEffect->getSendEffectClass();
			gcAddEffect.setEffectID(EffectID);

			// 데드라인과 현재 시간을 빼서 남은 시간을 날려줘야 한다.
			Timeval DeadLine = (*itr)->getDeadline();
			Turn_t Duration = DeadLine.tv_sec - currentTime.tv_sec;

			if (EffectID == Effect::EFFECT_CLASS_BLOOD_DRAIN || EffectID == Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR)
			{
				// Duration 날아가는 것이 WORD 형으로 날아가는데,
				// 2바이트라서 흡혈 시간 같은 경우에는 너무 길어
				// 오버플로우가 일어나게 된다.
				// 그래서 다른 이펙트 같은 경우에는 10을 곱해서 날리지만, 
				// 흡혈 이펙트는 10을 곱해서 날리지 않는다.
				gcAddEffect.setDuration(Duration);
			} 
			else 
			{
				gcAddEffect.setDuration(Duration*10);
			}

			pZone->broadcastPacket(x, y, &gcAddEffect);
		}
	}

	__END_PROFILE_EM("SEND_EFFECT_INFO");

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectManager::addEffect (Effect* pEffect) 
     throw()
{
	__BEGIN_TRY

	Assert(pEffect != NULL);
	m_Effects.push_back(pEffect);

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/*int EffectManager::heartbeat () 
     throw(Error)
{
	__BEGIN_TRY
	__END_DEBUG

	int rvalue = 0;

	Timeval currentTime;
	getCurrentTime(currentTime);

	list<Effect*>::iterator before  = m_Effects.end();
	list<Effect*>::iterator current = m_Effects.begin();

	while (current != m_Effects.end()) 
	{
		Assert(*current != NULL);
		Effect* pEffect = *current;
		
		// 이펙트가 expire 되었으면 삭제한다.
		if (currentTime > pEffect->getDeadline()) 
		{
			if (before == m_Effects.end()) 
			{
				// first effect
				m_Effects.erase(current);
				current = m_Effects.begin();
			} 
			else 
			{
				// !first effect
				m_Effects.erase(current);
				current = before;
				current ++;
			}

			// *CAUTION
			// EffectBlood Drain일 경우에 루프 도는 것을 멈춰준다.
			// 왜? EffectBlood Drain안에서 Slayer의 데이터가 변형되기 때문에.
			// 다음 Effect를 처리 하면서 개가 될 수도 있다.
			// 다음에 슬레이어가 되었을때 나머지 이펙트들은 로딩하도록 한다.
			pEffect->unaffect();
			SAFE_DELETE(pEffect);

			rvalue++;
		} 
		else 
		{
			// expire 되지 않은 이펙트 중에,
			// 다음 affect 시간이 되었으면 affect한다.
			if (currentTime > pEffect->getNextTime()) 
			{
				pEffect->affect();
			}

			before = current ++;
		}

	}

	return rvalue;

	__BEGIN_DEBUG
	__END_CATCH
}
*/
//////////////////////////////////////////////////////////////////////////////
// 위의 heartbeat랑 똑같은데
// 시간을 받아오는거만 다르다. -_-;
// getCurrentTime() 안 할려고.. 음하하.. by sigi. 2002.5.8
//////////////////////////////////////////////////////////////////////////////
int EffectManager::heartbeat (const Timeval& currentTime)
     throw(Error)
{
	__BEGIN_TRY
	__END_DEBUG

	int rvalue = 0;

	__BEGIN_PROFILE_EM("EM_HEARTBEAT");

	list<Effect*>::iterator before  = m_Effects.end();
	list<Effect*>::iterator current = m_Effects.begin();

	while (current != m_Effects.end()) 
	{
		Assert(*current != NULL);
		Effect* pEffect = *current;

		// by sigi. for debugging. 2002.12.23
		m_LastEffectClass = (int)pEffect->getEffectClass();
		
		// 이펙트가 expire 되었으면 삭제한다.
		if (currentTime > pEffect->getDeadline()) 
		{
			if (before == m_Effects.end()) 
			{
				// first effect
				m_Effects.erase(current);
				current = m_Effects.begin();
			} 
			else 
			{
				// !first effect
				m_Effects.erase(current);
				current = before;
				current ++;
			}

			// *CAUTION
			// EffectBlood Drain일 경우에 루프 도는 것을 멈춰준다.
			// 왜? EffectBlood Drain안에서 Slayer의 데이터가 변형되기 때문에.
			// 다음 Effect를 처리 하면서 개가 될 수도 있다.
			// 다음에 슬레이어가 되었을때 나머지 이펙트들은 로딩하도록 한다.
			// 이벤트 기반으로 바꿔서 루프 도는거 안 멈춰도 되게 수정했다. -_-
			pEffect->unaffect();
			SAFE_DELETE(pEffect);

			rvalue++;
		} 
		else 
		{
			// expire 되지 않은 이펙트 중에,
			// 다음 affect 시간이 되었으면 affect한다.
			if (currentTime > pEffect->getNextTime()) 
			{
				pEffect->affect();
			}

			before = current ++;
		}

	}

	__END_PROFILE_EM("EM_HEARTBEAT");

	return rvalue;

	__BEGIN_DEBUG
	__END_CATCH
}

void EffectManager::setTimeOutAllEffect()
	throw()
{
	__BEGIN_TRY

	list<Effect*>::iterator itr = m_Effects.begin();
	list<Effect*>::iterator endItr = m_Effects.end();

	for (; itr != endItr; ++itr )
	{
		Assert(*itr != NULL);
		Effect* pEffect = *itr;

		pEffect->setDeadline(0);
	}

	__END_CATCH
}

