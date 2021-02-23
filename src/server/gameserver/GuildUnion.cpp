#include "GuildUnion.h"
#include "DB.h"
#include "Gpackets/GGCommand.h"
#include "LoginServerManager.h"
#include "GameServer.h"
#include "GameServerInfoManager.h"
#include "PacketUtil.h"
#include <stdio.h>

#include "Player.h"
#include "PCFinder.h"
#include "Guild.h"
#include "GuildManager.h"
#include "VariableManager.h"
#include "Gpackets/GCModifyInformation.h"
GuildUnion::~GuildUnion()
{
	//cout << "GuildUnion : DELETE!!!" << endl;

			  
}

bool GuildUnion::hasGuild( GuildID_t gID ) const
{
	if ( gID == m_MasterGuildID ) return true;

	if ( findGuildItr( gID ) != m_Guilds.end() ) return true;

	return false;
}

bool GuildUnion::addGuild( GuildID_t gID ) throw(Error)
{
	if ( hasGuild( gID ) ) return false;

	m_Guilds.push_back( gID );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT INTO GuildUnionMember (UnionID, OwnerGuildID) VALUES (%u, %u)", m_UnionID, gID);
		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt );

	return true;
}

bool GuildUnion::removeGuild( GuildID_t gID ) throw(Error)
{
	if ( m_MasterGuildID == gID ) return false;

	list<GuildID_t>::iterator itr = findGuildItr( gID );
	if ( itr == m_Guilds.end() ) return false;

	m_Guilds.erase( itr );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM GuildUnionMember WHERE UnionID = %u and OwnerGuildID = %u", m_UnionID, gID);
		if ( pStmt->getAffectedRowCount() < 1 )
		{
			filelog("GuildUnion.log", "[%u:%u] 탈퇴하려는데 해당 레코드가 없습니다.", m_UnionID, gID);
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt );

	return true;
}

void GuildUnion::create() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "INSERT INTO GuildUnionInfo (MasterGuildID) VALUES (%u)", m_MasterGuildID );

		m_UnionID = pStmt->getInsertID();

		list<GuildID_t>::iterator itr = m_Guilds.begin();

		for ( ; itr != m_Guilds.end() ; ++itr )
		{
			pStmt->executeQuery( "INSERT INTO GuildUnionMember (UnionID, OwnerGuildID) VALUES (%u, %u)", m_UnionID, (*itr) );
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt );

	__END_CATCH
}

void GuildUnion::destroy() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "DELETE FROM GuildUnionInfo WHERE UnionID = %u", m_UnionID );
		pStmt->executeQuery( "DELETE FROM GuildUnionMember WHERE UnionID = %u", m_UnionID );
	}
	END_DB( pStmt );

	__END_CATCH
}

GuildUnionManager::GuildUnionManager()
{
 m_Mutex.setName("GuildUnionManager");
}

GuildUnionManager::~GuildUnionManager()
{
	list<GuildUnion*>::iterator itr = m_GuildUnionList.begin();

	for ( ; itr != m_GuildUnionList.end() ; ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

}

void GuildUnionManager::addGuildUnion( GuildUnion* pUnion )
{
	m_GuildUnionList.push_back( pUnion );

	m_UnionIDMap[pUnion->getUnionID()] = pUnion;
	m_GuildUnionMap[pUnion->getMasterGuildID()] = pUnion;

	list<GuildID_t>::iterator itr = pUnion->m_Guilds.begin();

	for ( ; itr != pUnion->m_Guilds.end() ; ++itr )
	{
		m_GuildUnionMap[*itr] = pUnion;
	}
}

void GuildUnionManager::sendModifyUnionInfo(uint gID)	throw(Error)
{
	char	Msg[80];
	sprintf(Msg,"*modifyunioninfo %d", gID);

	GGCommand ggCommand;
	ggCommand.setCommand(Msg);


// 각 server로 보낸다.
	HashMapGameServerInfo** pGameServerInfos = g_pGameServerInfoManager->getGameServerInfos();


	static int myWorldID = g_pConfig->getPropertyInt("WorldID");
	static int myServerID = g_pConfig->getPropertyInt("ServerID");

	int maxWorldID = g_pGameServerInfoManager->getMaxWorldID();
	int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();


	for (int worldID=1; worldID<maxWorldID; worldID++)
	{
		for (int groupID=0; groupID<maxServerGroupID; groupID++)
		{
			HashMapGameServerInfo& gameServerInfo = pGameServerInfos[worldID][groupID];

			if (!gameServerInfo.empty())
			{
				HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
				for (; itr != gameServerInfo.end(); itr++)
				{
					GameServerInfo* pGameServerInfo = itr->second;

					if (pGameServerInfo->getWorldID()==myWorldID)
					{
						// 현재 서버가 아닌 경우에만..(위에서 처리했으므로)
						if (pGameServerInfo->getGroupID()==myServerID)
						{
						}
						else
						{
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );
						}
					}
				}
			}
		}
	}


	

}

