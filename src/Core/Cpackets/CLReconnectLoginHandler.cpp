//////////////////////////////////////////////////////////////////////////////
// Filename    : CLReconnectLoginHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLReconnectLogin.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
    #include "Assert.h"
	#include "DB.h"
    #include "GameServerInfoManager.h"
	#include "OptionInfo.h"
	#include "ReconnectLoginInfoManager.h"

	#include "Lpackets/LCPCList.h"
	#include "Gpackets/GCDisconnect.h"
	#include "Properties.h"

#endif

//////////////////////////////////////////////////////////////////////////////
// CLReconnectLoginHandler::execute()
//
// 이 패킷은 로그인서버에서 최초로 게임 서버로 연결할 때, 또는 게임 서버에서
// 다른 게임 서버로 이동할 때, 클라이언트가 서버로 전송하는 최초의 패킷이다.
// 이때 플레이어 객체는 새로 생겨난 상태이고, 이 플레이어 객체는 IPM 에서
// 관리되는 상태이다. 
//
// 당연히 최초의 패킷으로 다른 패킷이 넘어오는 경우라면, 이것은 해킹 시도라고
// 봐도 무방하므로 이 패킷이 최초인지 검사해야 한다. 이를 위해서 플레이어 객체에
// 이전 패킷을 저장하고 있으므로, 이 값이 NULL 인지만 보면 되겠다.
//
// 잘못된 패킷이라면, ban 에 등록하고 접속을 종료한다.
//////////////////////////////////////////////////////////////////////////////
void CLReconnectLoginHandler::execute (CLReconnectLogin* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//cout << "CLReconnectLogin : STARTING HANDLING PROCESS" << endl;

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	pLoginPlayer->setWorldID( pPacket->isWebLogin() );
	//pLoginPlayer->setWebLogin( g_pConfig->getPropertyInt("WebLogin") != 0 );

	string PlayerID;

	//----------------------------------------------------------------------
	// 이 패킷을 ReconnectLoginInfo 객체를 갖고 온다.
	// 크래커는 키값과 캐릭터 이름을 일정 시간안에 맞춰야만 접속이 가능하다.
	//----------------------------------------------------------------------
	try 
	{
		ReconnectLoginInfo* pReconnectLoginInfo = g_pReconnectLoginInfoManager->getReconnectLoginInfo(pLoginPlayer->getSocket()->getHost());

		PlayerID = pReconnectLoginInfo->getPlayerID();

		// 플레이어 이름을 저장한다.
		pLoginPlayer->setID(PlayerID);

		// 키값을 인증한다.
		if (pPacket->getKey() != pReconnectLoginInfo->getKey())
			throw InvalidProtocolException("invalid key");

		// 따라서, 현재 시간과 expire time 을 비교한다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (pReconnectLoginInfo->getExpireTime() < currentTime) 
		{
			// 일단 삭제한다.
			g_pReconnectLoginInfoManager->deleteReconnectLoginInfo(pReconnectLoginInfo->getClientIP());
			throw InvalidProtocolException("session already expired");
		}

		// 인증되었으니, ReconnectLoginInfo 를 삭제한다.
		g_pReconnectLoginInfoManager->deleteReconnectLoginInfo(pReconnectLoginInfo->getClientIP());

	} 
	catch (NoSuchElementException & nsee) // 그런 IP를 가진 CI 가 없을 경우
	{ 
		// 흠.. 연결 이후 CLReconnectLogin 패킷을 보내는 딜레이가 너무 길 경우
		// session 이 expire 된다. 이럴 경우에도 짜르자!
		// (예를 들어서, 최초 연결에서는 성공했으나 그다음에 디버깅 상태로
		// 들어갈 경우, CLReconnectLogin 패킷을 보낼 때쯤에는 expire 된다.)
		GCDisconnect gcDisconnect;
		gcDisconnect.setMessage(nsee.toString());

		pLoginPlayer->sendPacket(&gcDisconnect);

		// 이렇게 던지면 상위 IPM::processCommands()에서 disconnect 처리한다.
		throw InvalidProtocolException("fuck");
	} 
	catch (InvalidProtocolException & ipe) 
	{
		cout << endl
			 << "+-----------------------+" << endl
			 << "| Level 2 Access Denied |" << endl
			 << "+-----------------------+" << endl
			 << endl;

		GCDisconnect gcDisconnect;
		gcDisconnect.setMessage(ipe.toString());

		pLoginPlayer->sendPacket(&gcDisconnect);

		// 이렇게 던지면 상위 IPM::processCommands()에서 disconnect 처리한다.
		throw;
	}

    ServerGroupID_t CurrentServerGroupID = 0;

    Statement  * pGStmt     = NULL;
    Result     * pGResult   = NULL;

	// 빌링~ by sigi. 2002.5.31
	PayType         payType;
	string          payPlayDate;
	uint            payPlayHours;
	uint            payPlayFlag;


    try {

		pGStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pGResult = pGStmt->executeQuery("SELECT CurrentWorldID, CurrentServerGroupID, LogOn, Access, PayType, PayPlayDate, PayPlayHours, PayPlayFlag FROM Player WHERE PlayerID = '%s'", PlayerID.c_str());

		// 로그인 여부를 체크한다.
		pGResult->next();

		WorldID_t CurrentWorldID = pGResult->getInt(1);

		CurrentServerGroupID = pGResult->getInt(2);

		pLoginPlayer->setWorldID(CurrentWorldID);
		pLoginPlayer->setServerGroupID(CurrentServerGroupID);

		string logon = pGResult->getString(3);

		payType              = (PayType)(pGResult->getInt(5));
		payPlayDate          = pGResult->getString(6);
		payPlayHours         = pGResult->getInt(7);
		payPlayFlag          = pGResult->getInt(8);


		if (logon == "GAME" || logon == "LOGON") {
			string msg = "ReconnectLogin verify failed: LogOn = ";
			msg += logon;
			pLoginPlayer->setID("NONE");
			throw SQLQueryException(msg);
		}

		if (logon == "LOGOFF")// || logon == "GAME") // by sigi. 2002.5.15
		{
			Statement* pStmt = NULL;
			try 
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

				/// LogOn이 'LOGOFF'인 경우만 LOGON으로 설정한다. by sigi. 2002.5.15
				pStmt->executeQuery("UPDATE Player SET LogOn='LOGON', CurrentLoginServerID=%d WHERE PlayerID='%s' AND LogOn='LOGOFF'", g_pConfig->getPropertyInt("LoginServerID"), PlayerID.c_str());

				// 이미 'LOGON'이었던 경우
				// PlayerID가 없는 경우..
				if (pStmt->getAffectedRowCount()==0)
				{
					cout << endl
						 << "+-----------------------+" << endl
						 << "|    Deny Multi Login   |" << endl
						 << "+-----------------------+" << endl
						 << endl;

					throw SQLQueryException("Deny MultiLogin");
				}

				SAFE_DELETE(pStmt);
			} 
			catch (SQLQueryException & sqe)
			{
				SAFE_DELETE(pStmt);
				throw;
			}
		}

		string access = pGResult->getString(4);

//		if (access == "DENY" || access == "WAIT") {
		if (access != "ALLOW") {
			throw SQLQueryException("ReconnectLogin verify failed ");
		}

#if defined(__THAILAND_SERVER__)
		if (strPermission != "ALLOW" && onChildGuardTimeArea(g_pConfig->getPropertyInt("CHILDGUARD_START_TIME"),g_pConfig->getPropertyInt("CHILDGUARD_END_TIME"), g_pConfig->getProperty("CHILDGUARD")) ) 
		{
			throw SQLQueryException("Player Permission is DENY (child guard) running. ");
		}
#endif
		
#ifdef __PAY_SYSTEM_LOGIN__
		string connectIP = pLoginPlayer->getSocket()->getHost();
		// 빌링 by sigi. 2002.5.31
		if (!pLoginPlayer->loginPayPlay(payType,
	                                    payPlayDate, payPlayHours, payPlayFlag,
	                                    connectIP, PlayerID))
		{
			SAFE_DELETE(pGStmt);
			throw InvalidProtocolException("Pay First!");
		}
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)
		string connectIP = pLoginPlayer->getSocket()->getHost();
		// 빌링 by sigi. 2002.5.31
		if (pLoginPlayer->loginPayPlay(payType,
	                                    payPlayDate, payPlayHours, payPlayFlag,
	                                    connectIP, PlayerID))
		{
			// Reconnect했는데 PayPlay가 가능하다는 것은..
			// BillingPlay가 아니고 PayPlay로 게임을 했다는 의미이다.
			// by sigi. 2002.11.22
			// 로그인 서버에서 billing 연결 부분 빼기로 했다.
            // 애드빌 요청 사항. by bezz 2003.04.22
		//#ifdef __CONNECT_BILLING_SYSTEM__
			//pLoginPlayer->setBillingLoginVerified();
			//pLoginPlayer->setBillingUserStatus("XX");
		//#endif
		}
		else
		{
			//// BillingPlay로 게임을 했었다는 의미이다.
			// by sigi. 2002.11.22
			// 로그인 서버에서 billing 연결 부분 빼기로 했다.
            // 애드빌 요청 사항. by bezz 2003.04.22
		//#ifdef __CONNECT_BILLING_SYSTEM__
			//pLoginPlayer->setBillingLoginVerified();
			//pLoginPlayer->setBillingUserStatus("HO");
		//#endif
		}
