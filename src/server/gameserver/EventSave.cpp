//////////////////////////////////////////////////////////////////////////////
// Filename    : EventSave.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventSave.h"
#include "GamePlayer.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "Gpackets/GCModifyInformation.h"

EventSave::EventSave (GamePlayer* pGamePlayer) 
	throw (Error)
: Event(pGamePlayer)
{
}

EventSave::~EventSave () 
	throw ()
{
}
			
void EventSave::activate () 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		Assert(m_pGamePlayer != NULL);	// by sigi
		Creature* pCreature = m_pGamePlayer->getCreature();
		Assert(pCreature != NULL);	// by sigi

		Assert(pCreature->isPC());

		GCModifyInformation gcModifyInformation;
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			pSlayer->save();
			gcModifyInformation.addLongData(MODIFY_FAME , pSlayer->getFame());

			m_pGamePlayer->sendPacket(&gcModifyInformation);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			pVampire->save();

			gcModifyInformation.addLongData(MODIFY_FAME , pVampire->getFame());

			m_pGamePlayer->sendPacket(&gcModifyInformation);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			pOusters->save();
		}

		Timeval delay;
		delay.tv_sec = 6000;
		delay.tv_usec = 0;
	
		m_Deadline = m_Deadline + delay;
	}
	else
	{
		Timeval delay;
		delay.tv_sec = 100;
		delay.tv_usec = 0;
	
		m_Deadline = m_Deadline + delay;
	}
	
	__END_CATCH
}
