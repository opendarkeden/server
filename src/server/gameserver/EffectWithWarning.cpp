#include "EffectWithWarning.h"

#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

#include "skill/EffectIceFieldToCreature.h"

#include "Zone.h"
#include "Tile.h"

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "ZoneUtil.h"
#include "Utility.h"

Effect::EffectClass EffectWithWarning::getEffectClass() const throw()
{
	if ( m_State ) return m_MainEffect;
	return m_SignEffect;
}

void EffectWithWarning::start()
{
//	cout << "시작하지롱" << m_SignDuration << endl;

	setNextTime( m_SignDuration );
	setDeadline( m_SignDuration + m_MainDuration );

	GCAddEffectToTile gcAET;
	gcAET.setXY( m_X, m_Y );
	gcAET.setObjectID( getObjectID() );
	gcAET.setEffectID( m_SignEffect );
	gcAET.setDuration( m_SignDuration );

	m_pZone->broadcastPacket( m_X, m_Y, &gcAET );
	m_State = false;

//	cout << m_pZone->getZoneID() << ", " << m_X << ", " << m_Y << endl;
}

void EffectWithWarning::affect() throw(Error)
{
	__BEGIN_TRY

//	cout << "때리지롱" << m_X << ", " << m_Y << endl;

	if ( !m_State )
	{
		GCDeleteEffectFromTile gcDET;
		gcDET.setXY( m_X, m_Y );
		gcDET.setObjectID( getObjectID() );
		gcDET.setEffectID( m_SignEffect );

		m_pZone->broadcastPacket( m_X, m_Y, &gcDET );
		setNextTime( m_MainDuration + m_SignDuration );
	//	m_State = 1;
	//	m_pZone->registerObject(this);

		GCAddEffectToTile gcAET;
		gcAET.setXY( m_X, m_Y );
		gcAET.setObjectID( getObjectID() );
		gcAET.setEffectID( m_MainEffect );
		gcAET.setDuration( m_MainDuration );

		m_pZone->broadcastPacket( m_X, m_Y, &gcAET );

//		setDeadline( m_MainDuration );
		m_State = true;
	}

	__END_CATCH
}

void EffectWithWarning::unaffect() throw(Error)
{
	__BEGIN_TRY

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	GCDeleteEffectFromTile gcDET;
	gcDET.setXY( m_X, m_Y );
	gcDET.setObjectID( getObjectID() );
	gcDET.setEffectID( m_MainEffect );

	m_pZone->broadcastPacket( m_X, m_Y, &gcDET );

	__END_CATCH
}

void EffectIcicle::affect() throw(Error)
{
	__BEGIN_TRY

	EffectWithWarning::affect();

	Dir_t dir = 0;

	for ( ; dir <= 8 ; dir+=2 )
	{
		ZoneCoord_t X = m_X;
		ZoneCoord_t Y = m_Y;

		if ( dir != 8 )
		{
			X += dirMoveMask[dir].x;
			Y += dirMoveMask[dir].y;
		}

		if ( !isValidZoneCoord( m_pZone, X, Y ) ) continue;

		Tile& rTile = m_pZone->getTile( X, Y );
		const slist<Object*>& rList = rTile.getObjectList();

		slist<Object*>::const_iterator itr = rList.begin();
		slist<Object*>::const_iterator endItr = rList.end();

	//	cout << "아프냐?" << endl;

		for ( ; itr != endItr ; ++itr )
		{
			Object* pObject = *itr;
			if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			if ( pCreature == NULL || pCreature->isFlag( Effect::EFFECT_CLASS_NO_DAMAGE ) ) continue;

			HP_t currentHP, finalHP = 0;
			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pCreature->getObjectID() );

			if ( pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert( pSlayer != NULL );

				currentHP = pSlayer->getHP();
				finalHP = currentHP - min( currentHP, (HP_t)(pSlayer->getHP(ATTR_MAX)*0.2) );

				pSlayer->setHP( finalHP );
			}
			else if ( pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				Assert( pVampire != NULL );

				currentHP = pVampire->getHP();
				finalHP = currentHP - min( currentHP, (HP_t)(pVampire->getHP(ATTR_MAX)*0.2) );

				pVampire->setHP( finalHP );
			}
			else if ( pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				Assert( pOusters != NULL );

				currentHP = pOusters->getHP();
				finalHP = currentHP - min( currentHP, (HP_t)(pOusters->getHP(ATTR_MAX)*0.2) );

				pOusters->setHP( finalHP );
			}
			else continue;

			gcHP.setCurrentHP( finalHP );
			m_pZone->broadcastPacket( m_X, m_Y, &gcHP );

//			cout << "아프다" << endl;

			if ( pCreature->isFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE) ) continue;

			// 이팩트 클래스를 만들어 붙인다.
			EffectIceFieldToCreature* pEffect = new EffectIceFieldToCreature(pCreature);
			pEffect->setDeadline(50);
			pCreature->addEffect(pEffect);
			pCreature->setFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pCreature->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);
			gcAddEffect.setDuration(50);

			m_pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );
		}
	}

	__END_CATCH
}

