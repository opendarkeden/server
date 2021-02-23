////////////////////////////////////////////////////////////////////////////////
// Filename    : VariableInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VARIABLE_INFO_H__
#define __VARIABLE_INFO_H__

#include "Types.h"
#include "Exception.h"

#include <vector>

class VariableInfo
{
public:
	static const char Seperator;
	static const char LParen;
	static const char RParen;
	static const char ParamSeperator;

public:
	VariableInfo( const string& buffer );
	~VariableInfo();

	const string& getName() const { return m_Name; }
	const string& getKeyword() const { return m_Keyword; }

	const string& getParameter( int index ) const throw(OutOfBoundException, Error);

	string toString() const throw();

private:
	void 	parse() throw (Error);

private:
	string 			m_Name;
	string 			m_Keyword;
	vector<string> 	m_Parameters;

	string			m_Buffer;
};

#endif
