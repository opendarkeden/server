/////////////////////////////////////////////////////////////////////////////
// Filename : PKTError.cpp
// Desc		: 파워짱 서버에서 에러에 대한 결과를 보내기 위해서 사용된다.
// 			  온라인 서버에서는 서버 오류로 일관 처리하고 대부분
// 			  디버그용으로 사용
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTError.h"
#include "MPacketID.h"

// 생성자
PKTError::PKTError()
{
	nSize = szPKTError - szMPacketSize;
}

// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
void PKTError::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTError );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
void PKTError::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nError		= htonl( nError );

	oStream.write( (const char*)this, szPKTError );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// debug message
string PKTError::toString() const
{
	StringStream msg;
	msg << "Result("
		<< "ErrorCode:" << nError
		<< ")";

	return msg.toString();
}

