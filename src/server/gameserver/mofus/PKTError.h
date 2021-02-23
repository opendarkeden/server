/////////////////////////////////////////////////////////////////////////////
// Filename : PKTError.h
// Desc		: 파워짱 서버에서 에러에 대한 결과를 보내기 위해서 사용된다.
// 			  온라인 서버에서는 서버 오류로 일관 처리하고 대부분
// 			  디버그용으로 사용
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_ERROR_H__
#define __PKT_ERROR_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 에러 코드
enum MERR_CODE
{
	MERR_SERVER = 0x01,			// 서버는 살아 있으나 현재 정상적으로
								// 동작하지 못하는 상황
	MERR_CONFIRM = 0x02,		// 온라인 게임 코드로 확인 이 실패할 경우
	MERR_PACKET = 0x03,			// 잘못된 패킷이 송/수신된 경우
	MERR_PROCESS = 0x04,		// 서버 처리 오류 ( ex: DB 오류 )
	MERR_SEARCH = 0x05,			// 파워짱 회원이 아닌 경우
	MERR_NULLPOINT = 0x06,		// 파워짱 회원이나 누적된 파워짱 포인트가
								// 없는 경우
	MERR_MATCHING = 0x07,		// 매칭 정보 오류 (ex: 회원 매칭 정보가 없음)
								// 홈페이지에서 매칭을 유도하는 문장을 전송.
};

// 패킷 구조
struct _PKT_ERROR
{
	int nSize;			// 패킷 전체의 크기
	int nCode;			// 패킷 코드
	int nError;			// 에러 코드
};

const int szPKTError = sizeof(_PKT_ERROR);

// class PKTError
class PKTError : public _PKT_ERROR, public MPacket
{
public:
	// 생성자
	PKTError();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTError - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환
	MPacket* create()
	{
		MPacket* pPacket = new PKTError;
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
	// get error code
	int getErrorCode() const { return nError; }
};

#endif

