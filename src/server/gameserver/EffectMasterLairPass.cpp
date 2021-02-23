//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMasterLairPass.cpp
// Written by  : 쉭
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectMasterLairPass.h"
#include "Creature.h"
#include "Player.h"
#include "ZoneInfoManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectMasterLairPass::EffectMasterLairPass(Creature* pCreature, ZoneID_t zoneID)
	throw(Error)
{
	__BEGIN_TRY

	m_ZoneID = zoneID;

	setTarget(pCreature);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMasterLairPass::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMasterLairPass::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

																														    	
	__END_CATCH
}

void EffectMasterLairPass::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMasterLairPass::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectMasterLairPass" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_MASTER_LAIR_PASS);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	/*
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_MASTER_LAIR_PASS);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	*/

	//cout << "EffectMasterLairPass" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMasterLairPass::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMasterLairPass("
		<< "ObjectID:" << getObjectID()
		<< ",ZoneID:" << m_ZoneID
		<< ")";
	return msg.toString();

	__END_CATCH
}
