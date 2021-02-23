//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStatusCurrentHP.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCStatusCurrentHP.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCStatusCurrentHP::GCStatusCurrentHP()
	throw( Error )
{
	__BEGIN_TRY
	m_CurrentHP = 0;
	m_ObjectID = 0;
	__END_CATCH
}

//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCStatusCurrentHP::~GCStatusCurrentHP()
	throw( Error )
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCStatusCurrentHP::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_CurrentHP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCStatusCurrentHP::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_CurrentHP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCStatusCurrentHP::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCStatusCurrentHPHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCStatusCurrentHP::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCStatusCurrentHP("
		<< "ObjectID:" << m_ObjectID
		<< ",CurrentHP:" << (int)m_CurrentHP
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
