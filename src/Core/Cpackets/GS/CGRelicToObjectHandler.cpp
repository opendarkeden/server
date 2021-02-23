//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRelicToObjectHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRelicToObject.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Corpse.h"
	#include "Relic.h"
	#include "Monster.h"
	#include "MonsterCorpse.h"
	#include "EffectPrecedence.h"
	#include "EffectIncreaseAttr.h"
	#include "EffectRelicTable.h"
	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "EffectSlayerRelic.h"
	#include "EffectVampireRelic.h"
	#include "EffectKillTimer.h"
	#include "CombatInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "ZoneUtil.h"
	#include "VariableManager.h"
	#include "SkillUtil.h"
	#include "RelicUtil.h"
	#include "ShrineInfoManager.h"
	#include "CastleShrineInfoManager.h"
	#include "StringPool.h"
	#include "LevelWarManager.h"
	#include "SiegeManager.h"

	#include "Sweeper.h"

	#include "ctf/FlagManager.h"

	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCSay.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCDeleteInventoryItem.h"

	#include <stdio.h>

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRelicToObjectHandler::execute (CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

//	cout << "CGRelicToObject start" << endl;
//	cout << "¹ÞÀº ÆÐÅ¶(¾ÆÀÌÅÛ ¿ÀºêÁ§Æ®)" << pPacket->getItemObjectID()
//		 << "¹ÞÀº ÆÐÅ¶(¼º¹° º¸°üÇÔ)"  << pPacket->getObjectID() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ·¼¸¯À» ÇØ´ç ¼º¹°º¸°üÇÔ¿¡ ³ÖÀ»¶§.. 
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();

	// ¼º¹° º¸°ü´ë¿¡ ÀÌ¹Ì µÑ ´Ù ÀÖ´Â °æ¿ì
	// ¼º¹° º¸°ü´ë¿¡ Slayer¼º¹°ÀÌ ÀÖ°í pItemÀÌ Slayer¼º¹°ÀÎ °æ¿ì
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
	if ( pPlayerCreature == NULL )
	{
		throw DisconnectException("CGRelicToObject : ÀÌ»óÇØ¿ä");
		return;
	}

	// ÇöÀç µé°í ÀÖ´Â ¾ÆÀÌÅÛ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	if ( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 31 )
	{
		static hash_map<string, string> scripts;
		if ( scripts.empty() )
		{
			cout << "½ºÅ©¸³Æ® ÃÊ±âÈ­" << endl;
			scripts["Ô¼º²Ñ·"] = "Ð»Ð»Äã,ÎÒÓÀÔ¶¶¼²»»áÍü¼ÇÄã¶ÔÎÒµÄ¶÷»Ý.";
			scripts["±ÈÁ¦"] = "¸Ï½ôÈ¥¾È¾ÈÆäËûÈË°É,°ÝÍÐÄãÁË.";
			scripts["Àí²éµÂ"] = "ÎØÎØ...ÖÕÓÚµÃ¾ÈÁË.";
			scripts["°£Ë¹¿¨Ì¹"] = "ÎÒÏÈ×ßÒ»²½ÁË.";
			scripts["Â·Ò×Ë¹"] = "ÎØÎØ...ÊµÔÚÊÇÌ«Í´¿àÁË.Ð»Ð»Äã!";
			scripts["Õ²Ä·Ë¹"] = "ÖÕÓÚµÃ¾ÈÁË.µ½´å×¯ÔÙÁÄ.";
			scripts["¿­Éª"] = "¸Ï½ôÈ¥¾È¾ÈÆäËûÈË°É.";
			scripts["ÅÂÒ×"] = "ÎØÎØ... »ëÉíÃ»¾¢°¡!";
			scripts["ÄáÄÇÂ¬Ë¹"] = "ºô~µÃ¾ÈÁË.";
			scripts["Â¬"] = "ºô~µÃ¾ÈÁË.";
			scripts["ÅåË¹ÌØ"] = "Ð»Ð»Äã!ÎÒÏÈ×ßÒ»²½ÁË.";
			scripts["Ð¤"] = "¸Ï½ôÈ¥¾È¾ÈÆäËûÈË°É.°ÝÍÐÄãÁË.";
			scripts["°¢Â¬Ë¹"] = "ÎØÎØ...Ì«²ÐÈÌÁË.ÖÕÓÚµÃ¾ÈÁË!";
			scripts["Õ²ç÷"] = "ÎÒÏÈ×ßÒ»²½ÁË.";
			scripts["¸ñÅ¬"] = "ÎÒÏàÐÅÄãÒ»¶¨»áÀ´¾ÈÎÒÃÇµÄ.";
		}

		Zone* pZone = pPlayerCreature->getZone();
		Monster* pMonster = dynamic_cast<Monster*>(pZone->getCreature(pPacket->getObjectID()));
		if ( pMonster == NULL )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			cout << "¸ó½ºÅÍ°¡ ¾ø½À´Ï´Ù." << endl;

			return;
		}

		if (
			( pPlayerCreature->isSlayer() && pMonster->getMonsterType() != 793 ) ||
			( pPlayerCreature->isVampire() && pMonster->getMonsterType() != 794 ) ||
			( pPlayerCreature->isOusters() && pMonster->getMonsterType() != 795 ) ||
			scripts.find(pMonster->getName()) == scripts.end()
		   )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);

			cout << "ÀÌ»óÇÑ ¸ó½ºÅÍÀÌ°Å³ª ¸ó½ºÅÍ ÀÌ¸§ÀÌ Æ²¸³´Ï´Ù. : " << (int)pMonster->getMonsterType() << "," << pMonster->getName() << endl;

			return;
		}

		GCSay gcSay;
		gcSay.setObjectID( pMonster->getObjectID() );
		gcSay.setColor(255);
		gcSay.setMessage( scripts[pMonster->getName()] );

		pZone->broadcastPacket( pMonster->getX(), pMonster->getY(), &gcSay );
		EffectKillTimer* pEffect = new EffectKillTimer( pMonster, true );
		pMonster->setFlag( pEffect->getEffectClass() );
		pEffect->setDeadline(50);
		pMonster->addEffect( pEffect );

		pPlayerCreature->deleteItemFromExtraInventorySlot();
		
		GCDeleteInventoryItem gcDI;
		gcDI.setObjectID( pPacket->getItemObjectID() );
		pGamePlayer->sendPacket( &gcDI );

		pItem->destroy();
		SAFE_DELETE( pItem );

		return;
	}

	if (pItem==NULL
		|| (!isRelicItem( pItem )&&!pItem->isFlagItem() && !pItem->isSweeper()))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		return;
	}

	if (pItem->getItemClass()==Item::ITEM_CLASS_RELIC)
	{
		executeRelic( pPacket, pPlayer );
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		executeBloodBible( pPacket, pPlayer );
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		executeCastleSymbol( pPacket, pPlayer );
	}
	else if ( pItem->isFlagItem() )
	{
		//cout << "±ê¹ß ²Å±â!" << endl;
		executeFlag( pPacket, pPlayer );
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_SWEEPER)
	{
		executeSweeper( pPacket, pPlayer );
	}
	else
	{
		throw DisconnectException("¾û¶×ÇÑ°Å µé°í RelicToObjectº¸³»Áö¸¶");
	}

