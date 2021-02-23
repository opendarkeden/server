//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestInfo.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestInfo.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Gpackets/GCOtherModifyInfo.h"
	#include "Gpackets/GCOtherGuildName.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 뭔가에 대한 정보를 요청하는 경우이다.
//////////////////////////////////////////////////////////////////////////////
void CGRequestInfoHandler::execute (CGRequestInfo* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer!=NULL);

	switch (pPacket->getCode())
	{
		//------------------------------------------------------------
		// 다른 캐릭터의 정보를 요청하는 경우
		//------------------------------------------------------------
		case CGRequestInfo::REQUEST_CHARACTER_INFO :
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Assert(pCreature!=NULL);

			Zone* pZone = pCreature->getZone();
			Assert(pZone!=NULL);

			Creature* pTargetCreature = pZone->getCreature( pPacket->getValue() );

			if (pTargetCreature!=NULL 
				&& pTargetCreature->isPC())
			{
				// 볼려는 대상이 운영자 모양이 아닌 경우만 된다.
				if (pTargetCreature->isSlayer())
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
					if (pSlayer->getCompetenceShape()!=1)
						return;
				}
				else if (pTargetCreature->isVampire())
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pTargetCreature);
					if (pVampire->getCompetenceShape()!=1)
						return;
				}
				else if (pTargetCreature->isOusters())
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pTargetCreature);
					if (pOusters->getCompetenceShape()!=1)
						return;
				}

				bool bSendInfo = false;

				if (pZone==NULL) return;

				GCOtherModifyInfo gcOtherModifyInfo;
				GCOtherGuildName gcOtherGuildName;

				// 값 설정 부분
				// 같은 종족만 보여준다.
				if (( pCreature->isSlayer() || pCreature->getCompetenceShape() != 1) && pTargetCreature->isSlayer())
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);

					gcOtherModifyInfo.addShortData( MODIFY_BASIC_STR, pSlayer->getSTR(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_STR, pSlayer->getSTR(ATTR_CURRENT) );
					gcOtherModifyInfo.addShortData( MODIFY_BASIC_DEX, pSlayer->getDEX(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_DEX, pSlayer->getDEX(ATTR_CURRENT) );
					gcOtherModifyInfo.addShortData( MODIFY_BASIC_INT, pSlayer->getINT(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_INT, pSlayer->getINT(ATTR_CURRENT) );
					gcOtherModifyInfo.addLongData( MODIFY_FAME, pSlayer->getFame() );
					gcOtherModifyInfo.addShortData( MODIFY_SWORD_DOMAIN_LEVEL, pSlayer->getSkillDomainLevel(SKILL_DOMAIN_SWORD) );
					gcOtherModifyInfo.addShortData( MODIFY_BLADE_DOMAIN_LEVEL, pSlayer->getSkillDomainLevel(SKILL_DOMAIN_BLADE) );
					gcOtherModifyInfo.addShortData( MODIFY_HEAL_DOMAIN_LEVEL, pSlayer->getSkillDomainLevel(SKILL_DOMAIN_HEAL) );
					gcOtherModifyInfo.addShortData( MODIFY_ENCHANT_DOMAIN_LEVEL, pSlayer->getSkillDomainLevel(SKILL_DOMAIN_ENCHANT) );
					gcOtherModifyInfo.addShortData( MODIFY_GUN_DOMAIN_LEVEL, pSlayer->getSkillDomainLevel(SKILL_DOMAIN_GUN) );
					gcOtherModifyInfo.addLongData( MODIFY_ALIGNMENT, pSlayer->getAlignment() );
					gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pSlayer->getGuildID() );
					gcOtherModifyInfo.addShortData( MODIFY_RANK, pSlayer->getRank() );

					bSendInfo = true;
				}
				else if ((pCreature->isVampire() || pCreature->getCompetenceShape() != 1) && pTargetCreature->isVampire())
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pTargetCreature);

					gcOtherModifyInfo.addShortData( MODIFY_BASIC_STR, pVampire->getSTR(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_STR, pVampire->getSTR(ATTR_CURRENT) );
					gcOtherModifyInfo.addShortData( MODIFY_BASIC_DEX, pVampire->getDEX(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_DEX, pVampire->getDEX(ATTR_CURRENT) );
					gcOtherModifyInfo.addShortData( MODIFY_BASIC_INT, pVampire->getINT(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_INT, pVampire->getINT(ATTR_CURRENT) );
					gcOtherModifyInfo.addLongData( MODIFY_FAME, pVampire->getFame() );
					gcOtherModifyInfo.addShortData( MODIFY_LEVEL, pVampire->getLevel() );
					gcOtherModifyInfo.addLongData( MODIFY_ALIGNMENT, pVampire->getAlignment() );
					gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pVampire->getGuildID() );
					gcOtherModifyInfo.addShortData( MODIFY_RANK, pVampire->getRank() );

					bSendInfo = true;
				}
				else if ((pCreature->isOusters() || pCreature->getCompetenceShape() != 1) && pTargetCreature->isOusters())
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pTargetCreature);

					gcOtherModifyInfo.addShortData( MODIFY_BASIC_STR, pOusters->getSTR(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_STR, pOusters->getSTR(ATTR_CURRENT) );
					gcOtherModifyInfo.addShortData( MODIFY_BASIC_DEX, pOusters->getDEX(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_DEX, pOusters->getDEX(ATTR_CURRENT) );
					gcOtherModifyInfo.addShortData( MODIFY_BASIC_INT, pOusters->getINT(ATTR_BASIC) );
					gcOtherModifyInfo.addShortData( MODIFY_CURRENT_INT, pOusters->getINT(ATTR_CURRENT) );
					gcOtherModifyInfo.addLongData( MODIFY_FAME, pOusters->getFame() );
					gcOtherModifyInfo.addShortData( MODIFY_LEVEL, pOusters->getLevel() );
					gcOtherModifyInfo.addLongData( MODIFY_ALIGNMENT, pOusters->getAlignment() );
					gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pOusters->getGuildID() );
					gcOtherModifyInfo.addShortData( MODIFY_RANK, pOusters->getRank() );

					bSendInfo = true;
				}

				if (bSendInfo)
				{
					gcOtherModifyInfo.setObjectID( pPacket->getValue() );

					pGamePlayer->sendPacket( &gcOtherModifyInfo );
					
					if ( pTargetCreature->isPC() )
					{
						PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pTargetCreature);

						if ( pPC != NULL && pPC->getGuildID() != pPC->getCommonGuildID() )
						{
							gcOtherGuildName.setObjectID( pPC->getObjectID() );
							gcOtherGuildName.setGuildID( pPC->getGuildID() );
							gcOtherGuildName.setGuildName( pPC->getGuildName() );

							pGamePlayer->sendPacket( &gcOtherGuildName );
						}
					}
				}
			}
		}
		break;
	}
#endif

	__END_DEBUG_EX __END_CATCH
}
