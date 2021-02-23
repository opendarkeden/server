//////////////////////////////////////////////////////////////////////////////
// Filename		: Guild.h
// Written by	: bezz
// Description	:
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUILD_H__
#define __GUILD_H__

#include "Types.h"
#include "Assert.h"
#include "Exception.h"
#include "Mutex.h"
#include <hash_map>
#include <list>

#include "VSDateTime.h"

#ifdef __SHARED_SERVER__
class GuildInfo2;
#endif

class GuildInfo;
class GCGuildMemberList;

//////////////////////////////////////////////////////////////////////////////
// class GuildMember
// 길드멤버에 관한 정보를 가진다.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef __CHINA_SERVER__
const Gold_t REQUIRE_SLAYER_MASTER_GOLD 	= 50000000;
const Gold_t REQUIRE_VAMPIRE_MASTER_GOLD	= 50000000;
const Gold_t REQUIRE_OUSTERS_MASTER_GOLD	= 50000000;

const Gold_t REQUIRE_SLAYER_SUBMASTER_GOLD	=  25000000;
const Gold_t REQUIRE_VAMPIRE_SUBMASTER_GOLD	=  25000000;
const Gold_t REQUIRE_OUSTERS_SUBMASTER_GOLD	=  25000000;

const Gold_t RETURN_SLAYER_MASTER_GOLD		= 0;
const Gold_t RETURN_VAMPIRE_MASTER_GOLD		= 0;
const Gold_t RETURN_OUSTERS_MASTER_GOLD		= 0;

const Gold_t RETURN_SLAYER_SUBMASTER_GOLD		= 0;
const Gold_t RETURN_VAMPIRE_SUBMASTER_GOLD		= 0;
const Gold_t RETURN_OUSTERS_SUBMASTER_GOLD		= 0;

const Fame_t REQUIRE_SLAYER_MASTER_FAME[SKILL_DOMAIN_ETC] =
{
	500000,		// SKILL_DOMAIN_BLADE
	500000,		// SKILL_DOMAIN_SWORD
	500000,		// SKILL_DOMAIN_GUN
	 100000,		// SKILL_DOMAIN_HEAL
	 150000			// SKILL_DOMAIN_ENCHANT
};

const Fame_t REQUIRE_SLAYER_SUBMASTER_FAME[SKILL_DOMAIN_ETC] =
{
	400000,		// SKILL_DOMAIN_BLADE
	400000,		// SKILL_DOMAIN_SWORD
	400000,		// SKILL_DOMAIN_GUN
	75000,		// SKILL_DOMAIN_HEAL
	125000		// SKILL_DOMAIN_ENCHANT
};

#else
#ifndef __OLD_GUILD_WAR__
const Gold_t REQUIRE_SLAYER_MASTER_GOLD 	= 10000000;
const Gold_t REQUIRE_VAMPIRE_MASTER_GOLD	= 10000000;
const Gold_t REQUIRE_OUSTERS_MASTER_GOLD	= 10000000;

const Gold_t REQUIRE_SLAYER_SUBMASTER_GOLD	=  0;
const Gold_t REQUIRE_VAMPIRE_SUBMASTER_GOLD	=  0;
const Gold_t REQUIRE_OUSTERS_SUBMASTER_GOLD	=  0;

const Gold_t RETURN_SLAYER_MASTER_GOLD		= 9000000;
const Gold_t RETURN_VAMPIRE_MASTER_GOLD		= 9000000;
const Gold_t RETURN_OUSTERS_MASTER_GOLD		= 9000000;

const Gold_t RETURN_SLAYER_SUBMASTER_GOLD		= 0;
const Gold_t RETURN_VAMPIRE_SUBMASTER_GOLD		= 0;
const Gold_t RETURN_OUSTERS_SUBMASTER_GOLD		= 0;

const Fame_t REQUIRE_SLAYER_MASTER_FAME[SKILL_DOMAIN_ETC] =
{
	100000,		// SKILL_DOMAIN_BLADE
	100000,		// SKILL_DOMAIN_SWORD
	100000,		// SKILL_DOMAIN_GUN
	 20000,		// SKILL_DOMAIN_HEAL
	 30000			// SKILL_DOMAIN_ENCHANT
};