#endif

	__END_DEBUG_EX __END_CATCH

}

void CGRelicToObjectHandler::executeRelic(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	// ·¼¸¯À» ÇØ´ç ¼º¹°º¸°üÇÔ¿¡ ³ÖÀ»¶§.. 
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();

	// ¼º¹° º¸°ü´ë¿¡ ÀÌ¹Ì µÑ ´Ù ÀÖ´Â °æ¿ì
	// ¼º¹° º¸°ü´ë¿¡ Slayer¼º¹°ÀÌ ÀÖ°í pItemÀÌ Slayer¼º¹°ÀÎ °æ¿ì
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ÇöÀç µé°í ÀÖ´Â ¾ÆÀÌÅÛ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);


	bool        Success   = false;

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	// ±×·± itemÀÌ ¾ø°Å³ª
	// ½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// Monster½ÃÃ¼°¡ ¾Æ´Ï¸é ¼º¹°º¸°ü´ë°¡ ¾Æ´Ï´Ù.
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not RelicTable" << endl;
		return;
	}

	// ¼º¹° º¸°ü´ë
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Å¸ÀÏ ¾È¿¡ ÀÖ¾î¾ß µÈ´Ù.
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile" << endl;
		return;
	}

	// Relic ¼ÒÀ¯ ¿©ºÎ¸¦ Ã¼Å©ÇÑ´Ù.
	bool bPlayerHasSlayerRelic 	= pCreature->isFlag(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);
	bool bPlayerHasVampireRelic = pCreature->isFlag(Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC);
	bool bTableHasSlayerRelic 	= pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
	bool bTableHasVampireRelic 	= pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
	bool bSlayerRelicTable 		= pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);
	bool bVampireRelicTable 	= pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);

	// ÀÌ¹Ì µÎ ¼º¹°ÀÌ ´Ù ÀÖ°Å³ª
	// Player°¡ µÎ ¼º¹°ÀÌ ´Ù ¾ø°Å³ª
	// itemÀÌ ¾ø´Â °æ¿ì?
	// ¼º¹°ÀÌ ¾Æ´Ï°Å³ª
	if (bTableHasSlayerRelic && bTableHasVampireRelic
		|| !bPlayerHasSlayerRelic && !bPlayerHasVampireRelic
		|| pItem==NULL
		|| pItem->getItemClass() != Item::ITEM_CLASS_RELIC)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: Cannot add" << endl;
		return;
	}

	ItemType_t 		relicIndex 			= pItem->getItemType();

	// RelicInfo¸¦ ¾ò´Â´Ù.
	const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(relicIndex));

	if ( pRelicInfo == NULL )
	{
		filelog( "relic.log", "no such relic index(%d)", relicIndex );

		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		return;
	}

	bool bSlayer = pCreature->isSlayer();
	bool bVampire = pCreature->isVampire();

	// itemObjectID°¡ Àß¸øµÇ¾ú°Å³ª
	// µé°í ÀÖ´Â ¾ÆÀÌÅÛÀÌ ¾ø°Å³ª
	// ³²ÀÇ º¸°ü´ëÀÌ°Å³ª
	// ÀÌ¹Ì °°Àº Á¾Á·ÀÇ ¼º¹°ÀÌ ÀÖ´Ù¸é ³ÖÀ» ¼ö ¾ø´Ù.
	if (pItem->getObjectID() != pPacket->getItemObjectID()
		|| bSlayer && bVampireRelicTable
		|| bVampire && bSlayerRelicTable
		|| bTableHasSlayerRelic && pRelicInfo->relicType==RELIC_TYPE_SLAYER
		|| bTableHasVampireRelic && pRelicInfo->relicType==RELIC_TYPE_VAMPIRE)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: Cannot Add2" << endl;
		return;
	}

	// ½½·¹ÀÌ¾îÀÎ °æ¿ì´Â ¿ÀÅä¹ÙÀÌ, ½º³ªÀÌÇÎ»óÅÂ ÀÌ¸é ¾ÈµÇ°í
	// ¹ìÆÄÀÌ¾îÀÎ °æ¿ì´Â º¯½Å»óÅÂ, Åõ¸í»óÅÂÀÌ¸é ¾ÈµÈ´Ù.
	if (bSlayer)
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		// ¿ÀÅä¹ÙÀÌ¸¦ Å¸°í ÀÖÀ¸¸é ºÒ°¡´ÉÇÏ´Ù.
		if (!pSlayer->hasRideMotorcycle()
			&& !pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
		{
			// Effect¸¦ ºÙÀÎ´Ù.
			Success = true;
		}
	}
	else if (bVampire)
	{
		if (!pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_FADE_OUT))
		{
			Success = true;
		}
	}

	// ¼º¹°º¸°ü´ë¿¡ ¼º¹°À» ³ÖÀ» ¼ö ÀÖ´Â °æ¿ì
	if (Success)
	{
		// Mouse¿¡¼­ ¾ÆÀÌÅÛÀ» Áö¿ì°í
		pPlayerCreature->deleteItemFromExtraInventorySlot();

		// ¼º¹°À» ¼º¹° º¸°ü´ë¿¡ Ãß°¡ÇÑ´Ù.
		pCorpse->addTreasure( pItem );

/*		StringStream msg;
		msg << pPlayerCreature->getName() << " ´ÔÀÌ ¼º¹° º¸°ü´ë¿¡ "
			<< "¼º¹°(" << pRelicInfo->getName() << ")À» ³Ö¾ú½À´Ï´Ù."; */

        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_PUT_RELIC_TO_RELIC_TABLE ),
                        pPlayerCreature->getName().c_str(),
                        pRelicInfo->getName().c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg );
		g_pZoneGroupManager->broadcast( &gcSystemMessage );

		Effect::EffectClass effectClass;
		Effect::EffectClass effectClassTable;

		// Creature¿¡¼­ Effect¸¦ Á¦°ÅÇÏ°í
		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			effectClass 		= Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
			effectClassTable 	= Effect::EFFECT_CLASS_SLAYER_RELIC;
		}
		else
		{
			effectClass 		= Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
			effectClassTable 	= Effect::EFFECT_CLASS_VAMPIRE_RELIC;
		}

		Effect* pEffect = pCreature->findEffect( effectClass );
		Assert(pEffect!=NULL);

		// CreatureÀÇ flag¸¦ ²ô°í
		// GCRemoveEffect¸¦ º¸³»°Ô µÈ´Ù.
		pEffect->unaffect();	
		pCreature->deleteEffect( effectClass );

		// ¼º¹° º¸°ü´ë°¡ RelicÀ» °¡Á³´Ù´Â Effect¸¦ ºÙ¿©ÁØ´Ù.
		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			EffectSlayerRelic* pEffect = new EffectSlayerRelic(pCorpse);

			pCorpse->getEffectManager().addEffect( pEffect );
			pCorpse->setFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
			pEffect->affect(pCorpse);
		}
		else
		{
			EffectVampireRelic* pEffect = new EffectVampireRelic(pCorpse);

			pCorpse->getEffectManager().addEffect( pEffect );
			pCorpse->setFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
			pEffect->affect(pCorpse);
		}

		// ¼º¹°º¸°ü´ë¿¡ Effect¸¦ ºÙÀÎ°É client¿¡ ¾Ë¸°´Ù.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pCorpse->getObjectID());
		gcAddEffect.setEffectID(effectClassTable);
		gcAddEffect.setDuration(65000);
		pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);

		// ¼º¹° ³õ¾Ò´Ù°í º¸³»ÁØ´Ù.
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID( pItem->getObjectID() );
		pPlayer->sendPacket(&gcDeleteObject);

		// RelicTable
		EffectRelicTable* pTableEffect = NULL;
		if (bSlayer)
		{
			// ¼º¹°ÀÇ ¼ÒÀ¯¸¦ ¼³Á¤ÇÑ´Ù.
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);

			// ÀÌÆåÆ®¸¦ Ã£´Â´Ù.
			Effect* pEffect = pCorpse->getEffectManager().findEffect( Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE );
			Assert(pEffect!=NULL);

			pTableEffect = dynamic_cast<EffectSlayerRelicTable*>(pEffect);
			Assert(pTableEffect!=NULL);
		}
		else
		{
			// ¼º¹°ÀÇ ¼ÒÀ¯¸¦ ¼³Á¤ÇÑ´Ù.
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);

			// ÀÌÆåÆ®¸¦ Ã£´Â´Ù.
			Effect* pEffect = pCorpse->getEffectManager().findEffect( Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE );
			Assert(pEffect!=NULL);

			pTableEffect = dynamic_cast<EffectVampireRelicTable*>(pEffect);
			Assert(pTableEffect!=NULL);
		}

		// ¼º¹°ÀÌ ÇÏ³ª µé¾î°¡¸é
		// ÇÑ µ¿¾È(10ÃÊ)Àº ¼º¹°À» »©³¾ ¼ö ¾ø´Ù.
		Timeval lockTime;
		getCurrentTime(lockTime);
		lockTime.tv_sec += 10;
		pTableEffect->setLockTime( lockTime );


		// µÎ ¼º¹°À» ¸ðµÎ °®°Ô µÇ´Â °æ¿ì
		if (bTableHasSlayerRelic && pRelicInfo->relicType==RELIC_TYPE_VAMPIRE
			|| bTableHasVampireRelic && pRelicInfo->relicType==RELIC_TYPE_SLAYER)

		{
			// ¼º¹° º¸°ü´ë°¡ ¾ÈÀüÇÑ ½Ã°£ ¼³Á¤
			Timeval safeTime;
			getCurrentTime( safeTime );
			safeTime.tv_sec += g_pVariableManager->getCombatBonusTime()*60;

			// ½Â¸® message ¸¦ º¸³»ÁØ´Ù.
			GCSystemMessage gcSystemMessage;

			pTableEffect->setSafeTime( safeTime );

			if (bSlayer)
			{
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_SLAYER_WIN ) );
				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
			}
			else
			{
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_VAMPIRE_WIN ) );
				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
			}

			// ÀüÀïÀÌ Á¾·áµÇ¾ú´Ù.
			g_pCombatInfoManager->setCombat( false );

			// ÀüÃ¼ »ç¿ëÀÚ¿¡°Ô message¸¦ º¸³½´Ù.
			g_pZoneGroupManager->broadcast( &gcSystemMessage );

			g_pCombatInfoManager->computeModify();
		}
	}
	else
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
	}

