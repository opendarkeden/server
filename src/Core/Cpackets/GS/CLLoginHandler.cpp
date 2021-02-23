//////////////////////////////////////////////////////////////////////////////
// Filename    : CLLoginHandler.cpp
// Written By  : Reiot
// Description : 
//
// 이 패킷은 클라이언트가 아이디와 패스워드를 암호화해서 
// 로그인 서버로 전송한다. 로그인 서버는 이 패킷을 받아서
// 플레이어의 아이디와 패스워드가 정확한지 DB로부터 읽어서
// 비교한 후, 로그인의 성공 여부를 전송한다.
//
// *CAUTION*
//
// 특정 아이디와 패스워드를 가진 플레이어를 검색하는 SQL 문으로 어떤 것이 
// 더 효율적일까?
//
// (1) SELECT Password FROM Player WHERE ID = 'AAA' 으로 검색한 후, 
//     패스워드를 비교한다.
// (2) SELECT ID FROM Player WHERE ID = 'AAA' AND Password = 'BBB' 으로 
//     검색해서 리턴하는 row 가 있는지 체크한다.
//
// 이에 따라서, 인덱스를 어떻게 설정하는지가 결정되겠다.
//
// (1) - CREATE INDEX PlayerIDIndex ON Player (ID)
// (2) - CREATE INDEX PlayerIDPasswordIndex ON Player (ID , Password)
//
// 현재의 선택은 (2) 되겠다.
//
// *CAUTION*
// 
// 같은 플레이어의 동시 접속을 막기 위해서 Player 테이블의 LogOn 컬럼값을
// 체크해야 한다. 만약 LogOn = 'LOGON' 일 경우, 이미 접속하고 있다고 간주
// 해야 하므로, 이런 사람은 접속을 차단해야 한다. (물론 적절한 메시지를
// 출력해줘야 한다.)
//
// 주의할 점은, 서버가 crash 될 경우 새로 띄워질때 LogOn 필드를 모두
// LOGOFF 로 초기화해줘야 한다는 점이다.
//////////////////////////////////////////////////////////////////////////////
/*

   // 넷마블의 Player table에 필요한것 정리. by sigi. 2002.10.23

   PlayerID,
   Password,	// 다른 의미.
   CurrentWorldID, 
   CurrentServerGroupID, 
   CurrentLoginServerID, 
   SpecialEventCount,
   LogOn, 
   Access, 
   LoginIP, 
   PayType, PayPlayDate, PayPlayHours, PayPlayFlag 
   LastSlot, 
   LastLoginDate, 
   LoginIP


   // 넷마블에서 작업해줘야하는 것
   UPDATE Player SET Password='12345678' WHERE PlayerID='playerid';

   if (getAffectedRowCount()==0)
   {
   		INSERT INTO Player (PlayerID, Password) Values ( 'playerid', '12345678' );
   }


*/

#include "CLLogin.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"

	#include "DatabaseManager.h"
	#include "GameServerGroupInfoManager.h"
	#include "GameServerInfoManager.h"

	#include "Lpackets/LCLoginOK.h"
	#include "Lpackets/LCLoginError.h"
	#include "UserInfoManager.h"
	#include "Assert.h"
	#include "Properties.h"
	#include "DB.h"

	#include <sys/time.h>
	#include <time.h>

	#include "gameserver/billing/BillingPlayerManager.h"

	#include "types/ServerType.h"

	#include "chinabilling/CBillingInfo.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
	#include "chinabilling/CBillingPlayerManager.h"
#endif

#endif

#define SYMBOL_TEST_CLIENT '#'	// 사내테스트 버전인 경우
#define SYMBOL_NET_MARBLE_CLIENT '@'	// 넷마블에서 접속하는 경우

