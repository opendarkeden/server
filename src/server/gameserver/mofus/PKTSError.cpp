/////////////////////////////////////////////////////////////////////////////
// Filename : PKTSError.cpp
// Desc		: 온라인 서버에서 처리 에러에 대한 결과를 보내기 위해서 사용된다.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTSError.h"
#include "MPacketID.h"

// 생성자
PKTSError::PKTSError()
{
	nSize = szPKTSError - szMPacketSize;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTSError::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTSError );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTSError::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nError		= htonl( nError );

	oStream.write( (const char*)this, szPKTSError );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// debug message
string PKTSError::toString() const
{
	StringStream msg;
	msg << "Result("
		<< "ErrorCode:" << nError
		<< ")";

	return msg.toString();
}

