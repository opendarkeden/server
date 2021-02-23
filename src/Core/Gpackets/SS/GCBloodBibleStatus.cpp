//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodBibleStatus.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCBloodBibleStatus.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatus::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_ItemType );
	iStream.read( m_ZoneID );
	iStream.read( m_Storage );
	iStream.read( m_Race );
	iStream.read( m_ShrineRace );
	iStream.read( m_X );
	iStream.read( m_Y );

	BYTE szOwnerName;
	iStream.read( szOwnerName );
	if ( szOwnerName > 256 )
		throw InvalidProtocolException("too large message length");

	if (szOwnerName>0)
	{
		iStream.read( m_OwnerName , szOwnerName );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatus::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ItemType );
	oStream.write( m_ZoneID );
	oStream.write( m_Storage );
	oStream.write( m_Race );
	oStream.write( m_ShrineRace );
	oStream.write( m_X );
	oStream.write( m_Y );

	BYTE szOwnerName = m_OwnerName.size();
	oStream.write( szOwnerName );
	if ( szOwnerName > 256 )
		throw InvalidProtocolException("too large message length");

	if (szOwnerName>0)
	{
		oStream.write( m_OwnerName );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCBloodBibleStatus::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCBloodBibleStatusHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCBloodBibleStatus::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCBloodBibleStatus("
		<< "ItemType=" << (int)m_ItemType
		<< ",ZoneID=" << (int)m_ZoneID
		<< ",Storage=" << (int)m_Storage
		<< ",OwnerName=" << m_OwnerName.c_str()
		<< ",Race=" << (int)m_Race
		<< ",ShrineRace=" << (int)m_ShrineRace
		<< ",X=" << (int)m_X
		<< ",Y=" << (int)m_Y
		<< ")";

	return msg.toString();
		
	__END_CATCH
}


