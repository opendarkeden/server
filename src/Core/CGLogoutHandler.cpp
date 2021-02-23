//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLogoutHandler.cc
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGLogout.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "Relic.h"
	#include "Creature.h"
	#include "LoginServerManager.h"
	#include "ZonePlayerManager.h"
	#include "Zone.h"
	#include "ZoneUtil.h"
	#include "RelicUtil.h"
	#include "ZoneInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "IncomingPlayerManager.h"
	#include "Properties.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "ResurrectLocationManager.h"
	#include "PKZoneInfoManager.h"
	#include <stdio.h>

	#include "GLIncomingConnection.h"
	#include "GCSystemMessage.h"
#endif


//////////////////////////////////////////////////////////////////////////////
// 클라이언트가 CGLogout 패킷을 보내면, 게임 서버는 크리처를 존에서 삭제하고,
// 크리처와 아이템 정보를 DB에 저장한 후, 접속을 종료한다.
//////////////////////////////////////////////////////////////////////////////
void CGLogoutHandler::execute (CGLogout* pPacket , Player* pPlayer)
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

//	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	// 새로그인 구조에서는 Logout을 하면 대기 상태로 나가야 한다.
	// Logout 패킷을 받으면 플레이어를 IncomingPlayerManager로 보낸다.
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	//cout << "CGLogoutHandler: " << pGamePlayer->getID() << endl;

	Creature* pCreature = pGamePlayer->getCreature();

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();

	Assert(pZone != NULL);


	// 나는 나간다 라고 로그를 남긴다.
	pGamePlayer->logLoginoutDateTime();

    try 
	{
		// 로그아웃할때 성물, 피의 성서 조각을 떨어뜨린다.
//		bool bSendPacket = false;
//		dropRelicToZone(pCreature, bSendPacket);

		if (pCreature->isPLAYER() && g_pPKZoneInfoManager->isPKZone(pCreature->getZoneID() ) )
		{
			g_pPKZoneInfoManager->leavePKZone(pCreature->getZoneID());
		}

		if (g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 && pPacket==NULL )
		{
		}
		else
		{
			// 크리처의 정보를 저장한다.
			pCreature->save();

			if (pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->tinysave("LastPlayDate=now()");
			}
			else if (pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->tinysave("LastPlayDate=now()");
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->tinysave("LastPlayDate=now()");
			}

			//////////////////////////////////////////////////////////////
			// 플레이어가 COMA상태(현재 죽은 상태)라면 로그아웃시 자동으로
			// 부활위치로 캐릭터를 이동시킨다.
			// Login/Logout의 반복으로 부활기술을 사용하지 못하게 함
			//
			// Creature의 정보를 먼저 DB에 업데이트한 후 새로 업데이트를 한다.
			//////////////////////////////////////////////////////////////

			// 이터니티를 한번 쓴 상태로 로그아웃하면 부활 위치로 날라간다.
			if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA) || pCreature->isFlag(Effect::EFFECT_CLASS_ETERNITY))
			{
				//cout << "COMA 상태에서 로그아웃했음" << endl;

				ZoneID_t  ZoneID = 0;
				ZoneCoord_t ZoneX = 0;
				ZoneCoord_t ZoneY = 0;
				ZONE_COORD ResurrectCoord;

				if (pCreature->isPC() )
				{
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

					g_pResurrectLocationManager->getPosition(pPC, ResurrectCoord);

					ZoneID = ResurrectCoord.id;
					ZoneX  = ResurrectCoord.x;
					ZoneY  = ResurrectCoord.y;

					char pField[80];
					sprintf(pField, "ZoneID=%d, XCoord=%d, YCoord=%d, CurrentHP=HP", ZoneID, ZoneX, ZoneY);

					if (pPC->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
						pSlayer->tinysave(pField);
					}
					else if (pPC->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
						pVampire->tinysave(pField);
					}
					else if (pPC->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
						pOusters->tinysave(pField);
					}
				}
			}

			// 포스 스크롤이 켜져 있으면 로그아웃하면저 저장한다.
			if (pCreature->isFlag(Effect::EFFECT_CLASS_BEHEMOTH_FORCE_SCROLL) )
			{
				Effect* pEffect = pCreature->findEffect(Effect::EFFECT_CLASS_BEHEMOTH_FORCE_SCROLL);
				pEffect->save(pCreature->getName());
			}
			if (pCreature->isFlag(Effect::EFFECT_CLASS_SAFE_FORCE_SCROLL) )
			{
				Effect* pEffect = pCreature->findEffect(Effect::EFFECT_CLASS_SAFE_FORCE_SCROLL);
				pEffect->save(pCreature->getName());
			}
			if (pCreature->isFlag(Effect::EFFECT_CLASS_CARNELIAN_FORCE_SCROLL) )
			{
				Effect* pEffect = pCreature->findEffect(Effect::EFFECT_CLASS_CARNELIAN_FORCE_SCROLL);
				pEffect->save(pCreature->getName());
			}
