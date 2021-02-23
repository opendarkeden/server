//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBombCrashWalk.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectBombCrashWalk.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "SkillInfo.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"

#include "EffectBombCrashWalkToEnemy.h"


int BombCrashWalkDamageModify[5][5] =
{
	{ 50, 50,  50, 50, 50 },
	{ 50, 75,  75, 75, 50 },
	{ 50, 75, 100, 75, 50 },
	{ 50, 75,  75, 75, 50 },
	{ 50, 50,  50, 50, 50 }
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBombCrashWalk::EffectBombCrashWalk(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_Damage = 0;
	m_UserObjectID = 0;
	m_StormTime = 0;
	m_Tick = 0;
	m_SkillType = SKILL_MAX;
	m_bLarge = true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalk::affect()
	throw(Error)
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	// »ç¿ëÀÚ¸¦ °¡Á®¿Â´Ù.
	// !! ÀÌ¹Ì Á¸À» ³ª°¬À» ¼ö ÀÖÀ¸¹Ç·Î NULLÀÌ µÉ ¼ö ÀÖ´Ù.
	// by bezz. 2003.1.4
	Creature* pCastCreature = m_pZone->getCreature( m_UserObjectID );
	// Ä³½ºÅÍ°¡ ¾øÀ¸¸é ¹«½ÃÇÑ´Ù.
	if ( pCastCreature == NULL )
		return;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCastCreature);

	SkillSlot* pSkillSlot	= pSlayer->hasSkill( m_SkillType );
	SkillInfo* pSkillInfo	= g_pSkillInfoManager->getSkillInfo( m_SkillType );
	SkillDomainType_t DomainType = pSkillInfo->getDomainType();
	SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

	int iMode=0;
	if (SkillLevel < 33)
	{
		iMode=0;
	}
	else if (SkillLevel <66)
	{
		iMode=1;
	}
	else if (SkillLevel <= 100)
	{
		iMode=2;
	}
	
	
	
	

	VSRect rect(0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1);
	if( !rect.ptInRect( m_X, m_Y ) ) return;

	GCSkillToObjectOK1 _GCSkillToObjectOK1;
	GCSkillToObjectOK2 _GCSkillToObjectOK2;
	GCSkillToObjectOK4 _GCSkillToObjectOK4;

	bool bHit = false;
	Damage_t maxDamage=0;

	int diff = 1;
	if ( m_bLarge ) diff = 2;

	Level_t maxEnemyLevel = 0;
	uint EnemyNum = 0;

	// ÇöÀç ÀÌÆåÆ®°¡ ºÙ¾îÀÖ´Â Å¸ÀÏÀ» ¹Þ¾Æ¿Â´Ù.
	// Áß½ÉÅ¸ÀÏ + ½ºÇÃ·¡½¬ Å¸ÀÏ
	for(int oX = -diff; oX <= diff; oX++)
	for(int oY = -diff; oY <= diff; oY++)
	{
		int tileX = m_X+oX;
		int tileY = m_Y+oY;
		if (!rect.ptInRect(tileX, tileY)) continue;

		Tile& tile = m_pZone->getTile(tileX, tileY);

		const slist<Object*>& oList = tile.getObjectList();
		slist<Object*>::const_iterator itr = oList.begin();
		for ( ; itr != oList.end(); itr++ )
		{
			Object* pObject = *itr;
			Assert( pObject != NULL );

			if ( pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
			{
				Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
				Assert( pTargetCreature != NULL );

				if ( pTargetCreature->getObjectID() == m_UserObjectID
					|| !canAttack( pCastCreature, pTargetCreature )
					|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) )
				{
					continue;
				}

				bool bPK				= verifyPK( pSlayer, pTargetCreature );
				bool bZoneLevelCheck	= checkZoneLevelToHitTarget( pTargetCreature );
				bool bHitRoll			= HitRoll::isSuccess( pSlayer, pTargetCreature, SkillLevel );			
				
				
				if ( bPK && bZoneLevelCheck && bHitRoll)
				{
					// ¿ø·¡ µ¥¹ÌÁö¿Í ½ºÅ³ µ¥¹ÌÁö º¸³Ê½º¸¦ ´õÇÑ ÃÖÁ¾ µ¥¹ÌÁö¸¦ ±¸ÇÑ´Ù.
					bool bCriticalHit = false;
					Damage_t FinalDamage = 0;
					FinalDamage += computeDamage( pSlayer, pTargetCreature, SkillLevel/2, bCriticalHit );
					FinalDamage += m_Damage;

					// Èì...´« Å©°Ô ¶ß°í º¸¼À...ÇÊ»ì ¾å»ð ÄÚµù
					int DamageModifier = BombCrashWalkDamageModify[oX+2][oY+2];
					Damage_t TileDamage = getPercentValue( FinalDamage, DamageModifier );

					if(pTargetCreature != NULL && !pTargetCreature->isSlayer())
					{
						// ¼ÆËãÉËº¦
						if(pTargetCreature->isPC())
						{
							GCModifyInformation gcMI;
							::setDamage( pTargetCreature, TileDamage, pSlayer, m_SkillType , &gcMI );
							pTargetCreature->getPlayer()->sendPacket( &gcMI );

						}
						else if(pTargetCreature->isMonster())
						{
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);

							::setDamage( pMonster, TileDamage, pSlayer, m_SkillType );

							pMonster->addEnemy( pSlayer );
						}
// add by Coffee Ôö¼ÓÄ¿±ê³ÖÐøÉËº¦»ðÐ§¹û
						// ¼ì²âÊÇ·ñ¿É¹¥»÷
						bool bAttackCheck		= false;
						int rn=Random(10,100);
						if (rn > 70 && iMode ==0)
							bAttackCheck=true;
						if (rn > 45 && iMode ==1)
							bAttackCheck=true;
						if (rn > 25 && iMode ==2)
							bAttackCheck=true;
						if (bAttackCheck)
						{
						
							if (pTargetCreature->isFlag( Effect::EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY)) continue;
							
							EffectBombCrashWalkToEnemy* pEffect = new EffectBombCrashWalkToEnemy(pTargetCreature);
							Assert(pEffect != NULL);
							Turn_t delay=0;
							switch(iMode)
							{
								case 0:
									delay=500;
									break;
								case 1:
									delay=650;
									break;
								case 2:
									delay=800;
									break;
							}
							pEffect->setDeadline(delay);
							pEffect->setTick(30);//output.Tick);
							pEffect->setPoint(delay / 10);//output.Damage); 
							pEffect->setUserObjectID( pSlayer->getObjectID() );
							pEffect->setNextTime(0);

				
							pTargetCreature->addEffect(pEffect);
							pTargetCreature->setFlag(Effect::EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY);
							
	// end by Coffee 2007-3-6

							if ( TileDamage > maxDamage ) maxDamage = TileDamage;
								// Í¨ÖªÊ¹ÓÃ¼¼ÄÜÕß
								Player* pPlayer = pSlayer->getPlayer();
								pPlayer->sendPacket(&_GCSkillToObjectOK1);
								_GCSkillToObjectOK1.setSkillType(m_SkillType);
								_GCSkillToObjectOK1.setCEffectID(Effect::EFFECT_CLASS_COMA);
								_GCSkillToObjectOK1.setTargetObjectID(pTargetCreature->getObjectID());
								_GCSkillToObjectOK1.setDuration(delay);

							if ( pTargetCreature->isPC() )
							{
								// Í¨Öª±»¹¥»÷¶ÔÏó
								_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
								_GCSkillToObjectOK2.setSkillType(m_SkillType);
								_GCSkillToObjectOK2.setDuration(delay);

								pTargetCreature->getPlayer()->sendPacket(&_GCSkillToObjectOK2);
							}
							// ·¢ËÍÈ«·þÎñÆ÷¹ã²¥ÐÅÏ¢
							_GCSkillToObjectOK4.setTargetObjectID( pTargetCreature->getObjectID() );
							_GCSkillToObjectOK4.setSkillType( m_SkillType );
							_GCSkillToObjectOK4.setDuration(delay);
							m_pZone->broadcastPacket( tileX, tileY, &_GCSkillToObjectOK4, pTargetCreature);

							bHit = true;
						}
// 
// 						if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
// 						EnemyNum++;
					}
				}
			}
		}
	}

	if ( bHit )
	{
		GCModifyInformation gcMI;
		//shareAttrExp( pSlayer, maxDamage, 8, 1, 1, gcMI );
		//increaseDomainExp( pSlayer, DomainType, pSkillInfo->getPoint(), gcMI, maxEnemyLevel, EnemyNum );
		increaseSkillExp( pSlayer, DomainType, pSkillSlot, pSkillInfo, gcMI );

		pSlayer->getPlayer()->sendPacket( &gcMI );
	}

	// ¾ø¾îÁ® ¹ö·Ç!!
	m_StormTime--;
	if ( m_StormTime <= 0 )
		setDeadline( 0 );
	else
		setNextTime( m_Tick );

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalk::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalk::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalk::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& EffectedTile = m_pZone->getTile(m_X, m_Y);
	EffectedTile.deleteEffect(m_ObjectID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBombCrashWalk::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectBombCrashWalk("
		<< "ObjectID:" << (int)getObjectID()
		<< ",Zone:" << (int)m_pZone
		<< ",X:" << (int)m_X
		<< ",Y:" << (int)m_Y
		<< ",Damage:" << (int)m_Damage
		<< ",UserOBjectID:" << (int)m_UserObjectID
		<< ",StormTime:" << (int)m_StormTime
		<< ",Tick:" << (int)m_Tick
		<< ",SkillType:" << (int)m_SkillType
		<< ")";

	return msg.toString();

	__END_CATCH

}

