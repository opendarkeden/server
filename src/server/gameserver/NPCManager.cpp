//////////////////////////////////////////////////////////////////////////////
// Filename    : NPCManager.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "NPCManager.h"
#include "DB.h"
#include "NPC.h"
#include "Thread.h"
#include "PCFinder.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// class NPCManager member methods
//////////////////////////////////////////////////////////////////////////////

NPCManager::NPCManager () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

NPCManager::~NPCManager () 
	throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void NPCManager::load (ZoneID_t zoneID, int race) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	bool bLoadAllRace = (race==0xFF);

	BEGIN_DB
	{
		//StringStream sql;

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		if (bLoadAllRace)
		{
			pResult = pStmt->executeQuery( 
				"SELECT Name, NPCID, SpriteType, Race, MainColor, SubColor, ClanType, ShowInMinimap, TaxingCastleZoneID FROM NPC WHERE ZoneID = %d", (int)zoneID);
		}
		else
		{
			pResult = pStmt->executeQuery( 
				"SELECT Name, NPCID, SpriteType, Race, MainColor, SubColor, ClanType, ShowInMinimap, TaxingCastleZoneID FROM NPC WHERE ZoneID = %d AND Race = %d", (int)zoneID, (int)race);
		}

		while (pResult->next())
		{
			uint i = 0;

			string Name( pResult->getString(++i) );

			if (getCreature(Name)==NULL)
			{
				// create NPC object
				NPC* pNPC = new NPC();

				pNPC->setName( Name );
				pNPC->setNPCID(pResult->getInt(++i));
				pNPC->setSpriteType(pResult->getInt(++i));
				pNPC->setRace(pResult->getInt(++i));
				pNPC->setMainColor(pResult->getInt(++i));
				pNPC->setSubColor(pResult->getInt(++i));
				pNPC->setClanType(pResult->getInt(++i));

				int ShowInMinimap = pResult->getInt(++i);

				if (ShowInMinimap != 0) pNPC->setShowInMinimap(true);
				else pNPC->setShowInMinimap(false);

				pNPC->setTaxingCastleZoneID( pResult->getInt(++i) );

//				cout << pNPC->getName() << "은 " << pNPC->getTaxingCastleZoneID() << " 존에서 세금 매깁니다." << endl;
				filelog("NPC.log", "%s는 %u존에서 세금 매깁니다.", pNPC->getName().c_str(), pNPC->getTaxingCastleZoneID() );

				printf("NPC[%s] loading begin >> ", pNPC->getName().c_str());
				pNPC->init();
				printf("loading end\n");
				// NPC trace 를 위해 by DEW 2003. 04. 16
				g_pPCFinder->addNPC(pNPC);

				// NPC->init() 에서 NPC 의 Trigger 를 로드하고,
				// CONDITION_AT_FIRST 를 찾아서 실행하는데
				// 이때 ACTION_SET_POSITION 이 실행되면서 Zone에 NPC 를 추가한다.
				// 만일 NPC 의 CONDITION_AT_FIRST 가 ACTION_SET_POSITION 이 아니라면 문제가 생길듯
				//addCreature(pNPC);
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_DEBUG
	__END_CATCH
}
	
void NPCManager::processCreatures () 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Timeval currentTime;
	getCurrentTime(currentTime);

	try
	{
		hash_map<ObjectID_t, Creature*>::iterator itr = m_Creatures.begin();
		for (; itr != m_Creatures.end() ; itr++)
		{
			itr->second->act(currentTime);
		}
	}
	catch (Throwable & t)
	{
		filelog("NPCManagerBug.log", "ProcessCreatureBug : %s", t.toString().c_str());
		//cerr << t.toString() << endl;
	}

	__END_DEBUG
	__END_CATCH
}

string NPCManager::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "NPCManager("
		<< CreatureManager::toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}
