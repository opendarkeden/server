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

	#include "GCCannotAdd.h"
	#include "GCSay.h"
	#include "GCAddEffect.h"
	#include "GCSystemMessage.h"
	#include "GCDeleteObject.h"
	#include "GCDeleteInventoryItem.h"

	#include <stdio.h>

    #include <map>
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRelicToObjectHandler::execute (CGRelicToObject* pPacket , Player* pPlayer)
	 throw(Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

//	cout << "CGRelicToObject start" << endl;
//	cout << "받은 패킷(아이템 오브젝트)" << pPacket->getItemObjectID()
//		 << "받은 패킷(성물 보관함)"  << pPacket->getObjectID() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 렐릭을 해당 성물보관함에 넣을때.. 
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();

	// 성물 보관대에 이미 둘 다 있는 경우
	// 성물 보관대에 Slayer성물이 있고 pItem이 Slayer성물인 경우
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
	if (pPlayerCreature == NULL )
	{
		throw DisconnectException("CGRelicToObject : 이상해요");
		return;
	}

	// 현재 들고 있는 아이템 == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 31 )
	{
		static map<string, string> scripts;
		if (scripts.empty() )
		{
			//cout << "스크립트 초기화" << endl;
			scripts["존슨"] = "고맙소. 이 은혜 잊지않겠소";
			scripts["빌리"] = "얼른 다른 동료들도 구해주세요. 부탁입니다.";
			scripts["리"] = "우웃…. 겨우 살았군.";
			scripts["에즈카탄"] = "난 먼저 가있도록 할게요.";
			scripts["루이스"] = "흐흑. 너무 힘들었소. 너무 고맙소.";
			scripts["젠지"] = "이제 살았군. 마을에서 봅시다";
			scripts["케스이"] = "얼른 다른 동지들도….";
			scripts["파이"] = "우웃…. 몸에 힘이 남아있지 않아.";
			scripts["니나이루"] = "난 먼저 가있도록 할게요.";
			scripts["료"] = "휴… 살았다.";
			scripts["페이트"] = "고맙습니다. 먼저가서 기다리겠어요.";
			scripts["솔"] = "얼른 다른 동료들도 구해주세요. 부탁입니다.";
			scripts["이루이"] = "우웃…. 지독했어요. 겨우 살았군요.";
			scripts["젼키"] = "난 먼저 가있도록 할게요.";
			scripts["그누"] = "당신이 올 줄 알았습니다.";
		}

		Zone* pZone = pPlayerCreature->getZone();
		Monster* pMonster = dynamic_cast<Monster*>(pZone->getCreature(pPacket->getObjectID()));
		if (pMonster == NULL )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			//cout << "몬스터가 없습니다." << endl;

			return;
		}

		if (
			(pPlayerCreature->isSlayer() && pMonster->getMonsterType() != 793 ) ||
			(pPlayerCreature->isVampire() && pMonster->getMonsterType() != 794 ) ||
			(pPlayerCreature->isOusters() && pMonster->getMonsterType() != 795 ) ||
			scripts.find(pMonster->getName()) == scripts.end()
		   )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);

			//cout << "이상한 몬스터이거나 몬스터 이름이 틀립니다. : " << (int)pMonster->getMonsterType() << "," << pMonster->getName() << endl;

			return;
		}

		GCSay gcSay;
		gcSay.setObjectID(pMonster->getObjectID());
		gcSay.setColor(255);
		gcSay.setMessage(scripts[pMonster->getName()]);

		pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &gcSay);
		EffectKillTimer* pEffect = new EffectKillTimer(pMonster, true);
		pMonster->setFlag(pEffect->getEffectClass());
		pEffect->setDeadline(50);
		pMonster->addEffect(pEffect);

		pPlayerCreature->deleteItemFromExtraInventorySlot();
		
		GCDeleteInventoryItem gcDI;
		gcDI.setObjectID(pPacket->getItemObjectID());
		pGamePlayer->sendPacket(&gcDI);

		pItem->destroy();
		SAFE_DELETE(pItem);

		return;
	}

	if (pItem==NULL
		|| (!isRelicItem(pItem )&&!pItem->isFlagItem() && !pItem->isSweeper()))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		return;
	}

	if (pItem->getItemClass()==Item::ITEM_CLASS_RELIC)
	{
		executeRelic(pPacket, pPlayer);
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		executeBloodBible(pPacket, pPlayer);
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		executeCastleSymbol(pPacket, pPlayer);
	}
	else if (pItem->isFlagItem() )
	{
		//cout << "깃발 꼽기!" << endl;
		executeFlag(pPacket, pPlayer);
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_SWEEPER)
	{
		executeSweeper(pPacket, pPlayer);
	}
	else
	{
		throw DisconnectException("엉뚱한거 들고 RelicToObject보내지마");
	}

