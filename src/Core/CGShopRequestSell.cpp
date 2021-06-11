////////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestSell.cpp 
// Written By  : 김성민
// Description : 
// 플레이어에게 자신이 가지고 있는 아이템을 상점 NPC에게
// 팔기를 요청할 때 쓰이는 패킷이다.
////////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestSell.h"

void CGShopRequestSell::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_ItemObjectID);
	iStream.read(m_OpCode);

	__END_CATCH
}

void CGShopRequestSell::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_ItemObjectID);
	oStream.write(m_OpCode);

	__END_CATCH
}

void CGShopRequestSell::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGShopRequestSellHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGShopRequestSell::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGShopRequestSell("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