void GuildUnionManager::sendRefreshCommand() throw(Error)
{
	GGCommand ggCommand;
	ggCommand.setCommand( "*refreshguildunion" );


	// 각 server로 보낸다.
	HashMapGameServerInfo** pGameServerInfos = g_pGameServerInfoManager->getGameServerInfos();


	static int myWorldID = g_pConfig->getPropertyInt("WorldID");
	static int myServerID = g_pConfig->getPropertyInt("ServerID");

	int maxWorldID = g_pGameServerInfoManager->getMaxWorldID();
	int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();


	for (int worldID=1; worldID<maxWorldID; worldID++)
	{
		for (int groupID=0; groupID<maxServerGroupID; groupID++)
		{
			HashMapGameServerInfo& gameServerInfo = pGameServerInfos[worldID][groupID];

			if (!gameServerInfo.empty())
			{
				HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
				for (; itr != gameServerInfo.end(); itr++)
				{
					GameServerInfo* pGameServerInfo = itr->second;

					if (pGameServerInfo->getWorldID()==myWorldID)
					{
						// 현재 서버가 아닌 경우에만..(위에서 처리했으므로)
						if (pGameServerInfo->getGroupID()==myServerID)
						{
						}
						else
						{
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );
						}
					}
				}
			}
		}
	}

	

}

bool GuildUnionManager::addGuild( uint uID, GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	GuildUnion* pUnion = m_UnionIDMap[uID];
	if ( pUnion == NULL ) return false;

	if ( pUnion->addGuild( gID ) )
	{
		m_GuildUnionMap[gID] = pUnion;
		
		sendRefreshCommand();

		return true;
	}
	else
	{
		return false;
	}

	__END_CATCH
}

