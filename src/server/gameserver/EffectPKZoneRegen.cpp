//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPKZoneRegen.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectPKZoneRegen.h"
#include "Zone.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "StringStream.h"
#include "ZoneUtil.h"
#include "skill/EffectBloodDrain.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPKZoneRegen::EffectPKZoneRegen(Zone* pZone, ZoneCoord_t left, ZoneCoord_t top, ZoneCoord_t right, ZoneCoord_t bottom) throw(Error)
	: m_Rect( left, top, right, bottom )
{
	__BEGIN_TRY

	m_pZone = pZone;
	Assert( left < right );
	Assert( top < bottom );

	m_bSlayer = m_bVampire = m_bOusters = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPKZoneRegen::affect()
	throw(Error)
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	Assert( isValidZoneCoord( m_pZone, m_Rect.left, m_Rect.top ) );
	Assert( isValidZoneCoord( m_pZone, m_Rect.right, m_Rect.bottom ) );

	for ( ZoneCoord_t X = m_Rect.left ; X <= m_Rect.right ; X++ )
	{
		for ( ZoneCoord_t Y = m_Rect.top ; Y <= m_Rect.bottom ; Y++ )
		{
			Tile& tile = m_pZone->getTile( X, Y );

			const slist<Object*>& oList = tile.getObjectList();
			for ( slist<Object*>::const_iterator itr = oList.begin() ; itr != oList.end() ; itr++ )
			{
				Object* pTargetObject = (*itr);

				if ( pTargetObject != NULL && pTargetObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
				{
					Creature* pCreature = dynamic_cast<Creature*>( pTargetObject );
					Assert( pCreature != NULL );

					affect( pCreature );
				}
			}
		}
	}

	setNextTime( m_Turn );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPKZoneRegen::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( !pCreature->isPC() ) return;
	if ( pCreature->isDead() ) return;
	if ( pCreature->isFlag( Effect::EFFECT_CLASS_COMA ) ) return;

	if ( m_bSlayer && pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>( pCreature );
		Assert( pSlayer != NULL );

		if ( pSlayer->getHP( ATTR_CURRENT ) < pSlayer->getHP( ATTR_MAX )
			|| pSlayer->getMP( ATTR_CURRENT ) < pSlayer->getMP( ATTR_MAX )
		)
		{
			pSlayer->setMP( min( (int)pSlayer->getMP( ATTR_MAX ), (int)pSlayer->getMP( ATTR_CURRENT ) + m_HP / 2 ) );
			pSlayer->setHP( min( (int)pSlayer->getHP( ATTR_MAX ), (int)pSlayer->getHP( ATTR_CURRENT ) + m_HP / 2 ) );

			GCModifyInformation gcMI;

			gcMI.addShortData( MODIFY_CURRENT_MP, pSlayer->getMP( ATTR_CURRENT ) );
			gcMI.addShortData( MODIFY_CURRENT_HP, pSlayer->getHP( ATTR_CURRENT ) );
			pSlayer->getPlayer()->sendPacket(&gcMI);

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pSlayer->getObjectID() );
			gcHP.setCurrentHP( pSlayer->getHP( ATTR_CURRENT ) );

			m_pZone->broadcastPacket( pSlayer->getX(), pSlayer->getY(), &gcHP, pSlayer );
		}
		// HP는 다 치료된 상태고 흡혈에 걸려있으면
		if ( pSlayer->getHP( ATTR_CURRENT ) >= pSlayer->getHP( ATTR_MAX ) && pSlayer->isFlag( Effect::EFFECT_CLASS_BLOOD_DRAIN ) )
		{
			EffectBloodDrain* pEffect = dynamic_cast<EffectBloodDrain*>(pSlayer->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN));
			if ( pEffect != NULL )
			{
				pEffect->destroy( pSlayer->getName() );
				pSlayer->deleteEffect( Effect::EFFECT_CLASS_BLOOD_DRAIN );

//				GCModifyInformation gcMI;

				SLAYER_RECORD prev;
				pSlayer->getSlayerRecord( prev );
				pSlayer->initAllStat();
				pSlayer->sendRealWearingInfo();
				pSlayer->sendModifyInfo( prev );

				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.addEffectList( (EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN );
				gcRemoveEffect.setObjectID( pSlayer->getObjectID() );

				pSlayer->getZone()->broadcastPacket( pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect );
			}
		}
	}
	else if ( m_bVampire && pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>( pCreature );
		Assert( pVampire != NULL );

		if ( pVampire->getHP( ATTR_MAX ) > pVampire->getHP( ATTR_CURRENT ) )
		{
			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pVampire->getObjectID() );

			pVampire->setHP( min( (int)pVampire->getHP( ATTR_MAX ), (int)pVampire->getHP( ATTR_CURRENT ) + m_HP ) );
			
			// 넘한테 뿌릴꺼
			gcHP.setCurrentHP( pVampire->getHP( ATTR_CURRENT ) );

			// 자기한테 보여줄꺼
			GCModifyInformation gcMI;
			gcMI.addShortData( MODIFY_CURRENT_HP, pVampire->getHP( ATTR_CURRENT ) );

			// HP가 실버 데미지를 넘어서게 되면 실버데미지를 날려 준다.
			if ( pVampire->getHP( ATTR_CURRENT ) > pVampire->getHP( ATTR_MAX ) - pVampire->getSilverDamage() )
			{
				pVampire->setSilverDamage( pVampire->getHP( ATTR_MAX ) - pVampire->getHP( ATTR_CURRENT ) );

				gcMI.addShortData( MODIFY_SILVER_DAMAGE, pVampire->getSilverDamage() );
			}

			pVampire->getPlayer()->sendPacket( &gcMI );

			m_pZone->broadcastPacket( pVampire->getX(), pVampire->getY(), &gcHP, pVampire );
		}
	}
	else if ( m_bOusters && pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>( pCreature );
		Assert( pOusters != NULL );

		if ( pOusters->getHP( ATTR_CURRENT ) < pOusters->getHP( ATTR_MAX ) 
			|| pOusters->getMP( ATTR_CURRENT ) < pOusters->getMP( ATTR_MAX )
			|| pOusters->getSilverDamage() != 0
			)
		{
			if ( pOusters->getMP( ATTR_CURRENT ) < pOusters->getMP( ATTR_MAX ) )
				pOusters->setMP( min( (int)pOusters->getMP( ATTR_MAX ), (int)pOusters->getMP( ATTR_CURRENT ) + m_HP / 2 ) );

			pOusters->setHP( min( (int)pOusters->getHP( ATTR_MAX ), (int)pOusters->getHP( ATTR_CURRENT ) + m_HP / 2 ) );

			GCModifyInformation gcMI;

			// HP가 실버 데미지를 넘어서게 되면 실버데미지를 날려 준다.
			if ( pOusters->getHP( ATTR_CURRENT ) > pOusters->getHP( ATTR_MAX ) - pOusters->getSilverDamage() )
			{
				pOusters->setSilverDamage( pOusters->getHP( ATTR_MAX ) - pOusters->getHP( ATTR_CURRENT ) );

				gcMI.addShortData( MODIFY_SILVER_DAMAGE, pOusters->getSilverDamage() );
			}

			gcMI.addShortData( MODIFY_CURRENT_MP, pOusters->getMP( ATTR_CURRENT ) );
			gcMI.addShortData( MODIFY_CURRENT_HP, pOusters->getHP( ATTR_CURRENT ) );
			pOusters->getPlayer()->sendPacket(&gcMI);

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pOusters->getObjectID() );
			gcHP.setCurrentHP( pOusters->getHP( ATTR_CURRENT ) );

			m_pZone->broadcastPacket( pOusters->getX(), pOusters->getY(), &gcHP, pOusters );
		}
	}
																													
	__END_CATCH
}

void EffectPKZoneRegen::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	StringStream msg;

	msg << "EffectPKZoneRegen[" << m_pZone->getZoneID() << "|("
		<< m_Rect.left << ","
		<< m_Rect.top << ","
		<< m_Rect.right << ","
		<< m_Rect.bottom << ")]"
		<< " 이펙트가 사라졌다..";

	filelog( "PKZone.txt", "EffectPKZoneRegen[%d|(%d,%d,%d,%d)] 이펙트가 사라졌다.",
			m_pZone->getZoneID(), m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPKZoneRegen::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPKZoneRegen::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectPKZoneRegen("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
