//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMPRecoveryEnd.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMPRecoveryEnd.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCMPRecoveryEnd::GCMPRecoveryEnd()
	throw( Error )
{
	__BEGIN_TRY
	m_CurrentMP = 0;
	__END_CATCH
}

//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCMPRecoveryEnd::~GCMPRecoveryEnd()
	throw( Error )
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryEnd::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_CurrentMP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryEnd::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_CurrentMP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCMPRecoveryEnd::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMPRecoveryEndHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCMPRecoveryEnd::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCMPRecoveryEnd("
		<< "CurrentMP:" << (int)m_CurrentMP
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
