//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSold.cpp 
// Written By  : 김성민
// Description : 한 플레이어가 상점 NPC에게 물건을 구입했는데,
//               다른 플레이어도 같은 상점 NPC와 대화 중이었다면,
//               그 플레이어와 아이템 목록을 동기화시켜주어야 한다.
//               이 패킷은 그를 위한 패킷이다.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCShopSold.h"
#include "Assert.h"

//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopSold::GCShopSold() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopSold::~GCShopSold() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------
void GCShopSold::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_Version );
	iStream.read( m_RackType );
	iStream.read( m_RackIndex );	

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCShopSold::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_Version );
	oStream.write( m_RackType );
	oStream.write( m_RackIndex );	
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopSold::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopSoldHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCShopSold::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopSold("     
		<< "ObjectID:"        << (int)m_ObjectID
		<< ",ShopVersion: "   << (int)m_Version
		<< ",ShopRackType: "  << (int)m_RackType
		<< ",ShopRackIndex: " << (int)m_RackIndex
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


