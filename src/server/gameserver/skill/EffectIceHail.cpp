//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceHail.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectIceHail.h"
#include "Slayer.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"
#include "EffectIceHailToTile.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectIceHail::EffectIceHail(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_CasterID = 0;

	setBroadcastingEffect(false);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHail::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectIceHail" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 시전자를 가져온다.
	Creature* pCastCreature = m_pZone->getCreature( m_CasterID );
	if ( pCastCreature == NULL ) return;

	for ( int i = -m_Range; i <= m_Range; ++i )
	{
		for ( int j = -m_Range; j <= m_Range; ++j )
		{
			Tile& rTile = m_pZone->getTile( m_X + i, m_Y + j );
			const slist<Object*>& rList = rTile.getObjectList();

			slist<Object*>::const_iterator itr = rList.begin();
			slist<Object*>::const_iterator endItr = rList.end();

		//	cout << "아프냐?" << endl;

			for ( ; itr != endItr ; ++itr )
			{
				Object* pObject = *itr;
				if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

				Creature* pCreature = dynamic_cast<Creature*>(pObject);
				if ( pCreature == NULL || pCreature->getObjectID() == m_CasterID ) continue;
				if ( !canAttack( pCastCreature, pCreature ) ) continue;

				if ( pCastCreature->isMonster() )
				{
					Monster* pGDR = dynamic_cast<Monster*>(pCastCreature);
					if ( pGDR != NULL )
					{
						if ( !pGDR->isEnemyToAttack( pCreature ) ) continue;
					}
				}

				HP_t currentHP, finalHP = 0;
				GCStatusCurrentHP gcHP;
				gcHP.setObjectID( pCreature->getObjectID() );

				if ( pCreature->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
					Assert( pSlayer != NULL );

					currentHP = pSlayer->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)m_Damage );

					pSlayer->setHP( finalHP );
				}
				else if ( pCreature->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
					Assert( pVampire != NULL );

					currentHP = pVampire->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)m_Damage );

					pVampire->setHP( finalHP );
				}
				else if ( pCreature->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
					Assert( pOusters != NULL );

					currentHP = pOusters->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)m_Damage );

					pOusters->setHP( finalHP );
				}
				else continue;

				gcHP.setCurrentHP( finalHP );
				m_pZone->broadcastPacket( m_X, m_Y, &gcHP );

		//		cout << "아프다" << endl;
			}

		}
	}

	setNextTime(m_Tick);

	//cout << "EffectIceHail" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHail::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHail::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHail::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectIceHail" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectIceHail" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectIceHail::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectIceHail("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

