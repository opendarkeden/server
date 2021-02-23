//--------------------------------------------------------------------------------
// 
// Filename    : GCUpdateInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_UPDATE_INFO_H__
#define __GC_UPDATE_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "GameTime.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "EffectInfo.h"
#include "Assert.h"
#include "RideMotorcycleInfo.h"
#include "NPCInfo.h"
#include "NicknameInfo.h"
#include "BloodBibleSignInfo.h"

#define FLAG_PREMIUM_ZONE			0x10	// premium으로 설정된 존이다.
#define FLAG_PREMIUM_PLAY			0x01	// premium play를 하는 중인가?

//--------------------------------------------------------------------------------
//
// class GCUpdateInfo;
//
// 클라이언트가 게임 서버에 접속해서 CGConnect 패킷을 보내면, 게임 서버는 크리처와
// 소유 아이템을 로딩해서 존에 들어갈 준비를 하게 된다. 그다음 PC와 아이템 정보,
// 그리고 존 정보를 GCUpdateInfo에 담아서 클라이언트로 전송하게 된다.
//
//--------------------------------------------------------------------------------

class GCUpdateInfo : public Packet {

public :

	enum
	{
		UNION_MASTER = 0,		// 길드연합의 연합마스터다
		UNION_GUILD_MASTER,		// 길드연합의 연합마스터가 아니지만 소속된 길드의 마스터다
		UNION_NOTHING,			// 아무것도 아니다.
		UNION_MAX
	};
	
	// constructor
	GCUpdateInfo() throw();

	// destructor
	~GCUpdateInfo() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_UPDATE_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		// [PCType][PCInfo]
		// [GameTime][Weather][WeatherLevel][DarkLevel][LightLevel]
		// [#NPCTypes][NPCType1]...[NPCTypeN]
		// [#MonsterTypes][MonsterType1]...[MonsterTypeM]
		PacketSize_t size = 0;

		WORD MotorcycleSize = 0;
		if(m_hasMotorcycle) 
		{
			MotorcycleSize = m_pRideMotorcycleInfo->getSize();
		}

		size += szBYTE;
		size += m_pPCInfo->getSize();
		size += m_pInventoryInfo->getSize();
		size += m_pGearInfo->getSize();
		size += m_pExtraInfo->getSize();
		size += szBYTE;
		size += MotorcycleSize;
		size += m_pEffectInfo->getSize();
		size += szZoneID;
		size += szCoord;
		size += szCoord;
		size += m_GameTime.getSize();
		size += szWeather;
		size += szWeatherLevel;
		size += szDarkLevel;
		size += szLightLevel;
		size += szBYTE;
		size += szNPCType* m_nNPCs;
		size += szBYTE;
		size += szMonsterType* m_nMonsters;

		size += szBYTE;
		list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
		for(; itr != m_NPCInfos.end(); itr++)
		{
			NPCInfo* pInfo = *itr;
			size += pInfo->getSize();
		}
		// 서버 상태
		size += szBYTE;
		// 프리미엄
		size += szBYTE;
		// SMS
		size += szDWORD;

		if ( m_pNicknameInfo == NULL )
		{
			NicknameInfo noNick;
			noNick.setNicknameType( NicknameInfo::NICK_NONE );
			size += noNick.getSize();
		}
		else
		{
			size += m_pNicknameInfo->getSize();
		}

		size += szBYTE;

		// GuildUnion
		size += sizeof(uint);
		size += szBYTE;

		size += m_pBloodBibleSign->getSize();

		// 파워짱 포인트
		size += szint;

		return size;
	}

	// get packet name
	string getPacketName() const throw() { return "GCUpdateInfo"; }
	
	// get packet's debug string
	string toString() const throw();