#endif	// __GAME_SERVER__
		
	__END_CATCH
}

void CGRelicToObjectHandler::executeBloodBible(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);


	// ¼º¹° º¸°ü´ë¿¡ ÀÌ¹Ì µÑ ´Ù ÀÖ´Â °æ¿ì
	// ¼º¹° º¸°ü´ë¿¡ Slayer¼º¹°ÀÌ ÀÖ°í pItemÀÌ Slayer¼º¹°ÀÎ °æ¿ì
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ÇöÀç µé°í ÀÖ´Â ¾ÆÀÌÅÛ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	// ±×·± itemÀÌ ¾ø°Å³ª
	// ½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// Monster½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// ShrineGuardµµ ShrineHolyµµ ¾Æ´Ï¸é.. ¼º´ÜÀÌ ¾Æ´ÏÁö.
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pTableItem->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD) &&
			!pTableItem->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ¼º´Ü
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Å¸ÀÏ ¾È¿¡ ÀÖÁö ¾Ê°Å³ª
	// shrineÀ¸·Î ¼³Á¤ÀÌ ¾ÈµÇ¾î ÀÖÀ¸¸é
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (g_pShrineInfoManager->putBloodBible( pPlayerCreature, pItem, pCorpse ))
	{
		// putBloodBible ¾È¿¡¼­ Ã³¸®ÇÑ´Ù.
	}	