void EffectLargeIcicle::affect() throw(Error)
{
	__BEGIN_TRY

	EffectWithWarning::affect();

	ZoneCoord_t X = m_X;
	ZoneCoord_t Y = m_Y;

	for ( int i=-1; i<=1; ++i )
	for ( int j=-1; j<=1; ++j )
	{
		X = m_X + i;
		Y = m_Y + j;

		if ( isValidZoneCoord( m_pZone, X, Y ) )
		{
			Tile& rTile = m_pZone->getTile( X, Y );
			const slist<Object*>& rList = rTile.getObjectList();

			slist<Object*>::const_iterator itr = rList.begin();
			slist<Object*>::const_iterator endItr = rList.end();

			for ( ; itr != endItr ; ++itr )
			{
				Object* pObject = *itr;
				if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

				Creature* pCreature = dynamic_cast<Creature*>(pObject);
				if ( pCreature == NULL || pCreature->isFlag( Effect::EFFECT_CLASS_NO_DAMAGE ) ) continue;

				HP_t currentHP, finalHP = 0;
				GCStatusCurrentHP gcHP;
				gcHP.setObjectID( pCreature->getObjectID() );

				if ( pCreature->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
					Assert( pSlayer != NULL );

					currentHP = pSlayer->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)(pSlayer->getHP(ATTR_MAX)*0.4) );

					pSlayer->setHP( finalHP );
				}
				else if ( pCreature->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
					Assert( pVampire != NULL );

					currentHP = pVampire->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)(pVampire->getHP(ATTR_MAX)*0.4) );

					pVampire->setHP( finalHP );
				}
				else if ( pCreature->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
					Assert( pOusters != NULL );

					currentHP = pOusters->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)(pOusters->getHP(ATTR_MAX)*0.4) );

					pOusters->setHP( finalHP );
				}
				else continue;

				gcHP.setCurrentHP( finalHP );
				m_pZone->broadcastPacket( X, Y, &gcHP );

				if ( pCreature->isFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE) ) continue;

				// 이팩트 클래스를 만들어 붙인다.
				EffectIceFieldToCreature* pEffect = new EffectIceFieldToCreature(pCreature);
				pEffect->setDeadline(50);
				pCreature->addEffect(pEffect);
				pCreature->setFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID(pCreature->getObjectID());
				gcAddEffect.setEffectID(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);
				gcAddEffect.setDuration(50);

				m_pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );
			}
		}
	}

	__END_CATCH
}

void EffectSideTrap::affect() throw(Error)
{
	__BEGIN_TRY

	EffectWithWarning::affect();

	ZoneCoord_t X = m_X;
	ZoneCoord_t Y = m_Y;

	for ( int i=0; i<6; ++i )
	{
		slist<Creature*> targetList;
		targetList.clear();

		if ( isValidZoneCoord( m_pZone, X, Y ) )
		{
			Tile& rTile = m_pZone->getTile( X, Y );
			const slist<Object*>& rList = rTile.getObjectList();

			slist<Object*>::const_iterator itr = rList.begin();
			slist<Object*>::const_iterator endItr = rList.end();

			for ( ; itr != endItr ; ++itr )
			{
				Object* pObject = *itr;
				if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

				Creature* pCreature = dynamic_cast<Creature*>(pObject);
				if ( pCreature == NULL || pCreature->isFlag( Effect::EFFECT_CLASS_NO_DAMAGE ) ) continue;

				HP_t currentHP, finalHP = 0;
				GCStatusCurrentHP gcHP;
				gcHP.setObjectID( pCreature->getObjectID() );

				if ( pCreature->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
					Assert( pSlayer != NULL );

					currentHP = pSlayer->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)(pSlayer->getHP(ATTR_MAX)*0.5) );

					pSlayer->setHP( finalHP );
				}
				else if ( pCreature->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
					Assert( pVampire != NULL );

					currentHP = pVampire->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)(pVampire->getHP(ATTR_MAX)*0.5) );

					pVampire->setHP( finalHP );
				}
				else if ( pCreature->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
					Assert( pOusters != NULL );

					currentHP = pOusters->getHP();
					finalHP = currentHP - min( currentHP, (HP_t)(pOusters->getHP(ATTR_MAX)*0.5) );

					pOusters->setHP( finalHP );
				}
				else continue;

				gcHP.setCurrentHP( finalHP );
				m_pZone->broadcastPacket( X, Y, &gcHP );

//				if ( finalHP != 0 )
//					knockbackCreature( m_pZone, pCreature, X - dirMoveMask[(m_Dir+2)%8].x, Y - dirMoveMask[(m_Dir+2)%8].y );
				targetList.push_front( pCreature );

				if ( pCreature->isFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE) ) continue;

				// 이팩트 클래스를 만들어 붙인다.
				EffectIceFieldToCreature* pEffect = new EffectIceFieldToCreature(pCreature);
				pEffect->setDeadline(50);
				pCreature->addEffect(pEffect);
				pCreature->setFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID(pCreature->getObjectID());
				gcAddEffect.setEffectID(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE);
				gcAddEffect.setDuration(50);

				m_pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );
			}
		}

		slist<Creature*>::iterator itr = targetList.begin();
		slist<Creature*>::iterator endItr = targetList.end();

		for ( ; itr != endItr; ++itr )
		{
			Creature* pCreature = *itr;
			knockbackCreature( m_pZone, pCreature, X - dirMoveMask[(m_Dir+2)%8].x, Y - dirMoveMask[(m_Dir+2)%8].y );
		}

		X += dirMoveMask[m_Dir].x;
		Y += dirMoveMask[m_Dir].y;
	}

	setNextTime(5);

	__END_CATCH
}
