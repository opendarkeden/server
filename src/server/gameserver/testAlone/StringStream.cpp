//////////////////////////////////////////////////////////////////////
//
// Filename    : StringStream.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "StringStream.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
StringStream::StringStream () 
	throw ()
: m_Size(0), m_bInserted(false), m_Buffer("")
{
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
StringStream::~StringStream () 
    throw ()
{
}

	
//////////////////////////////////////////////////////////////////////
// add string to stream
//////////////////////////////////////////////////////////////////////
StringStream & StringStream::operator << ( bool T ) 
	throw ()
{
	string buf( T == true ? "true" : "false" );

	m_Strings.push_back( buf );

	m_Size += buf.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( char T ) 
	throw ()
{
	string buf(2,'\0');
	buf[0] = T;

	m_Strings.push_back( buf );

	m_Size += buf.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( uchar T )
	throw ()
{
	string buf(2,0);
	buf[0] = T;

	m_Strings.push_back( buf );

	m_Size += buf.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( short T )
	throw ()
{
	char buf[7];
	sprintf( buf , "%d" , T );

	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( ushort T )
	throw ()
{
	char buf[7];
	sprintf( buf , "%u" , T );

	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( int T )
	throw ()
{
	char buf[12];
	sprintf( buf , "%d" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( uint T )
	throw ()
{	
	char buf[12];
	sprintf( buf , "%u" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( long T )
	throw ()
{
	char buf[12];
	sprintf( buf , "%ld" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( ulong T )
	throw ()
{	
	char buf[12];
	sprintf( buf , "%lu" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( float T )
	throw ()
{
	char buf[12];
	sprintf( buf , "%f" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( double T )
	throw ()
{
	char buf[22];
	sprintf( buf , "%f" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( const char * buf )
	throw ()
{
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( const string & str )
	throw ()
{
	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}


//////////////////////////////////////////////////////////////////////
// make string
//////////////////////////////////////////////////////////////////////
const string & StringStream::toString () const
	throw ()
{
	// 일단 스트링을 한번 생성해놓으면, 
	// 그다음 호출때에는 새로 추가되지 않는 한 그대로 사용한다.
	if ( m_bInserted ) {
		
		m_bInserted = false;

		// 속도를 위해 쓸데없는 복사 방지를 일단 메모리를 다 잡아놓고 시작한다.
		m_Buffer.reserve( m_Size );

		for ( list<string>::const_iterator itr = m_Strings.begin () ;
			  itr != m_Strings.end() ;
			  itr ++ ) {
			// 버퍼에 하나씩 추가한다.
			m_Buffer.append( *itr );
		}
	}

	return m_Buffer;
}