bool isAdultByBirthday(const string& birthday);
void addLoginPlayerData(const string& ID, const string& ip, const string& SSN, const string& zipcode);
// add By Coffee 2007-6-15
void addLoginPlayerData(const string& ID, const string& ip, const string& SSN, const string& zipcode, const string& MAC);
bool isBlockMAC(const string& MAC);
// add end by Coffee 2007-6-15
bool isBlockIP(const string& ip);


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CLLoginHandler::execute (CLLogin* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//add by zdj
	cout << pPacket->toString().c_str() << endl;

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	Statement*   pStmt        = NULL;

	// 좌우 공백 제거. by sigi. 2002.12.6
	pPacket->setID( trim(pPacket->getID()) );

	string          connectIP            = pLoginPlayer->getSocket()->getHost();
	string			connectMAC			 = pPacket->getMacAddress();
	string          ID                   = pPacket->getID();

	// MAC address setting
	pLoginPlayer->setMacAddress( pPacket->getRareMacAddress() );

	bool bFreePass = false;	//by sigi. 2002.10.23j

	// web login
	bool bWebLogin = pPacket->isWebLogin();
//	static bool bWebLogin = g_pConfig->getPropertyInt("WebLogin") != 0;

	//add by zdj
	cout << "CLLoginHandler.cpp step1" << endl;

	// set web login player
	if ( bWebLogin ) 
	{
		pLoginPlayer->setWebLogin();
		//add by zdj
		cout << "CLLoginHandler.cpp step2" << endl;
	
	}

//	cout << pPacket->toString() << endl;

	if ( isBlockIP(connectIP) || isBlockMAC(connectMAC))
	{
		LCLoginError lcLoginError;
		lcLoginError.setErrorID(IP_DENYED);
		pLoginPlayer->sendPacket(&lcLoginError);

		cout << "IP_DENYED:" << connectIP.c_str() << endl;

		filelog( "loginfail.txt", "Error Code: IP_DENYED, 1, PlayerID : %s", pPacket->getID().c_str() );
		return;
	}

	//add by zdj
	cout << "CLLoginHandler.cpp step3" << endl;


	// 사내테스트 버전에서는 '#sigi'  <-- 이런 식으로 계정이 들어온다.
	if (ID[0]==SYMBOL_TEST_CLIENT)
	{

		//add by zdj
		cout << "CLLoginHandler.cpp step4" << endl;

		ID = ID.c_str()+1;
		pPacket->setID( ID );

		// 웹 로그인 체크
		if ( bWebLogin )
		{

			cout << "WebLogin" << endl;

			if ( !checkWebLogin( pPacket, pPlayer ) )
			{
				return;
			}
			else
				cout << "Web Login OK" << endl;
		}
		else
		{
			cout << "not WebLogin" << endl;

			// 넷마블에서 접속하는 경우
			// by sigi. 2002.10.23
			if (!checkNetMarbleClient( pPacket, pPlayer ))
			{
				return;
			}
		}
	
		bFreePass = pLoginPlayer->isFreePass();
		if (!bWebLogin && bFreePass)
		{
			//add by zdj
			cout << "CLLoginHandler.cpp step5" << endl;

			// 웹로그인이 아닌 FreePass 는 넷마블 사용자로 ID 앞에 예약문자가 하나더 있다.
			ID = ID.c_str()+1;
			pPacket->setID( ID );
		}

//		cout << "테스트 클라이언트" << endl;
		BEGIN_DB
		{
			//add by zdj
			cout << "CLLoginHandler.cpp step6" << endl;

			// 증거를 남긴다.
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery(
				"INSERT INTO TestClientUser (PlayerID, IP, LoginDate) VALUES ('%s', '%s', now())", 
				ID.c_str(), connectIP.c_str());

			SAFE_DELETE(pStmt);
		} 
		END_DB(pStmt)
	}
	// 넷마블에서 접속하는 경우
	else 
	{
		//add by zdj
		cout << "CLLoginHandler.cpp step7" << endl;

		// 웹 로그인 체크
		if ( bWebLogin )
		{
			cout << "WebLogin" << endl;

			if ( !checkWebLogin( pPacket, pPlayer ) )
			{
				return;
			}
			else
				cout << "Web Login OK" << endl;
		}
		else
		{
			cout << "not WebLogin" << endl;

			// by sigi. 2002.10.23
			if (!checkNetMarbleClient( pPacket, pPlayer ))
			{
				return;
			}
		}

		bFreePass = pLoginPlayer->isFreePass();

		/*
		if (bFreePass)
		{
			ID = ID.c_str()+1;
			pPacket->setID( ID );
		}
		*/
	}

	string          PASSWORD             = pPacket->getPassword();
	string          SSN                  = "";
	ServerGroupID_t CurrentServerGroupID = 0;
	string          logon                = "";
	string          access               = "";
	string          zipcode              = "";

	string          lastIP       	     = "";
	string          lastMacAddress		 = "";

	// 빌링~ by sigi. 2002.5.31
	PayType			payType;
	string			payPlayDate;
	string			familyPayPlayDate;
	uint			payPlayHours;
	uint			payPlayFlag;
	bool			bAdult = false;

	try 
	{
		////////////////////////////////////////////////////////////
		// ID랑 PASSWORD에 이상한 문자가 들어있으면
		// 못 들어오게 막는다.
		////////////////////////////////////////////////////////////
		bool bError = false;

		if (ID.find_first_of("'\\", 0) < ID.size()) bError = true;
		if (PASSWORD.find_first_of("'\\", 0) < PASSWORD.size()) bError = true;

		if (bError)
		{
//			cout << "이상한 글자" << endl;
			//cout << "Error" << endl;
			LCLoginError lcLoginError;
			lcLoginError.setErrorID(INVALID_ID_PASSWORD);	
			pLoginPlayer->sendPacket(&lcLoginError);

			filelog( "loginfail.txt", "Error Code: INVALID_ID_PASSWORD, 2, PlayerID : %s", pPacket->getID().c_str() );
			return;
		}

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = NULL;
		
		// BINARY를 붙이면. 대소문자 구분을 하게 된다. 
		// 지금까지는 대소문자 관계없이 login할 수 있었는데..
		// 이게 빌링시스템쪽에서 문제가 돼서 수정했다. by sigi. 2002.12.20
		// BINARY PlayerID='%s'였는데.. 그냥 PlayerID를 다시 읽어와서 쓰는게 나을거 같아서..
		if ( bWebLogin )
		{
			pResult = pStmt->executeQuery(
				"SELECT PlayerID, SSN, CurrentServerGroupID, LogOn, Access, LoginIP, PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s'", 
				ID.c_str());
		}
		else if (bFreePass)	// by sigi. 2002.10.23
		{
			pResult = pStmt->executeQuery(
//				"SELECT PlayerID, CurrentServerGroupID, LogOn, Access, LoginIP, MacAddress,PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s'", 
				"SELECT PlayerID, CurrentServerGroupID, LogOn, Access, LoginIP, PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s'", 
				ID.c_str());
		}
		else
		{
			if ( g_pConfig->hasKey("DB_VERSION") && g_pConfig->getProperty("DB_VERSION")[0] == '4' )
			{
				pResult = pStmt->executeQuery(
					"SELECT PlayerID, SSN, CurrentServerGroupID, LogOn, Access, ZipCode, LoginIP, PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s' AND Password = OLD_PASSWORD('%s')", 
					ID.c_str() , PASSWORD.c_str());
			}
			else
			{
				pResult = pStmt->executeQuery(
	//				"SELECT PlayerID, SSN, CurrentServerGroupID, LogOn, Access, ZipCode, LoginIP, MacAddress,PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s' AND Password = PASSWORD('%s')", 
					"SELECT PlayerID, SSN, CurrentServerGroupID, LogOn, Access, ZipCode, LoginIP, PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID = '%s' AND Password = PASSWORD('%s')", 
					ID.c_str() , PASSWORD.c_str());
			}
		}

		// by sigi. 2002.10.30
		// Player가 없다 : 없고 넷마블이 아닌 경우
		bool bNoPlayer = ((pResult->getRowCount() == 0) && !bFreePass);

		// 쿼리 결과 ROW 의 개수가 0 이라는 뜻은 
		// invalid ID or Password 라는 뜻이다.
		if (bNoPlayer)	//pResult->getRowCount() == 0) 
		{
			//cout << "no Result : " << ID.c_str() << endl;
//			cout << "플레이어 없음" << endl;
			LCLoginError lcLoginError;
			lcLoginError.setErrorID(INVALID_ID_PASSWORD);
			pLoginPlayer->sendPacket(&lcLoginError);
			filelog( "loginfail.txt", "Error Code: INVALID_ID_PASSWORD, 3, PlayerID : %s", pPacket->getID().c_str() );

			// 실패 회수가 3보다 클 경우, 연결을 종료한다.
			uint nFailed = pLoginPlayer->getFailureCount();

//			cout << "실패 회수 " << nFailed << endl;

			if (nFailed > 3) 
			{
				SAFE_DELETE(pStmt);
				throw DisconnectException("too many failure");
			}

			pLoginPlayer->setFailureCount(nFailed);
			pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);

			return;
		} 
		// 쿼리 결과가 있다는 말은
		// 올바른 ID와 패스워드라는 말이다...
		else
		{
			int i = 0;

			if ( bWebLogin )
			{
				pResult->next();

				pPacket->setID( pResult->getString(++i) );	ID=pPacket->getID(); // by sigi. 2002.12.21
				SSN                  = pResult->getString(++i);
				CurrentServerGroupID = pResult->getInt(++i);
				logon                = pResult->getString(++i);
				access               = pResult->getString(++i);
				zipcode				= "000-000";
				lastIP               = pResult->getString(++i);
				payType              = (PayType)pResult->getInt(++i);
				payPlayDate          = pResult->getString(++i);
				payPlayHours         = pResult->getInt(++i);
				payPlayFlag          = pResult->getInt(++i);
				familyPayPlayDate    = pResult->getString(++i);

			}
			else if (bFreePass)
			{
				// 넷마블인 경우에.. 계정이 없다면.. 바로 생성해야 한다.
				if (pResult->getRowCount() == 0) 
				{
					/*
					cout << "NetMarble New Player: " << ID.c_str() << endl;

					pStmt->executeQuery("INSERT INTO Player (PlayerID, Password, Name, SSN, Event) Values ('%s', '%s', '%s', '123456-1122339', 0)",
											ID.c_str(), PASSWORD.c_str(), ID.c_str());										

					CurrentServerGroupID = 0;
					logon                = "LOGOFF";
					access               = "ALLOW";
					zipcode				=  "000-000";
					lastIP               = "255.255.255.255";
					payType              = PAY_TYPE_PERIOD;
					payPlayDate          = "2002-07-15 00:00:00";
					payPlayHours         = 0;
					payPlayFlag          = 0;
					*/

					// checkFreePass()에서 추가하므로 있어야 한다.
					LCLoginError lcLoginError;
					lcLoginError.setErrorID(ETC_ERROR);
					pLoginPlayer->sendPacket(&lcLoginError);
					pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);
					filelog( "loginfail.txt", "Error Code: ETC_ERROR, 4, PlayerID : %s", pPacket->getID().c_str() );
					SAFE_DELETE(pStmt);
				}
				else
				{
					cout << "NetMarble Player: " << ID.c_str() << endl;

					pResult->next();

					pPacket->setID( pResult->getString(++i) );	ID=pPacket->getID(); // by sigi. 2002.12.21
					CurrentServerGroupID = pResult->getInt(++i);
					logon                = pResult->getString(++i);
					access               = pResult->getString(++i);
					zipcode				= "000-000";
					lastIP               = pResult->getString(++i);
//					/*inthesky*/lastMacAddress    = pResult->getString(++i);
					payType              = (PayType)pResult->getInt(++i);
					payPlayDate          = pResult->getString(++i);
					payPlayHours         = pResult->getInt(++i);
					payPlayFlag          = pResult->getInt(++i);
					familyPayPlayDate    = pResult->getString(++i);
				}
			}
			else
			{
				cout << "Normal Player: " << ID.c_str() << endl;

				pResult->next();

				pPacket->setID( pResult->getString(++i) );	ID=pPacket->getID(); // by sigi. 2002.12.21
				SSN                  = pResult->getString(++i);
				CurrentServerGroupID = pResult->getInt(++i);
				logon                = pResult->getString(++i);
				access               = pResult->getString(++i);
				zipcode              = pResult->getString(++i);
				lastIP               = pResult->getString(++i);
//				/*inthesky*/lastMacAddress	 = pResult->getString(++i);
				payType              = (PayType)pResult->getInt(++i);
				payPlayDate          = pResult->getString(++i);
				payPlayHours         = pResult->getInt(++i);
				payPlayFlag          = pResult->getInt(++i);
				familyPayPlayDate    = pResult->getString(++i);
			}

			pLoginPlayer->setServerGroupID(CurrentServerGroupID);

//			if (access == "DENY" || access == "WAIT") 
			if (access != "ALLOW")
			{
				LCLoginError lcLoginError;
				lcLoginError.setErrorID(ETC_ERROR);
				pLoginPlayer->sendPacket(&lcLoginError);
				pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);
				filelog( "loginfail.txt", "Error Code: ETC_ERROR, 5, PlayerID : %s", pPacket->getID().c_str() );
				SAFE_DELETE(pStmt);
				return;
			}

			#if defined(__THAILAND_SERVER__)
			// add by inthesky for THAILAND child guard rule
			bool bChildGuardArea = onChildGuardTimeArea(g_pConfig->getPropertyInt("CHILDGUARD_START_TIME"),g_pConf

			cout << "Global ChildGuard Policy : " << g_pConfig->getProperty("CHILDGUARD") << endl;
			cout << "ChildGuard Start Time : " << (int)g_pConfig->getPropertyInt("CHILDGUARD_START_TIME") << endl;
			cout << "ChildGuard End Time : " << (int)g_pConfig->getPropertyInt("CHILDGUARD_END_TIME") << endl;

			if(bChildGuardArea)     cout << "ChildGuard System : RUN" << endl;
			else                    cout << "ChildGuard System : STOP" << endl;

			if(bPermission) cout << "(" << ID << ") Permission : ALLOW" << endl;
			else            cout << "(" << ID << ") Permission : DENY" << endl;

			if (!bPermission && bChildGuardArea )
			{

				LCLoginError lcLoginError;
				lcLoginError.setErrorID(CHILDGUARD_DENYED);
				pLoginPlayer->sendPacket(&lcLoginError);
				pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);
				SAFE_DELETE(pStmt);

				return;

			}
			#endif


