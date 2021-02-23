////////////////////////////////////////////////////////////////////////////////
// Filename    : VariableBuffer.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "VariableBuffer.h"
#include "VariableInfo.h"
#include "Utility.h"			// trim(), getline()


////////////////////////////////////////////////////////////////////////////////
// static constant variables
////////////////////////////////////////////////////////////////////////////////
const char VariableBuffer::Comment = '#';
const char VariableBuffer::Separator = ',';
const char VariableBuffer::EOL = '\n';
const char * VariableBuffer::WhiteSpaces = " \t\n";
const char * VariableBuffer::SpaceTab = " \t";

	
////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
VariableBuffer::VariableBuffer (const string & buffer) 
	throw ()
{
	m_Buffer = buffer;

	parse();
}

////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
VariableBuffer::~VariableBuffer () 
	throw ()
{
	clear();
}

void VariableBuffer::clear()
{
	vector<VariableInfo*>::iterator itr = m_VariableInfos.begin();

	for ( ; itr != m_VariableInfos.end(); itr++ )
	{
		SAFE_DELETE( *itr );
	}

	m_VariableInfos.clear();
}

void VariableBuffer::parse()
	throw (Error)
{
	__BEGIN_TRY

	string subStr = trim( m_Buffer );
	if ( subStr.size() == 0 )
		return;

	bool bEnd = false;

	int index = 0;
	uint i = 0;

	do
	{
		uint j = subStr.find_first_of( Separator, i );

		// separator 가 없다면 마지막 Variable 이다.
		if ( j == string::npos )
		{
			j = subStr.size();
			bEnd = true;
		}

		string variable = trim(subStr.substr( i, j - i ));

		VariableInfo* pVariableInfo = new VariableInfo( variable ); 
		
		m_VariableInfos.push_back( pVariableInfo );

		index++;
		i = j + 1;
	}
	while ( !bEnd );

	__END_CATCH
}

VariableInfo* VariableBuffer::getVariableInfo( int index )
	throw( OutOfBoundException, Error )
{
	__BEGIN_TRY

	if ( index < 0 || index >= (int)m_VariableInfos.size() )
		throw OutOfBoundException("VariableBuffer::getVariableInfo() OOB!!");

	return m_VariableInfos[index];

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string VariableBuffer::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "VariableBuffer(";

	vector<VariableInfo*>::const_iterator itr = m_VariableInfos.begin();

	for ( ; itr != m_VariableInfos.end(); itr++ )
	{
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();	

	__END_CATCH
}