/*
			if(pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert(pSlayer != NULL);

				if (g_pResurrectLocationManager->getSlayerPosition(pSlayer->getResurrectZoneID(), ResurrectCoord))
				{
					ZoneID = ResurrectCoord.id;
					ZoneX  = ResurrectCoord.x;
					ZoneY  = ResurrectCoord.y;
				}
				else
				{
					if (g_pResurrectLocationManager->getSlayerPosition(pSlayer->getZone()->getZoneID(), ResurrectCoord))
					{
						ZoneID = ResurrectCoord.id;
						ZoneX  = ResurrectCoord.x;
						ZoneY  = ResurrectCoord.y;
					}
					else
					{
						throw Error("Critical Error: ResurrectInfo is not established");
					}
				}

				char pField[80];
				sprintf(pField, "ZoneID=%d, XCoord=%d, YCoord=%d, CurrentHP=HP", ZoneID, ZoneX, ZoneY);
				pSlayer->tinysave(pField);
			}
			else if(pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				Assert(pVampire != NULL);

				if (g_pResurrectLocationManager->getVampirePosition(pVampire->getResurrectZoneID(), ResurrectCoord))
				{
					ZoneID = ResurrectCoord.id;
					ZoneX  = ResurrectCoord.x;
					ZoneY  = ResurrectCoord.y;
				}
				else
				{
					if (g_pResurrectLocationManager->getVampirePosition(pVampire->getZone()->getZoneID(), ResurrectCoord))
					{
						ZoneID = ResurrectCoord.id;
						ZoneX  = ResurrectCoord.x;
						ZoneY  = ResurrectCoord.y;
					}
					else
					{
						throw Error("Critical Error: ResurrectInfo is not established");
					}
				}
				// 이제 정보를 저장한다.
				char pField[80];
				sprintf(pField, "ZoneID=%d, XCoord=%d, YCoord=%d, CurrentHP=HP", ZoneID, ZoneX, ZoneY);
				pVampire->tinysave(pField);
			}
*/
		}


		//
		// 이제, 존에서 PC를 삭제한다.
		//
		// *CAUTION*
		//
		// pCreature의 좌표가 실제로 pCreature가 존재하는 타일의 좌표와 같아야 한다.
		// 따라서, 이 메쏘드를 호출하기 전에 좌표를 잘 바꿔놔야 한당..
		//
		pZone->deleteCreature(pCreature , pCreature->getX() , pCreature->getY());

		////cout << "PC deleted from Zone >> ";

		// 존그룹의 ZPM에서 플레이어를 삭제한다.
		// ZonePlayerManager의 ProcessCommand 안에서 지우는 것이므로 반드시 NoBlocked 으로 지워야 한다.
		pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(pGamePlayer->getSocket()->getSOCKET());

		// IPM으로 플레이어를 옮긴다.
		//g_pIncomingPlayerManager->pushPlayer(pGamePlayer);

		// Core의 구조를 바꾸면서 쓰레드로 부터 독립적으로 행하기 위하여 뒤에 한꺼번에 처리하기 위해서
		// OutList로 넣는다.
		pZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(pGamePlayer);

		////cout << "Move PC to IPM >> ";
	} 
	catch (NoSuchElementException & nsee) 
	{
		throw DisconnectException();
	}

	// 로그인 서버로 GLIncomingConnection을 보낸다.
	// PlayerName과 ClientIP를 같이 실어서 보낸다.
	/*
	GLIncomingConnection glIncomingConnection;
	glIncomingConnection.setPlayerID(pGamePlayer->getID());
	glIncomingConnection.setClientIP(pGamePlayer->getSocket()->getHost());

	if (g_pConfig->getProperty("User") == "excel96")
		g_pLoginServerManager->sendPacket("211.117.52.12" , g_pConfig->getPropertyInt("LoginServerUDPPort"), &glIncomingConnection);
	else if (g_pConfig->getProperty("User") == "elcastle")
		g_pLoginServerManager->sendPacket("211.117.52.12" , g_pConfig->getPropertyInt("LoginServerUDPPort"), &glIncomingConnection);
	else if (g_pConfig->getProperty("User") == "elca")
		g_pLoginServerManager->sendPacket("211.117.52.12" , g_pConfig->getPropertyInt("LoginServerUDPPort"), &glIncomingConnection);
	*/

	pGamePlayer->setPlayerStatus(GPS_AFTER_SENDING_GL_INCOMING_CONNECTION);

#endif

	__END_DEBUG_EX __END_CATCH
}


