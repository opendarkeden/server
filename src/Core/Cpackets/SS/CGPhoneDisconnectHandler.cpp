//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPhoneDisconnectHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGPhoneDisconnect.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "TelephoneCenter.h"

	#include "Gpackets/GCPhoneDisconnected.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPhoneDisconnectHandler::execute (CGPhoneDisconnect* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();

	Assert (pCreature->isSlayer());

	Player* pTargetPlayer = NULL;

	bool Success = false;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	SlotID_t PhoneSlot = pPacket->getSlotID();
	SlotID_t TargetPhoneSlot = MAX_PHONE_SLOT;

	Assert (PhoneSlot < MAX_PHONE_SLOT);

	PhoneNumber_t PhoneNumber = pSlayer->getPhoneNumber();
	PhoneNumber_t TargetPhoneNumber = pSlayer->getPhoneSlotNumber(PhoneSlot);

	Assert (TargetPhoneNumber != 0);

	Slayer* pTargetSlayer = g_pTelephoneCenter->getSlayer(TargetPhoneNumber);

	//cout << "Disconnect PhoneSlot : " << (int)PhoneSlot << ", Phone Number : " << (int)TargetPhoneNumber << endl;

	// 찾았으면....
	if (pTargetSlayer != NULL) 
	{
		pTargetPlayer = pTargetSlayer->getPlayer();

		if (pTargetSlayer->isSlotByPhoneNumber(PhoneNumber)) 
		{
			// 폰 번호로 그 번호가 들어있는 슬랏을 찾는다.
			TargetPhoneSlot = pTargetSlayer->getSlotWithPhoneNumber(PhoneNumber);

			Success = true;
		}
	}

	// 정상적으로 찾고 끊었을 경우
	if (Success) 
	{
		// 이제 끊기는 마당이므로 0 으로 양측 다 셋팅.
		pTargetSlayer->setPhoneSlotNumber(TargetPhoneSlot, 0);
		pSlayer->setPhoneSlotNumber(PhoneSlot, 0);

		// 끊는 사람에게 날리는 패킷
		GCPhoneDisconnected gcPhoneDisconnected;
		gcPhoneDisconnected.setPhoneNumber(TargetPhoneNumber);
		gcPhoneDisconnected.setSlotID(PhoneSlot);

		// 상대적으로 끊기는 사람에게 날리는 패킷
		GCPhoneDisconnected gcPhoneDisconnected2;
		gcPhoneDisconnected2.setPhoneNumber(PhoneNumber);
		gcPhoneDisconnected2.setSlotID(TargetPhoneSlot);

		pPlayer->sendPacket(&gcPhoneDisconnected);
		pTargetPlayer->sendPacket(&gcPhoneDisconnected2);

		//cout << "Disconnected Successfull" << endl;

	// 비정상 적일 경우 -_-;
	} 
	else 
	{
		// 등록된 전화번호를 가진 사람이 특정 이유로 나간 상태이다.
		// 따라서 등록 번호를 초기화 시켜준다.
		pSlayer->setPhoneSlotNumber(PhoneSlot, 0);

		// 끊는 사람에게 날리는 패킷
		GCPhoneDisconnected gcPhoneDisconnected;
		gcPhoneDisconnected.setPhoneNumber(TargetPhoneNumber);
		gcPhoneDisconnected.setSlotID(PhoneSlot);

		pPlayer->sendPacket(&gcPhoneDisconnected);

		//cout << "Not found That Slot PhoneNumber User" << endl;

	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