#endif

	__END_DEBUG_EX __END_CATCH

}

void CGRelicToObjectHandler::executeRelic(CGRelicToObject* pPacket , Player* pPlayer)
	 throw(Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	// 렐릭을 해당 성물보관함에 넣을때.. 
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();

	// 성물 보관대에 이미 둘 다 있는 경우
	// 성물 보관대에 Slayer성물이 있고 pItem이 Slayer성물인 경우
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// 현재 들고 있는 아이템 == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);


	bool        Success   = false;

	Item* pTableItem = pZone->getItem(pPacket->getObjectID());

	// 그런 item이 없거나
	// 시체가 아니거나
	// Monster시체가 아니면 성물보관대가 아니다.
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

	// 성물 보관대
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2타일 안에 있어야 된다.
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile" << endl;
		return;
	}

	// Relic 소유 여부를 체크한다.
	bool bPlayerHasSlayerRelic 	= pCreature->isFlag(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);
	bool bPlayerHasVampireRelic = pCreature->isFlag(Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC);
	bool bTableHasSlayerRelic 	= pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
	bool bTableHasVampireRelic 	= pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
	bool bSlayerRelicTable 		= pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);
	bool bVampireRelicTable 	= pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);

	// 이미 두 성물이 다 있거나
	// Player가 두 성물이 다 없거나
	// item이 없는 경우?
	// 성물이 아니거나
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

	// RelicInfo를 얻는다.
	const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(relicIndex));

	if (pRelicInfo == NULL )
	{
		filelog("relic.log", "no such relic index(%d)", relicIndex);

		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		return;
	}

	bool bSlayer = pCreature->isSlayer();
	bool bVampire = pCreature->isVampire();

	// itemObjectID가 잘못되었거나
	// 들고 있는 아이템이 없거나
	// 남의 보관대이거나
	// 이미 같은 종족의 성물이 있다면 넣을 수 없다.
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

	// 슬레이어인 경우는 오토바이, 스나이핑상태 이면 안되고
	// 뱀파이어인 경우는 변신상태, 투명상태이면 안된다.
	if (bSlayer)
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		// 오토바이를 타고 있으면 불가능하다.
		if (!pSlayer->hasRideMotorcycle()
			&& !pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
		{
			// Effect를 붙인다.
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

	// 성물보관대에 성물을 넣을 수 있는 경우
	if (Success)
	{
		// Mouse에서 아이템을 지우고
		pPlayerCreature->deleteItemFromExtraInventorySlot();

		// 성물을 성물 보관대에 추가한다.
		pCorpse->addTreasure(pItem);

/*		StringStream msg;
		msg << pPlayerCreature->getName() << " 님이 성물 보관대에 "
			<< "성물(" << pRelicInfo->getName() << ")을 넣었습니다."; */

        char msg[100];
        sprintf(msg, g_pStringPool->c_str(STRID_PUT_RELIC_TO_RELIC_TABLE ),
                        pPlayerCreature->getName().c_str(),
                        pRelicInfo->getName().c_str());

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg);
		g_pZoneGroupManager->broadcast(&gcSystemMessage);

		Effect::EffectClass effectClass;
		Effect::EffectClass effectClassTable;

		// Creature에서 Effect를 제거하고
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

		Effect* pEffect = pCreature->findEffect(effectClass);
		Assert(pEffect!=NULL);

		// Creature의 flag를 끄고
		// GCRemoveEffect를 보내게 된다.
		pEffect->unaffect();	
		pCreature->deleteEffect(effectClass);

		// 성물 보관대가 Relic을 가졌다는 Effect를 붙여준다.
		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			EffectSlayerRelic* pEffect = new EffectSlayerRelic(pCorpse);

			pCorpse->getEffectManager().addEffect(pEffect);
			pCorpse->setFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
			pEffect->affect(pCorpse);
		}
		else
		{
			EffectVampireRelic* pEffect = new EffectVampireRelic(pCorpse);

			pCorpse->getEffectManager().addEffect(pEffect);
			pCorpse->setFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
			pEffect->affect(pCorpse);
		}

		// 성물보관대에 Effect를 붙인걸 client에 알린다.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pCorpse->getObjectID());
		gcAddEffect.setEffectID(effectClassTable);
		gcAddEffect.setDuration(65000);
		pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);

		// 성물 놓았다고 보내준다.
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(pItem->getObjectID());
		pPlayer->sendPacket(&gcDeleteObject);

		// RelicTable
		EffectRelicTable* pTableEffect = NULL;
		if (bSlayer)
		{
			// 성물의 소유를 설정한다.
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);

			// 이펙트를 찾는다.
			Effect* pEffect = pCorpse->getEffectManager().findEffect(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);
			Assert(pEffect!=NULL);

			pTableEffect = dynamic_cast<EffectSlayerRelicTable*>(pEffect);
			Assert(pTableEffect!=NULL);
		}
		else
		{
			// 성물의 소유를 설정한다.
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);

			// 이펙트를 찾는다.
			Effect* pEffect = pCorpse->getEffectManager().findEffect(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);
			Assert(pEffect!=NULL);

			pTableEffect = dynamic_cast<EffectVampireRelicTable*>(pEffect);
			Assert(pTableEffect!=NULL);
		}

		// 성물이 하나 들어가면
		// 한 동안(10초)은 성물을 빼낼 수 없다.
		Timeval lockTime;
		getCurrentTime(lockTime);
		lockTime.tv_sec += 10;
		pTableEffect->setLockTime(lockTime);


		// 두 성물을 모두 갖게 되는 경우
		if (bTableHasSlayerRelic && pRelicInfo->relicType==RELIC_TYPE_VAMPIRE
			|| bTableHasVampireRelic && pRelicInfo->relicType==RELIC_TYPE_SLAYER)

		{
			// 성물 보관대가 안전한 시간 설정
			Timeval safeTime;
			getCurrentTime(safeTime);
			safeTime.tv_sec += g_pVariableManager->getCombatBonusTime()*60;

			// 승리 message 를 보내준다.
			GCSystemMessage gcSystemMessage;

			pTableEffect->setSafeTime(safeTime);

			if (bSlayer)
			{
				gcSystemMessage.setMessage(g_pStringPool->getString(STRID_COMBAT_SLAYER_WIN ));
				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
			}
			else
			{
				gcSystemMessage.setMessage(g_pStringPool->getString(STRID_COMBAT_VAMPIRE_WIN ));
				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
			}

			// 전쟁이 종료되었다.
			g_pCombatInfoManager->setCombat(false);

			// 전체 사용자에게 message를 보낸다.
			g_pZoneGroupManager->broadcast(&gcSystemMessage);

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
	 throw(Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);


	// 성물 보관대에 이미 둘 다 있는 경우
	// 성물 보관대에 Slayer성물이 있고 pItem이 Slayer성물인 경우
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// 현재 들고 있는 아이템 == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem(pPacket->getObjectID());

	// 그런 item이 없거나
	// 시체가 아니거나
	// Monster시체가 아니거나
	// ShrineGuard도 ShrineHoly도 아니면.. 성단이 아니지.
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

	// 성단
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2타일 안에 있지 않거나
	// shrine으로 설정이 안되어 있으면
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (g_pShrineInfoManager->putBloodBible(pPlayerCreature, pItem, pCorpse ))
	{
		// putBloodBible 안에서 처리한다.
	}	

#endif

	__END_CATCH
}

