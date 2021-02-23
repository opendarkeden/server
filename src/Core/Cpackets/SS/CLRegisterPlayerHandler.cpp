//////////////////////////////////////////////////////////////////////////////
// Filename    : CLRegisterPlayerHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLRegisterPlayer.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
    #include "GameServerGroupInfoManager.h"

	#include "Lpackets/LCRegisterPlayerError.h"
	#include "Lpackets/LCRegisterPlayerOK.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Å¬¶óÀÌ¾ðÆ®¿¡¼­ ÇÃ·¹ÀÌ¾î µî·Ï Á¤º¸¸¦ ³¯¸± °æ¿ì, ¼­¹ö¿¡¼­´Â ¿ì¼±
// ÇöÀç ¾ÆÀÌµð°¡ "guest"ÀÎÁö Ã¼Å©ÇÏ°í, ÃÖÃÊÀÇ ÆÐÅ¶ÀÎÁö Ã¼Å©ÇÑ ÈÄ,
// »ç¿ëÀÚ Á¤º¸¸¦ DB¿¡ µî·ÏÇÏ°í³ª¼­, ¿¬°áÀ» Â÷´ÜÇÑ´Ù.
//////////////////////////////////////////////////////////////////////////////
void CLRegisterPlayerHandler::execute (CLRegisterPlayer* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	__BEGIN_DEBUG

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	//cout << "Registering Player... " << endl;

	//----------------------------------------------------------------------
	// ·Î±×ÀÎ ÇÃ·¹ÀÌ¾îÀÇ ¾ÆÀÌµð°¡ guest ÀÎÁö Ã¼Å©ÇÑ´Ù.
	//----------------------------------------------------------------------
//	if (pLoginPlayer->getID() != "guest")
//		throw InvalidProtocolException("must be guest user");

	//----------------------------------------------------------------------
	// ÇÃ·¹ÀÌ¾î Á¤º¸ °ËÁõ
	// °¢ ½ºÆ®¸µÀÇ ±æÀÌ ¹× NULL ¿©ºÎ¸¦ Ã¼Å©ÇÑ´Ù.
	//----------------------------------------------------------------------
	LCRegisterPlayerError lcRegisterPlayerError;

	try {

		//cout << "ÇÃ·¹ÀÌ¾î Á¤º¸ °ËÁõ : " << pPacket->toString() << endl;

		if (pPacket->getID() == "") {
			lcRegisterPlayerError.setErrorID(EMPTY_ID);	
			throw string("ID field is empty");
		}

		if (pPacket->getID().size() < 4) {
			lcRegisterPlayerError.setErrorID(SMALL_ID_LENGTH);	
			throw string("too small ID length");
		}

		if (pPacket->getPassword() == "") 
		{
			lcRegisterPlayerError.setErrorID(EMPTY_PASSWORD);	
			throw string("Password field is empty");
		}
		else
		{
			string password = pPacket->getPassword();
			if (password.find("\'") < password.size()) throw string("Invalid Password");
			if (password.find("'") < password.size()) throw string("Invalid Password");
			else if (password.find("\\") < password.size()) throw string("Invalid Password");
			else if (password.find("\"") < password.size()) throw string("Invalid Password");
			else if (password.find(";") < password.size()) throw string("Invalid Password");
		}

		if (pPacket->getPassword().size() < 6) {
			lcRegisterPlayerError.setErrorID(SMALL_PASSWORD_LENGTH);	
			throw string("too small password length");
		}

		if (pPacket->getName() == "") {
			lcRegisterPlayerError.setErrorID(EMPTY_NAME);	
			throw string("Name field is empty");
		}

		if (pPacket->getSSN() == "") {
			lcRegisterPlayerError.setErrorID(EMPTY_SSN);	
			throw string("SSN field is empty");
		}

	} catch (string & errstr) {

		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//cout << lcRegisterPlayerError.toString() << endl;

		// ÀÏ´Ü ¹öÆÛ¸¦ ÇÃ·¯½ÃÇÏ°í, ¿¬°áÀ» Â÷´ÜÇÑ´Ù.
		//
		// *TODO*
		// ½ÇÆÐ È¸¼ö¸¦ ÀúÀåÇÑ ÈÄ, ±× È¸¼öº¸´Ù ÀÛÀº °æ¿ì¿¡´Â °è¼Ó ¿¬°áÀ» À¯ÁöÇÏµµ·Ï ÇÑ´Ù.
		//
		throw DisconnectException(lcRegisterPlayerError.toString());
	}
		

	//----------------------------------------------------------------------
	// ÀÌÁ¦ µ¥ÀÌÅ¸º£ÀÌ½º¿¡ µî·ÏÇÏµµ·Ï ÇÑ´Ù.
	//----------------------------------------------------------------------

	Statement* pStmt;
	Result* pResult;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		//--------------------------------------------------------------------------------
		// ¾ÆÀÌµð Áßº¹ ¿©ºÎ¸¦ Ã¼Å©ÇÑ´Ù.
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery("SELECT PlayerID FROM Player WHERE PlayerID = '%s'" , pPacket->getID().c_str());

		if (pResult->getRowCount() != 0) {
			lcRegisterPlayerError.setErrorID(ALREADY_REGISTER_ID);	
			throw DuplicatedException("±×·± ¾ÆÀÌµð°¡ ÀÌ¹Ì Á¸ÀçÇÕ´Ï´Ù.");
		}


		//--------------------------------------------------------------------------------
		// ÁÖ¹Îµî·Ï¹øÈ£¸¦ °ËÁõÇÑ´Ù. ³ªÁß¿¡.. -_-;
		//--------------------------------------------------------------------------------


		//--------------------------------------------------------------------------------
		// ÁÖ¹Îµî·Ï¹øÈ£ Áßº¹ ¿©ºÎ¸¦ Ã¼Å©ÇÑ´Ù. 
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery("SELECT SSN FROM Player WHERE SSN = '%s'" , pPacket->getSSN().c_str());

		if (pResult->getRowCount() != 0) {
			lcRegisterPlayerError.setErrorID(ALREADY_REGISTER_SSN);
			throw DuplicatedException("ÀÌ¹Ì µî·ÏµÈ ÁÖ¹Îµî·Ï¹øÈ£ÀÔ´Ï´Ù.");
		}


		//--------------------------------------------------------------------------------
		// ÇÃ·¹ÀÌ¾î¸¦ µî·ÏÇÑ´Ù.
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery(
			"INSERT INTO Player (PlayerID , Password , Name , Sex , SSN , Telephone , Cellular , Zipcode , Address , Nation , Email , Homepage , Profile , Pub) VALUES ('%s' , PASSWORD('%s') , '%s' , '%s' , '%s' , '%s' , '%s' , '%s' , '%s' , %d , '%s' , '%s' , '%s' , '%s')" ,
			pPacket->getID().c_str() , 
			pPacket->getPassword().c_str() , 
			pPacket->getName().c_str() , 
			Sex2String[ pPacket->getSex() ].c_str() , 
			pPacket->getSSN().c_str() , 
			pPacket->getTelephone().c_str() , 
			pPacket->getCellular().c_str() , 
			pPacket->getZipCode().c_str() , 
			pPacket->getAddress().c_str() , 
			(int)pPacket->getNation() ,
			pPacket->getEmail().c_str() , 
			pPacket->getHomepage().c_str() , 
			pPacket->getProfile().c_str() , 
			(pPacket->getPublic() == true) ? "PUBLIC" : "PRIVATE" 
		);
				
		// ¿©±â±îÁö ¿Ô´Ù¸é, DB¿¡ ÇÃ·¹ÀÌ¾î°¡ Àß Ãß°¡µÇ¾ú´Ù´Â ÀÇ¹Ì°¡ µÈ´Ù.
		// ÇÃ·¹ÀÌ¾î¿¡°Ô µî·ÏÀÌ Àß µÇ¾ú´Ù´Â LCRegisterPlayerOK ÆÐÅ¶À» º¸³»ÀÚ.
		Assert(pResult == NULL);
		Assert(pStmt->getAffectedRowCount() == 1);

		// µî·ÏÇÑ ÈÄ µðÆúÆ® ¼­¹öÀÇ ±×·ì ¾ÆÀÌµð¸¦ ¹Þ¾Æ¿Â´Ù.
		pResult = pStmt->executeQuery("SELECT CurrentWorldID, CurrentServerGroupID FROM Player WHERE PlayerID = '%s'" , pPacket->getID().c_str());

		if (pResult->getRowCount() == 0) {
			lcRegisterPlayerError.setErrorID(ETC_ERROR);
			throw SQLQueryException("Á¤»óÀûÀ¸·Î µ¥ÀÌÅÍº£ÀÌ½º°¡ ÀÔ·Â, Ãâ·Â µÇÁö ¾Ê¾Ò½À´Ï´Ù.");
		}

		WorldID_t 		 WorldID = 0;
		ServerGroupID_t  ServerGroupID = 0;

		if (pResult->next()) throw SQLQueryException("µ¥ÀÌÅÍº£ÀÌ½º¿¡ Ä¡¸íÀûÀÎ ¹®Á¦°¡ ÀÖ½À´Ï´Ù.");

		WorldID = pResult->getInt(1);
		ServerGroupID = pResult->getInt(2);

		pLoginPlayer->setServerGroupID(ServerGroupID);

		LCRegisterPlayerOK lcRegisterPlayerOK;

		lcRegisterPlayerOK.setGroupName(g_pGameServerGroupInfoManager->getGameServerGroupInfo(ServerGroupID, WorldID)->getGroupName());

		string SSN = pPacket->getSSN();
		string preSSN;
		bool isChina = false;
		// ÇÑ±¹
		if ( strstr(SSN.c_str(), "-") != NULL )
		{
			preSSN = SSN.substr(0, 6);
		}
		// Áß±¹
		else 
		{
			isChina = true;
			if (SSN.size() == 15)
			{
				preSSN = SSN.substr(6, 12);
			}
			else if (SSN.size() == 18)
			{
				preSSN = SSN.substr(8, 14);
			}
			else
			{
				// ÀÌ·± °æ¿ì´Â ¾ø´Ù°í ÇÏÁö¸¸ -_- ¸Ó ¾ÏÆ°
			 	preSSN = SSN.substr(0, 6);
			}

			//add by zdj 2005.5.11
			//ÒÔÉÏ´úÂëÓÐ´íÎó,²»¼ì²â³ÉÈËÉèÖÃ
			preSSN = "781109";
		}
//        string preSSN = pPacket->getSSN().substr(0, 6).c_str();

		StringStream AdultSSN;

		time_t daytime = time(0);
		tm Timec;
		localtime_r( &daytime, &Timec );
		AdultSSN << Timec.tm_year - 20 << Timec.tm_mon << Timec.tm_mday;

		// ¼ºÀÎÀÎÁö ¾Æ´ÑÁö ÁÖ¹Îµî·Ï ¹øÈ£ Ã¼Å©
		if (atoi(preSSN.c_str()) <= atoi(AdultSSN.toString().c_str())) {
			lcRegisterPlayerOK.setAdult(true);
		} else {
			lcRegisterPlayerOK.setAdult(false);
		}

		// Áß±¹ÀÌ¸é ¹«Á¶°Ç ¼ºÀÎ
		if ( isChina )
		{
			lcRegisterPlayerOK.setAdult(true);
		}

		pLoginPlayer->sendPacket(&lcRegisterPlayerOK);

		// ÀÌ¸§À» º¯°æÇØÁà¾ß ÇÑ´Ù.
		pLoginPlayer->setID(pPacket->getID());

		// µî·Ï¿¡ ¼º°øÇßÀ» °æ¿ì, CLGetPCList ÆÐÅ¶À» ±â´Ù¸°´Ù.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);

		SAFE_DELETE(pStmt);
	} 
	catch (DuplicatedException & de) 
	{
		SAFE_DELETE(pStmt);

		//cout << de.toString() << endl;

		//--------------------------------------------------------------------------------
		// µî·Ï ½ÇÆÐ ÆÐÅ¶À» Àü¼ÛÇÑ´Ù.
		//--------------------------------------------------------------------------------
		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//--------------------------------------------------------------------------------
		// ½ÇÆÐ È¸¼ö¸¦ Áõ°¡½ÃÅ²´Ù. ³Ê¹« ¸¹ÀÌ ½ÇÆÐÇßÀ» °æ¿ì, ¿¬°áÀ» Á¾·áÇÑ´Ù.
		//--------------------------------------------------------------------------------
		uint nFailed = pLoginPlayer->getFailureCount();

		//cout << pLoginPlayer->getID() << "'s Failure Count = " << ++nFailed << endl;

		if (nFailed > 3) 
			throw DisconnectException("too many failure");

		pLoginPlayer->setFailureCount(nFailed);

		// µî·Ï¿¡ ½ÇÆÐÇÒ °æ¿ì, ´Ù½Ã CLRegisterPlayer ÆÐÅ¶À» ±â´Ù¸°´Ù.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);

	} 
	catch (SQLQueryException & sqe) 
	{
		SAFE_DELETE(pStmt);

		// Èì. SQL ¿¡·¯ÀÌµçÁö µî·ÏÀÌ Àß ¾ÈµÇ¾ú´Ù´Â ¼Ò¸®´Ù.
		//cout << sqe.toString() << endl;

		//--------------------------------------------------------------------------------
		// µî·Ï ½ÇÆÐ ÆÐÅ¶À» Àü¼ÛÇÑ´Ù.
		//--------------------------------------------------------------------------------
		lcRegisterPlayerError.setErrorID(ETC_ERROR);

		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//--------------------------------------------------------------------------------
		// ½ÇÆÐ È¸¼ö¸¦ Áõ°¡½ÃÅ²´Ù. ³Ê¹« ¸¹ÀÌ ½ÇÆÐÇßÀ» °æ¿ì, ¿¬°áÀ» Á¾·áÇÑ´Ù.
		//--------------------------------------------------------------------------------
		uint nFailed = pLoginPlayer->getFailureCount();

		//cout << pLoginPlayer->getID() << "'s Failure Count = " << ++nFailed << endl;

		if (nFailed > 3) 
			throw DisconnectException("too many failure");

		pLoginPlayer->setFailureCount(nFailed);

		// µî·Ï¿¡ ½ÇÆÐÇÒ °æ¿ì, ´Ù½Ã CLRegisterPlayer ÆÐÅ¶À» ±â´Ù¸°´Ù.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);

	}

	__END_DEBUG

#endif
		
	__END_DEBUG_EX __END_CATCH
}
