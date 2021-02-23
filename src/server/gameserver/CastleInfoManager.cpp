////////////////////////////////////////////////////////////////////////////////
// Filename    : CastleInfoManager.cpp
// Written By  : 
// Description : 아담의 성지 근처에 있는 성에 대한 정보
////////////////////////////////////////////////////////////////////////////////

#include "CastleInfoManager.h"
#include "PlayerCreature.h"
#include "ItemUtil.h"
#include <stdio.h>
#include "Properties.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "VariableManager.h"
#include "Guild.h"
#include "GuildManager.h"
//#include "HolyLandRaceBonus.h"
#include "ZoneUtil.h"
#include "NPCManager.h"
#include "Zone.h"
#include "War.h"
#include "WarSystem.h"
#include "WarScheduler.h"
#include "ClientManager.h"
#include "PCManager.h"
#include "EventRefreshHolyLandPlayer.h"
#include "ShrineInfoManager.h"
#include "EffectHasBloodBible.h"
#include "CastleSkillInfo.h"
#include "GamePlayer.h"
#include "NPC.h"

#include "DB.h"
#include "StringPool.h"

#include "Skill.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCModifyInformation.h"

CastleInfo::CastleInfo() : m_Name(""), m_BonusOptionList() , m_CastleZoneIDList()
{
	m_ZoneID = 0;
	m_ShrineID = 0;
	m_GuildID = 0;
	m_ItemTaxRatio = 0;
	m_EntranceFee = 0;
	m_TaxBalance = 0;
}

CastleInfo::~CastleInfo()
{
}

Gold_t CastleInfo::increaseTaxBalance( Gold_t tax )
{
	if( tax > GUILD_TAX_BALANCE_MAX - m_TaxBalance ) // 총합이 오버할 경우
	{
		tax = GUILD_TAX_BALANCE_MAX - m_TaxBalance;
	}

	m_TaxBalance = min( GUILD_TAX_BALANCE_MAX, m_TaxBalance + tax );

	return m_TaxBalance;
}

Gold_t CastleInfo::decreaseTaxBalance( Gold_t tax )
{
	if( tax > m_TaxBalance ) tax = m_TaxBalance;

	m_TaxBalance = max( 0, (int)m_TaxBalance - (int)tax );
	return m_TaxBalance;
}

Gold_t CastleInfo::increaseTaxBalanceEx( Gold_t tax )
	throw(Error)
{
	__BEGIN_TRY

	static char query[100];

	increaseTaxBalance(tax);

	if( !isCommon() )
	{
		sprintf( query, "TaxBalance=%d", (int)getTaxBalance() );
		g_pCastleInfoManager->tinysave( getZoneID(), query );
	}

	return getTaxBalance();

	__END_CATCH
}

Gold_t CastleInfo::decreaseTaxBalanceEx( Gold_t tax )
	throw(Error)
{
	__BEGIN_TRY

	static char query[100];

	decreaseTaxBalance(tax);

	if( !isCommon() )
	{
		sprintf( query, "TaxBalance=%d", (int)getTaxBalance() );
		g_pCastleInfoManager->tinysave( getZoneID(), query );
	}
	
	return getTaxBalance();

	__END_CATCH
}

void CastleInfo::setOptionTypeList( const string& options )
	throw()
{
	__BEGIN_TRY

	makeOptionList( options, m_BonusOptionList );

	__END_CATCH
}

void CastleInfo::setZoneIDList( const string& zoneIDs ) 
	throw()
{
	__BEGIN_TRY

	makeZoneIDList( zoneIDs, m_CastleZoneIDList );

	__END_CATCH
}

void CastleInfo::setResurrectPosition( ResurrectPriority resurrectPriority, const ZONE_COORD& zoneCoord )
{
	m_ResurrectPosition[resurrectPriority].set( zoneCoord.id, zoneCoord.x, zoneCoord.y );
}

void CastleInfo::getResurrectPosition( ResurrectPriority resurrectPriority, ZONE_COORD& zoneCoord )
{
	zoneCoord.set( m_ResurrectPosition[resurrectPriority].id, m_ResurrectPosition[resurrectPriority].x, m_ResurrectPosition[resurrectPriority].y );
}

void CastleInfo::broadcast(Packet* pPacket) const
	throw (Error)
{
	__BEGIN_TRY

	Assert( pPacket != NULL );

	list<ZoneID_t>::const_iterator itr = m_CastleZoneIDList.begin();

	for ( ; itr != m_CastleZoneIDList.end() ; itr++)
	{
		Zone* pCastleZone = getZoneByZoneID( *itr );
		pCastleZone->broadcastPacket( pPacket );
	}

	__END_CATCH
}

