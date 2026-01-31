//////////////////////////////////////////////////////////////////////
//
// File Name 	: Statement.h
// Written by	: Gday29@ewestsoft.com
// Description	: SQL ¹®À» ¸¸µç´Ù..
//
//////////////////////////////////////////////////////////////////////

#ifndef __STATEMENT_H__
#define __STATEMENT_H__

// include files
#include "Connection.h"
#include "Exception.h"
#include "Types.h"

// forward declaration
class Result;

//////////////////////////////////////////////////////////////////////
//
// class Statement;
//
// SQL¹®À» ¸¸µé¾î µðºñ¿¡ Äõ¸®ÇÑ´Ù.
//
//////////////////////////////////////////////////////////////////////

class Statement {
public:
    // constructor
    Statement() throw();

    // constructor
    Statement(char* fmt, ...) throw(Error);

    // destructor
    ~Statement() throw();

public:
    // »çÀü¿¡ ÁöÁ¤µÈ SQL ¹®À» °¡Áö°í Äõ¸®ÇÑ´Ù.
    Result* executeQuery() throw(SQLQueryException, Error);

    // SQL ¹®À» ¹Þ¾Æ¼­ Äõ¸®ÇÑ´Ù.
    Result* executeQuery(char*, ...) throw(SQLQueryException, Error);
    Result* executeQuery(const string& sqlStatement) throw(SQLQueryException, Error);

    // get SQL statement
    string getStatement() const throw() {
        return m_Statement;
    }

    // SQL ¹®À» ÁöÁ¤ÇÑ´Ù.
    void setStatement(char* fmt, ...) throw(Error);

    // get connection object
    Connection* getConnection() const throw() {
        return m_pConnection;
    }

    // set connection object
    void setConnection(Connection* pConnection) throw() {
        m_pConnection = pConnection;
    }

    // get warning/error string
    string getError() const throw() {
        return (m_pConnection == NULL) ? ("Not Associated with Connection Object") : (m_pConnection->getError());
    }

    // get affected rows
    uint getAffectedRowCount() const throw() {
        return m_nAffectedRows;
    }


private:
    // Connection
    Connection* m_pConnection;

    // SQL Statement¹
    string m_Statement;

    // Query Result
    Result* m_pResult;

    // insert, update, delete ÇßÀ» ¶§ ¿µÇâÀ» ¹ÞÀº row ÀÇ °³¼ö
    uint m_nAffectedRows;
};

#endif // __STATEMENT_H__
