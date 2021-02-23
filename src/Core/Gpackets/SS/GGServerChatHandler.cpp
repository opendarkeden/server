//----------------------------------------------------------------------
//
// Filename    : GGServerChatHandler.cpp
// Written By  : inthesky
// Description : 서버간 Whisper Chat을 수행한다.
//
//----------------------------------------------------------------------

// include files
#include "GGServerChat.h"

#ifdef __GAME_SERVER__

	#include "Player.h"
	#include "Creature.h"
	#include "GuildManager.h"
	#include "Guild.h"
	#include "PCFinder.h"
	#include "Gpackets/GCWhisper.h"
    #include "Gpackets/GCWhisperFailed.h"

#endif

//----------------------------------------------------------------------
// 
// GGServerChatHander::execute()
// 
//----------------------------------------------------------------------
void GGServerChatHandler::execute ( GGServerChat * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
	
#ifdef __GAME_SERVER__

	__ENTER_CRITICAL_SECTION((*g_pPCFinder))
        
	Creature* pCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getReceiver());
	if ( pCreature != NULL && pCreature->getPlayer() != NULL )
	{   		
		GCWhisper gcWhisper;

		gcWhisper.setName	(pPacket->getSender()	);
		gcWhisper.setColor	(pPacket->getColor() 	);
		gcWhisper.setMessage(pPacket->getMessage()	);
		gcWhisper.setRace	(pPacket->getRace()		);

		pCreature->getPlayer()->sendPacket(&gcWhisper);

	}
	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))



#endif
		
	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
