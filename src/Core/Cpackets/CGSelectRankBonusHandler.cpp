//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectRankBonusHandler.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectRankBonus.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "RankBonus.h"
	#include "RankBonusInfo.h"

	#include "Gpackets/GCSelectRankBonusFailed.h"
	#include "Gpackets/GCSelectRankBonusOK.h"

	#include "SystemAvailabilitiesManager.h"
#endif	


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectRankBonusHandler::execute (CGSelectRankBonus* pPacket , Player* pPlayer)
	 throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT( SYSTEM_RANK_BONUS );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pGamePlayer->getCreature() );
	Assert( pPC != NULL );

	if ( pPC->learnRankBonus( pPacket->getRankBonusType() ) )
	{
		GCSelectRankBonusOK okpkt;
		okpkt.setRankBonusType( pPacket->getRankBonusType() );
		pPlayer->sendPacket( &okpkt );

		switch ( pPacket->getRankBonusType() )
		{
			case RankBonus::RANK_BONUS_BEHEMOTH_ARMOR:
			case RankBonus::RANK_BONUS_DRAGON_EYE:
			case RankBonus::RANK_BONUS_IMMORTAL_HEART:
			case RankBonus::RANK_BONUS_RELIANCE_BRAIN:
			case RankBonus::RANK_BONUS_SLAYING_KNIFE:
			case RankBonus::RANK_BONUS_HAWK_WING:

			case RankBonus::RANK_BONUS_IMMORTAL_BLOOD:
			case RankBonus::RANK_BONUS_BEHEMOTH_SKIN:
			case RankBonus::RANK_BONUS_SAFE_ROBE:
			case RankBonus::RANK_BONUS_CROW_WING:

			case RankBonus::RANK_BONUS_WOOD_SKIN:
			case RankBonus::RANK_BONUS_WIND_SENSE:
			case RankBonus::RANK_BONUS_HOMING_EYE:
			case RankBonus::RANK_BONUS_LIFE_ENERGY:
			case RankBonus::RANK_BONUS_SOUL_ENERGY:
			case RankBonus::RANK_BONUS_STONE_MAUL:
			case RankBonus::RANK_BONUS_SWIFT_ARM:
			case RankBonus::RANK_BONUS_PERCEPTION:
			case RankBonus::RANK_BONUS_STONE_OF_SAGE:
			case RankBonus::RANK_BONUS_FOOT_OF_RANGER:
			case RankBonus::RANK_BONUS_WARRIORS_FIST:
			case RankBonus::RANK_BONUS_POWER_OF_SPIRIT:
			case RankBonus::RANK_BONUS_WIND_OF_SPIRIT:
			case RankBonus::RANK_BONUS_PIXIES_EYES:
			case RankBonus::RANK_BONUS_GROUND_OF_SPIRIT:
			case RankBonus::RANK_BONUS_FIRE_OF_SPIRIT:
			case RankBonus::RANK_BONUS_EVOLUTION_IMMORTAL_HEART:
			case RankBonus::RANK_BONUS_BEHEMOTH_ARMOR_2:
			case RankBonus::RANK_BONUS_DRAGON_EYE_2:
			case RankBonus::RANK_BONUS_EVOLUTION_RELIANCE_BRAIN:
			case RankBonus::RANK_BONUS_HIT_CONTROL:
			case RankBonus::RANK_BONUS_SALAMANDERS_KNOWLEDGE:
			case RankBonus::RANK_BONUS_UNDINES_KNOWLEDGE:
			case RankBonus::RANK_BONUS_GNOMES_KNOWLEDGE:
			{
				if ( pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					Assert( pSlayer != NULL );

					SLAYER_RECORD prev;

					pSlayer->getSlayerRecord(prev);
					pSlayer->initAllStat();
					pSlayer->sendRealWearingInfo();
					pSlayer->sendModifyInfo(prev);
				}
				else if ( pPC->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
					Assert( pVampire != NULL );

					VAMPIRE_RECORD prev;
					
					pVampire->getVampireRecord(prev);
					pVampire->initAllStat();
					pVampire->sendModifyInfo(prev);
					pVampire->sendRealWearingInfo();
				}
				else if ( pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					Assert( pOusters != NULL );

					OUSTERS_RECORD prev;
					
					pOusters->getOustersRecord(prev);
					pOusters->initAllStat();
					pOusters->sendModifyInfo(prev);
					pOusters->sendRealWearingInfo();
				}
			}
			break;

			case RankBonus::RANK_BONUS_DEADLY_SPEAR:
			case RankBonus::RANK_BONUS_SAPPHIRE_BLESS:
			case RankBonus::RANK_BONUS_RUBY_BLESS:
			case RankBonus::RANK_BONUS_DIAMOND_BLESS:
			case RankBonus::RANK_BONUS_EMERALD_BLESS:
			case RankBonus::RANK_BONUS_WIGHT_HAND:
			case RankBonus::RANK_BONUS_SEIREN_HAND:
			case RankBonus::RANK_BONUS_FORTUNE_HAND:

			case RankBonus::RANK_BONUS_URANUS_BLESS:

			case RankBonus::RANK_BONUS_FIRE_ENDOW:
			case RankBonus::RANK_BONUS_WATER_ENDOW:
			case RankBonus::RANK_BONUS_EARTH_ENDOW:
			case RankBonus::RANK_BONUS_ANTI_ACID_SKIN:
			case RankBonus::RANK_BONUS_ANTI_BLOODY_SKIN:
			case RankBonus::RANK_BONUS_ANTI_CURSE_SKIN:
			case RankBonus::RANK_BONUS_ANTI_POISON_SKIN:
			case RankBonus::RANK_BONUS_ANTI_SILVER_DAMAGE_SKIN:
			case RankBonus::RANK_BONUS_BLESS_OF_NATURE:
			case RankBonus::RANK_BONUS_LIFE_ABSORB:
			case RankBonus::RANK_BONUS_SOUL_ABSORB:
			case RankBonus::RANK_BONUS_MYSTIC_RULE:
			case RankBonus::RANK_BONUS_ACID_INQUIRY:
			case RankBonus::RANK_BONUS_BLOODY_INQUIRY:
			case RankBonus::RANK_BONUS_CURSE_INQUIRY:
			case RankBonus::RANK_BONUS_POISON_INQUIRY:
			case RankBonus::RANK_BONUS_INQUIRY_MASTERY:
			case RankBonus::RANK_BONUS_ACID_MASTERY:
			case RankBonus::RANK_BONUS_BLOODY_MASTERY:
			case RankBonus::RANK_BONUS_CURSE_MASTERY:
			case RankBonus::RANK_BONUS_POISON_MASTERY:
			case RankBonus::RANK_BONUS_SKILL_MASTERY:
			{
				if ( pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					Assert( pSlayer != NULL );

					pSlayer->initAllStat();
				}
				else if ( pPC->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
					Assert( pVampire != NULL );

					pVampire->initAllStat();
				}
				else if ( pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					Assert( pOusters != NULL );

					pOusters->initAllStat();
				}
			}
			break;

			default:
			{
				break;
			}
		}
	}
	else
	{
		GCSelectRankBonusFailed failedpkt;
		failedpkt.setRankBonusType( pPacket->getRankBonusType() );
		pPlayer->sendPacket( &failedpkt );
	}
		
#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

