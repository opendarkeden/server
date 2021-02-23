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
	StringStream () throw ();
	
	// destructor
	~StringStream () throw ();
	
	
public :
	
	// add string to stream
	StringStream & operator << (bool T) throw ();
	StringStream & operator << (char T) throw ();
	StringStream & operator << (uchar T) throw ();
	StringStream & operator << (short T) throw ();
	StringStream & operator << (ushort T) throw ();
	StringStream & operator << (int T) throw ();
	StringStream & operator << (uint T) throw ();
	StringStream & operator << (long T) throw ();
	StringStream & operator << (ulong T) throw ();
	StringStream & operator << (float T) throw ();
	StringStream & operator << (double T) throw ();
	StringStream & operator << (const char* str) throw ();
	StringStream & operator << (const string & str) throw ();

	// make string
	const string& toString () const throw ();
	
	// true if stream is empty
	bool isEmpty () const throw () { return m_Size == 0; }

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
