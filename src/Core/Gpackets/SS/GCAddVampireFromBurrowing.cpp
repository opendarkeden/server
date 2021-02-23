//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireFromBurrowing.cpp
// Written By  : Reiot
// 
//----------------------------------------------------------------------

// include files
#include "GCAddVampireFromBurrowing.h"

//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
GCAddVampireFromBurrowing::~GCAddVampireFromBurrowing()
	throw()
{
	__BEGIN_TRY
	
	SAFE_DELETE(m_pEffectInfo);

	__END_CATCH
}

//----------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//----------------------------------------------------------------------
void GCAddVampireFromBurrowing::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	m_VampireInfo.read( iStream );

	m_pEffectInfo = new EffectInfo();
	m_pEffectInfo->read( iStream );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCAddVampireFromBurrowing::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	m_VampireInfo.write( oStream );

	m_pEffectInfo->write( oStream );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCAddVampireFromBurrowing::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddVampireFromBurrowingHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCAddVampireFromBurrowing::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCAddVampireFromBurrowing("
		<< "VampireInfo:" << m_VampireInfo.toString()
		<< "EffectInfo:" << m_pEffectInfo->toString()
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
