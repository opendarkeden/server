/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAsk.h
// Desc		: 온라인 게임 서버가 파워짱 서버에 자사의 게임 코드와 함께
// 			  접속을 요청한다.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ASK_H__
#define __PKT_CONNECT_ASK_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 패킷 구조
struct _PKT_CONNECT_ASK
{
	int nSize;			// 패킷 전체의 크기
	int nCode;			// 패킷 코드
	int nOnGameCode;	// 모퍼스에서 발급한 온라인사 게임 코드 값
};

const int szPKTConnectAsk = sizeof(_PKT_CONNECT_ASK);

// class PKTConnectASK
class PKTConnectAsk : public _PKT_CONNECT_ASK, public MPacket
{
public:
	// 생성자
	PKTConnectAsk();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTConnectAsk - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환
	MPacket* create()
	{
		MPacket* pPacket = new PKTConnectAsk;
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
	// get/set OnGameCode
	int getOnGameCode() const { return nOnGameCode; }
	void setOnGameCode( int onGameCode ) { nOnGameCode = onGameCode; }
};

#endif

