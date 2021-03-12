//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeartCatalyst.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHeartCatalyst.h"
#include "Slayer.h"
#include "Player.h"
#include "Item.h"
#include "ItemUtil.h"

#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectHeartCatalyst::EffectHeartCatalyst(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);
	// 한번 부를때마다 반전되는거. 의미없다.
	m_GiveExp = true;

	__END_CATCH
}

void EffectHeartCatalyst::affect() 
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH
}

void EffectHeartCatalyst::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert( pCreature != NULL );

	if ( !pCreature->isSlayer() )
	{
		setDeadline(0);
		return;
	}

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	Assert( pSlayer != NULL );

	Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pWeapon == NULL || !isArmsWeapon(pWeapon))
	{
		setDeadline(0);
		//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
		return;
	}

	if ( pSlayer->getHP(ATTR_CURRENT) >= pSlayer->getHP(ATTR_MAX) )
	{
		setNextTime( m_Tick );
		return;
	}

	HP_t CurrentHP = pSlayer->getHP(ATTR_CURRENT);
	HP_t NewHP = min( (int)pSlayer->getHP(ATTR_MAX), CurrentHP + m_HealPoint );

	pSlayer->setHP( NewHP );
	GCStatusCurrentHP gcHP;
	gcHP.setObjectID( pSlayer->getObjectID() );
	gcHP.setCurrentHP( pSlayer->getHP() );

	pSlayer->getZone()->broadcastPacket( pSlayer->getX(), pSlayer->getY(), &gcHP );

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectHeartCatalyst::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectHeartCatalyst " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectHeartCatalyst " << "unaffect END" << endl;

    __END_CATCH
}

void EffectHeartCatalyst::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectHeartCatalyst " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	pCreature->removeFlag(Effect::EFFECT_CLASS_HEART_CATALYST);

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	SLAYER_RECORD prev;
	pSlayer->getSlayerRecord(prev);
	pSlayer->initAllStat();
	pSlayer->sendRealWearingInfo();
	pSlayer->sendModifyInfo(prev);

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pSlayer->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HEART_CATALYST);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);

	//cout << "EffectHeartCatalyst " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectHeartCatalyst::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHeartCatalyst("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
