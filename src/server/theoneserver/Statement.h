//////////////////////////////////////////////////////////////////////
//
// File Name 	: Statement.h
// Written by	: Gday29@ewestsoft.com
// Description	: SQL 문을 만든다..
//
//////////////////////////////////////////////////////////////////////

#ifndef __STATEMENT_H__
#define __STATEMENT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Connection.h"

// forward declaration
class Result;

//////////////////////////////////////////////////////////////////////
//
// class Statement;
//
// SQL문을 만들어 디비에 쿼리한다.
//
//////////////////////////////////////////////////////////////////////

class Statement {

public:
	
	// constructor
	Statement() throw(); 

	// constructor
    Statement(char * fmt, ...) throw(Error);

	// destructor
	~Statement() throw();

public:
    
	// 사전에 지정된 SQL 문을 가지고 쿼리한다.
    Result * executeQuery() throw(SQLQueryException, Error);
	
	// SQL 문을 받아서 쿼리한다.
	Result * executeQuery(char *,...) throw(SQLQueryException, Error);
	Result * executeQuery(const string& sqlStatement) throw(SQLQueryException, Error);
	
	// get SQL statement
	string getStatement() const throw() { return m_Statement; }

	// SQL 문을 지정한다.
	void setStatement(char * fmt, ...) throw(Error);

	// get connection object
	Connection * getConnection() const throw() { return m_pConnection; }

	// set connection object
	void setConnection(Connection * pConnection) throw() { m_pConnection = pConnection; }

	// get warning/error string
	string getError() const throw() 
	{ 
		return(m_pConnection == NULL) ?("Not Associated with Connection Object") :(m_pConnection->getError()); 
	}

	// get affected rows
	uint getAffectedRowCount() const throw() { return m_nAffectedRows; }

	
private:
	
	// Connection
	Connection * m_pConnection;

	// SQL Statement�
	string m_Statement;

	// Query Result 
	Result * m_pResult;

	// insert, update, delete 했을 때 영향을 받은 row 의 개수
	uint m_nAffectedRows;

};

#endif // __STATEMENT_H__
