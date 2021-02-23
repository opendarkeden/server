////////////////////////////////////////////////////////////////////
// Filename : StringPool.h
// Desc     : 서버내에서 사용되는 string 들의 pool
////////////////////////////////////////////////////////////////////

#ifndef __STRING_POOL_H__
#define __STRING_POOL_H__

#include "Exception.h"

#include <string>
#include <hash_map>

enum StringID
{
	STRID_TEAM_REGISTRATION_ACCEPT,					// 0
	STRID_TEAM_REGISTRATION_ACCEPT_2,				// 1
	STRID_CLAN_REGISTRATION_ACCEPT,					// 2
	STRID_CLAN_REGISTRATION_ACCEPT_2,				// 3
	STRID_TEAM_JOIN_ACCEPT,							// 4
	STRID_CLAN_JOIN_ACCEPT,							// 5
	STRID_TEAM_BROKEN,								// 6
	STRID_CLAN_BROKEN,								// 7
	STRID_TEAM_CANCEL,								// 8
	STRID_CLAN_CANCEL,								// 9

	STRID_MAX
};

class StringPool
{
public:
	typedef hash_map<uint, string>		StringHashMap;
	typedef StringHashMap::iterator			StringHashMapItor;
	typedef StringHashMap::const_iterator	StringHashMapConstItor;

public:
	StringPool() throw(Error);
	~StringPool() throw(Error);

public:
	void clear() throw(Error);
	void load() throw(Error);

	void addString( uint strID, string sString ) throw( DuplicatedException, Error );
	
	string getString( uint strID ) throw( NoSuchElementException, Error );

	const char* c_str( uint strID ) throw( NoSuchElementException, Error );

private:
	StringHashMap	m_Strings;
};

extern StringPool* g_pStringPool;

#endif // __STRING_POOL_H__
