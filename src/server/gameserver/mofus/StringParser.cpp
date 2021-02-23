//////////////////////////////////////////////////////////////////////
//	
//	created		:	2004/04/08
//	filename	:	StringParser.cpp
//	author		:	bezz
//	
//	purpose		:	StringParser Å¬·¡½º
//	
//////////////////////////////////////////////////////////////////////

// include files
#include "StringParser.h"
#include <stdlib.h>
#include "Assert.h"

// constructor
StringParser::StringParser()
{
}

StringParser::StringParser( const string& str )
	: m_String( str )
{
	parsing();
}

StringParser::StringParser( const StringParser& stringParser )
: m_String( stringParser.m_String ), m_Parts( stringParser.m_Parts )
{
}

// destructor
StringParser::~StringParser()
{
	clear();
}

void StringParser::parsing()
{
	unsigned int i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t len = m_String.length();

	static const char* WhiteSpaces = "-";

	if ( len == 0 )
		return;

	do
	{
		j = m_String.find_first_not_of( WhiteSpaces, j );
		if ( j == string::npos )
			break;
		k = m_String.find_first_of( WhiteSpaces, j + 1 );

		string part( m_String.substr( j, k-j ) );

		m_Parts[ i++ ] = part;

		j = k + 1;
	}
	while ( k != string::npos );
}

void StringParser::clear()
{
	m_Parts.clear();
}

const string& StringParser::getPart( int index )
{
	HashMapStringItr itr = m_Parts.find( index );

	if ( itr == m_Parts.end() )
	{
		Assert( false );
	}

	return itr->second;
}

int StringParser::getPartInt( int index )
{
	return atoi( getPart( index ).c_str() );
}

string StringParser::toString() const
{
	StringStream msg;

	HashMapStringConstItr itr = m_Parts.begin();
	HashMapStringConstItr endItr = m_Parts.end();

	msg << "StringParser(";
	for ( ; itr != endItr; ++itr )
	{
		msg << "[" << itr->first << "]:" << itr->second;
	}
	msg << ")";

	return msg.toString();
}

