//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTypeStringList.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTypeStringList.h"

CGTypeStringList::CGTypeStringList () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGTypeStringList::~CGTypeStringList () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGTypeStringList::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	clearString();

	BYTE num;
		
	iStream.read(m_StringType);
//	cout << "CGTypeStringList( StringType:" << (int)m_StringType << ", ";
	iStream.read(num);
//	cout << "Number of String:" << (int)num << ", ";

	for ( BYTE i=0; i<num; i++ )
	{
		string temp;
		BYTE szString;
		iStream.read(szString);

		if ( szString == 0 ) throw InvalidProtocolException("String 길이가 0입니다.");
		if ( szString > MAX_STRING_LENGTH ) throw InvalidProtocolException("String 길이가 너무 깁니다.");

		iStream.read(temp, szString);

//		cout << "String[" << (int)i << "]:" << temp.c_str() << ", ";

		addString( temp );
	}

	iStream.read( m_Param );
//	cout << "Parameter : " << m_Param << " )" << endl;

	__END_CATCH
}

void CGTypeStringList::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_StringType);

	BYTE szList = m_StringList.size();

	oStream.write( szList );

	list<string>::const_iterator itr = m_StringList.begin();

	for( ; itr != m_StringList.end() ; ++itr )
	{
		BYTE szString = (*itr).size();
		oStream.write( szString );
		oStream.write( *itr );
	}

	oStream.write( m_Param );

	__END_CATCH
}

void CGTypeStringList::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGTypeStringListHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTypeStringList::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGTypeStringList("
		<< ")";
	return msg.toString();

	__END_CATCH
}
