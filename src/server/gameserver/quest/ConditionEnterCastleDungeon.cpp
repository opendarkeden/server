////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterCastleDungeon.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionEnterCastleDungeon.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "Zone.h"
#include "PaySystem.h"
#include "WarSystem.h"
#include "PacketUtil.h"
#include "GamePlayer.h"
#include "CastleInfoManager.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionEnterCastleDungeon::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	/*if (!g_pVariableManager->isActiveHolyLand())
	{
		return false;
	}*/
	// 나중에 전쟁중인지 체크해야 된다

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	//cout << "Condition: EnterCastleDungeon" << endl;

	bool bPayPlay = false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	Assert(pGamePlayer!=NULL);

#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	// 이미 유료존에 있는 경우라면... 관계없겠지.
	// 패밀리 요금제 적용중일 경우
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
		bool hasGuildWar = g_pWarSystem->hasCastleActiveWar( m_CastleZoneID );

		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
		Assert(pCastleInfo!=NULL);

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
		Assert(pPC!=NULL);

		GuildID_t GuildID 		= pPC->getGuildID();
		GuildID_t OwnerGuildID 	= pCastleInfo->getGuildID();

		// 전쟁이 없을 때 --> 성 소유 길드만 들어갈 수 있다.
		// 길드 전쟁 중 --> 공격 길드도 들어갈 수 있다.
		if ( OwnerGuildID!=SlayerCommon && OwnerGuildID!=VampireCommon && OwnerGuildID!=OustersCommon
			&& GuildID==OwnerGuildID)
		{
			return true;
		}

		if (hasGuildWar)
		{
			GuildID_t AttackGuildID;
			g_pWarSystem->getAttackGuildID( m_CastleZoneID, AttackGuildID );
			if (GuildID==AttackGuildID)
			{
				return true;
			}
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionEnterCastleDungeon::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_CastleZoneID = propertyBuffer.getPropertyInt("CastleZoneID");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionEnterCastleDungeon::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionEnterCastleDungeon("
		<< "CastleZoneID:" << (int)m_CastleZoneID
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
