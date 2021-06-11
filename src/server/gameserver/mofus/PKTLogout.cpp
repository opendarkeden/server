/////////////////////////////////////////////////////////////////////////////
// Filename : PKTLogout.cpp
// Desc		: 접소을 종료함을 통지한다.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTLogout.h"
#include "MPacketID.h"

// 생성자
PKTLogout::PKTLogout()
{
	nSize = szPKTLogout - szMPacketSize;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTLogout::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTLogout );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTLogout::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTLogout );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTLogout::toString() const
{
	return "Logout()";
}

