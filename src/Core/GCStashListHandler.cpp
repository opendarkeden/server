////////////////////////////////////////////////////////////////////////////////
// Filename    : GCStashListHandler.cpp
// Written By  : 김성민
// Description :
////////////////////////////////////////////////////////////////////////////////

// include files
#include "GCStashList.h"

void GCStashListHandler::execute(GCStashList* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX __BEGIN_DEBUG

#ifdef __GAME_CLIENT__
    // cout << pPacket->toString() << endl;
#endif

        __END_DEBUG __END_DEBUG_EX __END_CATCH
}
