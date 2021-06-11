//////////////////////////////////////////////////////////////////////
//
// File Name	: Connection.cpp
// Written by	: Gday29@ewestsoft.com
// Description	: 커넥션 클래스 구현
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Connection.h"
#include "Statement.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 데이터 베이스와 연결하고, 데이터베이스를 선택한다.
// 예외를 던지는 부분은 수정해야 한다.
//
//////////////////////////////////////////////////////////////////////

Connection::Connection ()
	throw ( Error )
: m_bConnected(false), m_bBusy(false)
{
	__BEGIN_TRY

	m_Mutex.setName("Connection");

	// MYSQL 객체를 초기화한다.
	if ( mysql_init(&m_Mysql) == NULL ) {
		throw Error( mysql_error(&m_Mysql) );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// *CAUTION*
//
// connect()를 호출할 때 port 를 명시하지 않을 경우, 디폴트값인 0 이 사용되며
// 이때 MYSQL의 디폴트 포트가 사용된다. 그렇지만, 보안을 위해서 MYSQL을 다른
// 포트에다가 띄워놔야 할 것이다. 따라서, 포트를 지정할 필요가 있다.
//
//////////////////////////////////////////////////////////////////////

Connection::Connection ( string host , string db , string user , string password , uint port )
	throw ( SQLConnectException , Error )
: m_bConnected(false), m_Host(host), m_Port(port), m_Database(db), m_User(user), m_Password(password)
{
	__BEGIN_TRY

	m_Mutex.setName("Connection");
		
	// MYSQL 객체를 초기화한다.
	if ( mysql_init(&m_Mysql) == NULL )
		throw Error( mysql_error(&m_Mysql) );

	// 바로 연결을 시도한다.
	connect( m_Host , m_Database , m_User , m_Password , m_Port );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
//	destructor
//
//////////////////////////////////////////////////////////////////////

Connection::~Connection() 
	throw ( Error )
{
	__BEGIN_TRY
		
	// 연결되어 있을 경우, 연결을 끊는다.
    if ( m_bConnected ) {
		close();
    }
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// connect()	
//
// Connection 객체가 생성될 때, 어디에 연결할 지 알지 못할 경우
// 일단 default constructor 를 사용해서 객체를 생성한 다음, 
// 연결할 때 값을 받아서 내부 데이터멤버들을 초기화한 후 연결한다. 
//
// *CAUTION*
//
// connect()를 호출할 때 port 를 명시하지 않을 경우, 디폴트값인 0 이 사용되며
// 이때 MYSQL 의 디폴트 포트가 사용된다. 그렇지만, 보안을 위해서 MYSQL을 다른
// 포트에다가 띄워놔야 할 것이다.
//
// 디폴트 파라미터를 사용해야 하기 때문에, 포트 파라미터가 맨 뒤로 갔다.. *_*;
//
// ex> Connection conn;
//     conn.connect( "vampire.ewestsoft.com" , "bbs" , "bbsuser" , "bbspassword" );
//
//////////////////////////////////////////////////////////////////////

void Connection::connect ( string host , string db , string user , string password , uint port )
	throw ( SQLConnectException )
{
	__BEGIN_TRY

	m_Host = host;
	m_Port = port;
	m_Database = db;
	m_User = user;
	m_Password = password;

	connect();

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
//
// connect()	
//
// 생성자에서 직접  정보를 입력받을 경우, 바로 이 메쏘드를 호출해서
// 연결을 시도한다.
//
//////////////////////////////////////////////////////////////////////

void Connection::connect ()
	throw ( SQLConnectException )
{
	__BEGIN_TRY
		
	// 연결을 하려구 하는데 이미 연결이 되어있다면 에러다.
	if ( m_bConnected ) 
	{
		// 이럴 경우, 연결은 닫아 주고 예외를 던져야 할 것이다.
		close();

		throw SQLConnectException("Already Connected"); 
	}

	//--------------------------------------------------
	// 에러가 생기는지 체크해야 함...
	//--------------------------------------------------
	m_bConnected = ( mysql_real_connect( &m_Mysql, m_Host.c_str(), m_User.c_str(), m_Password.c_str(), m_Database.c_str(), m_Port , 0, 0 ) != NULL );
	//cout << "Connection Calls~~~" << endl;
	
	// 연결상태가 아니라면 에러다.
	if( ! m_bConnected ) 
	{
		throw SQLConnectException( mysql_error(&m_Mysql) );
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//	
//	close()
//
//	연결을 끊는다.
//
//////////////////////////////////////////////////////////////////////

void Connection::close () 
	throw ( SQLConnectException , Error )
{
	__BEGIN_TRY
		
    if( ! m_bConnected ) 
	{
		throw SQLConnectException("Not Connected");
    }
	
	// void 이므로 무시.. - -;
    mysql_close( &m_Mysql );

	m_bConnected = false;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//	
//	createStatement
//
//	새로운 Statement 객체를 만들어 그 객체의 포인터를 리턴한다.
//
//////////////////////////////////////////////////////////////////////

Statement * Connection::createStatement ()
	throw ()
{
	__BEGIN_TRY
		
	// 새로운 Statement 객체를 만든다.
	Statement * pStatement = new Statement();
	
	// 만든 객체의 커넥션 값을 이 커넥션 객체로 하고..
	pStatement->setConnection(this);
	
	// 리턴한다.
	return pStatement;
	
	__END_CATCH
}
