#ifndef __WAIT_FOR_MEET_H__
#define __WAIT_FOR_MEET_H__

#include "PartnerWaitingManager.h"
#include "PlayerCreature.h"

class CoupleRingBase;

class WaitForMeet : public PartnerWaitInfo
{
public:
	WaitForMeet( PlayerCreature* pWaitingPC, string RequestedPCName ) : PartnerWaitInfo( pWaitingPC, RequestedPCName ){ }
public:
	uint waitPartner( PlayerCreature* pTargetPC ) throw(Error);
	uint acceptPartner( PlayerCreature* pRequestedPC ) throw(Error);
	void timeExpired() throw(Error);
	WaitType getWaitType() { return WAIT_FOR_MEET; }

public:
	static Gold_t	getCoupleRegisterFee( PlayerCreature* pPC ) throw(Error);

protected:
	static void receiveCoupleRegisterFee( PlayerCreature* pPC ) throw(Error);
	static uint canMakeCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 );
	static OptionType_t getRandomOptionType( PlayerCreature* pPC );
	static CoupleRingBase* giveCoupleRing( PlayerCreature* pPC, string partnerName, _TPOINT* pPt = NULL ) throw(Error);
	static bool canGetCoupleRing( PlayerCreature* pPC, _TPOINT& pt );
	static uint canHavePartner( PlayerCreature* pPC ) throw(Error);
};

#endif // __WAIT_FOR_MEET_H__

