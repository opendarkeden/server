//////////////////////////////////////////////////////////////////////////////
// Filename    : CLSelectPCHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLSelectPC.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "ZoneInfoManager.h"
	#include "ZoneGroupInfoManager.h"
	#include "GameServerInfo.h"
	#include "GameServerInfoManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "Assert.h"
	#include "gameserver/billing/BillingInfo.h"

	#include "Lpackets/LCSelectPCError.h"
	#include "Lpackets/LCReconnect.h"
	#include "Lpackets/LGIncomingConnection.h"

	#include "chinabilling/CBillingInfo.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// CLSelectPCHandler::execute()
// 
// ·Î±×ÀÎ ¼­¹ö´Â ÀÌ ÆÐÅ¶À» ¹ÞÀ¸¸é, ÁöÁ¤µÈ Name + PCType ¸¦ °¡Áø PC ¸¦ ·ÎµùÇÑ´Ù.°
// ÀÌ PC°¡ ÇÃ·¹ÀÌ¾îÀÇ Ä³¸¯ÅÍ¶ó¸é ÀÌ PC°¡ ±âÁ¸¿¡ ÀÖ´ø Á¸À» ¾Ë¾Æ³»¼­
// ±× Á¸À» ´ã´çÇÑ °ÔÀÓ ¼­¹ö¿¡°Ô LGIncomingConnection À» Àü¼ÛÇÑ´Ù.
// Á÷ÈÄ Å¬¶óÀÌ¾ðÆ®¿¡°Ô LCReconnect ÆÐÅ¶À» º¸³»¼­, °ÔÀÓ ¼­¹ö·Î ¿¬°áÇÏµµ·Ï
// ÇØÁØ´Ù.
//////////////////////////////////////////////////////////////////////////////
void CLSelectPCHandler::execute (CLSelectPC* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	bool bCheckATTR = false;

	// ·Î±×ÀÎ ¼­¹ö¿¡¼­ billing ¿¬°á ºÎºÐÀ» »©±â·Î ÇÑ´Ù.
    // ¾Öµåºô ¿äÃ» »çÇ×. by bezz 2003.04.22
/*#ifdef __CONNECT_BILLING_SYSTEM__

	// ºô¸µ ½Ã½ºÅÛÀ¸·ÎºÎÅÍ Ã¼Å©¸¦ ¹Þ´Â °æ¿ì
	// by sigi. 2002.11.21
	if (pLoginPlayer->isBillingLoginVerified())
	{
		if (pLoginPlayer->isBillingPlayAvaiable()
			&& pLoginPlayer->getBillingUserStatus()!="XX")
		{
			cout << "isBillingPlay: " << pLoginPlayer->getID().c_str() << endl;
		}
		else if (pLoginPlayer->isPayPlaying())
		{
			// °Á Åë°ú~
			cout << "isPayPlaying: " << pLoginPlayer->getID().c_str() << endl;

			// ±×·¯³ª.. ¹Ø¿¡¼­ ´É·ÂÄ¡ Ã¼Å©¸¦ ÇØ¾ßÇÑ´Ù.
			if (pLoginPlayer->getPayType()!=PAY_TYPE_FREE)
			{
				bCheckATTR = true;
			}
		}
		else
		{
			cout <<  "CannotPlay: " << pLoginPlayer->getID().c_str() << endl;

			// °ÔÀÓ ÇÒ ¼ö ¾ø´Â Ä³¸¯ÅÍ(ºô¸µ °ü·Ã)
			LCSelectPCError lcSelectPCError;
			lcSelectPCError.setCode( SELECT_PC_CANNOT_PLAY );
			pLoginPlayer->sendPacket( &lcSelectPCError );	

			//throw DisconnectException("cannot playing");
			return;
		}
	}
	else 
	{
		// ¾ÆÁ÷ ºô¸µ½Ã½ºÅÛÀ¸·ÎºÎÅÍ °ËÁõÀÌ µÇÁö ¾ÊÀº »óÅÂ
		// Å¬¶óÀÌ¾ðÆ®¿¡¼­ ´õ ±â´Ù¸®µµ·Ï ÇØ¾ßÇÑ´Ù.
		// ¾Æ´Ï¸é, ÀÏ´Ü ±×³É ³Ñ¾î°¡°í.. °× ¼­¹ö¿¡¼­ Â©¸®µµ·Ï ÇÒ±î?
		// ¾ÆÁ÷ °áÁ¦ Á¤º¸°¡ Ã¼Å©µÇÁö ¾Ê¾Ò´Ù.
		cout << "NotBillingChecked: " << pLoginPlayer->getID().c_str();

		if (pLoginPlayer->isPayPlaying()
			&& pLoginPlayer->getPayType()==PAY_TYPE_FREE)
		{
			// ¿ÏÀü ¹«·á »ç¿ëÀÚ´Â ±×³É Åë°úÇÑ´Ù.
			cout << "But PAY_TYPE_FREE" << endl;
		}
		else
		{
			cout << endl;

			LCSelectPCError lcSelectPCError;
			lcSelectPCError.setCode( SELECT_PC_NOT_BILLING_CHECK );
			pLoginPlayer->sendPacket( &lcSelectPCError );	

			//throw DisconnectException("cannot playing");
			return;
		}
	}
*/
#ifdef __CONNECT_CBILLING_SYSTEM__
	if ( pLoginPlayer->isCBillingVerified() )
	{
		if ( !pLoginPlayer->isPayPlayer() )
		{
			LCSelectPCError lcSelectPCError;
			lcSelectPCError.setCode( SELECT_PC_CANNOT_PLAY );
			pLoginPlayer->sendPacket( &lcSelectPCError );

			return;
		}
	}
	else
	{
		LCSelectPCError lcSelectPCError;
		lcSelectPCError.setCode( SELECT_PC_NOT_BILLING_CHECK );
		pLoginPlayer->sendPacket( &lcSelectPCError );

		return;
	}

#endif

// ¾Öµåºô ºô¸µÀº »ç¿ëÇÏÁö ¾Ê¾Æµµ..
// ´É·ÂÄ¡ Á¦ÇÑ Ã¼Å©´Â ÇØ¾ßÇÏ´Â °æ¿ì
#if defined(__PAY_SYSTEM_FREE_LIMIT__)
	// À¯·á »ç¿ëÀÚ°¡ ¾Æ´Ñ °æ¿ì´Â ... ´É·ÂÄ¡ Ã¼Å©ÇÑ´Ù.
	if (!pLoginPlayer->isPayPlaying())
	{
		bCheckATTR = true;
	}
#endif


	if (pLoginPlayer->getPlayerStatus() != LPS_PC_MANAGEMENT){
		filelog("selectPc.txt","invalid player status");
		throw DisconnectException("invalid player status");
		}
	// PC ÀÇ Á¤º¸¸¦ µ¥ÀÌÅ¸º£ÀÌ½º·ÎºÎÅÍ °¡Á® ¿Â´Ù.
	Statement* pStmt = NULL;
	Statement* pStmt1 = NULL;	// (!)
	Result* pResult;
	WorldID_t WorldID = pLoginPlayer->getWorldID();

	try 
	{
		pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement(); // (!)
		pStmt = g_pDatabaseManager->getConnection( WorldID )->createStatement();

		//----------------------------------------------------------------------
		// PC °¡ ¸¶Áö¸·À¸·Î ÇÃ·¹ÀÌÇÑ Á¸ÀÇ ¾ÆÀÌµð¸¦ °¡Á®¿Â´Ù.
		//----------------------------------------------------------------------

		// ½½·¹ÀÌ¾î È¤Àº ¹ìÆÄÀÌ¾î Å×ÀÌºí¿¡¼­ ³»°¡ ¼ÒÀ¯ÇÑ ¾×Æ¼ºê Ä³¸¯ÅÍ¸¦ Ã£´Â´Ù.
		/*
		pResult = pStmt->executeQuery(
			"SELECT ZoneID, Slot FROM %s WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
			pPacket->getPCType() == PC_SLAYER ? "Slayer" : "Vampire" ,
			pPacket->getPCName().c_str() ,
			pLoginPlayer->getID().c_str()
		);
		*/
		//È¡½ÇÉ«ÀàÐÍ£¬²»Ê¹ÓÃ¿Í»§¶ËÉÏÀ´µÄÀàÐÍ£¬·ÀÖ¹µôÏß
		//³Â¹â»ÔÐÞ¸Ä2006 05 31
		pResult = pStmt->executeQuery(
				"SELECT Race FROM Slayer WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);

		if (pResult->getRowCount() != 1)
		{
			SAFE_DELETE(pStmt);
			filelog("selectPc.txt","no such PC exist");
			throw InvalidProtocolException("no such PC exist.");
		}

		if (pResult->next())
		{
			string spRace 	= pResult->getString(1);

			if (spRace=="SLAYER") 
			{
				pPacket->setPCType(PC_SLAYER);
			}
			else if (spRace=="VAMPIRE")
			{
				pPacket->setPCType(PC_VAMPIRE);
			}
			else if (spRace=="OUSTERS")
			{
				pPacket->setPCType(PC_OUSTERS);
			}
			else
			{
				StringStream msg;
				msg << "Race type error! Character(" 
					<< pLoginPlayer->getID().c_str() << ")";

				filelog("selectPcError.txt", "%s", msg.toString().c_str());

				SAFE_DELETE(pStmt);
				throw ProtocolException( msg.toString().c_str() );
			}
		}
		
		bool isSlayer =  (pPacket->getPCType() == PC_SLAYER);
		bool isVampire =  (pPacket->getPCType() == PC_VAMPIRE);

		if (isSlayer)
		{
			pResult = pStmt->executeQuery(
				"SELECT ZoneID, Slot, GREATEST(SwordLevel,BladeLevel,GunLevel,EnchantLevel,HealLevel), Competence FROM Slayer WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);
		}
		else if (isVampire)
		{
			pResult = pStmt->executeQuery(
				"SELECT ZoneID, Slot, Level, Competence FROM Vampire WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);
		}
		else 
		{
			pResult = pStmt->executeQuery(
				"SELECT ZoneID, Slot, Level, Competence FROM Ousters WHERE Name = '%s' AND PlayerID = '%s' AND Active = 'ACTIVE'", 
				pPacket->getPCName().c_str() ,
				pLoginPlayer->getID().c_str()
			);
		}
	
		// ±×·± PC°¡ ¾øÀ» °æ¿ì
		if (pResult->getRowCount() != 1)
		{
			SAFE_DELETE(pStmt);
			filelog("selectPc.txt","no such PC exist");
			throw InvalidProtocolException("no such PC exist.");
		}

		pResult->next();

		ZoneID_t zoneID = pResult->getWORD(1);
		string slotStr 	= pResult->getString(2);

		// ´É·ÂÄ¡ Ã¼Å©. by sigi. 2002.11.22
		if (bCheckATTR)
		{
		#ifdef __PAY_SYSTEM_FREE_LIMIT__
			if (isSlayer)
			{
				static int slayerSum = g_pConfig->getPropertyInt("FreePlaySlayerDomainSum");

				int DomainSUM = pResult->getInt(3);

				if (DomainSUM > slayerSum)
				{
					LCSelectPCError lcSelectPCError;
					lcSelectPCError.setCode( SELECT_PC_CANNOT_PLAY_BY_ATTR );
					pLoginPlayer->sendPacket( &lcSelectPCError );	
					SAFE_DELETE(pStmt);
					return;
				}
			}
			else
			{
				static int vampireLevel = g_pConfig->getPropertyInt("FreePlayVampireLevel");

				int Level = pResult->getInt(3);

				if (Level > vampireLevel)
				{
					LCSelectPCError lcSelectPCError;
					lcSelectPCError.setCode( SELECT_PC_CANNOT_PLAY_BY_ATTR );
					pLoginPlayer->sendPacket( &lcSelectPCError );	
					SAFE_DELETE(pStmt);
					return;
				}
			}
		#endif
		}

		//////////////////////////////////////////////////////////////////////////////////////
		// PK Server Ã¼Å©
		//////////////////////////////////////////////////////////////////////////////////////
		bool bNonPKServer = g_pGameServerInfoManager->getGameServerInfo( 1, pLoginPlayer->getServerGroupID(), pLoginPlayer->getWorldID() )->isNonPKServer();
		if ( bNonPKServer )
		{
			//cout << "WorldID:" << (int)(pLoginPlayer->getWorldID()) << " ServerGroupID:" << (int)(pLoginPlayer->getServerGroupID()) << endl;

			int playerLevel = pResult->getInt(3);
			int competence = pResult->getInt(4);

			// 40 ·¹º§ º¸´Ù ³ôÀº ÇÃ·¹ÀÌ¾î´Â µé¾î°¥ ¼ö ¾ø´Ù.
			// ¿î¿µÀÚ´Â µé¾î°¡¾ßÇÑ´Ù.
			if ( playerLevel > 80 && competence == 3 )
			{
				LCSelectPCError lcSelectPCError;
				lcSelectPCError.setCode( SELECT_PC_CANNOT_PLAY_BY_ATTR );
				pLoginPlayer->sendPacket( &lcSelectPCError );	
				SAFE_DELETE(pStmt);
				return;
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////

		if (slotStr.size()!=5)
		{
			SAFE_DELETE(pStmt);
			filelog("selectPc.txt","no slot exist");
			throw InvalidProtocolException("no slot exist.");
		}

		int slot = slotStr.at(4) - '0';

		//----------------------------------------------------------------------
		// ÀÌ Á¸À» °ü¸®ÇÏ´Â °ÔÀÓ ¼­¹ö Á¤º¸¸¦ °¡Á®¿Â´Ù.
		//----------------------------------------------------------------------
		GameServerInfo* pGameServerInfo;
		if ( zoneID > 10000 && zoneID < 30000 )
		{
			// Ä³¸¯ÅÍ°¡ ±æµå ¾ÆÁöÆ®¿¡ ÀÖ´Ù. ±æµå ¾ÆÁöÆ® Á¸ÀÇ Á¤º¸´Â login server¿¡ ¾øÀ¸¹Ç·Î ´ëÃæ ¶«»§ÇÑ´Ù.
			pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo( 1, pLoginPlayer->getServerGroupID(), WorldID );
		}
		else
		{
			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(zoneID);
			ZoneGroupInfo* pZoneGroupInfo = g_pZoneGroupInfoManager->getZoneGroupInfo(pZoneInfo->getZoneGroupID());
			//cout << "ConnctServerGroup: " << (int)pLoginPlayer->getServerGroupID() << ", ServerID: " << (int)pZoneGroupInfo->getServerID();
			//cout << "WorldID " << (int)WorldID << ", ServerGroupID : " << (int)pLoginPlayer->getServerGroupID() << ", ServerID : " << (int)pZoneGroupInfo->getServerID() << endl;
			pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(pZoneGroupInfo->getServerID(), pLoginPlayer->getServerGroupID(), WorldID );
		}

		//----------------------------------------------------------------------
		// ÀÌ »ç¿ëÀÚÀÇ ÇöÀç Á¢¼Ó ¼­¹ö Á¤º¸¸¦ °¡Á®¿Â´Ù.
		//----------------------------------------------------------------------
//		GameServerInfo* pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(pPlayer->getServerID());


		//----------------------------------------------------------------------
		// °ÔÀÓ¼­¹ö¿¡°Ô incoming connection ÀÌ ¿Ã °Å¶ó°í ¾Ë·ÁÁØ´Ù.
		//----------------------------------------------------------------------
		LGIncomingConnection lgIncomingConnection;
		lgIncomingConnection.setClientIP(pLoginPlayer->getSocket()->getHost());
		lgIncomingConnection.setPlayerID(pLoginPlayer->getID());
		lgIncomingConnection.setPCName(pPacket->getPCName());

		//--------------------------------------------------------------------------------
		//
		// *CAUTION*
		//
		// LoginPlayer::setPlayerStatus()¿Í GameServerManager::sendPacket()ÀÇ ¼ø¼­¿¡ ÁÖÀÇÇÏ¶ó.
		// ´Ü¼øÇÏ°Ô »ý°¢ÇÏ¸é sendPacket()ÈÄ¿¡ setPlayerStatus()¸¦ È£ÃâÇÏ´Â °ÍÀÌ ³í¸®¿¡ ÇÕ´ç
		// ÇÏÁö¸¸, ½ÇÁ¦·Î ±×·¸°Ô ÇÏ¸é setPlayerStatus()¸¦ È£ÃâÇÏ±â Àü¿¡ °ÔÀÓ ¼­¹ö·ÎºÎÅÍ
		// GLIncomingConnectionXXX ÆÐÅ¶ÀÌ ³¯¾Æ¿Í¼­ ±× ÇÚµé·¯°¡ ½ÇÇàµÈ´Ù. - -;
		// µû¶ó¼­, ¾Æ·¡¿Í °°ÀÌ »óÅÂ¸¦ ¸ÕÀú ÁöÁ¤ÇÑ ÈÄ¿¡ UDP ÆÐÅ¶À» Àü¼ÛÇØ¾ß ÇÑ´Ù.
		//
		//--------------------------------------------------------------------------------
		pLoginPlayer->setPlayerStatus(LPS_AFTER_SENDING_LG_INCOMING_CONNECTION);

/*
		// ¾îÂ¿ ¼ö ¾øÀÌ user name À» »ç¿ëÇØ¼­ ÇÏµåÄÚµùÇÑ´Ù. -_-;
		g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , pGameServerInfo->getUDPPort() , &lgIncomingConnection);
*/
		
		if (g_pConfig->getProperty("User") == "excel96")
			//g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , pGameServerInfo->getUDPPort(), &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "beowulf")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 8886 , &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "crazydog")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 6665, &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "elcastle")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 8885 , &lgIncomingConnection);
		else if (g_pConfig->getProperty("User") == "elca")
			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , g_pConfig->getPropertyInt("GameServerUDPPort"), &lgIncomingConnection);
//			g_pGameServerManager->sendPacket(pGameServerInfo->getIP() , 3335 , &lgIncomingConnection);

		// ¸¶Áö¸·À¸·Î Á¢¼ÓÇÑ slot ±â¾ï. by sigi. 2002.5.6
		pStmt1->executeQuery(	// (!)
		//pStmt->executeQuery(
			"UPDATE Player Set CurrentWorldID = %d, CurrentServerGroupID = %d, LastSlot = %d WHERE PlayerID = '%s'",
			WorldID,
			pLoginPlayer->getServerGroupID(),
			slot,
			pLoginPlayer->getID().c_str()
		);

		pStmt->executeQuery( "UPDATE Slayer Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(), pPacket->getPCName().c_str() );
		pStmt->executeQuery( "UPDATE Vampire Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(), pPacket->getPCName().c_str() );
		pStmt->executeQuery( "UPDATE Ousters Set ServerGroupID = %d WHERE Name='%s'", pLoginPlayer->getServerGroupID(), pPacket->getPCName().c_str() );

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); //(!)

		//cout << "CLSelectPC SendPacket to Server IP : " << pGameServerInfo->getIP() << endl;
	} 
	catch (SQLQueryException & sqe) 
	{
		//cout << sqe.toString() << endl;

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); //(!)
		filelog("selectPc.txt","SQLQueryException & sqe");
		throw DisconnectException(sqe.toString());
	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;

		msg << "Critical Error : data intergrity broken at ZoneInfo - ZoneGroupInfo - GameServerInfo : " << nsee.toString();

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); //(!)
		filelog("selectPc.txt","NoSuchElementException & nsee");
		throw Error(msg.toString());
	}
	catch (...)
	{
		SAFE_DELETE(pStmt);
		SAFE_DELETE(pStmt1); 
		filelog("selectPc.txt","Select PC Error!check DB,player ID:%s",pLoginPlayer->getID().c_str());
		throw DisconnectException("Select PC Error!");
	}


#endif

	__END_DEBUG_EX __END_CATCH
}
