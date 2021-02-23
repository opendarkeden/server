//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBought.cpp 
// Written By  : 김성민
// Description : 
// 상점 NPC가 플레이어로부터 물건을 사들였을 때, 같은 NPC와
// 이야기하고 있는 플레이어에게 물건을 사들였다는 사실을
// 알려주기 위해 이 패킷을 보낸다.
// 클라이언트는 이 패킷을 받으면 해당하는 아이템을 해당하는 
// NPC의 상품 목록에 추가해야 한다. 상점 버전도 업데이트~
//////////////////////////////////////////////////////////////////////////////

#include "GCShopBought.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCShopBought::GCShopBought() 
	throw ()
{
	__BEGIN_TRY 
	
	m_ObjectID     = 0;
	m_Version      = 0;
	m_ShopType     = 0;
	m_ShopIndex    = 0;
	m_ItemObjectID = 0;
	m_ItemClass    = 0;
	m_Durability   = 0;
	m_Silver       = 0;
	m_Grade			= 0;
	m_EnchantLevel = 0;
	
	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCShopBought::~GCShopBought() 
	throw ()
{
	__BEGIN_TRY 
	
	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCShopBought::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_Version );
	iStream.read( m_ShopType );
	iStream.read( m_ShopIndex );
	iStream.read( m_ItemObjectID );
	iStream.read( m_ItemClass );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );
	for (int i=0; i<optionSize; i++)
	{
		OptionType_t optionType;
		iStream.read( optionType );
		addOptionType( optionType );
	}

	iStream.read( m_Durability );
	iStream.read( m_Silver );
	iStream.read( m_Grade );
	iStream.read( m_EnchantLevel );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCShopBought::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_Version );
	oStream.write( m_ShopType );
	oStream.write( m_ShopIndex );
	oStream.write( m_ItemObjectID );
	oStream.write( m_ItemClass );
	oStream.write( m_ItemType );
	
	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );
	list<OptionType_t>::const_iterator itr = m_OptionType.begin();
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
		oStream.write( optionType );
	}

	oStream.write( m_Durability );
	oStream.write( m_Silver );
	oStream.write( m_Grade );
	oStream.write( m_EnchantLevel );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCShopBought::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopBoughtHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCShopBought::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopBought("     
		<< "ObjectID:"       << (int)m_ObjectID << ","
		<< "ShopVersion: "   << (int)m_Version << ","
		<< "ShopRackType: "  << (int)m_ShopType << ","
		<< "ShopRackIndex: " << (int)m_ShopIndex << ","
		<< "ItemObjectID: "  << (int)m_ItemObjectID << ","
		<< "ItemClass: "     << (int)m_ItemClass << ","
		<< "ITemType: "      << (int)m_ItemType << ","
		<< "OptionTypeSize: "    << (int)m_OptionType.size() << ","
		<< "Durability: "    << (int)m_Durability << ","
		<< "Silver: "        << (int)m_Silver << ","
		<< "Grade: "        << (int)m_Grade << ","
		<< "EnchantLEvel: "  << (int)m_EnchantLevel; 
	msg << ")";
	return msg.toString();
		
	__END_CATCH
}


