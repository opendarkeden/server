#ifndef __WAIT_FOR_APART_H__
#define __WAIT_FOR_APART_H__

#include "Inventory.h"
#include "PlayerCreature.h"
#include "PartnerWaitingManager.h"

class WaitForApart : public PartnerWaitInfo
{
public:
	WaitForApart( PlayerCreature* pWaitingPC, string RequestedPCName ) : PartnerWaitInfo( pWaitingPC, RequestedPCName ){ }
public:
	uint waitPartner( PlayerCreature* pTargetPC ) throw(Error);
	uint acceptPartner( PlayerCreature* pRequestedPC ) throw(Error);
	void timeExpired() throw(Error);
	WaitType getWaitType() { return WAIT_FOR_APART; }

	static bool removeCoupleItem( PlayerCreature* pPC ) throw(Error);
	static bool hasCoupleItem( PlayerCreature* pPC ) throw(Error) { return getCoupleItem( pPC ) != NULL; }
	static Item* getCoupleItem( PlayerCreature* pPC ) throw(Error);
};

#endif // __WAIT_FOR_APART_H__

