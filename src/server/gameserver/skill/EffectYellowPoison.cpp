//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectYellowPoison.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectYellowPoison.h"
#include "EffectProtectionFromPoison.h"
#include "EffectYellowPoisonToCreature.h"
#include "EffectLight.h"
#include "Slayer.h"
#include "Player.h"
#include "DB.h"
#include "SkillUtil.h"
#include "HitRoll.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectYellowPoison::EffectYellowPoison(Zone* pZone, ZoneCoord_t ZoneX, ZoneCoord_t ZoneY)
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X     = ZoneX;
	m_Y     = ZoneY;

	m_bVampire = false;
	m_bForce = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoison::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool EffectYellowPoison::affectCreature(Creature* pTargetCreature, bool bAffectByMove)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pTargetCreature != NULL);

	// 슬레이어도 아니고 아우스터즈도 아니면 안 걸린다.
	if (!pTargetCreature->isSlayer() && !pTargetCreature->isOusters() && !isForce()) return false;
	if (pTargetCreature->getCompetence() != 3) return false;

	// 안전지대인지 체크한다.
	// 2003.1.10 by bezz.Sequoia
	if ( !checkZoneLevelToHitTarget( pTargetCreature ) )
	{
		return false;
	}

	Player* pPlayer = pTargetCreature->getPlayer();
	Assert(pPlayer != NULL);
	
	// 상대방의 poison 저항력에 따라 걸릴 수도 안 걸릴 수도 있다...
	Resist_t resist = pTargetCreature->getResist(MAGIC_DOMAIN_POISON);

	// poison 저항력에 의해서 걸리지 않았다.
	if ( m_bVampire )
	{
		if (!HitRoll::isSuccessVampireCurse(m_Level, resist)) return false;
	}
	else
	{
		if (!HitRoll::isSuccessCurse(m_Level, resist)) return false;
	}

	// 중복시키지 않는다. ABCD 2001/03/21
	// 중복시킬때  OldSight을 얻는 과정에서 문제가 생겨서 Sight가 3으로 고착되는 버그가 있었던
	// 것 같다.
	if (!pTargetCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
	{
		Zone* pZone = pTargetCreature->getZone();

		// 플래그가 켜져있지 않으므로, 이펙트도 없겠지만, 혹시나 해서
		// 이미 걸려 있는 같은 이펙트가 있다면 이미 걸려 있던 것을 지워준다.
		if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			pTargetCreature->deleteEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		}

		Sight_t CurrentSight = pTargetCreature->getSight();
		Sight_t oldSight     = CurrentSight;

		// 이펙트를 생성하고, 파라미터를 지정해 준다.
		EffectYellowPoisonToCreature* pEffect = new EffectYellowPoisonToCreature(pTargetCreature);
		pEffect->setDeadline(m_Duration);
		pEffect->setOldSight(CurrentSight);
		pEffect->setLevel(m_Level);

		// Creature에 Effect Flag를 On 시킨다.
		pTargetCreature->setFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		pTargetCreature->addEffect(pEffect);

		// DB에 Effect를 생성한다.
		//pEffect->create(pTargetCreature->getName());

		// 원래 이 부분에 존 레벨을 체크해서, 안전지대일 경우,
		// GCChangeDarkLight에다 다크레벨을 0으로 해서 보내주었으나,
		// 필요가 없는 코드인 것 같아서 빼버렸다. -- 김성민
		GCChangeDarkLight gcChangeDarkLight;
		gcChangeDarkLight.setDarkLevel(15);
		gcChangeDarkLight.setLightLevel(1);
		pPlayer->sendPacket(&gcChangeDarkLight);

		pTargetCreature->setSight(pTargetCreature->getEffectedSight());
		GCModifyInformation gcMI;
		
		// 시야가 변했으므로.. 시야 update..
		if ( oldSight != pTargetCreature->getSight() )
		{
			pZone->updateScan(pTargetCreature, oldSight, pTargetCreature->getSight());
			gcMI.addShortData(MODIFY_VISION, pTargetCreature->getSight());
		}

		// send GCModifyInformation for sight change
		gcMI.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		gcMI.addLongData(MODIFY_DURATION, m_Duration);
		pPlayer->sendPacket(&gcMI);

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pTargetCreature->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		gcAddEffect.setDuration(m_Duration);

		pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect, pTargetCreature);
			
		return true;
	}

	return false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoison::affect(Creature* pTargetCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoison::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoison::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoison::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectYellowPoison::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectYellowPoison("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

void EffectYellowPoisonLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT LeftX, TopY, RightX, BottomY, Value1, Value2, Value3 FROM ZoneEffectInfo WHERE ZoneID = %d AND EffectID = %d", pZone->getZoneID(), (int)Effect::EFFECT_CLASS_YELLOW_POISON);

		while (pResult->next())
		{
			int count = 0;
			
			ZoneCoord_t left 	= pResult->getInt( ++count );
			ZoneCoord_t top 	= pResult->getInt( ++count );
			ZoneCoord_t right 	= pResult->getInt( ++count );
			ZoneCoord_t	bottom	= pResult->getInt( ++count );
			int 		value1	= pResult->getInt( ++count );
			int 		value2	= pResult->getInt( ++count );
			int 		value3	= pResult->getInt( ++count );

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			for ( int X = left ; X <= right ; X++ )
			for ( int Y = top ; Y <= bottom ; Y++ )
			{
				if ( rect.ptInRect(X, Y) )
				{
					Tile& tile = pZone->getTile(X,Y);
					if ( tile.canAddEffect() ) 
					{
						EffectYellowPoison* pEffect = new EffectYellowPoison(pZone, X, Y);
						pEffect->setForce(true);
						pEffect->setDuration( value1 );
						pEffect->setLevel( 100 );

						// 존 및 타일에다가 이펙트를 추가한다.
						pZone->registerObject(pEffect);
						pZone->addEffect(pEffect);
						tile.addEffect(pEffect);

					}

				}
			}

		}
	}
	END_DB(pStmt)

	__END_CATCH
}

EffectYellowPoisonLoader* g_pEffectYellowPoisonLoader = NULL;

