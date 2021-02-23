//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectNicknameHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectNickname.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "NicknameBook.h"
#include "NicknameInfo.h"
#include "Zone.h"

#include "Gpackets/GCModifyNickname.h"
#include "Gpackets/GCNicknameVerify.h"
#endif	// __GAME_SERVER__

void CGSelectNicknameHandler::execute (CGSelectNickname* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	GCModifyNickname gcMN;
	GCNicknameVerify gcNV;

	WORD nID = pPacket->getNicknameID();

	NicknameInfo* pCurrent = pPC->getNickname();
	if ( pCurrent != NULL &&
		( pCurrent->getNicknameType() == NicknameInfo::NICK_CUSTOM_FORCED ||
		  pCurrent->getNicknameType() == NicknameInfo::NICK_FORCED ) )
	{
		gcNV.setCode(NICKNAME_SELECT_FAIL_FORCED);
		pGamePlayer->sendPacket( &gcNV );
		return;
	}

	NicknameInfo* pNickname = pPC->getNicknameBook()->getNicknameInfo( nID );

	if ( pNickname == NULL )
	{
		if ( nID != 0xffff )
		{
			gcNV.setCode(NICKNAME_SELECT_FAIL_NO_SUCH);
			pGamePlayer->sendPacket( &gcNV );
			return;
		}
		else
		{
			static NicknameInfo noNick;
			noNick.setNicknameType( NicknameInfo::NICK_NONE );
			pNickname = &noNick;
		}
	}

	gcNV.setCode(NICKNAME_SELECT_OK);
	pGamePlayer->sendPacket( &gcNV );

	if ( pNickname->getNicknameType() == NicknameInfo::NICK_NONE )
	{
		pPC->setNickname( NULL );
	}
	else
	{
		pPC->setNickname( pNickname );
	}

	gcMN.setObjectID( pPC->getObjectID() );
	gcMN.setNicknameInfo( pNickname );
	pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcMN );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