bool GuildUnionManager::removeMasterGuild(GuildID_t gID) throw(Error)
{

	__BEGIN_TRY

	// 내가 길드연합장인데..내가 탈퇴한다면..
	// 내가 속한 길드연합을 깨보자..

	GuildUnion* pUnion = m_GuildUnionMap[gID];
	// 내가 마스터인 연합이 있다면 -> 내 연합에 소속된 모든 길드를 out시키고 내 연합을 깨버린다. 
	if(pUnion != NULL)
	{
		
		uint	uID	= pUnion->getUnionID();		// 연합ID
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			Result *pResult = NULL;
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery( "SELECT OwnerGuildID FROM GuildUnionMember WHERE UnionID = %u", uID );
		
			// 아무것도 없다면 이상한거다..
			if (pResult->getRowCount() == 0 )	
			{ 
				SAFE_DELETE( pStmt );
				return false; 
			}

			string	unionMasterID	= g_pGuildManager->getGuild( gID )->getMaster();
			// 각각의 모든 길드들을 연합에서 탈퇴시킨다.	// 모두 지워지면 연합도 알아서 깨진다.
			while ( pResult->next() )
			{
				if ( pUnion->removeGuild( pResult->getInt(1) ) )
				{
					m_GuildUnionMap[gID] = NULL;
					if ( pUnion->m_Guilds.empty() )
					{
						list<GuildUnion*>::iterator itr = find(m_GuildUnionList.begin(), m_GuildUnionList.end(), pUnion);
						if(itr != m_GuildUnionList.end() )
						{
							pUnion->destroy();
							m_GuildUnionList.erase( itr );
							m_GuildUnionMap.erase ( pUnion->getMasterGuildID() );
							m_UnionIDMap.erase 	  ( pUnion->getUnionID() );
				
							SAFE_DELETE( pUnion );
						} //
					} // isEmpty
					sendGCOtherModifyInfoGuildUnionByGuildID( pResult->getInt(1) );
				}	// if
			}	// while
			// 모든 길드를 다 제거한다. 마지막에 남은 길드까지 깨끗히 청소하고 나면

			Creature *pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))

			pTargetCreature = g_pPCFinder->getCreature_LOCKED(unionMasterID);
			if (pTargetCreature!=NULL)
			{
				GCModifyInformation gcModifyInformation2;
				makeGCModifyInfoGuildUnion(&gcModifyInformation2, pTargetCreature);
				pTargetCreature->getPlayer()->sendPacket(&gcModifyInformation2);

			}
			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			// 연합마스터 바뀐정보를 보내줘보자..
			sendGCOtherModifyInfoGuildUnionByGuildID( gID );

			sendRefreshCommand();
		}
		END_DB( pStmt );
	}
	else	// 내가 마스터인 연합이 없다면, 내가 어느연합의 멤버인지를 찾는다. 어느연합의 멤버인지 찾아서 연합에서 제외 
	{
		Statement* pStmt = NULL;
		Statement* pStmt2 = NULL;

		string unionMasterID = "";
		string guildMasterID = "";		
		GuildID_t	unionMasterGuildID = 0;

		BEGIN_DB
		{
			Result *pResult = NULL;
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery( "SELECT UnionID, OwnerGuildID FROM GuildUnionMember WHERE OwnerGuildID = %u", gID );

			// 어디에도 소속되지 않았다면 그냥 나간다.
			if (pResult->getRowCount() == 0 )	
			{ 
				SAFE_DELETE( pStmt );
				return false; 
			}

			// 어딘가에 속해있다면..
			pResult->next();
			
			BEGIN_DB
			{
				Result *pResult2 = NULL;
				pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pResult2 = pStmt->executeQuery( "SELECT MasterGuildID FROM GuildUnionInfo WHERE UnionID = %u", pResult->getInt(1) );

				// 마스터길드의 ID를 찾으면..
				if(pResult2->getRowCount() != 0)
				{
					pResult->next();

					unionMasterGuildID = pResult2->getInt(1);
					unionMasterID	= g_pGuildManager->getGuild( unionMasterGuildID )->getMaster();
					
				}

			}
			END_DB( pStmt2 );

			guildMasterID	= g_pGuildManager->getGuild( gID )->getMaster();
			
			if( removeGuild( pResult->getInt(1), pResult->getInt(2) ) )
			{	
				Creature *pTargetCreature = NULL;		// 해당길드의 장
				Creature *pTargetCreature2 = NULL;		// 연합길드의 장
				
				__ENTER_CRITICAL_SECTION((*g_pPCFinder))

				pTargetCreature = g_pPCFinder->getCreature_LOCKED(guildMasterID);
				if (pTargetCreature!=NULL)
				{
					GCModifyInformation gcModifyInformation2;
					makeGCModifyInfoGuildUnion(&gcModifyInformation2, pTargetCreature);
					pTargetCreature->getPlayer()->sendPacket(&gcModifyInformation2);

				}

				pTargetCreature2 = g_pPCFinder->getCreature_LOCKED(unionMasterID);
				if (pTargetCreature!=NULL)
				{
					GCModifyInformation gcModifyInformation2;
					makeGCModifyInfoGuildUnion(&gcModifyInformation2, pTargetCreature2);
					pTargetCreature2->getPlayer()->sendPacket(&gcModifyInformation2);

				}
				__LEAVE_CRITICAL_SECTION((*g_pPCFinder))



				// 길드마스터 바뀐정보를 보내줘보자..
				sendGCOtherModifyInfoGuildUnionByGuildID( gID );
				// 특정길드가 깨져서 연합에서 remove되었다면 연합마스터에게도 알려야 하겠다.
				sendGCOtherModifyInfoGuildUnionByGuildID( unionMasterGuildID );

				// 길드를 제거 하였으니..다른 서버에도 알려줘야 하겠다.
				sendRefreshCommand();
			}

		}
		END_DB( pStmt );	
	}

	__END_CATCH

	return true;	
}

