//--------------------------------------------------------------------------------
// 
// Filename    : GCShopMarketCondition.cpp 
// Written By  : 김성민
// Description : 플레이어에게 서버 측의 상점 버전을 알려줄 때 쓰이는 패킷이다.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCShopMarketCondition.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopMarketCondition::GCShopMarketCondition() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopMarketCondition::~GCShopMarketCondition() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------
void GCShopMarketCondition::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	// read object id
	iStream.read( m_ObjectID );

	iStream.read( m_MarketCondBuy );

	iStream.read( m_MarketCondSell );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCShopMarketCondition::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// write object id
	oStream.write( m_ObjectID );

	oStream.write( m_MarketCondBuy );

	oStream.write( m_MarketCondSell );
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopMarketCondition::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopMarketConditionHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCShopMarketCondition::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShopMarketCondition(" 
	    << "ObjectID: "       << (int)m_ObjectID << ", "
	    << "MarketCondBuy: "  << (int)m_MarketCondBuy << ", "
	    << "MarketCondsell: " << (int)m_MarketCondSell;
	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}


