//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeMoneyHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeMoney.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeMoney.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::execute (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t      TargetOID   = pPacket->getTargetObjectID();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pPC = pGamePlayer->getCreature();
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);
	
	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);
	
	Creature* pTargetPC = NULL;
	/*
	try { pTargetPC = pZone->getCreature(TargetOID); } 
	catch (NoSuchElementException) { pTargetPC = NULL; }
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID);

	// 교환 상대가 없다면 에러다.
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// 교환 상대가 사람이 아니거나, 같은 종족이 에러다.
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
	else throw ProtocolException("CGTradeMoney::execute() : 알 수 없는 플레이어 크리쳐");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeSlayer (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 검사를 했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	Gold_t        Amount          = pPacket->getAmount();
	BYTE          Code            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID); 

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*       pSender         = dynamic_cast<Slayer*>(pPC);
	Slayer*       pReceiver       = dynamic_cast<Slayer*>(pTargetPC);
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	Gold_t        finalAmount     = Amount;
	Gold_t        margin          = 0;
	GCTradeMoney  gcTradeMoney;
	GCTradeVerify gcTradeVerify;

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 상태가 맞는지 체크를 해봐야한다.
	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pReceiver->getName());

	// 인벤토리에서 돈을 덜어, 교환창에다 더한다.
	if (Code == CG_TRADE_MONEY_INCREASE)
	{
		// 교환창에다 더할 액수보다 많은 돈을 가지고 있어야 한다.
		if (pSender->getGold() >= Amount)
		{
			// 돈을 받는 쪽이 맥스를 초과하게 된다면, 일부만 넣어줘야 한다.
			// 현재 교환 예정인 돈도 더해서 계산. by sigi. 2003.1.8
			Gold_t receiverGold = pReceiver->getGold() + pInfo1->getGold();
			if (receiverGold + Amount > MAX_MONEY)
			{
				margin      = receiverGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// 인벤토리에서 돈을 빼고, 교환창에다 더한다.
			pSender->setGold(pSender->getGold() - finalAmount);
			pInfo1->setGold(pInfo1->getGold() + finalAmount);

			// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// 인증 패킷을 날려준다.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_INCREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 아이템을 더하거나 뺄 경우, 상태를 변환해줘야 한다.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// 돈을 올린 당사자에게 실제로 인벤토리에서
			// 빠진 금액이 얼마인지 보내준다.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// 상대방에게 바뀐 정보를 보내준다.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else 
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_INCREASE_MONEY);
			return;
		}
	}
	// 교환창에서 돈을 덜어, 인벤토리에다가 더한다.
	else if (Code == CG_TRADE_MONEY_DECREASE)
	{
		// 인벤토리에다 더할 액수보다 교환창에 있는 돈이 많아야 한다.
		if (pInfo1->getGold() >= Amount)
		{
			// 돈이 맥스를 초과하게 된다면, 일부만 뺄 수 있다.
			Gold_t senderGold = pSender->getGold() + pInfo2->getGold();
			if (senderGold + Amount > MAX_MONEY)
			{
				margin      = senderGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}
			
			// 인벤토리에다가 돈을 더하고, 교환창에서 돈을 뺀다.
			pSender->setGold(pSender->getGold() + finalAmount);
			pInfo1->setGold(pInfo1->getGold() - finalAmount);

			// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// 인증 패킷을 날려준다.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_DECREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 아이템을 더하거나 뺄 경우, 상태를 변환해줘야 한다.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// 돈을 올린 당사자에게 실제로 인벤토리에다 
			// 더한 금액이 얼마인지 보내준다.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// 상대방에게 바뀐 정보를 보내준다.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_DECREASE_MONEY);
			return;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeVampire (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 검사를 했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	Gold_t        Amount          = pPacket->getAmount();
	BYTE          Code            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID); 

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*      pSender         = dynamic_cast<Vampire*>(pPC);
	Vampire*      pReceiver       = dynamic_cast<Vampire*>(pTargetPC);
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	Gold_t        finalAmount     = Amount;
	Gold_t        margin          = 0;
	GCTradeMoney  gcTradeMoney;
	GCTradeVerify gcTradeVerify;

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 상태가 맞는지 체크를 해봐야한다.
	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pReceiver->getName());

	// 인벤토리에서 돈을 덜어, 교환창에다 더한다.
	if (Code == CG_TRADE_MONEY_INCREASE)
	{
		// 교환창에다 더할 액수보다 많은 돈을 가지고 있어야 한다.
		if (pSender->getGold() >= Amount)
		{
			// 돈을 받는 쪽이 맥스를 초과하게 된다면, 일부만 넣어줘야 한다.
			// 현재 교환 예정인 돈도 더해서 계산. by sigi. 2003.1.8
			Gold_t receiverGold = pReceiver->getGold() + pInfo1->getGold();
			if (receiverGold + Amount > MAX_MONEY)
			{
				margin		= receiverGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// 인벤토리에서 돈을 빼고, 교환창에다 더한다.
			pSender->setGold(pSender->getGold() - finalAmount);
			pInfo1->setGold(pInfo1->getGold() + finalAmount);

			// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// 인증 패킷을 날려준다.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_INCREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 아이템을 더하거나 뺄 경우, 상태를 변환해줘야 한다.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// 돈을 올린 당사자에게 실제로 인벤토리에서
			// 빠진 금액이 얼마인지 보내준다.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// 상대방에게 바뀐 정보를 보내준다.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else 
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_INCREASE_MONEY);
			return;
		}
	}
	// 교환창에서 돈을 덜어, 인벤토리에다가 더한다.
	else if (Code == CG_TRADE_MONEY_DECREASE)
	{
		// 인벤토리에다 더할 액수보다 교환창에 있는 돈이 많아야 한다.
		if (pInfo1->getGold() >= Amount)
		{
			// 돈이 맥스를 초과하게 된다면, 일부만 뺄 수 있다.
			Gold_t senderGold = pSender->getGold() + pInfo2->getGold();
			if (senderGold + Amount > MAX_MONEY)
			{
				margin      = senderGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// 인벤토리에다가 돈을 더하고, 교환창에서 돈을 뺀다.
			pSender->setGold(pSender->getGold() + finalAmount);
			pInfo1->setGold(pInfo1->getGold() - finalAmount);

			// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// 인증 패킷을 날려준다.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_DECREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 아이템을 더하거나 뺄 경우, 상태를 변환해줘야 한다.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// 돈을 올린 당사자에게 실제로 인벤토리에다 
			// 더한 금액이 얼마인지 보내준다.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// 상대방에게 바뀐 정보를 보내준다.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_DECREASE_MONEY);
			return;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeOusters (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 검사를 했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	Gold_t        Amount          = pPacket->getAmount();
	BYTE          Code            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID); 

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*      pSender         = dynamic_cast<Ousters*>(pPC);
	Ousters*      pReceiver       = dynamic_cast<Ousters*>(pTargetPC);
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	Gold_t        finalAmount     = Amount;
	Gold_t        margin          = 0;
	GCTradeMoney  gcTradeMoney;
	GCTradeVerify gcTradeVerify;

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 상태가 맞는지 체크를 해봐야한다.
	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pReceiver->getName());

	// 인벤토리에서 돈을 덜어, 교환창에다 더한다.
	if (Code == CG_TRADE_MONEY_INCREASE)
	{
		// 교환창에다 더할 액수보다 많은 돈을 가지고 있어야 한다.
		if (pSender->getGold() >= Amount)
		{
			// 돈을 받는 쪽이 맥스를 초과하게 된다면, 일부만 넣어줘야 한다.
			// 현재 교환 예정인 돈도 더해서 계산. by sigi. 2003.1.8
			Gold_t receiverGold = pReceiver->getGold() + pInfo1->getGold();
			if (receiverGold + Amount > MAX_MONEY)
			{
				margin		= receiverGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// 인벤토리에서 돈을 빼고, 교환창에다 더한다.
			pSender->setGold(pSender->getGold() - finalAmount);
			pInfo1->setGold(pInfo1->getGold() + finalAmount);

			// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// 인증 패킷을 날려준다.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_INCREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 아이템을 더하거나 뺄 경우, 상태를 변환해줘야 한다.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// 돈을 올린 당사자에게 실제로 인벤토리에서
			// 빠진 금액이 얼마인지 보내준다.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// 상대방에게 바뀐 정보를 보내준다.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else 
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_INCREASE_MONEY);
			return;
		}
	}
	// 교환창에서 돈을 덜어, 인벤토리에다가 더한다.
	else if (Code == CG_TRADE_MONEY_DECREASE)
	{
		// 인벤토리에다 더할 액수보다 교환창에 있는 돈이 많아야 한다.
		if (pInfo1->getGold() >= Amount)
		{
			// 돈이 맥스를 초과하게 된다면, 일부만 뺄 수 있다.
			Gold_t senderGold = pSender->getGold() + pInfo2->getGold();
			if (senderGold + Amount > MAX_MONEY)
			{
				margin      = senderGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// 인벤토리에다가 돈을 더하고, 교환창에서 돈을 뺀다.
			pSender->setGold(pSender->getGold() + finalAmount);
			pInfo1->setGold(pInfo1->getGold() - finalAmount);

			// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// 인증 패킷을 날려준다.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_DECREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 아이템을 더하거나 뺄 경우, 상태를 변환해줘야 한다.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// 돈을 올린 당사자에게 실제로 인벤토리에다 
			// 더한 금액이 얼마인지 보내준다.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// 상대방에게 바뀐 정보를 보내준다.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_DECREASE_MONEY);
			return;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeError (CGTradeMoney* pPacket , Player* pPlayer, BYTE ErrorCode)
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