bool GuildUnionManager::removeGuild( uint uID, GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	GuildUnion* pUnion = m_UnionIDMap[uID];
	if ( pUnion == NULL ) return false;

	if ( pUnion->removeGuild( gID ) )
	{
		m_GuildUnionMap[gID] = NULL;
		if ( pUnion->m_Guilds.empty() )
		{
	
			list<GuildUnion*>::iterator itr = find(m_GuildUnionList.begin(), m_GuildUnionList.end(), pUnion);
			if(itr != m_GuildUnionList.end() )
			{
				pUnion->destroy();
		
				//m_GuildUnionMap[pUnion->getMasterGuildID()] = NULL;
				//m_UnionIDMap[pUnion->getUnionID()] = NULL;
			
				m_GuildUnionList.erase( itr );
				m_GuildUnionMap.erase ( pUnion->getMasterGuildID() );
				m_UnionIDMap.erase 	  ( pUnion->getUnionID() );
			
				SAFE_DELETE( pUnion );
			}
			 
		
		}

		sendRefreshCommand();
		return true;
	}
	else
	{
		return false;
	}

	__END_CATCH
}

void GuildUnionManager::reload() throw(Error)
{

	__ENTER_CRITICAL_SECTION(m_Mutex)

	list<GuildUnion*>::iterator itr = m_GuildUnionList.begin();
	list<GuildUnion*>::iterator endItr = m_GuildUnionList.end();
	
	for ( ; itr != endItr; ++itr ) 
	{
		GuildUnion *pUnion = *itr;
		SAFE_DELETE( pUnion );
	}
	m_GuildUnionList.clear();

	m_GuildUnionMap.clear();
	m_UnionIDMap.clear();
	
	load();

    __LEAVE_CRITICAL_SECTION(m_Mutex)
}

void GuildUnionManager::load() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Statement* pStmt2 = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT UnionID, MasterGuildID FROM GuildUnionInfo");

		while ( pResult->next() )
		{
			uint uID = pResult->getInt(1);
			GuildID_t gID = pResult->getInt(2);

			GuildUnion* pUnion = new GuildUnion( gID );
			pUnion->setUnionID( uID );

			BEGIN_DB
			{
				pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				Result* pResult2 = pStmt2->executeQuery("SELECT OwnerGuildID FROM GuildUnionMember WHERE UnionID = %u", uID);

				while ( pResult2->next() )
				{
					GuildID_t gID2 = pResult2->getInt(1);
					pUnion->m_Guilds.push_back( gID2 );
//					pUnion->addGuild( gID2 );
				}

				SAFE_DELETE( pStmt2 );
			}
			END_DB( pStmt2 )

			addGuildUnion( pUnion );
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )

	__END_CATCH
}

