//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPeace.cpp
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectPeace.h"
#include "Peace.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "DB.h"
#include "DarkLightInfo.h"
#include "MonsterInfo.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPeace::EffectPeace(Creature* pCreature, ObjectID_t PeaceCreatureID)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_PeaceCreatureID = PeaceCreatureID;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(!pCreature->isSlayer()); // 슬레이어는 걸리지 않는다.
	Assert(!pCreature->isNPC()); // NPC도 걸리지 않는다.

	if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		pMonster->deleteEnemy( pCreature->getObjectID() );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectPeace " << "unaffect BEGIN" << endl;

	pCreature->removeFlag(Effect::EFFECT_CLASS_PEACE);

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PEACE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectPeace " << "unaffect END" << endl;
	
	__END_DEBUG
	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectPeace " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectPeace " << "unaffect END" << endl;
	
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPeace::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectPeace("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

