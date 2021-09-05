//////////////////////////////////////////////////////////////////////////////
// Filename    : Restore.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Restore.h"
#include "PCFinder.h"
#include "NPC.h"
#include "DB.h"
#include "Party.h"
#include "TradeManager.h"

#include "EffectBloodDrain.h"
#include "EffectRestore.h"

#include "GCSkillToObjectOK1.h"
#include "GCSkillToSelfOK1.h"
#include "GCMorph1.h"
#include "GCMorphSlayer2.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Restore::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;
	cout << "Restore2 Start" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pFromCreature = pZone->getCreature(TargetObjectID);

		// �����̾ �ǵ帱 ���� �ִ�.
		// NoSuch����. by sigi. 2002.5.2
		if (pFromCreature==NULL
			|| !pFromCreature->isVampire())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1; // ��ų �� �ѿ���...
		GCMorph1           _GCMorph1;           // ���� ����ڿ���..
		GCMorphSlayer2     _GCMorphSlayer2;     // ���� ����۵鿡��..

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		bool bRangeCheck = verifyDistance(pSlayer, pFromCreature, pSkillInfo->getRange());
		bool bHitRoll    = true;

		if (bRangeCheck && bHitRoll)
		{
			//////////////////////////////////////////////////////////////////////
			// ���� �� ���� ������ �����ؾ� �Ѵ�.
			//////////////////////////////////////////////////////////////////////

			// ��Ƽ �ʴ� ���̶�� ������ ������ �ش�.
			PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();
			Assert(pPIIM != NULL);
			pPIIM->cancelInvite(pFromCreature);

			// ��Ƽ ���� ������ ������ �ش�.
			int PartyID = pFromCreature->getPartyID();
			if (PartyID != 0)
			{
				// ���� ���ÿ��� �����ϰ�...
				LocalPartyManager* pLPM = pZone->getLocalPartyManager();
				Assert(pLPM != NULL);
				pLPM->deletePartyMember(PartyID, pFromCreature);

				// �۷ι������� ������ �ش�.
				deleteAllPartyInfo(pFromCreature);
			}

			// Ʈ���̵� ���̾��ٸ� Ʈ���̵� ���� ������ �������ش�.
			TradeManager* pTM = pZone->getTradeManager();
			Assert(pTM != NULL);
			pTM->cancelTrade(pFromCreature);

			//////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////

			Slayer*  pNewSlayer = new Slayer;
			Vampire* pVampire   = dynamic_cast<Vampire*>(pFromCreature);

			// DB���� Ȥ�� �������� �� �𸣴� ���� ������ �������ش�.
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				StringStream sql;
				sql << "DELETE FROM EffectBloodDrain WHERE OwnerID = '" + pFromCreature->getName() + "'";
				pStmt->executeQueryString(sql.toString());
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			pNewSlayer->setName(pFromCreature->getName());

			// ũ���� ���� �÷��̾� �����Ϳ� �÷��̾� ���� ũ���� �����͸� �����Ѵ�.
			Player* pFromPlayer = pFromCreature->getPlayer();
			pNewSlayer->setPlayer(pFromPlayer);
			GamePlayer* pFromGamePlayer = dynamic_cast<GamePlayer*>(pFromPlayer);
			pFromGamePlayer->setCreature(pNewSlayer);

			pNewSlayer->setZone(pZone);
			pNewSlayer->load();
			pNewSlayer->setObjectID(pFromCreature->getObjectID());
			pNewSlayer->setMoveMode(Creature::MOVE_MODE_WALKING);
			
			ZoneCoord_t x    = pFromCreature->getX();
			ZoneCoord_t y    = pFromCreature->getY();
			Dir_t       dir  = pFromCreature->getDir();
			Tile&       tile = pZone->getTile(x, y);

			// �� pFromCreature ��, ������ �����̾� ��ü�� ������ ���̹Ƿ�,
			// PCFinder�� �� �ִ� ���� ������ ���� �� ���̴�. 
			// �׷��Ƿ� �����̾� �����͸� �����ְ�, ���ο� �����̾� �����͸� ���Ѵ�.
			g_pPCFinder->deleteCreature(pFromCreature->getName());
			g_pPCFinder->addCreature(pNewSlayer);

			// ��� ���� ���� ��� ����Ʈ���� �����Ѵ�.
			if ( pVampire->getGuildID() != 0 )
				g_pGuildManager->getGuild( pVampire->getGuildID() )->deleteCurrentMember( pVampire->getName() );

			// �κ��丮 ��ü.
			Inventory* pInventory = pVampire->getInventory();
			pNewSlayer->setInventory(pInventory);
			pVampire->setInventory(NULL);

			// ������ ��ü
			pNewSlayer->deleteStash();
			pNewSlayer->setStash(pVampire->getStash());
			pNewSlayer->setStashNum(pVampire->getStashNum());
			pNewSlayer->setStashStatus(false);
			pVampire->setStash(NULL);

			/*
			// ������ ��ü
			while (true)
			{
				Item* pGarbage = pVampire->popItemFromGarbage();

				// �� �̻� ���ٸ� �극��ũ...
				if (pGarbage == NULL) break;

				pNewSlayer->addItemToGarbage(pGarbage);
			}
			*/

			// �÷��� �� ��ü
			pNewSlayer->deleteFlagSet();
			pNewSlayer->setFlagSet(pVampire->getFlagSet());
			pVampire->setFlagSet(NULL);

			Item* pItem = NULL;
			_TPOINT point;

			// �԰� �ִ� �����۵��� �κ��丮 �Ǵ� �ٴ����� �ű��.
			for(int part = 0; part < (int)Vampire::VAMPIRE_WEAR_MAX; part++)
			{
				pItem = pVampire->getWearItem((Vampire::WearPart)part);
				if (pItem != NULL)
				{
					// ���� ���� �����ϰ�...
					pVampire->deleteWearItem((Vampire::WearPart)part);
			
					// �κ��丮�� �ڸ��� ������ �κ��丮�� ���ϰ�...
					if (pInventory->getEmptySlot(pItem, point))
					{
						pInventory->addItem(point.x, point.y, pItem);
						pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
					}
					// �ڸ��� ������ �ٴڿ� ����߸���.
					else
					{
						ZoneCoord_t ZoneX = pVampire->getX();
						ZoneCoord_t ZoneY = pVampire->getY();

						TPOINT pt;

						pt = pZone->addItem(pItem, ZoneX , ZoneY);

						if (pt.x != -1) 
						{
							pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
						} 
						else 
						{
							pItem->destroy();
							SAFE_DELETE(pItem);
						}
					}
				}
			}

			pItem = pVampire->getExtraInventorySlotItem();
			if (pItem != NULL)
			{
				pVampire->deleteItemFromExtraInventorySlot();

				// �κ��丮�� �ڸ��� ������ �κ��丮�� ���ϰ�...
				if (pInventory->getEmptySlot(pItem, point))
				{
					pInventory->addItem(point.x, point.y, pItem);
					pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
				}
				// �ڸ��� ������ �ٴڿ� ����߸���.
				else
				{
					TPOINT pt;
					ZoneCoord_t ZoneX = pVampire->getX();
					ZoneCoord_t ZoneY = pVampire->getY();

					pt = pZone->addItem(pItem, ZoneX , ZoneY);

					if (pt.x != -1) 
					{
						pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
					} 
					else 
					{
						pItem->destroy();
						SAFE_DELETE(pItem);
					}
				}
			}

			// �����̾� ������ �ִ� ���� �����̾�� �Ű��ش�.
			pNewSlayer->setGoldEx(pVampire->getGold());

			// ��ų ������ �����Ѵ�.
			pNewSlayer->sendSlayerSkillInfo();

			_GCMorph1.setPCInfo2(pNewSlayer->getSlayerInfo2());
			_GCMorph1.setInventoryInfo(pNewSlayer->getInventoryInfo());
			_GCMorph1.setGearInfo(pNewSlayer->getGearInfo());
			_GCMorph1.setExtraInfo(pNewSlayer->getExtraInfo());

			_GCMorphSlayer2.setSlayerInfo(pNewSlayer->getSlayerInfo3());

			pFromPlayer->sendPacket(&_GCMorph1);
			//pFromGamePlayer->deleteEvent(Event::EVENT_CLASS_REGENERATION);

			pZone->broadcastPacket(x, y, &_GCMorphSlayer2, pNewSlayer);

			// Ÿ�� �� ������ ���� �����̾ �����ϰ�, ���ο� �����̾ ���Ѵ�.
			tile.deleteCreature(pFromCreature->getObjectID());
			pZone->deletePC(pFromCreature);

			TPOINT pt = findSuitablePosition(pZone, x, y, Creature::MOVE_MODE_WALKING);
			Tile& newtile = pZone->getTile(pt.x, pt.y);

			newtile.addCreature(pNewSlayer);
			pNewSlayer->setXYDir(pt.x, pt.y, dir);

			pZone->addPC(pNewSlayer);

			pNewSlayer->tinysave("Race='SLAYER'");
			SAFE_DELETE(pFromCreature);

			// �þ� update..
			pZone->updateHiddenScan(pNewSlayer);
		
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			pSkillSlot->setRunTime(0);

			EffectRestore* pEffectRestore = new EffectRestore(pNewSlayer);
			pEffectRestore->setDeadline(60*60*24*7*10); // 7�� 
			pNewSlayer->addEffect(pEffectRestore);
			pNewSlayer->setFlag(Effect::EFFECT_CLASS_RESTORE);
			pEffectRestore->create(pNewSlayer->getName());
		}
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pFromCreature);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// NPC ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Restore::execute(NPC* pNPC, Creature* pFromCreature)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;
	cout << "NPC Restore start" << endl;

	Assert(pNPC != NULL);
	Assert(pFromCreature != NULL);

	try 
	{
		Zone* pZone = pNPC->getZone();
		Assert(pZone != NULL);

		// �����̾ �ǵ帱 ���� �ִ�.
		if (!pFromCreature->isVampire())
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCMorph1           _GCMorph1;           // ���� ����ڿ���..
		GCMorphSlayer2     _GCMorphSlayer2;     // ���� ����۵鿡��..

		SkillType_t SkillType = SKILL_RESTORE;

		//bool bRangeCheck = verifyDistance(pNPC, pFromCreature, pSkillInfo->getRange());
		bool bHitRoll    = true;

		//if (bRangeCheck && bHitRoll)
		if (bHitRoll)
		{
			//////////////////////////////////////////////////////////////////////
			// ���� �� ���� ������ �����ؾ� �Ѵ�.
			//////////////////////////////////////////////////////////////////////

			// ��Ƽ �ʴ� ���̶�� ������ ������ �ش�.
			PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();
			Assert(pPIIM != NULL);
			pPIIM->cancelInvite(pFromCreature);

			// ��Ƽ ���� ������ ������ �ش�.
			int PartyID = pFromCreature->getPartyID();
			if (PartyID != 0)
			{
				// ���� ���ÿ��� �����ϰ�...
				LocalPartyManager* pLPM = pZone->getLocalPartyManager();
				Assert(pLPM != NULL);
				pLPM->deletePartyMember(PartyID, pFromCreature);

				// �۷ι������� ������ �ش�.
				deleteAllPartyInfo(pFromCreature);
			}

			// Ʈ���̵� ���̾��ٸ� Ʈ���̵� ���� ������ �������ش�.
			TradeManager* pTM = pZone->getTradeManager();
			Assert(pTM != NULL);
			pTM->cancelTrade(pFromCreature);

			//////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////

			Slayer*  pNewSlayer = new Slayer;
			Vampire* pVampire   = dynamic_cast<Vampire*>(pFromCreature);

			// DB���� Ȥ�� �������� �� �𸣴� ���� ������ �������ش�.
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				StringStream sql;
				sql << "DELETE FROM EffectBloodDrain WHERE OwnerID = '" + pFromCreature->getName() + "'";
				pStmt->executeQueryString(sql.toString());
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			pNewSlayer->setName(pFromCreature->getName());
			pNewSlayer->setZone(pZone);
			pNewSlayer->load();
			pNewSlayer->setObjectID(pFromCreature->getObjectID());
			pNewSlayer->setMoveMode(Creature::MOVE_MODE_WALKING);
			
			ZoneCoord_t x    = pFromCreature->getX();
			ZoneCoord_t y    = pFromCreature->getY();
			Dir_t       dir  = pFromCreature->getDir();
			Tile&       tile = pZone->getTile(x, y);

			pNewSlayer->setXYDir(x, y, dir);

			// ũ���� ���� �÷��̾� �����Ϳ� �÷��̾� ���� ũ���� �����͸� �����Ѵ�.
			Player* pFromPlayer = pFromCreature->getPlayer();
			pNewSlayer->setPlayer(pFromPlayer);
			GamePlayer* pFromGamePlayer = dynamic_cast<GamePlayer*>(pFromPlayer);
			pFromGamePlayer->setCreature(pNewSlayer);

			// �� pFromCreature ��, ������ �����̾� ��ü�� ������ ���̹Ƿ�,
			// PCFinder�� �� �ִ� ���� ������ ���� �� ���̴�. 
			// �׷��Ƿ� �����̾� �����͸� �����ְ�, ���ο� �����̾� �����͸� ���Ѵ�.
			g_pPCFinder->deleteCreature(pFromCreature->getName());
			g_pPCFinder->addCreature(pNewSlayer);

			// ��� ���� ���� ��� ����Ʈ���� �����Ѵ�.
			if ( pVampire->getGuildID() != 0 )
				g_pGuildManager->getGuild( pVampire->getGuildID() )->deleteCurrentMember( pVampire->getName() );

			// �κ��丮 ��ü.
			Inventory* pInventory = pVampire->getInventory();
			pNewSlayer->setInventory(pInventory);
			pVampire->setInventory(NULL);

			// ������ ��ü
			pNewSlayer->deleteStash();
			pNewSlayer->setStash(pVampire->getStash());
			pNewSlayer->setStashNum(pVampire->getStashNum());
			pNewSlayer->setStashStatus(false);
			pVampire->setStash(NULL);

			// �÷��� �� ��ü
			pNewSlayer->deleteFlagSet();
			pNewSlayer->setFlagSet(pVampire->getFlagSet());
			pVampire->setFlagSet(NULL);

			Item* pItem = NULL;
			_TPOINT point;

			// �԰� �ִ� �����۵��� �κ��丮 �Ǵ� �ٴ����� �ű��.
			for(int part = 0; part < (int)Vampire::VAMPIRE_WEAR_MAX; part++)
			{
				pItem = pVampire->getWearItem((Vampire::WearPart)part);
				if (pItem != NULL)
				{
					// ���� ���� �����ϰ�...
					pVampire->deleteWearItem((Vampire::WearPart)part);
			
					// �κ��丮�� �ڸ��� ������ �κ��丮�� ���ϰ�...
					if (pInventory->getEmptySlot(pItem, point))
					{
						pInventory->addItem(point.x, point.y, pItem);
						pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
					}
					// �ڸ��� ������ �ٴڿ� ����߸���.
					else
					{
						ZoneCoord_t ZoneX = pVampire->getX();
						ZoneCoord_t ZoneY = pVampire->getY();

						TPOINT pt;

						pt = pZone->addItem(pItem, ZoneX , ZoneY);

						if (pt.x != -1) 
						{
							pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
						} 
						else 
						{
							pItem->destroy();
							SAFE_DELETE(pItem);
						}
					}
				}
			}

			pItem = pVampire->getExtraInventorySlotItem();
			if (pItem != NULL)
			{
				pVampire->deleteItemFromExtraInventorySlot();

				// �κ��丮�� �ڸ��� ������ �κ��丮�� ���ϰ�...
				if (pInventory->getEmptySlot(pItem, point))
				{
					pInventory->addItem(point.x, point.y, pItem);
					pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
				}
				// �ڸ��� ������ �ٴڿ� ����߸���.
				else
				{
					TPOINT pt;
					ZoneCoord_t ZoneX = pVampire->getX();
					ZoneCoord_t ZoneY = pVampire->getY();

					pt = pZone->addItem(pItem, ZoneX , ZoneY);

					if (pt.x != -1) 
					{
						pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
					} 
					else 
					{
						pItem->destroy();
						SAFE_DELETE(pItem);
					}
				}
			}

			// �����̾� ������ �ִ� ���� �����̾�� �Ű��ش�.
			pNewSlayer->setGoldEx(pVampire->getGold());

			// ��ų ������ �����Ѵ�.
			pNewSlayer->sendSlayerSkillInfo();

			_GCMorph1.setPCInfo2(pNewSlayer->getSlayerInfo2());
			_GCMorph1.setInventoryInfo(pNewSlayer->getInventoryInfo());
			_GCMorph1.setGearInfo(pNewSlayer->getGearInfo());
			_GCMorph1.setExtraInfo(pNewSlayer->getExtraInfo());

			_GCMorphSlayer2.setSlayerInfo(pNewSlayer->getSlayerInfo3());

			pFromPlayer->sendPacket(&_GCMorph1);
			//pFromGamePlayer->deleteEvent(Event::EVENT_CLASS_REGENERATION);

			pZone->broadcastPacket(x, y, &_GCMorphSlayer2, pNewSlayer);

			// Ÿ�� �� ������ ���� �����̾ �����ϰ�, ���ο� �����̾ ���Ѵ�.
			tile.deleteCreature(pFromCreature->getObjectID());
			pZone->deletePC(pFromCreature);

			TPOINT pt = findSuitablePosition(pZone, x, y, Creature::MOVE_MODE_WALKING);
			Tile& newtile = pZone->getTile(pt.x, pt.y);

			newtile.addCreature(pNewSlayer);
			pNewSlayer->setXYDir(pt.x, pt.y, dir);

			pZone->addPC(pNewSlayer);

			pNewSlayer->tinysave("Race='SLAYER'");
			SAFE_DELETE(pFromCreature);

			// �þ� update..
			pZone->updateHiddenScan(pNewSlayer);

			EffectRestore* pEffectRestore = new EffectRestore(pNewSlayer);
			pEffectRestore->setDeadline(60*60*24*7*10); // 7�� 
			pNewSlayer->addEffect(pEffectRestore);
			pNewSlayer->setFlag(Effect::EFFECT_CLASS_RESTORE);
			pEffectRestore->create(pNewSlayer->getName());
		}
		else 
		{
			executeSkillFailNormal(pNPC, getSkillType(), pFromCreature);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pNPC, getSkillType());

	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Restore g_Restore;
