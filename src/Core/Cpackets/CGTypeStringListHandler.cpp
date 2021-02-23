//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTypeStringListHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGTypeStringList.h"
#include "Player.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "NPC.h"
#include "PCFinder.h"
#include "FlagSet.h"
#include "couple/PartnerWaitingManager.h"
#include "couple/WaitForApart.h"
#include "couple/CoupleManager.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

#include "SystemAvailabilitiesManager.h"

#ifdef __GAME_SERVER__
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTypeStringListHandler::execute (CGTypeStringList* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	if ( pPacket->getSize() < 1 )
	{
		return;
	}

	SYSTEM_ASSERT( SYSTEM_COUPLE );

	switch ( pPacket->getType() )
	{
		case CGTypeStringList::STRING_TYPE_WAIT_FOR_MEET:
			executeWaitForMeet( pPacket, pPlayer );
			break;

		case CGTypeStringList::STRING_TYPE_WAIT_FOR_APART:
			executeWaitForApart( pPacket, pPlayer );
			break;

		case CGTypeStringList::STRING_TYPE_FORCE_APART_COUPLE:
			executeApartForce( pPacket, pPlayer );
			break;

		default:
			break;
	}

	return;

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}

void CGTypeStringListHandler::executeWaitForMeet(CGTypeStringList* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	Assert(pPacket->getSize() != 0);

	GCNPCResponse gcQuitDialog;
	gcQuitDialog.setCode( NPC_RESPONSE_QUIT_DIALOGUE );

	GamePlayer* pGP = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGP->getCreature());
	Assert( pPC != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	Creature* pNPCCreature = pZone->getCreature((ObjectID_t)pPacket->getParam());
	if ( pNPCCreature == NULL ) 
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	if ( !pNPCCreature->isNPC() )
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pNPCCreature);
	Assert( pNPC != NULL );

	PartnerWaitingManager *pPWM = pNPC->getCoupleRegisterManager();
	Assert( pPWM != NULL );

	uint result = pPWM->waitForPartner( pPC, pPacket->popString() );

	if ( result != 0 )
	{
		gcQuitDialog.setCode( NPC_RESPONSE_COUPLE_CANNOT_MEET );
		gcQuitDialog.setParameter( result );
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

#endif
    __END_DEBUG_EX __END_CATCH
}
void CGTypeStringListHandler::executeWaitForApart(CGTypeStringList* pPacket, Player* pPlayer) 
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	Assert(pPacket->getSize() != 0);

	GCNPCResponse gcQuitDialog;
	gcQuitDialog.setCode( NPC_RESPONSE_NOT_COUPLE );

	GamePlayer* pGP = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGP->getCreature());
	Assert( pPC != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	Creature* pNPCCreature = pZone->getCreature((ObjectID_t)pPacket->getParam());
	if ( pNPCCreature == NULL ) 
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	if ( !pNPCCreature->isNPC() )
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pNPCCreature);
	Assert( pNPC != NULL );

	PartnerWaitingManager *pPWM = pNPC->getCoupleUnregisterManager();
	Assert( pPWM != NULL );

	uint result = pPWM->waitForPartner( pPC, pPacket->popString() );
	if ( result != 0 )
	{
		gcQuitDialog.setParameter( result );
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

#endif
    __END_DEBUG_EX __END_CATCH
}

void CGTypeStringListHandler::executeApartForce( CGTypeStringList* pPacket, Player* pPlayer )
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	Assert(pPacket->getSize() != 0);

	GCNPCResponse gcQuitDialog;
	gcQuitDialog.setCode( NPC_RESPONSE_NOT_COUPLE );

	GamePlayer* pGP = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGP->getCreature());
	Assert( pPC != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	if ( !g_pCoupleManager->hasCouple( pPC ) )
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	string PartnerName;
	if ( !g_pCoupleManager->getPartnerName( pPC, PartnerName ) )
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	if ( pPacket->popString() != PartnerName )
	{
		pPlayer->sendPacket( &gcQuitDialog );
		return;
	}

	PlayerCreature* pPartnerPC = NULL;

    __ENTER_CRITICAL_SECTION((*g_pPCFinder))

    Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED(PartnerName);
    if (pTargetCreature!=NULL)
    {
        if ( !pTargetCreature->isPC() )
        {
            g_pPCFinder->unlock();
			pPlayer->sendPacket( &gcQuitDialog );
			return;
        }

        pPartnerPC = dynamic_cast<PlayerCreature*>( pTargetCreature );
		if ( pPartnerPC != NULL )
		{
			WaitForApart::removeCoupleItem( pPartnerPC );
			pPartnerPC->getFlagSet()->turnOff( FLAGSET_IS_COUPLE );
			pPartnerPC->getFlagSet()->save( pPartnerPC->getName() );

			gcQuitDialog.setCode( NPC_RESPONSE_COUPLE_APART_SUCCESS );
			pPartnerPC->getPlayer()->sendPacket( &gcQuitDialog );
		}
    }

    __LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	WaitForApart::removeCoupleItem( pPC );

	g_pCoupleManager->removeCoupleForce( pPC, PartnerName );

	pPC->getFlagSet()->turnOff( FLAGSET_IS_COUPLE );
	pPC->getFlagSet()->save( pPC->getName() );

	Alignment_t	currentAlignment = pPC->getAlignment();
	Alignment_t newAlignment = max( -10000, (int)currentAlignment - 5000 );

	pPC->setAlignment( newAlignment );
	GCModifyInformation gcMI;
	gcMI.addLongData( MODIFY_ALIGNMENT, newAlignment );
	pPlayer->sendPacket( &gcMI );

	gcQuitDialog.setCode( NPC_RESPONSE_COUPLE_APART_SUCCESS );
	pPlayer->sendPacket( &gcQuitDialog );

	return;
#endif
    __END_DEBUG_EX __END_CATCH
}