#endif

	__END_CATCH
}

void CGRelicToObjectHandler::executeCastleSymbol(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	// ¼º¹° º¸°ü´ë¿¡ ÀÌ¹Ì µÑ ´Ù ÀÖ´Â °æ¿ì
	// ¼º¹° º¸°ü´ë¿¡ Slayer¼º¹°ÀÌ ÀÖ°í pItemÀÌ Slayer¼º¹°ÀÎ °æ¿ì
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ÇöÀç µé°í ÀÖ´Â ¾ÆÀÌÅÛ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();


	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

//	cout << "executeCastleSymbol" << endl;

	// ±×·± itemÀÌ ¾ø°Å³ª
	// ½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// Monster½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// ShrineGuardµµ ShrineHolyµµ ¾Æ´Ï¸é.. ¼º´ÜÀÌ ¾Æ´ÏÁö.
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pTableItem->isFlag(Effect::EFFECT_CLASS_CASTLE_SHRINE_GUARD) &&
			!pTableItem->isFlag(Effect::EFFECT_CLASS_CASTLE_SHRINE_HOLY))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ¼º´Ü
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Å¸ÀÏ ¾È¿¡ ÀÖÁö ¾Ê°Å³ª
	// shrineÀ¸·Î ¼³Á¤ÀÌ ¾ÈµÇ¾î ÀÖÀ¸¸é
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

