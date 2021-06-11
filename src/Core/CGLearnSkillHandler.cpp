//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLearnSkillHandler.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGLearnSkill.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "StringPool.h"
	#include "SkillParentInfo.h"
	#include "SkillInfo.h"
	#include "SkillDomainInfoManager.h"

	#include "GCLearnSkillFailed.h"
	#include "GCLearnSkillOK.h"
	#include "GCLearnSkillReady.h"
	#include "GCSystemMessage.h"

	#include <cstdio>

	bool CheckRequiredSkill(SkillInfo* pSkillInfo, Ousters* pOusters, int domain);
	int getSkillMapID(ElementalDomain domain);
#endif	

//////////////////////////////////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////////////////////////////////

#define DOMAIN_DIFFER           0
#define NPC_LEVEL_LIMIT         1
#define PARENT_SKILL_NEED       2
#define SKILL_NOT_IMPLEMENTED  10


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGLearnSkillHandler::execute (CGLearnSkill* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
		
	Assert(pPacket != NULL && pPlayer != NULL);

	cout << pPacket->toString() << endl;

	SkillType_t        targetSkillType  = pPacket->getSkillType();
	GamePlayer*        pGamePlayer      = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature*    pPC              = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	GCLearnSkillFailed failpkt; 

	// ÇöÀç ±¸ÇöµÇÁö ¾ÊÀº ±â¼úÀ» ¹è¿ì·Á´ÂÁö Ã¼Å©ÇÑ´Ù.
	switch (targetSkillType)
	{
		////////////////////////////////////////////////////////////
		// Áö¿øµÇ´Â ±â¼ú
		////////////////////////////////////////////////////////////
		case SKILL_DOUBLE_IMPACT:
		case SKILL_TRIPLE_SLASHER:
		case SKILL_RAINBOW_SLASHER:
		case SKILL_THUNDER_SPARK:
		case SKILL_DANCING_SWORD:
		case SKILL_CROSS_COUNTER:
		case SKILL_FLASH_SLIDING:
		case SKILL_LIGHTNING_HAND:
		case SKILL_SINGLE_BLOW:
		case SKILL_SPIRAL_SLAY:
		case SKILL_TRIPLE_BREAK:
		case SKILL_WILD_SMASH:
		case SKILL_GHOST_BLADE:
		case SKILL_POTENTIAL_EXPLOSION:
		case SKILL_SHADOW_WALK:
		case SKILL_CHARGING_POWER:
		case SKILL_FAST_RELOAD:
		case SKILL_QUICK_FIRE:
//		case SKILL_SMG_MASTERY:
		case SKILL_MULTI_SHOT:	
		case SKILL_HEAD_SHOT:
//		case SKILL_AR_MASTERY:
		case SKILL_PIERCING:
		case SKILL_CREATE_HOLY_WATER:
		case SKILL_LIGHT:
		case SKILL_DETECT_HIDDEN:
		case SKILL_AURA_BALL:
		case SKILL_BLESS:
		case SKILL_CONTINUAL_LIGHT:
		case SKILL_FLARE:
		case SKILL_PURIFY:
		case SKILL_AURA_RING:
		case SKILL_STRIKING:
		case SKILL_CURE_LIGHT_WOUNDS:
		case SKILL_CURE_POISON:
		case SKILL_PROTECTION_FROM_POISON:
		case SKILL_CAUSE_LIGHT_WOUNDS:
		case SKILL_CURE_SERIOUS_WOUNDS:
		case SKILL_REMOVE_CURSE:
		case SKILL_PROTECTION_FROM_CURSE:
		case SKILL_CAUSE_SERIOUS_WOUNDS:
		case SKILL_CURE_CRITICAL_WOUNDS:
		case SKILL_ACID_TOUCH:
		case SKILL_ACID_BOLT:
		case SKILL_ACID_BALL:
		case SKILL_POISONOUS_HANDS:
		case SKILL_GREEN_POISON:
		case SKILL_YELLOW_POISON:
		case SKILL_DARKBLUE_POISON:
		case SKILL_GREEN_STALKER:
		case SKILL_PARALYZE:
		case SKILL_DOOM:
		case SKILL_HIDE:
		case SKILL_DARKNESS:
		case SKILL_BLOODY_MARKER:
		case SKILL_BLOODY_TUNNEL:
		case SKILL_SNAKE_COMBO:	
		case SKILL_SWORD_WAVE:
		case SKILL_TORNADO_SEVER:
//		case SKILL_SG_MASTERY:
//		case SKILL_SR_MASTERY:
		case SKILL_AURA_SHIELD:
		case SKILL_ACID_SWAMP:
		case SKILL_INVISIBILITY:
		case SKILL_TRANSFORM_TO_WOLF:
		case SKILL_TRANSFORM_TO_BAT:
		case SKILL_SACRIFICE:
		case SKILL_DETECT_INVISIBILITY:
		case SKILL_MEDITATION:
		case SKILL_PRAYER:
		case SKILL_RESURRECT:
		case SKILL_WIND_DIVIDER:
		case SKILL_EARTHQUAKE:
		case SKILL_SEDUCTION:
		case SKILL_SNIPING:
		case SKILL_PROTECTION_FROM_ACID:
		case SKILL_BLOODY_NAIL:
		case SKILL_BLOODY_KNIFE:
		case SKILL_CAUSE_CRITICAL_WOUNDS:
		case SKILL_HURRICANE_COMBO:
//		case SKILL_CREATE_BOMB:
		case SKILL_CREATE_MINE:	
		case SKILL_INSTALL_MINE:
		case SKILL_THUNDER_BOLT:
		case SKILL_EXPANSION:
		case SKILL_BERSERKER:
		case SKILL_MOONLIGHT_SEVER:
		case SKILL_POISON_STRIKE:
		case SKILL_POISON_STORM:
		case SKILL_ACID_STRIKE:
		case SKILL_ACID_STORM:
		case SKILL_EXTREME:
		case SKILL_VISIBLE:
		case SKILL_ENERGY_DROP:
		case SKILL_VIGOR_DROP:
		case SKILL_REVEALER:
		case SKILL_CURE_ALL:
		case SKILL_BLOODY_BALL:
		case SKILL_DOUBLE_SHOT:
		case SKILL_TRIPLE_SHOT:
		case SKILL_THROW_BOMB:
		case SKILL_DEATH:
		// 2002.6.18Ãß°¡
		case SKILL_SHADOW_DANCING:
		case SKILL_SWORD_MASTERY:
		case SKILL_SHIELD_MASTERY:
		case SKILL_THUNDER_STORM:
		case SKILL_CONCENTRATION:
		case SKILL_EVASION:
		case SKILL_TYPHOON:
		case SKILL_PEACE:
		case SKILL_ACTIVATION:
		//case SKILL_EXORCISM:
		case SKILL_SANCTUARY:
//		case SKILL_REFLECTION:
		case SKILL_HYMN:
		case SKILL_TRANSFUSION:
		case SKILL_BLOODY_SPEAR:
		case SKILL_MEPHISTO:
		// 2002.6.19 Ãß°¡
		case SKILL_SUMMON_CASKET:
		case SKILL_MENTAL_SWORD:
		case SKILL_OBSERVING_EYE:
		// 2002.10.23
		case SKILL_SOUL_CHAIN:
		// 2002.11.27
		case SKILL_LIVENESS :
		// 2002.12.30
		case SKILL_SHARP_SHIELD:
		case SKILL_WIDE_LIGHTNING:
		case SKILL_GUN_SHOT_GUIDANCE:
		case SKILL_AIR_SHIELD:
		case SKILL_BULLET_OF_LIGHT:
		case SKILL_HANDS_OF_WISDOM:
		case SKILL_LIGHT_BALL:
		case SKILL_HOLY_ARROW:
		case SKILL_REBUKE:
		case SKILL_SPIRIT_GUARD:
		case SKILL_REGENERATION:
		case SKILL_POWER_OF_LAND:
		case SKILL_TURN_UNDEAD:
		// 2003. 1. 3.
		case SKILL_BLOODY_WALL:
		case SKILL_BLOODY_WAVE:
		case SKILL_BLOODY_BREAKER:
		case SKILL_METEOR_STRIKE:
		case SKILL_RAPID_GLIDING:
		// 2003. 5. 6
		case SKILL_DENIAL_MAGIC:
		case SKILL_REQUITAL:
		case SKILL_CONCEALMENT:
		case SKILL_SWORD_RAY:
		case SKILL_MULTI_AMPUTATE:
		case SKILL_NAIL_MASTERY:
		case SKILL_BLOODY_STRIKE:
		case SKILL_HALLUCINATION:
		case SKILL_HIT_CONVERT:
		case SKILL_WILD_TYPHOON:
		case SKILL_ULTIMATE_BLOW:
		case SKILL_ILLENDUE:
		case SKILL_LIGHTNESS:
		case SKILL_FLOURISH:
		case SKILL_EVADE:
		case SKILL_SHARP_ROUND:
		case SKILL_HIDE_SIGHT:
		case SKILL_BACK_STAB:
		case SKILL_BLUNTING:
		case SKILL_GAMMA_CHOP:
		case SKILL_CROSS_GUARD:
		case SKILL_KASAS_ARROW:
		case SKILL_HANDS_OF_FIRE:
		case SKILL_PROMINENCE:
		case SKILL_RING_OF_FLARE:
		case SKILL_BLAZE_BOLT:
		case SKILL_ICE_FIELD:
		case SKILL_WATER_BARRIER:
		case SKILL_HANDS_OF_NIZIE:
		case SKILL_NYMPH_RECOVERY:
		case SKILL_LIBERTY:
		case SKILL_TENDRIL:
		case SKILL_GNOMES_WHISPER:
		case SKILL_STONE_AUGER:
		case SKILL_REFUSAL_ETHER:
		case SKILL_DRIFTING_SOUL:
		case SKILL_CRITICAL_MAGIC:
		case SKILL_FIRE_OF_SOUL_STONE:
		case SKILL_ICE_OF_SOUL_STONE:
		case SKILL_SAND_OF_SOUL_STONE:
		case SKILL_BLOCK_HEAD:
		case SKILL_EARTHS_TEETH:
		case SKILL_EMISSION_WATER:
		case SKILL_BEAT_HEAD:
		case SKILL_DIVINE_SPIRITS:
		case SKILL_BLITZ_SLIDING:
		case SKILL_JABBING_VEIN:
		case SKILL_GREAT_HEAL:
		case SKILL_DIVINE_GUIDANCE:
		case SKILL_BLAZE_WALK:
		case SKILL_BLOODY_ZENITH:
		case SKILL_REDIANCE:
		case SKILL_LAR_SLASH:
		case SKILL_ARMS_MASTERY_1:
		case SKILL_ARMS_MASTERY_2:
		case SKILL_TRIDENT:
		case SKILL_HEART_CATALYST:
		case SKILL_PROTECTION_FROM_BLOOD:
		case SKILL_MOLE_SHOT:
		case SKILL_VIVID_MAGAZINE:
		case SKILL_ETERNITY:
		case SKILL_INSTALL_TRAP:
		case SKILL_HOLY_ARMOR:
		case SKILL_MERCY_GROUND:
		case SKILL_CREATE_HOLY_POTION:
		case SKILL_TRANSFORM_TO_WERWOLF:
		case SKILL_GRAY_DARKNESS:
		case SKILL_TALON_OF_CROW:
		case SKILL_STONE_SKIN:
		case SKILL_HOWL:
		case SKILL_ACID_ERUPTION:
		case SKILL_TELEPORT:
		case SKILL_FIRE_PIERCING:
		case SKILL_SUMMON_FIRE_ELEMENTAL:
		case SKILL_MAGNUM_SPEAR:
		case SKILL_HELLFIRE:
		case SKILL_ICE_LANCE:
		case SKILL_FROZEN_ARMOR:
		case SKILL_SUMMON_WATER_ELEMENTAL:
		case SKILL_EXPLOSION_WATER:
		case SKILL_SOUL_REBIRTH:
		case SKILL_SOUL_REBIRTH_MASTERY:
		case SKILL_REACTIVE_ARMOR:
		case SKILL_GROUND_BLESS:
		case SKILL_SUMMON_GROUND_ELEMENTAL:
		case SKILL_SHARP_CHAKRAM:
		case SKILL_SHIFT_BREAK:
		case SKILL_DESTRUCTION_SPEAR:
		case SKILL_FATAL_SNICK:
		case SKILL_DUCKING_WALLOP:
		case SKILL_CHARGING_ATTACK:
		case SKILL_DISTANCE_BLITZ:
		case SKILL_BLESS_FIRE:
		case SKILL_WATER_SHIELD:
		case SKILL_SAND_CROSS:
		case SKILL_METEOR_STORM:
#ifndef __CHINA_SERVER__
		// 2004.04.29
		case SKILL_FABULOUS_SOUL:
		case SKILL_WILL_OF_IRON:
		case SKILL_SWORD_OF_THOR:
		case SKILL_BURNING_SOL_CHARGING:
		case SKILL_SWEEP_VICE_1:
		case SKILL_WHITSUNTIDE:
		case SKILL_VIOLENT_PHANTOM:
		case SKILL_INSTALL_TURRET:
		case SKILL_SUMMON_GORE_GLAND:
		case SKILL_DESTRUCTION_SPEAR_MASTERY:
		case SKILL_FATAL_SNICK_MASTERY:
		case SKILL_MAGNUM_SPEAR_MASTERY:
		case SKILL_ICE_LANCE_MASTERY:
		case SKILL_REACTIVE_ARMOR_MASTERY:

		case SKILL_INFINITY_THUNDERBOLT:
		case SKILL_SPIT_STREAM:
		case SKILL_PLASMA_ROCKET_LAUNCHER:
		case SKILL_INTIMATE_GRAIL:
		case SKILL_BOMBING_STAR:
		case SKILL_SET_AFIRE:
		case SKILL_NOOSE_OF_WRAITH:
		case SKILL_SHARP_HAIL:
		case SKILL_SUMMON_MIGA:
		case SKILL_ICE_HORIZON:
		case SKILL_FURY_OF_GNOME:

//#ifdef __TEST_SERVER__
		case SKILL_HALO:
		case SKILL_DESTINIES:
		case SKILL_FIERCE_FLAME:
		case SKILL_SHADOW_OF_STORM:
		case SKILL_WILD_WOLF:
		case SKILL_ABERRATION:
		case SKILL_DRAGON_TORNADO:
		case SKILL_BIKE_CRASH:
		case SKILL_HARPOON_BOMB:
		case SKILL_PASSING_HEAL:
		case SKILL_ROTTEN_APPLE:
		// add by coffee 2007-2-18  ÐÂ¼¼ÄÜ
		case SKILL_BLLODY_SCARIFY:	   			//374  ÑªÖ®ÀÓÓ¡  (ÎüÑª¹íÐÂ¼¼ÄÜ )
		case SKILL_BLOOD_CURSE:					//375  ÑªÖ®Ô{Öä  
	//////////////////////////////////////////////////////////////////////////
	//ÈËÀà¼¼ÄÜ
		case SKILL_SHINE_SWORD:					//376  ÉÁÒ«Ö®½£
		case SKILL_BOMB_CRASH_WALK: 			//377  ¾ÞÅÚºäÕ¨
		case SKILL_SATELLITE_BOMB:	   			//378  ÎÀÐÇºä»÷
		case SKILL_ILLUSION_INVERSION:			//379  ¿Ö²À»Ã¾õ
		case SKILL_HEAVEN_GROUND:    			//380  ÌìÉñ½µÁÙ
		// add by coffee 2007-3-3	
		case SKILL_DUMMY_DRAKE:					// 382 µÂÀ×¿Ë¿þÀÜ(»ð)
		case SKILL_HYDRO_CONVERGENCE:			// 383 ¸´ºÏË®ÁÆ(Ë®)
		case SKILL_SUMMON_CLAY:					// 384 Õ³ÍÁÕÙ»½(ÍÁ)
		case SKILL_HETER_CHAKRAM:						// 385 ÏÄ²¼Àû»ùÒò(Õ½Ê¿)
                case SKILL_Sky_Fire:
                case SKILL_Cut_Storm:
                case SKILL_XRL_Missile:	
                case SKILL_Sacred_Stamp:	
                case SKILL_Bramble_Halo:	
                case SKILL_Deadly_Claw:	
                case SKILL_Voodoo_Ring:	
                case SKILL_Penetrate_Wheel:	
                case SKILL_Fire_Meteor:	
                case SKILL_Big_Rockfall:	
                case SKILL_Rapid_Freeze:	
//#endif
#endif
			break;
		////////////////////////////////////////////////////////////
		// Áö¿øµÇÁö ¾Ê´Â ±â¼ú
		////////////////////////////////////////////////////////////
		case SKILL_ARMAGEDDON:
		case SKILL_HOLY_BLAST:
		case SKILL_BLOODY_STORM:
		case SKILL_MIRACLE_SHIELD:
		case SKILL_THUNDER_FLASH:
		case SKILL_DRAGON_RISING:
		case SKILL_FIVE_STORM_CRASH:
		case SKILL_HEAVENS_SWORD:
		case SKILL_ARMAGEDDON_SLASHER:
		case SKILL_SOUL_SHOCK:
		case SKILL_SAINT_BLADE:
		case SKILL_DISARM_MINE:
		case SKILL_IDENTIFY:
		case SKILL_ENCHANT:
		case SKILL_CHAIN_AURA:
		case SKILL_SAINT_AURA:
		case SKILL_MASS_CURE:
		case SKILL_MASS_HEAL:
		case SKILL_SUMMON_WOLF:
		case SKILL_RAISING_DEAD:
		case SKILL_SUMMON_SERVANT:
		case SKILL_EXORCISM:
		case SKILL_RESTORE:
		case SKILL_INVINCIBLE:
			failpkt.setSkillType(targetSkillType);
			failpkt.setDesc(SKILL_NOT_IMPLEMENTED);
			pPlayer->sendPacket(&failpkt);
			return;
		default:
			failpkt.setSkillType(targetSkillType);
			failpkt.setDesc(SKILL_NOT_IMPLEMENTED);
			pPlayer->sendPacket(&failpkt);
			return;
	}

	// ÇÃ·¹ÀÌ¾î°¡ Á¤»óÀûÀÎ »óÅÂÀÎÁö¸¦ °Ë»çÇÑ´Ù.
	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		// NPC°¡ °¡¸£ÃÄ ÁÙ ¼ö ÀÖ´ÂÁö °Ë»çÇÑ´Ù.
		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(targetSkillType);
		Assert(pSkillInfo != NULL);

		if ( pSkillInfo->getLevel() >= 150 )
		{
			if ( !pPC->isAdvanced() )
			{
				failpkt.setSkillType(targetSkillType);
				failpkt.setDesc(NPC_LEVEL_LIMIT);
				pPlayer->sendPacket(&failpkt);
				return;
			}
			// add by Coffee Ôö¼Ó¶Ô¶þ×ª¼¼ÄÜµÄÏÞÖÆ
			switch(targetSkillType)
			{
				//////////////////////////////////////////////////////////////////////////
				// 170 ¼¶¼¼ÄÜ
				case SKILL_BLLODY_SCARIFY:	   			//374  ÑªÖ®ÀÓÓ¡  (ÎüÑª¹íÐÂ¼¼ÄÜ )
				case SKILL_BLOOD_CURSE:					//375  ÑªÖ®Ô{Öä  
					//////////////////////////////////////////////////////////////////////////
					//ÈËÀà¼¼ÄÜ
				case SKILL_SHINE_SWORD:					//376  ÉÁÒ«Ö®½£
				case SKILL_BOMB_CRASH_WALK: 			//377  ¾ÞÅÚºäÕ¨
				case SKILL_SATELLITE_BOMB:	   			//378  ÎÀÐÇºä»÷
				case SKILL_ILLUSION_INVERSION:			//379  ¿Ö²À»Ã¾õ
				case SKILL_HEAVEN_GROUND:    			//380  ÌìÉñ½µÁÙ
					// add by coffee 2007-3-3	
				case SKILL_DUMMY_DRAKE:					// 382 µÂÀ×¿Ë¿þÀÜ(»ð)
				case SKILL_HYDRO_CONVERGENCE:			// 383 ¸´ºÏË®ÁÆ(Ë®)
				case SKILL_SUMMON_CLAY:					// 384 Õ³ÍÁÕÙ»½(ÍÁ)
				case SKILL_HETER_CHAKRAM:						// 385 ÏÄ²¼Àû»ùÒò(Õ½Ê¿)
                                 case SKILL_Sky_Fire:
                                 case SKILL_Cut_Storm:
                                 case SKILL_XRL_Missile:	
                                 case SKILL_Sacred_Stamp:	
                                 case SKILL_Bramble_Halo:	
                                 case SKILL_Deadly_Claw:	
                                 case SKILL_Voodoo_Ring:	
                                 case SKILL_Penetrate_Wheel:	
                                 case SKILL_Fire_Meteor:	
                                 case SKILL_Big_Rockfall:	
                                 case SKILL_Rapid_Freeze:	
					if (pPC->isSlayer())
					{
						Slayer*           pSlayer          = dynamic_cast<Slayer*>(pPC);
						if (pSlayer->getSlayerInfo2()->getAdvancementLevel() < 20)
						{
							failpkt.setSkillType(targetSkillType);
							failpkt.setDesc(NPC_LEVEL_LIMIT);
							pPlayer->sendPacket(&failpkt);
							return;
						}
					}
					else if (pPC->isVampire())
					{
						Vampire*           pVampire          = dynamic_cast<Vampire*>(pPC);
						if (pVampire->getVampireInfo2()->getAdvancementLevel() < 20 )
						{
							failpkt.setSkillType(targetSkillType);
							failpkt.setDesc(NPC_LEVEL_LIMIT);
							pPlayer->sendPacket(&failpkt);
							return;
						}
					}
					else if (pPC->isOusters())
					{
						Ousters*           pOusters          = dynamic_cast<Ousters*>(pPC);
						if (pOusters->getOustersInfo2()->getAdvancementLevel() < 20)
						{
							failpkt.setSkillType(targetSkillType);
							failpkt.setDesc(NPC_LEVEL_LIMIT);
							pPlayer->sendPacket(&failpkt);
							return;
						}
						
					}
					break;
			}
			
		}

		// ÇÃ·¹ÀÌ¾î°¡ ½½·¹ÀÌ¾îÀÎÁö ¹ìÆÄÀÌ¾îÀÎÁö ±¸ºÐ
		if (pPC->isSlayer()) executeSlayerSkill(pPacket, pPlayer);
		else if (pPC->isVampire()) executeVampireSkill(pPacket, pPlayer);
		else if (pPC->isOusters()) executeOustersSkill(pPacket, pPlayer);
		else throw ProtocolException("CGLearnSkillHandler::execute() : Unknown player creature!");
	}
	else throw ProtocolException("CGLearnSkillHandler::execute() : Game Player Status is not NORMAL!");

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ½½·¹ÀÌ¾î ±â¼ú ½ÀµæÀ» Ã³¸®
//////////////////////////////////////////////////////////////////////////////
void CGLearnSkillHandler::executeSlayerSkill (CGLearnSkill* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ÆÐÅ¶ Á¤º¸¸¦ »Ì¾Æ³½´Ù.
	SkillType_t       targetSkillType  = pPacket->getSkillType();
	SkillDomainType_t targetDomainType = pPacket->getSkillDomainType();
	GamePlayer*       pGamePlayer      = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*         pPC              = pGamePlayer->getCreature();
	Slayer*           pSlayer          = dynamic_cast<Slayer*>(pPC);
	bool              bSuccess         = false;

	// ETC µµ¸ÞÀÎÀÇ °æ¿ì ¸ðµç µµ¸ÞÀÎ¿¡¼­ °ø¿ëÀ¸·Î ¾²ÀÌ´Â ±â¼úÀÌ´Ù.
	// ETC µµ¸ÞÀÎ ±â¼ú¿¡ ´ëÇØ¼­´Â ½½·¹ÀÌ¾îÀÇ °¡Àå ³ôÀº µµ¸ÞÀÎ ·¹º§°ú ºñ±³ÇÑ´Ù.
	SkillDomainType_t actualDomainType = targetDomainType;
	if ( actualDomainType == SKILL_DOMAIN_ETC )
		actualDomainType = pSlayer->getHighestSkillDomain();

	if (targetSkillType >= SKILL_MAX && targetSkillType < SKILL_DOUBLE_IMPACT) {

		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(PARENT_SKILL_NEED);
		pPlayer->sendPacket(&failpkt);
		return;

	}

	// ±× ±â¼úÀ» ¹è¿ï ¼ö ÀÖ´Â ·¹º§ÀÌ ÇöÀç µµ¸ÞÀÎÀÇ ·¹º§ º¸´Ù ³·´Ù¸é ±â¼úÀ» ¹è¿ï ¼ö ÀÖ´Ù.
	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(targetSkillType);

//check skill type ,modified by chengh 2006 06 14
	if  (pSkillInfo->getType() != SKILL_SOUL_CHAIN  && (pSkillInfo->getDomainType()!=actualDomainType || actualDomainType>SKILL_DOMAIN_ETC)){
		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(DOMAIN_DIFFER);
		pPlayer->sendPacket(&failpkt);
		filelog("learnSkillError.txt","slayer domain error,player is %s,skill is :%s",pSlayer->getName().c_str(),pSkillInfo->getName().c_str());
		return;
		}


	
//	if (pSkillInfo->getLevel() <= pSlayer->getSkillDomainLevel(pSkillInfo->getDomainType())) bSuccess = true;
	if (pSkillInfo->getLevel() <= pSlayer->getSkillDomainLevel(actualDomainType)) bSuccess = true;

	// ±â¼úÀ» ¹è¿ï¼ö ÀÖ´Â °æÇèÄ¡°¡ ¾Æ´Ï¸é ¹è¿ï ¼ö ¾ø´Ù. ·¹º§ÀÌ ÀÌ»óÀÌ ÀÖÀ» °æ¿ì¸¦ ´ëºñÇØ °æÇèÄ¡µµ Ã¼Å©ÇÑ´Ù.
	// ETC µµ¸ÞÀÎÀÏ °æ¿ì ¿¹¿Ü·Î Ã³¸®ÇÑ´Ù.
	if ( targetDomainType != SKILL_DOMAIN_ETC )
//		if (pSlayer->getSkillDomainExp(pSkillInfo->getDomainType())
//				>= g_pSkillDomainInfoManager->getDomainInfo((SkillDomain)pSkillInfo->getDomainType(), (Level_t)max(0, (int)pSkillInfo->getLevel() - 1))->getAccumExp())
		if ( pSlayer->getSkillDomainLevel(pSkillInfo->getDomainType()) >= pSkillInfo->getLevel() ) bSuccess = true;

	if ( pSlayer->hasSkill( targetSkillType ) )
	{
		GCSystemMessage gcSM;
		gcSM.setMessage( g_pStringPool->getString(STRID_ALREAY_LEARN_SKILL) );
		pPlayer->sendPacket( &gcSM );
	}

	else
	// ¼º°ø ¿©ºÎ¸¦ Ã¼Å©ÇØ¼­ ¾Ë¸ÂÀº ÆÐÅ¶À» ³¯¸°´Ù.
	if (bSuccess)
	{
		// ±â¼úÀ» ´õÇÏ°í...
		pSlayer->addSkill(targetSkillType);
		
		// ±â¼ú ¹è¿ü´Ù°í ÆÐÅ¶ ³¯·ÁÁØ´Ù.
		GCLearnSkillOK okpkt;
		okpkt.setSkillType(targetSkillType);
		okpkt.setSkillDomainType(targetDomainType);
		pPlayer->sendPacket (&okpkt);

		// ÀÏºÎ ½ºÅ³µéÀº ´É·ÂÄ¡ °ü·Ã °ªµéÀÌ ¹Ù·Î º¯ÇÑ´Ù.
		switch (targetSkillType)
		{
			case SKILL_SWORD_MASTERY :
			case SKILL_SHIELD_MASTERY:
			case SKILL_SMG_MASTERY:
			case SKILL_SG_MASTERY:
			case SKILL_SR_MASTERY:
			case SKILL_AR_MASTERY:
			case SKILL_ARMS_MASTERY_1:
			case SKILL_ARMS_MASTERY_2:
			case SKILL_CONCENTRATION:
			case SKILL_EVASION:
			case SKILL_LIVENESS:
			case SKILL_FABULOUS_SOUL:
			case SKILL_WILL_OF_IRON:
			{
				SLAYER_RECORD prev;

				pSlayer->getSlayerRecord(prev);
				pSlayer->initAllStat();
				pSlayer->sendRealWearingInfo();
				pSlayer->sendModifyInfo(prev);
			}
			break;
		}
	}
	else
	{
		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(PARENT_SKILL_NEED);
		pPlayer->sendPacket(&failpkt);
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¹ìÆÄÀÌ¾î ±â¼ú ½ÀµæÀ» Ã³¸®
//////////////////////////////////////////////////////////////////////////////
void CGLearnSkillHandler::executeVampireSkill (CGLearnSkill* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ÆÐÅ¶ Á¤º¸¸¦ »Ì¾Æ³½´Ù.
	SkillType_t       targetSkillType  = pPacket->getSkillType();
	SkillDomainType_t targetDomainType = pPacket->getSkillDomainType();

	// ÆÐÅ¶¿¡¼­ »Ì¾Æ³½ Á¤º¸¸¦ °¡°ø
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Vampire*    pVampire    = dynamic_cast<Vampire*>(pPC);
	bool        bSuccess    = false;

	// ±× ±â¼úÀ» ¹è¿ï ¼ö ÀÖ´Â ·¹º§ÀÌ ÇöÀç ·¹º§ º¸´Ù ³·´Ù¸é ±â¼úÀ» ¹è¿ï ¼ö ÀÖ´Ù.
	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(targetSkillType);

//check skill type ,modified by chengh 2006 06 14
	if (pSkillInfo->getType() != SKILL_SOUL_CHAIN  && (pSkillInfo->getDomainType()!=targetDomainType || targetDomainType!=SKILL_DOMAIN_VAMPIRE)){
		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(DOMAIN_DIFFER);
		pPlayer->sendPacket(&failpkt);
		filelog("learnSkillError.txt","vampire domain error,player is %s,skill is:%s",pVampire->getName().c_str(),pSkillInfo->getName().c_str());
		return;
		}


	
	if (pSkillInfo->getLevel() <= pVampire->getLevel()) bSuccess = true;

	// ¼º°ø ¿©ºÎ¸¦ Ã¼Å©ÇØ¼­ ¾Ë¸ÂÀº ÆÐÅ¶À» ³¯¸°´Ù.
	if (bSuccess) 
	{
		pVampire->addSkill(targetSkillType);

		GCLearnSkillOK okpkt;
		okpkt.setSkillType(targetSkillType);
		okpkt.setSkillDomainType(targetDomainType);
		pPlayer->sendPacket (&okpkt);
	} 
	else 
	{
		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(PARENT_SKILL_NEED);
		pPlayer->sendPacket(&failpkt);
	}

	switch ( targetSkillType )
	{
		case SKILL_NAIL_MASTERY:
		{
			VAMPIRE_RECORD prev;

			pVampire->getVampireRecord( prev );
			pVampire->initAllStat();
			pVampire->sendRealWearingInfo();
			pVampire->sendModifyInfo( prev );
		}
			break;

		default :
			break;
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

void CGLearnSkillHandler::executeOustersSkill(CGLearnSkill* pPacket, Player* pPlayer)
	
{
	__BEGIN_DEBUG_EX __BEGIN_TRY
#ifdef __GAME_SERVER__

	// ÆÐÅ¶ Á¤º¸¸¦ »Ì¾Æ³½´Ù.
	SkillType_t       targetSkillType  = pPacket->getSkillType();
	SkillDomainType_t targetDomainType = pPacket->getSkillDomainType();

	// ÆÐÅ¶¿¡¼­ »Ì¾Æ³½ Á¤º¸¸¦ °¡°ø
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Ousters*    pOusters    = dynamic_cast<Ousters*>(pPC);

	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(targetSkillType);


//check skill type ,modified by chengh 2006 06 14
	if (pSkillInfo->getType() != SKILL_SOUL_CHAIN  && (pSkillInfo->getDomainType()!=targetDomainType || targetDomainType!=SKILL_DOMAIN_OUSTERS)){
		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(DOMAIN_DIFFER);
		pPlayer->sendPacket(&failpkt);
		filelog("learnSkillError.txt","ousters domain error,player is: %s,skill is: %s",pOusters->getName().c_str(),pSkillInfo->getName().c_str());
		return;
		}

	
	if (pSkillInfo->getLevel() > pOusters->getLevel())
	{
		GCLearnSkillFailed failpkt; 
		failpkt.setSkillType(targetSkillType);;
		failpkt.setDesc(PARENT_SKILL_NEED);
		pPlayer->sendPacket(&failpkt);
		return;
	}

	OustersSkillSlot* pOustersSkillSlot = pOusters->hasSkill( targetSkillType );

	if ( pOustersSkillSlot != NULL )
	{
		////////////////////////////////////////
		// ½ºÅ³ÀÇ ·¹º§ ¾÷ÀÌ´Ù.
		////////////////////////////////////////
		int LevelUpPoint = pSkillInfo->getLevelUpPoint();

		if ( LevelUpPoint==0 || pOusters->getSkillBonus() < LevelUpPoint || pOustersSkillSlot->getExpLevel() >= 30 )
		{
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(targetSkillType);;
			failpkt.setDesc(NPC_LEVEL_LIMIT);
			pPlayer->sendPacket(&failpkt);

			return;
		}

		pOusters->setSkillBonus( pOusters->getSkillBonus() - LevelUpPoint );
		char query[50];
		sprintf(query, "SkillBonus = %u", pOusters->getSkillBonus() );
		pOusters->tinysave( query );

		GCModifyInformation gcMI;
		gcMI.addShortData( MODIFY_SKILL_BONUS_POINT, pOusters->getSkillBonus() );
		pPlayer->sendPacket( &gcMI );

		pOustersSkillSlot->setExpLevel( pOustersSkillSlot->getExpLevel() + 1 );
		pOustersSkillSlot->save();

		GCLearnSkillOK okpkt;
		okpkt.setSkillType(targetSkillType);
		okpkt.setSkillDomainType(targetDomainType);
		pPlayer->sendPacket (&okpkt);

		switch ( targetSkillType )
		{
			case SKILL_HIDE_SIGHT:
			{
				OUSTERS_RECORD prev;

				pOusters->getOustersRecord( prev );
				pOusters->initAllStat();
				pOusters->sendRealWearingInfo();
				pOusters->sendModifyInfo( prev );
			}
				break;

			default :
				break;
		}
	}
	else
	{
		if ( !CheckRequiredSkill( pSkillInfo, pOusters, pSkillInfo->getElementalDomain() ) )
		{
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(targetSkillType);;
			failpkt.setDesc(PARENT_SKILL_NEED);
			pPlayer->sendPacket(&failpkt);

			return;
		}

		int SkillPoint = pSkillInfo->getSkillPoint();
		if ( pOusters->getSkillBonus() < SkillPoint || !pOusters->canLearnSkill(targetSkillType) )
		{
			GCLearnSkillFailed failpkt; 
			failpkt.setSkillType(targetSkillType);;
			failpkt.setDesc(NPC_LEVEL_LIMIT);
			pPlayer->sendPacket(&failpkt);

			return;
		}

		pOusters->setSkillBonus( pOusters->getSkillBonus() - SkillPoint );
		char query[50];

		sprintf(query, "SkillBonus = %u", pOusters->getSkillBonus() );
		pOusters->tinysave( query );

		GCModifyInformation gcMI;
		gcMI.addShortData( MODIFY_SKILL_BONUS_POINT, pOusters->getSkillBonus() );
		pPlayer->sendPacket( &gcMI );

		pOusters->addSkill( targetSkillType );
		GCLearnSkillOK okpkt;
		okpkt.setSkillType(targetSkillType);
		okpkt.setSkillDomainType(targetDomainType);
		pPlayer->sendPacket (&okpkt);

		switch ( targetSkillType )
		{
			case SKILL_HIDE_SIGHT:
			case SKILL_FIRE_OF_SOUL_STONE:
			case SKILL_ICE_OF_SOUL_STONE:
			case SKILL_SAND_OF_SOUL_STONE:
			case SKILL_BLOCK_HEAD:
			{
				OUSTERS_RECORD prev;

				pOusters->getOustersRecord( prev );
				pOusters->initAllStat();
				pOusters->sendRealWearingInfo();
				pOusters->sendModifyInfo( prev );
			}
				break;

			default :
				break;
		}
	}
	
#endif
	__END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__

// ¾Æ¿ì½ºÅÍÁîÀÇ ½ºÅ³¸Ê¿¡¼­ ÀÌ ½ºÅ³À» ¹è¿ì±â À§ÇØ ÇÊ¿äÇÑ ½ºÅ³À» Ã¼Å©ÇÑ´Ù.
bool CheckRequiredSkill(SkillInfo* pSkillInfo, Ousters* pOusters, int domain)
{

	if ( pSkillInfo->getType() == SKILL_SOUL_CHAIN )
	{
		if ( pOusters->getLevel() >= 100 )
			return true;
		else
			return false;
	}

	const list<SkillType_t>& RequiredSkills = pSkillInfo->getRequireSkills();

	// ÇÊ¿äÇÑ ½ºÅ³ÀÌ ¾øÀ¸¸é ¹«Á¶°Ç..
	if ( RequiredSkills.empty() ) return true;

	list<SkillType_t>::const_iterator itr = RequiredSkills.begin();
	list<SkillType_t>::const_iterator endItr = RequiredSkills.end();

	// ÇÊ¿äÇÑ ½ºÅ³Áß¿¡ ÇÏ³ª¶óµµ ÀÖÀ¸¸é µÈ´Ù.
	for ( ; itr != endItr ; ++itr )
	{
		// ÇÊ¿äÇÑ ½ºÅ³ÀÌ ETC µµ¸ÞÀÎÀÏ °æ¿ì, ¾î´ÀÂÊ ½ºÅ³¸Ê¿¡¼­ ¹è¿î°ÇÁö Ã¼Å©ÇØ¾ß ÇÑ´Ù.
		SkillInfo* pParentSkillInfo = g_pSkillInfoManager->getSkillInfo( *itr );
		if ( pParentSkillInfo->getElementalDomain() == ELEMENTAL_DOMAIN_ETC )
		{
			if ( !CheckRequiredSkill(pParentSkillInfo, pOusters, domain ) ) continue;
		}
		// ÇÊ¿äÇÑ ½ºÅ³ÀÌ ¹è¿ï ½ºÅ³°ú °°Àº ½ºÅ³ ¸Ê¿¡ ÀÖÁö ¾ÊÀ» °æ¿ì¿£ Ã¼Å©ÇØÁÖ¸é ¾ÈµÈ´Ù.
		else if ( domain != ELEMENTAL_DOMAIN_ETC && getSkillMapID((ElementalDomain)pParentSkillInfo->getElementalDomain()) != getSkillMapID((ElementalDomain)domain) ) continue;

		if ( pOusters->hasSkill(*itr) != NULL )
		{
			return true;
		}
	}

	return false;
}

int getSkillMapID(ElementalDomain domain)
{
	switch ( domain )
	{
		case ELEMENTAL_DOMAIN_FIRE:
		case ELEMENTAL_DOMAIN_WATER:
		case ELEMENTAL_DOMAIN_EARTH:
		case ELEMENTAL_DOMAIN_WIND:
			return 1;
		case ELEMENTAL_DOMAIN_COMBAT:
		case ELEMENTAL_DOMAIN_ELEMENTAL_COMBAT:
			return 0;
		default:
			return -1;
	}
}

#endif
