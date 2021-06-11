//////////////////////////////////////////////////////////////////////////////
// Filename    : LogClient.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __LOGCLIENT_H__
#define __LOGCLIENT_H__

#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// LogType
// 로그의 종류는 중요도에 따라 일정 그룹으로 구분할 수 있다.
// 현재는 1000 단위로 그 로그 그룹을 구분한다.
// LogClient 내부의 LogLevel을 1000 단위로 지정하면,
// 일정 그룹의 로그는 로그하고, 나머지는 로그하지 않는 일이 가능하다.
//////////////////////////////////////////////////////////////////////////////

enum LogType
{
	LOG_SYSTEM              =    0, // 시스템 로그
	LOG_SYSTEM_ERROR        =   10, // 시스템 에러 로그

	LOG_GAMESERVER          =   20, // 게임 서버 메시지
	LOG_GAMESERVER_ERROR    =   30, // 게임 서버 에러 메시지

	LOG_LOGINSERVER         =   40, // 로그인 서버 메시지
	LOG_LOGINSERVER_ERROR   =   50, // 로그인 서버 에러 메시지

	LOG_SHAREDSERVER         =   60, // 로그인 서버 메시지
	LOG_SHAREDSERVER_ERROR   =   70, // 로그인 서버 에러 메시지

	LOG_CGCONNECT           =   80, // 게임 서버에 로그인

	LOG_PICKUP_ITEM         = 1010, // 아이템 줍기
	LOG_DROP_ITEM           = 1020, // 아이템 떨어뜨리기

	LOG_PICKUP_MONEY        = 1030, // 돈 줍기
	LOG_DROP_MONEY          = 1040, // 돈 떨어뜨리기

	LOG_USE_ITEM            = 1050, // 아이템 사용하기
	LOG_CREATE_ITEM         = 1060, // 아이템 생성하기 (성수나 폭탄)
	LOG_REPAIR_ITEM         = 1065, // 아이템을 수리함
	LOG_DESTROY_ITEM        = 1070, // 아이템 내구력이 다 되어 부서짐

	LOG_BUY_ITEM            = 1080, // 상점에서 아이템 사기
	LOG_SELL_ITEM           = 1090, // 상점에서 아이템 팔기
	LOG_SHOP_CREATE_ITEM    = 1100, // 상점에서 아이템이 생성
	LOG_SHOP_DESTROY_ITEM   = 1110, // 상점에서 아이템이 사라짐

	LOG_DROP_ITEM_DIE       = 1120, // 죽으면서 아이템을 떨어뜨림
	LOG_DROP_ITEM_MORPH     = 1130, // 변신하면서 아이템을 떨어뜨림
	LOG_LOOT_CORPSE         = 1140, // 시체에서 아이템을 꺼냄

	LOG_STASH_ADD_ITEM      = 1150, // 보관함에 아이템을 넣음
	LOG_STASH_REMOVE_ITEM   = 1160, // 보관함에서 아이템을 뺌
	LOG_STASH_ADD_MONEY     = 1170, // 보관함에 돈을 넣음
	LOG_STASH_REMOVE_MONEY  = 1180, // 보관함에서 돈을 뺌

	LOG_USE_BONUS_POINT     = 1190, // 보너스 포인트를 사용

	LOG_TRADE               = 1200, // 교환

	LOG_KILL_PLAYER         = 2000, // 플레이어가 플레이어를 죽임

	LOG_BLOODDRAIN          = 2010, // 피를 빰
	LOG_BLOODDRAINED        = 2020, // 피를 빨림

	LOG_SLAYER_TO_VAMPIRE   = 2030, // 슬레이어에서 뱀파이어로
	LOG_VAMPIRE_TO_SLAYER   = 2040, // 뱀파이어에서 슬레이어로
	LOG_HEAL                = 2050, // 치료를 받다

	LOG_DEBUG_MSG           = 3000, // 디버깅 관련 메시지

	LOGTYPE_MAX                
};


//////////////////////////////////////////////////////////////////////////////
// class LogClient
// 로그를 위한 클라이언트 클래스이다. SIGNAL에 관한 처리는 일부러
// 하지 않았으므로, 클래스 외부에서 SIGNAL 처리를 해줘야 한다. 그렇지 않으면
// 로그 서버가 죽으면 같이 죽어버린다.
//
// 로그 레벨 (큰 로그레벨은 하위 레벨의 로그를 포함한다.)
// 0    : 서버 시스템 관련 내용만 로그한다.
// 1000 : 게임 내에서 제일 중요한 부분을 로그한다.
// 2000 : 게임 내에서 별로 중요하지 않은 부분도 로그한다.
//////////////////////////////////////////////////////////////////////////////

class LogClient
{

///// member methods /////

public:
	LogClient(string ip, short port);
	virtual ~LogClient();

public:
	void connect(string ip, short port);
	void disconnect(void);

	void _log(short type, const string& source, const string& target);
	void _log(short type, const string& source, const string& target, const string& content);
	void _log(short type, const string& source, const string& target, const string& content, short ZoneID);

public:
	static int getLogLevel(void) { return m_LogLevel; }
	static void setLogLevel(int level) { m_LogLevel = level; }

///// member data /////

protected:
	int       m_Socket;
	bool      m_bConnected;
	long long m_Sent;

	static int m_LogLevel;
};

//////////////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////////////

extern LogClient* g_pLogClient;

void log(short type, const string& source, const string& target);
void log(short type, const string& source, const string& target, const string& content);
void log(short type, const string& source, const string& target, const string& content, short ZoneID);


#endif


