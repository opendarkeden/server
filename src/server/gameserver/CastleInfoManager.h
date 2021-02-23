#ifndef __CASTLE_INFO_MANAGER_H__
#define __CASTLE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "PlayerCreature.h"

class Zone;
class NPC;

class CastleInfo
{
public:
	enum ResurrectPriority
	{
		CASTLE_RESURRECT_PRIORITY_FIRST,
		CASTLE_RESURRECT_PRIORITY_SECOND,
		CASTLE_RESURRECT_PRIORITY_THIRD,

		CASTLE_RESURRECT_PRIORITY_MAX
	};

public:
	CastleInfo();
	~CastleInfo();

public:
	ZoneID_t getZoneID() const { return m_ZoneID; }
	void	 setZoneID(const ZoneID_t zoneID) { m_ZoneID = zoneID; }

	ShrineID_t getShrineID() const { return m_ShrineID; }
	void   setShrineID( const ShrineID_t id ) { m_ShrineID = id; }

	GuildID_t getGuildID() const { return m_GuildID; }
	void	  setGuildID( const GuildID_t guildID ) { m_GuildID = guildID; }

	const string& getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	int	getItemTaxRatio() const { return m_ItemTaxRatio; }
	void setItemTaxRatio( const int itemTaxRatio ) { m_ItemTaxRatio = itemTaxRatio; }

	Gold_t getEntranceFee() const { return m_EntranceFee; }
	void   setEntranceFee( const Gold_t entranceFee ) { m_EntranceFee = entranceFee; }

	Gold_t getTaxBalance() const { return m_TaxBalance; }
	void   setTaxBalance( const Gold_t balance ) { m_TaxBalance = balance; }

	Gold_t increaseTaxBalance( Gold_t tax );
	Gold_t decreaseTaxBalance( Gold_t tax );

	Gold_t increaseTaxBalanceEx( Gold_t tax ) throw(Error);
	Gold_t decreaseTaxBalanceEx( Gold_t tax ) throw(Error);

	const list<OptionType_t>& getOptionTypeList() const throw() { return m_BonusOptionList; }
	void setOptionTypeList( const string& options ) throw();

	bool isCastleZone(ZoneID_t targetZoneID) const throw (Error);
	const list<ZoneID_t>& getZoneIDList() const throw() { return m_CastleZoneIDList; }
	void setZoneIDList( const string& zoneIDs ) throw();

	Race_t getRace() const { return m_Race; }
	void   setRace( Race_t race ) { m_Race = race; }

	void setResurrectPosition( ResurrectPriority resurrectPriority, const ZONE_COORD& zoneCoord );
	void getResurrectPosition( ResurrectPriority resurrectPriority, ZONE_COORD& zoneCoord );

	bool isCommon() const { return ( m_GuildID == SlayerCommon || m_GuildID == VampireCommon || m_GuildID == OustersCommon ); }

	void	broadcast(Packet* pPacket) const throw (Error);

	string toString() const throw();

private:
	ZoneID_t 	m_ZoneID;		// 존ID
	ShrineID_t 	m_ShrineID;		// 성 상징의 ShrineID
	GuildID_t 	m_GuildID;	// 주인 길드 ID
	string 		m_Name;			// 성 이름
	int 		m_ItemTaxRatio;		// 아이템 살 때 세율 (%)
	Gold_t 		m_EntranceFee;	// 입장료
	Gold_t 		m_TaxBalance;	// 세금 쌓여있는거
	Race_t 		m_Race;			// 어느 종족의 성인가

	list<OptionType_t> 	m_BonusOptionList;	// 종족 보너스
	list<ZoneID_t> 		m_CastleZoneIDList;

	ZONE_COORD m_ResurrectPosition[ CASTLE_RESURRECT_PRIORITY_MAX ];		// 성의 부활 위치
};

class CastleInfoManager
{
public:
	CastleInfoManager();
	~CastleInfoManager();
public:
	void init() throw(Error);
	void load() throw(Error);
	void save(ZoneID_t zoneID) throw(Error);

