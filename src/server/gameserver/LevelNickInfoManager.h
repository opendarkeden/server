#ifndef __LEVEL_NICK_INFO_H__
#define __LEVEL_NICK_INFO_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include <vector>

class Creature;

class LevelNickInfo
{
public:
	LevelNickInfo(Race_t race, Level_t lvl, DWORD idx) : m_Race(race), m_Level10(lvl), m_NickIndex(idx) { }

	bool	isFitRace(Creature* pCreature) const;
	DWORD	getNickIndex() const { return m_NickIndex; }

private:
	Race_t	m_Race;
	Level_t	m_Level10;
	DWORD	m_NickIndex;
};

class LevelNickInfoManager
{
public:
	LevelNickInfoManager() { m_LevelNickInfoMap.clear(); }
	~LevelNickInfoManager() { clear(); }

	void clear();
	void load();

	vector<LevelNickInfo*>& getLevelNickInfo( Level_t Level ) { return m_LevelNickInfoMap[Level/10]; }

	static LevelNickInfoManager& Instance() { static LevelNickInfoManager theInstance; return theInstance; }

private:
	hash_map<Level_t, vector<LevelNickInfo*> > m_LevelNickInfoMap;
};

#endif
