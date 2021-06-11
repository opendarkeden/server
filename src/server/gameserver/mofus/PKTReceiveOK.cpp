/////////////////////////////////////////////////////////////////////////////
// Filename : PKTReceiveOK.cpp
// Desc		: 받은 자료에 대한 처리 여부를 파워링 서버에 답신한다.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTReceiveOK.h"
#include "MPacketID.h"

// 생성자
PKTReceiveOK::PKTReceiveOK()
{
	nSize = szPKTReceiveOK - szMPacketSize;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTReceiveOK::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTReceiveOK );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTReceiveOK::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTReceiveOK );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTReceiveOK::toString() const
{
	return "ReceiveOK()";
}

