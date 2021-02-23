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
	MonsterType_t	m_LootingMonsterID;
	Item::ItemClass	m_LootingItemClass;
	ItemType_t		m_LootingItemTypeMin;
	ItemType_t		m_LootingItemTypeMax;

	Race_t			m_Race;
	QuestGrade_t	m_MinGrade;
	QuestGrade_t	m_MaxGrade;

public:
	bool			isTargetMonster( PlayerCreautre* pPC, Monster* pMonster ) const;
	Item*			getLootingItem() const throw(Error);
};

class EventQuestLootingManager
{
public:
	bool			isTargetMonster( PlayerCreature* pPC, Monster* pMonster ) const;
	bool			killed( PlayerCreature* pPC, Monster* pMonster ) const throw(Error);

	void 			load() throw(Error);
private:
	map<ZoneID_t,vector<EventQuestLootingInfo*> >	m_ZoneLootingInfo;
	map<MonsterType_t,vector<EventQuestLootingInfo*> >	m_MonsterLootingInfo;
};

#endif// __EVENT_QUEST_LOOTING_MANAGER_H__
