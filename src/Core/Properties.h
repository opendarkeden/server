//////////////////////////////////////////////////////////////////////
//
// Filename    : Properties.h
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <map>

// help class
class StringCompare {
public :
	bool operator () (const string & left, const string & right) const
	{
		return left.compare(right) < 0;
	}
};

//////////////////////////////////////////////////////////////////////
//
// class Properties;
//
// 파일로부터 (key,value) pair 를 읽어서 map 의 형태로 가지고 있는다.
// 주로 환경이나 옵션등을 담은 파일에 사용한다. 객체를 생성해서 각종
// 옵션을 설정하고 저장하면 새 파일이 만들어진다. 
//
// *Usage*
//
// Properties prop;
// prop.load("gameserver.conf");
// cout << prop.getProperty("MODE") << endl;
// cout << prop.getProperty("NumOfPlayerThreads") << endl;
// prop.setProperty("MODE","MODE_IV");
// prop.save();
//
// Properties prop2("loginserver.conf");
// prop2.load();
// prop2.save("loginserver.new");
//
//////////////////////////////////////////////////////////////////////

class Properties {
	
public :
	
	static const char Comment;
	static const char Separator;
	static const char* WhiteSpaces;
	
public :
	
	// constructor
	Properties () throw ();
	Properties (const string & filename) throw ();
	
	// destructor
	~Properties () throw ();
	

public :
	
	// load from file
	void load () throw (IOException, Error);
	void load (const string & filename) throw (IOException, Error) { m_Filename = filename; load(); }

	// save to file
	void save () throw (IOException);
	void save (const string & filename) throw (IOException) { m_Filename = filename; save(); }

	// get/set property
	string getProperty (string key) const throw (NoSuchElementException);
	int getPropertyInt (string key) const throw (NoSuchElementException);
	void setProperty (string key, string value) throw ();

	bool hasKey(const string& key) const { return m_Properties.find(key) != m_Properties.end(); }

	// get debug string
	string toString () const throw ();
	
private :
	
	// key 가 string 이고, value 역시 string 인 map 이다.
	map< string, string, StringCompare > m_Properties;

	// load/save target file's name
	string m_Filename;
	
};

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
extern Properties* g_pConfig;
extern Properties* g_pTestConfig;	// by sigi. 2002.12.26

#endif
