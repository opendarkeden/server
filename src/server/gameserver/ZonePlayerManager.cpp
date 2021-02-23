//
// Filename    : ZonePlayerManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "ZonePlayerManager.h"
#include "IncomingPlayerManager.h"
#include "Assert.h"
#include "SocketAPI.h"
#include "Socket.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "LogClient.h"
#include "Zone.h"
#include <algorithm>
#include "StringStream.h"
#include "Cpackets/CGLogout.h"
#include "Profile.h"
#include "ZoneInfoManager.h"
#include "PaySystem.h"
#include "ZoneUtil.h"
#include "ResurrectLocationManager.h"
#include "Thread.h"
#include "billing/BillingInfo.h"
//#include "UserGateway.h"
#include "StringPool.h"
#include "DB.h"
#include "ZoneGroup.h"
#include "VariableManager.h"
#include "Party.h"
#include "DefaultOptionSetInfo.h"
#include "BroadcastFilter.h"

#include "chinabilling/CBillingInfo.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCKickMessage.h"

#ifdef __THAILAND_SERVER__
	
	#include "Properties.h"
	#include "TimeChecker.h"

#endif

//#define __FULL_PROFILE__

#ifndef __FULL_PROFILE__
#undef beginProfileEx
#define beginProfileEx(name) ((void)0)
#undef endProfileEx
#define endProfileEx(name) ((void)0)
#endif

bool checkZonePlayerManager( GamePlayer* pGamePlayer, ZonePlayerManager* pZPM, const string& str );

//////////////////////////////////////////////////////////////////////////////
// constructor
// 하위 매니저 객체를 생성한다.
//////////////////////////////////////////////////////////////////////////////
ZonePlayerManager::ZonePlayerManager () 
	throw ()