const Fame_t REQUIRE_SLAYER_SUBMASTER_FAME[SKILL_DOMAIN_ETC] =
{
	0,		// SKILL_DOMAIN_BLADE
	0,		// SKILL_DOMAIN_SWORD
	0,		// SKILL_DOMAIN_GUN
	0,		// SKILL_DOMAIN_HEAL
	0		// SKILL_DOMAIN_ENCHANT
};
#else
const Gold_t REQUIRE_SLAYER_MASTER_GOLD 	= 100000000;
const Gold_t REQUIRE_VAMPIRE_MASTER_GOLD	= 100000000;
const Gold_t REQUIRE_OUSTERS_MASTER_GOLD	= 100000000;

const Gold_t REQUIRE_SLAYER_SUBMASTER_GOLD	=  50000000;
const Gold_t REQUIRE_VAMPIRE_SUBMASTER_GOLD	=  50000000;
const Gold_t REQUIRE_OUSTERS_SUBMASTER_GOLD	=  50000000;

const Gold_t RETURN_SLAYER_MASTER_GOLD		= 90000000;
const Gold_t RETURN_VAMPIRE_MASTER_GOLD		= 90000000;
const Gold_t RETURN_OUSTERS_MASTER_GOLD		= 90000000;

const Gold_t RETURN_SLAYER_SUBMASTER_GOLD		= 45000000;
const Gold_t RETURN_VAMPIRE_SUBMASTER_GOLD		= 45000000;
const Gold_t RETURN_OUSTERS_SUBMASTER_GOLD		= 45000000;

const Fame_t REQUIRE_SLAYER_MASTER_FAME[SKILL_DOMAIN_ETC] =
{
	1000000,		// SKILL_DOMAIN_BLADE
	1000000,		// SKILL_DOMAIN_SWORD
	1000000,		// SKILL_DOMAIN_GUN
	 200000,		// SKILL_DOMAIN_HEAL
	 300000			// SKILL_DOMAIN_ENCHANT
};

const Fame_t REQUIRE_SLAYER_SUBMASTER_FAME[SKILL_DOMAIN_ETC] =
{
	800000,		// SKILL_DOMAIN_BLADE
	800000,		// SKILL_DOMAIN_SWORD
	800000,		// SKILL_DOMAIN_GUN
	150000,		// SKILL_DOMAIN_HEAL
	250000		// SKILL_DOMAIN_ENCHANT
};
#endif

#endif

const SkillLevel_t		REQUIRE_SLAYER_MASTER_SKILL_DOMAIN_LEVEL	= 50;
const Level_t			REQUIRE_VAMPIRE_MASTER_LEVEL				= 50;	
const Level_t			REQUIRE_OUSTERS_MASTER_LEVEL				= 50;	

#ifndef __OLD_GUILD_WAR__
const SkillLevel_t		REQUIRE_SLAYER_SUBMASTER_SKILL_DOMAIN_LEVEL	= 30;
#else
const SkillLevel_t		REQUIRE_SLAYER_SUBMASTER_SKILL_DOMAIN_LEVEL	= 40;
#endif
const Level_t			REQUIRE_VAMPIRE_SUBMASTER_LEVEL				= 40;	
const Level_t			REQUIRE_OUSTERS_SUBMASTER_LEVEL				= 40;	

class GuildMember
{

public:
	GuildMember() throw();

///// Member constants /////

public:

	enum GuildRank
	{
		GUILDMEMBER_RANK_NORMAL	= 0,		// 일반 멤버
		GUILDMEMBER_RANK_MASTER,			// 길드 마스터
		GUILDMEMBER_RANK_SUBMASTER,			// 길드 서브 마스터
		GUILDMEMBER_RANK_WAIT,				// 길드 가입 대기
		GUILDMEMBER_RANK_DENY,				// 추방/거부 당함
		GUILDMEMBER_RANK_LEAVE,				// 길드 탈퇴(스스로)

		GUILDMEMBER_RANK_MAX
	};

	
public: // DB methods
	void create() throw();
	bool load() throw();
	void save() throw();
	void destroy() throw();
	void expire() throw();
	void leave() throw();
	
	void saveIntro( const string& intro ) throw();
	string getIntro() const throw();

	
public: // identity methods
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID(GuildID_t guildID) throw() { m_GuildID = guildID; }

	string getName() const throw() { return m_Name; }
	void setName(const string& name) throw() { m_Name = name; }

	GuildMemberRank_t getRank() const throw() { return m_Rank; }
	void setRank(GuildMemberRank_t rank) throw();		// Guild class 에서 처리한다.

