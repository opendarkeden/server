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
	uint waitPartner( PlayerCreature* pTargetPC ) ;
	uint acceptPartner( PlayerCreature* pRequestedPC ) ;
	void timeExpired() ;
	WaitType getWaitType() { return WAIT_FOR_APART; }

	static bool removeCoupleItem( PlayerCreature* pPC ) ;
	static bool hasCoupleItem( PlayerCreature* pPC )  { return getCoupleItem( pPC ) != NULL; }
	static Item* getCoupleItem( PlayerCreature* pPC ) ;
};

#endif // __WAIT_FOR_APART_H__

