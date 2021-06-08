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
// Ŭ���̾�Ʈ�� CGLogout ��Ŷ�� ������, ���� ������ ũ��ó�� ������ �����ϰ�,
// ũ��ó�� ������ ������ DB�� ������ ��, ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGLogoutHandler::execute (CGLogout* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

//	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	// ���α��� ���������� Logout�� �ϸ� ��� ���·� ������ �Ѵ�.
	// Logout ��Ŷ�� ������ �÷��̾ IncomingPlayerManager�� ������.
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	//cout << "CGLogoutHandler: " << pGamePlayer->getID() << endl;

	Creature* pCreature = pGamePlayer->getCreature();

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();

	Assert(pZone != NULL);


	// ���� ������ ��� �α׸� �����.
	pGamePlayer->logLoginoutDateTime();

    try 
	{
		// �α׾ƿ��Ҷ� ����, ���� ���� ������ ����߸���.
//		bool bSendPacket = false;
//		dropRelicToZone( pCreature, bSendPacket );

		if ( pCreature->isPLAYER() && g_pPKZoneInfoManager->isPKZone( pCreature->getZoneID() ) )
		{
			g_pPKZoneInfoManager->leavePKZone( pCreature->getZoneID() );
		}

		if ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 && pPacket==NULL )
		{
		}
		else
		{
			// ũ��ó�� ������ �����Ѵ�.
			pCreature->save();

			if ( pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->tinysave("LastPlayDate=now()");
			}
			else if ( pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->tinysave("LastPlayDate=now()");
			}
			else if ( pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->tinysave("LastPlayDate=now()");
			}

			//////////////////////////////////////////////////////////////
			// �÷��̾ COMA����(���� ���� ����)��� �α׾ƿ��� �ڵ�����
			// ��Ȱ��ġ�� ĳ���͸� �̵���Ų��.
			// Login/Logout�� �ݺ����� ��Ȱ����� ������� ���ϰ� ��
			//
			// Creature�� ������ ���� DB�� ������Ʈ�� �� ���� ������Ʈ�� �Ѵ�.
			//////////////////////////////////////////////////////////////

			// ���ʹ�Ƽ�� �ѹ� �� ���·� �α׾ƿ��ϸ� ��Ȱ ��ġ�� ���󰣴�.
			if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA) || pCreature->isFlag(Effect::EFFECT_CLASS_ETERNITY))
			{
				//cout << "COMA ���¿��� �α׾ƿ�����" << endl;

				ZoneID_t  ZoneID = 0;
				ZoneCoord_t ZoneX = 0;
				ZoneCoord_t ZoneY = 0;
				ZONE_COORD ResurrectCoord;

				if ( pCreature->isPC() )
				{
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

					g_pResurrectLocationManager->getPosition( pPC, ResurrectCoord );

					ZoneID = ResurrectCoord.id;
					ZoneX  = ResurrectCoord.x;
					ZoneY  = ResurrectCoord.y;

					char pField[80];
					sprintf(pField, "ZoneID=%d, XCoord=%d, YCoord=%d, CurrentHP=HP", ZoneID, ZoneX, ZoneY);

					if ( pPC->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
						pSlayer->tinysave(pField);
					}
					else if ( pPC->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
						pVampire->tinysave(pField);
					}
					else if ( pPC->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
						pOusters->tinysave(pField);
					}
				}
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
				// ���� ������ �����Ѵ�.
				char pField[80];
				sprintf(pField, "ZoneID=%d, XCoord=%d, YCoord=%d, CurrentHP=HP", ZoneID, ZoneX, ZoneY);
				pVampire->tinysave(pField);
			}
*/
		}


		//
		// ����, ������ PC�� �����Ѵ�.
		//
		// *CAUTION*
		//
		// pCreature�� ��ǥ�� ������ pCreature�� �����ϴ� Ÿ���� ��ǥ�� ���ƾ� �Ѵ�.
		// ����, �� �޽�带 ȣ���ϱ� ���� ��ǥ�� �� �ٲ���� �Ѵ�..
		//
		pZone->deleteCreature(pCreature , pCreature->getX() , pCreature->getY());

		////cout << "PC deleted from Zone >> ";

		// ���׷��� ZPM���� �÷��̾ �����Ѵ�.
		// ZonePlayerManager�� ProcessCommand �ȿ��� ����� ���̹Ƿ� �ݵ�� NoBlocked ���� ������ �Ѵ�.
		pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(pGamePlayer->getSocket()->getSOCKET());

		// IPM���� �÷��̾ �ű��.
		//g_pIncomingPlayerManager->pushPlayer(pGamePlayer);

		// Core�� ������ �ٲٸ鼭 ������� ���� ���������� ���ϱ� ���Ͽ� �ڿ� �Ѳ����� ó���ϱ� ���ؼ�
		// OutList�� �ִ´�.
		pZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(pGamePlayer);

		////cout << "Move PC to IPM >> ";
	} 
	catch (NoSuchElementException & nsee) 
	{
		throw DisconnectException();
	}

	// �α��� ������ GLIncomingConnection�� ������.
	// PlayerName�� ClientIP�� ���� �Ǿ ������.
	//add by zdj
	GLIncomingConnection glIncomingConnection;
	glIncomingConnection.setPlayerID(pGamePlayer->getID());
	glIncomingConnection.setClientIP(pGamePlayer->getSocket()->getHost());

	g_pLoginServerManager->sendPacket(g_pConfig->getProperty("LoginServerIP") , 9999, &glIncomingConnection);

	pGamePlayer->setPlayerStatus(GPS_AFTER_SENDING_GL_INCOMING_CONNECTION);

#endif

	__END_DEBUG_EX __END_CATCH
}


