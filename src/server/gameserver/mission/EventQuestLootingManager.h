#ifndef __EVENT_QUEST_LOOTING_MANAGER_H__
#define __EVENT_QUEST_LOOTING_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"

#include <vector>
#include <map>

class Monster;
class Item;
class PlayerCreature;

class EventQuestLootingInfo
{
public:
	enum TYPE
	{
		LOOTING_ZONE,
		LOOTING_MONSTER,
		LOOTING_BOTH,
		LOOTING_NONE
	};

public:
	TYPE			m_Type;
	int				m_QuestLevel;
	ZoneID_t		m_LootingZoneID;
	MonsterType_t	m_LootingMonsterType;
	Item::ItemClass	m_LootingItemClass;
	ItemType_t		m_LootingItemTypeMin;
	ItemType_t		m_LootingItemTypeMax;

	Race_t			m_Race;
	QuestGrade_t	m_MinGrade;
	QuestGrade_t	m_MaxGrade;

public:
	bool			isTargetMonster( PlayerCreature* pPC, Monster* pMonster ) const;
	Item*			getLootingItem() throw(Error);

	string			toString() const;
};

class EventQuestLootingManager
{
public:
	EventQuestLootingInfo* isTargetMonster( PlayerCreature* pPC, Monster* pMonster );
	bool			killed( PlayerCreature* pPC, Monster* pMonster ) throw(Error);

	void 			load() throw(Error);
private:
	map<ZoneID_t,vector<EventQuestLootingInfo*> >	m_ZoneLootingInfo;
	map<MonsterType_t,vector<EventQuestLootingInfo*> >	m_MonsterLootingInfo;
};

extern EventQuestLootingManager* g_pEventQuestLootingManager;

#endif// __EVENT_QUEST_LOOTING_MANAGER_H__
