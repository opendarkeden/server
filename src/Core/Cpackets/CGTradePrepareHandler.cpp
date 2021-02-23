//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradePrepareHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradePrepare.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"
	#include "StringStream.h"

	#include "Gpackets/GCTradePrepare.h"
	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradePrepareHandler::execute (CGTradePrepare* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t     TargetOID   = pPacket->getTargetObjectID();
	BYTE           CODE        = pPacket->getCode();
	GamePlayer*    pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	GCTradePrepare gcTradePrepare;

	Creature* pSender = pGamePlayer->getCreature();
	Assert(pSender != NULL);

	Zone* pZone = pSender->getZone();
	Assert(pZone != NULL);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// 교환 상대자를 존에서 찾아본다.
	Creature* pReceiver = NULL;
	/*
	try { pReceiver = pZone->getCreature(TargetOID); }
	catch (NoSuchElementException) { pReceiver = NULL; }
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pReceiver = pZone->getCreature(TargetOID);

	// 교환을 할 놈이 존재하지 않는다면 당연히 교환할 수 없다.
	if (pReceiver == NULL)
	{
		pTradeManager->cancelTrade(pSender);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// 교환을 할 놈과 받을 놈의 이름이 같다면, 즉 같은 캐릭이라면 접속을 잘라버린다.
	// 실제로 이런 경우가 발생했다. 듀얼 접속인 것 같은데... 2002-03-04 김성민
	if (pSender->getName() == pReceiver->getName())
	{
		StringStream msg;
		msg << "CGTradePrepare : Error, Same Creature!!! Name[" << pSender->getName() << "]";
		filelog("TradeError.log", "%s", msg.toString().c_str());
		throw ProtocolException(msg.toString());
	}

	// 교환을 할 놈이 PC가 아니거나, 종족이 다르다면 교환을 할 수가 없다.
	if (!pReceiver->isPC() || !isSameRace(pSender, pReceiver))
	{
		pTradeManager->cancelTrade(pSender);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

	// 둘 다 안전 지대에 있는지 체크를 한다.
	if (!isInSafeZone(pSender) || !isInSafeZone(pReceiver))
	{
		pTradeManager->cancelTrade(pSender);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// 오토바이를 타고 있다면 에러다.
	if (pSender->isSlayer() && pReceiver->isSlayer())
	{
		Slayer* pSlayer1 = dynamic_cast<Slayer*>(pSender);
		Slayer* pSlayer2 = dynamic_cast<Slayer*>(pReceiver);

		if (pSlayer1->hasRideMotorcycle() || pSlayer2->hasRideMotorcycle())
		{
			pTradeManager->cancelTrade(pSender);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	if (pSender->isOusters() && pReceiver->isOusters())
	{
		Ousters* pOusters1 = dynamic_cast<Ousters*>(pSender);
		Ousters* pOusters2 = dynamic_cast<Ousters*>(pReceiver);

		if ( pOusters1->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
			|| pOusters2->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
		)
		{
			pTradeManager->cancelTrade(pSender);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	TradeInfo* pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*    pReceiverPlayer = pReceiver->getPlayer();

	// A가 B에게 교환을 제일 처음 요구했다...
	switch (CODE)
	{
		////////////////////////////////////////////////////////////
		// A가 B에게 교환을 요구했으므로,
		// B에게 A가 교환을 요구하고 있다는 사실을 알려준다.
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_REQUEST:
			// 교환을 요구한 놈이 교환 중이라면... -_-
			if (pInfo1 != NULL)
			{
				pTradeManager->cancelTrade(pSender);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_ALREADY_TRADING);
				return;
			}

			// 교환을 요구받은 놈이 교환 중이라면,
			// 바쁘니까 교환에 응할 수 없다.
			if (pInfo2 != NULL)
			{
				gcTradePrepare.setTargetObjectID(pPacket->getTargetObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_BUSY);
				pPlayer->sendPacket(&gcTradePrepare);
				return;
			}
			   
			// 패킷을 보내준다.
			gcTradePrepare.setTargetObjectID(pSender->getObjectID());
			gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_REQUEST);
			pReceiverPlayer->sendPacket(&gcTradePrepare);

			// 둘 다 교환 모드로 들어갔으므로, TradeInfo를 생성해 준다.
			pTradeManager->initTrade(pSender, pReceiver);
			break;

		////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_CANCEL:
			// 교환 중인지를 체크한다.
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_CANCEL);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
				// 교환을 거부했으므로, TradeInfo를 삭제해 준다.
				pTradeManager->cancelTrade(pSender, pReceiver);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		////////////////////////////////////////////////////////////
		// B가 교환에 응한다는 사실을 A에게 알려준다.
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_ACCEPT:
			// 교환 중인지를 체크한다.
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_ACCEPT);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		////////////////////////////////////////////////////////////
		// B가 교환을 거부한다는 사실을 A에게 알려준다.
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_REJECT:
			// 교환 중인지를 체크한다.
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_REJECT);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
				// 교환을 거부했으므로, TradeInfo를 삭제해 준다.
				pTradeManager->cancelTrade(pSender, pReceiver);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		////////////////////////////////////////////////////////////
		// B가 현재 교환에 응할 수 없는 상태(상점에 있는 경우)라는 
		// 것을 A에게 알려준다. 
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_BUSY:
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				// 패킷을 보내준다.
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_BUSY);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
				// 교환을 거부했으므로, TradeInfo를 삭제해준다.
				pTradeManager->cancelTrade(pSender, pReceiver);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		// 알수 없는 코드다...
		default:
			throw ProtocolException("CGTradePrepare::execute() : 알 수 없는 코드");
	}


#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradePrepareHandler::executeError (CGTradePrepare* pPacket , Player* pPlayer, BYTE ErrorCode)
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


