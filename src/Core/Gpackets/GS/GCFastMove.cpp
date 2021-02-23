//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFastMove.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCFastMove.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCFastMove::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_FromX );
	iStream.read( m_FromY );
	iStream.read( m_ToX );
	iStream.read( m_ToY );
	iStream.read( m_SkillType );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCFastMove::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_FromX );
	oStream.write( m_FromY );
	oStream.write( m_ToX );
	oStream.write( m_ToY );
	oStream.write( m_SkillType );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCFastMove::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCFastMoveHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCFastMove::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCFastMove(ObjectID:" << m_ObjectID 
		<< ",From(X,Y):" << (int)m_FromX << "," <<(int)m_FromY 
		<< ",To(X,Y):" << (int)m_ToX << "," << (int)m_ToY
		<< ",SkillType:" << m_SkillType
		<< ")";
	return msg.toString();

	__END_CATCH
}


