//////////////////////////////////////////////////////////////////////
//
// File Name 	: Connection.h
// Written by	: Gday29@ewestsoft.com
// Description	: 데이타베이스와의 연결을 담당하는 클래스
//
//////////////////////////////////////////////////////////////////////

#ifndef __CONNECTION_H__
#define __CONNECTION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <mysql/mysql.h>
#include "Mutex.h"

// forward declaration
class Statement;

//////////////////////////////////////////////////////////////////////
//
// class Connection;
//
// 데이터 베이스에 연결하고, 관리한다.
//
//////////////////////////////////////////////////////////////////////

class Connection {

public:
	
	// constructor
    Connection() throw(Error);

	// constructor(1-time connection)
    Connection(string host, string db, string user, string password, uint port = 0) throw(SQLConnectException, Error);
    
	// destructor
	~Connection() throw(Error);

    // close the connection to database
	void close() throw(SQLConnectException, Error);
	
	// 데이타베이스에 연결을 시도한다.
	void connect(string host, string db, string user, string password, uint port = 0) throw(SQLConnectException);

	// 데이타베이스에 연결을 시도한다.
	void connect() throw(SQLConnectException);
	
	// check the connection 
	bool isConnected() const throw() { return m_bConnected; }
	bool operator !() const throw() { return m_bConnected == false; }
	
	// Statement 객체를 생성해서 리턴한다.
	Statement * createStatement() throw();	
	
	// get the MYSQL object
	MYSQL * getMYSQL() throw() { return &m_Mysql; }
	
	// get MS's host name(ip)
	string getHost() const throw() { return m_Host; }

	// get MS's service port
	uint getPort() const throw() { return m_Port; }

	// get database name
	string getDatabase() const throw() { return m_Database; }

	// get user id 
	string getUser() const throw() { return m_User; }

	// get user password
	string getPassword() const throw() { return m_Password; }

	// get connection's name
	string getName() const throw() { return m_Name; }

	// set connection's name
	void setName(string name) throw() { m_Name = name; }

	// get/set busy status
	bool isBusy(void) const throw() { return m_bBusy;}
	void setBusy(bool busy=true) throw() { m_bBusy = busy;}

	// get error
	string getError() throw() { return mysql_error(&m_Mysql); }

	// lock/unlock
	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }
	
private:
	
	// ??
    MYSQL m_Mysql;

	// is connected?
	bool m_bConnected;

	// DBMS 가 운영되는 호스트 명
	string m_Host;

	// DBMS 의 연결 포트
	uint m_Port;

	// 데이타베이스 이름
	string m_Database;

	// 사용자 아이디
	string m_User;

	// 사용자 패스워드
	string m_Password;

	// connection name(DatabaseManager 에서 사용할 키값)
	string m_Name;

	// 현재 사용중인 커넥션인가?
	bool m_bBusy;

	// 동시 쿼리를 막기 위한 lock
	Mutex m_Mutex;

};

#endif // __CONNECTION_H__
