//////////////////////////////////////////////////////////////////////
//
// File Name 	: Statement.h
// Written by	: Gday29@ewestsoft.com
// Description	: SQL ���� �����..
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
// SQL���� ����� ��� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class Statement {
public:
    // constructor
    Statement();

    // constructor
    Statement(const char* fmt, ...);

    // destructor
    ~Statement();

public:
    // ������ ������ SQL ���� ������ �����Ѵ�.
    Result* executeQuery();

    // SQL ���� �޾Ƽ� �����Ѵ�.
    Result* executeQuery(const char*, ...);
    Result* executeQueryString(const string& sqlStatement);

    // get SQL statement
    string getStatement() const {
        return m_Statement;
    }

    // SQL ���� �����Ѵ�.
    void setStatement(const char* fmt, ...);

    // get connection object
    Connection* getConnection() const {
        return m_pConnection;
    }

    // set connection object
    void setConnection(Connection* pConnection) {
        m_pConnection = pConnection;
    }

    // get warning/error string
    string getError() const {
        return (m_pConnection == NULL) ? ("Not Associated with Connection Object") : (m_pConnection->getError());
    }

    // get affected rows
    uint getAffectedRowCount() const {
        return m_nAffectedRows;
    }

    // get insert id
    uint getInsertID() const;


private:
    // Connection
    Connection* m_pConnection;

    // SQL Statement�
    string m_Statement;

    // Query Result
    Result* m_pResult;

    // insert, update, delete ���� �� ������ ���� row �� ����
    uint m_nAffectedRows;
};

#endif // __STATEMENT_H__
