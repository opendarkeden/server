#include "EffectIceHailToTile.h"
#include "Gpackets/GCStatusCurrentHP.h" 

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "Zone.h"

void EffectIceHailToTile::affect() throw(Error)
{
	__BEGIN_TRY

	Tile& rTile = m_pZone->getTile( m_X, m_Y );
	const slist<Object*>& rList = rTile.getObjectList();

	slist<Object*>::const_iterator itr = rList.begin();
	slist<Object*>::const_iterator endItr = rList.end();

//	cout << "아프냐?" << endl;

	for ( ; itr != endItr ; ++itr )
	{
		Object* pObject = *itr;
		if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

		Creature* pCreature = dynamic_cast<Creature*>(pObject);
		if ( pCreature == NULL ) continue;

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

		gcHP.setCurrentHP( finalHP );
		m_pZone->broadcastPacket( m_X, m_Y, &gcHP );

//		cout << "아프다" << endl;
	}

	EffectWithWarning::affect();

	__END_CATCH
}


