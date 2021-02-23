//////////////////////////////////////////////////////////////////////////////
// Filename    : CommonBillingPacketHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CommonBillingPacket.h"
#include "BillingPlayer.h"

#ifdef __GAME_SERVER__
	#include "PlayerCreature.h"
	#include "GamePlayer.h"
	#include "PCFinder.h"
	#include "EventKick.h"
	#include "EventSystemMessage.h"
	#include "VSDateTime.h"
	#include "StringPool.h"
	#include "ResurrectLocationManager.h"
	#include "ZoneUtil.h"
	#include "BillingResultLoginErrorMessage.h"
#elif defined(__LOGIN_SERVER__)
	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
#endif

#include "Gpackets/GCSystemMessage.h"

// packetUtil.h에 추가해야 한다.
extern void sendSystemMessage(GamePlayer* pGamePlayer, const string& msg) throw (Error);

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CommonBillingPacketHandler::execute (CommonBillingPacket* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
//#ifdef __GAME_SERVER__

	// 다 로그를 남기자
	filelog(LOGFILE_BILLING_PACKET, "%s", pPacket->toString().c_str());

	int code = pPacket->Packet_Type;

	switch (code)
	{
		// 게임에 들어올때 보낸 packet에 대한 인증 정보
		case BILLING_PACKET_LOGIN :
			executeBillingLoginVerify(pPacket, pPlayer);
		break;

		// 남은 시간을 보여준다.	(B->G only)
		case BILLING_PACKET_REMAIN :
			executeBillingRemain(pPacket, pPlayer);
		break;

		// 접속 중 체크. BillingServer로 접속 정보를 보내준다.
		case BILLING_PACKET_CHECK :
			executeBillingCheck(pPacket, pPlayer);
		break;

		// 유료 사용 가능한지만 체크한다. 
		case BILLING_PACKET_LOGIN_CHECK :
			executeBillingLoginCheckVerify(pPacket, pPlayer);
		break;


		default :
			break;
	}


//#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 게임에 들어올때 보낸 packet에 대한 인증 정보
//////////////////////////////////////////////////////////////////////////////
void CommonBillingPacketHandler::executeBillingLoginVerify(CommonBillingPacket* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	int result = pPacket->Result;

	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	Creature* pCreature = g_pPCFinder->getCreatureByID_LOCKED(pPacket->User_ID);

	if (pCreature!=NULL)
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());

		// 검증 되었다고 체크한다.
		pGamePlayer->setBillingLoginVerified();

		if (result==BILLING_RESULT_LOGIN_OK)
		{
			char userStatus[10];
			memcpy( userStatus, pPacket->User_Status, 2 ); userStatus[2] = '\0';

			if ( strcmp( userStatus, "PM" ) != 0 )
			{
				char billMethod[10], expireDate[20];
				memcpy(billMethod, pPacket->Bill_Method, 2); billMethod[2]='\0';
				memcpy(expireDate, pPacket->Expire_Date, 12); expireDate[12]='\0';

				filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: PayPlay (%s, %s, %s, %d)", pPacket->User_ID,
																				billMethod,
																				expireDate,
																				pPacket->Remain_Time);
#ifdef __COUT_BILLING_SYSTEM__
				cout << "LoginVerify: PayPlay ( " 
						<<  pPacket->User_ID << ", "
						<< billMethod << ", " 
						<< expireDate << ", " 
						<< pPacket->Remain_Time << " )" << endl;
#endif
			}
			else
			{
				// PC 방 사용자
				filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: PayPlay (%s, PCRoom)", pPacket->User_ID);
#ifdef __COUT_BILLING_SYSTEM__
				cout << "LoginVerify: PayPlay ( " 
						<<  pPacket->User_ID << ", PCRoom )" << endl;
#endif
			}

			// 유료 접속 가능
			pGamePlayer->setBillingUserStatus( pPacket->User_Status );
			pGamePlayer->setPremiumPlay();

			// 유료 사용자이면.. 무료플레이가 필요없다.
			#ifdef __PAY_SYSTEM_FREE_LIMIT__
			if (pGamePlayer->isPayPlaying())
			{
				bool bClear = true;	// Pay정보 제거한다.
				pGamePlayer->logoutPayPlay(pGamePlayer->getID(), bClear);
			}
			#endif

			// 접속 후, 남은 시간을 보내준다.
			sendBillingRemainMessage(pPacket, pGamePlayer);
		}
		else if ( result==BILLING_RESULT_LOGIN_NO_ACCOUNT )
		{
			// 무료 사용자.
			// 일단 걍 둔다.
			// 무료 사용자도 게임할 수 있다.
			// by bezz 2003.04.22

			filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: No Account(%s)", pPacket->User_ID );

			#ifdef __COUT_BILLING_SYSTEM__
			cout << "LoginVerify: No Account(" << pPacket->User_ID << ")" << endl;
			#endif

			// 유료 사용 불가
			// 일단은 찝찝하지만.. 걍 짜른다.
			//pGamePlayer->setPenaltyFlag( PENALTY_TYPE_KICKED );

			//#ifdef __PAY_SYSTEM_FREE_LIMIT__
			/*	if (pGamePlayer->isPayPlaying())
				{
					Creature* pCreature = pGamePlayer->getCreature();
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

					if (pPC->isPayPlayAvaiable())
					{
						// 아직 무료 기간이 남아있는 경우.
						filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: FreePlay (%s)", pPacket->User_ID);
						#ifdef __COUT_BILLING_SYSTEM__
							cout << "LoginVerify: FreePlay (" <<  pPacket->User_ID << ")" << endl;
						#endif
					}
					else
					{
						// 능력치 over된 경우
						filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: Disconnect by ATTR (%s)", pPacket->User_ID);
					
						#ifdef __COUT_BILLING_SYSTEM__
							cout << "LoginVerify: Disconnect by ATTR (" << pPacket->User_ID << ")" << endl;
						#endif

						disconnectGamePlayer( pGamePlayer, 5*10 ); // 5초 후 짜른다.
					}
				}
				else
			//#endif
				{
					filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: Disconnect (%s)", pPacket->User_ID);

					#ifdef __COUT_BILLING_SYSTEM__
						cout << "LoginVerify: Disconnect (" << pPacket->User_ID << ")" << endl;
					#endif

					disconnectGamePlayer( pGamePlayer, 5*10 ); // 5초 후 짜른다.
				}
			*/
		}
		else
		{
			BillingResultLoginErrorMessage* pMessage = BillingResultLoginErrorMessage::Instance();
			sendSystemMessage(pGamePlayer, pMessage->getMessage(result));

			filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: Disconnect (%s)", pPacket->User_ID);

			#ifdef __COUT_BILLING_SYSTEM__
				cout << "LoginVerify: Disconnect (" << pPacket->User_ID << ")" << endl;
			#endif

			disconnectGamePlayer( pGamePlayer, 10*10 ); // 10 초 후 짜른다.
		}
	}
	else
	{
		filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: No Such Player(%s)", pPacket->User_ID);

		#ifdef __COUT_BILLING_SYSTEM__
			cout << "LoginVerify: No Such Player(" << pPacket->User_ID << ")" << endl;
		#endif
	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

#else
	filelog(LOGFILE_BILLING_PLAYER, "[Error] BillingLoginVerify: Wrong Packet(%s)", pPacket->User_ID);
#endif

	__END_DEBUG_EX __END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// 로그인 서버에서 유료 사용이 가능한지 체크만 하는 경우
//////////////////////////////////////////////////////////////////////////////
void CommonBillingPacketHandler::executeBillingLoginCheckVerify(CommonBillingPacket* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __LOGIN_SERVER__

	int result = pPacket->Result;

	__ENTER_CRITICAL_SECTION((*g_pLoginPlayerManager))

	LoginPlayer* pLoginPlayer = g_pLoginPlayerManager->getPlayer_NOLOCKED(pPacket->User_ID);

	if (pLoginPlayer!=NULL)
	{
		// 검증 되었다고 체크한다.
		pLoginPlayer->setBillingLoginVerified();

		if (result==BILLING_RESULT_LOGIN_OK)
		{
			char billMethod[10], expireDate[20];
			memcpy(billMethod, pPacket->Bill_Method, 2); billMethod[2]='\0';
			memcpy(expireDate, pPacket->Expire_Date, 12); expireDate[12]='\0';

			filelog(LOGFILE_BILLING_PLAYER, "LoginVerify: PayPlayCheck (%s, %s, %s, %d)", pPacket->User_ID,
																			billMethod,
																			expireDate,
																			pPacket->Remain_Time);
#ifdef __COUT_BILLING_SYSTEM__
			cout << "LoginVerify: PayPlayCheck ( " 
					<<  pPacket->User_ID << ", "
					<< billMethod << ", " 
					<< expireDate << ", " 
					<< pPacket->Remain_Time << " )" << endl;
#endif

			// 유료 접속 가능
			pLoginPlayer->setBillingUserStatus( pPacket->User_Status );

			// 애드빌에서 UserStatus를 안 넣어준 바람에 임시로 사용했던 코드. by sigi. 2002.12.5
			//if (pLoginPlayer->getBillingUserStatus().empty())
			//{
			//	pLoginPlayer->setBillingUserStatus( "HO" );
			//}

			// login서버에서는 이게 의미가 없겠지.
			// pLoginPlayer->setPremiumPlay();

			// 유료 사용자이면.. 무료플레이가 필요없다.
			#ifdef __PAY_SYSTEM_FREE_LIMIT__
			if (pLoginPlayer->isPayPlaying())
			{
				bool bClear = true;	// Pay정보 제거한다.
				pLoginPlayer->logoutPayPlay(pLoginPlayer->getID(), bClear);
			}
			#endif
		}
		else
		{
			if (pLoginPlayer->isPayPlaying())
			{
				// 머 어쨋든.. 게임 가능한 애다.
				// 캐릭터 능력치별로 짜르는거는 CLSelectPCHandler.cpp에서 한다.
				pLoginPlayer->setBillingUserStatus( "XX" );

				filelog(LOGFILE_BILLING_PLAYER, "LoginCheckVerify: Can FreePlay (%s)", pPacket->User_ID);

				#ifdef __COUT_BILLING_SYSTEM__
					cout << "LoginCheckVerify: Can FreePlay (" << pPacket->User_ID << ")" << endl;
				#endif

			}
			else
			{
				// 짤라야될 애당.
				cout << pPacket->User_ID << " cannot play by billing" << endl;

				filelog(LOGFILE_BILLING_PLAYER, "LoginCheckVerify: Cannot BillingPlay (%s)", pPacket->User_ID);

				#ifdef __COUT_BILLING_SYSTEM__
					cout << "LoginCheckVerify: Cannot BillingPlay (" << pPacket->User_ID << ")" << endl;
				#endif
			}
		}
	}
	else
	{
		filelog(LOGFILE_BILLING_PLAYER, "LoginCheckVerify: No Such Player(%s)", pPacket->User_ID);

		#ifdef __COUT_BILLING_SYSTEM__
			cout << "LoginCheckVerify: No Such Player(" << pPacket->User_ID << ")" << endl;
		#endif
	}

	__LEAVE_CRITICAL_SECTION((*g_pLoginPlayerManager))

#else
	filelog(LOGFILE_BILLING_PLAYER, "[Error] BillingLoginCheckVerify: Wrong Packet(%s)", pPacket->User_ID);
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 남은 시간을 보여준다.	(B->G only)
//////////////////////////////////////////////////////////////////////////////
void CommonBillingPacketHandler::executeBillingRemain(CommonBillingPacket* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	Creature* pCreature = g_pPCFinder->getCreatureByID_LOCKED(pPacket->User_ID);

	if (pCreature!=NULL)
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());

		int result = pPacket->Result;

		switch (result)
		{
			//-----------------------------------------------------------------
			// 접속을 종료 시키는 경우
			//-----------------------------------------------------------------
			case BILLING_RESULT_REMAIN_DISCONNECT :	// 강제 종료
			case BILLING_RESULT_REMAIN_DUPLICATE :	// 중복 접속
			case BILLING_RESULT_REMAIN_REFUND :		// 환불

				// 유료 사용 불가
				// 일단은 찝찝하지만.. 걍 짜른다.
				//pGamePlayer->setPenaltyFlag( PENALTY_TYPE_KICKED );
				// 5 초 후 짜른다.
				char session[40];
				memcpy(session, pPacket->Session, 32); session[32]='\0';
				if (pGamePlayer->getBillingSession()==session)
				{
					#ifdef __COUT_BILLING_SYSTEM__
						cout << "***** Disconnect (" << pPacket->User_ID << ":" << session << ")" << endl;
					#endif
					disconnectGamePlayer( pGamePlayer, 5*10 );
					filelog(LOGFILE_BILLING_PLAYER, "BillingRemain: Disconnect(%s:%s), Result=%d", pPacket->User_ID, session, result);
				}
				else
				{
					#ifdef __COUT_BILLING_SYSTEM__
						cout << "*****  No Such Session(" << pPacket->User_ID << ":" << session << ")" << endl;
					#endif

					filelog(LOGFILE_BILLING_PLAYER, "BillingRemain: Disconnect: No Such Session(%s:%s)", pPacket->User_ID, session);
				}
			break;

			//-----------------------------------------------------------------
			// 유료 사용 시간이 다 되었다. 무료 사용으로 전환
			//-----------------------------------------------------------------
			case BILLING_RESULT_REMAIN_NONE :
			{
				//char message[40];
				//sprintf( message, "유료 사용시간이 다 되었습니다." )
				//sendSystemMessage(pGamePlayer, message);

				// ZonePlayerManager 에서 유료존에 있을 경우 짤리게 된다.
				pGamePlayer->setBillingUserStatus( "" );
			}
			break;

			//-----------------------------------------------------------------
			// 결제 정보를 보여주는 경우
			//-----------------------------------------------------------------
			case BILLING_RESULT_REMAIN_RESERVE :	// 새로운 결제정보 사용 시작
			{
				char billMethod[10];
				//char expireDate[20];
				memcpy(billMethod, pPacket->Bill_Method, 2); billMethod[2]='\0';
				//memcpy(expireDate, pPacket->Expire_Date, 12); expireDate[12]='\0';

				filelog(LOGFILE_BILLING_PLAYER, "BillingRemain: (%s, %dm)", pPacket->User_ID, (pPacket->Remain_Time/60));

				// 결제 정보를 다시 보여주는 경우
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_APPLY_NEW_BILLING_INFO ));
				pGamePlayer->sendPacket( &gcSystemMessage );

				// 접속 후, 남은 시간을 보내준다.
				sendBillingRemainMessage(pPacket, pGamePlayer);

			}
			break;

			//-----------------------------------------------------------------
			// 정상적으로 남은 시간
			//-----------------------------------------------------------------
			case BILLING_RESULT_REMAIN_TIME :		
			{
				char billMethod[10];
				//char expireDate[20];
				memcpy(billMethod, pPacket->Bill_Method, 2); billMethod[2]='\0';
				//memcpy(expireDate, pPacket->Expire_Date, 12); expireDate[12]='\0';

				filelog(LOGFILE_BILLING_PLAYER, "BillingRemain: (%s, %dm)", pPacket->User_ID, (pPacket->Remain_Time/60));

				int sec = pPacket->Remain_Time;
				int hour = sec/3600;
				int min = (sec-(hour*3600))/60;

				StringStream msg;
				msg << "유료 서비스 사용 가능 시간이 ";

				if (hour>0)
				{
					msg	<< hour << "시간 ";
				}
					
				msg << min << "분 남았습니다.";

				if (strcmp(billMethod, "FM")==0)		msg << "(월정액)";
				else if (strcmp(billMethod, "FD")==0)	msg << "(일정액)";
				else if (strcmp(billMethod, "TH")==0)	msg << "(정량)";

				#ifdef __COUT_BILLING_SYSTEM__
					cout << "[" << pPacket->User_ID << "] " 
							<< msg.toString().c_str() << endl;

							//<< billMethod << ", "
							//<< pPacket->getExpire_DateToString().c_str() << "까지, "
				#endif

				sendSystemMessage(pGamePlayer, msg.toString());
			}
			break;
		}
	}
	else
	{
		#ifdef __COUT_BILLING_SYSTEM__
			cout << "BillingRemain: No Such Player(" << pPacket->User_ID << ")" << endl;
		#endif
		filelog(LOGFILE_BILLING_PLAYER, "BillingRemain: No Such Player(%s)", pPacket->User_ID);
	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
#else
	filelog(LOGFILE_BILLING_PLAYER, "[Error] BillingRemain: Wrong Packet(%s)", pPacket->User_ID);
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 접속 중 체크. BillingServer로 접속 정보를 보내준다.
//////////////////////////////////////////////////////////////////////////////
void CommonBillingPacketHandler::executeBillingCheck(CommonBillingPacket* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	BillingPlayer* pBillingPlayer = dynamic_cast<BillingPlayer*>(pPlayer);
	Assert(pBillingPlayer!=NULL);

	// 다시 결과값을 보낸다.
	pBillingPlayer->sendPayCheck( pPacket );

#else
	filelog(LOGFILE_BILLING_PLAYER, "[Error] BillingCheck: Wrong Packet(%s)", pPacket->User_ID);
#endif

	__END_DEBUG_EX __END_CATCH
}

void CommonBillingPacketHandler::disconnectGamePlayer(GamePlayer* pGamePlayer, Turn_t delay)
	throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	if ( pGamePlayer->getEvent( Event::EVENT_CLASS_KICK ) != NULL )
		return;

	EventKick* pEventKick = new EventKick(pGamePlayer);

	pEventKick->setDeadline(delay);

	// 몇 초후에 짤린다..고 보내준다.
	pEventKick->sendMessage();

	pGamePlayer->addEvent(pEventKick);

#endif

	__END_CATCH
}

