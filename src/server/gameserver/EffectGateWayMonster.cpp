//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGateWayMonster.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectGateWayMonster.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectGateWayMonster::EffectGateWayMonster(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGateWayMonster::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	HP_t HPRecovery = 1;

	if(pCreature->isSlayer() || pCreature->isVampire() || pCreature->isOusters()) {
		cout << "(EffectGateWayMonster) Vampire, Slayer or Ousters." << endl;
		return;
	}

	if(pCreature->isMonster()) {
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

        if(pMonster->getMonsterType()>=371 && pMonster->getMonsterType()<= 375) {
			HP_t CurrentHP = pMonster->getHP(ATTR_CURRENT);

            if(CurrentHP > 0) {
				HP_t PlusHP = min(5000, CurrentHP+1);

				pMonster->setHP(PlusHP, ATTR_CURRENT);

				GCStatusCurrentHP pkt;
				pkt.setObjectID(pMonster->getObjectID());
                pkt.setCurrentHP(CurrentHP);
				pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &pkt);
		} else {
			cout << "(EffectGateWayMonster) Not within 371-375 mtype range." << endl;
			return;
		}
	} else {
		cout << "(EffectGateWayMonster) Can not use monster effect." << endl;
		return 0;
	}

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectGateWayMonster::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGateWayMonster::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_GATEWAY_MONSTER);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GATEWAY_MONSTER);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectGateWayMonster::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectGateWayMonster("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