#ifdef __PAY_SYSTEM_LOGIN__
			// 빌링 by sigi. 2002.5.31
			if (!pLoginPlayer->loginPayPlay(payType, 
											payPlayDate, payPlayHours, payPlayFlag,
											connectIP, ID))
			{
				// 돈 안 낸 계정이다. 냥~~
				LCLoginError lcLoginError;
				lcLoginError.setErrorID(NOT_PAY_ACCOUNT);
				pLoginPlayer->sendPacket(&lcLoginError);
				pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);
				filelog( "loginfail.txt", "Error Code: NOT_PAY_ACCOUNT, 6, PlayerID : %s", pPacket->getID().c_str() );
				SAFE_DELETE(pStmt);
				return;
			}
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)
			// 빌링 by sigi. 2002.11.21
			if (pLoginPlayer->loginPayPlay(payType, 
											payPlayDate, payPlayHours, payPlayFlag,
											connectIP, ID))
			{
				// 일단 그냥 들어가둔다.
			}
#else //elif defined(__PAY_SYSTEM_ZONE__)
	        pLoginPlayer->setPayPlayValue(payType, payPlayDate, payPlayHours, payPlayFlag, familyPayPlayDate);
#endif

			// 이미 게임 중에 접속되어 있다면, 접속할 수 없다.
			bool bSameIP = false;
			if (logon == "LOGON" || 
				logon == "GAME")
			{
				// LOGON상태라면 같은 IP에서 접속했으면 접속 가능
				//if (logon=="LOGON" && connectIP==lastIP)
				//{
				//}
				// (!) IP가 다르면 재접불가다.
				//else 

				// LOGON상태에서는 재접 불가하다.
				// IP 접속지가 다르면.. GAME이라도 접속불가다.
				if (logon=="LOGON" || connectIP!=lastIP)// || !pPacket->checkMacAddress(lastMacAddress))
				{

					LCLoginError lcLoginError;
					//lcLoginError.setMessage("already connected");	
					lcLoginError.setErrorID(ALREADY_CONNECTED);	
					pLoginPlayer->sendPacket(&lcLoginError);
					filelog( "loginfail.txt", "Error Code: ALREADY_CONNECTED, 7, PlayerID : %s", pPacket->getID().c_str() );

					// 실패 회수가 3보다 클 경우, 연결을 종료한다.
					uint nFailed = pLoginPlayer->getFailureCount();

					if (nFailed > 3) 
					{
						SAFE_DELETE(pStmt);
						throw DisconnectException("too many failure");
					}

					SAFE_DELETE(pStmt);
					pLoginPlayer->setFailureCount(nFailed);
					pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);
					return;

					//bSameIP = false;
				}
					// GAME이고 IP가 같은 경우
				else
				{
					bSameIP = true;
				}
			}

			// -- 돈 복사 때문에 잠시 봉인
			// '이미 접속 중'인데..
			// 강제 접속 해제를 시키길 기다리는 상태로 설정한다.
			if (bSameIP)
			{
				if ( !bFreePass || bWebLogin )	// by sigi. 2002.10.23
				{
					// 한국
					if ( strstr(SSN.c_str(), "-") != NULL )
					{
						bAdult = isAdultByBirthday( SSN.substr(0, 6) );
					}
					// 중국
					else 
					{
#ifdef __CHINA_SERVER__
						// 중국은 무조건 성인
						bAdult = true;
#else
						if (SSN.size() == 15)
						{
							bAdult = isAdultByBirthday( SSN.substr(6, 12) );
						}
						else if (SSN.size() == 18)
						{
							bAdult = isAdultByBirthday( SSN.substr(8, 14) );
						}
						else
						{
							// 이런 경우는 없다고 하는데 -_-a
							bAdult = false;
						}
#endif
						//add by zdj 2005.5.11
						bAdult = true;
					}
				}

				// 일단 PlayerID를 저장해둔다.
				pLoginPlayer->setID(ID);
				pLoginPlayer->setSSN( SSN );
				pLoginPlayer->setZipcode( zipcode );

				// 이 경우는 GameServer의 응답을 받아야지 LCLoginOK를 보내기 때문에
				// 일단, 쿼리 결과를 이용해서 값을 저장해둔다.
				pLoginPlayer->setAdult( bAdult );

				pLoginPlayer->sendLGKickCharacter();

				SAFE_DELETE(pStmt);
				return;
			}

			//if (logon == "LOGOFF" || bSameIP)
			if (logon == "LOGOFF"
				|| logon=="LOGON")
			{

				__BEGIN_DEBUG

				/*
				if (bSameIP)
				{
					// 로그인에 성공했으면, LogOn 정보를 LOGOFF 에서 LOGON 으로 변경한다.
					pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGON' WHERE PlayerID = '%s'",ID.c_str());
				}
				else
				{
				*/
					// LOGOFF인 경우만 LOGON으로 바꾼다.
					// by sigi. 2002.5.15
//					pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGON', LoginIP = '%s',MacAddress = '%s', CurrentLoginServerID=%d, LastLoginDate=now() WHERE PlayerID = '%s' AND LogOn='LOGOFF'",connectIP.c_str(), connectMAC.c_str(),g_pConfig->getPropertyInt("LoginServerID"), ID.c_str());
					pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGON', LoginIP = '%s', CurrentLoginServerID=%d, LastLoginDate=now() WHERE PlayerID = '%s' AND LogOn='LOGOFF'",connectIP.c_str(), g_pConfig->getPropertyInt("LoginServerID"), ID.c_str());
					int affectedRowCount = pStmt->getAffectedRowCount();
					
					// 최근 접속 IP를 5개까지 남긴다. IP Table은 별도로 기록한다.
					// LoginPlayerData 에 IP를 남기므로 필요없다. by bezz 2003.04.21
					//pStmt->executeQuery("UPDATE PlayerIPList SET IP1=IP2, Date1=Date2, IP2=IP3, Date2=Date3, IP3=IP4, Date3=Date4, IP4=IP5, Date4=Date5, IP5='%s', Date5=now() WHERE PlayerID='%s'",connectIP.c_str(),  ID.c_str());

					//if (pStmt->getAffectedRowCount()==0)
					//{
					//	pStmt->executeQuery("INSERT IGNORE INTO PlayerIPList (PlayerID) Values('%s')",
					//							ID.c_str());
					//}

				    // LogOn이 LOGOFF가 아니거나.
					// PlayerID가 없거나.. -_-
					if (affectedRowCount==0)
					{

						// 다른 LoginServer에 이미 접속되어 있는지 확인하고
						// 이미 있다면 그 Player를 kick하고
						// 여기서 접속할 수 있게 설정해야 한다.

						// 일단 다 막는다. 뭔가 문제가 있어서 LogOn 상태는 허용시켜놓은것 같은데
						// 문제가 생기면 다시 푼다. by bezz 2003.07.07

						// LogOn 상태는 일단 허용시켜 본다.
						//pStmt->executeQuery("UPDATE Player SET LoginIP = '%s', CurrentLoginServerID=%d, LastLoginDate=now() WHERE PlayerID = '%s' AND LogOn='LOGON'",connectIP.c_str(), g_pConfig->getPropertyInt("LoginServerID"), ID.c_str());

						//if (pStmt->getAffectedRowCount()==0)
						//{
							LCLoginError lcLoginError;
							//lcLoginError.setMessage("already connected");	
							lcLoginError.setErrorID(ALREADY_CONNECTED);	
							pLoginPlayer->sendPacket(&lcLoginError);
							filelog( "loginfail.txt", "Error Code: ALREADY_CONNECTED, 8, PlayerID : %s", pPacket->getID().c_str() );

							SAFE_DELETE(pStmt);
							pLoginPlayer->setPlayerStatus(LPS_BEGIN_SESSION);
							
							return;
						//}

						// LogOn상태로 login이 허용된 상태
					}
				/*
				}
				*/

				__END_DEBUG

				// 일단 인증이 되었으므로, 아이디를 로그인 플레이어 객체에 저장한다.
				pLoginPlayer->setID(ID);

				// loginserver 에서 billing 부분 빼기로 한다.
				// 애드빌 요청. by bezz 2003.04.22
//#ifdef __CONNECT_BILLING_SYSTEM__
			// by sigi. 2002.11.21
			//pLoginPlayer->setBillingSession();

			//pLoginPlayer->sendBillingLogin();
//#endif
#ifdef __CONNECT_CBILLING_SYSTEM__
				// 중국 빌링 서버에 로그인 하라고 알린다.
				g_pCBillingPlayerManager->sendLogin( pLoginPlayer );
#endif


				// 로그인 전에는 무조건 게임서버에 이 패킷 보내서 
				// 접속해 있지만 DB 에 잘못 기록되 중복 로긴이 되는 것을 막는다 
//				pLoginPlayer->sendLGKickCharacter();

				// 로그인 성공을 알려준다.
				LCLoginOK lcLoginOK;
				lcLoginOK.setFamily( false );

				if ( !bFreePass || bWebLogin )	// by sigi. 2002.10.23
				{
					// 한국 
					if ( strstr(SSN.c_str(), "-") != NULL )
					{
						bAdult = isAdultByBirthday( SSN.substr(0, 6) );
					}
					// 중국
					else 
					{
#ifdef __CHINA_SERVER__
						// 중국은 무조건 성인
						bAdult = true;
#else
						if (SSN.size() == 15)
						{
							bAdult = isAdultByBirthday( SSN.substr(6, 12) );
						}
						else if (SSN.size() == 18)
						{
							bAdult = isAdultByBirthday( SSN.substr(8, 14) );
						}
						else
						{
							// 이런 경우는 없다고 하는데 -_-a
							bAdult = false;
						}
#endif
						//add by zdj 2005.5.11
						bAdult = true;
					}
				}

				if (g_pConfig->getPropertyInt("IsNetMarble")==1)
					bAdult = pPacket->isAdult();

				lcLoginOK.setAdult( bAdult );

#ifndef __CONNECT_BILLING_SYSTEM__

#ifdef __CHINA_SERVER__
				lcLoginOK.setLastDays( 0xffff );
#else

//				if ( pLoginPlayer->getPayType() == 0 || pLoginPlayer->isFamilyPayAvailable() ) 
				if ( pLoginPlayer->getPayType() == 0 ) 
					lcLoginOK.setLastDays( 0xfffe );
				else
				{
					int lastDays = VSDateTime::currentDateTime().daysTo( pLoginPlayer->getPayPlayAvailableDateTime() );
					int lastSecs = VSDateTime::currentDateTime().secsTo( pLoginPlayer->getPayPlayAvailableDateTime() );

					int familyLastDays = VSDateTime::currentDateTime().daysTo( pLoginPlayer->getFamilyPayPlayAvailableDateTime() );
					int familyLastSecs = VSDateTime::currentDateTime().secsTo( pLoginPlayer->getFamilyPayPlayAvailableDateTime() );

					if ( lastSecs < 0 && familyLastSecs < 0 )
					{
						if ( pLoginPlayer->getPayPlayAvailableHours() > 0 ) lcLoginOK.setLastDays( 0xfffe );
						else lcLoginOK.setLastDays( 0xfffe );
					}
					else 
					{
						if ( lastSecs < familyLastSecs )
						{
							lcLoginOK.setFamily( true );
							lcLoginOK.setLastDays( familyLastDays );

							cout << "Family 요금제" << endl;
						}
						else 
						{
							lcLoginOK.setFamily( false );
							lcLoginOK.setLastDays( lastDays );
							cout << "Premium 요금제" << endl;
						}
					}
				}

				cout << lcLoginOK.getLastDays() << "일 남았습니다." << endl;
				if ( lcLoginOK.getLastDays() > 1000 )
					filelog("PayPlayDateLog.txt", "UserID : %s , LastDays : %ld", ID.c_str() ,lcLoginOK.getLastDays());

				// 컴백 이벤트 관련
				{
					pResult = pStmt->executeQuery( "SELECT PlayerID FROM Event200501Main WHERE PlayerID = '%s' AND RecvPremiumDate = '0000-00-00'",
														pLoginPlayer->getID().c_str() );

					if ( pResult->next() )
					{
						// 컴백 이벤트 대상자다.
						// 프리미엄 7일을 넣어주자
						pStmt->executeQuery( "UPDATE Player SET PayPlayDate = IF ( PayPlayDate < NOW(), NOW() + INTERVAL 7 DAY, PayPlayDate + INTERVAL 7 DAY ) WHERE PlayerID = '%s'",
														pLoginPlayer->getID().c_str() );

						// 컴백 이벤트 프리미엄 7일을 받았다고 넣어주자
						pStmt->executeQuery( "UPDATE Event200501Main SET RecvPremiumDate = NOW() WHERE PlayerID = '%s'", pLoginPlayer->getID().c_str() );

						// 클라이언트에 이벤트 대상자라고 알리기
						lcLoginOK.setLastDays( 0xfffd );
					}
				}
#endif
#endif

				/*
				// 서버 그룹 이름을 셋팅한다.
				// 서버 아이디로 서버의 그룹아이디를 찾은 다음 서버 그룹 정보를 찾는다.
				lcLoginOK.setGroupName(g_pGameServerGroupInfoManager->getGameServerGroupInfo(pLoginPlayer->getServerGroupID())->getGroupName());
				lcLoginOK.setStat(SERVER_FREE);

				UserInfo * pUserInfo = g_pUserInfoManager->getUserInfo( pLoginPlayer->getServerGroupID() );
				BYTE UserModify = 0;

				if( CurrentServerGroupID == 0 || CurrentServerGroupID == 1 || CurrentServerGroupID == 2 || CurrentServerGroupID == 7 ) {
//					UserModify = 200;
				}

				if (pUserInfo->getUserNum() < 100 + UserModify ) 
				{
					lcLoginOK.setStat(SERVER_FREE);
				} 
				else if (pUserInfo->getUserNum() < 250 + UserModify ) 
				{
					lcLoginOK.setStat(SERVER_NORMAL);
				} 
				else if (pUserInfo->getUserNum() < 400 + UserModify ) 
				{
					lcLoginOK.setStat(SERVER_BUSY);
				} 
				else if (pUserInfo->getUserNum() < 500 + UserModify ) 
				{
					lcLoginOK.setStat(SERVER_VERY_BUSY);
				} 
				else if (pUserInfo->getUserNum() >= 500 + UserModify ) 
				{
					lcLoginOK.setStat(SERVER_FULL);
				} 
				else 
				{
					lcLoginOK.setStat(SERVER_DOWN);
				}

				*/
				pLoginPlayer->sendPacket(&lcLoginOK);
				cout << "LoginOK send" << endl;

				pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);
			}
		} // end of if (pResult->getRowCount() == 0) else

		SAFE_DELETE(pStmt);
	} 
	catch (SQLQueryException & sqe) 
	{
		SAFE_DELETE(pStmt);
		throw Error(sqe.toString());
	}

	// 다른 곳에서도 필요한 코드라서. 함수로 뺏당. by sigi. 2002.5.8
	addLoginPlayerData( ID, connectIP, SSN, zipcode ,connectMAC);

