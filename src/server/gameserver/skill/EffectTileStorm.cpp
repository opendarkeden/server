//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTileStorm.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectTileStorm.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "SkillInfo.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"

int StormDamageModify[5][5] =
{
	{ 50, 50,  50, 50, 50 },
	{ 50, 75,  75, 75, 50 },
	{ 50, 75, 100, 75, 50 },
	{ 50, 75,  75, 75, 50 },
	{ 50, 50,  50, 50, 50 }
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTileStorm::EffectTileStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
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
void EffectTileStorm::affect()
	throw(Error)
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

	VSRect rect(0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1);
	if( !rect.ptInRect( m_X, m_Y ) ) return;

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

				if ( bPK && bZoneLevelCheck && bHitRoll )
				{
					// 원래 데미지와 스킬 데미지 보너스를 더한 최종 데미지를 구한다.
					bool bCriticalHit = false;
					Damage_t FinalDamage = 0;
					FinalDamage += computeDamage( pSlayer, pTargetCreature, SkillLevel/2, bCriticalHit );
					FinalDamage += m_Damage;

					// 흠...눈 크게 뜨고 보셈...필살 얍삽 코딩
					int DamageModifier = StormDamageModify[oX+2][oY+2];
					Damage_t TileDamage = getPercentValue( FinalDamage, DamageModifier );

					if(pTargetCreature != NULL && !pTargetCreature->isSlayer())
					{
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

						if ( TileDamage > maxDamage ) maxDamage = TileDamage;

						if ( pTargetCreature->isPC() )
						{
							// 공격을 당한 뱀파이어에게 
							_GCSkillToObjectOK2.setObjectID(1);
							_GCSkillToObjectOK2.setSkillType(SKILL_ATTACK_MELEE);
							_GCSkillToObjectOK2.setDuration(0);

							pTargetCreature->getPlayer()->sendPacket(&_GCSkillToObjectOK2);
						}

						_GCSkillToObjectOK4.setTargetObjectID( pTargetCreature->getObjectID() );
						_GCSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						_GCSkillToObjectOK4.setDuration(0);
						m_pZone->broadcastPacket( tileX, tileY, &_GCSkillToObjectOK4, pTargetCreature);

						bHit = true;

						if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
						EnemyNum++;
					}
				}
			}
		}
	}

	if ( bHit )
	{
		GCModifyInformation gcMI;
		shareAttrExp( pSlayer, maxDamage, 8, 1, 1, gcMI );
		increaseDomainExp( pSlayer, DomainType, pSkillInfo->getPoint(), gcMI, maxEnemyLevel, EnemyNum );
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
void EffectTileStorm::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTileStorm::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTileStorm::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& EffectedTile = m_pZone->getTile(m_X, m_Y);
	EffectedTile.deleteEffect(m_ObjectID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTileStorm::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectTileStorm("
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

EffectTileStormLoader* g_pEffectTileStormLoader = NULL;