void CommonBillingPacketHandler::sendBillingRemainMessage(CommonBillingPacket* pPacket, GamePlayer* pGamePlayer)
	throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	char userStatus[10];
	memcpy( userStatus, pPacket->User_Status, 2 ); userStatus[2] = '\0';

	char billMethod[10];
	memcpy(billMethod, pPacket->Bill_Method, 2); billMethod[2]='\0';

	StringStream msg;
	msg << "유료 서비스 사용 가능 ";

	// PC 방 사용자일 경우
	if ( strcmp( userStatus, "PM" ) == 0 )
	{
		msg << "[PC방]";
	}
	// 남은 날 수를 출력하는 경우
	else if (strcmp(billMethod,"FM")==0 || strcmp(billMethod,"FD")==0)		// 남은 날 수
	{
		char expireDate[20];
		memcpy(expireDate, pPacket->Expire_Date, 12); expireDate[12]='\0';
		string sExpireDate( expireDate );

		VSDateTime vsdtExpireDate = VSDateTime::fromYYYYMMDDHHMMSS( sExpireDate );
		VSDateTime currentDateTime = VSDateTime::currentDateTime();
		int day = currentDateTime.daysTo( vsdtExpireDate );
		#ifdef __COUT_BILLING_SYSTEM__
			cout <<	"[" << pPacket->User_ID << "] ExpireDateTime : " << vsdtExpireDate.toString()
				 << " CurrentDateTime : " << currentDateTime.toString()
				 << " Remain Days : " << day << endl;
		#endif

		//int day = pPacket->Remain_Time;
		if ( day == 0 && currentDateTime.date() == vsdtExpireDate.date() )
		{
			msg << "기간은 오늘까지 입니다";
		}
		else
		{
			msg << "기간이 " << (day==0?1:day) << "일 남았습니다.";
		}

		// 겜방 이용자이다.
		// 메시지 출력안한다.
		if ( sExpireDate.size() < 7 )
		{
			filelog(LOGFILE_BILLING_PLAYER, "LoginRemain: (%s, Netmarble PCRoom)", pPacket->User_ID);
			return;
		}

		filelog(LOGFILE_BILLING_PLAYER, "LoginRemain: (%s, %d day)", pPacket->User_ID, day);
	}
	// 남은 시간을 출력하는 경우
	else if (strcmp(billMethod,"TH")==0)	// 남은 시간
	{
		// 남은 시간 무조건 한번 출력
		int sec = pPacket->Remain_Time;
		int hour = sec/3600;
		int min = (sec-(hour*3600))/60;

		msg << "시간이 ";
		
		if (hour>0)
		{
			msg << hour << "시간 ";
		}
		
		msg << min << "분 남았습니다.";
	
		filelog(LOGFILE_BILLING_PLAYER, "LoginRemain: (%s, %dh %dm)", pPacket->User_ID, hour, min);
	}

	#ifdef __COUT_BILLING_SYSTEM__
		cout <<	"[" << pPacket->User_ID << "] "
				<< msg.toString().c_str() << endl;
	#endif

	sendSystemMessage(pGamePlayer, msg.toString());

#endif

	__END_CATCH
}

