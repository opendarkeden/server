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

#include "GCModifyInformation.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK4.h"

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
	
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	// 사용자를 가져온다.
	// !! 이미 존을 나갔을 수 있으므로 NULL이 될 수 있다.
	// by bezz. 2003.1.4
	Creature* pCastCreature = m_pZone->getCreature( m_UserObjectID );
	// 캐스터가 없으면 무시한다.
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

	// 현재 이펙트가 붙어있는 타일을 받아온다.
	// 중심타일 + 스플래쉬 타일
	for(int oX = -diff; oX <= diff; oX++)
	for(int oY = -diff; oY <= diff; oY++)
	{
		int tileX = m_X+oX;
		int tileY = m_Y+oY;
		if (!rect.ptInRect(tileX, tileY)) continue;

		Tile& tile = m_pZone->getTile(tileX, tileY);

		const forward_list<Object*>& oList = tile.getObjectList();
		forward_list<Object*>::const_iterator itr = oList.begin();
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
					// 원래 데미지와 스킬 데미지 보너스를 더한 최종 데미지를 구한다.
					bool bCriticalHit = false;
					Damage_t FinalDamage = 0;
					FinalDamage += computeDamage( pSlayer, pTargetCreature, SkillLevel/2, bCriticalHit );
					FinalDamage += m_Damage;

					// 흠...눈 크게 뜨고 보셈...필살 얍삽 코딩
					int DamageModifier = BombCrashWalkDamageModify[oX+2][oY+2];
					Damage_t TileDamage = getPercentValue( FinalDamage, DamageModifier );

					if(pTargetCreature != NULL && !pTargetCreature->isSlayer())
					{
						// 셕炬�襁�
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
// add by Coffee 藤속커깃넣崎�襁┿爪㏏�
						// 쇱꿎角뤠옵묑샌
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
								// 繫列賈痰세콘諒
								Player* pPlayer = pSlayer->getPlayer();
								pPlayer->sendPacket(&_GCSkillToObjectOK1);
								_GCSkillToObjectOK1.setSkillType(m_SkillType);
								_GCSkillToObjectOK1.setCEffectID(Effect::EFFECT_CLASS_COMA);
								_GCSkillToObjectOK1.setTargetObjectID(pTargetCreature->getObjectID());
								_GCSkillToObjectOK1.setDuration(delay);

							if ( pTargetCreature->isPC() )
							{
								// 繫列굳묑샌뚤蹶
								_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
								_GCSkillToObjectOK2.setSkillType(m_SkillType);
								_GCSkillToObjectOK2.setDuration(delay);

								pTargetCreature->getPlayer()->sendPacket(&_GCSkillToObjectOK2);
							}
							// 랙箇홍륩蛟포밤꺄斤口
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

	// 없어져 버렷!!
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
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalk::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBombCrashWalk::unaffect()
	
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
		<< ",Zone:" << (int64_t)m_pZone
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

