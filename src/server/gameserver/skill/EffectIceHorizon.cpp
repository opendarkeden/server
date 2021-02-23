//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceHorizon.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectIceHorizon.h"
#include "Slayer.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectIceHorizon::EffectIceHorizon(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_CasterName ="";
	m_CasterID = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHorizon::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectIceHorizon" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 이펙트를 사용한 크리쳐를 가져온다.
	// !! 이미 존을 나갔을 수도 있으므로 NULL이 될 수 있다.
	// by bezz. 2003.1.4
	Creature* pCastCreature = m_pZone->getCreature( m_CasterID );

	// 현재 이펙트가 붙어있는 타일을 받아온다.
    Tile& tile = m_pZone->getTile(m_X, m_Y);

	// 타일 안에 존재하는 오브젝트들을 검색한다.
    const slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::const_iterator itr = oList.begin();
    for (; itr != oList.end(); itr++) 
	{
		Assert(*itr != NULL);

		Object* pObject = *itr;
		Assert(pObject != NULL);

    	if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature != NULL);

			if ( pCreature->isFlag(Effect::EFFECT_CLASS_COMA) )
			{
				continue;
			}
			
			if ( !pCreature->isOusters() )
			{
				continue;
			}

			if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
			{
				Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
				Assert( pTargetOusters != NULL );

				GCModifyInformation gcTargetMI;
				GCStatusCurrentHP gcTargetHP;
				
				HP_t final = min( (int)pTargetOusters->getHP(ATTR_MAX), pTargetOusters->getHP() + m_IncreaseAmount );
				if ( final > pTargetOusters->getHP(ATTR_MAX) - pTargetOusters->getSilverDamage() )
				{
					pTargetOusters->setSilverDamage( pTargetOusters->getHP(ATTR_MAX) - final );
					gcTargetMI.addShortData(MODIFY_SILVER_DAMAGE, pTargetOusters->getSilverDamage());
				}

				if ( pTargetOusters->getHP() != final )
				{
					pTargetOusters->setHP( final );
					gcTargetMI.addShortData(MODIFY_CURRENT_HP, final);
				}

				gcTargetHP.setObjectID( pTargetOusters->getObjectID() );
				gcTargetHP.setCurrentHP( final );

				pTargetOusters->getPlayer()->sendPacket( &gcTargetMI );
				m_pZone->broadcastPacket( pTargetOusters->getX(), pTargetOusters->getY(), &gcTargetHP, pTargetOusters );

				GCAddEffect gcAE;
				gcAE.setObjectID( pTargetOusters->getObjectID() );
				gcAE.setEffectID( Effect::EFFECT_CLASS_ICE_HORIZON );
				gcAE.setDuration( 0 );
				m_pZone->broadcastPacket( pTargetOusters->getX(), pTargetOusters->getY(), &gcAE );
			}
		}
	}
	
	setNextTime(m_Tick);

	//cout << "EffectIceHorizon" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHorizon::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHorizon::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectIceHorizon::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectIceHorizon" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectIceHorizon" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectIceHorizon::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectIceHorizon("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

