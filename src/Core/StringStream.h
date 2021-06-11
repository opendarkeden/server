//////////////////////////////////////////////////////////////////////
//
// Filename    : StringStream.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __STRING_STREAM_H__
#define __STRING_STREAM_H__

// include files
#include "Types.h"
#include <list>
#include <string>

// end of stream
const char eos = '\n';

class StringStream {
	
public :
	
	// constructor
	StringStream () ;
	
	// destructor
	~StringStream () ;
	
	
public :
	
	// add string to stream
	StringStream & operator << (bool T) ;
	StringStream & operator << (char T) ;
	StringStream & operator << (uchar T) ;
	StringStream & operator << (short T) ;
	StringStream & operator << (ushort T) ;
	StringStream & operator << (int T) ;
	StringStream & operator << (uint T) ;
	StringStream & operator << (long T) ;
	StringStream & operator << (ulong T) ;
	StringStream & operator << (float T) ;
	StringStream & operator << (double T) ;
	StringStream & operator << (const char* str) ;
	StringStream & operator << (const string & str) ;

	// make string
	const string& toString () const ;
	
	// true if stream is empty
	bool isEmpty () const  { return m_Size == 0; }

private :
	
	// list of string
	list<string> m_Strings;

	// size of string which will be generated
	ushort m_Size;
	
	// inserted flag 
	mutable bool m_bInserted;
	
	// buffer for string will be generated
	mutable string m_Buffer;

};

#endif
