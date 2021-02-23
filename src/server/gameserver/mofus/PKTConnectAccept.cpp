/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAccept.cpp
// Desc		: 정상적으로 접속되었음을 패킷으로 알려준다.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTConnectAccept.h"

// 생성자
PKTConnectAccept::PKTConnectAccept()
{
	nSize = szPKTConnectAccept - szMPacketSize;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTConnectAccept::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTConnectAccept );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTConnectAccept::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTConnectAccept );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTConnectAccept::toString() const
{
	return "ConenctAccept()";
}

