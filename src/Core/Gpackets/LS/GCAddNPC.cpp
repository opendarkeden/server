//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddNPC.cc 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAddNPC.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAddNPC::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ObjectID );

	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too large name length");
		
	iStream.read( m_Name , szName );
	iStream.read( m_NPCID );

	iStream.read( m_SpriteType );

	iStream.read( m_MainColor );
	iStream.read( m_SubColor );

	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAddNPC::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ObjectID );

	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too large name length");

	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_NPCID );

	oStream.write( m_SpriteType );

	oStream.write( m_MainColor );
	oStream.write( m_SubColor );

	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddNPC::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddNPCHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddNPC::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCAddNPC("
		<< "ObjectID:" << m_ObjectID 
		<< ",Name:" << m_Name 
		<< ",SpriteType:" << (int)m_SpriteType
		<< ",MainColor:" << (int)m_MainColor
		<< ",SubColor:" << (int)m_SubColor
		<< ",X:" << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",Dir: " << (int)m_Dir 
		<< ")" ;

	return msg.toString();

	__END_CATCH
}


