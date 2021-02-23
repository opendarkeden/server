//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDialUpHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDialUp.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "TelephoneCenter.h"
	#include "Slayer.h"
	#include "Gpackets/GCRing.h"
	#include "Gpackets/GCPhoneConnected.h"
	#include "Gpackets/GCPhoneConnectionFailed.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDialUpHandler::execute (CGDialUp* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();

	Assert (pCreature->isSlayer());

	bool Success = false;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	Player* pTargetPlayer = NULL;

	SlotID_t PSlot = MAX_PHONE_SLOT;
	SlotID_t PSlot2 = MAX_PHONE_SLOT;

	// 폰 번호를 받아온다.
	PhoneNumber_t PNumber = pPacket->getPhoneNumber();

	Slayer* pTargetSlayer = g_pTelephoneCenter->getSlayer(PNumber);

	if (pSlayer->findEmptyPhoneSlot() != MAX_PHONE_SLOT && pSlayer != pTargetSlayer) 
	{
		if (pTargetSlayer != NULL) 
		{
			pTargetPlayer = pTargetSlayer->getPlayer();

			if (pTargetSlayer->isEmptyPhoneSlot()) 
			{
				if (!(pTargetSlayer->isSlotByPhoneNumber(PNumber))) 
				{
					Success = true;
				}
			}
		}
	}

	if (Success) 
	{
		// 상대방의 빈 슬랏을 받아온다.
		PSlot2 = pTargetSlayer->findEmptyPhoneSlot();

		// 자신의 빈 슬랏을 찾는다.
		PSlot = pSlayer->findEmptyPhoneSlot();

		// 상대방의 슬랏에 자신의 번호를 셋팅
		pTargetSlayer->setPhoneSlotNumber (PSlot2, pSlayer->getPhoneNumber());

		// 자신의 슬랏에 상대방의 번호 셋팅
		pSlayer->setPhoneSlotNumber (PSlot, PNumber);

		//cout << "Call Number : " << pSlayer->getPhoneNumber() << ", Called Number : " << PNumber << endl;
		//cout << "Call Slot : " << PSlot << ", Called Slot : " << PSlot2 << endl;

		// 전화 받을 상대에게 날리는 패킷
		GCRing gcRing;
		gcRing.setPhoneNumber(pSlayer->getPhoneNumber());
		gcRing.setSlotID(PSlot2);
		gcRing.setName(pSlayer->getName());

		// 전화 건 당사자에게 날리는 패킷
		GCPhoneConnected gcPhoneConnected;
		gcPhoneConnected.setSlotID(PSlot);
		gcPhoneConnected.setName(pTargetSlayer->getName());

		pTargetPlayer->sendPacket(&gcRing);
		pGamePlayer->sendPacket(&gcPhoneConnected);
	} 
	else 
	{
		GCPhoneConnectionFailed gcPhoneConnectionFailed;
		pGamePlayer->sendPacket(&gcPhoneConnectionFailed);
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
