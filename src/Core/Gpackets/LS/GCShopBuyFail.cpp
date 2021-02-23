//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBuyFail.cpp 
// Written By  : excel96
// Description :
// 플레이어가 상점에서 아이템을 구입하려고 했는데,
// 정상적인 구매가 실패했을 경우에 플레이어에게 보내는 패킷.
//////////////////////////////////////////////////////////////////////////////

#include "GCShopBuyFail.h"
#include "Assert.h"

GCShopBuyFail::GCShopBuyFail()
{
	m_ObjectID = 0;
	m_Code     = GC_SHOP_BUY_FAIL_MAX;
	m_Amount   = 0;
}

GCShopBuyFail::~GCShopBuyFail()
{
}

void GCShopBuyFail::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_Code);
	iStream.read(m_Amount);

	__END_CATCH
}
		    
void GCShopBuyFail::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);
	oStream.write(m_Code);
	oStream.write(m_Amount);

	__END_CATCH
}

void GCShopBuyFail::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCShopBuyFailHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCShopBuyFail::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopBuyFail(" 
		<< "ObjectID:" << m_ObjectID 
		<< ",CODE:" << GCShopBuyFailCode2String[m_Code]
		<< ",Amount:" << m_Amount
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