	bool getLogOn() const throw() { return m_bLogOn; }
	void setLogOn( bool logOn ) throw() { m_bLogOn = logOn; }

	ServerID_t	getServerID()	const throw() { return m_ServerID; }
	void		setServerID( ServerID_t ServerID ) throw() { m_ServerID = ServerID; }
	
	string getRequestDateTime() const throw();
	void setRequestDateTime( const VSDateTime& vsdatetime ) throw() { m_RequestDateTime = vsdatetime; }
	void setRequestDateTime( const string& rdatetime ) throw();
	bool isRequestDateTimeOut( const VSDateTime& currentDateTime ) const throw();

public: // debug
	string toString() const throw();


///// operator overloadgin /////

public:
	GuildMember& operator = ( GuildMember& Member );


///// Member data /////

protected:
	GuildID_t			m_GuildID;			// 길드 ID
	string				m_Name;				// 멤버 이름
	GuildMemberRank_t	m_Rank;				// 멤버의 계급
	VSDateTime			m_RequestDateTime;	// 가입 신청 시간
	bool				m_bLogOn;			// 접속 여부
	ServerID_t			m_ServerID;			// 서버 위치
};


//////////////////////////////////////////////////////////////////////////////
// class Guild
// 길드에 관한 정보를 가진다.
//
// GuildInfo 테이블의 구조
// ----------------------------------------
// GuildID            INT
// GuildName          VARCHAR(20)
// GuildType          TINYINT
// GuildGold          INT
// ----------------------------------------
//////////////////////////////////////////////////////////////////////////////

#ifndef __OLD_GUILD_WAR__
#define MAX_GUILDMEMBER_ACTIVE_COUNT		100
#define MIN_GUILDMEMBER_COUNT				3
#else
#define MAX_GUILDMEMBER_ACTIVE_COUNT		230
#define MIN_GUILDMEMBER_COUNT				5
#endif
#define MAX_GUILDMEMBER_WAIT_COUNT			15

typedef hash_map<string, GuildMember*> HashMapGuildMember;
typedef HashMapGuildMember::iterator HashMapGuildMemberItor;
typedef HashMapGuildMember::const_iterator HashMapGuildMemberConstItor;

class Guild
{

///// Member constants /////

public:

	enum GuildTypes
	{
		GUILD_TYPE_NORMAL = 0,		// 일반 길드
		GUILD_TYPE_JUDGE,			// 판관 길드
		GUILD_TYPE_ASSASSIN,		// 암살자 길드

		GUILD_TYPE_MAX
	};

	enum GuildState
	{
		GUILD_STATE_ACTIVE = 0,		// 활동 중인 길드
		GUILD_STATE_WAIT,			// 등록 대기 중인 길드
		GUILD_STATE_CANCEL,			// 취소된 길드
		GUILD_STATE_BROKEN,			// 해체된 길드

		GUILD_STATE_MAX
	};

	enum GuildRace
	{
		GUILD_RACE_SLAYER = 0,		// 슬레이어 길드
		GUILD_RACE_VAMPIRE,			// 뱀파이어 길드
		GUILD_RACE_OUSTERS,			// 아우스터즈 길드

		GUILD_RACE_MAX
	};

public: // constructor & destructor
	Guild() throw();
	virtual ~Guild() throw();


public: // DB methods
	void create() throw();
	bool load() throw();
	void save() throw();
	void destroy() throw();

	
public: // identity methods
	GuildID_t getID() const throw() { return m_ID; }
	void setID(GuildID_t id) throw() { m_ID = id; }

	string getName() const throw() { return m_Name; }
	void setName(const string& name) throw() { m_Name = name; }

	GuildType_t getType() const throw() { return m_Type; }
	void setType(GuildType_t type) throw() { m_Type = type; }

	GuildRace_t getRace() const throw() { return m_Race; }
	void setRace( GuildRace_t race ) throw() { m_Race = race; }

	GuildState_t getState() const throw() { return m_State; }
	void setState(GuildState_t state) throw() { m_State = state; }

	ServerGroupID_t getServerGroupID() const throw() { return m_ServerGroupID; }
	void setServerGroupID( ServerGroupID_t serverGroupID ) throw() { m_ServerGroupID = serverGroupID; }

	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID( ZoneID_t zoneID ) throw() { m_ZoneID = zoneID; }