void CGRelicToObjectHandler::executeCastleSymbol(CGRelicToObject* pPacket , Player* pPlayer)
	 throw(Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	// 성물 보관대에 이미 둘 다 있는 경우
	// 성물 보관대에 Slayer성물이 있고 pItem이 Slayer성물인 경우
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// 현재 들고 있는 아이템 == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();


	Item* pTableItem = pZone->getItem(pPacket->getObjectID());

//	cout << "executeCastleSymbol" << endl;

	// 그런 item이 없거나
	// 시체가 아니거나
	// Monster시체가 아니거나
	// ShrineGuard도 ShrineHoly도 아니면.. 성단이 아니지.
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

	// 성단
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2타일 안에 있지 않거나
	// shrine으로 설정이 안되어 있으면
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
//	if (pZone->getZoneID() == 1500 )
//	{
		cout << "siegeManager Call" << endl;
		SiegeManager::Instance().putItem(pPlayerCreature, pCorpse, pItem);
		return;
//	}
#else
	if (g_pCastleShrineInfoManager->putCastleSymbol(pPlayerCreature, pItem, pCorpse ))
	{
		// putCastleSymbol 안에서 처리한다.
	}
#endif

#endif

	__END_CATCH
}
	
void CGRelicToObjectHandler::executeFlag(CGRelicToObject* pPacket , Player* pPlayer)
	 throw(Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	if (!g_pFlagManager->hasFlagWar() ) return;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	// 성물 보관대에 이미 둘 다 있는 경우
	// 성물 보관대에 Slayer성물이 있고 pItem이 Slayer성물인 경우
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// 현재 들고 있는 아이템 == Flag ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem(pPacket->getObjectID());

	// 그런 item이 없거나
	// 시체가 아니거나
	// Monster시체가 아니거나
	// 깃대가 아니면
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !g_pFlagManager->isFlagPole(dynamic_cast<MonsterCorpse*>(pTableItem) ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// 성단
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2타일 안에 있지 않거나
	// shrine으로 설정이 안되어 있으면
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (g_pFlagManager->putFlag(pPlayerCreature, pItem, pCorpse ))
	{
		// putCastleSymbol 안에서 처리한다.
		//cout << "깃발 꽂았지롱~" << endl;
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
	 throw(Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	LevelWarManager* pLevelWarManager = pZone->getLevelWarManager();
	Assert(pLevelWarManager!=NULL);

	if (!pLevelWarManager->hasWar() ) return;

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem(pPacket->getObjectID());

	const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pItem->getItemType()));

	// 그런 item이 없거나
	// 시체가 아니거나
	// Monster시체가 아니거나
	// 깃대가 아니면
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pLevelWarManager->isSafe(dynamic_cast<MonsterCorpse*>(pTableItem) ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// 성단
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2타일 안에 있지 않거나
	// shrine으로 설정이 안되어 있으면
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (pLevelWarManager->putSweeper(pPlayerCreature, pItem, pCorpse ))
	{
		// Sweeper 를 꽂았으면 가지고 있던 건 지워준다
		pPlayerCreature->deleteItemFromExtraInventorySlot();
		GCDeleteInventoryItem gcDeleteInventoryItem;
		gcDeleteInventoryItem.setObjectID(pPacket->getItemObjectID());
		pPlayerCreature->getPlayer()->sendPacket(&gcDeleteInventoryItem);
		Effect* pEffect = pPlayerCreature->findEffect(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (pEffect != NULL)
		{
			pEffect->setDeadline(0);
		}

		// 꽂았을 때 존에 시스템 메세지를 뿌려준다
		char race[15];
		if (pCreature->isSlayer() )
		{
			sprintf(race, g_pStringPool->c_str(STRID_SLAYER ));
		}
		else if (pCreature->isVampire() )
		{
			sprintf(race, g_pStringPool->c_str(STRID_VAMPIRE ));
		}
		else if (pCreature->isOusters() )
		{
			sprintf(race, g_pStringPool->c_str(STRID_OUSTERS ));
		}
		else
		{
			Assert(false);
		}

		char msg[100];

		sprintf(msg , g_pStringPool->c_str(STRID_PUT_SWEEPER ) ,
							pCreature->getName().c_str(),
							race,
							pSweeperInfo->getName().c_str()
							);
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg);
		pZone->broadcastPacket(&gcSystemMessage);
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