uint GuildUnionOfferManager::offerJoin( GuildID_t gID, GuildID_t masterGID ) throw(Error)
{
	__BEGIN_TRY

	if ( GuildUnionManager::Instance().getGuildUnion( gID ) != NULL ) return ALREADY_IN_UNION;
	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( masterGID );

	Guild *pReqGuild = g_pGuildManager->getGuild(gID);
	Guild *pMasterGuild = g_pGuildManager->getGuild(masterGID);

	if(pReqGuild !=NULL && pMasterGuild !=NULL)
	{
	
		if(pReqGuild->getActiveMemberCount() > MAX_GUILDMEMBER_ACTIVE_COUNT 
			|| pMasterGuild->getActiveMemberCount() > MAX_GUILDMEMBER_ACTIVE_COUNT)
		{
			return TOO_MANY_MEMBER;
		}
	}
	
	//
	if ( pUnion == NULL )
	{
		pUnion = new GuildUnion( masterGID );
		pUnion->create();
		GuildUnionManager::Instance().addGuildUnion( pUnion );
	}
	else if ( pUnion->getMasterGuildID() != masterGID )
	{
		return TARGET_IS_NOT_MASTER;
	}

	if ( hasOffer( gID ) )
	{
		return ALREADY_OFFER_SOMETHING;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// 과거 10일 이내에서 강제 탈퇴한 이력이 있는지 본다
		Result *pResult = pStmt->executeQuery("SELECT COUNT(*) FROM GuildUnionOffer WHERE OfferType='ESCAPE' and OwnerGuildID='%u' and OfferTime >= now() - interval 10 day", gID);
	
		pResult->next();
		
		// 이력이 있으면 패뻐린다.
		if(pResult->getInt(1) > 0)
		{
			SAFE_DELETE( pStmt );	
			return YOU_HAVE_PENALTY;
		}

		
		pResult = pStmt->executeQuery("SELECT COUNT(*) FROM GuildUnionMember WHERE UnionID='%u'", pUnion->getUnionID());
		pResult->next();

		if(pResult->getInt(1) >= g_pVariableManager->getVariable(GUILD_UNION_MAX))
		{
			SAFE_DELETE( pStmt );
			return NOT_ENOUGH_SLOT;
		}
		
		// 10일이 넘은 데이타는 지워버린다.
		pStmt->executeQuery("DELETE FROM GuildUnionOffer WHERE OwnerGuildID='%u' and OfferTime < now() - interval 10 day", gID);
		pStmt->executeQuery("INSERT INTO GuildUnionOffer (UnionID, OfferType, OwnerGuildID, OfferTime) VALUES (%u, 'JOIN', %u, now())", pUnion->getUnionID(), gID);

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return OK;

	__END_CATCH
}

uint GuildUnionOfferManager::offerQuit( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( gID );

	if ( pUnion == NULL )
	{
		return NOT_IN_UNION;
	}
	else if ( pUnion->getMasterGuildID() == gID )
	{
		return MASTER_CANNOT_QUIT;
	}

	if ( hasOffer( gID ) )
	{
		return ALREADY_OFFER_SOMETHING;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT INTO GuildUnionOffer (UnionID, OfferType, OwnerGuildID, OfferTime) VALUES (%u, 'QUIT', %u, now())",
				pUnion->getUnionID(), gID);

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return OK;

	__END_CATCH
}

bool GuildUnionOfferManager::makeOfferList( uint uID, GCUnionOfferList& offerList ) throw(Error)
{
	Statement* pStmt = NULL;
	Statement* pStmt2 = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT OfferType+0, OwnerGuildID, DATE_FORMAT(Offertime,'%%y%%m%%d') FROM GuildUnionOffer WHERE UnionID=%u", uID);
		
	
		//cout << "연합길드 : " << uID << ", GuildUnionOffer return row : " << pResult->getRowCount() << endl;
		
		if (pResult->getRowCount() == 0 )	{ return false; }

		while ( pResult->next() )
		{
			SingleGuildUnionOffer *offer = new SingleGuildUnionOffer;
		
			offer->setGuildType( pResult->getInt(1) );
			offer->setGuildID( pResult->getInt(2) );
			
			DWORD dwDate = pResult->getInt(3);
			offer->setDate( dwDate*100 );

			//cout << "Date : " << (DWORD)offer->getDate() << endl;

			//cout << "TYPE : " << (int)pResult->getInt(1) << endl;

			pStmt2 =  g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			Result* pResult2 = pStmt2->executeQuery("SELECT GuildName, Master FROM GuildInfo WHERE GuildID=%u", pResult->getInt(2) );
			
			if (pResult2->getRowCount() == 0 )
			{ 
				delete offer;
				return false; 
			}
			
			pResult2->next();
			
			offer->setGuildName( pResult2->getString(1) );
			offer->setGuildMaster( pResult2->getString(2) );
			
			offerList.addUnionOfferList(offer);

			/*cout << "GuildID : " << offer->getGuildID()
				<< ", GuildType : " <<  (int)offer->getGuildType()
				<< ", GuildName : " <<  offer->getGuildName()
				<< ", GuildMaster : " <<  offer->getGuildMaster()
				<< endl;
			 */
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )
	
	//cout << "make offerlist success!" << endl;
	return true;
}

uint GuildUnionOfferManager::acceptJoin( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Statement* pStmt2 = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT UnionID FROM GuildUnionOffer WHERE OfferType='JOIN' AND OwnerGuildID=%u", gID );

		if(pResult->getRowCount() == 0) return NO_TARGET_UNION;
		
		if ( pResult->next() )
		{
			clearOffer( gID );

			GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( gID );
			if ( pUnion != NULL )
			{
				return ALREADY_IN_UNION;
			}

			uint uID = pResult->getInt(1);
			pUnion = GuildUnionManager::Instance().getGuildUnionByUnionID( uID );
			if ( pUnion == NULL )
			{
				return NO_TARGET_UNION;
			}
			
			Result *pResult2 = pStmt2->executeQuery("SELECT COUNT(*) FROM GuildUnionMember WHERE UnionID='%u'", uID);
			pResult2->next();

			if(pResult2->getInt(1) >= g_pVariableManager->getVariable(GUILD_UNION_MAX))
			{
				SAFE_DELETE( pStmt2 );
				return NOT_ENOUGH_SLOT;
			}


			GuildUnionManager::Instance().addGuild( uID, gID );
		}
	}
	END_DB( pStmt );
	
	return OK;

	__END_CATCH
}