#endif
		
	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//
// YYMMDD 로 성인 판별
//
//////////////////////////////////////////////////////////////////////////////
bool
isAdultByBirthday(const string& birthday)
{
	StringStream AdultSSN;

	time_t daytime = time(0);
	tm Timec;
	localtime_r( &daytime, &Timec );

	AdultSSN << Timec.tm_year - 18;
	// tm_mon - range 0 to 11
	if ( (Timec.tm_mon+1) < 10 ) AdultSSN << "0";
	AdultSSN << (Timec.tm_mon+1);
	if ( Timec.tm_mday < 10 ) AdultSSN << "0";
	AdultSSN << Timec.tm_mday;

	cout << "SSN = " << birthday.c_str() << " ADULTSSN = " << AdultSSN.toString().c_str() << endl;

	// 성인인지 아닌지 주민등록 번호 체크
	if (atoi(birthday.c_str()) <= atoi(AdultSSN.toString().c_str()))
	{
		//cout << "어른" << endl;
		return true;
	}
		
	//cout << "애들" << endl;
	return false;
}


//////////////////////////////////////////////////////////////////////////////
//
// add LoginPlayerdata
//
// 접속자 통계를 위해서 
// UserInfo DB의 LoginPlayerData에 Login한 사용자를 추가한다.
//
//////////////////////////////////////////////////////////////////////////////
void
addLoginPlayerData(const string& ID, const string& ip, const string& SSN, const string& zipcode)
{

#ifdef __LOGIN_SERVER__

	Statement* pStmt2 = NULL;

	// [홍창봐라]
	// 밑에꺼 말고..
	// UPDATE Player Set LoginFlagDay=1, LoginFlagWeek=1, LoginFlagMonth=1 WHERE PlayerID='%s'
	// 이 정도로만 해놔도 괜찮지 않을까.. 
	// 시간을 넣어서 쓸 필요가 있는지 확인이 필요하겠지?
	// 누구의 최근 접속 시간 같은걸 UserInfo에서 뽑아서 쓰는가?
	// 근데 이거 SSN은 왜 넣노? 나이 통계도 뽑나?
	// 글고. DARKEDEN이랑 DB는 분리된채로 두는게 나을까?
	// 근무시간이 다르니 답답하군.

	// 유저 통계 관련 정보를 입력한다.
	BEGIN_DB
	{
		// 먼저 현재 시간을 얻어낸다.
		int year, month, day, hour, minute, second;
		getCurrentTimeEx(year, month, day, hour, minute, second);
		string currentDT = VSDateTime::currentDateTime().toDateTime();

		StringStream sql;
		/*
		sql << "INSERT INTO LoginPlayerData (Year,Month,Day,Hour,Minute,Second,PlayerID,SSN,ZipCode,Date,Time) VALUES ("
			<< year << "," << month << "," << day << "," << hour << "," << minute << "," << second << ",'"
			<< ID << "','" << SSN << "','" << zipcode << "','"
			<< currentDT.substr( 0, 10 ).c_str() << "','" << currentDT.substr( 11 ).c_str() << "')";
		*/
		sql << "INSERT INTO LoginPlayerData (PlayerID,IP,Date,Time) VALUES ('"
			<< ID << "','" << ip << "','" 
			<< currentDT.substr( 0, 10 ).c_str() << "','" << currentDT.substr( 11 ).c_str() << "')";

		pStmt2 = g_pDatabaseManager->getUserInfoConnection()->createStatement();
		pStmt2->executeQuery(sql.toString());

		SAFE_DELETE(pStmt2);	// 2002.1.16 by sigi
	}
	END_DB(pStmt2)

#endif

}
//////////////////////////////////////////////////////////////////////////
// add By Coffee 2007-6-15 藤속괏닸MAC뒈囹돕鑒앴욋
//////////////////////////////////////////////////////////////////////////
void addLoginPlayerData(const string& ID, const string& ip, const string& SSN, const string& zipcode, const string& MAC)
{
#ifdef __LOGIN_SERVER__

	Statement* pStmt2 = NULL;

	// [홍창봐라]
	// 밑에꺼 말고..
	// UPDATE Player Set LoginFlagDay=1, LoginFlagWeek=1, LoginFlagMonth=1 WHERE PlayerID='%s'
	// 이 정도로만 해놔도 괜찮지 않을까.. 
	// 시간을 넣어서 쓸 필요가 있는지 확인이 필요하겠지?
	// 누구의 최근 접속 시간 같은걸 UserInfo에서 뽑아서 쓰는가?
	// 근데 이거 SSN은 왜 넣노? 나이 통계도 뽑나?
	// 글고. DARKEDEN이랑 DB는 분리된채로 두는게 나을까?
	// 근무시간이 다르니 답답하군.

	// 유저 통계 관련 정보를 입력한다.
	BEGIN_DB
	{
		// 먼저 현재 시간을 얻어낸다.
		int year, month, day, hour, minute, second;
		getCurrentTimeEx(year, month, day, hour, minute, second);
		string currentDT = VSDateTime::currentDateTime().toDateTime();

		StringStream sql;
		/*
		sql << "INSERT INTO LoginPlayerData (Year,Month,Day,Hour,Minute,Second,PlayerID,SSN,ZipCode,Date,Time) VALUES ("
		<< year << "," << month << "," << day << "," << hour << "," << minute << "," << second << ",'"
		<< ID << "','" << SSN << "','" << zipcode << "','"
		<< currentDT.substr( 0, 10 ).c_str() << "','" << currentDT.substr( 11 ).c_str() << "')";
		*/
		sql << "INSERT INTO LoginPlayerData (PlayerID,IP,Date,Time,SSN) VALUES ('"
			<< ID << "','" << ip << "','" 
			<< currentDT.substr( 0, 10 ).c_str() << "','" << currentDT.substr( 11 ).c_str() << "','" << MAC << "')";

		pStmt2 = g_pDatabaseManager->getUserInfoConnection()->createStatement();
		pStmt2->executeQuery(sql.toString());

		SAFE_DELETE(pStmt2);	// 2002.1.16 by sigi
	}
	END_DB(pStmt2)

#endif

}

