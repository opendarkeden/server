//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDragonTornado.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectDragonTornado.h"
#include "PlayerCreature.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDragonTornado::EffectDragonTornado(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_UserOID = 0;
	m_bCanSplit = true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonTornado::affect()
	throw(Error)
{
	__BEGIN_TRY

	setNextTime(10);

	if ( m_pZone == NULL || !isValidZoneCoord( m_pZone, m_X, m_Y ) ) return;

	int action = rand()%11;
	if ( !m_bCanSplit ) action = rand()%9;

	if ( action == 0 )
	{
	}
	else if ( action <= 8 )
	{
		Dir_t dir = rand()%8;
		ZoneCoord_t newX = m_X + dirMoveMask[dir].x;
		ZoneCoord_t newY = m_Y + dirMoveMask[dir].y;

		if ( isValidZoneCoord( m_pZone, newX, newY ) && m_pZone->getTile(newX, newY).canAddEffect() )
		{
			GCAddEffectToTile gcAE;
			gcAE.setEffectID( getSendEffectClass() );
			gcAE.setObjectID( getObjectID() );
			gcAE.setDuration( getRemainDuration() );
			gcAE.setXY( newX, newY );
			m_pZone->broadcastPacket( newX, newY, &gcAE );

			m_pZone->getTile(m_X, m_Y).deleteEffect( getObjectID() );
			m_pZone->getTile(newX, newY).addEffect(this);
			m_X = newX;
			m_Y = newY;
		}
	}
	else
	{
		Dir_t dir = rand()%8;
		ZoneCoord_t newX = m_X + dirMoveMask[dir].x;
		ZoneCoord_t newY = m_Y + dirMoveMask[dir].y;

		if ( isValidZoneCoord( m_pZone, newX, newY ) && m_pZone->getTile(newX, newY).canAddEffect() )
		{
			EffectDragonTornado* pEffect = new EffectDragonTornado( m_pZone, newX, newY );
			pEffect->setDamage( m_ChildDamage );
			pEffect->setUserOID( m_UserOID );
			pEffect->setSplit( false );
			pEffect->setDeadline( getRemainDuration() );
			pEffect->setNextTime( 10 );
			m_pZone->registerObject( pEffect );

			GCAddEffectToTile gcAE;
			gcAE.setEffectID( pEffect->getSendEffectClass() );
			gcAE.setObjectID( pEffect->getObjectID() );
			gcAE.setDuration( pEffect->getRemainDuration() );
			gcAE.setXY( newX, newY );
			m_pZone->broadcastPacket( newX, newY, &gcAE );

			m_pZone->getTile(newX, newY).addEffect(pEffect);
			m_pZone->addEffect( pEffect );
		}
	}

	Tile& tile = m_pZone->getTile(m_X, m_Y);

	slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::iterator itr = oList.begin();

	for ( ; itr != oList.end(); ++itr )
	{
		Object* pObject = *itr;
		if ( pObject == NULL ) continue;

		if ( pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;
		Creature* pCreature = dynamic_cast<Creature*>(pObject);
		affect(pCreature);
	}

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonTornado::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Creature* pCastCreature = pZone->getCreature( m_UserOID );
	if ( pCastCreature == NULL ) return;

	// 자신은 맞지 않는다
	// 무적상태 체크. by sigi. 2002.9.5
	if (pCreature->getObjectID()==m_UserOID
		|| !canAttack( pCastCreature, pCreature )
		|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
		|| !checkZoneLevelToHitTarget( pCreature )
		|| pCreature->isSlayer()
	)
	{
		return;
	}

	if ( pCastCreature != NULL && pCastCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCastCreature);
		if ( pMonster != NULL && !pMonster->isEnemyToAttack( pCreature ) ) return;
	}

	bool isStun = false;

	if ( pCastCreature != NULL )
	{
		int myLevel = pCastCreature->getLevel();
		int otherLevel = pCreature->getLevel();
		int ratio = 50 + myLevel - otherLevel;
		if ( (rand()%100) < ratio ) isStun = true;
	}

	//GCModifyInformation gcMI;
	GCModifyInformation gcAttackerMI;
	GCSkillToObjectOK6 gcSkillToObjectOK6;

	if (pCreature->isSlayer()) 
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		::setDamage( pSlayer, m_Damage, pCastCreature, SKILL_DRAGON_TORNADO, &gcSkillToObjectOK6, &gcAttackerMI);

/*						Player* pPlayer = pSlayer->getPlayer();
		Assert(pPlayer != NULL);
		pPlayer->sendPacket(&gcMI);*/

	} 
	else if (pCreature->isVampire())
	{
		// 뱀파이어가 사용했을 경우 뱀파이어는 중심 타일을 제외하고는 맞지 않는다.
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		::setDamage( pVampire, m_Damage, pCastCreature, SKILL_DRAGON_TORNADO, &gcSkillToObjectOK6, &gcAttackerMI );

/*						Player* pPlayer = pVampire->getPlayer();
		Assert(pPlayer != NULL);
		pPlayer->sendPacket(&gcMI);*/
	}
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		::setDamage( pOusters, m_Damage, pCastCreature, SKILL_DRAGON_TORNADO, &gcSkillToObjectOK6, &gcAttackerMI );

/*						Player* pPlayer = pOusters->getPlayer();
		Assert(pPlayer != NULL);
		pPlayer->sendPacket(&gcMI);*/
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		::setDamage( pMonster, m_Damage, pCastCreature, SKILL_DRAGON_TORNADO, NULL, &gcAttackerMI );

		if ( pCastCreature != NULL ) pMonster->addEnemy( pCastCreature );

		// delay설정 ( + 1초 )
		if (!pMonster->isMaster() && isStun )
		{
			Timeval delay;
			delay.tv_sec  = 1;
			delay.tv_usec = 0;//500000;
			pMonster->addAccuDelay(delay);
		}
	}

	SkillType_t skillType = (isStun)?SKILL_DRAGON_TORNADO:SKILL_ATTACK_MELEE;

	// user한테는 맞는 모습을 보여준다.
	if (pCreature->isPC())
	{
		gcSkillToObjectOK6.setSkillType( skillType );
		gcSkillToObjectOK6.setDuration(0);
		pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK6);
	}

	GCSkillToObjectOK4 gcSkillToObjectOK4;
	gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
	gcSkillToObjectOK4.setSkillType( skillType );
	gcSkillToObjectOK4.setDuration(0);

	m_pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcSkillToObjectOK4, pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonTornado::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonTornado::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDragonTornado" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	GCDeleteEffectFromTile gcDT;
	gcDT.setXY(m_X, m_Y);
	gcDT.setObjectID(getObjectID());
	gcDT.setEffectID(getSendEffectClass());
	m_pZone->broadcastPacket( m_X, m_Y, &gcDT );

	//cout << "EffectDragonTornado" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDragonTornado::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectDragonTornado("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

