////////////////////////////////////////////////////////////////////////////////
// Filename    : CGBuyStoreItem.cpp 
// Written By  : 김성민
// Description : 
// 플레이어가 상점 NPC의 진열창을 보고, 물건을 구입하고자 할 때
// 보내는 패킷이다. 서버는 플레이어에게 충분한 돈과 인벤토리에
// 자리가 있는지 검증한 후 플레이어에게 아이템을 넘긴다.
////////////////////////////////////////////////////////////////////////////////

#include "CGBuyStoreItem.h"

void CGBuyStoreItem::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_OwnerObjectID);
	iStream.read(m_ItemObjectID);
	iStream.read(m_Index);

	__END_CATCH
}

void CGBuyStoreItem::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_OwnerObjectID);
	oStream.write(m_ItemObjectID);
	oStream.write(m_Index);

	__END_CATCH
}

void CGBuyStoreItem::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGBuyStoreItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGBuyStoreItem::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGBuyStoreItem(" 
			<< ")";
	return msg.toString();

	__END_CATCH
}
