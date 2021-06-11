//////////////////////////////////////////////////////////////////////////////
// File Name 	: Result.cc
// Written By	: Gday29@ewestsoft.com
// Description	: Result class 구현
//////////////////////////////////////////////////////////////////////////////

#include "Result.h"
#include "Assert.h"
#include "StringStream.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

Result::Result (T_RESULT * pResult, const string& statement) 
	throw (Error) 
{
	__BEGIN_TRY

	m_pResult = pResult;
	m_pRow = NULL;

	Assert(m_pResult != NULL);

	// #rows 값을 지정한다.
	m_RowCount   = mysql_num_rows(m_pResult);
	m_FieldCount = mysql_num_fields(m_pResult);

	m_Statement = statement;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

Result::~Result () 
	throw ()
{
	__BEGIN_TRY

    if (m_pResult != NULL) 
	{
		// If the result set is empty, don't call mysql_free_result
		// otherwise when you call malloc later you might run into
		// some nasty debugging issues. 
		// [Note: man malloc has some interesting information to track
		// the problem like system varibles such as MALLOC_CHCK_]
		/*
		if (m_RowCount > 0)
		{
			mysql_free_result(m_pResult);
			m_pResult = NULL;
		}
		*/

		mysql_free_result(m_pResult);
		m_pResult = NULL;
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// next()	
// 다음 row 가 존재할 경우 true 를, 없을 경우 false 를 리턴한다.
//////////////////////////////////////////////////////////////////////////////

bool Result::next () 
	throw (Error)
{
	__BEGIN_TRY
		
	Assert(m_pResult != NULL);

	return (m_pRow = mysql_fetch_row(m_pResult)) != NULL;
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// getField
// 파라미터로 인덱스를 지정해서 그 컬럼을 리턴한다.
// 1 이 최초의 컬럼이 된다. (0 이 아니당..)
//////////////////////////////////////////////////////////////////////////////

char * Result::getField (uint index) 
	throw (OutOfBoundException , Error)
{
	__BEGIN_TRY
		
	if (m_pRow == NULL)
	{
		StringStream msg;
		msg << "Result::getField() : CALL Result::next() - Statement[" << m_Statement << "]";
		filelog("ResultBug.log", "%s", msg.toString().c_str());
		throw Error(msg.toString());
	}

	if (index == 0 || index > m_FieldCount)
	{
		StringStream msg;
		msg << "Result::getField() : Out of Bound! - Statement[" << m_Statement << "]";
		filelog("ResultBug.log", "%s", msg.toString().c_str());
		throw OutOfBoundException(msg.toString());
	}
	
	return m_pRow[ index - 1 ];
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

const char* Result::getString(uint index)
	throw (OutOfBoundException, Error)
{
	__BEGIN_TRY

	static const char* pNULL = "";
	const char* pField = getField(index);

	if (pField==NULL)
	{
		return pNULL;
	}

	return pField;

	//if (getField(index) == NULL) return "";
	//return getField(index);

	__END_CATCH
}
