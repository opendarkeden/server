//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopMarketConditionHandler.cpp
// Written By  : 김성민
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShopMarketCondition.h"

void GCShopMarketConditionHandler::execute(GCShopMarketCondition* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__
    // cout << pPacket->toString() << endl;
#endif

        __END_DEBUG_EX __END_CATCH
}
