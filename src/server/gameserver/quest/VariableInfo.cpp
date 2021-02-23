////////////////////////////////////////////////////////////////////////////////
// Filename    : VariableInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "VariableInfo.h"
#include "Utility.h"

////////////////////////////////////////////////////////////////////////////////
// static constant variables
////////////////////////////////////////////////////////////////////////////////
const char VariableInfo::Seperator = ':';
const char VariableInfo::LParen = '(';
const char VariableInfo::RParen = ')';
const char VariableInfo::ParamSeperator = '|';


VariableInfo::VariableInfo( const string& buffer )
{
	m_Buffer = buffer;

	parse();
}

VariableInfo::~VariableInfo()
{
}

/////////////////////////////////////////////////////////
//
//             i             j      k
// 0123456789012345678901234567890123
// EntranceFee : EntranceFee ( 1003 )
//
/////////////////////////////////////////////////////////
void VariableInfo::parse()
	throw (Error)
{
	__BEGIN_TRY

	uint i = m_Buffer.find( Seperator );
	uint j = m_Buffer.find( LParen );
	uint k = m_Buffer.find( RParen );

	if ( i == string::npos
		|| j == string::npos
		|| k == string::npos
		|| i > j
		|| j > k
	)
	{
		throw Error("Invalid VariableInfo String");
	}

	m_Name = trim( m_Buffer.substr( 0, i ) );
	m_Keyword = trim( m_Buffer.substr( i+1, j-i-1 ) );

	string parameters = trim( m_Buffer.substr( j+1, k-j-1 ) );

	if ( parameters.size() == 0 )
		return;

	bool bEnd = false;

	int index = 0;
	i = 0;

	do 
	{
		j = parameters.find_first_of( ParamSeperator, i );

		// seperator 가 없다면 마지막 값이다.
		if ( j == string::npos )
		{
			j = parameters.size();
			bEnd = true;
		}

		string parameter = parameters.substr( i, j-i );
		//m_Parameters.push_back( trim( parameters.substr( i, j-i ) ) );
		m_Parameters.push_back( trim( parameter) );

		index ++;
		i = j + 1;
	}
	while ( !bEnd );
	
	__END_CATCH
}

const string& VariableInfo::getParameter( int index ) const
	throw(OutOfBoundException, Error)
{
	__BEGIN_TRY

	if ( index < 0 || index >= (int)m_Parameters.size() )
		throw OutOfBoundException("VariableInfo::getParameter() OOB!!");

	return m_Parameters[index];

	__END_CATCH
}

string VariableInfo::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "VariableInfo("
		<< "Name:" << m_Name
		<< ",Keyword:" << m_Keyword
		<< ",Parameter(";

	vector<string>::const_iterator itr = m_Parameters.begin();

	for ( ; itr != m_Parameters.end(); itr++ )
	{
		msg << (*itr) << ",";
	}

	msg << "))";

	return msg.toString();

	__END_CATCH
}
