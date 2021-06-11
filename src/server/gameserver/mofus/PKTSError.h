/////////////////////////////////////////////////////////////////////////////
// Filename : PKTSError.h
// Desc		: 온라인 서버에서 처리 에러에 대한 결과를 보내기 위해서 사용된다.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_SERROR_H__
#define __PKT_SERROR_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 에러 코드
enum MSERR_CODE
{
	MSERR_MATCH = 0x01,			// 회원을 확인했으나 정보가 서로 매치 되지
								// 않을 경우 ( 즉 요청자와 파워짱 정보가
								// 일치 되지 않을 경우 )
};

// 패킷 구조
struct _PKT_SERROR
{
	int nSize;			// 패킷 전체의 크기
	int nCode;			// 패킷 코드
	int nError;			// 에러 코드
};

const int szPKTSError = sizeof(_PKT_SERROR);

// class PKTSError
class PKTSError : public _PKT_SERROR, public MPacket
{
public:
	// 생성자
	PKTSError();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTSError - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환
	MPacket* create()
	{
		MPacket* pPacket = new PKTSError;
		Assert( pPacket != NULL );
		return pPacket;
	}

	// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
	void read( SocketInputStream& iStream );

	// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
	void write( SocketOutputStream& oStream );

	// debug message
	string toString() const;

public:
	// 에러 코드 설정
	void setErrorCode( int errorCode ) { nError = errorCode; }
};

#endif

