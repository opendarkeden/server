#ifndef __REGEN_ZONE_MANAGER_H__
#define __REGEN_ZONE_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "MonsterCorpse.h"
#include "Mutex.h"

#include <map>

class PlayerCreature;
class GCRegenZoneStatus;

class RegenZoneInfo
{
public:
	enum RegenZoneIndex
	{
		REGEN_ZONE_SLAYER,
		REGEN_ZONE_VAMPIRE,
		REGEN_ZONE_OUSTERS,
		REGEN_ZONE_DEFAULT
	};

	RegenZoneInfo( uint ID, MonsterCorpse* pTower, uint Owner ) : m_ID(ID), m_pRegenZoneTower(pTower) { Assert( Owner < 4 ); m_Owner = (RegenZoneIndex)Owner; }
	uint getID() const { return m_ID; }
	MonsterCorpse* getTower() const { return m_pRegenZoneTower; }

	RegenZoneIndex getOwner() const { return m_Owner; }
	void setOwner( RegenZoneIndex owner ) { m_Owner = owner; }

	RegenZoneIndex getOriginalOwner() const { return m_OriginalOwner; }
	void setOriginalOwner( RegenZoneIndex owner ) { m_OriginalOwner = owner; }

	void putTryingPosition() throw(Error);
	void deleteTryingPosition() throw(Error);

private:
	uint			m_ID;
	MonsterCorpse*	m_pRegenZoneTower;
	RegenZoneIndex	m_Owner;
	RegenZoneIndex	m_OriginalOwner;
};

class RegenZoneManager
{
	map<uint, RegenZoneInfo*>	m_RegenZoneInfos;
	Mutex						m_Mutex;
	GCRegenZoneStatus*			m_pStatusPacket;
	RegenZoneManager();
public:
	~RegenZoneManager();

	void load() throw(Error);
	void reload() throw(Error);

	void lock() { m_Mutex.lock(); }
	void unlock() { m_Mutex.unlock(); }

	void putTryingPosition() throw(Error);
	void deleteTryingPosition() throw(Error);

	void changeRegenZoneOwner( MonsterCorpse* pTower, Race_t race );

	bool canTryRegenZone( PlayerCreature* pPC, MonsterCorpse* pTower );
	bool canRegen( PlayerCreature* pPC, uint ID );

	void regeneratePC( PlayerCreature* pPC, uint ID );

	void broadcastStatus();
	GCRegenZoneStatus* getStatusPacket() const { return m_pStatusPacket; }

	static RegenZoneManager* getInstance() { static RegenZoneManager theInstance; return &theInstance; }
};

#endif// __REGEN_ZONE_MANAGER_H__
