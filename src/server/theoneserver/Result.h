//////////////////////////////////////////////////////////////////////////////
// File Name	: Result.h
// Written By	: Gday29@ewestsoft.com
// Description	: Definition of Result Class
//////////////////////////////////////////////////////////////////////////////

#ifndef __RESULT_H__
#define __RESULT_H__

#include "Types.h"
#include "Exception.h"
#include <sys/time.h>
#include <mysql/mysql.h>

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Connection;
class Statement;

#define T_RESULT MYSQL_RES

//////////////////////////////////////////////////////////////////////////////
// class Result;
// Result 는 삭제할 필요가 없다. 사용자는 Statement 만 삭제하면 된다.
//////////////////////////////////////////////////////////////////////////////

class Result 
{
public:
	Result(T_RESULT *, const string& statement) throw(Error);
	~Result() throw();

public:
	// 다음 row로 넘어간다.
	bool next() throw(Error);
	
	// 특정 필드(컬럼) 값을 가지고 온다.
	char * getField(uint index) throw(OutOfBoundException, Error);
	char getChar(uint index) throw(OutOfBoundException, Error) { return(getField(index))[0]; }
	int getInt(uint index) throw(OutOfBoundException, Error) { return atoi(getField(index)); }
	uint getUInt(uint index) throw(OutOfBoundException, Error) { return(uint)atoi(getField(index)); }
	BYTE getBYTE(uint index) throw(OutOfBoundException, Error) { return(BYTE)atoi(getField(index)); }
	WORD getWORD(uint index) throw(OutOfBoundException, Error) { return(WORD)atoi(getField(index)); }
	DWORD getDWORD(uint index) throw(OutOfBoundException, Error) { return strtoul(getField(index), (char**)NULL, 10); }
	const char* getString(uint index) throw(OutOfBoundException, Error);

	// 쿼리 결과값이 포함하는 row/column의 숫자를 리턴한다.
	uint getRowCount() const throw() { return m_RowCount; }
	uint getFieldCount() const throw() { return m_FieldCount; }

	string getStatement(void) const { return m_Statement; }

private:
	T_RESULT*  m_pResult;    // 결과값을 나타내는 MYSQL structure
	MYSQL_ROW  m_pRow;       // 현재 처리하고 있는 row
	uint       m_RowCount;   // 쿼리 결과로 얻어낸 row의 숫자
	uint       m_FieldCount;
	string     m_Statement;  // 어떤 query문에 의한 결과인가...?
};

#endif // __RESULT_H__
