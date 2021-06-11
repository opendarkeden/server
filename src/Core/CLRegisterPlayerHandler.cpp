//////////////////////////////////////////////////////////////////////////////
// Filename    : CLRegisterPlayerHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLRegisterPlayer.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert1.h"
	#include "DB.h"
    #include "GameServerGroupInfoManager.h"

	#include "LCRegisterPlayerError.h"
	#include "LCRegisterPlayerOK.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 클라이언트에서 플레이어 등록 정보를 날릴 경우, 서버에서는 우선
// 현재 아이디가 "guest"인지 체크하고, 최초의 패킷인지 체크한 후,
// 사용자 정보를 DB에 등록하고나서, 연결을 차단한다.
//////////////////////////////////////////////////////////////////////////////
void CLRegisterPlayerHandler::execute (CLRegisterPlayer* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	__BEGIN_DEBUG

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	//cout << "Registering Player... " << endl;

	//----------------------------------------------------------------------
	// 로그인 플레이어의 아이디가 guest 인지 체크한다.
	//----------------------------------------------------------------------
//	if (pLoginPlayer->getID() != "guest")
//		throw InvalidProtocolException("must be guest user");

	//----------------------------------------------------------------------
	// 플레이어 정보 검증
	// 각 스트링의 길이 및 NULL 여부를 체크한다.
	//----------------------------------------------------------------------
	LCRegisterPlayerError lcRegisterPlayerError;

	try {

		//cout << "플레이어 정보 검증 : " << pPacket->toString() << endl;

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

		// 일단 버퍼를 플러시하고, 연결을 차단한다.
		//
		// *TODO*
		// 실패 회수를 저장한 후, 그 회수보다 작은 경우에는 계속 연결을 유지하도록 한다.
		//
		throw DisconnectException(lcRegisterPlayerError.toString());
	}
		

	//----------------------------------------------------------------------
	// 이제 데이타베이스에 등록하도록 한다.
	//----------------------------------------------------------------------

	Statement* pStmt;
	Result* pResult;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		//--------------------------------------------------------------------------------
		// 아이디 중복 여부를 체크한다.
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery("SELECT PlayerID FROM Player WHERE PlayerID = '%s'" , pPacket->getID().c_str());

		if (pResult->getRowCount() != 0) {
			lcRegisterPlayerError.setErrorID(ALREADY_REGISTER_ID);	
			throw DuplicatedException("그런 아이디가 이미 존재합니다.");
		}


		//--------------------------------------------------------------------------------
		// 주민등록번호를 검증한다. 나중에.. -_-;
		//--------------------------------------------------------------------------------


		//--------------------------------------------------------------------------------
		// 주민등록번호 중복 여부를 체크한다. 
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery("SELECT SSN FROM Player WHERE SSN = '%s'" , pPacket->getSSN().c_str());

		if (pResult->getRowCount() != 0) {
			lcRegisterPlayerError.setErrorID(ALREADY_REGISTER_SSN);
			throw DuplicatedException("이미 등록된 주민등록번호입니다.");
		}


		//--------------------------------------------------------------------------------
		// 플레이어를 등록한다.
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
				
		// 여기까지 왔다면, DB에 플레이어가 잘 추가되었다는 의미가 된다.
		// 플레이어에게 등록이 잘 되었다는 LCRegisterPlayerOK 패킷을 보내자.
		Assert(pResult == NULL);
		Assert(pStmt->getAffectedRowCount() == 1);

		// 등록한 후 디폴트 서버의 그룹 아이디를 받아온다.
		pResult = pStmt->executeQuery("SELECT CurrentWorldID, CurrentServerGroupID FROM Player WHERE PlayerID = '%s'" , pPacket->getID().c_str());

		if (pResult->getRowCount() == 0) {
			lcRegisterPlayerError.setErrorID(ETC_ERROR);
			throw SQLQueryException("정상적으로 데이터베이스가 입력, 출력 되지 않았습니다.");
		}

		WorldID_t 		 WorldID = 0;
		ServerGroupID_t  ServerGroupID = 0;

		if (pResult->next()) throw SQLQueryException("데이터베이스에 치명적인 문제가 있습니다.");

		WorldID = pResult->getInt(1);
		ServerGroupID = pResult->getInt(2);

		pLoginPlayer->setServerGroupID(ServerGroupID);

		LCRegisterPlayerOK lcRegisterPlayerOK;

		lcRegisterPlayerOK.setGroupName(g_pGameServerGroupInfoManager->getGameServerGroupInfo(ServerGroupID, WorldID)->getGroupName());

		string SSN = pPacket->getSSN();
		string preSSN;
		bool isChina = false;
		// 한국
		if (strstr(SSN.c_str(), "-") != NULL )
		{
			preSSN = SSN.substr(0, 6);
		}
		// 중국
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
				// 이런 경우는 없다고 하지만 -_- 머 암튼
			 	preSSN = SSN.substr(0, 6);
			}
		}
