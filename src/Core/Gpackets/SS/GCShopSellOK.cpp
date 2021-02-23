//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellOK.cpp 
// Written By  : 김성민
// Description : 플레이어가 상점 NPC에게 물건 구입을 요청했을 때, 제대로
//               인증이 되면 이 패킷이 플레이어에게 날아간다.
//               클라이언트는 이 패킷을 받아서 상점 버전을 업데이트하고,
//               오브젝트 ID로 아이템 정보를 체크해 놓고, 가격을 이용해
//               플레이어의 돈을 업데이트한다.
// 
//--------------------------------------------------------------------------------

// include files
#include "GCShopSellOK.h"
#include "Assert.h"


//--------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------

GCShopSellOK::GCShopSellOK() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------
GCShopSellOK::~GCShopSellOK() 
	throw ()
{
	__BEGIN_TRY 
	
	
	__END_CATCH;
}

//--------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------
void GCShopSellOK::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_Version);
	iStream.read(m_ItemObjectID);
	iStream.read(m_Price);

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCShopSellOK::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_Version);
	oStream.write(m_ItemObjectID);
	oStream.write(m_Price);
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCShopSellOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopSellOKHandler::execute( this , pPlayer );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCShopSellOK::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopSellOK("
		<< "ObjectID:"      << m_ObjectID
	    << ",Version:"      << (int)m_Version
		<< ",ItemObejctID:" << m_ItemObjectID
		<< ",Price:"        << m_Price
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


