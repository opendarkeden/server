//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopBuyOKHandler.cpp
// Written By  : 김성민
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShopBuyOK.h"

void GCShopBuyOKHandler::execute(GCShopBuyOK* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__
    // cout << pPacket->toString() << endl;
#endif

        __END_DEBUG_EX __END_CATCH
}
