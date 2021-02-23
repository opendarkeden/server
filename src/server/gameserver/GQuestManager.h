#ifndef __GQUEST_MANAGER_H__
#define __GQUEST_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "GQuestInventory.h"

#include <hash_map>

class Packet;
class PlayerCreature;
class GQuestStatus;
class GQuestMission;
class Item;
class NPC;
class PetInfo;
class SkillSlot;
class MonsterCorpse;
class Monster;

class XMLTree;

class GQuestManager
{
public:
	enum EventTypes
	{
		TIMER,
		BLOODDRAIN,
		LEVELUP,
		ITEM,
		MEETNPC,
		TAMEPET,
		KILLED,
		SKILL_LEVELUP,
		RIDE_MOTORCYCLE,
		TOUCH_WAY_POINT,
		KILLMONSTER,
		PARTY_DISSECT,
		EVENT_PARTY,
		EVENT_PARTY_CRASH,
		FASTMOVE,
		ILLEGAL_WARP,
		TRAVEL,
		ADVANCEMENT_LEVELUP,
		CLEAR_DYNAMIC_ZONE,
		ENTER_DYNAMIC_ZONE,
		MAX
	};

	GQuestManager(PlayerCreature* pOwner) : m_pOwner(pOwner), m_bPartyQuest(false) { }
	void load() throw(Error);
	void init() throw(Error);
	void refreshQuest(bool sendPacket=true);

	Packet*	getStatusInfoPacket() const;

	void accept(DWORD qID);
	void cancel(DWORD qID);

	void heartbeat();
	void blooddrain();
	void levelUp();
	void getItem(Item* pItem);
	bool metNPC(NPC* pNPC);
	void tamePet(PetInfo* pPetInfo);
	void killed();
	void skillLevelUp(SkillSlot* pSkillSlot);
	void rideMotorcycle(bool isParty=false);
	void touchWayPoint(MonsterCorpse* waypoint);
	void killedMonster(Monster* pMonster);
	void partyDissect(MonsterCorpse* pCorpse);
	void eventParty();
	void eventPartyCrash();
	void fastMove(bool isParty = false);
	void illegalWarp(bool isParty = false);
	void partyTravel(MonsterCorpse* pCorpse);
	void advancementClassLevelUp();
	void clearDynamicZone(ZoneID_t zoneID);
	void enterDynamicZone(ZoneID_t zoneID);

	list<GQuestMission*>&	getEventMission(EventTypes type) { return m_EventMissions[type]; }
	const list<GQuestMission*>&	getEventMission(EventTypes type) const { return m_EventMissions[type]; }

	GQuestInventory&		getGQuestInventory() { return m_GQuestInventory; }
	const GQuestInventory&	getGQuestInventory() const { return m_GQuestInventory; }

	GQuestStatus*			getGQuestStatus(DWORD qID);
	void					eraseQuest(DWORD qID);

	bool					canEnterDynamicZone( ZoneID_t zoneID ) { return m_DynamicZoneInfo[zoneID] != 0; }
	void					setEnterDynamicZone( ZoneID_t zoneID, BYTE enter ) { m_DynamicZoneInfo[zoneID] = enter; }

private:
	PlayerCreature* m_pOwner;
	hash_map<DWORD, GQuestStatus*>	m_QuestStatuses;

	list<GQuestMission*>	m_EventMissions[MAX];
	GQuestInventory			m_GQuestInventory;

	bool					m_bPartyQuest;

	hash_map<ZoneID_t, BYTE>	m_DynamicZoneInfo;
};

#endif
