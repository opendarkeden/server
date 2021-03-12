////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterCastle.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionEnterCastle.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "Zone.h"
#include "PaySystem.h"
#include "GamePlayer.h"
#include "PacketUtil.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "ZoneUtil.h"
#include "VariableManager.h"
#include "CastleInfoManager.h"
#include "DB.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionEnterCastle::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	/*if (!g_pVariableManager->isActiveCastle())
	{
		return false;
	}*/
	// 나중에 전쟁중인지 체크해야 된다

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	//cout << "Condition: EnterCastle" << endl;

	bool bPayPlay = false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	Assert(pGamePlayer!=NULL);

#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	// 이미 유료존에 있는 경우라면... 관계없겠지.
	// 패밀리 요금 적용중일 경우
	if (pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass())
	{
		bPayPlay = true;
	}
	else
	{
		// 일단 zone 요금 체크
		string connectIP = pGamePlayer->getSocket()->getHost();
		
		if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
		{
			sendPayInfo(pGamePlayer);
			bPayPlay = true;
		}
	}
#else
	bPayPlay = true;
#endif

	// 돈 낸 사람만 castle 에 들어갈 수 있다.
	if (bPayPlay)
	{
		// 존을 찾는다.
		Zone* pZone = getZoneByZoneID(m_TargetZoneID);
		Assert(pZone!=NULL);

		// castle 이 아니면 체크할 필요가 없는거다.
		if (!pZone->isCastle())
		{
			return true;
		}

		// 종족간 전쟁중에는 종족에 상관없이 누구나 통과시켜야 한다.
		// 동족간 전쟁중에는 타종족을 통과시켜서는 안 된다.
		// 평시에는 NPC를 통해야 하므로 누구도 통과시킬 수 없다.
		// 전쟁시스템 만들때 이거 다 추가시켜야 된다. 2003. 1.20.
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );

		return g_pCastleInfoManager->canPortalActivate( m_TargetZoneID, pPC );
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionEnterCastle::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_TargetZoneID = propertyBuffer.getPropertyInt("TargetZoneID");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionEnterCastle::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionEnterCastle("
		<< "TargetZoneID:" << (int)m_TargetZoneID
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