	void addCastleInfo( CastleInfo* pCastleInfo ) throw(Error);
	void deleteCastleInfo( ZoneID_t zoneID ) throw(Error);
	CastleInfo* getCastleInfo( ZoneID_t zoneID ) const throw(Error);
	int  size() const { return m_CastleInfos.size(); }

	bool modifyCastleOwner(ZoneID_t zoneID, PlayerCreature* pPC ) throw(Error);
	bool modifyCastleOwner(ZoneID_t zoneID, Race_t race, GuildID_t guildID ) throw (Error);
	bool tinysave( ZoneID_t zoneID, const string& query ) throw(Error);
	bool increaseTaxBalance( ZoneID_t zoneID, Gold_t tax ) throw(Error);
	bool decreaseTaxBalance( ZoneID_t zoneID, Gold_t tax ) throw(Error);

	bool setItemTaxRatio( Zone* pZone, int itemTaxRatio ) throw(Error);
	const hash_map<ZoneID_t, CastleInfo*>& getCastleInfos() const 	{ return m_CastleInfos; }

	int getItemTaxRatio( const PlayerCreature* pPC, const NPC* pNPC = NULL ) const throw(Error);
	Gold_t getEntranceFee( ZoneID_t zoneID, PlayerCreature* pPC ) const  throw(Error);

	bool isCastleMember( PlayerCreature* pPC ) const throw(Error);
	bool isCastleMember( ZoneID_t zoneID, PlayerCreature* pPC ) const throw(Error);
	bool isPossibleEnter( ZoneID_t zoneID, PlayerCreature* pPC ) const throw(Error);
	bool canPortalActivate( ZoneID_t zoneID, PlayerCreature* pPC ) const throw(Error);
	bool hasOtherBloodBible( ZoneID_t zoneID, PlayerCreature* pPC ) const throw(Error);

	CastleInfo* getGuildCastleInfo( GuildID_t guildID ) const throw(Error);
	list<CastleInfo*> getGuildCastleInfos( GuildID_t guildID ) const throw(Error);

	bool getResurrectPosition( PlayerCreature* pPC, ZONE_COORD& zoneCoord ) throw (Error);

	//----------------------------------------------------------------------
	// CastleZoneID 관련
	//----------------------------------------------------------------------
	bool 		isCastleZone(ZoneID_t castleZoneID, ZoneID_t targetZoneID) const throw (Error);
	bool		isCastleZone(ZoneID_t zoneID) const;
	void		clearCastleZoneIDs() throw (Error);
	bool	 	getCastleZoneID(ZoneID_t zoneID, ZoneID_t &castleZoneID) const throw (Error);
	void 		setCastleZoneID(ZoneID_t zoneID, ZoneID_t castleZoneID) throw (Error);
	bool		isSameCastleZone(ZoneID_t zoneID1, ZoneID_t zoneID2) const throw (Error);

	//----------------------------------------------------------------------
	// 모든 성에 적용 되는 것들
	//----------------------------------------------------------------------
	void	releaseAllSafeZone() throw (Error);
	void    resetAllSafeZone() throw (Error);

	void	deleteAllNPCs() throw (Error);
	void	loadAllNPCs() throw (Error);

	void	transportAllOtherRace() throw (Error);

	ZoneID_t 	getCastleZoneID(ShrineID_t shrineID) const throw (Error);
	void		broadcastShrinePacket(ShrineID_t shrineID, Packet* pPacket) const throw (Error);

	SkillType_t getCastleSkillType( ZoneID_t zoneID, GuildID_t guildID ) const throw (Error);

	string toString() const throw();

private:
	hash_map<ZoneID_t, CastleInfo*> m_CastleInfos;
	hash_map<ZoneID_t, ZoneID_t> 	m_CastleZoneIDs;
};

extern CastleInfoManager* g_pCastleInfoManager;

#endif // __CASTlE_INFO_MANAGER_H__
