/////////////////////////////////////////////////////////////////////////////
// Filename : PKTPowerPoint.h
// Desc		: 온라인 게임으로부터 전송되어온 데이터를 통해 파워링 DB에서
// 			  추훌한 값을 온라인사로 넘겨준다.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_POWERPOINT_H__
#define __PKT_POWERPOINT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// 패킷 구조
struct _PKT_POWERPOINT
{
	int nSize;
	int nCode;
	int nMoDataCode;				// 자료 처리를 위한 Index, Unique 값
	char sPhoneNo[12];				// 파워링 포인트를 등록한 유저의 핸드폰 번호
	char sMemID[20];				// 파워링 유저 계정 ID
	int nMatchingCode;				// 파워링 테이블내 매칭 코드
	char sMoGameName[20];			// 온라인 게임과 연동된 모바일 게임명
	int nMoGameCode;				// 온라인 게임과 연동되 모바일 게임코드
	int nOnGameCode;				// 온라인 게임 코드
	char sOnGameName[20];			// 온라인 게임명
	int nOnGameSerCode;				// 온라인 게임 서버 코드
	char sOnGameSerName[20];		// 온라인 게임 서버 명
	char sOnGameID[20];				// 온라인 게임 아이디
	char sCharName[40];				// 온라인 게임 캐릭터명
	int nOnAbilityCode;				// 온라인 게임 적용 능력치 코드
	char sOnAbilityName[20];		// 온라인 게임 적용 능력치명
	int nPowerPoint;				// 유저가 전송한 파워링 포인트
	char sInputDate[20];			// 유저가 모바일로 입력한 파워링 포인트 입력 시간
	int nIndex;						// 온라인사의 편의를 위한 인덱스
	int nContinue;					// 다음 데이터 유무. 1:있음. 0:없음
};

const int szPKTPowerPoint = sizeof(_PKT_POWERPOINT);

// class PKTPowerPoint
class PKTPowerPoint : public _PKT_POWERPOINT, public MPacket
{
public:
	// 생성자
	PKTPowerPoint();

public:
	// 패킷 아이디를 반환한다.
	MPacketID_t getID() const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getSize() const
	{
		return szPKTPowerPoint - szMPacketSize;
	}

	// 새로운 패킷을 생성해서 반환
	MPacket* create()
	{
		MPacket* pPacket = new PKTPowerPoint;
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
	// get methods
	bool isContinue() const { return nContinue == 1; }

	// get PowerPoint
	int getPowerPoint() const { return nPowerPoint; }

	// get GameCode
	int getGameCode() const { return nOnGameCode; }

	// get GameServerCode
	int getGameServerCode() const { return nOnGameSerCode; }

	// get Character Name
	const char* getCharacterName() const { return (const char*)sCharName; }
};

#endif

