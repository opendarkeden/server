/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAsk.cpp
// Desc		: 온라인 게임 서버가 파워짱 서버에 자사의 게임 코드와 함께
// 			  접속을 요청한다.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTConnectAsk.h"

// 생성자
PKTConnectAsk::PKTConnectAsk()
{
	nSize = szPKTConnectAsk - szMPacketSize;
	nOnGameCode = 10;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTConnectAsk::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTConnectAsk );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nOnGameCode	= ntohl( nOnGameCode );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTConnectAsk::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nOnGameCode	= htonl( nOnGameCode );

	oStream.write( (const char*)this, szPKTConnectAsk );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nOnGameCode	= ntohl( nOnGameCode );
}

// debug message
string PKTConnectAsk::toString() const
{
	StringStream msg;

	msg << "ConnectAsk("
		<< "OnGameCode:" << nOnGameCode
		<< ")";

	return msg.toString();
}

