#ifndef __SHRINE_INFO_MANAGER_H__
#define __SHRINE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Mutex.h"

class PlayerCreature;
class ZoneItemPosition;
class Zone;
class Item;
class BloodBible;
class MonsterCorpse;
class GCBloodBibleStatus;

class ShrineInfo
{
public:
	enum ShrineType
	{
		SHRINE_GUARD,		// 성에 있는 수호성단
		SHRINE_HOLY			// 성 밖에 있는 성지성단
	};

public:
	ShrineInfo() {}
	~ShrineInfo() {}

public:
	MonsterType_t 	getMonsterType() const 			{ return m_MonsterType; }
	void	 		setMonsterType(MonsterType_t mt){ m_MonsterType = mt; }

	ShrineType 		getShrineType() const 			{ return m_ShrineType; }
	void	 		setShrineType(ShrineType st) 	{ m_ShrineType = st; }

	ZoneID_t 		getZoneID() const 				{ return m_ZoneID; }
	void	 		setZoneID(const ZoneID_t zoneID) { m_ZoneID = zoneID; }

	ZoneCoord_t		getX() const					{ return m_X; }
	void	 		setX(ZoneCoord_t x) 			{ m_X = x; }
	ZoneCoord_t		getY() const					{ return m_Y; }
	void	 		setY(ZoneCoord_t y) 			{ m_Y = y; }

	const string& 	getName() const 				{ return m_Name; }
	void			setName( const string& name ) 	{ m_Name = name; }

	ObjectID_t		getObjectID() const				{ return m_ObjectID; }
	void			setObjectID( ObjectID_t objectID ) { m_ObjectID = objectID; }

	string toString() const throw();

private:
	MonsterType_t	m_MonsterType;
	ShrineType		m_ShrineType;
	ZoneID_t 		m_ZoneID;		// 존ID
	ZoneCoord_t 	m_X;
	ZoneCoord_t 	m_Y;
	ObjectID_t 		m_ObjectID;
	string 			m_Name;			// 성단 이름
};

class ShrineSet
{
public: 
	ShrineSet();
	~ShrineSet();

	ItemID_t getBloodBibleItemID() const			{ return m_ItemID; }
	void	 setBloodBibleItemID(ItemID_t itemID) 	{ m_ItemID = itemID; }

	string toString() const throw();

	ShrineID_t		getShrineID() const				{ return m_ShrineID; }
	void			setShrineID( ShrineID_t sid )	{ m_ShrineID = sid; }

	ShrineInfo& 	getSlayerGuardShrine()	{ return m_SlayerGuardShrine; }
	ShrineInfo& 	getVampireGuardShrine() { return m_VampireGuardShrine; }
	ShrineInfo& 	getOustersGuardShrine() { return m_OustersGuardShrine; }
	ShrineInfo& 	getHolyShrine() 		{ return m_HolyShrine; }

	ShrineInfo& 	getReturnGuardShrine() throw(Error);

	void	setSlayerGuardShrine()  { m_OwnerRace = RACE_SLAYER; }
	void	setVampireGuardShrine() { m_OwnerRace = RACE_VAMPIRE; }
	void	setOustersGuardShrine() { m_OwnerRace = RACE_OUSTERS; }

	ItemType_t		getBloodBibleItemType() const					{ return m_ItemType; }
	void			setBloodBibleItemType( ItemType_t itemType ) 	{ m_ItemType = itemType; }

	Race_t			getOwnerRace() const		{ return m_OwnerRace; }
	void			setOwnerRace( Race_t race ) throw(Error);

	void			sendBloodBibleStatus( PlayerCreature* pPC ) throw(Error);
	void			setBloodBibleStatus( GCBloodBibleStatus* pGCBBS ) throw(Error);
	void 			broadcastBloodBibleStatus() throw(Error);

	Item* 			createBloodBibleInGuardShrine() throw(Error);

