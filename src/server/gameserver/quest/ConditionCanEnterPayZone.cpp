////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterPayZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterPayZone.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "PaySystem.h"
#include "GamePlayer.h"
#include "PacketUtil.h"
#include "DB.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterPayZone::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());

	Assert(pGamePlayer!=NULL);

	// 이미 유료존에 있는 경우라면... 관계없겠지.
	// 패밀리 요금 적용중인 경우
	if (pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass() )
	{
		return true;
	}

	string connectIP = pGamePlayer->getSocket()->getHost();
	
	if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
	{
		sendPayInfo(pGamePlayer);
		return true;
	}
	else
	{
		return false;
	}
#else
	return true;
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterPayZone::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterPayZone::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanEnterPayZone("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
