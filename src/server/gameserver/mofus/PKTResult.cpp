/////////////////////////////////////////////////////////////////////////////
// Filename : PKTResult.cpp
// Desc		: 마지마긍로 전송 받은 자료에 대한 처리 여부를 파워링 서버에
// 			  답신한다.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTResult.h"
#include "MPacketID.h"

// 생성자
PKTResult::PKTResult()
{
	nSize = szPKTResult - szMPacketSize;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTResult::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTResult );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTResult::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTResult );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTResult::toString() const
{
	return "Result()";
}

