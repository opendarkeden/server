//////////////////////////////////////////////////////////////////////
// 
// Filename    : WorldInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "WorldInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
WorldInfo::WorldInfo () 
     throw ()
{
	__BEGIN_TRY
	m_Stat = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
WorldInfo::~WorldInfo () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void WorldInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName;
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ID );
	iStream.read( szName );
	iStream.read( m_Name, szName );
	iStream.read( m_Stat );

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void WorldInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_Stat );

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t WorldInfo::getSize()
	throw()
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	PacketSize_t PacketSize = szWorldID + szBYTE + szName + szBYTE;

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string WorldInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "WorldInfo( "
		<< "ID : "<< m_ID
		<< "Name : " << m_Name
		<< "Stat : " << m_Stat
		<< ")";

	return msg.toString();

	__END_CATCH
}


