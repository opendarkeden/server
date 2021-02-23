//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeShape.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCChangeShape.h"




//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCChangeShape::GCChangeShape () 
     throw ()
{
	__BEGIN_TRY

	m_Flag = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCChangeShape::~GCChangeShape () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCChangeShape::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_ItemClass );
	iStream.read( m_ItemType );
	iStream.read( m_OptionType );
	iStream.read( m_AttackSpeed );
	iStream.read( m_Flag );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCChangeShape::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_ItemClass );
	oStream.write( m_ItemType );
	oStream.write( m_OptionType );
	oStream.write( m_AttackSpeed );
	oStream.write( m_Flag );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCChangeShape::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	GCChangeShapeHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// toString()
//////////////////////////////////////////////////////////////////////
string GCChangeShape::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCChangeShape("
		<< "ObjectID:" << (int)m_ObjectID
		<< ",ItemClass:" << (int)m_ItemClass
		<< ",ItemType:" << (int)m_ItemType
		<< ",OptionType:" << (int)m_OptionType
		<< ",AttackSpeed :" << (int)m_AttackSpeed
		<< ",Flag :" << (int)m_Flag
		<< ")";
	return msg.toString();

	__END_CATCH
}