bool CLLoginHandler::checkNetMarbleClient (CLLogin* pPacket , Player* pPlayer)
	     throw (ProtocolException , Error)
{
    __BEGIN_TRY __BEGIN_DEBUG_EX
#ifdef __LOGIN_SERVER__

	bool isNetmarble = pPacket->isNetmarble();

	if (isNetmarble)	// by sigi. 2002.10.23
	{
		LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

		bool bFreePass = checkFreePass(pPacket, pPlayer);

		if (!bFreePass)
		{
			LCLoginError lcLoginError;
			lcLoginError.setErrorID(INVALID_ID_PASSWORD);	
			pLoginPlayer->sendPacket(&lcLoginError);
			filelog( "loginfail.txt", "Error Code: INVALID_ID_PASSWORD, 9, PlayerID : %s", pPacket->getID().c_str() );

			return false;
		}

		// 일부 체크에서.. FreePass로 넘어가게 된다.
		pLoginPlayer->setFreePass(true);


		//cout << "NetMarble Login OK" << endl;
	}

#endif
	__END_DEBUG_EX __END_CATCH

	return true;
}


bool CLLoginHandler::checkFreePass (CLLogin* pPacket , Player* pPlayer)
	     throw (ProtocolException , Error)
{
    __BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

    Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

	//LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	// key_code를 분석해서
	// DB의 그 ID의 key_code와 비교한다.
	// 같으면 true
	Statement* pStmt = NULL;
	
	try {
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = NULL;
		
		pResult = pStmt->executeQuery(
			"SELECT Password FROM Player WHERE PlayerID = '%s'", 
			pPacket->getID().c_str());

		if (pResult->next())
		{
			string password = pResult->getString(1);
			
			if (password==pPacket->getPassword())
			{
				//cout << "password OK" << endl;
				SAFE_DELETE(pStmt);
				return true;
			}
			else
			{
				//cout << "password wrong: " << password << " != " << pPacket->getPassword().c_str() << endl;
			}
		}
		else
		{
			//cout << "ID wrong: " << pPacket->getID().c_str() << endl;
			// 원래는 안되는건데..
			// 새 사용자는 무조건 추가한다고 넷마블해서 그래 하라네. 헐~~~
			cout << "NetMarble New Player: " << pPacket->getID().c_str() << endl;

			// 여기까지 오면 무조건 넷마블이라고 본다.
			// SpecialEventCount 칼럼은 2로 세팅해준다. 즉, 이벤트 아이템을 이미준걸로 생각
			// 예약가입 한 넘들 한테만 아이템 준다.
			// 2003.04.30 by bezz, DEW
			pStmt->executeQuery("INSERT IGNORE INTO Player (PlayerID, Password, Name, SSN, SpecialEventCount, Event, creation_date) Values ('%s', '%s', '%s', '123456-1122339', 2, 0, CURDATE())",
								pPacket->getID().c_str(), 
								pPacket->getPassword().c_str(), 
								pPacket->getID().c_str());

			//string  connectIP  = pPlayer->getSocket()->getHost();
			// LoginPlayerData 에 IP 정보를 남기므로 필요없다. by bezz 2003.04.21
			//pStmt->executeQuery("INSERT IGNORE INTO PlayerIPList (PlayerID) Values('%s')",
			//						pPacket->getID().c_str());


			return true;
		}


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	} catch (Throwable& t) {
		return false;
	}


#endif
	__END_DEBUG_EX __END_CATCH

	return false;
}

