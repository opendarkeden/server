//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMonsterKillQuestInfoHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMonsterKillQuestInfo.h"

//////////////////////////////////////////////////////////////////////
//
// Handler invoked when the client sends this packet.
//
//////////////////////////////////////////////////////////////////////
void GCMonsterKillQuestInfoHandler::execute(GCMonsterKillQuestInfo* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__
    // cout << pPacket->toString() << endl;
#endif

        __END_DEBUG_EX __END_CATCH
}