: m_MinFD(-1), m_MaxFD(-1)
{
	__BEGIN_TRY

	m_Mutex.setName("ZonePlayerManager");
	m_MutexBroadcast.setName("ZonePlayerManagerBroadcast");
	m_PlayerListQueue.clear();
	m_BroadcastQueue.clear();

	// fd_set 들을 0 으로 초기화한다.
	FD_ZERO(&m_ReadFDs[0]);
	FD_ZERO(&m_WriteFDs[0]);
	FD_ZERO(&m_ExceptFDs[0]);

	// m_Timeout 을 초기화한다.
	// 나중에는 이 주기 역시 옵션으로 처리하도록 하자.
	m_Timeout[0].tv_sec = 0;
	m_Timeout[0].tv_usec = 0;
/*
#if defined(__THAILAND_SERVER__)

	// add by inthesky for THAILAND ChildGuard rule
	string strChildGuardSwitch = g_pConfig->getProperty("CHILDGUARD");

	cout << "ChildGuard Policy : " << strChildGuardSwitch << endl;

	if(strChildGuardSwitch == "Enable" || strChildGuardSwitch == "ENABLE" || strChildGuardSwitch == "enable")
	{
		m_bChildGuard   = true;
	}
	else m_bChildGuard      = false;

	m_nChildGuardStartTime  = g_pConfig->getPropertyInt("CHILDGUARD_START_TIME");
	m_nChildGuardEndTime    = g_pConfig->getPropertyInt("CHILDGUARD_END_TIME");
	m_nChildGuardKickTime   = g_pConfig->getPropertyInt("CHILDGUARD_REMAIN_TIME");

	m_nChildGuardCheckTerm  = g_pConfig->getPropertyInt("CHILDGUARD_CHECKTERM");
	getCurrentTime(m_tmChildGuardCheckTerm);
	m_tmChildGuardCheckTerm.tv_sec += m_nChildGuardCheckTerm;

	cout << "ChildGuard TimeArea : "<<(int)m_nChildGuardStartTime << " - " << (int)m_nChildGuardEndTime << endl;
	cout << "ChildGuard CheckTerm : "<<(int)m_nChildGuardCheckTerm << "/sec" << endl;

#endif
*/
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
ZonePlayerManager::~ZonePlayerManager () 
	throw ()
{
	__BEGIN_TRY

	// 플레이어 삭제는 PlayerManager 레벨에서 이루어지므로 신경쓰지 않아도 된다.

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::broadcastPacket (Packet* pPacket)
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	PlayerManager::broadcastPacket(pPacket);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::broadcastPacket_NOBLOCKED (Packet* pPacket)
	throw (Error)
{
	__BEGIN_TRY

	PlayerManager::broadcastPacket(pPacket);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::pushBroadcastPacket( Packet* pPacket, BroadcastFilter* pFilter )
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexBroadcast)

	// 여기에 쓰는 패킷이 Encrypter 를 쓰지 않는 다는 전제하에 해놓은 코딩이다.
	// 만일 Encrypter 를 쓰는 패킷을 사용하려면 BroadcastQueue 를 Zone 에 두고
	// 그것을 사용해야한다.

	// 필터와 패킷을 큐에 넣는다.
	// 필터는 새로 생성한 객체(클론)를 넣는다.
	// 패킷을 스트림에 써서 큐에 넣는다.
	SocketOutputStream* pStream = new SocketOutputStream( NULL, szPacketHeader + pPacket->getPacketSize() );
	pPacket->writeHeaderNBody( *pStream );

	m_BroadcastQueue.push_back( PairFilterStream( pFilter->Clone(), pStream ) );

	__LEAVE_CRITICAL_SECTION(m_MutexBroadcast)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::flushBroadcastPacket()
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexBroadcast)

	list<PairFilterStream>::iterator itr = m_BroadcastQueue.begin();
	list<PairFilterStream>::iterator endItr = m_BroadcastQueue.end();

	for ( ; itr != endItr; ++itr )
	{
		BroadcastFilter*	pFilter	= itr->first;
		SocketOutputStream*	pStream	= itr->second;

		if ( pStream == NULL )
		{
			filelog("ZoneBug.txt", "%s : %s", "Zone::flushBroadcastPacket", "pStream이 NULL입니다.");
			continue;
		}

		for ( uint i=0; i<nMaxPlayers; ++i )
		{
			if ( m_pPlayers[i] != NULL )
			{
				GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
				if ( pFilter == NULL || pFilter->isSatisfy(pGamePlayer) )
				{
					try
					{
						pGamePlayer->sendStream( pStream );
					}
					catch ( Throwable& t )
					{
						filelog("ZonePlayerManager.log", "broadcastPacket: %s", t.toString().c_str() );
					}
				}
			}
		}
	}

/*	for ( ; itr != endItr; ++itr )
	{
		Packet* pPacket = *itr;

		if ( pPacket == NULL )
		{
			filelog("ZoneBug.txt", "%s : %s", "Zone::flushBroadcastPacket", "pPacket가 NULL입니다.");
			continue;
		}

		bool bSend = false;

		// Ranger Say 인 경우
		if ( pPacket->getPacketID() == Packet::PACKET_GC_SYSTEM_MESSAGE )
		{
			GCSystemMessage* pSystemMessage = dynamic_cast<GCSystemMessage*>(pPacket);
			Assert( pSystemMessage != NULL );

			if ( pSystemMessage->getType() == SYSTEM_MESSAGE_RANGER_SAY )
			{
				bSend = true;

				Race_t race = pSystemMessage->getRace();

				for ( uint i=0; i<nMaxPlayers; ++i )
				{
					if ( m_pPlayers[i] != NULL )
					{
						GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);

						if ( pGamePlayer->getCreature()->getRace() == race )
						{
							try
							{
								m_pPlayers[i]->sendPacket( pPacket );
							}
							catch ( Throwable& t )
							{
								filelog("ZonePlayerManager.log", "broadcastPacket: %s", t.toString().c_str() );
							}
						}
					}
				}
			}
		}

		if ( !bSend )
		{
			for ( uint i=0; i<nMaxPlayers; ++i )
			{
				if ( m_pPlayers[i] != NULL )
				{
					try
					{
						m_pPlayers[i]->sendPacket( pPacket );
					}
					catch ( Throwable& t )
					{
						filelog("ZonePlayerManager.log", "broadcastPacket: %s", t.toString().c_str() );
					}
				}
			}
		}

		// 이때 패킷을 동적으로 할당되어 있다.
		// 그러므로 메모리에서 삭제해야한다.
		SAFE_DELETE( pPacket );
	}
*/
	m_BroadcastQueue.clear();

	__LEAVE_CRITICAL_SECTION(m_MutexBroadcast)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::copyPlayers()
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	PlayerManager::copyPlayers();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// call select() system call
// 상위에서 TimeoutException 을 받으면 플레이어는 처리하지 않아도 된다.
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::select ()
	throw (TimeoutException , InterruptedException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// m_Timeout[0] 을 m_Timeout[1] 으로 복사한다.
	m_Timeout[1].tv_sec  = m_Timeout[0].tv_sec;
	m_Timeout[1].tv_usec = m_Timeout[0].tv_usec;

	// m_XXXFDs[0] 을 m_XXXFDs[1] 으로 복사한다.
	m_ReadFDs[1]   = m_ReadFDs[0];
	m_WriteFDs[1]  = m_WriteFDs[0];
	m_ExceptFDs[1] = m_ExceptFDs[0];

	__LEAVE_CRITICAL_SECTION(m_Mutex)

    try 
	{
		// 이제 m_XXXFDs[1] 을 가지고 select() 를 호출한다.
		SocketAPI::select_ex(m_MaxFD + 1 , &m_ReadFDs[1] , &m_WriteFDs[1] , &m_ExceptFDs[1] , &m_Timeout[1]);
    } 
	// 주석처리 by sigi. 2002.5.14
	//catch (TimeoutException&) 
	//{
		// do nothing
    //} 
	catch (InterruptedException & ie) 
	{
	    // 시그널이 올 리가 엄찌~~
		log(LOG_GAMESERVER_ERROR, "", "", ie.toString());
    }

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// process all players' inputs
//
// 서버 소켓의 read flag가 켜졌을 경우, 새로운 접속이 들어왔으므로
// 이를 처리하고, 다른 소켓의 read flag가 켜졌을 경우, 새로운 패킷이
// 들어왔으므로 그 플레이어의 processInput()을 호출하면 된다.
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::processInputs () 
	throw (IOException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{ 
		//m_Mutex.unlock();
		return;
	}

	//copyPlayers();

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		// ZPM에는 플레이어만 들어있으므로, 더 비교할 꺼리가 없다.
		if (FD_ISSET(i , &m_ReadFDs[1])) 
		{
			if (m_pPlayers[i] != NULL && m_pPlayers[i] == m_pPlayers[i]) 
			{
				GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
				Assert (pTempPlayer != NULL);
				Assert (m_pPlayers[i] != NULL);

				if ( g_pVariableManager->getVariable( PCROOM_ITEM_RATIO_BONUS ) == 100 && !checkZonePlayerManager( pTempPlayer, this, "PI" ) )
				{
					try
					{
						CGLogoutHandler::execute( NULL, pTempPlayer );
					}
					catch ( DisconnectException& de )
					{
						deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
						pushOutPlayer( pTempPlayer );
					}
				}
				else if (pTempPlayer->getSocket()->getSockError()) 
				{
					pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
					pTempPlayer->setItemRatioBonusPoint(7);
					
					try
					{
						CGLogoutHandler::execute( NULL, pTempPlayer );
					}
					catch ( DisconnectException& de )
					{
						filelog( "DIFF_ZG.log", "%s ZPM+PI+SOCKERR", de.toString().c_str() );
						deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
						pushOutPlayer( pTempPlayer );
					}

					// by sigi. 2002.12.30
//					UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_INPUT_ERROR );

					/*
					try 
					{
						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
						pTempPlayer->disconnect(DISCONNECTED);
					} 
					catch (Throwable & t) 
					{
						filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processInput(1)", t.toString().c_str());
					} 

					deletePlayer(i);
					deleteQueuePlayer(pTempPlayer);

					// 플레이어 객체를 삭제한다.
					delete pTempPlayer;
					*/
				} 
				else 
				{
					try 
					{
						pTempPlayer->processInput();
					} 
					catch (ConnectException & ce) 
					{
						pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
						pTempPlayer->setItemRatioBonusPoint(8);
						
						try
						{
							CGLogoutHandler::execute( NULL, pTempPlayer );
						}
						catch ( DisconnectException& de )
						{
							filelog( "DIFF_ZG.log", "%s ZPM+PI+CE", de.toString().c_str() );
							deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
							pushOutPlayer( pTempPlayer );
						}

						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_INPUT_DISCONNECT );

						/*
						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pTempPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processInput(4)", t.toString().c_str());
						} 

						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						// 플레이어 객체를 삭제한다.
						delete pTempPlayer;
						*/
					}
					catch (IOException & ioe)
					{
						pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
						pTempPlayer->setItemRatioBonusPoint(9);

						try
						{
							CGLogoutHandler::execute( NULL, pTempPlayer );
						}
						catch ( DisconnectException& de )
						{
							filelog( "DIFF_ZG.log", "%s ZPM+PI+IOE", de.toString().c_str() );
							deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
							pushOutPlayer( pTempPlayer );
						}

						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_INPUT_DISCONNECT2 );

						/*
						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pTempPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
						} 

						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						delete pTempPlayer;
						*/
					}
				}
			}
		}
	}