#ifndef __OLD_GUILD_WAR__
//	if ( pZone->getZoneID() == 1500 )
//	{
		cout << "siegeManager Call" << endl;
		SiegeManager::Instance().putItem( pPlayerCreature, pCorpse, pItem );
		return;
//	}
#else
	if (g_pCastleShrineInfoManager->putCastleSymbol( pPlayerCreature, pItem, pCorpse ))
	{
		// putCastleSymbol ¾È¿¡¼­ Ã³¸®ÇÑ´Ù.
	}
#endif

#endif

	__END_CATCH
}
	
void CGRelicToObjectHandler::executeFlag(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	if ( !g_pFlagManager->hasFlagWar() ) return;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	// ¼º¹° º¸°ü´ë¿¡ ÀÌ¹Ì µÑ ´Ù ÀÖ´Â °æ¿ì
	// ¼º¹° º¸°ü´ë¿¡ Slayer¼º¹°ÀÌ ÀÖ°í pItemÀÌ Slayer¼º¹°ÀÎ °æ¿ì
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ÇöÀç µé°í ÀÖ´Â ¾ÆÀÌÅÛ == Flag ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	// ±×·± itemÀÌ ¾ø°Å³ª
	// ½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// Monster½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// ±ê´ë°¡ ¾Æ´Ï¸é
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !g_pFlagManager->isFlagPole( dynamic_cast<MonsterCorpse*>(pTableItem) ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ¼º´Ü
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Å¸ÀÏ ¾È¿¡ ÀÖÁö ¾Ê°Å³ª
	// shrineÀ¸·Î ¼³Á¤ÀÌ ¾ÈµÇ¾î ÀÖÀ¸¸é
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (g_pFlagManager->putFlag( pPlayerCreature, pItem, pCorpse ))
	{
		// putCastleSymbol ¾È¿¡¼­ Ã³¸®ÇÑ´Ù.
		//cout << "±ê¹ß ²È¾ÒÁö·Õ~" << endl;
	}	
	else
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

#endif

	__END_CATCH
}

void CGRelicToObjectHandler::executeSweeper(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	LevelWarManager* pLevelWarManager = pZone->getLevelWarManager();
	Assert(pLevelWarManager!=NULL);

	if ( !pLevelWarManager->hasWar() ) return;

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pItem->getItemType()));

	// ±×·± itemÀÌ ¾ø°Å³ª
	// ½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// Monster½ÃÃ¼°¡ ¾Æ´Ï°Å³ª
	// ±ê´ë°¡ ¾Æ´Ï¸é
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pLevelWarManager->isSafe( dynamic_cast<MonsterCorpse*>(pTableItem) ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ¼º´Ü
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Å¸ÀÏ ¾È¿¡ ÀÖÁö ¾Ê°Å³ª
	// shrineÀ¸·Î ¼³Á¤ÀÌ ¾ÈµÇ¾î ÀÖÀ¸¸é
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (pLevelWarManager->putSweeper( pPlayerCreature, pItem, pCorpse ))
	{
		// Sweeper ¸¦ ²È¾ÒÀ¸¸é °¡Áö°í ÀÖ´ø °Ç Áö¿öÁØ´Ù
		pPlayerCreature->deleteItemFromExtraInventorySlot();
		GCDeleteInventoryItem gcDeleteInventoryItem;
		gcDeleteInventoryItem.setObjectID( pPacket->getItemObjectID() );
		pPlayerCreature->getPlayer()->sendPacket( &gcDeleteInventoryItem );
		Effect* pEffect = pPlayerCreature->findEffect( Effect::EFFECT_CLASS_HAS_SWEEPER );

		if (pEffect != NULL)
		{
			pEffect->setDeadline(0);
		}

		// ²È¾ÒÀ» ¶§ Á¸¿¡ ½Ã½ºÅÛ ¸Þ¼¼Áö¸¦ »Ñ·ÁÁØ´Ù
		char race[15];
		if ( pCreature->isSlayer() )
		{
			sprintf( race, g_pStringPool->c_str( STRID_SLAYER ) );
		}
		else if ( pCreature->isVampire() )
		{
			sprintf( race, g_pStringPool->c_str( STRID_VAMPIRE ) );
		}
		else if ( pCreature->isOusters() )
		{
			sprintf( race, g_pStringPool->c_str( STRID_OUSTERS ) );
		}
		else
		{
			Assert(false);
		}

		char msg[100];

		sprintf( msg , g_pStringPool->c_str( STRID_PUT_SWEEPER ) ,
							pCreature->getName().c_str(),
							race,
							pSweeperInfo->getName().c_str()
							);
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg );
		pZone->broadcastPacket( &gcSystemMessage );
	}	
	else
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

#endif

	__END_CATCH
}