	string getMaster() const throw() { return m_Master; }
	void setMaster(const string& master) throw() { m_Master = master; }

	string getDate() const throw() { return m_Date; }
	void setDate( const string& Date ) throw() { m_Date = Date; }

	string getIntro() const throw() { return m_Intro; }
	void setIntro( const string& intro ) throw() { m_Intro = intro; }

#ifdef __SHARED_SERVER__
	void saveIntro( const string& intro ) throw();
	void tinysave( const char* field ) const throw();
	void saveCount() const throw();
#endif


///// GuildMember get/add/delete/modify /////
	GuildMember* getMember( const string& name ) const throw();
	GuildMember* getMember_NOLOCKED( const string& name ) const throw();
	void addMember( GuildMember* pMember ) throw( DuplicatedException, Error );
	void deleteMember( const string& name ) throw();
	void modifyMember( GuildMember& Member ) throw();

	void modifyMemberRank( const string& name, GuildMemberRank_t rank ) throw();

	HashMapGuildMember& getMembers() throw() { return m_Members; }

	int getActiveMemberCount() const throw() { return m_ActiveMemberCount; }
	int getWaitMemberCount() const throw() { return m_WaitMemberCount; }

#ifdef __GAME_SERVER__
	void addCurrentMember( const string& name ) throw( DuplicatedException, Error );
	void deleteCurrentMember( const string& name ) throw( NoSuchElementException );
	list<string> getCurrentMembers() throw();
#endif

#ifdef __SHARED_SERVER__
	void makeInfo( GuildInfo2* pGulidInfo ) throw();
#endif

	void makeInfo( GuildInfo* pGuildInfo ) throw();
	void makeMemberInfo( GCGuildMemberList& gcGuildMemberList ) throw();


public: // static
	static GuildID_t getMaxGuildID() throw() { return m_MaxGuildID; }
	static void setMaxGuildID(GuildID_t id) throw() { m_MaxGuildID = id; }

	static ZoneID_t getMaxSlayerZoneID() throw() { return m_MaxSlayerZoneID; }
	static void setMaxSlayerZoneID( ZoneID_t zoneID ) throw() { m_MaxSlayerZoneID = zoneID; }

	static ZoneID_t getMaxVampireZoneID() throw() { return m_MaxVampireZoneID; }
	static void setMaxVampireZoneID( ZoneID_t zoneID ) throw() { m_MaxVampireZoneID = zoneID; }

	static ZoneID_t getMaxOustersZoneID() throw() { return m_MaxOustersZoneID; }
	static void setMaxOustersZoneID( ZoneID_t zoneID ) throw() { m_MaxOustersZoneID = zoneID; }

public:
	void expireTimeOutWaitMember( VSDateTime currentDateTime, list<string>& mList ) throw(Error);

public: // debug
	string toString() const throw();

	static string correctString( const string& str ) throw();


///// Member data /////

protected:
	GuildID_t			m_ID;					// 길드 ID
	string				m_Name;					// 길드 이름
	GuildType_t			m_Type;					// 길드 타입
	GuildRace_t			m_Race;					// 길드 종족
	GuildState_t		m_State;				// 길드 상태
	ServerGroupID_t		m_ServerGroupID;		// 길드 존이 있는 서버 그룹 ID
	ZoneID_t			m_ZoneID;				// 길드 ZoneID
	string				m_Master;				// 길드 마스터
	string				m_Date;					// 길드 Expire, Regist Date
	string				m_Intro;				// 길드 소개

	HashMapGuildMember	m_Members;				// 길드 멤버 포인터 맵
	int					m_ActiveMemberCount;	// Active Member Count
	int					m_WaitMemberCount;		// Wait Member Count

	static GuildID_t	m_MaxGuildID;			// 길드 아이디 최대값
	static ZoneID_t		m_MaxSlayerZoneID;		// 슬레이어 길드 존 ID 최대값
	static ZoneID_t		m_MaxVampireZoneID;		// 뱀파이어 길드 존 ID 최대값
	static ZoneID_t		m_MaxOustersZoneID;		// 아우스터즈 길드 존 ID 최대값

	mutable Mutex		m_Mutex;				// Mutex for Guild

#ifdef __GAME_SERVER__
	list<string>		m_CurrentMembers;		// 현재 접속 중인 멤버
#endif

};

#endif
