//--------------------------------------------------------------------------------
// 
// Filename    : GCShopVersion.cpp 
// Written By  : 김성민
// Description : 플레이어에게 서버 측의 상점 버전을 알려줄 때 쓰이는 패킷이다.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCShopVersion.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopVersion::GCShopVersion() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopVersion::~GCShopVersion() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------
void GCShopVersion::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	// read object id
	iStream.read( m_ObjectID );

	// read versions
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
		iStream.read(m_Version[i]);

	iStream.read(m_MarketCondSell);

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCShopVersion::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// write object id
	oStream.write( m_ObjectID );

	// write versions
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
		oStream.write(m_Version[i]);

	oStream.write( m_MarketCondSell );
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopVersion::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopVersionHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCShopVersion::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShopVersion(" << "ObjectID:" << m_ObjectID;
	
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
		msg << " Version[" << (int)i << "] : " << (int)m_Version[i];

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}


