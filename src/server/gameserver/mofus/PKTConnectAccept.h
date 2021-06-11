/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAccept.h
// Desc		: 정상적으로 접속되었음을 패킷으로 알려준다.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ACCEPT_H__
#define __PKT_CONNECT_ACCEPT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 패킷 구조
struct _PKT_CONNECT_ACCEPT
{
	int nSize;		// 패킷 전체의 크리
	int nCode;		// 패킷 코드
};

const int szPKTConnectAccept = sizeof(_PKT_CONNECT_ACCEPT);

// class PKTConnectAccept
class PKTConnectAccept : public _PKT_CONNECT_ACCEPT, public MPacket
{
public:
	// 생성자
	PKTConnectAccept();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTConnectAccept - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환한다.
	MPacket* create()
	{
		MPacket* pPacket = new PKTConnectAccept;
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

