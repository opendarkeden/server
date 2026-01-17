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

#include "GCModifyInformation.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK4.h"

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
	
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	// ����ڸ� �����´�.
	// !! �̹� ���� ������ �� �����Ƿ� NULL�� �� �� �ִ�.
	// by bezz. 2003.1.4
	Creature* pCastCreature = m_pZone->getCreature( m_UserObjectID );
	// ĳ���Ͱ� ������ �����Ѵ�.
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

	// ���� ����Ʈ�� �پ��ִ� Ÿ���� �޾ƿ´�.
	// �߽�Ÿ�� + ���÷��� Ÿ��
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

				if ( bPK && bZoneLevelCheck && bHitRoll )
				{
					// ���� �������� ��ų ������ ���ʽ��� ���� ���� �������� ���Ѵ�.
					bool bCriticalHit = false;
					Damage_t FinalDamage = 0;
					FinalDamage += computeDamage( pSlayer, pTargetCreature, SkillLevel/2, bCriticalHit );
					FinalDamage += m_Damage;

					// ��...�� ũ�� �߰� ����...�ʻ� ��� �ڵ�
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
							// ������ ���� �����̾�� 
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

	// ������ ����!!
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
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTileStorm::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTileStorm::unaffect()
	
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
		<< ",Zone:" << (long)m_pZone
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
