//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPhoneSayHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGPhoneSay.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "TelephoneCenter.h"
	#include "Slayer.h"

	#include "Gpackets/GCPhoneSay.h"
	#include "Gpackets/GCPhoneDisconnected.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPhoneSayHandler::execute (CGPhoneSay* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	bool Success = false;
	
	Creature* pCreature = pGamePlayer->getCreature();

	Assert (pCreature->isSlayer());
	
	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	SlotID_t PhoneSlot = pPacket->getSlotID();

	Assert (PhoneSlot < MAX_PHONE_SLOT);

	PhoneNumber_t PhoneNumber = pSlayer->getPhoneNumber();

	PhoneNumber_t TargetPhoneNumber = pSlayer->getPhoneSlotNumber(PhoneSlot);

	Slayer* pTargetSlayer = g_pTelephoneCenter->getSlayer(TargetPhoneNumber);

	//cout << "PhoneSlot : " << (int)PhoneSlot << ", Message : " << pPacket->getMessage() << endl;

	if (pTargetSlayer != NULL) {

		if (pTargetSlayer->isSlotByPhoneNumber(PhoneNumber)) {
	
			Success = true;
	
		}
	}

	// 정상적인 통신 상태일때 Message를 날린다.
	if (Success) {

		SlotID_t TargetPhoneSlot = pTargetSlayer->getSlotWithPhoneNumber(PhoneNumber);

		Player* pTargetPlayer = pTargetSlayer->getPlayer();

		// 서버에서 클라이언트로 전송하므로 GC- 패킷을 사용해야 한다.
		GCPhoneSay gcPhoneSay;
	
		// 크리처 이름과 메시지를 패킷에 대입한다.
		gcPhoneSay.setSlotID(TargetPhoneSlot);	
		gcPhoneSay.setMessage(pPacket->getMessage());

		pTargetPlayer->sendPacket(&gcPhoneSay);

		//cout << "Phone Say Successfull " << endl;

	// 상대의 접속이 끊겼거나 이상한 짓거리가 발생했을때..
	} else {

		GCPhoneDisconnected gcPhoneDisconnected;
		gcPhoneDisconnected.setSlotID(PhoneSlot);

		pGamePlayer->sendPacket(&gcPhoneDisconnected);

		//cout << "Phone Say Failed" << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
