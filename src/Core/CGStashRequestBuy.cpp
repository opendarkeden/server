//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashRequestBuy.cpp
// Written By  : 김성민
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGStashRequestBuy.h"

void CGStashRequestBuy::read(SocketInputStream& iStream)

{
    __BEGIN_TRY
    __END_CATCH
}

void CGStashRequestBuy::write(SocketOutputStream& oStream) const

{
    __BEGIN_TRY
    __END_CATCH
}

void CGStashRequestBuy::execute(Player* pPlayer)

{
    __BEGIN_TRY

    CGStashRequestBuyHandler::execute(this, pPlayer);

    __END_CATCH
}

string CGStashRequestBuy::toString() const {
    StringStream msg;
    msg << "CGStashRequestBuy("
        << ")";
    return msg.toString();
}
