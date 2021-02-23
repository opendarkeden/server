//////////////////////////////////////////////////////////////////////////////
// File Name 	: Statement.cpp
// Written by	: Gday29@ewestsoft.com
// Description	: SQL 문을 만든다..
//////////////////////////////////////////////////////////////////////////////

#include "Statement.h"
#include <stdio.h>
#include <sys/time.h>
#include <mysql/mysql.h>
#include "Result.h"
#include "Assert.h"
#include "Mutex.h"
#include "Profile.h"

#define __FULL_PROFILE__

#ifndef __FULL_PROFILE__
#undef beginProfileEx
#define beginProfileEx(name) ((void)0)
#undef endProfileEx
#define endProfileEx(name) ((void)0)
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Statement::Statement() 
	throw ()
{
	__BEGIN_TRY

	m_pConnection   = NULL;
	m_pResult       = NULL;
	m_nAffectedRows = 0;

	__END_CATCH
}

Statement::Statement (char * fmt , ... ) 
	throw (Error )
{
	__BEGIN_TRY

	// variable argument list
	va_list valist;
	
	va_start(valist , fmt );
	
	char buffer[2048];
	
	int nchars = vsnprintf(buffer, 2048, fmt, valist );

	// 만약 버퍼 크기가 부족하게 되면, 에러를 던져서 수동으로 값을 증가시켜야 한다.
	if (nchars == -1 || nchars > 2048 )
		throw Error("more buffer size needed for SQL statement buffer...");
	
	va_end(valist);
	
	// string 이므로 대입해도 안전하다. 
	// 만약 char * 였다면, local variable을 포인팅하는 것은 위험하다.
    m_Statement = buffer;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 쿼리문에서 만든 결과를 메모리에서 해제한다.
//
//////////////////////////////////////////////////////////////////////

Statement::~Statement() 
	throw ()
{
	__BEGIN_TRY

	if (m_pResult != NULL ) 
	{
		delete m_pResult;
		m_pResult = NULL;
	}
	
	__END_CATCH
}

    
//////////////////////////////////////////////////////////////////////
//
// executeQuery()
//
// Connection, SQL문을 스트링으로 받아서 결과값을 Result *로 리턴한다.
//
//////////////////////////////////////////////////////////////////////

Result * Statement::executeQuery () 
	throw (SQLQueryException , Error )
{
	__BEGIN_TRY
		
	Assert(m_pConnection != NULL );

	if (m_pResult != NULL ) 
	{
		// 어플리케이션에서 Result 를 삭제하지 않은 경우,
		delete m_pResult;
		m_pResult = NULL;
	}

	beginProfileEx("ZPM_QUERY");

	if (mysql_real_query(m_pConnection->getMYSQL(), m_Statement.c_str() , m_Statement.size() ) != 0 )
	{
		cout << "Stmt::EQ real Query Error" << endl;
		cout << "Stmt [" << m_Statement << "]" << endl;
		cout << getError() << endl;

		throw SQLQueryException(getError() );
	}
	
	MYSQL_RES * pResult = mysql_store_result(m_pConnection->getMYSQL());
	
	// 쿼리 결과값이 NULL일 경우는 update문이거나 에러이다.
	if (pResult != NULL)
	{
		m_pResult = new Result(pResult, m_Statement);
	}
	else 
	{
		//if (mysql_num_fields(m_pConnection->getMYSQL() ) != 0 )
		if (mysql_field_count(m_pConnection->getMYSQL() ) != 0 )
		{
			cerr << "Stmt::EQ Unknown Error > " << getError() << endl;

			throw SQLQueryException(getError() );
		}
		else
		{
			m_nAffectedRows = mysql_affected_rows(m_pConnection->getMYSQL());
		}
	}

	endProfileEx("ZPM_QUERY");

	return m_pResult;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// executeQuery ()
//
// Connection, SQL문을 스트링으로 받아서 결과값을 Result *로 리턴한다.
//
//////////////////////////////////////////////////////////////////////

Result * Statement::executeQuery (const string& sqlStatement )
	throw (SQLQueryException, Error )
{
	__BEGIN_TRY
		
	m_Statement = sqlStatement;

	return executeQuery();

	__END_CATCH
}	
	
//////////////////////////////////////////////////////////////////////
//
// executeQuery ()
//
// Connection, SQL문을 스트링으로 받아서 결과값을 Result *로 리턴한다.
//
//////////////////////////////////////////////////////////////////////

Result * Statement::executeQuery (char * fmt , ... ) 
	throw (SQLQueryException, Error )
{
	__BEGIN_TRY
		
	// SQL Statement 를 만들어낸다.
	va_list valist;

	va_start(valist, fmt);

	char buffer[2048+1];

	int nchars = vsnprintf(buffer, 2048, fmt, valist );

	// 만약 버퍼 크기가 부족하게 되면, 예외를 던져서 값을 증가시켜야 한다.
	if (nchars == -1 || nchars > 2048 )
		throw Error("more buffer size needed for SQL statement buffer...");

	va_end(valist);

	m_Statement = buffer;

	return executeQuery();

	__END_CATCH
}	
	
//////////////////////////////////////////////////////////////////////
//
//	setStatement()
//
//	쿼리문을 다시 만든다.
//
//////////////////////////////////////////////////////////////////////

void Statement::setStatement (char * fmt , ... ) 
	throw (Error ) 
{
	__BEGIN_TRY

	// variable argument list
	va_list valist;
	
	va_start(valist, fmt );
	
	// buffer size = 1kb..Too big??
	char buffer[2048+1];
	
	int nchars = vsnprintf(buffer, 2048 , fmt, valist );
	
	// 만약 버퍼 크기가 부족하게 되면, 예외를 던져서 값을 증가시켜야 한다.
	if (nchars == -1 || nchars > 2048 )
		throw Error("more buffer size needed for SQL statement buffer...");

	va_end(valist);
	
	m_Statement = buffer;
	
	__END_CATCH	
}

uint Statement::getInsertID() const throw()
{
	__BEGIN_TRY
	return mysql_insert_id( m_pConnection->getMYSQL() );
	__END_CATCH
}
