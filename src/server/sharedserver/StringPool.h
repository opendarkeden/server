////////////////////////////////////////////////////////////////////
// Filename : StringPool.h
// Desc     : ���������� ���Ǵ� string ���� pool
////////////////////////////////////////////////////////////////////

#ifndef __STRING_POOL_H__
#define __STRING_POOL_H__

#include "Exception.h"

#include <string>
#include <unordered_map>

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
	typedef unordered_map<uint, string>		StringHashMap;
	typedef StringHashMap::iterator			StringHashMapItor;
	typedef StringHashMap::const_iterator	StringHashMapConstItor;

public:
	StringPool() noexcept(false);
	~StringPool() noexcept;

public:
	void clear() noexcept(false);
	void load() noexcept(false);

	void addString( uint strID, string sString ) noexcept(false);
	
	string getString( uint strID ) noexcept(false);

	const char* c_str( uint strID ) noexcept(false);

private:
	StringHashMap	m_Strings;
};

extern StringPool* g_pStringPool;

#endif // __STRING_POOL_H__