//        string preSSN = pPacket->getSSN().substr(0, 6).c_str();

		StringStream AdultSSN;

		time_t daytime = time(0);
		tm Timec;
		localtime_r(&daytime, &Timec);
		AdultSSN << Timec.tm_year - 20 << Timec.tm_mon << Timec.tm_mday;

		// 성인인지 아닌지 주민등록 번호 체크
		if (atoi(preSSN.c_str()) <= atoi(AdultSSN.toString().c_str())) {
			lcRegisterPlayerOK.setAdult(true);
		} else {
			lcRegisterPlayerOK.setAdult(false);
		}

		// 중국이면 무조건 성인
		if (isChina )
		{
			lcRegisterPlayerOK.setAdult(true);
		}

		pLoginPlayer->sendPacket(&lcRegisterPlayerOK);

		// 이름을 변경해줘야 한다.
		pLoginPlayer->setID(pPacket->getID());

		// 등록에 성공했을 경우, CLGetPCList 패킷을 기다린다.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);

		SAFE_DELETE(pStmt);
	} 
	catch (DuplicatedException & de) 
	{
		SAFE_DELETE(pStmt);

		//cout << de.toString() << endl;

		//--------------------------------------------------------------------------------
		// 등록 실패 패킷을 전송한다.
		//--------------------------------------------------------------------------------
		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//--------------------------------------------------------------------------------
		// 실패 회수를 증가시킨다. 너무 많이 실패했을 경우, 연결을 종료한다.
		//--------------------------------------------------------------------------------
		uint nFailed = pLoginPlayer->getFailureCount();

		//cout << pLoginPlayer->getID() << "'s Failure Count = " << ++nFailed << endl;

		if (nFailed > 3) 
			throw DisconnectException("too many failure");

		pLoginPlayer->setFailureCount(nFailed);

		// 등록에 실패할 경우, 다시 CLRegisterPlayer 패킷을 기다린다.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);

	} 
	catch (SQLQueryException & sqe) 
	{
		SAFE_DELETE(pStmt);

		// 흠. SQL 에러이든지 등록이 잘 안되었다는 소리다.
		//cout << sqe.toString() << endl;

		//--------------------------------------------------------------------------------
		// 등록 실패 패킷을 전송한다.
		//--------------------------------------------------------------------------------
		lcRegisterPlayerError.setErrorID(ETC_ERROR);

		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//--------------------------------------------------------------------------------
		// 실패 회수를 증가시킨다. 너무 많이 실패했을 경우, 연결을 종료한다.
		//--------------------------------------------------------------------------------
		uint nFailed = pLoginPlayer->getFailureCount();

		//cout << pLoginPlayer->getID() << "'s Failure Count = " << ++nFailed << endl;

		if (nFailed > 3) 
			throw DisconnectException("too many failure");

		pLoginPlayer->setFailureCount(nFailed);

		// 등록에 실패할 경우, 다시 CLRegisterPlayer 패킷을 기다린다.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);

	}

	__END_DEBUG

#endif
		
	__END_DEBUG_EX __END_CATCH
}
