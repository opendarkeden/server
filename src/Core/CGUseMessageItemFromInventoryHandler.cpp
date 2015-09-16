//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseMessageItemFromInventoryHandler.cpp
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseMessageItemFromInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "MonsterCorpse.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemUtil.h"
	#include "CreatureUtil.h"
	#include "ZoneUtil.h"
	#include "VariableManager.h"
	#include "CastleInfoManager.h"
	#include "DB.h"
	#include "Store.h"

	#include "GCCannotUse.h"
	#include "GCUseOK.h"
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseMessageItemFromInventoryHandler::execute(CGUseMessageItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();
	Zone*      pZone      = pPC->getZone();

	Assert(pInventory != NULL);
	Assert(pZone != NULL);

	CoordInven_t InvenX = pPacket->getX();
	CoordInven_t InvenY = pPacket->getY();

	// 인벤토리 좌표를 넘어가는 영역이라면 안 된다.
	if (InvenX >= pInventory->getWidth() || InvenY >= pInventory->getHeight())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 인벤토리에 그 아이템이 없다면 에러다.
	Item* pItem = pInventory->getItem(InvenX, InvenY);
	if (pItem == NULL)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 인벤토리에 있는 아이템의 Object를 받는다.
	ObjectID_t ItemObjectID = pItem->getObjectID();

	// OID가 일치하지 않거나, 사용할 수 없는 아이템이라면 에러다.
	if (ItemObjectID != pPacket->getObjectID() || !isUsableItem(pItem, pCreature))
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	if (pPC->getStore()->getItemIndex(pItem) != 0xff )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 아이템의 종류에 따라, 처리 함수를 분기시켜 준다.
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_EVENT_TREE:
			executeEventTree(pPacket, pPlayer);
			break;

		default:
		{
			//Assert(false);
			// by sigi. 2002.12.25
			filelog("useItemError.txt", "[CGUseMessageItemFromInventory] No Such ItemClassHandler=%s, owner=%s", ItemClass2ShortString[pItem->getItemClass()].c_str(), pCreature->getName().c_str());

			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);

		}
		return;
	}

#endif

    __END_DEBUG_EX __END_CATCH
}


void CGUseMessageItemFromInventoryHandler::executeEventTree(CGUseMessageItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();
	MonsterType_t	MType		 = 0;

	int				time		 = 0;

	switch (pItem->getItemType() )
	{
		case 12:
			MType = 482;
			time = g_pVariableManager->getVariable(CHRISTMAS_TREE_DECAY_TIME ) / 10;
			break;
		case 26:
			MType = 650;
			time = 21600;
			break;
		case 27:
			MType = 650;
			time = 43200;
			break;
		case 28:
			MType = 650;
			time = 86400;
			break;
		default:
			{
				filelog("EventTree.log", "이상한 아템을 썼다. : %s 가 %d", pPC->getName().c_str(), pItem->getItemType());
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
			}
			return;
	}

	// 타일에 스킬을 쓰는 것이라고 보고 쓸 수 있는지를 체크한다.
	// 안전지대에서는 사용할 수 없다.
	// 쓸 수 있는 아이템 타입인지 왁인한다. ItemType 이 12인 것만 사용할 수 있다.
	// 근처에(플레이어 주위의 5x5타일 이내) 다른 트리가 있다면 사용할 수 없다.
	if (!isAbleToUseTileSkill(pCreature )
		|| pZone->isMasterLair()
		|| ItemObjectID != pPacket->getObjectID()
		|| checkCorpse(pZone, MType, pPC->getX() - 2, pPC->getY() - 2, pPC->getX() + 2, pPC->getY() + 2 )
		)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 성이면 성주 길드원만 쓸 수 있다.
	if (!pPC->isGOD() )
	{
		if (pZone->isCastle() )
		{
			if (!g_pCastleInfoManager->isCastleMember(pZone->getZoneID(), pPC ) )
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		}
		// 성이 아닌 곳의 안전지대에선 절대 못 쓴다.
		else if (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & SAFE_ZONE)
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	}

/*	// 트리를 존에 추가한다. (트리는 몬스터 시체를 이용한다)
    MonsterCorpse* pMonsterCorpse = new MonsterCorpse(482, pPacket->getMessage(), 2); 
    Assert(pMonsterCorpse!=NULL); 
 
    pZone->getObjectRegistry().registerObject(pMonsterCorpse); 
 
    // 생성된 시체를 존에 추가한다. 
	int delayTime = g_pVariableManager->getVariable(CHRISTMAS_TREE_DECAY_TIME); // by sigi. 2002.12.17
	TPOINT pt = pZone->addItem(pMonsterCorpse, pPC->getX(), pPC->getY(), true, delayTime);	// 6시간 뒤에 트리(시체)가 사라진다.
	if (pt.x == -1)*/
	if (!createBulletinBoard(pZone, pPC->getX(), pPC->getY(), MType, pPacket->getMessage(), 
				VSDateTime::currentDateTime().addSecs(time ) ) )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);

		return;
	}

	// 사용한 아이템이므로 지워준다.
	pInventory->deleteItem(InvenX, InvenY);
	pItem->destroy();
	SAFE_DELETE(pItem);

	// 아이템을 사용했다고 클라이언트에 알린다.
	GCUseOK gcUseOK;
	pGamePlayer->sendPacket(&gcUseOK);

	//pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffectToTile);

#endif
    __END_DEBUG_EX __END_CATCH
}