bool isBlockIP(const string& ip)
{

#ifdef __LOGIN_SERVER__

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		uint i = ip.find_first_of('.',0);
		uint j = ip.find_first_of('.',i+1);
		uint k = ip.find_first_of('.',j+1);

		/*
		 * ip = 61.78.53.228
		 * classA = 61
		 * classB = 61.78
		 * classC = 61.78.53
		 */
		string classA = ip.substr(0, i);
		string classB = ip.substr(0, j);
		string classC = ip.substr(0, k);
//		int classD    = atoi(ip.substr(k+1, ip.size()-k-1).c_str());

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT class, first, last FROM IPBlockInfo WHERE
			(IP = '%s' AND class=1) OR
			(IP = '%s' AND class=2) OR
			(IP = '%s')",
			classA.c_str(), classB.c_str(), classC.c_str() );

		while ( pResult->next() )
		{
			int ipClass = pResult->getInt(1);
			int first = pResult->getInt(2);
			int last = pResult->getInt(3);
			int index;

			switch ( ipClass )
			{
				// classC 가 맞고 범위가 지정된 경우
				case 0:
					index = atoi(ip.substr(k+1, ip.size()-k-1).c_str());
					break;
				// classA 가 맞고 범위가 지정된 경우
				case 1:
					index = atoi(ip.substr(i+1, j-i-1).c_str());
					break;
				// classB 가 맞고 범위가 지정된 경우
				case 2:
					index = atoi(ip.substr(j+1, k-j-1).c_str());
					break;
				default:
					index = -1;
					break;

			}

			if ( index < 0 ) return true;

			if ( index >= first && index <= last )
				return true;

/*			if ( ipClass == 0 )
			{
				if ( classD >= first && classD <= last )
				{
					return true;
				}
			}
			else
			{
				return true;
			}*/
		}

		SAFE_DELETE(pStmt); // 2002.1.16 by sigi
	}
	END_DB(pStmt)

	return false;

