#ifndef __SYSTEM_AVAILABILITIES_MANAGER_H__
#define __SYSTEM_AVAILABILITIES_MANAGER_H__

#include <bitset>

#include "Types.h"
#include "Exception.h"

#include "Gpackets/GCSystemAvailabilities.h"

#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__)
#define SYSTEM_ASSERT(KIND) SystemAvailabilitiesManager::AssertAvailable(SystemAvailabilitiesManager::KIND,\
		string() + __PRETTY_FUNCTION__ + " : 잘못된 클라이언트를 사용했거나 클라이언트와 서버의 정보가 맞지 않습니다.")
#define SYSTEM_RETURN_IF_NOT(KIND) \
		if ( !SystemAvailabilitiesManager::getInstance()->isAvailable(SystemAvailabilitiesManager::KIND) ) \
		{ filelog( "SystemAvailabilities.log", \
		(string() + __PRETTY_FUNCTION__ + " : 잘못된 클라이언트를 사용했거나 클라이언트와 서버의 정보가 맞지 않습니다.").c_str() ); \
		return; }
#define SEND_SYSTEM_AVAILABILITIES(PLAYER) PLAYER->sendPacket( SystemAvailabilitiesManager::getInstance()->getAvailabilitiesPacket() )
#else
#define SYSTEM_ASSERT(X) (void)(0)
#define SYSTEM_RETURN_IF_NOT(X) (void)(0)
#define SEND_SYSTEM_AVAILABILITIES(X) (void)(0)
#endif

const int OpenDegreeID = 999;
const int SkillLimitID = 888;

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
const int ItemLevelLimitID = 777;
#endif

class SystemAvailabilitiesManager
{
public:
	enum SystemKind
	{
		SYSTEM_PARTY,
		SYSTEM_GAMBLE,
		SYSTEM_RANK_BONUS,
		SYSTEM_ENCHANT,
		SYSTEM_GUILD,
		SYSTEM_MASTER_LAIR,
		SYSTEM_PK_ZONE,
		SYSTEM_MARKET,
		SYSTEM_GRAND_MASTER_EFFECT,
		SYSTEM_COUPLE,
		SYSTEM_HOLY_LAND_WAR,
		SYSTEM_GUILD_WAR,
		SYSTEM_RACE_WAR,
		SYSTEM_FLAG_WAR,

		SYSTEM_MAX
	};

	void load() throw(Error);

	bool isAvailable( SystemKind kind ) const { return m_SystemFlags.test(kind); }
	void setAvailable( SystemKind kind, bool avail = true ) {
		m_SystemFlags.set(kind,avail);
		m_bEdited = true;
	}

	Packet* getAvailabilitiesPacket() const
	{
		if ( m_bEdited ) 
		{
			if ( m_pAvailabilitiesPacket == NULL ) m_pAvailabilitiesPacket = new GCSystemAvailabilities();
			m_pAvailabilitiesPacket->setFlag( (DWORD)m_SystemFlags.to_ulong() );
			m_pAvailabilitiesPacket->setOpenDegree( m_ZoneOpenDegree );
			m_pAvailabilitiesPacket->setSkillLimit( m_SkillLevelLimit );
			m_bEdited = false;
		}
		return m_pAvailabilitiesPacket;
	}

	// 싱글톤이당
	static SystemAvailabilitiesManager* getInstance()
	{
		static SystemAvailabilitiesManager theInstance;
		return &theInstance;
	}

	static void AssertAvailable( SystemKind kind, const string& msg ) throw (DisconnectException)
	{
		if ( getInstance()->isAvailable( kind ) ) return;
		filelog( "SystemAvailabilities.log", msg.c_str() );
		throw DisconnectException( msg );
	}

	int getZoneOpenDegree() const { return m_ZoneOpenDegree; }
	int getSkillLevelLimit() const { return m_SkillLevelLimit; }
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__)
	int getItemLevelLimit()	const	{ return m_ItemLevelLimit; }
#endif
	
private:
	bitset<SYSTEM_MAX>	m_SystemFlags;
	mutable GCSystemAvailabilities* m_pAvailabilitiesPacket;
	mutable bool m_bEdited;

	int m_ZoneOpenDegree;
	int m_SkillLevelLimit;

#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__)
	int m_ItemLevelLimit;
#endif
	
	SystemAvailabilitiesManager() { m_SystemFlags.reset(); m_pAvailabilitiesPacket = NULL; m_bEdited = true; }
};

#endif// __SYSTEM_AVAILABILITIES_MANAGER_H__