	bool saveBloodBibleOwner() throw(Error);

private :
	ShrineID_t		m_ShrineID;				// Shrine ID. ItemType과 같아야 한다.
	ShrineInfo		m_SlayerGuardShrine;	// 슬레이어 성 안에 있는 Shrine
	ShrineInfo		m_VampireGuardShrine;	// 뱀파이어 성 안에 있는 Shrine
	ShrineInfo		m_OustersGuardShrine;	// 아우스터즈 성 안에 있는 Shrine
	ShrineInfo		m_HolyShrine;			// 아담의 성지에 있는 Shrine
	ItemType_t		m_ItemType;				// 성서 조각 ItemType
	ItemID_t		m_ItemID;				// 성서 조각 ItemID
	Race_t			m_OwnerRace;			// 최종적으로 차지했던 종족
	GCBloodBibleStatus* m_pGCBBS;			// 피의 성서 위치 정보

	mutable Mutex	m_Mutex;
};


class ShrineInfoManager
{
public:
	typedef hash_map<ShrineID_t, ShrineSet*>	HashMapShrineSet;
	typedef HashMapShrineSet::iterator			HashMapShrineSetItor;
	typedef HashMapShrineSet::const_iterator	HashMapShrineSetConstItor;

public:
	ShrineInfoManager() {}
	~ShrineInfoManager();

public:
	void init() throw(Error);
	void load() throw(Error);
	void reloadOwner() throw(Error);
	void clear();

	void addAllShrineToZone() throw(Error);
	void addShrineToZone( ShrineInfo& shrineInfo, ItemType_t itemType = 0 ) throw(Error);

	void addShrineSet( ShrineSet* pShrineSet ) throw(Error);
	void deleteShrineSet( ShrineID_t shrineID ) throw(Error);
	ShrineSet* getShrineSet( ShrineID_t shrineID ) const throw(Error);
	int  size() const { return m_ShrineSets.size(); }

	string toString() const throw();

public:
	bool isMatchGuardShrine(Item* pItem, MonsterCorpse* pMonsterCorpse, PlayerCreature* pPC) const throw(Error);
	bool isMatchHolyShrine(Item* pItem, MonsterCorpse* pMonsterCorpse) const throw(Error);
	bool isDefenderOfGuardShrine( PlayerCreature* pPC, MonsterCorpse* pShrine ) const throw(Error);
	bool canPickupBloodBible( Race_t race, BloodBible* pBloodBible ) const throw (Error);
	bool getMatchGuardShrinePosition(Item* pItem, ZoneItemPosition& zip) const throw(Error);

//	bool returnCastleBloodBible( ZoneID_t castleZoneID ) const throw (Error);
	bool returnAllBloodBible() const throw (Error);
	bool returnBloodBible( ShrineID_t shrineID, bool bLock = true ) const throw (Error);
	bool returnBloodBible( Zone* pZone, BloodBible* pBloodBible ) const throw (Error);

//	bool removeShrineShield( Zone* pZone ) throw(Error);
	bool removeShrineShield( ShrineInfo* pShrineInfo ) throw(Error);
	//bool addShrineShield( Zone* pZone ) throw(Error);
	//bool addShrineShield_LOCKED( Zone* pZone ) throw(Error);
	bool addShrineShield( ShrineInfo &shrineInfo ) throw(Error);

	bool putBloodBible(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pCorpse) const throw (Error);

public :
	void addAllShrineShield() throw(Error);
	bool removeAllShrineShield() throw(Error);

	// DB에 현재 Owner정보를 저장한다.
	bool saveBloodBibleOwner() throw(Error);

	// 피의 성서 위치 정보를 등록한다.
	void registerBloodBibleStatus( ItemType_t m_Part, GCBloodBibleStatus* pGCBBS ) throw(Error);
	void sendBloodBibleStatus( PlayerCreature* pPC ) throw(Error);

	void broadcastBloodBibleStatus() throw(Error);

private:
	HashMapShrineSet		m_ShrineSets;
};

extern ShrineInfoManager* g_pShrineInfoManager;

#endif // __SHRINE_INFO_MANAGER_H__