//	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// process all players' commands
//////////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::processCommands() 
	throw (IOException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// test code
	/*
	for (int i=0; i<100; i++)
	{
		PaySystem ps;

		try {
			ps.loginPayPlay("111.111.222.333", "sdfdf");
			cout << "[" << (int)Thread::self() << "] " << i << endl;
		} catch (Throwable&t)
		{
			cout << t.toString().c_str() << endl;
		}
	}
	*/

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{	
		//m_Mutex.unlock();
		return;
	}

	//copyPlayers();

	VSDateTime currentDateTime( VSDate::currentDate(), VSTime::currentTime() );

	Timeval currentTime;
	getCurrentTime(currentTime);

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (m_pPlayers[i] != NULL) 
		{
			GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
			Assert (pTempPlayer);
			Assert (m_pPlayers[i] != NULL);

			if (pTempPlayer->getSocket()->getSockError()) 
			{
				pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
				pTempPlayer->setItemRatioBonusPoint(10);

				try
				{
					CGLogoutHandler::execute( NULL, pTempPlayer );
				}
				catch ( DisconnectException& de )
				{
					filelog( "DIFF_ZG.log", "%s ZPM+PC+SOCKERR", de.toString().c_str() );
					deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
					pushOutPlayer( pTempPlayer );
				}

				// by sigi. 2002.12.30
//				UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_COMMAND_ERROR );

				/*
				try 
				{
					// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
					pTempPlayer->disconnect(DISCONNECTED);
				} 
				catch (Throwable & t) 
				{
					filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processCommands(1)", t.toString().c_str());
				}

				deletePlayer(i);
				deleteQueuePlayer(pTempPlayer);

				// 플레이어 객체를 삭제한다.
				delete pTempPlayer;
				*/
			} 
			else 
			{
				bool IsPayPlayEnd = false;

				try 
				{
					beginProfileEx("ZPM_PACKET");
					pTempPlayer->processCommand();
					endProfileEx("ZPM_PACKET");

					if ( g_pVariableManager->getVariable( PCROOM_ITEM_RATIO_BONUS ) == 100 && !checkZonePlayerManager( pTempPlayer, this, "PC" ) )
					{
						try
						{
							CGLogoutHandler::execute( NULL, pTempPlayer );
						}
						catch ( DisconnectException& de )
						{
							deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
							pushOutPlayer( pTempPlayer );
						}
					}

					// 정상적인 게임 상태에서(GPS_NORMAL)만 Pay체크를 한다.
					// PCManager::killCreature()에서는 GPS_IGNORE_ALL로 바뀌고
					// tile에서 지우고.. zone이동이 되므로.. 이걸로 문제가 생길 수 있다고 본다.
					// by sigi. 2002.12.10
					else if (pTempPlayer->getPlayerStatus()==GPS_NORMAL)
					{

#ifdef __CONNECT_BILLING_SYSTEM__
						// 아직 빌링 시스템에서 검증되지 않았다면..
						if (!pTempPlayer->isBillingLoginVerified())
						{
							if ( !pTempPlayer->isMetroFreePlayer() )
								pTempPlayer->sendBillingLogin();
						}
						// 빌링 시스템 검증이 된 경우이고..
						// 빌링 플레이가 불가능한 경우라면..
						// 제한적인 무료 플레이가 가능한지 체크해본다.	// by sigi. 2002.12.5
						else if (pTempPlayer->isBillingLoginVerified() 
								&& !pTempPlayer->isBillingPlayAvaiable())
#endif

						// 패밀리 요금제 적용이 끝난 경우. 유료존에 있는 무료 파티원들을 무료존으로 옮겨야한다.
						if ( pTempPlayer->isFamilyFreePassEnd() )
						{
							Creature* pCreature = pTempPlayer->getCreature();
							Zone* pZone = pCreature->getZone();
							Assert(pZone!=NULL);

							if ( pZone->isPayPlay() )
							{
								// 무료 사용자일 경우 아래 if 문에서 유료 체크를 하고 무료존으로 옮겨간다.
								pTempPlayer->setPremiumPlay();
							}
						}

						// 유료 사용자인 경우는 시간을 줄인다.
						// 패밀리 요금 사용자인 경우 시간이 다되었는지 확인한다. 유무료존에 상관없이
						if ((pTempPlayer->isPayPlaying() || pTempPlayer->isPremiumPlay() || pTempPlayer->isFamilyPayAvailable() )
							&& !pTempPlayer->updatePayPlayTime(pTempPlayer->getID(), currentDateTime, currentTime))
						{
							Creature* pCreature = pTempPlayer->getCreature();
							Zone* pZone = pCreature->getZone();
							Assert(pZone!=NULL);

							// 유료 서비스 종료
							pTempPlayer->logoutPayPlay( pTempPlayer->getID() );

							// 패밀리 요금 사용자인 경우 FamilyPayAvailable flag 을 꺼준다.
							// 패밀리 요금 디폴트 옵션을 끊다.
							if ( pTempPlayer->isFamilyPayAvailable() )
							{
								pTempPlayer->setFamilyPayAvailable( false );

								// 파티원일 경우 Family Pay를 refresh 한다.
								int PartyID = pCreature->getPartyID();
								if ( PartyID != 0 )
								{
									g_pGlobalPartyManager->refreshFamilyPay( PartyID );
								}

								PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
								Assert( pPC != NULL );

								pPC->removeDefaultOptionSet( DEFAULT_OPTION_SET_FAMILY_PAY );
								pPC->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
							}

							// by sigi. 2002.12.30
							IsPayPlayEnd = true;

						// Zone단위 유료인 경우는.. 무료존으로 옮긴다.
						#if defined(__PAY_SYSTEM_ZONE__)
							
							// 유료 서비스 사용 불가인 경우
							//
							// slayer : 에슬남동에서 부활하는 곳으로 간다.
							// vampire : 림보남동에서 부활하는 곳으로 간다.
							if (pZone->isPayPlay())
							{
								ZONE_COORD zoneCoord;

								Assert( pCreature->isPC() );
								PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
								Assert( pPC != NULL );

								// 클라이언트에 유료 사용이 끝났다는 메시지를 출력하도록한다.
								// 일단 무료존으로 이동하게 되므로 지금 보내줘서는 소용이 없다.
								// 새로운 존에 들어가서 메시지를 받도록 한다.
								Statement* pStmt = NULL;

								BEGIN_DB
								{
									uint strID = STRID_END_PAY_PLAY;

									// 패밀리 요금제 해제로 인한 무료존 이동시 메시지
									if ( pTempPlayer->isFamilyFreePassEnd() )
										strID = STRID_FAMILY_FREE_PLAY_END;

									pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
									pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s')", pPC->getName().c_str(), g_pStringPool->c_str( strID ) );
									
									if ( pCreature->isFlag( Effect::EFFECT_CLASS_LOGIN_GUILD_MESSAGE ) )
										pCreature->removeFlag( Effect::EFFECT_CLASS_LOGIN_GUILD_MESSAGE );

									SAFE_DELETE(pStmt);
								}
								END_DB(pStmt)
							
								// 무료존으로 옮긴다.
								if ( g_pResurrectLocationManager->getRaceDefaultPosition( pPC->getRace(), zoneCoord ) )
								{
									transportCreature(pCreature, zoneCoord.id, zoneCoord.x, zoneCoord.y, true);
								}
								else
								{
									// 아, 비상이닷...
									throw Error("Critical Error : ResurrectInfo is not established!1");
								}
							}
						#elif defined(__PAY_SYSTEM_FREE_LIMIT__) || defined(__PAY_SYSTEM_LOGIN__) 
							//cout << "Pay timeout" << endl;
							//throw DisconnectException();

							PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
							Assert(pPC!=NULL);

							if (pPC->isPayPlayAvaiable())
							{
								// 유료존일 경우 무료존으로 옮긴다.
								if (pZone->isPayPlay())
								{
									ZONE_COORD zoneCoord;

									Assert( pCreature->isPC() );
									PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
									Assert( pPC != NULL );
									
									if ( g_pResurrectLocationManager->getRaceDefaultPosition( pPC->getRace(), zoneCoord ) )
									{
										transportCreature(pCreature, zoneCoord.id, zoneCoord.x, zoneCoord.y, true);
									}
									else
									{
										// 아, 비상이닷...
										throw Error("Critical Error : ResurrectInfo is not established!1");
									}
								}
								else
								{
									GCSystemMessage gcSystemMessage;
									gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPIRE_PREMIUM_SERVICE ) );
									pTempPlayer->sendPacket( &gcSystemMessage );
								}
							}
							else
							{
								pTempPlayer->kickPlayer( 30, KICK_MESSAGE_PAY_TIMEOUT );
/*								EventKick* pEventKick = new EventKick(pTempPlayer);
								pEventKick->setDeadline(30*10);
								pTempPlayer->addEvent(pEventKick);

								// 몇 초후에 짤린다..고 보내준다.
								GCKickMessage gcKickMessage;
								gcKickMessage.setType( KICK_MESSAGE_PAY_TIMEOUT );
								gcKickMessage.setSeconds( 30 );
								pTempPlayer->sendPacket( &gcKickMessage ); */
							}

						#endif
						}
				
						/*
						#if defined(__THIALAND_SERVER__)
						// add by inthesky for THAILAND ChildGuard rule
						Timeval cTime;
						getCurrentTime(cTime);

						if(cTime > m_tmChildGuardCheckTerm )    // m_nChildGuardCheckTerm 시간마다 한번씩만 체크
						{
							//cout << "check time : 30sec.."<<endl;
							bool bChildGuardArea = onChildGuardTimeArea(m_nChildGuardStartTime, m_nChildGuardEndTime, m_bChildGuard);

                            //if(bChildGuardArea)   cout << "ChildGuard Area : Yes" << endl;
                            //else                  cout << "ChildGuard Area : No" << endl;

                            //if(pTempPlayer->getPermission())      cout << "Player Permission : ALLOW"<<endl;
                            //else                                  cout << "Player Permission : DENY"<<endl;

							if( bChildGuardArea && !pTempPlayer->getPermission() )
							{
								pTempPlayer->kickPlayer( m_nChildGuardKickTime, KICK_MESSAGE_CHILDGUARD );
							}

							m_tmChildGuardCheckTerm = cTime;
							m_tmChildGuardCheckTerm.tv_sec += m_nChildGuardCheckTerm;
						}
						#endif
						*/
#ifdef __THAILAND_SERVER__
						// child guard check !
						if ( !pTempPlayer->getPermission() && g_pTimeChecker->isInPeriod( TIME_PERIOD_CHILD_GUARD ) )
						{
							pTempPlayer->kickPlayer( 30, KICK_MESSAGE_CHILDGUARD );
						}
#endif

						// 패밀리 요금제 적용이 끝났다면, 다시 체크하지 않게 하기위에 타입을 바꿔준다.
						if ( pTempPlayer->isFamilyFreePassEnd() )
						{
							pTempPlayer->setFamilyPayPartyType( FAMILY_PAY_PARTY_TYPE_NONE );
						}

#ifdef __CONNECT_CBILLING_SYSTEM__
						if ( !pTempPlayer->isPayPlayer() )
						{
							// 유료 시간 끝났음. 짜른다.
							pTempPlayer->kickPlayer( 30, KICK_MESSAGE_PAY_TIMEOUT );
						}
						else
						{
							// 유료 사용자의 경우 pay info 를 아직 안 보내줬다면 보내준다.
							if ( pTempPlayer->isCBillingVerified() && !pTempPlayer->isCBShowPayInfo() )
							{
								pTempPlayer->sendCBillingPayInfo();
								pTempPlayer->setCBShowPayInfo();
							}
						}
#endif
					}
				} 
				catch (ProtocolException & pe) 
				{

					pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
					pTempPlayer->setItemRatioBonusPoint(11);

					try
					{
						CGLogoutHandler::execute( NULL, pTempPlayer );
					}
					catch ( DisconnectException& de )
					{
						filelog( "DIFF_ZG.log", "%s ZPM+PC+PE", de.toString().c_str() );
						deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
						pushOutPlayer( pTempPlayer );
					}

					// by sigi. 2002.12.30
					if (IsPayPlayEnd)
					{
						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_COMMAND_PAYPLAY_END );
					}
					else
					{
						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_COMMAND_ERROR );
					}

					/*
					try 
					{
						// 출력 버퍼를 플러시한다.
						pTempPlayer->disconnect(UNDISCONNECTED);
					} 
					catch (Throwable & t) 
					{
						filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processCommands(4)", t.toString().c_str());
					}

					deletePlayer(i);
					deleteQueuePlayer(pTempPlayer);

					// 플레이어 객체를 삭제한다.
					delete pTempPlayer;
					*/
				}
			}
		}
	}