bool CastleInfo::isCastleZone(ZoneID_t targetZoneID) const 
	throw (Error)
{
	__BEGIN_TRY

	list<ZoneID_t>::const_iterator itr = m_CastleZoneIDList.begin();

	for ( ; itr != m_CastleZoneIDList.end() ; itr++)
	{
		ZoneID_t zoneID = *itr;

		if (zoneID==targetZoneID)
			return true;
	}

	return false;

	__END_CATCH
}


string CastleInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "CastleInfo("
		<< "ZoneID:" << m_ZoneID
		<< ",Item Tax Ratie:" << m_ItemTaxRatio
		<< ",Entrance Fee:" << m_EntranceFee
		<< ",Tax Balance:" << m_TaxBalance
		<< ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
CastleInfoManager::CastleInfoManager () 
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
CastleInfoManager::~CastleInfoManager () 
{
	__BEGIN_TRY

	hash_map< ZoneID_t , CastleInfo *>::iterator itr = m_CastleInfos.begin();
	for (; itr != m_CastleInfos.end(); itr++)
	{
		CastleInfo* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	// 해쉬맵안에 있는 모든 pair 들을 삭제한다.
	m_CastleInfos.clear();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////////////
// initialize zone info manager
//////////////////////////////////////////////////////////////////////////////
void CastleInfoManager::init () 
	throw (Error)
{
	__BEGIN_TRY

	// init == load
	load();
			
	__END_CATCH
}

	
//void testMaxMemory();

//////////////////////////////////////////////////////////////////////////////
// load from database
//////////////////////////////////////////////////////////////////////////////
void CastleInfoManager::load ()
	throw (Error)
{
	__BEGIN_TRY

	clearCastleZoneIDs();

	Statement* pStmt = NULL;

	BEGIN_DB
	{

		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT ZoneID, ShrineID, GuildID, Name, Race, ItemTaxRatio, EntranceFee, TaxBalance, BonusOptionType, FirstResurrectZoneID, FirstResurrectX, FirstResurrectY, SecondResurrectZoneID, SecondResurrectX, SecondResurrectY, ThirdResurrectZoneID, ThirdResurrectX, ThirdResurrectY, ZoneIDList FROM CastleInfo WHERE ServerID = %d",
			g_pConfig->getPropertyInt( "ServerID" ) );

		ZoneCoord_t x, y;
		ZONE_COORD zoneCoord;

		while (pResult->next()) 
		{
			uint i = 0;

			ZoneID_t zoneID = pResult->getInt(++i);

			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( zoneID );
			Assert( pZoneInfo!=NULL );

			pZoneInfo->setCastle();

			CastleInfo* pCastleInfo = new CastleInfo();
			//cout << "new OK" << endl;

			pCastleInfo->setZoneID( zoneID );
			pCastleInfo->setShrineID( pResult->getInt(++i) );
			pCastleInfo->setGuildID( pResult->getInt(++i) );
			pCastleInfo->setName( pResult->getString(++i) );
			pCastleInfo->setRace( pResult->getInt(++i) );
			pCastleInfo->setItemTaxRatio( pResult->getInt(++i) );
			pCastleInfo->setEntranceFee( pResult->getInt(++i) );
			pCastleInfo->setTaxBalance( pResult->getInt(++i) );
			pCastleInfo->setOptionTypeList( pResult->getString(++i) );

			zoneID	= pResult->getInt( ++i );
			x		= pResult->getInt( ++i );
			y		= pResult->getInt( ++i );

			zoneCoord.set( zoneID, x, y );
			pCastleInfo->setResurrectPosition( CastleInfo::CASTLE_RESURRECT_PRIORITY_FIRST, zoneCoord );

			zoneID	= pResult->getInt( ++i );
			x		= pResult->getInt( ++i );
			y		= pResult->getInt( ++i );

			zoneCoord.set( zoneID, x, y );
			pCastleInfo->setResurrectPosition( CastleInfo::CASTLE_RESURRECT_PRIORITY_SECOND, zoneCoord );

			zoneID	= pResult->getInt( ++i );
			x		= pResult->getInt( ++i );
			y		= pResult->getInt( ++i );

			zoneCoord.set( zoneID, x, y );
			pCastleInfo->setResurrectPosition( CastleInfo::CASTLE_RESURRECT_PRIORITY_THIRD, zoneCoord );

			pCastleInfo->setZoneIDList( pResult->getString(++i) );

			addCastleInfo(pCastleInfo);

			cout << pCastleInfo->toString().c_str() << endl;

		}
			
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}

void CastleInfoManager::save( ZoneID_t zoneID )
	throw(Error)
{
	__BEGIN_TRY

	CastleInfo* pCastleInfo = getCastleInfo( zoneID );
	if( pCastleInfo == NULL ) return;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
			"UPDATE CastleInfo SET GuildID=%d, Name='%s', Race=%d, ItemTaxRatio=%d, EntranceFee=%d, TaxBalance=%d WHERE ServerID=%d AND ZoneID=%d",
							(int)pCastleInfo->getGuildID(), 
							pCastleInfo->getName().c_str(), 
							(int)pCastleInfo->getRace(), 
							pCastleInfo->getItemTaxRatio(), 
							(int)pCastleInfo->getEntranceFee(), 
							(int)pCastleInfo->getTaxBalance(), 
							(int)g_pConfig->getPropertyInt( "ServerID" ),
							(int)zoneID );

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
// add zone info to zone info manager
//////////////////////////////////////////////////////////////////////////////
void CastleInfoManager::addCastleInfo (CastleInfo* pCastleInfo) 
	throw (Error)
{
	__BEGIN_TRY

	// 일단 같은 아이디의 존이 있는지 체크해본다.
	hash_map< ZoneID_t , CastleInfo *>::iterator itr = m_CastleInfos.find(pCastleInfo->getZoneID());
	
	if (itr != m_CastleInfos.end())
		// 똑같은 아이디가 이미 존재한다는 소리다. - -;
		throw Error("duplicated zone id");

	m_CastleInfos[ pCastleInfo->getZoneID() ] = pCastleInfo;

	// 성과 관련된 모든 ZoneID를 등록한다.
	const list<ZoneID_t>& zoneIDs = pCastleInfo->getZoneIDList();
	list<ZoneID_t>::const_iterator iZoneID = zoneIDs.begin();

	for (; iZoneID!=zoneIDs.end(); iZoneID++)
	{
		ZoneID_t zoneID = *iZoneID;
		setCastleZoneID(zoneID, pCastleInfo->getZoneID());
	}

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// Delete zone info from zone info manager
//////////////////////////////////////////////////////////////////////////////
void CastleInfoManager::deleteCastleInfo (ZoneID_t zoneID) 
	throw (Error)
{
	__BEGIN_TRY
		
	hash_map< ZoneID_t , CastleInfo *>::iterator itr = m_CastleInfos.find(zoneID);
	
	if (itr != m_CastleInfos.end()) 
	{
		// 존을 삭제한다.
		SAFE_DELETE(itr->second);

		// pair를 삭제한다.
		m_CastleInfos.erase(itr);
	} 
	else 
	{
		// 그런 존 아이디를 찾을 수 없었을 때
		return;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get zone from zone info manager
//////////////////////////////////////////////////////////////////////////////
CastleInfo* CastleInfoManager::getCastleInfo (ZoneID_t zoneID) const
	throw (Error)
{
	__BEGIN_TRY
		
	CastleInfo* pCastleInfo = NULL;

	hash_map< ZoneID_t , CastleInfo *>::const_iterator itr = m_CastleInfos.find(zoneID);
	
	if (itr != m_CastleInfos.end()) {

		pCastleInfo = itr->second;

	} else {

		// 그런 존 아이디를 찾을 수 없었을 때

		return NULL;

	}

	return pCastleInfo;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string CastleInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "CastleInfoManager(";

	if (m_CastleInfos.empty()) msg << "EMPTY";
	else 
	{
		for (hash_map< ZoneID_t , CastleInfo* >::const_iterator itr = m_CastleInfos.begin() ; itr != m_CastleInfos.end() ; itr ++) 
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

bool CastleInfoManager::modifyCastleOwner(ZoneID_t zoneID, PlayerCreature* pPC )
	throw(Error)
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	Race_t 		race 	= pPC->getRace();
	GuildID_t 	guildID = pPC->getGuildID();

	return modifyCastleOwner( zoneID, race, guildID );

	__END_CATCH
}

bool CastleInfoManager::modifyCastleOwner(ZoneID_t zoneID, Race_t race, GuildID_t guildID )
	throw(Error)
{
	__BEGIN_TRY

	CastleInfo* pCastleInfo = getCastleInfo( zoneID );
	if( pCastleInfo == NULL ) return false;

	Race_t oldRace = pCastleInfo->getRace();

	pCastleInfo->setGuildID( guildID );
	pCastleInfo->setRace( race );
	pCastleInfo->setTaxBalance( 0 );

	Zone* pZone = getZoneByZoneID(zoneID);

	if( pCastleInfo->isCommon() )
	{
		pCastleInfo->setEntranceFee( g_pVariableManager->getVariable( COMMON_CASTLE_ENTRANCE_FEE ) );
		setItemTaxRatio( pZone, g_pVariableManager->getVariable( COMMON_CASTLE_ITEM_TAX_RATIO ) );
	}
	else
	{
		pCastleInfo->setEntranceFee( g_pVariableManager->getVariable( GUILD_CASTLE_ENTRANCE_FEE ) );
		setItemTaxRatio( pZone, g_pVariableManager->getVariable( GUILD_CASTLE_ITEM_TAX_RATIO ) );
	}

	StringStream msg;

	msg << "GuildID = " << (int)pCastleInfo->getGuildID()
		<< ",Race = " << (int)pCastleInfo->getRace()
		<< ",TaxBalance = " << (int)pCastleInfo->getTaxBalance()
		<< ",ItemTaxRatio = " << (int)pCastleInfo->getItemTaxRatio()
		<< ",EntranceFee = " << (int)pCastleInfo->getEntranceFee();

	if( tinysave( zoneID, msg.toString() ) )
	{
//		StringStream msg;
		char msg[100];
		if( guildID == SlayerCommon )
		{
//			msg << pCastleInfo->getName() << "성이 슬레이어 공용 성이 되었습니다.";
			sprintf( msg, g_pStringPool->c_str( STRID_BECOME_SLAYER_COMMON_CASTLE ),
							pCastleInfo->getName().c_str() );
		}
		else if ( guildID == VampireCommon )
		{
//			msg << pCastleInfo->getName() << "성이 뱀파이어 공용 성이 되었습니다.";
			sprintf( msg, g_pStringPool->c_str( STRID_BECOME_VAMPIRE_COMMON_CASTLE ),
							pCastleInfo->getName().c_str() );
		}
		else if ( guildID == OustersCommon )
		{
			sprintf( msg, "%s 성이 아우스터즈 공용 성이 되었습니다.", pCastleInfo->getName().c_str() );
		}
		else
		{
			Guild* pGuild = g_pGuildManager->getGuild( guildID );

			if( pGuild == NULL )
			{
				filelog( "CastleError.log", "알 수 없는 길드ID : %d", (int)guildID );
			}
			else
			{
				if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
				{
//					msg << pGuild->getName() << " 팀이 ";
					sprintf( msg, g_pStringPool->c_str( STRID_BECOME_SLAYER_GUILD_CASTLE ),
								pGuild->getName().c_str(), pCastleInfo->getName().c_str() );
				}
				else
				{
//					msg << pGuild->getName() << " 클랜이 ";
					sprintf( msg, g_pStringPool->c_str( STRID_BECOME_VAMPIRE_GUILD_CASTLE ),
								pGuild->getName().c_str(), pCastleInfo->getName().c_str() );
				}
			}

//			msg << pCastleInfo->getName() << " 성을 점령했습니다.";
		}

		// 성을 소유한 종족이 바뀐 경우의 처리
		if ( oldRace != race )
		{
			// 성 관련 보너스 재설정
			//g_pHolyLandRaceBonus->refresh();

			// [NPC 재설정] --> War에서 한다.
			/*
			Zone* pZone = getZoneByZoneID( zoneID );

			// 성의 NPC를 모두 지운다.
			pZone->deleteNPCs( oldRace );

			// 성의 NPC를 다시 Load한다.
			pZone->loadNPCs( race );
			*/

			// 성의 전쟁 스케쥴을 모두 취소한다.
			WarScheduler* pWarScheduler = pZone->getWarScheduler();
			Assert(pWarScheduler!=NULL);

			// 길드전 스케쥴을 모두 취소한다.
			pWarScheduler->cancelGuildSchedules();
		}

		filelog( "WarLog.txt", "[CastleZoneID:%u]%s", (uint)pCastleInfo->getZoneID(), msg );

		// Holy Land Race Bonus 를 Player 에게 바로 적용되도록 한다.
		EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
		pEvent->setDeadline(0);
		g_pClientManager->addEvent( pEvent );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setType( SYSTEM_MESSAGE_HOLY_LAND );
		gcSystemMessage.setMessage( msg );
		g_pZoneGroupManager->broadcast( &gcSystemMessage );
	}

	return true;

	__END_CATCH
}

bool CastleInfoManager::increaseTaxBalance( ZoneID_t zoneID, Gold_t tax )
	throw(Error)
{
	__BEGIN_TRY

	CastleInfo* pCastleInfo = getCastleInfo( zoneID );
	if ( pCastleInfo == NULL) return false;

	Gold_t TaxBalance = pCastleInfo->increaseTaxBalance(tax);

	char str[40];
	sprintf(str, "TaxBalance=%d", (int)TaxBalance );

	return tinysave( zoneID, str );

	__END_CATCH
}
bool CastleInfoManager::decreaseTaxBalance( ZoneID_t zoneID, Gold_t tax ) 
	throw(Error)
{
	__BEGIN_TRY

	CastleInfo* pCastleInfo = getCastleInfo( zoneID );
	if ( pCastleInfo == NULL) return false;

	Gold_t TaxBalance = pCastleInfo->decreaseTaxBalance(tax);

	char str[40];
	sprintf(str, "TaxBalance=%d", (int)TaxBalance );

	return tinysave( zoneID, str );

	__END_CATCH
}

bool CastleInfoManager::setItemTaxRatio( Zone* pZone, int itemTaxRatio ) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	CastleInfo* pCastleInfo = getCastleInfo( pZone->getZoneID() );
	if ( pCastleInfo == NULL) return false;

	pCastleInfo->setItemTaxRatio( itemTaxRatio );

	char str[40];
	sprintf(str,"ItemTaxRatio=%d", (int)itemTaxRatio);

	tinysave( pZone->getZoneID(), str );

	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode(NOTICE_EVENT_SHOP_TAX_CHANGE);
	gcNoticeEvent.setParameter((uint)itemTaxRatio);

	pZone->broadcastPacket(&gcNoticeEvent);

	return true;

	__END_CATCH
}

int CastleInfoManager::getItemTaxRatio( const PlayerCreature* pPC, const NPC* pNPC ) const
	throw(Error)
{
	__BEGIN_TRY

	if ( pNPC == NULL ) return 100;

	ZoneID_t castleZoneID = pNPC->getTaxingCastleZoneID();
	if ( castleZoneID == 0 ) return 100;

	Assert(pPC != NULL);
//	Zone* pZone = pPC->getZone();
	const CastleInfo* pCastleInfo = getCastleInfo( castleZoneID );

	if (pCastleInfo != NULL) 
	{
		GuildID_t 	OwnerGuildID = pCastleInfo->getGuildID();
		GuildID_t 	PlayerGuildID = pPC->getGuildID();
		int			ItemTaxRatio = pCastleInfo->getItemTaxRatio();
		

		if ( PlayerGuildID == SlayerCommon 
			 || PlayerGuildID == VampireCommon
			 || PlayerGuildID == OustersCommon
			 || PlayerGuildID != OwnerGuildID )
		{
			return ItemTaxRatio;
		}
	}

	return 100;

	__END_CATCH
}

Gold_t CastleInfoManager::getEntranceFee( ZoneID_t zoneID, PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

    Assert(pPC != NULL);
    const CastleInfo* pCastleInfo = getCastleInfo( zoneID );

	// 성이 전쟁 중이라면 입장료가 0 이다.
    if ( pCastleInfo != NULL && !g_pWarSystem->hasCastleActiveWar( zoneID ) && !g_pWarSystem->hasActiveRaceWar() )
    {
        GuildID_t   OwnerGuildID = pCastleInfo->getGuildID();
        GuildID_t   PlayerGuildID = pPC->getGuildID();
        Gold_t      EntranceFee = pCastleInfo->getEntranceFee();

        if ( PlayerGuildID == SlayerCommon
             || PlayerGuildID == VampireCommon
             || PlayerGuildID == OustersCommon
             || PlayerGuildID != OwnerGuildID )
        {
            return EntranceFee;
        }
    }

    return 0;

	__END_CATCH
}

bool CastleInfoManager::isCastleMember( PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

    Assert(pPC != NULL);
    Zone* pZone = pPC->getZone();
    const CastleInfo* pCastleInfo = getCastleInfo( pZone->getZoneID() );

    if (pCastleInfo != NULL)
    {
        GuildID_t   OwnerGuildID = pCastleInfo->getGuildID();
        GuildID_t   PlayerGuildID = pPC->getGuildID();

        if ( PlayerGuildID == SlayerCommon
             || PlayerGuildID == VampireCommon
			 || PlayerGuildID == OustersCommon
             || PlayerGuildID != OwnerGuildID )
        {
            return false;
        }
    }

    return true;

	__END_CATCH
}

bool CastleInfoManager::isCastleMember( ZoneID_t zoneID, PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

    Assert(pPC != NULL);
    const CastleInfo* pCastleInfo = getCastleInfo( zoneID );

    if (pCastleInfo != NULL)
    {
        GuildID_t   OwnerGuildID = pCastleInfo->getGuildID();
        GuildID_t   PlayerGuildID = pPC->getGuildID();

        if ( PlayerGuildID == SlayerCommon
             || PlayerGuildID == VampireCommon
             || PlayerGuildID == OustersCommon
             || PlayerGuildID != OwnerGuildID )
        {
            return false;
        }
    }
	else
		return false;

    return true;

	__END_CATCH
}

bool CastleInfoManager::hasOtherBloodBible( ZoneID_t zoneID, PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	if ( pPC->isFlag( Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE ) )
	{
		// 이 성에 해당하지 않는 피의 성서를 들고 있으면 못 들어가게 해야 한다.
		EffectHasBloodBible* pEffect = dynamic_cast<EffectHasBloodBible*>( pPC->findEffect( Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE ) );
		Assert( pEffect != NULL );
		
		int part = pEffect->getPart();
		ShrineSet* pShrineSet = g_pShrineInfoManager->getShrineSet( part );
		if ( pShrineSet->getVampireGuardShrine().getZoneID() == zoneID
		||	 pShrineSet->getSlayerGuardShrine().getZoneID() == zoneID
		||	 pShrineSet->getOustersGuardShrine().getZoneID() == zoneID )
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}

	__END_CATCH
}
	
bool CastleInfoManager::isPossibleEnter( ZoneID_t zoneID, PlayerCreature* pPC ) const
	throw(Error)
{

    __BEGIN_TRY

    Assert(pPC != NULL);
    const CastleInfo* pCastleInfo = getCastleInfo( zoneID );

    if (pCastleInfo != NULL)
    {
        Race_t   OwnerRace = pCastleInfo->getRace();
        Race_t   PlayerRace = pPC->getRace();//(pPC->isSlayer()? RACE_SLAYER : RACE_VAMPIRE);

		if ( g_pWarSystem->hasActiveRaceWar() )
		{
			if ( hasOtherBloodBible( zoneID, pPC ) )
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if ( OwnerRace == PlayerRace ) 
		{
			return true;
		}
		return false;
    }

    return true;

    __END_CATCH

}

bool CastleInfoManager::canPortalActivate( ZoneID_t zoneID, PlayerCreature* pPC ) const 
	throw(Error)
{
	__BEGIN_TRY

	const CastleInfo* pCastleInfo = getCastleInfo( zoneID );

	if ( pCastleInfo == NULL )
	{
		filelog( "CastleError.log", "CastleInfoManager::canPortalActivate() CastleInfo(%d)가 없습니다.", (int)zoneID );
		Assert( false );
	}

	if ( g_pWarSystem->hasActiveRaceWar() )
	{
		if ( hasOtherBloodBible( zoneID, pPC ) )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	if ( g_pWarSystem->hasCastleActiveWar( zoneID ) )
	{
		War* pWar = g_pWarSystem->getActiveWar( zoneID );
		
		if ( pWar != NULL )
		{
			return pPC->getRace() == pCastleInfo->getRace();
		}
	}

	return false;

	__END_CATCH
}

CastleInfo* CastleInfoManager::getGuildCastleInfo( GuildID_t guildID ) const
	throw(Error)
{

	__BEGIN_TRY

	if (guildID==SlayerCommon 
		|| guildID==VampireCommon
		|| guildID==OustersCommon
		)
	{
		return NULL;
	}

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		if (pCastleInfo->getGuildID()==guildID)
		{
			return pCastleInfo;
		}
	}
	
	return NULL;

	__END_CATCH

}

list<CastleInfo*> CastleInfoManager::getGuildCastleInfos( GuildID_t guildID ) const
	throw(Error)
{

	__BEGIN_TRY

	list<CastleInfo*> castleList;

	if (guildID==SlayerCommon 
		|| guildID==VampireCommon
		|| guildID==OustersCommon
		)
	{
		return castleList;
	}

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		if (pCastleInfo->getGuildID()==guildID)
		{
			castleList.push_back(pCastleInfo);
		}
	}
	
	return castleList;

	__END_CATCH

}

bool CastleInfoManager::getResurrectPosition( PlayerCreature* pPC, ZONE_COORD& zoneCoord ) 
	throw (Error)
{
	CastleInfo::ResurrectPriority resurrectPriority = CastleInfo::CASTLE_RESURRECT_PRIORITY_SECOND;

	ZoneID_t castleZoneID;
	bool isCastleZone = g_pCastleInfoManager->getCastleZoneID( pPC->getResurrectZoneID(), castleZoneID );

	if (!isCastleZone)
		return false;

	CastleInfo* pCastleInfo = getCastleInfo( castleZoneID );

	if ( pCastleInfo != NULL )
	{
		if ( pCastleInfo->getZoneID() != pPC->getResurrectZoneID() || g_pWarSystem->hasCastleActiveWar( castleZoneID ) )
		{
			// 부활위치가 성밖으로 되어 있는 경우
			// 부활위치가 성에 딸린 던젼으로 되어 있으면 성밖에 부활위치를 지정한 것으로 인식한다.
			// 필살 하드 코딩. 존에 부활 위치를 하나밖에 지정할 수 없어서 이렇게 코딩한다.
			// 아담의 성지 서쪽이나 동쪽 같은 경우에 인근한 두 성의 성밖 부활위치를 모두 지정할 수 없다.ㅡㅡ;
			// 또, 현재 성이 전쟁 중이라면 성밖에서 부활하도록 한다.
			if ( isCastleMember( castleZoneID, pPC ) )
				resurrectPriority = CastleInfo::CASTLE_RESURRECT_PRIORITY_SECOND;
			else
				resurrectPriority = CastleInfo::CASTLE_RESURRECT_PRIORITY_THIRD;
		}
		else
		{
			// 부활위치가 성안으로 되어 있는 경우
			// 길드원이 아니면 요금을 받는다. 요금이 모자라면 성밖에 부활 시킨다.
			if ( isCastleMember( castleZoneID, pPC ) )
				resurrectPriority = CastleInfo::CASTLE_RESURRECT_PRIORITY_FIRST;
			else
			{
				Gold_t fee = pCastleInfo->getEntranceFee();
				Gold_t remain = pPC->getGold();

				if ( remain < fee )
				{
					// 요금이 부족한 경우 성밖에 부활 시킨다.
					resurrectPriority = CastleInfo::CASTLE_RESURRECT_PRIORITY_THIRD;
				}
				else
				{
					// 요금이 있다면 요금을 받고 성안에 부활 시킨다.
					pPC->decreaseGoldEx( fee );
					increaseTaxBalance( pCastleInfo->getZoneID(), fee );

					GCModifyInformation gcMI;
					gcMI.addLongData( MODIFY_GOLD, pPC->getGold() );

					GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
					if ( pGamePlayer->getPlayerStatus() == GPS_NORMAL )
						pGamePlayer->sendPacket( &gcMI );

					resurrectPriority = CastleInfo::CASTLE_RESURRECT_PRIORITY_FIRST;
				}
			}
		}
	}
	else
	{
		return false;
	}

	pCastleInfo->getResurrectPosition( resurrectPriority, zoneCoord );

	return true;
}

bool CastleInfoManager::tinysave( ZoneID_t zoneID, const string& query )
	throw(Error)
{
	__BEGIN_TRY

	CastleInfo* pCastleInfo = getCastleInfo( zoneID );
	if( pCastleInfo == NULL ) return false;

	Statement* pStmt = NULL;
	bool isAffected = false;

	BEGIN_DB
	{
		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
			"UPDATE CastleInfo SET %s WHERE ZoneID=%d AND ServerID=%d",
			query.c_str(), pCastleInfo->getZoneID(), g_pConfig->getPropertyInt("ServerID") );

		if( pStmt->getAffectedRowCount() > 0 )
			isAffected = true;

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return isAffected;

	__END_CATCH
}

void    CastleInfoManager::deleteAllNPCs() 
	throw (Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		Zone* pZone = getZoneByZoneID( pCastleInfo->getZoneID() );
		Assert( pZone != NULL );

		__ENTER_CRITICAL_SECTION( (*pZone) )

		// NPC를 모두 지운다.
		pZone->deleteNPCs( RACE_SLAYER );
		pZone->deleteNPCs( RACE_VAMPIRE );

		__LEAVE_CRITICAL_SECTION( (*pZone) )
	}

	__END_CATCH
}

void    CastleInfoManager::releaseAllSafeZone() 
	throw (Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		Zone* pZone = getZoneByZoneID( pCastleInfo->getZoneID() );
		Assert( pZone != NULL );

		__ENTER_CRITICAL_SECTION( (*pZone) )

		pZone->releaseSafeZone();

		__LEAVE_CRITICAL_SECTION( (*pZone) )
	}

	__END_CATCH
}

void    CastleInfoManager::resetAllSafeZone() 
	throw (Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		Zone* pZone = getZoneByZoneID( pCastleInfo->getZoneID() );
		Assert( pZone != NULL );

		__ENTER_CRITICAL_SECTION( (*pZone) )

		pZone->resetSafeZone();

		__LEAVE_CRITICAL_SECTION( (*pZone) )
	}

	__END_CATCH
}

void	CastleInfoManager::transportAllOtherRace()
	throw (Error)
{	
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		// 성과 관련된 모든 ZoneID를 등록한다.
		const list<ZoneID_t>& zoneIDs = pCastleInfo->getZoneIDList();
		list<ZoneID_t>::const_iterator iZoneID = zoneIDs.begin();

		for (; iZoneID!=zoneIDs.end(); iZoneID++)
		{
			ZoneID_t zoneID = *iZoneID;

			Zone* pZone = getZoneByZoneID( zoneID );
			Assert( pZone != NULL );

			__ENTER_CRITICAL_SECTION( (*pZone) )

			// 종족전쟁의 패배자들은 부활 위치로 모두 쫓아보낸다.
			Race_t otherRace = (pCastleInfo->getRace()==RACE_SLAYER? RACE_VAMPIRE : RACE_SLAYER);

			ZONE_COORD zoneCoord;
			pCastleInfo->getResurrectPosition( CastleInfo::CASTLE_RESURRECT_PRIORITY_SECOND, zoneCoord);

			PCManager* pPCManager = (PCManager*)(pZone->getPCManager());
			pPCManager->transportAllCreatures( zoneCoord.id, zoneCoord.x, zoneCoord.y, otherRace );

			__LEAVE_CRITICAL_SECTION( (*pZone) )
		}
	}

	__END_CATCH

}

void	CastleInfoManager::loadAllNPCs()
	throw (Error)
{	
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		Zone* pZone = getZoneByZoneID( pCastleInfo->getZoneID() );
		Assert( pZone != NULL );

		__ENTER_CRITICAL_SECTION( (*pZone) )

		// NPC 로드
		pZone->loadNPCs( pCastleInfo->getRace() );

		__LEAVE_CRITICAL_SECTION( (*pZone) )
	}

	__END_CATCH

}