uint GuildUnionOfferManager::acceptQuit( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT UnionID FROM GuildUnionOffer WHERE OfferType='QUIT' AND OwnerGuildID=%u", gID );

		if ( pResult->next() )
		{
			clearOffer( gID );

			GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( gID );
			if ( pUnion == NULL )
			{
				return NOT_IN_UNION;
			}

			uint uID = pResult->getInt(1);
			if ( uID != pUnion->getUnionID() )
			{
				return NOT_YOUR_UNION;
			}

			pUnion = GuildUnionManager::Instance().getGuildUnionByUnionID( uID );
			if ( pUnion == NULL )
			{
				return NO_TARGET_UNION;
			}

			GuildUnionManager::Instance().removeGuild( uID, gID );
		}
	}
	END_DB( pStmt );
	
	return OK;

	__END_CATCH
}

uint GuildUnionOfferManager::denyJoin( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT UnionID FROM GuildUnionOffer WHERE OfferType='JOIN' AND OwnerGuildID=%u", gID );

		if ( pResult->next() )
		{
			clearOffer( gID );

			GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( gID );
			if ( pUnion != NULL )
			{
				return ALREADY_IN_UNION;
			}

			uint uID = pResult->getInt(1);
			pUnion = GuildUnionManager::Instance().getGuildUnionByUnionID( uID );
			if ( pUnion == NULL )
			{
				return NO_TARGET_UNION;
			}
		}
	}
	END_DB( pStmt );
	
	return OK;

	__END_CATCH
}

uint GuildUnionOfferManager::denyQuit( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT UnionID FROM GuildUnionOffer WHERE OfferType='QUIT' AND OwnerGuildID=%u", gID );

		if ( pResult->next() )
		{
			clearOffer( gID );

			GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( gID );
			if ( pUnion == NULL )
			{
				return NOT_IN_UNION;
			}

			uint uID = pResult->getInt(1);
			if ( uID != pUnion->getUnionID() )
			{
				return NOT_YOUR_UNION;
			}

			pUnion = GuildUnionManager::Instance().getGuildUnionByUnionID( uID );
			if ( pUnion == NULL )
			{
				return NO_TARGET_UNION;
			}
		}
	}
	END_DB( pStmt );
	
	return OK;

	__END_CATCH
}

void GuildUnionOfferManager::clearOffer( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM GuildUnionOffer WHERE OwnerGuildID=%u", gID);
	}
	END_DB( pStmt )

	__END_CATCH
}

bool GuildUnionOfferManager::hasOffer( GuildID_t gID ) throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT count(*) FROM GuildUnionOffer WHERE OwnerGuildID=%u", gID);
		if ( pResult->next() )
		{
			if ( pResult->getInt(1) > 0 )
			{
				SAFE_DELETE( pStmt );
				return true;
			}
		}
	}
	END_DB( pStmt )

	return false;

	__END_CATCH
}