#else //elif defined(__PAY_SYSTEM_ZONE__)
        pLoginPlayer->setPayPlayValue(payType, payPlayDate, payPlayHours, payPlayFlag);
#endif


		SAFE_DELETE(pGStmt);
	} 
	catch (SQLQueryException & sce) 
	{
		//cout << sce.toString() << endl;
		// 쿼리 결과 및 쿼리문 객체를 삭제한다.
		SAFE_DELETE(pGStmt);
		throw DisconnectException(sce.toString());
	}

	//cout << "CLReconnectLogin : ReconnectLoginInfo verified" << endl;

	pLoginPlayer->setServerGroupID(CurrentServerGroupID);

	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);


	//----------------------------------------------------------------------
	// 이제 LCPCList 패킷을 만들어서 전송하자
	//----------------------------------------------------------------------
	LCPCList lcPCList;

	pLoginPlayer->makePCList( lcPCList );
	pLoginPlayer->sendPacket(&lcPCList);
	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);

#ifdef __CONNECT_CBILLING_SYSTEM__
	pLoginPlayer->setCBillingVerified();
	pLoginPlayer->setPayPlayer();
#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}
#if defined(__THAILAND_SERVER__) 
bool CLReconnectLoginHandler::onChildGuardTimeArea(int pm, int am, string enable)
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

