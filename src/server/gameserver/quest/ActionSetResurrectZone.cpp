////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSetResurrectZone.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "ActionSetResurrectZone.h"
#include "Creature.h"
#include "Trigger.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "StringPool.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSetResurrectZone::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		m_ZoneID = propertyBuffer.getPropertyInt("ZoneID"); 
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionSetResurrectZone::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	// 일단 클라이언트를 위해서 OK 패킷을 함 날린다.
	GCNPCResponse okpkt;
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&okpkt);

	if (pCreature2->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
		pSlayer->setResurrectZoneIDEx(m_ZoneID);
	}
	else if (pCreature2->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
		pVampire->setResurrectZoneIDEx(m_ZoneID);
	}
	else if (pCreature2->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
		pOusters->setResurrectZoneIDEx(m_ZoneID);
	}

	GCSystemMessage msg;
	msg.setMessage( g_pStringPool->getString( STRID_SET_RESURRECTION_POSITION ) );
	pPlayer->sendPacket(&msg);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSetResurrectZone::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSetResurrectZone(" << ")";
	return msg.toString();

	__END_CATCH
}
