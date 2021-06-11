/////////////////////////////////////////////////////////////////////////////
// Filename : PKTResult.h
// Desc		: 마지막으로 전송 받은 자료에 대한 처리 여부를 파워링 서버에
// 			  답신한다.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_RESULT_H__
#define __PKT_RESULT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 패킷 구조
struct _PKT_RESULT
{
	int nSize;			// 패킷 전체의 크기
	int nCode;			// 패킷 코드
};

const int szPKTResult = sizeof(_PKT_RESULT);

// class PKTResult
class PKTResult : public _PKT_RESULT, public MPacket
{
public:
	// 생성자
	PKTResult();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTResult - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환
	MPacket* create()
	{
		MPacket* pPacket = new PKTResult;
		Assert( pPacket != NULL );
		return pPacket;
	}

	// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
	void read( SocketInputStream& iStream );

	// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
	void write( SocketOutputStream& oStream );

	// debug message
	string toString() const;

};

#endif