//	__ENTER_CRITICAL_SECTION(m_Mutex)
/*

	if (m_MinFD == -1 && m_MaxFD == -1) {	// no player exist
		m_Mutex.unlock();
		return;
	}

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) {

		if (m_pPlayers[i] != NULL) {

			Assert (m_pPlayers[i] != NULL);

			if (m_pPlayers[i]->getSocket()->getSockError()) {

				try {
				// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
				m_pPlayers[i]->disconnect(DISCONNECTED);
				} catch (Throwable & t) {
				}


				// 플레이어 객체를 삭제한다.
				delete m_pPlayers[i];	

				// 플레이어 매니저에서 플레이어 포인터를 삭제한다.
//				deletePlayer_NOBLOCKED(i);
				deletePlayer(i);

			} else {

				try {

					m_pPlayers[i]->processCommand();

				} catch (ProtocolException & pe) {

	//				LOG1("INVALID PROTOCOL %s (%s)\n", m_pPlayers[i]->getID().c_str() , pe.toString().c_str());

					try {

					// 출력 버퍼를 플러시한다.
					m_pPlayers[i]->disconnect(UNDISCONNECTED);

					} catch (Throwable & t) {
					}

					// 플레이어 객체를 삭제한다.
					delete m_pPlayers[i];

					// 플레이어 매니저에서 플레이어 포인터를 삭제한다.
//					deletePlayer_NOBLOCKED(i);
					deletePlayer(i);

				}
			}
		}
	}
*/