ZoneID_t    CastleInfoManager::getCastleZoneID(ShrineID_t shrineID) const
	throw (Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for (; itr!=m_CastleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;		

		if (pCastleInfo->getShrineID()==shrineID)
		{
			return pCastleInfo->getZoneID();
		}
	}

	StringStream msg;
	msg << "그런 ShrineID(" << (int)shrineID << ")가 없습니다.";

	throw Error(msg.toString());

	return 0;

	__END_CATCH
}

void CastleInfoManager::broadcastShrinePacket(ShrineID_t shrineID, Packet* pPacket) const
	throw (Error)
{
	__BEGIN_TRY

	ZoneID_t castleZoneID = getCastleZoneID( shrineID );

	const CastleInfo* pCastleInfo = getCastleInfo( castleZoneID );
	Assert(pCastleInfo!=NULL);

	pCastleInfo->broadcast( pPacket );

	__END_CATCH
}

bool CastleInfoManager::isCastleZone(ZoneID_t castleZoneID, ZoneID_t targetZoneID) const
	throw (Error)
{
	__BEGIN_TRY

	const CastleInfo* pCastleInfo = getCastleInfo( castleZoneID );
	Assert(pCastleInfo!=NULL);

	return pCastleInfo->isCastleZone( targetZoneID );

	__END_CATCH
}

