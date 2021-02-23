//////////////////////////////////////////////////////////////////////////////
// Filename    : DatabaseManager.h
// Written By  : elca
// Description : 데이타베이스 매니저
//////////////////////////////////////////////////////////////////////////////

#ifndef __DATABASE_MANAGER_H__
#define __DATABASE_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Connection.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class DatabaseManager;
//////////////////////////////////////////////////////////////////////////////

class DatabaseManager 
{
public:
	DatabaseManager() throw();
	~DatabaseManager() throw();
	
public:
	void init() throw(Error);
	void addConnection(int TID, Connection * pConnection) throw(DuplicatedException);
	void addDistConnection(int TID, Connection * pConnection) throw(DuplicatedException);
	void addCBillingConnection(int TID, Connection * pConnection) throw(DuplicatedException);
//	void addPCRoomConnection(int TID, Connection * pConnection) throw(DuplicatedException);

	Connection* getConnection(const string& ip) throw(NoSuchElementException);
	Connection* getDistConnection(const string& ip) throw(NoSuchElementException);
	Connection* getCBillingConnection(const string& ip) throw(NoSuchElementException);
//	Connection* getPCRoomConnection(const string& ip) throw(NoSuchElementException);
	Connection* getUserInfoConnection(void) throw() { return m_pUserInfoConnection; }
	void	executeDummyQuery(Connection* pConnection) throw (Error);

	//--------------------------------------------------------------------
	// * elca's NOTE
	// 로그인 서버에서는 캐릭터의 정보를 어디서 얻어오는지 알아내기 위하여
	// DB의 위치를 알아내 온다.
	// 메인 DB에서는 DB의 위치를 포함하는 Table이 존재해야 한다.
	// GameServerIP로 뽑아 낼 수도 있지만 DB와 GameServer가 다른 경우를
	// 생각하여 확장성을 고려한다.
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// * elca's NOTE
	// 각 게임 서버의 경우 Parent/Main DB만을 알면 된다.
	// 메인 DB 서버의 월드 아이디는 무조건 0 번이라고 약정하고
	// 메인 DB 서버에 쿼리는 0 번 인자로 넘긴다.
	// 게임 서버일 경우 이 0 번의 커넥션만 가지고 있으면 된다.
	// 혹시나 하는 버그의 우려가 있기 때문에 절대 다른 커넥션은 열지 않도록
	// 주의 하도록 한다.
	// 일반 게임 서버에서의 쿼리는 쓰레드 별로 나뉘어져 있기 때문에
	// 신경쓰지 않도록 한다.
	//--------------------------------------------------------------------
	Connection* getConnection( int TID ) throw(NoSuchElementException);
//	void addConnection(WorldID_t WorldID, Connection * pConnection) throw(DuplicatedException);

private:
	// 각 쓰레드별로 존재하는 DB 연결
	hash_map<int, Connection*> m_Connections;

	// 각 쓰레드별로 존재하는 Distribute DB 연결
	hash_map<int, Connection*> m_DistConnections;

//	hash_map<WorldID_t, Connection*> m_WorldConnections;
	hash_map<int, Connection*> m_WorldConnections;

	// 각 쓰레드별로 존재하는 CBilling DB 연결
	hash_map<int, Connection*> m_CBillingConnections;

	// PC방 통합용 DB 연결
//	hash_map<int, Connection*> m_PCRoomConnections;

	// 각 월드별로 존재하는 DB 연결

	// 제일 처음 생성되는 기본 DB 연결
	Connection* m_pDefaultConnection;

	// 제일 처음 생성되는 최 상위 DB의 기본 연결
	Connection* m_pWorldDefaultConnection;

	// 사용자 통계 관련 DB 연결
	Connection* m_pUserInfoConnection;

	Connection* m_pDistConnection;

	// PC방 통합용 DB 연결 default. 로그인 서버에서 쓴다.
//	Connection* m_pPCRoomConnection;

	mutable Mutex m_Mutex;
};

extern DatabaseManager * g_pDatabaseManager;

#endif
