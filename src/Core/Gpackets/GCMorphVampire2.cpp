//----------------------------------------------------------------------
// 
// Filename    : GCMorphVampire2.cpp
// Written By  : crazydog
// 
//----------------------------------------------------------------------

// include files
#include "GCMorphVampire2.h"


//----------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//----------------------------------------------------------------------
void GCMorphVampire2::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	m_VampireInfo3.read( iStream );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCMorphVampire2::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

		
	m_VampireInfo3.write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCMorphVampire2::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMorphVampire2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCMorphVampire2::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCMorphVampire2("
		<< m_VampireInfo3.toString()
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
