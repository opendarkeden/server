//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellFail.cpp 
// Written By  : 김성민
// Description : 플레이어가 NPC에게 물건을 팔려고 했는데, 어떤 이유로
//               실패했을 경우에는 이 패킷을 플레이어에게 보내준다.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCShopSellFail.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopSellFail::GCShopSellFail() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopSellFail::~GCShopSellFail() 
	throw ()
{
	__BEGIN_TRY 
	
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------
void GCShopSellFail::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	//-----------------------------------------------------------------
	// read object id
	//-----------------------------------------------------------------
	iStream.read( m_ObjectID );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCShopSellFail::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	//-----------------------------------------------------------------
	// write object id
	//-----------------------------------------------------------------
	oStream.write( m_ObjectID );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopSellFail::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopSellFailHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCShopSellFail::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopSellFail(" 
		<< "ObjectID:" << m_ObjectID
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


