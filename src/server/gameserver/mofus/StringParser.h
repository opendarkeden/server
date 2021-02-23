//////////////////////////////////////////////////////////////////////
//	
//	created		:	2004/04/08
//	filename	:	CommandStringParser.h
//	author		:	bezz
//	
//	purpose		:	StringParser Å¬·¡½º
//	
//////////////////////////////////////////////////////////////////////

// include files
#include <string>
#include <hash_map>

// forward declaration;

//////////////////////////////////////////////
// tringParser class
//////////////////////////////////////////////

class StringParser
{
public:
	// type define
	typedef hash_map< int, string >				HashMapString;
	typedef HashMapString::iterator				HashMapStringItr;
	typedef HashMapString::const_iterator		HashMapStringConstItr;

public:
	// constructor & destructor
	StringParser();
	StringParser( const string& str );
	StringParser( const StringParser& stringParser );
	virtual ~StringParser();

protected:
	// parsing;
	void parsing();
	
	// clear hash map
	void clear();

public:
	// get part of string
	const string& getPart( int index );
	int getPartInt( int index );

	// size
	int size() const { return (int)(m_Parts.size()); }

	// debug string
	string toString() const;

private:
	// original string
	string			m_String;

	// parts of string
	HashMapString	m_Parts;
};

