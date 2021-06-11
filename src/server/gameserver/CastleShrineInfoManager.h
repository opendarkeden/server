#ifndef __CASTLE_SHRINE_INFO_MANAGER_H__
#define __CASTLE_SHRINE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "ShrineInfoManager.h"
#include <unordered_map>

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

	string toString() const ;

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
	typedef unordered_map<ShrineID_t, CastleShrineSet*>	HashMapShrineSet;
	typedef HashMapShrineSet::iterator			HashMapShrineSetItor;
	typedef HashMapShrineSet::const_iterator	HashMapShrineSetConstItor;

public:
	CastleShrineInfoManager() {}
	~CastleShrineInfoManager();

public:
	void init() ;
	void load() ;
	void clear();

	void addAllShrineToZone() ;
	Item* addShrineToZone( ShrineInfo& shrineInfo, ItemType_t itemType = 0 ) ;

	void addShrineSet( CastleShrineSet* pShrineSet ) ;
	void deleteShrineSet( ShrineID_t shrineID ) ;
	CastleShrineSet* getShrineSet( ShrineID_t shrineID ) const ;
	int  size() const { return m_ShrineSets.size(); }

	string toString() const ;

public:
	bool isMatchHolyShrine(Item* pItem, MonsterCorpse* pMonsterCorpse) const ;
	bool isDefenderOfGuardShrine( PlayerCreature* pPC, MonsterCorpse* pShrine ) const ;
	bool canPickupCastleSymbol( Race_t race, CastleSymbol* pCastleSymbol ) const ;
	bool getMatchGuardShrinePosition(Item* pItem, ZoneItemPosition& zip) const ;

	bool returnAllCastleSymbol( ZoneID_t castleZoneID ) const ;
	bool returnCastleSymbol( ShrineID_t shrineID, bool bLock = true ) const ;
	bool returnCastleSymbol( Zone* pZone, CastleSymbol* pCastleSymbol ) const ;

	ZoneID_t getGuardShrineZoneID( ZoneID_t castleZoneID ) const ;

	bool removeShrineShield( Zone* pZone ) ;
	bool addShrineShield( Zone* pZone ) ;
	bool addShrineShield_LOCKED( Zone* pZone ) ;

	bool putCastleSymbol(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pCorpse) const ;

private:
	HashMapShrineSet		m_ShrineSets;
};

extern CastleShrineInfoManager* g_pCastleShrineInfoManager;

#endif // __SHRINE_INFO_MANAGER_H__
