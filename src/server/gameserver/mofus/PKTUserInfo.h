/////////////////////////////////////////////////////////////////////////////
// Filename : PKTUserInfo.h
// Desc		: 온라인 게임 유저ID, 캐릭터명, 회원이름, 서버의 정보를
// 			  파워링 서버로 보내 회원을 인증한다.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_USERINFO_H__
#define __PKT_USERINFO_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 패킷 구조
struct _PKT_USERINFO
{
	int nSize;
	int nCode;
	char sJuminNo[20];		// 주민번호
	char sHandPhone[12];	// 핸드폰 번호
	int nIndex;				// 온라인사의 편의를 위한 인덱스
};

const int szPKTUserInfo = sizeof(_PKT_USERINFO);

// class PKTUserInfo
class PKTUserInfo : public _PKT_USERINFO, public MPacket
{
public:
	// 생성자
	PKTUserInfo();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTUserInfo - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환
	MPacket* create()
	{
		MPacket* pPacket = new PKTUserInfo;
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
	// set ssn & cellnum
	void setSSN( const string& ssn );
	void setCellNum( const string& cellnum );
};

#endif