//	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// process all players' outputs
//
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::processOutputs () 
	throw (IOException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{	
		//m_Mutex.unlock();
		return;
	}

	//copyPlayers();

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (FD_ISSET(i , &m_WriteFDs[1])) 
		{
			if (m_pPlayers[i] != NULL) 
			{
				GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
				Assert (pTempPlayer);
				Assert (m_pPlayers[i] != NULL);

				if (pTempPlayer->getSocket()->getSockError()) 
				{	
					pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
					pTempPlayer->setItemRatioBonusPoint(12);

					try
					{
						CGLogoutHandler::execute( NULL, pTempPlayer );
					}
					catch ( DisconnectException& de )
					{
						filelog( "DIFF_ZG.log", "%s ZPM+PO+SOCKERR", de.toString().c_str() );
						deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
						pushOutPlayer( pTempPlayer );
					}

					// by sigi. 2002.12.30
//					UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_OUTPUT_ERROR );
					/*
					try 
					{
						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
						pTempPlayer->disconnect(DISCONNECTED);
					} 
					catch (Throwable & t) 
					{
						filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processOutput(1)", t.toString().c_str());
					}

					deletePlayer(i);
					deleteQueuePlayer(pTempPlayer);

					// 플레이어 객체를 삭제한다.
					delete pTempPlayer;
					*/
				} 
				else 
				{
					try 
					{
						pTempPlayer->processOutput();
					} 
					catch (ConnectException & ce) 
					{
						pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
						pTempPlayer->setItemRatioBonusPoint(13);

						try
						{
							CGLogoutHandler::execute( NULL, pTempPlayer );
						}
						catch ( DisconnectException& de )
						{
							filelog( "DIFF_ZG.log", "%s ZPM+PO+CE", de.toString().c_str() );
							deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
							pushOutPlayer( pTempPlayer );
						}

						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_OUTPUT_DISCONNECT );

						/*
						try 
						{
							// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
							pTempPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processOutput(4)", t.toString().c_str());
						}

						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						// 플레이어 객체를 삭제한다.
						delete pTempPlayer;
						*/
					} 
					catch (ProtocolException & cp) 
					{
						pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
						pTempPlayer->setItemRatioBonusPoint(14);

						try
						{
							CGLogoutHandler::execute( NULL, pTempPlayer );
						}
						catch ( DisconnectException& de )
						{
							filelog( "DIFF_ZG.log", "%s ZPM+PO+PE", de.toString().c_str() );
							deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
							pushOutPlayer( pTempPlayer );
						}

						// by sigi. 2002.12.30
//						UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_OUTPUT_DISCONNECT2 );

						/*
						// 이미 연결이 종료되었으므로, 출력 버퍼를 플러시해서는 안된다.
						try 
						{
							pTempPlayer->disconnect(DISCONNECTED);
						} 
						catch (Throwable & t) 
						{
							filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processOutput(7)", t.toString().c_str());
						}

						deletePlayer(i);
						deleteQueuePlayer(pTempPlayer);

						// 플레이어 객체를 삭제한다.
						delete pTempPlayer;
						*/
					}
				}
			}
		}
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// process all players' exceptions
//
// 현재까지는 OOB 데이타를 전송할 계획은 없다.
// 따라서, 만약 OOB가 켜져 있다면 에러로 간주하고 접속을 확 짤라 버린다.
//
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::processExceptions () 
	throw (IOException , Error)
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	if (m_MinFD == -1 && m_MaxFD == -1) // no player exist
	{	
		//m_Mutex.unlock();
		return;
	}
	//	copyPlayers();

	for (int i = m_MinFD ; i <= m_MaxFD ; i ++) 
	{
		if (FD_ISSET(i , &m_ExceptFDs[1])) 
		{
			if (m_pPlayers[i] != NULL && m_pPlayers[i] == m_pPlayers[i]) 
			{
				GamePlayer* pTempPlayer = dynamic_cast<GamePlayer*>(m_pPlayers[i]);
				Assert (pTempPlayer != NULL);
				Assert (m_pPlayers[i] != NULL);

				pTempPlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
				pTempPlayer->setItemRatioBonusPoint(15);

				try
				{
					CGLogoutHandler::execute( NULL, pTempPlayer );
				}
				catch ( DisconnectException& de )
				{
					filelog( "DIFF_ZG.log", "%s ZPM+PE", de.toString().c_str() );
					deletePlayer( pTempPlayer->getSocket()->getSOCKET() );
					pushOutPlayer( pTempPlayer );
				}

				// by sigi. 2002.12.30
//				UserGateway::getInstance()->passUser( UserGateway::USER_OUT_ZPM_EXCEPTION );

				/*
				try 
				{
					// 출력 버퍼를 플러시한다.
					m_pPlayers[i]->disconnect(UNDISCONNECTED);
				} 
				catch (Throwable & t) 
				{
					filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::processException(1)", t.toString().c_str());
				}

				deletePlayer(i);
				deleteQueuePlayer(pTempPlayer);

				// 플레이어 객체를 삭제한다.
				delete pTempPlayer;
				*/
			}
		}
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// 특정 플레이어를 매니저에 추가한다.
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::addPlayer (GamePlayer* pGamePlayer) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	PlayerManager::addPlayer(pGamePlayer);


	SOCKET fd = pGamePlayer->getSocket()->getSOCKET();

	// m_MinFD , m_MaxFD 를 재조정한다.
	if (m_MinFD == -1 && m_MaxFD == -1) 
	{
		// 최초의 플레이어의 경우
		m_MinFD = m_MaxFD = fd;
	} 
	else 
	{
		m_MinFD = min(fd , m_MinFD);
		m_MaxFD = max(fd , m_MaxFD);
	}

	// 모든 fd_set 에 fd 비트를 on 시킨다.
	// m_XXXFDs[1] 은 다음번에 처리해주면 된다.
	FD_SET(fd , &m_ReadFDs[0]);
	FD_SET(fd , &m_WriteFDs[0]);
	FD_SET(fd , &m_ExceptFDs[0]);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 특정 플레이어를 매니저에 추가한다.
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::addPlayer_NOBLOCKED (GamePlayer* pGamePlayer) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	PlayerManager::addPlayer(pGamePlayer);


	SOCKET fd = pGamePlayer->getSocket()->getSOCKET();

	// m_MinFD , m_MaxFD 를 재조정한다.
	if (m_MinFD == -1 && m_MaxFD == -1) 
	{
		// 최초의 플레이어의 경우
		m_MinFD = m_MaxFD = fd;
	} 
	else 
	{
		m_MinFD = min(fd , m_MinFD);
		m_MaxFD = max(fd , m_MaxFD);
	}

	// 모든 fd_set 에 fd 비트를 on 시킨다.
	// m_XXXFDs[1] 은 다음번에 처리해주면 된다.
	FD_SET(fd , &m_ReadFDs[0]);
	FD_SET(fd , &m_WriteFDs[0]);
	FD_SET(fd , &m_ExceptFDs[0]);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 특정 플레이어를 매니저에서 삭제한다.
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::deletePlayer_NOBLOCKED (SOCKET fd) 
	throw (OutOfBoundException , NoSuchElementException , Error)
{
	__BEGIN_TRY

	// 플레이어 포인터를 플레이어 배열에서 삭제한다.
	PlayerManager::deletePlayer(fd);

	Assert(m_pPlayers[fd] == NULL);

	// m_MinFD , m_MaxFD 를 재조정한다.
	// fd == m_MinFD && fd == m_MaxFD 인 경우는 첫번째 if 에서 처리된다.
	if (fd == m_MinFD) {

		// 앞에서부터 제일 작은 fd 를 찾는다.
		// m_MinFD 자리는 현재 NULL 이 되어 있음을 유의하라.
		int i = m_MinFD;
		for (i = m_MinFD ; i <= m_MaxFD ; i ++) {
			if (m_pPlayers[i] != NULL) {
				m_MinFD = i;	
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		// 이때에는 m_MinFD == m_MaxFD 인 경우이다.
		// 이때에는 둘 다 -1 로 설정해주자.
		if (i > m_MaxFD)
			m_MinFD = m_MaxFD = -1;

	} else if (fd == m_MaxFD) {

		// 뒤에서부터 가장 큰 fd 를 찾는다.
		int i = m_MaxFD;
		for (i = m_MaxFD ; i >= m_MinFD ; i --) {
			if (m_pPlayers[i] != NULL) {
				m_MaxFD = i;
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		if (i < m_MinFD) 
		{
			filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::deletePlayer_NOBLOCKED()", "MinMaxFD problem");
			throw UnknownError("m_MinFD & m_MaxFD problem.");
		}
	}

	// 모든 fd_set 에 fd 비트를 off 시킨다.
	// m_XXXFDs[1]도 고쳐야 하는 이유는, 이후 처리에서 객체가 없어졌는데도
	// 처리받을 확률이 있기 때문이다.
	FD_CLR(fd , &m_ReadFDs[0]);
	FD_CLR(fd , &m_ReadFDs[1]);
	FD_CLR(fd , &m_WriteFDs[0]);
	FD_CLR(fd , &m_WriteFDs[1]);
	FD_CLR(fd , &m_ExceptFDs[0]);
	FD_CLR(fd , &m_ExceptFDs[1]);


	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 특정 플레이어를 매니저에서 삭제한다.
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::deletePlayer (SOCKET fd) 
	throw (OutOfBoundException , NoSuchElementException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	try
	{
		// 플레이어 포인터를 플레이어 배열에서 삭제한다.
		PlayerManager::deletePlayer(fd);
	}
	catch ( OutOfBoundException& o )
	{
		filelog( "ZPMError.txt", "OOB: %s, Socket: %d", o.toString().c_str(), fd );
		throw;
	}
	catch ( NoSuchElementException& n )
	{
		filelog( "ZPMError.txt", "NSEE: %s, Socket: %d", n.toString().c_str(), fd );
		throw;
	}
	catch ( Error& e)
	{
		filelog( "ZPMError.txt", "Error: %s, Socket: %d", e.toString().c_str(), fd );
		throw;
	}
	catch (...)
	{
		filelog( "ZPMError.txt", "난 몰라. Socket: %d", fd );
		throw;
	}

	Assert(m_pPlayers[fd] == NULL);

	// m_MinFD , m_MaxFD 를 재조정한다.
	// fd == m_MinFD && fd == m_MaxFD 인 경우는 첫번째 if 에서 처리된다.
	if (fd == m_MinFD) {

		// 앞에서부터 제일 작은 fd 를 찾는다.
		// m_MinFD 자리는 현재 NULL 이 되어 있음을 유의하라.
		int i = m_MinFD;
		for (i = m_MinFD ; i <= m_MaxFD ; i ++) {
			if (m_pPlayers[i] != NULL) {
				m_MinFD = i;	
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		// 이때에는 m_MinFD == m_MaxFD 인 경우이다.
		// 이때에는 둘 다 -1 로 설정해주자.
		if (i > m_MaxFD)
			m_MinFD = m_MaxFD = -1;

	} else if (fd == m_MaxFD) {

		// 뒤에서부터 가장 큰 fd 를 찾는다.
		int i = m_MaxFD;
		for (i = m_MaxFD ; i >= m_MinFD ; i --) {
			if (m_pPlayers[i] != NULL) {
				m_MaxFD = i;
				break;
			}
		}

		// 적절한 m_MinFD를 찾지 못했을 경우,
		if (i < m_MinFD) 
		{
			filelog("ZonePlayerManagerBug.txt", "%s : %s", "ZonePlayerManager::deletePlayer()", "MinMaxFD problem");
			throw UnknownError("m_MinFD & m_MaxFD problem.");
		}
	}

	// 모든 fd_set 에 fd 비트를 off 시킨다.
	// m_XXXFDs[1]도 고쳐야 하는 이유는, 이후 처리에서 객체가 없어졌는데도
	// 처리받을 확률이 있기 때문이다.
	FD_CLR(fd , &m_ReadFDs[0]);
	FD_CLR(fd , &m_ReadFDs[1]);
	FD_CLR(fd , &m_WriteFDs[0]);
	FD_CLR(fd , &m_WriteFDs[1]);
	FD_CLR(fd , &m_ExceptFDs[0]);
	FD_CLR(fd , &m_ExceptFDs[1]);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
Player* ZonePlayerManager::getPlayer (SOCKET fd)
	throw (OutOfBoundException , NoSuchElementException , Error)
{
	__BEGIN_TRY

	Player* pPlayer = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	pPlayer = PlayerManager::getPlayer(fd);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return pPlayer;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
Player* ZonePlayerManager::getPlayerByPhoneNumber(PhoneNumber_t PhoneNumber)
	throw(OutOfBoundException, NoSuchElementException , Error)
{
	__BEGIN_TRY
	return NULL;
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 전체 사용자들의 세이브를 담당하는 루틴.
// 다른 쓰레드에서 접근 할 수 있으므로 락을 걸어 줘야 하나..
// 현재 쓰레드의 Event처리를 하면서 save를 할 수 있으므로...
// 하위 save에 Lock을 걸어주고 이 루틴에서는 함수만 호출하도록 한다.
// ZonePlayerManager:: save()
//////////////////////////////////////////////////////////////////////
void ZonePlayerManager::save()
	throw(Error)
{

	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	unsigned int i;

	for(i = 0; i < nMaxPlayers ; i++) 
	{
		if (m_pPlayers[i] != NULL) 
		{
			Assert(m_pPlayers[i] != NULL);	// by sigi

			Creature* pCreature = ((GamePlayer*)m_pPlayers[i])->getCreature();

			Assert(pCreature != NULL);	// by sigi

			pCreature->save();
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void ZonePlayerManager::pushPlayer(GamePlayer* pGamePlayer)
	throw(Error)
{
	__BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_Mutex)

    m_PlayerListQueue.push_back(pGamePlayer);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void ZonePlayerManager::pushOutPlayer(GamePlayer* pGamePlayer)
	throw(Error)
{
	__BEGIN_TRY

    m_PlayerOutListQueue.push_back(pGamePlayer);

	__END_CATCH
}

void ZonePlayerManager::processPlayerListQueue()
	throw(Error) 
{
	__BEGIN_TRY

	// PlayerQueue의 Player를 메니져에 추가한다.    
	while(! m_PlayerListQueue.empty())
	{
		GamePlayer* pGamePlayer = m_PlayerListQueue.front();

		if (pGamePlayer == NULL)
		{
			filelog("ZoneBug.txt", "%s : %s", "Zone::heartbeat(1)", "pGamePlayer가 NULL입니다.");
			continue;
		}

		addPlayer_NOBLOCKED(pGamePlayer);

		m_PlayerListQueue.pop_front();
	
		Creature* pCreature = pGamePlayer->getCreature();

		Assert(pCreature != NULL);

		// 새로 들어갈 Zone.. by sigi. 2002.5.11
		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		/*
		// getNewZone()은 IncomingPlayerManager에서 처리하도록 했다.
		// by sigi. 2002.5.15
		if (pZone==NULL)
		{
			pZone = pCreature->getZone();
			Assert(pZone != NULL);
		}
		else
		{
			pCreature->setZone( pZone );
			pCreature->setNewZone( NULL );

			pCreature->setXY( pCreature->getNewX(), pCreature->getNewY() );

			// 새 Zone에 들어가게 되는 경우
			//pCreature->registerObject();
		}
		*/

		pZone->addPC(pCreature, pCreature->getX(), pCreature->getY(), DOWN);
	}

	__END_CATCH
}

void ZonePlayerManager::heartbeat()
	throw(Error) 
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	processPlayerListQueue();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	// 나갈 대기열에 있는 사람을 처리 해 준다.
	// 기냥 IPM으로 Push하믄 끝이다.
	while(!m_PlayerOutListQueue.empty()) 
	{
		GamePlayer* pGamePlayer = m_PlayerOutListQueue.front();

		m_PlayerOutListQueue.pop_front();

		Assert(pGamePlayer != NULL);

		g_pIncomingPlayerManager->pushPlayer(pGamePlayer);
	}

	// broadcast packet queue 를 처리한다.
	if ( !m_BroadcastQueue.empty() )
		flushBroadcastPacket();

	__END_CATCH
}

void ZonePlayerManager::deleteQueuePlayer(GamePlayer* pGamePlayer)
    throw(NoSuchElementException , Error)
{

    __BEGIN_TRY

	// 필요없는 lock인거 같다.
	// 제거 by sigi. 2002.5.9
	//__ENTER_CRITICAL_SECTION(m_Mutex)

	Assert(pGamePlayer != NULL);

	list<GamePlayer *>::iterator itr = find_if (m_PlayerOutListQueue.begin(), m_PlayerOutListQueue.end(), isSamePlayer(pGamePlayer));

	if (itr != m_PlayerOutListQueue.end()) 
	{
		m_PlayerOutListQueue.erase(itr);
	}

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void    ZonePlayerManager::removeFlag (Effect::EffectClass EC) 
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for (uint i = 0; i < nMaxPlayers ; i++) 
	{
		Player* pPlayer = m_pPlayers[i];

		if (pPlayer != NULL) 
		{
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>( pPlayer );
			Assert(pGamePlayer!=NULL);

			Creature* pCreature = pGamePlayer->getCreature();
			Assert(pCreature != NULL);

			pCreature->removeFlag( EC );
		}
    }

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// ZonePlayerManager 에 있는 모든 사용자를 정리한다.
////////////////////////////////////////////////////////////////////////
void ZonePlayerManager::clearPlayers()
	throw (Error)
{
	__BEGIN_TRY

	// PlayerListQueue 에 있는 애들을 정리한다.
	while ( !m_PlayerListQueue.empty() )
	{
		GamePlayer* pGamePlayer = m_PlayerListQueue.front();

		m_PlayerListQueue.pop_front();

		if ( pGamePlayer != NULL )
		{
			try
			{
				pGamePlayer->disconnect();
			}
			catch ( Throwable& t )
			{
				// 무시
			}

			SAFE_DELETE( pGamePlayer );
		}
	}

	// PlayerOutListQueue 에 있는 애들을 정리한다.
	while ( !m_PlayerOutListQueue.empty() )
	{
		GamePlayer* pGamePlayer = m_PlayerOutListQueue.front();

		m_PlayerOutListQueue.pop_front();

		if ( pGamePlayer != NULL )
		{
			try
			{
				pGamePlayer->disconnect();
			}
			catch ( Throwable& t )
			{
				// 무시
			}

			SAFE_DELETE( pGamePlayer );
		}
	}

	if ( m_MinFD == -1 && m_MaxFD == -1 )
		return;

	// 플레이어를 정리한다.
	for ( int i = m_MinFD; i <= m_MaxFD; i ++ )
	{
		if ( m_pPlayers[i] != NULL )
		{
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>( m_pPlayers[i] );

			if ( pGamePlayer != NULL )
			{
				try
				{
					pGamePlayer->disconnect();
				}
				catch ( Throwable& t )
				{
					// 무시
				}

				SAFE_DELETE( pGamePlayer );
			}
		}
	}

	__END_CATCH
}

bool checkZonePlayerManager( GamePlayer* pGamePlayer, ZonePlayerManager* pZPM, const string& str )
{
	if ( pGamePlayer == NULL )
		return true;

	Creature* pCreature = pGamePlayer->getCreature();
	if ( pCreature == NULL )
		return true;

	Zone* pZone = pCreature->getZone();
	if ( pZone == NULL )
		return true;

	ZoneGroup* pZoneGroup = pZone->getZoneGroup();
	if ( pZoneGroup == NULL )
		return true;

	ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
	if ( pZonePlayerManager == NULL )
		return true;

	if ( pZPM != pZonePlayerManager )
	{
		filelog( "ZPMCheck.log", "CZPM:%u GZPM:%u SOCK:%d ZID:%u NAME:%s P:%s",
					pZPM->getZGID(), 
					pZonePlayerManager->getZGID(),
					pGamePlayer->getSocket()->getSOCKET(),
					pZone->getZoneID(),
					pCreature->getName().c_str(),
					str.c_str() );

		return false;
	}

	return true;
}
#if defined(__THAILAND_SERVER__)
// 태국용이다. 미성년자 접속을 막기 위한 코드이다.
// 현재 시간중 (시*100+분) 값을 이용해서 차단중인 시간대 인지 아닌지를 구별한다.
//
// 예를들어 오전 6시 30분의 경우 630 이란 값이
// 오후 11시 15분일경우 2315 가 된다.
//
// 입력 - am : 이 시간 이전은 제한되는 시간대이다.
//        pm : 이 시간 이후는 제한되는 시간대이다.
//
//
// 출력 - true : 제한시간대이다.
//        false : 제한시간대가 아니다.
bool ZonePlayerManager::onChildGuardTimeArea(int pm, int am, bool bSwitch)
{
        bool returnValue = false;
        tm Timem;
        time_t daytime = time(0);
        localtime_r( &daytime, &Timem );

        int Hour    = Timem.tm_hour;
        int Min     = Timem.tm_min;

        int timeValue = (Hour*100) + Min;

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

// external variable definition
ZonePlayerManager* g_pZonePlayerManager = NULL;