//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get/set PC info
	PCInfo* getPCInfo() const throw() { return m_pPCInfo; }
	void setPCInfo(PCInfo* pPCInfo) throw(Error) { m_pPCInfo = pPCInfo; }

	// get/set Inventory Info
	InventoryInfo* getInventoryInfo() const throw() { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo) throw(Error) { m_pInventoryInfo = pInventoryInfo; }

	// get/set Gear Info
	GearInfo* getGearInfo() const throw() { return m_pGearInfo; }
	void setGearInfo(GearInfo* pGearInfo) throw(Error) { m_pGearInfo = pGearInfo; }

	// get/set ExtraInfo
	ExtraInfo* getExtraInfo() const throw() { return m_pExtraInfo; }
	void setExtraInfo(ExtraInfo* pExtraInfo) throw(Error) { m_pExtraInfo = pExtraInfo; }

	// get/set EffectInfo
	EffectInfo* getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw(Error) { m_pEffectInfo = pEffectInfo; }

	// get/set hasMotorcycle
	bool hasMotorcycle() const throw() { return m_hasMotorcycle; }

	// get/set RideMotorcycleInfo
	RideMotorcycleInfo* getRideMotorcycleInfo() const throw() { return m_pRideMotorcycleInfo; }
	void setRideMotorcycleInfo(RideMotorcycleInfo* pRideMotorcycleInfo) throw() {
		m_pRideMotorcycleInfo = pRideMotorcycleInfo;
		m_hasMotorcycle = true;
	}

	// get/set ZoneID
	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID(const ZoneID_t & zoneID) throw() { m_ZoneID = zoneID; }

	// get / set ZoneX
	Coord_t getZoneX() const throw() { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX) { m_ZoneX = ZoneX; }

	// get / set ZoneY
	Coord_t getZoneY() const throw() { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY) { m_ZoneY = ZoneY; }

	// get/set GameTime
	GameTime getGameTime() const throw() { return m_GameTime; }
	void setGameTime(const GameTime & gameTime) throw() { m_GameTime = gameTime; }

	// get/set weather
	Weather getWeather() const throw() { return m_Weather; }
	void setWeather(Weather weather) throw() { m_Weather = weather; }

	// get/set weather level
	WeatherLevel_t getWeatherLevel() const throw() { return m_WeatherLevel; }
	void setWeatherLevel(WeatherLevel_t weatherLevel) throw() { m_WeatherLevel = weatherLevel; }

	// get/set darklevel
	DarkLevel_t getDarkLevel() const throw() { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	// get/set lightlevel
	LightLevel_t getLightLevel() const throw() { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }

	// get/set # of NPC
	uint getNPCCount() const throw() { return m_nNPCs; }
	void setNPCCount(uint n) throw(Error) { Assert(n <= maxNPCPerZone); m_nNPCs = n; }

	// get/set NPC type
	NPCType_t getNPCType(uint n) const throw() { Assert(n < maxNPCPerZone); return m_NPCTypes[n]; }
	void setNPCType(uint n, NPCType_t npcType) throw() { Assert(n < maxNPCPerZone); m_NPCTypes[n] = npcType; }

	// get/set # of monster
	uint getMonsterCount() const throw() { return m_nMonsters; }
	void setMonsterCount(uint n) throw(Error) { Assert(n <= maxMonsterPerZone); m_nMonsters = n; }

	// get/set Monster type
	MonsterType_t getMonsterType(uint n) const throw() { Assert(n < maxMonsterPerZone); return m_MonsterTypes[n]; }
	void setMonsterType(uint n, MonsterType_t npcType) throw() { Assert(n < maxMonsterPerZone); m_MonsterTypes[n] = npcType; }

	// get/set npc info
	void addNPCInfo(NPCInfo* pInfo) { m_NPCInfos.push_back(pInfo);}
	NPCInfo* popNPCInfo(void) { if (m_NPCInfos.empty()) return NULL; NPCInfo* pInfo = m_NPCInfos.front(); m_NPCInfos.pop_front(); return pInfo; }

	// get/set ServerStat
	void setServerStat( BYTE ServerStat ) throw() { m_ServerStat = ServerStat; }
	BYTE getServerStat() const throw() { return m_ServerStat; }

	// premium play 관련
	void setPremiumZone() { m_fPremium |= FLAG_PREMIUM_ZONE; }
	void setPremiumPlay() { m_fPremium |= FLAG_PREMIUM_PLAY; }
	BYTE isPremiumZone() const { return m_fPremium & FLAG_PREMIUM_ZONE; }
	BYTE isPremiumPlay() const { return m_fPremium & FLAG_PREMIUM_PLAY; }

	DWORD	getSMSCharge() const { return m_SMSCharge; }
	void	setSMSCharge(DWORD charge) { m_SMSCharge = charge; }

	NicknameInfo* getNicknameInfo() const throw() { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw(Error) { m_pNicknameInfo = pNicknameInfo; }

	BYTE	isNonPK() const { return m_NonPK; }
	void	setNonPK(BYTE pk) { m_NonPK = pk; }

		
	BYTE	getGuildUnionUserType() const { return m_GuildUnionUserType; }
	void	setGuildUnionUserType(BYTE type) { m_GuildUnionUserType= type; }

	uint	getGuildUnionID() const { return m_GuildUnionID; }
	void	setGuildUnionID(uint ID) { m_GuildUnionID = ID; }

	BloodBibleSignInfo*	getBloodBibleSignInfo() { return m_pBloodBibleSign; }
	void	setBloodBibleSignInfo( BloodBibleSignInfo* pInfo ) { m_pBloodBibleSign = pInfo; }

    // get / set PowerPoint
    int getPowerPoint() const { return m_PowerPoint; }
    void setPowerPoint( int powerpoint ) { m_PowerPoint = powerpoint; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :

	//--------------------------------------------------------------------------------
	// PC Information
	//--------------------------------------------------------------------------------
	// PCSlayerInfo2 또는 PCVampireInfo2 를 사용한다.
	PCInfo* m_pPCInfo;

	//--------------------------------------------------------------------------------
	// Inventory Information
	//--------------------------------------------------------------------------------
	InventoryInfo* m_pInventoryInfo;

	//--------------------------------------------------------------------------------
	// Gear Information
	//--------------------------------------------------------------------------------
	GearInfo* m_pGearInfo;

	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	ExtraInfo* m_pExtraInfo;

	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	EffectInfo* m_pEffectInfo;

	//--------------------------------------------------------------------------------
	// 모토사이클이 있나 없나.
	//--------------------------------------------------------------------------------
	bool m_hasMotorcycle;

	//--------------------------------------------------------------------------------
	// Motorcycle Information
	//--------------------------------------------------------------------------------
	RideMotorcycleInfo* m_pRideMotorcycleInfo;

	// inventory
	// quick item slot
	// gear

	// 저널(PDA)
	// 수행 퀘스트 정보
	// 공지사항, 이벤트 정보
	// 흐흠.. 얘들은 처음 PDS를 켤 때 다운받을까나.. - -;

	//--------------------------------------------------------------------------------
	// Zone Information
	//--------------------------------------------------------------------------------
	// 존 아이디
	ZoneID_t m_ZoneID;	

	// 나타날 좌표의 대강의 위치
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

	// Game Time
	GameTime m_GameTime;
	
	// Weather(날씨 정보)
	Weather m_Weather;
	WeatherLevel_t m_WeatherLevel;

	// Dark/Light
	DarkLevel_t m_DarkLevel;
	LightLevel_t m_LightLevel;

	// 존에 출현하는 NPC 스프라이트 타입의 개수, 스프라이트 타입 배열
	BYTE m_nNPCs;
	NPCType_t m_NPCTypes[ maxNPCPerZone ];

	// 존에 출현하는 몬스터 스프라이트 타입의 개수, 스프라이트 타입 배열
	BYTE m_nMonsters;
	MonsterType_t m_MonsterTypes[ maxMonsterPerZone ];

	// 현재 존에 존재하는 NPC들에 대한 정보
	list<NPCInfo*> m_NPCInfos;

	// 서버 상태
	BYTE m_ServerStat;

	// 프리미엄 관련
	BYTE m_fPremium;

	DWORD	m_SMSCharge;
	NicknameInfo*	m_pNicknameInfo;

	BYTE	m_NonPK;

	// 연합길드 정보
	uint	m_GuildUnionID;
	BYTE	m_GuildUnionUserType;

	BloodBibleSignInfo* m_pBloodBibleSign;

    // 파워짱 포인트
    int    m_PowerPoint;
};


//--------------------------------------------------------------------------------
//
// class GCUpdateInfoFactory;
//
// Factory for GCUpdateInfo
//
//--------------------------------------------------------------------------------

class GCUpdateInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUpdateInfo(); }

	// get packet name
	string getPacketName() const throw() { return "GCUpdateInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_UPDATE_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUpdateInfoPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		size += PCSlayerInfo2::getMaxSize();
		size += InventoryInfo::getMaxSize();
		size += GearInfo::getMaxSize();
		size += ExtraInfo::getMaxSize();
		size += EffectInfo::getMaxSize();
		size += szBYTE;
		size += RideMotorcycleInfo::getMaxSize();
		size += szZoneID;
		size += szCoord;
		size += szCoord;
		size += GameTime::getMaxSize();
		size += szWeather;
		size += szWeatherLevel;
		size += szDarkLevel;
		size += szLightLevel;
		size += szBYTE;
		size += szNPCType* maxNPCPerZone;
		size += szBYTE;
		size += szMonsterType* maxMonsterPerZone; 

		size += szBYTE;
		size += NPCInfo::getMaxSize()* 255;
		// 서버 상태
		size += szBYTE;
		// 프리미엄
		size += szBYTE;
		size += szDWORD;
		size += NicknameInfo::getMaxSize();

		size += szBYTE;

		// GuildUnion
		size += sizeof(uint);
		size += szBYTE;

		size += BloodBibleSignInfo::getMaxSize();

		// 파워짱 포인트
		size += szint;

		return size;
	}

};



//--------------------------------------------------------------------------------
//
// class GCUpdateInfoHandler;
//
//--------------------------------------------------------------------------------

class GCUpdateInfoHandler {

public :

	// execute packet's handler
	static void execute(GCUpdateInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
