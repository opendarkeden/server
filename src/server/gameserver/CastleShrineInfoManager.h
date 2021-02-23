#ifndef __CASTLE_SHRINE_INFO_MANAGER_H__
#define __CASTLE_SHRINE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "ShrineInfoManager.h"
#include <hash_map>

class PlayerCreature;
class ZoneItemPosition;
class Zone;
class Item;
class CastleSymbol;
class MonsterCorpse;

class CastleShrineSet
{
public: 
	CastleShrineSet() {}
	~CastleShrineSet() {}

	ItemID_t getCastleSymbolItemID() const			{ return m_ItemID; }
	void	 setCastleSymbolItemID(ItemID_t itemID) 	{ m_ItemID = itemID; }

	string toString() const throw();

public :
	ShrineID_t		m_ShrineID;				// Shrine ID. ItemType과 같아야 한다.
	ShrineInfo		m_GuardShrine;			// 성 안에 있는 Shrine
	ShrineInfo		m_HolyShrine;			// 아담의 성지에 있는 Shrine
	ItemType_t		m_ItemType;				// 성서 조각 ItemType
	ItemID_t		m_ItemID;				// 성서 조각 ItemID
};


class CastleShrineInfoManager
{
public:
	typedef hash_map<ShrineID_t, CastleShrineSet*>	HashMapShrineSet;
	typedef HashMapShrineSet::iterator			HashMapShrineSetItor;
	typedef HashMapShrineSet::const_iterator	HashMapShrineSetConstItor;

public:
	CastleShrineInfoManager() {}
	~CastleShrineInfoManager();

public:
	void init() throw(Error);
	void load() throw(Error);
	void clear();

	void addAllShrineToZone() throw(Error);
	Item* addShrineToZone( ShrineInfo& shrineInfo, ItemType_t itemType = 0 ) throw(Error);

	void addShrineSet( CastleShrineSet* pShrineSet ) throw(Error);
	void deleteShrineSet( ShrineID_t shrineID ) throw(Error);
	CastleShrineSet* getShrineSet( ShrineID_t shrineID ) const throw(Error);
	int  size() const { return m_ShrineSets.size(); }

	string toString() const throw();

public:
	bool isMatchHolyShrine(Item* pItem, MonsterCorpse* pMonsterCorpse) const throw(Error);
	bool isDefenderOfGuardShrine( PlayerCreature* pPC, MonsterCorpse* pShrine ) const throw(Error);
	bool canPickupCastleSymbol( Race_t race, CastleSymbol* pCastleSymbol ) const throw (Error);
	bool getMatchGuardShrinePosition(Item* pItem, ZoneItemPosition& zip) const throw(Error);

	bool returnAllCastleSymbol( ZoneID_t castleZoneID ) const throw (Error);
	bool returnCastleSymbol( ShrineID_t shrineID, bool bLock = true ) const throw (Error);
	bool returnCastleSymbol( Zone* pZone, CastleSymbol* pCastleSymbol ) const throw (Error);

	ZoneID_t getGuardShrineZoneID( ZoneID_t castleZoneID ) const throw(Error);

	bool removeShrineShield( Zone* pZone ) throw(Error);
	bool addShrineShield( Zone* pZone ) throw(Error);
	bool addShrineShield_LOCKED( Zone* pZone ) throw(Error);

	bool putCastleSymbol(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pCorpse) const throw (Error);

private:
	HashMapShrineSet		m_ShrineSets;
};

extern CastleShrineInfoManager* g_pCastleShrineInfoManager;

#endif // __SHRINE_INFO_MANAGER_H__
