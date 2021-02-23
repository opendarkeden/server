//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDownSkillHandler.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDownSkill.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillParentInfo.h"
	#include "SkillInfo.h"
	#include "SkillDomainInfoManager.h"
	#include "Ousters.h"
	#include "OustersSkillSlot.h"

	#include "Gpackets/GCDownSkillOK.h"
	#include "Gpackets/GCDownSkillFailed.h"
	#include "Gpackets/GCModifyInformation.h"

	#include <cmath>
	#include <cstdio>
	int getSkillMapID(ElementalDomain domain);
#endif	

#define DOMAIN_DIFFER 0
#define NOT_OUSTERS 1
#define TOO_LOW 2
#define TOO_HIGH 3
#define NOT_ENOUGH_MONEY 4
#define INVALID_SKILL 5
#define HAVE_NOT_SKILL 6
#define CANNOT_DROP_SKILL 7

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDownSkillHandler::execute (CGDownSkill* pPacket , Player* pPlayer)
	 throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	SkillType_t targetSkillType = pPacket->getSkillType();

	GCDownSkillFailed failpkt;
	failpkt.setSkillType( targetSkillType );

	if ( !pPC->isOusters() )
	{
		failpkt.setDesc( NOT_OUSTERS );
		pPlayer->sendPacket( &failpkt );

		return;
	}

	Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
	Assert( pOusters != NULL );
	OustersSkillSlot* pTargetSkillSlot = pOusters->getSkill( targetSkillType );

	if ( pTargetSkillSlot == NULL )
	{
		failpkt.setDesc( HAVE_NOT_SKILL );
		pPlayer->sendPacket( &failpkt );
		return;
	}

	SkillInfo* pTargetSkillInfo = NULL;

	try
	{
		pTargetSkillInfo = g_pSkillInfoManager->getSkillInfo( targetSkillType );
	}
	catch(Exception& e)
	{
		failpkt.setDesc( INVALID_SKILL );
		pPlayer->sendPacket( &failpkt );

		return;
	}

	if ( pTargetSkillSlot->getExpLevel() <= 1 )
	{
		if ( !pTargetSkillInfo->canDelete() )
		{
			failpkt.setDesc( TOO_LOW );
			pPlayer->sendPacket( &failpkt );
			return;
		}

		list<SkillType_t>& rRequiredSkills = pTargetSkillInfo->getRequiredSkills();
		list<SkillType_t>::iterator itr = rRequiredSkills.begin();

		for ( ; itr != rRequiredSkills.end(); ++itr )
		{
			if ( pOusters->hasSkill(*itr) != NULL )
			{
				bool canDrop = false;
				SkillInfo* pFollowingSkillInfo = g_pSkillInfoManager->getSkillInfo(*itr);
				list<SkillType_t>& rRequireSkills = pFollowingSkillInfo->getRequireSkills();
				list<SkillType_t>::iterator itr2 = rRequireSkills.begin();
				for ( ; itr2 != rRequireSkills.end(); ++itr2 )
				{
					if ( (*itr2) != targetSkillType && pOusters->hasSkill(*itr2) != NULL )
					{
						SkillInfo* pAlternativeSkillInfo = g_pSkillInfoManager->getSkillInfo(*itr2);
						if ( getSkillMapID((ElementalDomain)pAlternativeSkillInfo->getElementalDomain()) == getSkillMapID((ElementalDomain)pTargetSkillInfo->getElementalDomain()) )
							canDrop = true;
					}
				}

				if ( !canDrop )
				{
					failpkt.setDesc( CANNOT_DROP_SKILL );
					pPlayer->sendPacket( &failpkt );
					return;
				}
			}
		}
	}

/*	if ( pTargetSkillSlot->getExpLevel() >= 30 )
	{
		failpkt.setDesc( TOO_HIGH );
		pPlayer->sendPacket( &failpkt );
		return;
	}*/

	Assert( pTargetSkillInfo != NULL );

	int backPoint = pTargetSkillInfo->getLevelUpPoint();
	Price_t downPrice = (int)(backPoint * pow(pOusters->getLevel(),1.3) * 200);

	if ( pTargetSkillSlot->getExpLevel() <= 1 )
	{
		downPrice *= 5;
		if ( downPrice == 0 ) downPrice = 1000000;
	}

	if ( pOusters->getGold() < downPrice )
	{
		failpkt.setDesc( NOT_ENOUGH_MONEY );
		pPlayer->sendPacket( &failpkt );

		return;
	}

	pOusters->decreaseGoldEx( downPrice );
	pTargetSkillSlot->setExpLevel( pTargetSkillSlot->getExpLevel() - 1 );
	pTargetSkillSlot->save();
	if ( pTargetSkillSlot->getExpLevel() <= 0 )
	{
		pTargetSkillSlot->destroy(pOusters->getName());
		backPoint = pTargetSkillInfo->getSkillPoint();
		pOusters->removeSkill(targetSkillType);
	}

	pOusters->setSkillBonus( pOusters->getSkillBonus() + backPoint );
	char query[50];
	sprintf( query, "SkillBonus=%d", pOusters->getSkillBonus() );
	pOusters->tinysave(query);

	GCDownSkillOK okpkt;
	okpkt.setSkillType(targetSkillType);
	pPlayer->sendPacket(&okpkt);

	GCModifyInformation gcMI;
	gcMI.addLongData( MODIFY_GOLD, pOusters->getGold() );
	gcMI.addShortData( MODIFY_SKILL_BONUS_POINT, pOusters->getSkillBonus() );

	switch ( targetSkillType )
	{
		case SKILL_HIDE_SIGHT:
		{
			OUSTERS_RECORD prev;
			pOusters->getOustersRecord( prev );
			pOusters->initAllStat();
			pOusters->sendRealWearingInfo();
			pOusters->addModifyInfo( prev, gcMI );
		}
			break;

		default :
			break;
	}

	pPlayer->sendPacket(&gcMI);

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

