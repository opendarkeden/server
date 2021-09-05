//////////////////////////////////////////////////////////////////////
//
// File Name	: Connection.cpp
// Written by	: Gday29@ewestsoft.com
// Description	: Ŀ�ؼ� Ŭ���� ����
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Connection.h"
#include "Statement.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// ������ ���̽��� �����ϰ�, �����ͺ��̽��� �����Ѵ�.
// ���ܸ� ������ �κ��� �����ؾ� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

Connection::Connection ()
: m_bConnected(false), m_bBusy(false)
{
	__BEGIN_TRY

	m_Mutex.setName("Connection");

	// MYSQL ��ü�� �ʱ�ȭ�Ѵ�.
	if ( mysql_init(&m_Mysql) == NULL ) {
		throw Error( mysql_error(&m_Mysql) );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// *CAUTION*
//
// connect()�� ȣ���� �� port �� ������� ���� ���, ����Ʈ���� 0 �� ���Ǹ�
// �̶� MYSQL�� ����Ʈ ��Ʈ�� ���ȴ�. �׷�����, ������ ���ؼ� MYSQL�� �ٸ�
// ��Ʈ���ٰ� ������� �� ���̴�. ����, ��Ʈ�� ������ �ʿ䰡 �ִ�.
//
//////////////////////////////////////////////////////////////////////

Connection::Connection ( string host , string db , string user , string password , uint port )
: m_bConnected(false), m_Host(host), m_Port(port), m_Database(db), m_User(user), m_Password(password)
{
	__BEGIN_TRY

	m_Mutex.setName("Connection");
		
	// MYSQL ��ü�� �ʱ�ȭ�Ѵ�.
	if ( mysql_init(&m_Mysql) == NULL )
		throw Error( mysql_error(&m_Mysql) );

	// �ٷ� ������ �õ��Ѵ�.
	connect( m_Host , m_Database , m_User , m_Password , m_Port );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
//	destructor
//
//////////////////////////////////////////////////////////////////////

Connection::~Connection() 
{
	// ����Ǿ� ���� ���, ������ ���´�.
    if ( m_bConnected ) {
		close();
    }
}

//////////////////////////////////////////////////////////////////////
//
// connect()	
//
// Connection ��ü�� ������ ��, ��� ������ �� ���� ���� ���
// �ϴ� default constructor �� ����ؼ� ��ü�� ������ ����, 
// ������ �� ���� �޾Ƽ� ���� �����͸������ �ʱ�ȭ�� �� �����Ѵ�. 
//
// *CAUTION*
//
// connect()�� ȣ���� �� port �� ������� ���� ���, ����Ʈ���� 0 �� ���Ǹ�
// �̶� MYSQL �� ����Ʈ ��Ʈ�� ���ȴ�. �׷�����, ������ ���ؼ� MYSQL�� �ٸ�
// ��Ʈ���ٰ� ������� �� ���̴�.
//
// ����Ʈ �Ķ���͸� ����ؾ� �ϱ� ������, ��Ʈ �Ķ���Ͱ� �� �ڷ� ����.. *_*;
//
// ex> Connection conn;
//     conn.connect( "vampire.ewestsoft.com" , "bbs" , "bbsuser" , "bbspassword" );
//
//////////////////////////////////////////////////////////////////////

void Connection::connect ( string host , string db , string user , string password , uint port )
	
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
// �����ڿ��� ����  ������ �Է¹��� ���, �ٷ� �� �޽�带 ȣ���ؼ�
// ������ �õ��Ѵ�.
//
//////////////////////////////////////////////////////////////////////

void Connection::connect ()
	
{
	__BEGIN_TRY
		
	// ������ �Ϸ��� �ϴµ� �̹� ������ �Ǿ��ִٸ� ������.
	if ( m_bConnected ) 
	{
		// �̷� ���, ������ �ݾ� �ְ� ���ܸ� ������ �� ���̴�.
		close();

		throw SQLConnectException("Already Connected"); 
	}

	//--------------------------------------------------
	// ������ ������� üũ�ؾ� ��...
	//--------------------------------------------------
	m_bConnected = ( mysql_real_connect( &m_Mysql, m_Host.c_str(), m_User.c_str(), m_Password.c_str(), m_Database.c_str(), m_Port , 0, 0 ) != NULL );
	//cout << "Connection Calls~~~" << endl;
	
	// ������°� �ƴ϶�� ������.
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
//	������ ���´�.
//
//////////////////////////////////////////////////////////////////////

void Connection::close () 
	
{
	__BEGIN_TRY
		
    if( ! m_bConnected ) 
	{
		throw SQLConnectException("Not Connected");
    }
	
	// void �̹Ƿ� ����.. - -;
    mysql_close( &m_Mysql );

	m_bConnected = false;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//	
//	createStatement
//
//	���ο� Statement ��ü�� ����� �� ��ü�� �����͸� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

Statement * Connection::createStatement ()
{
	__BEGIN_TRY
		
	// ���ο� Statement ��ü�� �����.
	Statement * pStatement = new Statement();
	
	// ���� ��ü�� Ŀ�ؼ� ���� �� Ŀ�ؼ� ��ü�� �ϰ�..
	pStatement->setConnection(this);
	
	// �����Ѵ�.
	return pStatement;
	
	__END_CATCH
}
