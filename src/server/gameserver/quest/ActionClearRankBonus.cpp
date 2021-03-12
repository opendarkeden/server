////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionClearRankBonus.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionClearRankBonus.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "GamePlayer.h"
#include "FlagSet.h"
#include "VariableManager.h"
#include "StringPool.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCModifyInformation.h"

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionClearRankBonus::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
	
	try
	{
		m_Rank = propertyBuffer.getPropertyInt("Rank");
	}
	catch ( NoSuchElementException& nsee )
	{
		throw Error( nsee.toString() );
	}

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionClearRankBonus::execute (Creature * pCreature1, Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	if ( !pCreature2->isPC() )
		return;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	// 일단 창을 닫고 본다.
	GCNPCResponse response;

	Gold_t clearFee = 0;
	FlagSetType flagSet = FLAGSET_MAX;
	switch ( m_Rank )
	{
		case 5 :
			clearFee = 500000;
			flagSet = FLAGSET_CLEAR_RANK_BONUS_5;
			break;
		case 10 :
			clearFee = 2000000;
			flagSet = FLAGSET_CLEAR_RANK_BONUS_10;
			break;
		case 15 :
			clearFee = 10000000;
			flagSet = FLAGSET_CLEAR_RANK_BONUS_15;
			break;
		case 20 :
			clearFee = 50000000;
			flagSet = FLAGSET_CLEAR_RANK_BONUS_20;
			break;
		default :
			{
				response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
				pPlayer->sendPacket( &response );
			}
	}

	FlagSet* pFlagSet = pPC->getFlagSet();
	Assert( pFlagSet != NULL );

	if ( pFlagSet->isOn( flagSet ) )
	{
		response.setCode( NPC_RESPONSE_ALREADY_CLEAR_RANK_BONUS );
		pPlayer->sendPacket( &response );

		response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &response );

		return;
	}

	if ( pPC->getRankBonusByRank( m_Rank ) == NULL )
	{
		response.setCode( NPC_RESPONSE_NO_RANK_BONUS );
		pPlayer->sendPacket( &response );

		response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &response );

		return;
	}

	if ( pPC->getGold() < clearFee )
	{
		response.setCode( NPC_RESPONSE_NOT_ENOUGH_MONEY );
		pPlayer->sendPacket( &response );

		response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &response );

		return;
	}

	pPC->clearRankBonus( m_Rank );

	GCModifyInformation gcMI;

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>( pPC );
		Assert( pSlayer != NULL );

		SLAYER_RECORD prev;
		pSlayer->getSlayerRecord( prev );

		pSlayer->initAllStat();

		pSlayer->sendRealWearingInfo();
		pSlayer->sendModifyInfo( prev );

		pSlayer->setGoldEx( pSlayer->getGold() - clearFee );
		gcMI.addLongData( MODIFY_GOLD, pSlayer->getGold() );
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>( pPC );
		Assert( pVampire != NULL );

		VAMPIRE_RECORD prev;
		pVampire->getVampireRecord( prev );

		pVampire->initAllStat();

		pVampire->sendRealWearingInfo();
		pVampire->sendModifyInfo( prev );

		pVampire->setGoldEx( pVampire->getGold() - clearFee );
		gcMI.addLongData( MODIFY_GOLD, pVampire->getGold() );
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>( pPC );
		Assert( pOusters != NULL );

		OUSTERS_RECORD prev;
		pOusters->getOustersRecord( prev );

		pOusters->initAllStat();

		pOusters->sendRealWearingInfo();
		pOusters->sendModifyInfo( prev );

		pOusters->setGoldEx( pOusters->getGold() - clearFee );
		gcMI.addLongData( MODIFY_GOLD, pOusters->getGold() );
	}

	pFlagSet->turnOn( flagSet );
	pFlagSet->save( pPC->getName() );

	pPlayer->sendPacket( &gcMI );
	pPC->sendRankBonusInfo();

	response.setCode( NPC_RESPONSE_CLEAR_RANK_BONUS_OK );
	pPlayer->sendPacket( &response );

	response.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &response );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionClearRankBonus::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionClearRankBonus("
		<< ")";
	return msg.toString();

	__END_CATCH
}