bool CastleInfoManager::isCastleZone(ZoneID_t zoneID) const
{
	__BEGIN_TRY

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = m_CastleInfos.begin();

	for ( ; itr != m_CastleInfos.end() ; ++itr )
	{
		if ( itr->second->isCastleZone( zoneID ) ) return true;
	}

	return false;

	__END_CATCH
}

void  
CastleInfoManager::clearCastleZoneIDs()
	throw (Error)
{
	__BEGIN_TRY

	m_CastleZoneIDs.clear();

	__END_CATCH
}

bool 
CastleInfoManager::getCastleZoneID(ZoneID_t zoneID, ZoneID_t &castleZoneID) const
	throw (Error)
{
	__BEGIN_TRY

	hash_map<ZoneID_t, ZoneID_t>::const_iterator itr = m_CastleZoneIDs.find( zoneID );

	if (itr!=m_CastleZoneIDs.end())
	{
		castleZoneID = itr->second;
		return true;
	}

	return false;

	__END_CATCH
}

void  
CastleInfoManager::setCastleZoneID(ZoneID_t zoneID, ZoneID_t castleZoneID)
	throw (Error)
{
	__BEGIN_TRY

	m_CastleZoneIDs[zoneID] = castleZoneID;

	__END_CATCH
}

bool        
CastleInfoManager::isSameCastleZone(ZoneID_t zoneID1, ZoneID_t zoneID2) const 
	throw (Error)
{
	__BEGIN_TRY

	ZoneID_t castleZoneID1, castleZoneID2;

	bool isCastle1 = getCastleZoneID(zoneID1, castleZoneID1);
	bool isCastle2 = getCastleZoneID(zoneID2, castleZoneID2);

	// 한 군데라도 성이 아니면 같은 성에 속한 존이 아니다.
	if (!isCastle1 || !isCastle2)
		return false;

	return castleZoneID1==castleZoneID2;

	__END_CATCH
}

SkillType_t CastleInfoManager::getCastleSkillType( ZoneID_t zoneID, GuildID_t guildID ) const
	throw (Error)
{
	__BEGIN_TRY

    const CastleInfo* pCastleInfo = getCastleInfo( zoneID );

    if (pCastleInfo != NULL)
    {
        GuildID_t   OwnerGuildID = pCastleInfo->getGuildID();

		// 성의 소유 길드가 아니면 없다.
        if ( guildID == SlayerCommon
             || guildID == VampireCommon
             || guildID == OustersCommon
             || guildID != OwnerGuildID )
        {
            return SKILL_MAX;
        }

		// 성이 길드 전쟁 중이라면 없다.
		if ( g_pWarSystem->hasCastleActiveWar( zoneID ) )
		{
			return SKILL_MAX;
		}

		return g_pCastleSkillInfoManager->getSkillType( zoneID );
    }

    return SKILL_MAX;

	__END_CATCH
}

// global variable definition
CastleInfoManager* g_pCastleInfoManager = NULL;
