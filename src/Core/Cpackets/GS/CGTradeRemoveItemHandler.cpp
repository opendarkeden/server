//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItemHandler.cpp
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeRemoveItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "Inventory.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeRemoveItem.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::execute (CGTradeRemoveItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t TargetOID = pPacket->getTargetObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pPC = pGamePlayer->getCreature();
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환을 원하는 상대방을 존에서 찾아본다.
	Creature* pTargetPC = NULL;
	/*
	try { pTargetPC = pZone->getCreature(TargetOID); } 
	catch (NoSuchElementException) { pTargetPC = NULL; }
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID);

	// 교환 상대가 없거나, 같은 종족이 아니라면 에러다
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// 교환 상대가 사람이 아니거나, 같은 종족이 아니라면 에러다.
	if (!pTargetPC->isPC() || !isSameRace(pTargetPC, pPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

	// 둘 다 안전 지대에 있는지 체크를 한다.
	if (!isInSafeZone(pPC) || !isInSafeZone(pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// 오토바이를 타고 있다면 에러다.
	if (pPC->isSlayer() && pTargetPC->isSlayer())
	{
		Slayer* pSlayer1 = dynamic_cast<Slayer*>(pPC);
		Slayer* pSlayer2 = dynamic_cast<Slayer*>(pTargetPC);

		if (pSlayer1->hasRideMotorcycle() || pSlayer2->hasRideMotorcycle())
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	if (pPC->isOusters() && pTargetPC->isOusters())
	{
		Ousters* pOusters1 = dynamic_cast<Ousters*>(pPC);
		Ousters* pOusters2 = dynamic_cast<Ousters*>(pTargetPC);

		if ( pOusters1->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
			|| pOusters2->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
		)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	// 둘이서 교환을 하고 있는 상태가 아니라면 에러다.
	if (!pTradeManager->isTrading(pPC, pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
		return;
	}

	if (pPC->isSlayer()) executeSlayer(pPacket, pPlayer);
	else if (pPC->isVampire()) executeVampire(pPacket, pPlayer);
	else if (pPC->isOusters()) executeOusters(pPacket, pPlayer);
	else throw ProtocolException("CGTradeRemoveItem::execute() : 알 수 없는 플레이어 크리쳐");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeSlayer (CGTradeRemoveItem* pPacket, Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에 
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t  ItemOID     = pPacket->getItemObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	Creature*   pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*     pSender     = dynamic_cast<Slayer*>(pPC);

	// 교환 대상에 추가할 아이템의 포인터를 얻어낸다.
	CoordInven_t X, Y;
	Inventory*   pInventory     = pSender->getInventory();
	Item*        pItem          = pInventory->findItemOID(ItemOID, X, Y);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 빼야할 아이템이 없다면 당연히 더 이상 처리가 불가능하다.
	if (pItem == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_REMOVE_ITEM);
		return;
	}

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	// TradeManager에서 교환 대상으로 들어가 있던 아이템을 제거한다.
	//Assert(pInfo1->removeItem(pItem));
	pInfo1->removeItem(pItem);

	Timeval currentTime;
	getCurrentTime(currentTime);
	pInfo1->setNextTime(currentTime);

	// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH이므로, 인증 패킷을 보내준다." << endl;

		// 인증패킷을 날려준다.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_REMOVE_ITEM);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH가 아니므로, 인증 패킷 날리지 않는다." << endl;
	}

	// 아이템을 더하거나 뺄 경우, 상태가 TRADE_FINISH라면 
	// TRADE_TRADING으로 바꿔줘야 한다.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// 상대방에게서 날려줄 아이템 정보를 구성한다.
	GCTradeRemoveItem gcTradeRemoveItem;
	gcTradeRemoveItem.setTargetObjectID(pSender->getObjectID());
	gcTradeRemoveItem.setItemObjectID(pItem->getObjectID());

	// 상대방에게 빼야할 아이템의 정보를 날려준다.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeRemoveItem);

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeVampire (CGTradeRemoveItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에 
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t  ItemOID     = pPacket->getItemObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	Creature*   pTargetPC  = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*    pSender    = dynamic_cast<Vampire*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 대상에 추가할 아이템의 포인터를 얻어낸다.
	CoordInven_t X, Y;
	Inventory*   pInventory     = pSender->getInventory();
	Item*        pItem          = pInventory->findItemOID(ItemOID, X, Y);

	// 빼야할 아이템이 없다면 당연히 더 이상 처리가 불가능하다.
	if (pItem == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_REMOVE_ITEM);
		return;
	}

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	// TradeManager에서 교환 대상으로 들어가 있던 아이템을 제거한다.
	//Assert(pInfo1->removeItem(pItem));
	pInfo1->removeItem(pItem);

	// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH이므로, 인증 패킷을 보내준다." << endl;

		// 인증패킷을 날려준다.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_REMOVE_ITEM);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH가 아니므로, 인증 패킷 날리지 않는다." << endl;
	}

	// 아이템을 더하거나 뺄 경우, 상태가 TRADE_FINISH라면 
	// TRADE_TRADING으로 바꿔줘야 한다.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// 상대방에게서 날려줄 아이템 정보를 구성한다.
	GCTradeRemoveItem gcTradeRemoveItem;
	gcTradeRemoveItem.setTargetObjectID(pSender->getObjectID());
	gcTradeRemoveItem.setItemObjectID(pItem->getObjectID());

	// 상대방에게 빼야할 아이템의 정보를 날려준다.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeRemoveItem);

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeOusters (CGTradeRemoveItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에 
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t  ItemOID     = pPacket->getItemObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	Creature*   pTargetPC  = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*    pSender    = dynamic_cast<Ousters*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 대상에 추가할 아이템의 포인터를 얻어낸다.
	CoordInven_t X, Y;
	Inventory*   pInventory     = pSender->getInventory();
	Item*        pItem          = pInventory->findItemOID(ItemOID, X, Y);

	// 빼야할 아이템이 없다면 당연히 더 이상 처리가 불가능하다.
	if (pItem == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_REMOVE_ITEM);
		return;
	}

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	// TradeManager에서 교환 대상으로 들어가 있던 아이템을 제거한다.
	//Assert(pInfo1->removeItem(pItem));
	pInfo1->removeItem(pItem);

	// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH이므로, 인증 패킷을 보내준다." << endl;

		// 인증패킷을 날려준다.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_REMOVE_ITEM);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]의 상태가 TRADE_FINISH가 아니므로, 인증 패킷 날리지 않는다." << endl;
	}

	// 아이템을 더하거나 뺄 경우, 상태가 TRADE_FINISH라면 
	// TRADE_TRADING으로 바꿔줘야 한다.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// 상대방에게서 날려줄 아이템 정보를 구성한다.
	GCTradeRemoveItem gcTradeRemoveItem;
	gcTradeRemoveItem.setTargetObjectID(pSender->getObjectID());
	gcTradeRemoveItem.setItemObjectID(pItem->getObjectID());

	// 상대방에게 빼야할 아이템의 정보를 날려준다.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeRemoveItem);

#endif

	__END_DEBUG_EX __END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeError (CGTradeRemoveItem* pPacket , Player* pPlayer, BYTE ErrorCode)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	GCTradeError gcTradeError;
	gcTradeError.setTargetObjectID(pPacket->getTargetObjectID());
	gcTradeError.setCode(ErrorCode);
	pPlayer->sendPacket(&gcTradeError);

#endif

	__END_DEBUG_EX __END_CATCH
}

