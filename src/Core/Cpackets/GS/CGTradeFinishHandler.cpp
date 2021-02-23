//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeFinishHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeFinish.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeFinish.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::execute (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
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
	try 
	{ 
		pTargetPC = pZone->getCreature(TargetOID); 
	}
	catch (NoSuchElementException) 
	{ 
		pTargetPC = NULL; 
	}
	*/

	// NoSuch제거. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID); 

	// 교환 상대가 없다면 에러다
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
	else throw ProtocolException("CGTradeFinishHanderl::execuete() : 알 수 없는 플레이어 크리쳐입니다.");
		
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeSlayer (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	BYTE          CODE            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*       pSender         = dynamic_cast<Slayer*>(pPC);
	Slayer*       pReceiver       = dynamic_cast<Slayer*>(pTargetPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	TradeInfo*    pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo*    pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	GCTradeFinish gcTradeFinish;

	// 현재 시간을 얻어온다.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// 교환을 승낙하는 코드다. 
	if (CODE == CG_TRADE_FINISH_ACCEPT)
	{
		// OK가 날아올 시간이 아니라면 에러다.
		if (pInfo1->isValidOKTime(currentTime) == false)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_UNKNOWN);
			return;
		}

		// 교환을 승낙했다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_ACCEPT);
		pTargetPlayer->sendPacket(&gcTradeFinish);

		// 교환 상태를 변환한다.
		pInfo1->setStatus(TRADE_FINISH);

		//cout << "CGTradeFinish [" << pSender->getName() << "]의 상태가 TRADE_FINISH로 바뀌었다." << endl;

		// 상대방도 교환을 허락하고 있다면, 실제로 교환을 하도록 한다.
		if (pInfo2->getStatus() == TRADE_FINISH)
		{
			//cout << "CGTradeFinish [" << pReceiver->getName() << "]의 상태도 TRADE_FINISH이므로, 교환을 수행한다." << endl;

			// 확실히 교환을 할 수 있다면 교환을 한다.
			if (pTradeManager->canTrade(pSender, pReceiver) == 1)
			{
				// 양 측에 교환을 수행하라는 패킷을 날려준다.
				gcTradeFinish.setTargetObjectID(pSender->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pTargetPlayer->sendPacket(&gcTradeFinish);

				gcTradeFinish.setTargetObjectID(pReceiver->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pPlayer->sendPacket(&gcTradeFinish);

				// 실제로 교환을 수행한다.
				pTradeManager->processTrade(pSender, pReceiver);
			}
			else if ( pTradeManager->canTrade(pSender, pReceiver) == 2 )
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX);
				return;
			}
			else 
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE);
				return;
			}
		}
	}
	// 교환을 거부하는 코드다.
	else if (CODE == CG_TRADE_FINISH_REJECT)
	{
		// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// 인증 패킷을 날려준다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_REJECT);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// 교환을 취소시킨다.
		pTradeManager->cancelTrade(pSender, pReceiver);

		// 교환이 취소되었다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_REJECT);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// 교환을 재고려하는 코드다.
	else if (CODE == CG_TRADE_FINISH_RECONSIDER)
	{
		// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// 인증 패킷을 날려준다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// 교환 상태를 변환한다.
		pInfo1->setStatus(TRADE_TRADING);

		// OK를 눌렀다가 cancel을 누르면, 다음 4초 동안은 OK가 다시 날아와서는
		// 안 된다. 그러므로 여기서 시간을 세팅해 준다.
		pInfo1->setNextTime(currentTime);

		// 교환이 재고려되었다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_RECONSIDER);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// 알수 없는 코드다. 사뿐하게 짤라준다.
	else throw ProtocolException("CGTradeFinish::executeSlayer() : 알 수 없는 코드");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeVampire (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	BYTE          CODE            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*      pSender         = dynamic_cast<Vampire*>(pPC);
	Vampire*      pReceiver       = dynamic_cast<Vampire*>(pTargetPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	TradeInfo*    pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo*    pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	GCTradeFinish gcTradeFinish;

	// 현재 시간을 얻어온다.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// 교환을 승낙하는 코드다. 
	if (CODE == CG_TRADE_FINISH_ACCEPT)
	{
		// OK가 날아올 시간이 아니라면 에러다. 
		if (pInfo1->isValidOKTime(currentTime) == false)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_UNKNOWN);
			return;
		}

		// 교환을 승낙했다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_ACCEPT);
		pTargetPlayer->sendPacket(&gcTradeFinish);

		// 교환 상태를 변환한다.
		pInfo1->setStatus(TRADE_FINISH);

		// 상대방도 교환을 허락하고 있다면, 실제로 교환을 하도록 한다.
		if (pInfo2->getStatus() == TRADE_FINISH)
		{
			// 확실히 교환을 할 수 있다면 교환을 한다.
			//cout << "CGTradeFinish [" << pReceiver->getName() << "]의 상태도 TRADE_FINISH이므로, 교환을 수행한다." << endl;
			if (pTradeManager->canTrade(pSender, pReceiver) == 1)
			{
				// 양 측에 교환을 수행하라는 패킷을 날려준다.
				gcTradeFinish.setTargetObjectID(pSender->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pTargetPlayer->sendPacket(&gcTradeFinish);

				gcTradeFinish.setTargetObjectID(pReceiver->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pPlayer->sendPacket(&gcTradeFinish);

				// 실제로 교환을 수행한다.
				pTradeManager->processTrade(pSender, pReceiver);
			}
			else if (pTradeManager->canTrade(pSender, pReceiver) == 2)
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX);
				return;
			}
			else
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE);
				return;
			}
		}
	}
	// 교환을 거부하는 코드다.
	else if (CODE == CG_TRADE_FINISH_REJECT)
	{
		// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// 인증 패킷을 날려준다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_REJECT);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// 교환을 취소시킨다.
		pTradeManager->cancelTrade(pSender, pReceiver);

		// 교환이 취소되었다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_REJECT);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// 교환을 재고려하는 코드다.
	else if (CODE == CG_TRADE_FINISH_RECONSIDER)
	{
		// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// 인증 패킷을 날려준다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// 교환 상태를 변환한다.
		pInfo1->setStatus(TRADE_TRADING);

		// OK를 눌렀다가 cancel을 누르면, 다음 4초 동안은 OK가 다시 날아와서는
		// 안 된다. 그러므로 여기서 시간을 세팅해 준다.
		pInfo1->setNextTime(currentTime);

		// 교환이 재고려되었다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_RECONSIDER);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// 알수 없는 코드다. 사뿐하게 짤라준다.
	else throw ProtocolException("CGTradeFinish::executeVampire() : 알 수 없는 코드");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeOusters (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 상위 함수에서 에러를 검사했기 때문에,
	// 여기서는 포인터가 널인지를 검사하지 않는다.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	BYTE          CODE            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*      pSender         = dynamic_cast<Ousters*>(pPC);
	Ousters*      pReceiver       = dynamic_cast<Ousters*>(pTargetPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	TradeInfo*    pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo*    pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	GCTradeFinish gcTradeFinish;

	// 현재 시간을 얻어온다.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// 교환을 승낙하는 코드다. 
	if (CODE == CG_TRADE_FINISH_ACCEPT)
	{
		// OK가 날아올 시간이 아니라면 에러다. 
		if (pInfo1->isValidOKTime(currentTime) == false)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_UNKNOWN);
			return;
		}

		// 교환을 승낙했다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_ACCEPT);
		pTargetPlayer->sendPacket(&gcTradeFinish);

		// 교환 상태를 변환한다.
		pInfo1->setStatus(TRADE_FINISH);

		// 상대방도 교환을 허락하고 있다면, 실제로 교환을 하도록 한다.
		if (pInfo2->getStatus() == TRADE_FINISH)
		{
			// 확실히 교환을 할 수 있다면 교환을 한다.
			//cout << "CGTradeFinish [" << pReceiver->getName() << "]의 상태도 TRADE_FINISH이므로, 교환을 수행한다." << endl;
			if (pTradeManager->canTrade(pSender, pReceiver) == 1)
			{
				// 양 측에 교환을 수행하라는 패킷을 날려준다.
				gcTradeFinish.setTargetObjectID(pSender->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pTargetPlayer->sendPacket(&gcTradeFinish);

				gcTradeFinish.setTargetObjectID(pReceiver->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pPlayer->sendPacket(&gcTradeFinish);

				// 실제로 교환을 수행한다.
				pTradeManager->processTrade(pSender, pReceiver);
			}
			else if (pTradeManager->canTrade(pSender, pReceiver) == 2)
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX);
				return;
			}
			else
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE);
				return;
			}
		}
	}
	// 교환을 거부하는 코드다.
	else if (CODE == CG_TRADE_FINISH_REJECT)
	{
		// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// 인증 패킷을 날려준다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_REJECT);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// 교환을 취소시킨다.
		pTradeManager->cancelTrade(pSender, pReceiver);

		// 교환이 취소되었다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_REJECT);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// 교환을 재고려하는 코드다.
	else if (CODE == CG_TRADE_FINISH_RECONSIDER)
	{
		// 현재 OK를 누른 상태라면, 클라이언트에게 인증 패킷을 보내줘야 한다.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// 인증 패킷을 날려준다.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// 교환 상태를 변환한다.
		pInfo1->setStatus(TRADE_TRADING);

		// OK를 눌렀다가 cancel을 누르면, 다음 4초 동안은 OK가 다시 날아와서는
		// 안 된다. 그러므로 여기서 시간을 세팅해 준다.
		pInfo1->setNextTime(currentTime);

		// 교환이 재고려되었다는 것을 상대방에게 알려준다.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_RECONSIDER);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// 알수 없는 코드다. 사뿐하게 짤라준다.
	else throw ProtocolException("CGTradeFinish::executeOusters() : 알 수 없는 코드");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeError(CGTradeFinish* pPacket, Player* pPlayer, BYTE ErrorCode)
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

