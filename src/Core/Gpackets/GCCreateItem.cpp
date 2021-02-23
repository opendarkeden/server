//////////////////////////////////////////////////////////////////////////////
// Filename    : GCCreateItem.cpp
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCCreateItem.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCCreateItem::GCCreateItem()
	throw()
{
	__BEGIN_TRY

	m_ObjectID     = 0;
	m_ItemClass    = 0;
	m_ItemType     = 0;
	m_Durability   = 0;
	m_Silver       = 0;
	m_Grade       = 0;
	m_EnchantLevel = 0;
	m_ItemNum      = 0;
	m_InvenX       = 0;
	m_InvenY       = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_ObjectID );
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
	iStream.read( m_ItemNum );
	iStream.read( m_InvenX );
	iStream.read( m_InvenY );
		
	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
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
	oStream.write( m_ItemNum );
	oStream.write( m_InvenX );
	oStream.write( m_InvenY );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCCreateItem::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCCreateItemHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCCreateItem::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCCreateItem("
		<< "ObjectID:"      << (int)m_ObjectID
		<< ",ItemClass:"    << (int)m_ItemClass
		<< ",ItemType:"     << (int)m_ItemType
		<< ",OptionTypeSize:"   << (int)m_OptionType.size()
		<< ",Durability:"   << (int)m_Durability
		<< ",Silver:"       << (int)m_Silver
		<< ",Grade:"       << (int)m_Grade
		<< ",EnchantLEvel:" << (int)m_EnchantLevel
		<< ",ItemNum:"      << (int)m_ItemNum
		<< ",InvenX:"       << (int)m_InvenX
		<< ",InvenY:"       << (int)m_InvenY
		<< ")";
	return msg.toString();

	__END_CATCH
}