#endif

}
// 藤속뚤MAC뒈囹쇱꿎
bool isBlockMAC(const string& MAC)
{
#ifdef __LOGIN_SERVER__

	Statement* pStmt = NULL;

	BEGIN_DB
	{


		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT LockMAC, State FROM MACBlockInfo WHERE
			(LockMAC = '%s' AND State='DENY')",
			MAC.c_str());

		while ( pResult->next() )
		{
			/*
			string DenyMAC =pResult->getString(1);
			if (MAC = DenyMAC)
			{
				// ..... 뇹잿덜쯤
				return true;
			}
			*/
			return true;
			

			/*			if ( ipClass == 0 )
			{
			if ( classD >= first && classD <= last )
			{
			return true;
			}
			}
			else
			{
			return true;
			}*/
		}

		SAFE_DELETE(pStmt); // 2002.1.16 by sigi
	}
	END_DB(pStmt)

		return false;

#endif

}
bool CLLoginHandler::checkWebLogin( CLLogin* pPacket, Player* pPlayer )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

#ifdef __LOGIN_SERVER__

    Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	Statement* pStmt = NULL;
	
	try {
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = NULL;
		
		pResult = pStmt->executeQuery(
			"SELECT LoginKey, CreateTime, now() FROM WebLogin WHERE PlayerID = '%s'", 
			pPacket->getID().c_str());

		if (pResult->next())
		{
			string key = pResult->getString(1);
			VSDateTime vsCreate( pResult->getString(2) );
			VSDateTime vsNow( pResult->getString(3) );

			cout << "PlayerID: " << pPacket->getID().c_str() << endl;
			cout << "*DB)     Key: " << key.c_str() << ", create: " << vsCreate.toString().c_str() << ", now:" << vsNow.toString().c_str() << endl;
			cout << "*Packet) Key: " << pPacket->getPassword() << endl;

			// check key
			if ( key != pPacket->getPassword() )
			{
				cout << "키가 틀림 : " << pPacket->getPassword() << endl;
				LCLoginError lcLoginError;
				lcLoginError.setErrorID(INVALID_ID_PASSWORD);	
				pLoginPlayer->sendPacket(&lcLoginError);
				filelog( "loginfail.txt", "Error Code: INVALID_ID_PASSWORD, 10, PlayerID : %s", pPacket->getID().c_str() );
				filelog( "keydiff.txt", "db key: %s, packet key: %s, Player ID: %s", key.c_str(), pPacket->getPassword().c_str(), pPacket->getID().c_str() );

				SAFE_DELETE(pStmt);
				cout << "3" << endl;
				return false;
			}

			// check date time.
			if ( vsCreate.secsTo( vsNow ) > 300 )
			{
				LCLoginError lcLoginError;
				lcLoginError.setErrorID(KEY_EXPIRED);	
				pLoginPlayer->sendPacket(&lcLoginError);
				filelog( "loginfail.txt", "Error Code: KEY_EXPIRED, 12, PlayerID : %s", pPacket->getID().c_str() );

				SAFE_DELETE(pStmt);
				return false;
			}

			// 일부 체크에서.. FreePass로 넘어가게 된다.
			pLoginPlayer->setFreePass(true);

			// 키를 지운다.
			pStmt->executeQuery( "DELETE FROM WebLogin WHERE PlayerID = '%s'", pPacket->getID().c_str() );
		}
		else
		{
			cout << "키가 없다 : " << pPacket->getID() << endl;
			// 키가 없다.
			LCLoginError lcLoginError;
			lcLoginError.setErrorID(NOT_FOUND_KEY);	
			pLoginPlayer->sendPacket(&lcLoginError);
			filelog( "loginfail.txt", "Error Code: NOT_FOUND_KEY, 11, PlayerID : %s", pPacket->getID().c_str() );

			SAFE_DELETE(pStmt);
			cout << "4" << endl;
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	} catch (Throwable& t) {
		cout << "5" << endl;
		return false;
	}

#endif
	__END_CATCH

	return true;
}

#if defined(__THAILAND_SERVER__)
bool CLLoginHandler::onChildGuardTimeArea(int pm, int am, string enable)
{
        bool returnValue = false;
        tm Timem;
        time_t daytime = time(0);
        localtime_r( &daytime, &Timem );

        int Hour    = Timem.tm_hour;
        int Min     = Timem.tm_min;

        int timeValue = (Hour*100) + Min;
        bool bSwitch = (enable == "ENABLE" || enable == "enable" || enable == "Enable" );

        if((timeValue >= pm && timeValue <= am) && bSwitch )
        {
            returnValue = true;
        }
        else if((timeValue <= pm && timeValue <= am) && bSwitch )
        {
            if(am > 1200)   returnValue = false;
            else            returnValue = true;
        }
        else if((timeValue <= pm && timeValue <= am) && bSwitch )
        {
            returnValue = false;
        }
        else if((timeValue >= pm && timeValue >= am) && bSwitch )
        {

            if(am > 1200)   returnValue = false;
            else            returnValue = true;
        }


        return returnValue;
}
#endif
