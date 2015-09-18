//----------------------------------------------------------------------
//
// Filename    : EffectContinualGroundAttack.cpp
// Written by  : elca
//
//----------------------------------------------------------------------

// include files
#include "Assert1.h"
#include "EffectContinualGroundAttack.h"
#include "EffectGroundAttack.h"
#include "EffectMeteorStrike.h"
#include "MonsterManager.h"
#include "PCManager.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "SkillUtil.h"
#include "GCAddEffectToTile.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectContinualGroundAttack::EffectContinualGroundAttack (Zone* pZone , EffectClass attackEffect, Turn_t delay) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone!=NULL);

	m_pZone = pZone;

	m_AttackEffect = attackEffect;

	m_Delay = delay;

	setNextTime(10);	// 1초 후 시작
	setDeadline(delay);

	m_MinNumber = 1;
	m_MaxNumber = 1;

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectContinualGroundAttack::~EffectContinualGroundAttack () 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectContinualGroundAttack::affect()
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pZone!=NULL);

	int creatureNum = m_pZone->getPCManager()->getSize()
						+ m_pZone->getMonsterManager()->getSize();

	// 부하를 조금이라도 줄이기 위해서..
	// 존에 공격받을 캐릭터가 있어야지 effect를 붙이지..
	if (creatureNum > 0)
	{
		// zone의 특정 위치에 effect를 출력하고 damage를 준다.
		int range = min(100, (m_MaxNumber-m_MinNumber));		// 동시에 1~100사이
		int number = (range>0? m_MinNumber + rand()%range : m_MinNumber);

		VSRect rect(0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1);

		// m_MinNumber ~ m_MaxNumber 개의 공격
		for (int i=0; i<number; i++)
		{
			const BPOINT& pt = m_pZone->getRandomEmptyTilePosition();

			if (!rect.ptInRect(pt.x, pt.y)) continue;

			// 중심 타일 체크
			Tile& tile = m_pZone->getTile(pt.x, pt.y);

			int X = pt.x;
			int Y = pt.y;

			if (!tile.canAddEffect()) continue;

			int	DamagePercent = 100;
		
			// 이펙트 오브젝트를 생성한다.
			Effect* pAttackEffect = NULL;

			switch (m_AttackEffect)
			{
				case EFFECT_CLASS_GROUND_ATTACK :
				{
					// 같은 이펙트가 이미 존재한다면 더 쎈 damage로 설정한다.
					Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GROUND_ATTACK);
					if (pOldEffect != NULL)
					{
						EffectGroundAttack* pGAEffect = dynamic_cast<EffectGroundAttack*>(pOldEffect);
						pGAEffect->setDamagePercent(max(DamagePercent, pGAEffect->getDamagePercent()));
						continue;
					}

					EffectGroundAttack* pEffect = new EffectGroundAttack(m_pZone, X, Y);
					pEffect->setDeadline(22); // 2초+알파
					pEffect->setDamagePercent(DamagePercent);

					pAttackEffect = pEffect;
				}
				break;

				case EFFECT_CLASS_METEOR_STRIKE :
				{
					// 같은 이펙트가 있다면 삭제한다.
					Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_METEOR_STRIKE);
					if (pOldEffect != NULL )
					{
						ObjectID_t effectID = pOldEffect->getObjectID();
						m_pZone->deleteEffect(effectID);
					}

					EffectMeteorStrike* pEffect = new EffectMeteorStrike(m_pZone, X, Y);
					pEffect->setDeadline(10); // 1초

					// 400 ~ 600 100%
					// 200 ~ 300 50%
					// 100 ~ 150 25%
					pEffect->setDamage(400+rand()%200);

					pAttackEffect = pEffect;
				}
				break;

				default :
				break;
			}


			if (pAttackEffect!=NULL)
			{
				// 타일에 붙은 이펙트는 OID를 받아야 한다.
				ObjectRegistry & objectregister = m_pZone->getObjectRegistry();
				objectregister.registerObject(pAttackEffect);
			
				// 존 및 타일에다가 이펙트를 추가한다.
				m_pZone->addEffect(pAttackEffect);	
				tile.addEffect(pAttackEffect);

				// 가운데꺼만 이펙트를 보여준다.
				GCAddEffectToTile gcAddEffectToTile;
				gcAddEffectToTile.setEffectID(pAttackEffect->getEffectClass());
				gcAddEffectToTile.setObjectID(pAttackEffect->getObjectID());
				gcAddEffectToTile.setXY(X, Y);
				gcAddEffectToTile.setDuration(20);	// 2초

				m_pZone->broadcastPacket(X, Y, &gcAddEffectToTile);
			}
		}
	}

	setNextTime(m_Delay);
	
	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect()
//--------------------------------------------------------------------
void EffectContinualGroundAttack::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectContinualGroundAttack::toString () const 
	throw()
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectContinualGroundAttack("
				<< "ZoneID:" << (int)m_pZone->getZoneID();
	}

	msg << ",Delay:" << (int)m_Delay
		<< ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}
