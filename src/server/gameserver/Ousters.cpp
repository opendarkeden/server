//////////////////////////////////////////////////////////////////////////////
// Filename    : Ousters.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Ousters.h"
#include "Player.h"
#include "OptionInfo.h"
#include "SkillInfo.h"
#include "ItemLoaderManager.h"
#include "EffectLoaderManager.h"
#include "SkillParentInfo.h"
#include "DB.h"
#include "ItemInfoManager.h"
#include "AbilityBalance.h"
#include "Stash.h"
#include "TradeManager.h"
#include "CreatureUtil.h"
#include "FlagSet.h"
#include "OustersEXPInfo.h"
#include "Party.h"
#include "ItemUtil.h"
#include "PacketUtil.h"
#include "SkillUtil.h"
#include "Shape.h"
#include "GamePlayer.h"
//#include "RankEXPInfo.h"
#include "RankExpTable.h"
#include "VariableManager.h"
#include "WarSystem.h"
#include "ResurrectLocationManager.h"
#include "PKZoneInfoManager.h"
#include "TimeLimitItemManager.h"
#include <stdio.h>

#include "item/AR.h"
#include "item/SR.h"
#include "item/SG.h"
#include "item/SMG.h"
#include "item/Belt.h"
#include "item/Skull.h"
#include "item/OustersWristlet.h"
#include "item/OustersStone.h"
#include "item/OustersArmsband.h"

#include "skill/EffectBless.h"
#include "skill/EffectParalyze.h"
#include "skill/EffectDoom.h"
#include "skill/EffectTransformToWolf.h"
#include "skill/EffectTransformToBat.h"
#include "EffectGrandMasterOusters.h"
#include "RaceWarLimiter.h"

#include "GCModifyInformation.h"
#include "GCChangeShape.h"
#include "GCSkillInfo.h"
#include "GCRealWearingInfo.h"
#include "GCStatusCurrentHP.h"
#include "GCTakeOff.h"
#include "GCOtherModifyInfo.h"
#include "GCPetStashList.h"

#include "MonsterInfo.h"
#include "CastleSkillInfo.h"
#include "skill/OustersCastleSkillSlot.h"
#include "GuildUnion.h"
#include "Store.h"
#include "AdvancementClassExpTable.h"
#include "DynamicZone.h"

#include "SystemAvailabilitiesManager.h"

const Color_t UNIQUE_COLOR = 0xFFFF;
const Color_t QUEST_COLOR = 0xFFFE;

const Level_t MAX_OUSTERS_LEVEL = 150;

Ousters::Ousters () 
	 
: PlayerCreature(0, NULL)
{
	__BEGIN_TRY

	m_CClass = CREATURE_CLASS_OUSTERS;

	m_Mutex.setName("Ousters");

	// AttackMelee °°Àº ±âº» °ø°ÝÀ» Áý¾î³Ö¾îÁØ´Ù.
	for (int i=0; i<SKILL_DOUBLE_IMPACT; i++)
	{
		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;
		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(i);
		pOustersSkillSlot->setInterval(5);
		pOustersSkillSlot->setRunTime();

		addSkill(pOustersSkillSlot);
	}

	//////////////////////////////////////
	// ±âº» ½ºÅ³
	//////////////////////////////////////
	{
		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;
		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(SKILL_ABSORB_SOUL);
		pOustersSkillSlot->setExpLevel(1);
		pOustersSkillSlot->setInterval(5);
		pOustersSkillSlot->setRunTime();

		addSkill(pOustersSkillSlot);
	}
	{
		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;
		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(SKILL_SUMMON_SYLPH);
		pOustersSkillSlot->setExpLevel(1);
		pOustersSkillSlot->setInterval(5);
		pOustersSkillSlot->setRunTime();

		addSkill(pOustersSkillSlot);
	}

    for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
        m_pWearItem[i] = NULL;

	getCurrentTime(m_MPRegenTime);

	// °æÇèÄ¡ ¼¼ÀÌºê Ä«¿îÆ® ÃÊ±âÈ­
//	m_RankExpSaveCount		= 0;
	m_ExpSaveCount			= 0;
	m_FameSaveCount			= 0;
	m_AlignmentSaveCount	= 0;

	__END_CATCH
}

Ousters::~Ousters() 
    
{
	__BEGIN_TRY

	// º¹Àå Á¤º¸¸¦ »ý¼ºÇØµÐ´Ù. by sigi. 2002.6.18
	char pField[128];
	sprintf(pField, "CoatType=%d,ArmType=%d,CoatColor=%d,ArmColor=%d,BootsColor=%d",
					m_OustersInfo.getCoatType(),
					m_OustersInfo.getArmType(),
					m_OustersInfo.getCoatColor(),
					m_OustersInfo.getArmColor(),
					m_OustersInfo.getBootsColor() );

	tinysave(pField);

	// ¶³¾îÁø ¾ÆÀÌÅÛÀÇ ³»±¸¼º°ú °æÇèÄ¡, ¼ºÇâ µîÀ» ÀúÀåÇÑ´Ù.
	saveGears();
	saveExps();
	saveSkills();

	// ÀÔ°í ÀÖ´Â ¾ÆÀÌÅÛÀ» ¸Þ¸ð¸®¿¡¼­ »èÁ¦ÇÑ´Ù.
	destroyGears();

	// Å¬·¡½º°¡ »èÁ¦µÉ °æ¿ì, ÇØ´çÇÏ´Â ±³È¯ Á¤º¸¸¦ »èÁ¦ÇØ¾ß ÇÔÀº ¹°·Ð,
	// ±³È¯ »ó´ë¿¡°Ôµµ ÀÌ »ç½ÇÀ» ¾Ë·ÁÁà¾ß ÇÑ´Ù.
	TradeManager* pTradeManager = m_pZone->getTradeManager();
	TradeInfo* pInfo = pTradeManager->getTradeInfo(getName());
	if (pInfo != NULL)
	{
		// ±³È¯ Á¤º¸¸¦ »èÁ¦
		pTradeManager->cancelTrade(this);
	}

	// ±Û·Î¹ú ÆÄÆ¼ Á¤º¸¸¦ »èÁ¦ÇÑ´Ù. 
	// ÀÏ¹ÝÀûÀÎ ·Î±×¾Æ¿ôÀÇ °æ¿ì¿¡´Â
	// CGLogoutHandler¿¡¼­ Zone::deleteCreature() ÇÔ¼ö¸¦ ºÎ¸£°Ô µÇ°í,
	// ºñÁ¤»óÀûÀÎ °æ¿ì¶ó°í ÇØµµ, 
	// GamePlayer::disconnect()¿¡¼­ Zone::deleteCreature() ÇÔ¼ö¸¦ ºÎ¸£°Ô µÇ¹Ç·Î,
	// ·ÎÄÃ ÆÄÆ¼ ¹× ÆÄÆ¼ ÃÊ´ë, Æ®·¹ÀÌµå Á¤º¸¸¦ °ÆÁ¤ÇÒ ÇÊ¿ä´Â ¾ø´Ù.
	deleteAllPartyInfo(this);

	// ±â¼úµéÀ» »èÁ¦
	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		OustersSkillSlot* pOustersSkillSlot = itr->second;
		SAFE_DELETE(pOustersSkillSlot);
	}

	__END_CATCH
}

// registerObject
// Zone¿¡ Á¾¼ÓµÈ ObjectRegistry¸¦ »ç¿ëÇØ¼­, Ousters ¿Í ¼ÒÀ¯¾ÆÀÌÅÛµéÀÇ
// ObjectID¸¦ ÇÒ´ç¹Þ´Â´Ù.
void Ousters::registerObject ()
    
{
    __BEGIN_TRY

    Assert(getZone() != NULL);

    // zone ÀÇ object registery ¿¡ Á¢±ÙÇÑ´Ù.
    ObjectRegistry & OR = getZone()->getObjectRegistry();

    __ENTER_CRITICAL_SECTION(OR)

	// ¸ðµç ¾ÆÀÌÅÛ¿¡ OID °¡ ¹Ù²î¹Ç·Î ½Ã°£Á¦ÇÑ ¾ÆÀÌÅÛ ¸Å´ÏÀú¿¡¼­ OID ¸ÊÀ» Áö¿öÁà¾ß ÇÑ´Ù.
	if (m_pTimeLimitItemManager != NULL)
		m_pTimeLimitItemManager->clear();

	// ¿ì¼± ¾Æ¿ì½ºÅÍ½ºÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	OR.registerObject_NOLOCKED(this);

	// ÀÎº¥Åä¸®ÀÇ ¾ÆÀÌÅÛµéÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	registerInventory(OR);

	// Goods InventoryÀÇ ¾ÆÀÌÅÛµéÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	registerGoodsInventory(OR);

	// ÀåÂøÇÏ°í ÀÖ´Â ¾ÆÀÌÅÛµéÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			bool bCheck = true;

			// ¾ç¼Õ ¹«±âÀÏ °æ¿ì, WEAR_LEFTHAND ¿¡¼­ µî·ÏÇßÀ¸¹Ç·Î,
			// ¶Ç µî·ÏÇÒ ÇÊ¿ä´Â ¾ø´Ù.
			if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				bCheck = false;

			if (bCheck) registerItem(pItem, OR);
		}
	}

	// ¸¶¿ì½º¿¡ µé°í ÀÖ´Â ¾ÆÀÌÅÛÀÇ OID¸¦ µî·Ï ¹Þ´Â´Ù.
	Item* pSlotItem = m_pExtraInventorySlot->getItem();
	if (pSlotItem != NULL) registerItem(pSlotItem, OR);

	m_Garbage.registerObject(OR);

	for ( int i=0; i<MAX_PET_STASH; ++i )
	{
		Item* pItem = getPetStashItem(i);
		if ( pItem != NULL ) registerItem( pItem, OR );
	}

    __LEAVE_CRITICAL_SECTION(OR)

	m_OustersInfo.setObjectID(m_ObjectID);
	m_pStore->updateStoreInfo();

    __END_CATCH
}

// Zone¿¡ Á¾¼ÓµÈ ObjectRegistry¸¦ »ç¿ëÇØ¼­, Ousters ¿Í ¼ÒÀ¯¾ÆÀÌÅÛµéÀÇ
// ObjectID¸¦ ÇÒ´ç¹Þ´Â´Ù. ItemTrace ¸¦ ³²±æÁö ¿©ºÎ °áÁ¤À» À§ÇØ µû·Î »°´Ù
void Ousters::registerInitObject ()
    
{
    __BEGIN_TRY

    Assert(getZone() != NULL);

    // zone ÀÇ object registery ¿¡ Á¢±ÙÇÑ´Ù.
    ObjectRegistry & OR = getZone()->getObjectRegistry();

    __ENTER_CRITICAL_SECTION(OR)

	// ¸ðµç ¾ÆÀÌÅÛ¿¡ OID °¡ ¹Ù²î¹Ç·Î ½Ã°£Á¦ÇÑ ¾ÆÀÌÅÛ ¸Å´ÏÀú¿¡¼­ OID ¸ÊÀ» Áö¿öÁà¾ß ÇÑ´Ù.
	if (m_pTimeLimitItemManager != NULL)
		m_pTimeLimitItemManager->clear();

	// ¿ì¼± ¾Æ¿ì½ºÅÍ½ºÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	OR.registerObject_NOLOCKED(this);

	// ÀÎº¥Åä¸®ÀÇ ¾ÆÀÌÅÛµéÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	registerInitInventory(OR);

	// Goods InventoryÀÇ ¾ÆÀÌÅÛµéÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	registerGoodsInventory(OR);

	// ÀåÂøÇÏ°í ÀÖ´Â ¾ÆÀÌÅÛµéÀÇ OID¸¦ µî·Ï¹Þ´Â´Ù.
	for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			// ItemTrace ¸¦ ³²±æ °ÍÀÎÁö °áÁ¤
			pItem->setTraceItem( bTraceLog( pItem ) );

			bool bCheck = true;

			// ¾ç¼Õ ¹«±âÀÏ °æ¿ì, WEAR_LEFTHAND ¿¡¼­ µî·ÏÇßÀ¸¹Ç·Î,
			// ¶Ç µî·ÏÇÒ ÇÊ¿ä´Â ¾ø´Ù.
			if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				bCheck = false;

			if (bCheck) registerItem(pItem, OR);
		}
	}

	// ¸¶¿ì½º¿¡ µé°í ÀÖ´Â ¾ÆÀÌÅÛÀÇ OID¸¦ µî·Ï ¹Þ´Â´Ù.
	Item* pSlotItem = m_pExtraInventorySlot->getItem();
	if (pSlotItem != NULL)
	{
		// ItemTrace ¸¦ ³²±æ °ÍÀÎÁö °áÁ¤
		pSlotItem->setTraceItem( bTraceLog( pSlotItem ) );
		registerItem(pSlotItem, OR);
	}

	m_Garbage.registerObject(OR);

    __LEAVE_CRITICAL_SECTION(OR)

	m_OustersInfo.setObjectID(m_ObjectID);

    __END_CATCH
}

// ½Ã°£Á¦ÇÑ ¾ÆÀÌÅÛÀ» Ã¼Å©ÇÑ´Ù.
// ¸ðµç ¾ÆÀÌÅÛÀÌ ÀÌ¹Ì register µÇ¾îÀÖ¾î¾ß ÇÑ´Ù.
void Ousters::checkItemTimeLimit() 
{
	__BEGIN_TRY

	// ÀÎº¥Åä¸®¿¡¼­ Ã£´Â´Ù.
	{
		list<Item*> ItemList;
		int height = m_pInventory->getHeight();
		int width  = m_pInventory->getWidth();

		for (int j=0; j<height; j++)
		{
			for (int i=0; i<width; i++)
			{
				Item* pItem = m_pInventory->getItem(i, j);
				if (pItem != NULL)
				{
					// Ã¼Å©µÈ ¾ÆÀÌÅÛÀÇ ¸®½ºÆ®¿¡¼­ ÇöÀç ¾ÆÀÌÅÛÀ» Ã£´Â´Ù.
					list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

					if (itr == ItemList.end())
					{
						i += pItem->getVolumeWidth() - 1;

						if ( wasteIfTimeLimitExpired( pItem ) )
						{
							m_pInventory->deleteItem( pItem->getObjectID() );
							SAFE_DELETE( pItem );
						}
						else
						{
							// ¸®½ºÆ®¿¡ ¾ÆÀÌÅÛÀÌ ¾øÀ¸¸é
							// °°Àº ¾ÆÀÌÅÛÀ» µÎ¹ø Ã¼Å©ÇÏÁö ¾Ê±â À§ÇØ¼­
							// ¸®½ºÆ®¿¡´Ù°¡ ¾ÆÀÌÅÛÀ» Áý¾î³Ö´Â´Ù.
							ItemList.push_back(pItem);
						}
					}
				}
			}
		}
	}

	// ÀåÂøÇÏ°í ÀÖ´Â °Í Áß¿¡ Ã£´Â´Ù.
	{
		for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
		{
			Item* pItem = m_pWearItem[i];

			if (pItem != NULL) 
			{
				bool bCheck = true;

				// ¾ç¼Õ ¹«±âÀÏ °æ¿ì, WEAR_LEFTHAND ¿¡¼­ µî·ÏÇßÀ¸¹Ç·Î,
				// ¶Ç µî·ÏÇÒ ÇÊ¿ä´Â ¾ø´Ù.
				if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
					bCheck = false;

				if (bCheck) 
				{
					if ( wasteIfTimeLimitExpired( pItem ) )
					{
						deleteWearItem( (WearPart)i );
						if ( i == WEAR_LEFTHAND && isTwohandWeapon(pItem) )
							deleteWearItem( WEAR_RIGHTHAND );
						SAFE_DELETE( pItem );
					}
				}
			}
		}
	}

	// ¸¶¿ì½º¿¡ µé°í ÀÖ´Â ¾ÆÀÌÅÛÀ» Ã¼Å©ÇÑ´Ù.
	{
		Item* pSlotItem = m_pExtraInventorySlot->getItem();
		if (pSlotItem != NULL && wasteIfTimeLimitExpired( pSlotItem ))
		{
			deleteItemFromExtraInventorySlot();
			SAFE_DELETE( pSlotItem );
		}
	}

	__END_CATCH
}

void Ousters::updateEventItemTime( DWORD time ) 
{
	__BEGIN_TRY

	// ÀÎº¥Åä¸®¿¡¼­ Ã£´Â´Ù.
	{
		list<Item*> ItemList;
		int height = m_pInventory->getHeight();
		int width  = m_pInventory->getWidth();

		for (int j=0; j<height; j++)
		{
			for (int i=0; i<width; i++)
			{
				Item* pItem = m_pInventory->getItem(i, j);
				if (pItem != NULL)
				{
					// Ã¼Å©µÈ ¾ÆÀÌÅÛÀÇ ¸®½ºÆ®¿¡¼­ ÇöÀç ¾ÆÀÌÅÛÀ» Ã£´Â´Ù.
					list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

					if (itr == ItemList.end())
					{
						i += pItem->getVolumeWidth() - 1;
						updateItemTimeLimit( pItem, time );
						// ¸®½ºÆ®¿¡ ¾ÆÀÌÅÛÀÌ ¾øÀ¸¸é
						// °°Àº ¾ÆÀÌÅÛÀ» µÎ¹ø Ã¼Å©ÇÏÁö ¾Ê±â À§ÇØ¼­
						// ¸®½ºÆ®¿¡´Ù°¡ ¾ÆÀÌÅÛÀ» Áý¾î³Ö´Â´Ù.
						ItemList.push_back(pItem);
					}
				}
			}
		}
	}

	// ÀåÂøÇÏ°í ÀÖ´Â °Í Áß¿¡ Ã£´Â´Ù.
	{
		for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
		{
			Item* pItem = m_pWearItem[i];

			if (pItem != NULL) 
			{
				bool bCheck = true;

				// ¾ç¼Õ ¹«±âÀÏ °æ¿ì, WEAR_LEFTHAND ¿¡¼­ µî·ÏÇßÀ¸¹Ç·Î,
				// ¶Ç µî·ÏÇÒ ÇÊ¿ä´Â ¾ø´Ù.
				if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
					bCheck = false;

				if (bCheck) 
				{
					updateItemTimeLimit( pItem, time );
				}
			}
		}
	}

	// ¸¶¿ì½º¿¡ µé°í ÀÖ´Â ¾ÆÀÌÅÛÀ» Ã¼Å©ÇÑ´Ù.
	{
		Item* pSlotItem = m_pExtraInventorySlot->getItem();
		if (pSlotItem != NULL)
		{
			updateItemTimeLimit( pSlotItem, time );
		}
	}

	__END_CATCH
}

///////////////////////////////////////////
//	Ousters¿Í Slayer»çÀÌÀÇ º¯½ÅÀ» À§ÇØ¼­
//	¾ÆÅÛ ·ÎµùÀº µû·Î Ã³¸®ÇÑ´Ù.
//
void Ousters::loadItem( bool checkTimeLimit )
	
{
	__BEGIN_TRY

	PlayerCreature::loadItem();

    // ÀÎº¥Åä¸®¸¦ »ý¼ºÇÑ´Ù.
	SAFE_DELETE(m_pInventory);
	m_pInventory = new Inventory(10, 6);
	m_pInventory->setOwner(getName());

	// ¾ÆÀÌÅÛÀ» ·ÎµåÇÑ´Ù.
	g_pItemLoaderManager->load(this);

	PlayerCreature::loadGoods();

	// ·ÎµåÇÑ ¾ÆÀÌÅÛµéÀ» µî·Ï½ÃÅ°°í
    registerInitObject();

	// Ã³À½ Á¢¼ÓÇÑ »ç¶÷ÀÏ °æ¿ì ÃÊº¸ÀÚ¿ë ¾ÆÀÌÅÛ¼¼Æ®¸¦ ÀÏ´Ü ÁØ ´ÙÀ½..
	if( !m_pFlagSet->isOn( FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO ) )
	{
		addNewbieItemToInventory( this );
		addNewbieGoldToInventory( this );
		addNewbieItemToGear( this );
		// ÁÖ¾úÀ» °æ¿ì Áá´Ù´Â ÇÃ·¡±×¸¦ ²¨ÁØ´Ù.
		m_pFlagSet->turnOn( FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO );
		m_pFlagSet->save( getName() );
	}

	if ( checkTimeLimit )
	{
		checkItemTimeLimit();
	}

	// ÀÔ°í ÀÖ´Â ¿Ê¿¡ µû¶ó ´É·ÂÄ¡¸¦ °è»êÇØÁØ´Ù.
	initAllStat();

	__END_CATCH
}


//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::load ()
	
{
	__BEGIN_TRY

	if ( !PlayerCreature::load() ) return false;

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
			"SELECT Name, AdvancementClass, AdvancementGoalExp, Sex,MasterEffectColor,\
			STR, DEX, INTE, HP, CurrentHP, MP, CurrentMP, Fame, \
			GoalExp, Level, Bonus, SkillBonus, Gold, GuildID, \
			ZoneID, XCoord, YCoord, Sight, Alignment,\
			StashGold, StashNum, Competence, CompetenceShape, ResurrectZone, SilverDamage, SMSCharge,\
			`Rank`, RankGoalExp, HairColor FROM Ousters WHERE Name = '%s' AND Active = 'ACTIVE'",
			m_Name.c_str()
		);

		if (pResult->getRowCount() == 0) 
		{
			//throw Error("Critical Error : data intergrity broken. (·Î±×ÀÎ ¼­¹ö¿¡¼­ °ÔÀÓ ¼­¹ö·Î ³Ñ¾î¿À´Â µ¿¾È¿¡ Ä³¸¯ÅÍ°¡ »èÁ¦µÇ¾ú½À´Ï´Ù.)");
			SAFE_DELETE(pStmt);
			return false;
		}

		pResult->next();

		uint i = 0;

		setName(pResult->getString(++i));

		Level_t advLevel = pResult->getInt(++i);
		Exp_t	advGoalExp = pResult->getInt(++i);

		m_pAdvancementClass = new AdvancementClass( advLevel, advGoalExp, AdvancementClassExpTable::s_AdvancementClassExpTable );
		if ( getAdvancementClassLevel() > 0 ) m_bAdvanced = true;

		setSex(pResult->getString(++i));
		setMasterEffectColor(pResult->getInt(++i));

		m_STR[ATTR_BASIC]   = pResult->getInt(++i);
		m_STR[ATTR_CURRENT] = m_STR[ATTR_BASIC];
	   	m_STR[ATTR_MAX]     = m_STR[ATTR_BASIC];

		m_DEX[ATTR_BASIC]   = pResult->getInt(++i);
		m_DEX[ATTR_CURRENT] = m_DEX[ATTR_BASIC];
	   	m_DEX[ATTR_MAX]     = m_DEX[ATTR_BASIC];

		m_INT[ATTR_BASIC]   = pResult->getInt(++i);
		m_INT[ATTR_CURRENT] = m_INT[ATTR_BASIC];
	   	m_INT[ATTR_MAX]     = m_INT[ATTR_BASIC];

		setHP(pResult->getInt(++i) , ATTR_MAX);
		setHP(getHP(ATTR_MAX) , ATTR_BASIC);
		setHP(pResult->getInt(++i) , ATTR_CURRENT);

		setMP(pResult->getInt(++i) , ATTR_MAX);
		setMP(getMP(ATTR_MAX) , ATTR_BASIC);
		setMP(pResult->getInt(++i) , ATTR_CURRENT);
		
		setFame(pResult->getInt(++i));

//		setExp(pResult->getInt(++i));
		setGoalExp(pResult->getInt(++i));
//		setExpOffset(pResult->getInt(++i));
		setLevel(pResult->getInt(++i));
		setBonus(pResult->getInt(++i));
		setSkillBonus(pResult->getInt(++i));

		setGold(pResult->getInt(++i));
		setGuildID(pResult->getInt(++i));

		ZoneID_t zoneID = pResult->getInt(++i);
		setX(pResult->getInt(++i));
		setY(pResult->getInt(++i));

		setSight (pResult->getInt(++i));

		setAlignment(pResult->getInt(++i));

		setStashGold(pResult->getInt(++i));
		setStashNum(pResult->getBYTE(++i));
		
		m_Competence = pResult->getBYTE(++i);

		if ( m_Competence >= 4 )
			m_Competence = 3;

		m_CompetenceShape = pResult->getBYTE(++i);

		setResurrectZoneID(pResult->getInt(++i));
		setSilverDamage(pResult->getInt(++i));

		setSMSCharge( pResult->getInt(++i) );

		Rank_t CurRank               = pResult->getInt(++i);
		RankExp_t RankGoalExp        = pResult->getInt(++i);

		m_pRank = new Rank( CurRank, RankGoalExp, RankExpTable::s_RankExpTables[RANK_TYPE_OUSTERS] );

//		setRank( pResult->getInt(++i) );
//		setRankExp( pResult->getInt(++i) );
//		setRankGoalExp( pResult->getInt(++i) );

		setHairColor(pResult->getInt(++i));

		// maxHP¸¦ ´Ù½Ã °è»êÇØ¼­ ¼³Á¤ÇØÁØ´Ù.
		// 2002.7.15 by sigi
		// °ø½Ä ¹Ù²î¸é AbilityBalance.cppÀÇ computeHPµµ ¼öÁ¤ÇØ¾ßÇÑ´Ù.
		int maxHP = m_STR[ATTR_CURRENT]*2 + m_INT[ATTR_CURRENT] + m_DEX[ATTR_CURRENT] + m_Level;
		maxHP = min((int)maxHP, OUSTERS_MAX_HP);
		setHP( maxHP, ATTR_MAX );

		try
		{
			setZoneID( zoneID );
		}
		catch ( Error& e )
		{
			ZONE_COORD ResurrectCoord;
			g_pResurrectLocationManager->getOustersPosition( 1311, ResurrectCoord );
			setZoneID( ResurrectCoord.id );
			setX( ResurrectCoord.x );
			setY( ResurrectCoord.y );
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	//----------------------------------------------------------------------
	// Ousters Outlook Information À» ±¸¼ºÇÑ´Ù.
	//----------------------------------------------------------------------
	// ¾Æ¿ì½ºÅÍ½º´Â ·ÎµùÇÒ¶§ ObjectID¸¦ ¼¼ÆÃ ÇÏµµ·Ï ÇÑ´Ù.
	m_OustersInfo.setObjectID(m_ObjectID);
	m_OustersInfo.setName(m_Name);
	m_OustersInfo.setSex(m_Sex);
	m_OustersInfo.setHairColor(m_HairColor);
	m_OustersInfo.setMasterEffectColor(m_MasterEffectColor);

	m_OustersInfo.setCompetence(m_CompetenceShape);

    //----------------------------------------------------------------------
	// ½ºÅ³À» ·ÎµùÇÑ´Ù.
	//----------------------------------------------------------------------
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT SkillType, SkillLevel, Delay, CastingTime, NextTime FROM OustersSkillSave WHERE OwnerID = '%s'", m_Name.c_str());
	
		while(pResult->next()) 
		{
			int         i          = 0;
			SkillType_t SkillType = pResult->getInt(++i);

			if (hasSkill(SkillType) == NULL) 
			{
				OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot();
		
				pOustersSkillSlot->setName(m_Name);
				pOustersSkillSlot->setSkillType(SkillType);
				pOustersSkillSlot->setExpLevel(pResult->getInt(++i));
				pOustersSkillSlot->setInterval (pResult->getInt(++i));
				pOustersSkillSlot->setCastingTime (pResult->getInt(++i));
				pOustersSkillSlot->setRunTime();
		
				addSkill(pOustersSkillSlot);
			}
		}
	
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

    //----------------------------------------------------------------------
	// Rank Bonus ¸¦  ·ÎµùÇÑ´Ù.
	//----------------------------------------------------------------------
	loadRankBonus();

    //----------------------------------------------------------------------
	// ÀÌÆåÆ®¸¦ ·ÎµùÇÑ´Ù.
	//----------------------------------------------------------------------
	g_pEffectLoaderManager->load(this);

	//----------------------------------------------------------------------
	// GrandMasterÀÎ °æ¿ì´Â Effect¸¦ ºÙ¿©ÁØ´Ù.
	//----------------------------------------------------------------------
	// by sigi. 2002.11.8
	if (m_Level>=100
		&& SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_GRAND_MASTER_EFFECT ) )
	{
		if (!isFlag(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS))
		{
			EffectGrandMasterOusters* pEffect = new EffectGrandMasterOusters(this);
			pEffect->setDeadline(999999);
			getEffectManager()->addEffect( pEffect );
			setFlag(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS);
		}
	}

	//----------------------------------------------------------------------
	// ÇÃ·¡±× ¼ÂÀ» ·ÎµåÇÑ´Ù.
	//----------------------------------------------------------------------
	m_pFlagSet->load(getName());

	//----------------------------------------------------------------------
	// Ousters Outlook Information À» ÃÊ±âÈ­ÇÑ´Ù.
	//----------------------------------------------------------------------
	m_OustersInfo.setCoatType(OUSTERS_COAT_BASIC);
	m_OustersInfo.setArmType(OUSTERS_ARM_GAUNTLET);
	m_OustersInfo.setSylphType(OUSTERS_SYLPH_NONE);
	m_OustersInfo.setHairColor(m_HairColor);

	m_OustersInfo.setCoatColor( 377 );
	m_OustersInfo.setAdvancementLevel( getAdvancementClassLevel() );

	// Àß¸øµÈ °æÇèÄ¡¸¦ ÀçÁ¶Á¤ ÇØÁØ´Ù.
/*	OustersEXPInfo* pOustersEXPInfo = g_pOustersEXPInfoManager->getOustersEXPInfo(m_Level);

	if ( (pOustersEXPInfo->getAccumExp() != m_Exp + m_GoalExp) 
		&& m_Level > 1 && m_Level < OUSTERS_MAX_LEVEL ) 
	{
		// ÇöÀç ´©Àû °æÇèÄ¡ = ÇöÀç ·¹º§ÀÇ ÃÑ °æÇèÄ¡ - ¸ñÇ¥ °æÇèÄ¡
		m_Exp = pOustersEXPInfo->getAccumExp() - m_GoalExp;

		char pField[80];
		sprintf(pField, "Exp=%lu", m_Exp);
		tinysave(pField);
	}
*/
	// rank°¡ 0ÀÌ¸é ÃÊ±â°ªÀÌ ¼³Á¤µÇÁö ¾Ê¾Ò´Ù´Â ÀÇ¹ÌÀÌ´Ù. by sigi. 2002.9.13
	if (getRank()==0)
	{
		saveInitialRank();
	}


	// Àß¸øµÈ °è±ÞÀ» ÀçÁ¶Á¤ ÇØÁØ´Ù.
/*	RankEXPInfo* pRankEXPInfo = g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->getRankEXPInfo(m_Rank);

	if ((pRankEXPInfo->getAccumExp() != m_RankExp + m_RankGoalExp) 
		&& m_Rank > 1 && m_Rank < OUSTERS_MAX_RANK) 
	{
		m_RankExp = pRankEXPInfo->getAccumExp() - m_RankGoalExp;

		char pField[80];
		sprintf(pField, "RankExp=%lu", m_RankExp);
		tinysave(pField);
	}
*/

	initAllStat();

	// ÀüÀï Âü°¡ Flag Ã¼Å©
	if ( RaceWarLimiter::isInPCList( this ) )
	{
		setFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET );
	}

	if (m_pZone->isHolyLand()
        && g_pWarSystem->hasActiveRaceWar()
        && !isFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET ))
	{
        ZONE_COORD ResurrectCoord;
        g_pResurrectLocationManager->getPosition( this, ResurrectCoord );
        setZoneID( ResurrectCoord.id );
        setX( ResurrectCoord.x );
        setY( ResurrectCoord.y );
    }

	return true;

	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
void Ousters::save () const
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Statement* pStmt;

	//--------------------------------------------------------------------------------
	// ¾Æ¿ì½ºÅÍ½º Á¤º¸¸¦ ÀúÀåÇÑ´Ù.
	//--------------------------------------------------------------------------------
	BEGIN_DB
	{
		StringStream sql;
		sql << "UPDATE Ousters SET"
			<< " CurrentHP = " << (int)m_HP[ATTR_CURRENT]
			<< ", HP = " << (int)m_HP[ATTR_MAX]
			<< ", CurrentMP = " << (int)m_MP[ATTR_CURRENT]
			<< ", MP = " << (int)m_MP[ATTR_MAX]
			<< ", ZoneID = " << (int)getZoneID()
			<< ", XCoord = " << (int)m_X
			<< ", YCoord = " << (int)m_Y
			<< " WHERE Name = '" << m_Name << "'";
		
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQueryString(sql.toString());

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	//--------------------------------------------------
	// ÀÌÆåÆ®¸¦ ¼¼ÀÌºê ÇÑ´Ù.
	//--------------------------------------------------
	m_pEffectManager->save(m_Name);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//----------------------------------------------------------------------
// tinysave
//----------------------------------------------------------------------
void Ousters::tinysave(const string & field)	// by sigi. 2002.5.15
	    const 
{
    __BEGIN_TRY

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Ousters SET %s WHERE Name='%s'", field.c_str(), m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// »ç¿ëÇÑ skill bonus Æ÷ÀÎÆ®¸¦ ¸®ÅÏÇÑ´Ù.
////////////////////////////////////////////////////////////////////////////////
SkillBonus_t Ousters::getSumOfUsedSkillBonus() const
	
{
	__BEGIN_TRY

	return 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
//
// ½ºÅ³ °ü·Ã ÇÔ¼ö
//
//
////////////////////////////////////////////////////////////////////////////////

// Æ¯Á¤ SkillÀ» ¸®ÅÏÇÑ´Ù.
OustersSkillSlot* Ousters::getSkill (SkillType_t SkillType) const 
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::const_iterator itr = m_SkillSlot.find(SkillType);
	if (itr != m_SkillSlot.end())
	{
		return itr->second;
	}

	return NULL;

	__END_CATCH
}

// Æ¯Á¤ SkillÀ» add ÇÑ´Ù
void Ousters::addSkill(SkillType_t SkillType)
	
{
	__BEGIN_TRY

	switch (SkillType)
	{
		case SKILL_UN_BURROW:
		case SKILL_UN_TRANSFORM:
		case SKILL_UN_INVISIBILITY:
		case SKILL_THROW_HOLY_WATER:
		case SKILL_EAT_CORPSE:
		case SKILL_HOWL:
			filelog("OustersError.log", "SkillType[%d], %s", SkillType, toString().c_str());
			Assert(false);
			break;
		default:
			break;
	}

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);

	if (itr == m_SkillSlot.end())
	{
		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Turn_t Delay = pSkillInfo->getMaxDelay();

		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;

		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(SkillType);
		pOustersSkillSlot->setInterval(Delay);
		pOustersSkillSlot->setRunTime();
		pOustersSkillSlot->setExpLevel(1);
		pOustersSkillSlot->create(m_Name);

		m_SkillSlot[SkillType] = pOustersSkillSlot;
	}

	__END_CATCH
}

// Æ¯Á¤ SkillSlotÀ» ÀÚµ¿À¸·Î ºó ½½¶ùÀ» Ã£¾Æ ³Ö´Â´Ù.
void Ousters::addSkill(OustersSkillSlot* pOustersSkillSlot)
	
{
	__BEGIN_TRY

	SkillType_t SkillType = pOustersSkillSlot->getSkillType();
	switch (SkillType)
	{
		case SKILL_UN_BURROW:
		case SKILL_UN_TRANSFORM:
		case SKILL_UN_INVISIBILITY:
		case SKILL_THROW_HOLY_WATER:
		case SKILL_EAT_CORPSE:
		case SKILL_HOWL:
			filelog("OustersError.log", "SkillType[%d], %s", SkillType, toString().c_str());
			Assert(false);
			break;
		default:
			break;
	}

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(pOustersSkillSlot->getSkillType());
	
	if (itr == m_SkillSlot.end())
	{
		m_SkillSlot[pOustersSkillSlot->getSkillType()] = pOustersSkillSlot;
	}
	// 2002.1.16 by sigi
	else
	{
		delete pOustersSkillSlot;
	}

	__END_CATCH
}

void Ousters::removeSkill(SkillType_t SkillType)
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);
	
	if (itr != m_SkillSlot.end())
	{
		OustersSkillSlot* pSkillSlot = itr->second;

		SAFE_DELETE( pSkillSlot );

		m_SkillSlot.erase( itr );
	}

	__END_CATCH
}

// ¼ºÁö½ºÅ³À» Áö¿öÁÖ´Â ÇÔ¼ö´Ù.
void Ousters::removeCastleSkill(SkillType_t SkillType)
	
{
	__BEGIN_TRY

	// ¼ºÁö ½ºÅ³¸¸ Áö¿ï ¼ö ÀÖ´Ù.
	if ( g_pCastleSkillInfoManager->getZoneID( SkillType ) == 0 ) return;

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);
	
	if (itr != m_SkillSlot.end())
	{
		OustersCastleSkillSlot* pCastleSkillSlot = dynamic_cast<OustersCastleSkillSlot*>(itr->second);

		SAFE_DELETE( pCastleSkillSlot );

		m_SkillSlot.erase( itr );
	}

	__END_CATCH
}

// °®°í ÀÖ´Â ¸ðµç ¼ºÁö½ºÅ³À» Áö¿öÁÖ´Â ÇÔ¼öÀÌ´Ù.
void Ousters::removeAllCastleSkill()
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();

	while ( itr != m_SkillSlot.end() )
	{
		if ( itr->second != NULL )
		{
			OustersSkillSlot* pSkillSlot = itr->second;
			if ( g_pCastleSkillInfoManager->getZoneID( pSkillSlot->getSkillType() ) == 0 )
			{
				// ¼ºÁö½ºÅ³ÀÌ ¾Æ´Ï¸é ´ÙÀ½²¬·Î ³Ñ¾î°£´Ù.
				++itr;
				continue;
			}

			// ¼ºÁö½ºÅ³ÀÌ¸é Áö¿öÁØ´Ù. ¹Ýº¹ÀÚ »ç¿ë¿¡ ÁÖÀÇ
			SAFE_DELETE( pSkillSlot );
			unordered_map<SkillType_t, OustersSkillSlot*>::iterator prevItr = itr;
			
			++itr;
			m_SkillSlot.erase( prevItr );
		}
		else
		{
			// ÀÌ°Ç ¸Ö±î.... Assert ÇØ¾ß µÇÁö ¾Ê³ª -_-;
			Assert(false);
		}
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
//
// ¾ÆÀÌÅÛ Âø/Å» °ü·Ã ÇÔ¼ö
//
//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
//
// Ousters::WearItem()
//
// ItemÀ» ÀåÂøÃ¢¿¡ ÀåÂø½ÃÅ°°í ´É·ÂÄ¡¸¦ °è»êÇÑ´Ù.
//
//----------------------------------------------------------------------
void Ousters::wearItem(WearPart Part, Item* pItem)
	
{
	__BEGIN_TRY

	Assert(pItem != NULL);

	Item* pPrevItem = NULL;
	Item* pLeft = NULL;
	Item* pRight = NULL;

	// ¾ç¼Õ ¹«±âÀÏ °æ¿ì¿¡´Â ¾ç¼Õ ÀåÂøÃ¢¿¡´Ù ÇÏ³ªÀÇ ¾ÆÀÌÅÛ Æ÷ÀÎÅÍ¸¦ ÇÒ´ç...
	if (isTwohandWeapon(pItem))
	{
		// ¾ç¼Õ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÀ» °æ¿ì
		if (isWear(WEAR_RIGHTHAND) && isWear(WEAR_LEFTHAND))
		{
			pLeft  = getWearItem(WEAR_RIGHTHAND);
			pRight = getWearItem(WEAR_LEFTHAND);
			
			// ¾ç¼Õ ¹«±â¸¦ µé°í ÀÖÀ» °æ¿ì
			if (pLeft == pRight)
			{
				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö°í,
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				char pField[80];
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// ¿ø·¡ ÀÖ´ø ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾Æ ÁØ´Ù.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);
			}
			// ³É³É
			else
			{
				// ¾ç¼Õ¿¡ °Ë°ú ¹æÆÐ¸¦ µé°í ÀÖ¾ú´Âµ¥...¾ç¼Õ ¹«±â¸¦ µé·Á°í ÇÏ¸é,
				// °ËÀº ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾ÆÁÙ ¼ö ÀÖÁö¸¸, ¹æÆÐ´Â ¾î¶»°Ô ÇÒ ¼ö°¡ ¾ø´Ù.
				// ÀÎº¥Åä¸®¿¡ ³Ö¾îÁà¾ß ÇÒ ÅÙµ¥, Áö±Ý ´çÀåÀº ¾î¶»°Ô ÇÒ Áö¸¦ ¸ð¸£°Ú³×...
				// °Á ÀÔÀ» ¼ö ¾ø´Ù´Â ÆÐÅ¶À» º¸³»ÁÖÀÚ...
				//cerr << "¾ç¼Õ¿¡ Ä®°ú ¹æÆÐ¸¦ µé°í ÀÖ¾î¼­, ¾ç¼Õ ¹«±â¸¦ ÀåÂøÇÒ ¼ö ¾ø½À´Ï´Ù." << endl;
				return;
			}
		}
		// ¾ç¼Õ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÁö ¾ÊÀ» °æ¿ì
		else 
		{
			char pField[80];

			// ¿À¸¥ÂÊ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÀ» °æ¿ì
			if (isWear(WEAR_RIGHTHAND))
			{
				pRight = getWearItem(WEAR_RIGHTHAND);
				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// ¿ø·¡ ÀÖ´ø ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾Æ ÁØ´Ù.
				addItemToExtraInventorySlot(pRight);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pRight->tinysave(pField);
			}
			// ¿ÞÂÊ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÀ» °æ¿ì
			else if (isWear(WEAR_LEFTHAND))
			{
				pLeft = getWearItem(WEAR_LEFTHAND);
				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// ¿ø·¡ ÀÖ´ø ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾Æ ÁØ´Ù.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);
			}
			// ¾Æ¹«ÂÊµµ ¾ÆÀÌÅÛÀ» µé°í ÀÖÁö ¾ÊÀ» °æ¿ì
			else
			{
				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);
			}
		}
	}
	else 
	{
		if (isWear(Part))
		{
			pPrevItem = getWearItem(Part);
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			char pField[80];
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);

			addItemToExtraInventorySlot(pPrevItem);
			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pPrevItem->tinysave(pField);
		}
		else
		{
			// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			char pField[80];
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);
		}
	}

	// ¿ÊÀÌ¶ó¸é ¿Ê¿¡ µû¸¥ »ö±òÀ» Á¤ÇØÁØ´Ù.
	// ³ªÁß¿¡¶óµµ ¿Ê Å¸ÀÔÀÌ ¿©·¯ °¡Áö°¡ µÉ ¼ö ÀÖÀ¸¸®¶ó »ý°¢ÇÏ´Âµ¥,
	// ÇöÀç·Î¼­´Â ¿Ê Å¸ÀÔÀÌ ÇÏ³ªÀÌ¹Ç·Î, »ö±ò¸¸ ¼¼ÆÃÇØÁØ´Ù.
	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_OUSTERS_COAT:
			// item typeÀ» ¼³Á¤ÇØÁØ´Ù. 
			m_OustersInfo.setCoatType( getOustersCoatType( pItem->getItemType() ) );
			m_OustersInfo.setCoatColor( getItemShapeColor( pItem ) );
			break;
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
			m_OustersInfo.setArmType( OUSTERS_ARM_CHAKRAM );
			m_OustersInfo.setArmColor( getItemShapeColor( pItem ) );
			break;
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
			m_OustersInfo.setArmColor( getItemShapeColor( pItem ) );
			break;
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
			m_OustersInfo.setBootsColor( getItemShapeColor( pItem ) );
			break;
		default:
			break;
	}

	__END_CATCH
}


//----------------------------------------------------------------------
// Ousters::WearItem()
// ItemÀ» ÀåÂøÃ¢¿¡ ÀåÂø½ÃÅ°°í ´É·ÂÄ¡¸¦ °è»êÇÑ´Ù.
//----------------------------------------------------------------------
void Ousters::wearItem(WearPart Part)
	
{
	__BEGIN_TRY

	// ÀåÂø ÁØºñÁßÀÎ ¾ÆÀÌÅÛÀ» ¹Þ¾Æ¿Â´Ù.
	Item* pItem = getExtraInventorySlotItem();
	Assert(pItem != NULL);

	Item* pPrevItem = NULL;
	Item* pLeft = NULL;
	Item* pRight = NULL;

	// ¸ÕÀú ¿ÊÀ» ÀÔÈ÷°Å³ª, ¹þ±â±â Àü¿¡ ÇöÀçÀÇ ´É·ÂÄ¡¸¦ ¹öÆÛ¿¡´Ù ÀúÀåÇØ µÐ´Ù.
	// ÀÌ´Â ³ªÁß¿¡ º¯ÇÑ ´É·ÂÄ¡¸¸À» Àü¼ÛÇÏ±â À§ÇÑ °ÍÀÌ´Ù.
	OUSTERS_RECORD prev;
	getOustersRecord(prev);

	char pField[80];

	// ¾ç¼Õ ¹«±âÀÏ °æ¿ì¿¡´Â ¾ç¼Õ ÀåÂøÃ¢¿¡´Ù ÇÏ³ªÀÇ ¾ÆÀÌÅÛ Æ÷ÀÎÅÍ¸¦ ÇÒ´ç...
	if (isTwohandWeapon(pItem))
	{
		// ¾ç¼Õ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÀ» °æ¿ì
		if (isWear(WEAR_RIGHTHAND) && isWear(WEAR_LEFTHAND))
		{
			pLeft  = getWearItem(WEAR_RIGHTHAND);
			pRight = getWearItem(WEAR_LEFTHAND);
			
			// ¾ç¼Õ ¹«±â¸¦ µé°í ÀÖÀ» °æ¿ì
			if (pLeft == pRight)
			{
				takeOffItem(WEAR_LEFTHAND, false, false);

				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö°í,
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;
				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡¼­ Á¦°ÅÇÑ´Ù.
				deleteItemFromExtraInventorySlot();
				// ¿ø·¡ ÀÖ´ø ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾Æ ÁØ´Ù.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);

			}
			// °Ë°ú ¹æÆÐ¸¦ µé°í ÀÖÀ» °æ¿ì
			else
			{
				// ¾ç¼Õ¿¡ °Ë°ú ¹æÆÐ¸¦ µé°í ÀÖ¾ú´Âµ¥...¾ç¼Õ ¹«±â¸¦ µé·Á°í ÇÏ¸é,
				// °ËÀº ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾ÆÁÙ ¼ö ÀÖÁö¸¸, ¹æÆÐ´Â ¾î¶»°Ô ÇÒ ¼ö°¡ ¾ø´Ù.
				// ÀÎº¥Åä¸®¿¡ ³Ö¾îÁà¾ß ÇÒ ÅÙµ¥, Áö±Ý ´çÀåÀº ¾î¶»°Ô ÇÒ Áö¸¦ ¸ð¸£°Ú³×...
				// °Á ÀÔÀ» ¼ö ¾ø´Ù´Â ÆÐÅ¶À» º¸³»ÁÖÀÚ...
				return;
			}
		}
		// ¾ç¼Õ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÁö ¾ÊÀ» °æ¿ì
		else 
		{
			// by sigi. 2002.5.15
			// ¿À¸¥ÂÊ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÀ» °æ¿ì
			if (isWear(WEAR_RIGHTHAND))
			{
				pRight = getWearItem(WEAR_RIGHTHAND);

				takeOffItem(WEAR_RIGHTHAND, false, false);

				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡¼­ Á¦°ÅÇÑ´Ù.
				deleteItemFromExtraInventorySlot();
				// ¿ø·¡ ÀÖ´ø ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾Æ ÁØ´Ù.
				addItemToExtraInventorySlot(pRight);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pRight->tinysave(pField);
				
			}
			// ¿ÞÂÊ¿¡ ¾ÆÀÌÅÛÀ» µé°í ÀÖÀ» °æ¿ì
			else if (isWear(WEAR_LEFTHAND))
			{
				pLeft = getWearItem(WEAR_LEFTHAND);
				
				takeOffItem(WEAR_LEFTHAND, false, false);

				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;
				
				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡¼­ Á¦°ÅÇÑ´Ù.
				deleteItemFromExtraInventorySlot();
				// ¿ø·¡ ÀÖ´ø ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡ ´Þ¾Æ ÁØ´Ù.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);
			}
			// ¾Æ¹«ÂÊµµ ¾ÆÀÌÅÛÀ» µé°í ÀÖÁö ¾ÊÀ» °æ¿ì
			else
			{
				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ÀåÂø Æ÷ÀÎÆ®¿¡ ³Ö´Â´Ù.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				// ¿ä±¸ÇÑ ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Æ÷ÀÎÅÍ¿¡¼­ Á¦°ÅÇÑ´Ù.
				deleteItemFromExtraInventorySlot();
			}
		}
	}
	else
	{
		if (isWear(Part))
		{
			pPrevItem = getWearItem(Part);
			takeOffItem(Part, false, false);
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);

			deleteItemFromExtraInventorySlot();
			addItemToExtraInventorySlot(pPrevItem);

			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pPrevItem->tinysave(pField);
		}
		else
		{
			m_pWearItem[Part] = pItem;
			deleteItemFromExtraInventorySlot();

			// by sigi. 2002.5.15
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);
		}
	}

	initAllStat();
	sendRealWearingInfo();
	sendModifyInfo(prev);

	// ½ÇÁ¦ Àû¿ëµÇ´Â ¾ÆÀÌÅÛ¸¸ º¹ÀåÀ» ¹Ù²Û´Ù. by sigi. 2002.10.30
	if (m_pRealWearingCheck[Part])
	{
		if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_COAT
			|| pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_WRISTLET
			|| pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_CHAKRAM
			|| pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_BOOTS ) 
		{
			Color_t color = getItemShapeColor( pItem );

			// ¿ÊÀ» °¥¾ÆÀÔ¾úÀ¸´Ï, ÁÖÀ§¿¡´Ù°¡ ¿Ê °¥¾ÆÀÔ¾ú´Ù°í Á¤º¸¸¦ ³¯¸°´Ù.
			GCChangeShape pkt;
			pkt.setObjectID(getObjectID());
			pkt.setItemClass(pItem->getItemClass());
			pkt.setItemType(pItem->getItemType());
			pkt.setOptionType(pItem->getFirstOptionType());
			pkt.setAttackSpeed(m_AttackSpeed[ATTR_CURRENT]);

			if ( color == QUEST_COLOR )
				pkt.setFlag( SHAPE_FLAG_QUEST );

			Zone* pZone = getZone();
			pZone->broadcastPacket(m_X, m_Y , &pkt, this);

			// PCOustersInfo3 Á¤º¸¸¦ ¹Ù²ãÁØ´Ù.
			switch ( pItem->getItemClass() )
			{
				case Item::ITEM_CLASS_OUSTERS_COAT:
					// item typeÀ» ¼³Á¤ÇØÁØ´Ù. 
					m_OustersInfo.setCoatType( getOustersCoatType( pItem->getItemType() ) );
					m_OustersInfo.setCoatColor( color );
					break;
				case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
					m_OustersInfo.setArmType( OUSTERS_ARM_CHAKRAM );
					m_OustersInfo.setArmColor( color );
					break;
				case Item::ITEM_CLASS_OUSTERS_WRISTLET:
					m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
					m_OustersInfo.setArmColor( color );
					break;
				case Item::ITEM_CLASS_OUSTERS_BOOTS:
					m_OustersInfo.setBootsColor( color );
					break;
				default:
					break;
			}
		}
	}

	if (m_pZone != NULL)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, this, &prev);

		if (gcOtherModifyInfo.getShortCount() != 0 || gcOtherModifyInfo.getLongCount() != 0)
		{
			m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
		}
	}
	
	__END_CATCH
}


//----------------------------------------------------------------------
//
// Ousters::takeOffItem()
//
//----------------------------------------------------------------------
void Ousters::takeOffItem(WearPart Part, bool bAddOnMouse, bool bSendModifyInfo)
	
{
	__BEGIN_TRY

	OUSTERS_RECORD prev;

	// ÀåÂøÃ¢¿¡ ÀÖ´Â ¾ÆÀÌÅÛÀ» ¹Þ¾Æ¿Â´Ù.
	Item* pItem = m_pWearItem[Part];
	Assert(pItem != NULL);

	// ÀåÂøÃ¢¿¡ ÀÖ´Â ¾ÆÀÌÅÛÀ» ¹Þ¾Æ¿Â´Ù.
	//Item::ItemClass IClass = pItem->getItemClass();

	if (Part == WEAR_LEFTHAND || Part == WEAR_RIGHTHAND)
	{
		if (m_pWearItem[WEAR_RIGHTHAND] && m_pWearItem[WEAR_LEFTHAND])
		{
			if (m_pWearItem[WEAR_RIGHTHAND] == m_pWearItem[WEAR_LEFTHAND])
			{
				m_pWearItem[WEAR_RIGHTHAND] = NULL;
				m_pWearItem[WEAR_LEFTHAND] = NULL;
			}
		}
	}

	// ¾ÆÀÌÅÛÀ» ÀåÂøÆ÷ÀÎÆ®¿¡¼­ Á¦°ÅÇÑ´Ù.
	if (isTwohandWeapon(pItem))
	{
		m_pWearItem[WEAR_RIGHTHAND] = NULL;
		m_pWearItem[WEAR_LEFTHAND] = NULL;
	}
	else m_pWearItem[Part] = NULL;

	// wearItem¿¡¼­ ÁöÁ¤µÈ ½½¶ù¿¡ ¿ÊÀ» ÀÌ¹Ì ÀÔ°í ÀÖ´Â °æ¿ì¿¡, ±×°ÍÀ» ¹þ±â°í
	// ´Ù½Ã ¿ÊÀ» ÀÔÈ÷´Âµ¥, ±×·¯¸é ¹þ±æ ¶§ ÆÐÅ¶À» ÇÑ¹ø, ÀÔ¾úÀ» ¶§ ´Ù½Ã ÆÐÅ¶À»
	// ÇÑ¹ø, ÃÑ µÎ ¹øÀÇ ÆÐÅ¶À» º¸³»°Ô µÈ´Ù. ±×°ÍÀ» ¹æÁöÇÏ±â À§ÇØ¼­
	// bool º¯¼ö¸¦ ÇÏ³ª Áý¾î³Ö¾ú´Ù. -- 2002.01.24 ±è¼º¹Î
	if (bSendModifyInfo)
	{
		getOustersRecord(prev);
		initAllStat();
		sendRealWearingInfo();
		sendModifyInfo(prev);
	}
	else
	{
		initAllStat();
	}

	//---------------------------------------------
	// ÀÖ¾î¼± ¾ÈµÉ Ã¼Å© -_-; ÀÓ½Ã ¶«»§
	// ¾ÆÀÌÅÛÀ» ¸¶¿ì½º Ä¿¼­¿¡´Ù ´Þ¾ÆÁØ´ç.
	//---------------------------------------------
	if (bAddOnMouse) 
	{
		addItemToExtraInventorySlot(pItem);
		// itemÀúÀå ÃÖÀûÈ­. by sigi. 2002.5.13
		char pField[80];
        sprintf(pField, "Storage=%d, Durability=%d", STORAGE_EXTRASLOT, pItem->getDurability());
        pItem->tinysave(pField);
	}

	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_OUSTERS_COAT:
			{
				m_OustersInfo.setCoatType( OUSTERS_COAT_BASIC );
				m_OustersInfo.setCoatColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_COAT);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
			{
				m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
				m_OustersInfo.setArmColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_LEFTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			{
				m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
				m_OustersInfo.setArmColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_LEFTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
			{
				m_OustersInfo.setBootsColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_TROUSER);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		default:
			break;
	}

	if (m_pZone != NULL)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, this, &prev);

		if (gcOtherModifyInfo.getShortCount() != 0 || gcOtherModifyInfo.getLongCount() != 0)
		{
			m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
		}
	}

	__END_CATCH
}




//----------------------------------------------------------------------
// destroyGears
// ÀåÂø ¾ÆÀÌÅÛÀ» Delete ÇÑ´Ù.
//----------------------------------------------------------------------
void Ousters::destroyGears() 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	for (int j = 0; j < OUSTERS_WEAR_MAX; j++) 
	{
		Item* pItem = m_pWearItem[j];
		if (pItem != NULL)
		{
			Item::ItemClass IClass = pItem->getItemClass();

			//-------------------------------------------------------------
			// ½½·¹ÀÌ¾î¿ë ¾ÆÀÌÅÛÀ» ÀÔ°í ÀÖ´Â ÀÌ»óÇÑ ÀÚ½ÄÀÌ ÀÖÀ¸¸é ´Ù ¾î¼­Æ®
			//-------------------------------------------------------------
			Assert(IClass != Item::ITEM_CLASS_AR);
			Assert(IClass != Item::ITEM_CLASS_SR);
			Assert(IClass != Item::ITEM_CLASS_SG);
			Assert(IClass != Item::ITEM_CLASS_SMG);
			Assert(IClass != Item::ITEM_CLASS_SWORD);
			Assert(IClass != Item::ITEM_CLASS_BLADE);
			Assert(IClass != Item::ITEM_CLASS_SHIELD);
			Assert(IClass != Item::ITEM_CLASS_CROSS);
			Assert(IClass != Item::ITEM_CLASS_MACE);
			Assert(IClass != Item::ITEM_CLASS_HELM);
			Assert(IClass != Item::ITEM_CLASS_GLOVE);
			Assert(IClass != Item::ITEM_CLASS_TROUSER);
			Assert(IClass != Item::ITEM_CLASS_COAT);

			// ¾ç¼Õ ¹«±âÀÎÁö¸¦ °Ë»çÇØ¼­ ¾ÆÀÌÅÛ ÇÏ³ª¸¦ Áö¿ì¸é¼­
			// ¾ç¼ÕÀ» ºñ¿öÁØ´Ù.
			if (isTwohandWeapon(pItem))
			{
				m_pWearItem[WEAR_RIGHTHAND] = NULL;
				m_pWearItem[WEAR_LEFTHAND]  = NULL;
			}
			else m_pWearItem[j] = NULL;

			SAFE_DELETE(pItem);
		}
	}

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::isRealWearing(WearPart part) const
	
{
	__BEGIN_TRY

	if (part >= OUSTERS_WEAR_MAX) throw("Ousters::isRealWearing() : invalid wear point!");

	if (m_pWearItem[part] == NULL) return false;
	if (part >= WEAR_ZAP1 && part <= WEAR_ZAP4)
	{
		// ÇØ´ç À§Ä¡¿¡ Á¤·É¼®µµ ÀÖ¾î¾ß µÈ´Ù.
		if ( m_pWearItem[part-WEAR_ZAP1+WEAR_STONE1]==NULL ) return false;
	}

	return isRealWearing(m_pWearItem[part]);

	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::isRealWearing(Item* pItem) const
	
{
	__BEGIN_TRY

	if (pItem == NULL) return false;

/*	if ( m_pZone != NULL && m_pZone->isDynamicZone() && m_pZone->getDynamicZone()->getTemplateZoneID() == 4005 )
	{
		if ( !isOustersWeapon( pItem->getItemClass() ) ) return false;
	}*/

	// ½Ã°£Á¦ÇÑ¾ÆÀÌÅÛÀº ·¹¾î³ª À¯´ÏÅ©³ª ¹«·á»ç¿ëÀÚµµ ¾µ ¼ö ÀÖ´Ù....... 2003.5.4
	if ( pItem->isTimeLimitItem() )
	{
		return true;
	}

	// ÇÁ¸®¹Ì¾ö Á¸¿¡¼­´Â À¯·á»ç¿ëÀÚ¸¸ À¯´ÏÅ©/·¹¾î ¾ÆÀÌÅÛÀÌ Àû¿ëµÈ´Ù.
	// Ä¿ÇÃ¸µµµ À¯·á»ç¿ëÀÚ¸¸ ¾µ ¼ö ÀÖ´Ù. by Sequoia 2003. 3. 5.
	if (getZone()->isPremiumZone()
		&& (pItem->isUnique() || pItem->getOptionTypeSize()>1  ) )
			//pItem->getItemClass() == Item::ITEM_CLASS_COUPLE_RING || pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_COUPLE_RING))
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(getPlayer());
		if (!pGamePlayer->isPayPlaying() 
			&& !pGamePlayer->isPremiumPlay())
		{
			return false;
		}
	}

	Item::ItemClass IClass    = pItem->getItemClass();
	ItemInfo*       pItemInfo = g_pItemInfoManager->getItemInfo(IClass, pItem->getItemType());

	Level_t			ReqAdvancedLevel = pItemInfo->getReqAdvancedLevel();
	if ( ReqAdvancedLevel > 0 && ( !isAdvanced() || getAdvancementClassLevel() < ReqAdvancedLevel ) ) return false;

	if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_COAT || pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_BOOTS ||
		isOustersWeapon(pItem->getItemClass()) )
	{
		if ( ReqAdvancedLevel <= 0 && isAdvanced() ) return false;
	}
	
	Level_t         ReqLevel  = pItemInfo->getReqLevel();
	Attr_t			ReqSTR    = pItemInfo->getReqSTR();
	Attr_t			ReqDEX    = pItemInfo->getReqDEX();
	Attr_t			ReqINT    = pItemInfo->getReqINT();
	Attr_t			ReqSum    = pItemInfo->getReqSum();

	// ¾ÆÀÌÅÛÀÌ ¿É¼ÇÀ» °¡Áö°í ÀÖ´Ù¸é,
	// ¿É¼ÇÀÇ Á¾·ù¿¡ µû¶ó¼­ ´É·ÂÄ¡ Á¦ÇÑÀ» ¿Ã·ÁÁØ´Ù.
	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	list<OptionType_t>::const_iterator itr;

	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
		if (ReqLevel != 0) ReqLevel += pOptionInfo->getReqLevel();
		if (ReqSTR != 0) ReqSTR += (pOptionInfo->getReqSum() * 2);
		if (ReqDEX != 0) ReqDEX += (pOptionInfo->getReqSum() * 2);
		if (ReqINT != 0) ReqINT += (pOptionInfo->getReqSum() * 2);
		if (ReqSum != 0) ReqSum += pOptionInfo->getReqSum();
	}

	ReqLevel = min(ReqLevel, MAX_OUSTERS_LEVEL );
//	ReqSum = min((int)ReqSum, OUSTERS_MAX_SUM);
//	ReqSTR = min((int)ReqSTR, OUSTERS_MAX_ATTR);
//	ReqDEX = min((int)ReqDEX, OUSTERS_MAX_ATTR);
//	ReqINT = min((int)ReqINT, OUSTERS_MAX_ATTR);

	// ´É·ÂÄ¡ Á¦ÇÑÀÌ ÇÏ³ª¶óµµ ÀÖ´Ù¸é,
	// ±× ´É·ÂÀ» ¸¸Á·½ÃÅ°´ÂÁö °Ë»çÇØ¾ß ÇÑ´Ù.
	Attr_t CSTR = m_STR[ATTR_CURRENT];
	Attr_t CDEX = m_DEX[ATTR_CURRENT];
	Attr_t CINT = m_INT[ATTR_CURRENT];
	Attr_t CSUM = CSTR + CDEX + CINT;

	if ( CSTR < ReqSTR || CDEX < ReqDEX || CINT < ReqINT || CSUM < ReqSum || m_Level < ReqLevel )
	{
		return false;
	}

	return true;

	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::isRealWearingEx(WearPart part) const
{
	if (part >= OUSTERS_WEAR_MAX) return false;
	return m_pRealWearingCheck[part];
}

DWORD Ousters::sendRealWearingInfo(void) const
	
{
	__BEGIN_TRY

	DWORD info = 0;
	DWORD flag = 1;

	for (int i=0; i<OUSTERS_WEAR_MAX; i++)
	{
		if (isRealWearing((Ousters::WearPart)i)) info |= flag;
		flag <<= 1;
	}

	GCRealWearingInfo pkt;
	pkt.setInfo(info);
	m_pPlayer->sendPacket(&pkt);

	return info;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
//
// ÀÎÆ÷ °ü·Ã ÇÔ¼ö
//
//
////////////////////////////////////////////////////////////////////////////////

PCOustersInfo2* Ousters::getOustersInfo2 ()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	PCOustersInfo2* pInfo = new PCOustersInfo2();

	pInfo->setObjectID(m_ObjectID);
	pInfo->setName(m_Name);
	pInfo->setLevel(m_Level);
	pInfo->setSex(m_Sex);
	pInfo->setHairColor(m_HairColor);
	pInfo->setMasterEffectColor(m_MasterEffectColor);

    // ¼ºÇâ
	pInfo->setAlignment(m_Alignment);

	// ´É·ÂÄ¡
	pInfo->setSTR(m_STR[ATTR_CURRENT], ATTR_CURRENT);
	pInfo->setSTR(m_STR[ATTR_MAX], ATTR_MAX);
	pInfo->setSTR(m_STR[ATTR_BASIC], ATTR_BASIC);
	pInfo->setDEX(m_DEX[ATTR_CURRENT], ATTR_CURRENT);
	pInfo->setDEX(m_DEX[ATTR_MAX], ATTR_MAX);
	pInfo->setDEX(m_DEX[ATTR_BASIC], ATTR_BASIC);
	pInfo->setINT(m_INT[ATTR_CURRENT], ATTR_CURRENT);
	pInfo->setINT(m_INT[ATTR_MAX], ATTR_MAX);
	pInfo->setINT(m_INT[ATTR_BASIC], ATTR_BASIC);
	
	pInfo->setHP(m_HP[ATTR_CURRENT] , m_HP[ATTR_MAX]);
	pInfo->setMP(m_MP[ATTR_CURRENT] , m_MP[ATTR_MAX]);
	pInfo->setSilverDamage( m_SilverDamage );

	pInfo->setFame(m_Fame);
	pInfo->setExp(m_GoalExp);
	pInfo->setGold(m_Gold);
	pInfo->setSight(m_Sight);
	pInfo->setBonus(m_Bonus);
	pInfo->setSkillBonus(m_SkillBonus);

	// by sigi. 2002.8.30
	pInfo->setRank(getRank());
	pInfo->setRankExp(getRankGoalExp());

	pInfo->setCompetence(m_CompetenceShape);
	pInfo->setGuildID(m_GuildID);
	pInfo->setGuildName( getGuildName() );
	pInfo->setGuildMemberRank( getGuildMemberRank() );

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( m_GuildID );
	if ( pUnion == NULL ) pInfo->setUnionID( 0 );
	else pInfo->setUnionID( pUnion->getUnionID() );

	pInfo->setAdvancementLevel( getAdvancementClassLevel() );
	pInfo->setAdvancementGoalExp( getAdvancementClassGoalExp() );

	return pInfo;

	__END_DEBUG
	__END_CATCH
}


//----------------------------------------------------------------------
// Ousters Outlook Information
//----------------------------------------------------------------------
PCOustersInfo3 Ousters::getOustersInfo3 () const 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	m_OustersInfo.setObjectID(m_ObjectID);
	m_OustersInfo.setX(m_X);
	m_OustersInfo.setY(m_Y);
	m_OustersInfo.setDir(m_Dir);
	m_OustersInfo.setCurrentHP(m_HP[ATTR_CURRENT]);
	m_OustersInfo.setMaxHP(m_HP[ATTR_MAX]);
	m_OustersInfo.setAttackSpeed(m_AttackSpeed[ATTR_CURRENT]);
	m_OustersInfo.setAlignment(m_Alignment);
	m_OustersInfo.setGuildID(m_GuildID);

	// by sigi. 2002.9.10
	m_OustersInfo.setRank(getRank());

    m_OustersInfo.setHairColor(m_HairColor);
    m_OustersInfo.setMasterEffectColor(m_MasterEffectColor);

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( m_GuildID );
	if ( pUnion == NULL ) m_OustersInfo.setUnionID( 0 );
	else m_OustersInfo.setUnionID( pUnion->getUnionID() );

	m_OustersInfo.setAdvancementLevel( getAdvancementClassLevel() );

	return m_OustersInfo;

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
//
// get Extra Info
//
//----------------------------------------------------------------------
ExtraInfo* Ousters::getExtraInfo() const
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	BYTE ItemCount = 0;

	ExtraInfo* pExtraInfo = new ExtraInfo();

	Item* pItem = m_pExtraInventorySlot->getItem();

	if (pItem != NULL) {
	
	//	Item::ItemClass IClass = pItem->getItemClass();

		ExtraSlotInfo* pExtraSlotInfo = new ExtraSlotInfo();
		pItem->makePCItemInfo( *pExtraSlotInfo );

/*		pExtraSlotInfo->setObjectID(pItem->getObjectID());
		pExtraSlotInfo->setItemClass(pItem->getItemClass());
		pExtraSlotInfo->setItemType(pItem->getItemType());
		pExtraSlotInfo->setOptionType(pItem->getOptionTypeList());
		pExtraSlotInfo->setDurability(pItem->getDurability());
		pExtraSlotInfo->setSilver(pItem->getSilver());
		pExtraSlotInfo->setSilver(pItem->getEnchantLevel());
		pExtraSlotInfo->setItemNum(pItem->getNum());

		// ¾Ï½º¹êµå¶ó¸é Sub ¾ÆÀÌÅÛÀÇ Ãß°¡ Á¤º¸°¡ ÇÊ¿äÇÏ´Ù.
		if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
		{
			OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
			Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pItem)->getInventory();
			BYTE SubItemCount = 0;

			// Æ÷ÄÏÀÇ ¼ýÀÚ¸¸Å­ ¾ÆÀÌÅÛÀÇ Á¤º¸¸¦ ÀÐ¾î µéÀÎ´Ù.
			for (int i = 0; i < pOustersArmsband->getPocketCount(); i++) 
			{
				Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);

				if (pOustersArmsbandItem != NULL) 
				{
					SubItemInfo* pSubItemInfo = new SubItemInfo();
					pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
					pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
					pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
					pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
					pSubItemInfo->setSlotID(i);

					pExtraSlotInfo->addListElement(pSubItemInfo);

					SubItemCount++;
				}
			}

			pExtraSlotInfo->setListNum(SubItemCount);

		}

		// »óÀÇ ÇÏÀÇ Main Color Áö±ÝÀº ±×³É 0 À¸·Î ¼ÂÆÃ ÇØµÐ´Ù.
		pExtraSlotInfo->setMainColor(0);*/
	
		pExtraInfo->addListElement(pExtraSlotInfo);

		ItemCount++;

	}

	pExtraInfo->setListNum(ItemCount);

	return pExtraInfo;

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
//
// get Gear Info
//
//----------------------------------------------------------------------
GearInfo* Ousters::getGearInfo() const
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	int ItemCount = 0;

	GearInfo* pGearInfo = new GearInfo();

	for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			//Item::ItemClass IClass = pItem->getItemClass();

			GearSlotInfo* pGearSlotInfo = new GearSlotInfo();
			pItem->makePCItemInfo( *pGearSlotInfo );
			pGearSlotInfo->setSlotID(i);
/*
			pGearSlotInfo->setObjectID(pItem->getObjectID());
			pGearSlotInfo->setItemClass(pItem->getItemClass());
			pGearSlotInfo->setItemType(pItem->getItemType());
			pGearSlotInfo->setOptionType(pItem->getOptionTypeList());
			pGearSlotInfo->setDurability(pItem->getDurability());
			pGearSlotInfo->setSilver(pItem->getSilver());
			pGearSlotInfo->setEnchantLevel(pItem->getEnchantLevel());

			// ¾Ï½º¹êµå¶ó¸é Sub ¾ÆÀÌÅÛÀÇ Ãß°¡ Á¤º¸°¡ ÇÊ¿äÇÏ´Ù.
			if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND)
			{
				// ¾ÆÀÌÅÛ ÀÎÆ÷¸¦ ¹Þ¾Æ¿Â´Ù.
				ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());

				// Æ÷ÄÏÀÇ ¼ýÀÚ¸¦ ¹Þ¾Æ¿Â´Ù.
				BYTE PocketNum = ((OustersArmsbandInfo*)pItemInfo)->getPocketCount();

				// º§Æ®ÀÇ ÀÎº¥Åä¸®¸¦ ¹Þ¾Æ¿Â´Ù.
				Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pItem)->getInventory();

				BYTE SubItemCount = 0;

				// Æ÷ÄÏÀÇ ¼ýÀÚ¸¸Å­ ¾ÆÀÌÅÛÀÇ Á¤º¸¸¦ ÀÐ¾î µéÀÎ´Ù.
				for (int i = 0; i < PocketNum ; i++)
				{
					Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
					if (pOustersArmsbandItem != NULL)
					{
						SubItemInfo* pSubItemInfo = new SubItemInfo();
						pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
						pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
						pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
						pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
						pSubItemInfo->setSlotID(i);

						pGearSlotInfo->addListElement(pSubItemInfo);

						SubItemCount++;
					}
				}
				pGearSlotInfo->setListNum(SubItemCount);
			}

			pGearSlotInfo->setSlotID(i);
	
			// »óÀÇ ÇÏÀÇ Main Color Áö±ÝÀº ±×³É 0 À¸·Î ¼ÂÆÃ ÇØµÐ´Ù.
			pGearSlotInfo->setMainColor(0);*/
		
			pGearInfo->addListElement(pGearSlotInfo);

			ItemCount++;
		}
	}

	pGearInfo->setListNum(ItemCount);

	return pGearInfo;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get Inventory Info
//////////////////////////////////////////////////////////////////////////////
InventoryInfo* Ousters::getInventoryInfo() const
    
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	BYTE ItemCount = 0;

	InventoryInfo* pInventoryInfo = new InventoryInfo();
	list<Item*> ItemList;
	VolumeHeight_t Height = m_pInventory->getHeight();
	VolumeWidth_t Width = m_pInventory->getWidth();

	for (int j = 0; j < Height; j++) 
	{
		for (int i = 0 ; i < Width ; i ++) 
		{
			if (m_pInventory->hasItem(i, j)) 
			{
				Item* pItem = m_pInventory->getItem(i , j);
				VolumeWidth_t ItemWidth = pItem->getVolumeWidth();
				//Item::ItemClass IClass = pItem->getItemClass();
				list<Item*>::iterator itr = find(ItemList.begin() , ItemList.end() , pItem);

				if (itr == ItemList.end()) 
				{
					ItemList.push_back(pItem);

					// InventorySlotInfo¸¦ ±¸¼º
					InventorySlotInfo* pInventorySlotInfo = new InventorySlotInfo();
					pItem->makePCItemInfo( *pInventorySlotInfo );
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);
/*
					pInventorySlotInfo->setObjectID(pItem->getObjectID());
					pInventorySlotInfo->setItemClass(pItem->getItemClass());
					pInventorySlotInfo->setItemType(pItem->getItemType());
					pInventorySlotInfo->setOptionType(pItem->getOptionTypeList());
					pInventorySlotInfo->setSilver(pItem->getSilver());
					pInventorySlotInfo->setDurability(pItem->getDurability());
					pInventorySlotInfo->setEnchantLevel(pItem->getEnchantLevel());
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);
					pInventorySlotInfo->setItemNum(pItem->getNum());

					// ¾Ï½º¹êµå¶ó¸é Sub ¾ÆÀÌÅÛÀÇ Ãß°¡ Á¤º¸°¡ ÇÊ¿äÇÏ´Ù.
					if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
					{
						OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
						Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pItem)->getInventory();

						BYTE SubItemCount = 0;

						// Æ÷ÄÏÀÇ ¼ýÀÚ¸¸Å­ ¾ÆÀÌÅÛÀÇ Á¤º¸¸¦ ÀÐ¾î µéÀÎ´Ù.
						for (int i = 0; i < pOustersArmsband->getPocketCount() ; i++) 
						{
							Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
							if (pOustersArmsbandItem != NULL) 
							{
								SubItemInfo* pSubItemInfo = new SubItemInfo();
								pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
								pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
								pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
								pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
								pSubItemInfo->setSlotID(i);

								pInventorySlotInfo->addListElement(pSubItemInfo);

								SubItemCount++;
							}
						}

						pInventorySlotInfo->setListNum(SubItemCount);
					}

					pInventorySlotInfo->setMainColor(0);*/

					pInventoryInfo->addListElement(pInventorySlotInfo);
					ItemCount++;
					i = i + ItemWidth - 1;
				}
			}
		}
	}

	pInventoryInfo->setListNum(ItemCount);

	return pInventoryInfo;

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
// getSkillInfo
//----------------------------------------------------------------------
void Ousters::sendOustersSkillInfo()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	OustersSkillInfo* pOustersSkillInfo = new OustersSkillInfo();

	BYTE SkillCount = 0;

	// ÇöÀç ½Ã°£, ³²Àº Ä³½ºÆÃ Å¸ÀÓÀ» °è»êÇÏ±â À§ÇØ
	Timeval currentTime;
	getCurrentTime( currentTime );

	unordered_map<SkillType_t, OustersSkillSlot*>::const_iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		OustersSkillSlot* pOustersSkillSlot = itr->second;
		Assert(pOustersSkillSlot != NULL);

		// AttackMelee µîÀÇ ±âº» °ø°Ý ±â¼ú Á¤º¸´Â º¸³»ÁÖÁö ¾Ê¾Æ¾ß ÇÑ´Ù.
		if (pOustersSkillSlot->getSkillType() >= SKILL_DOUBLE_IMPACT)
		{
			SubOustersSkillInfo* pSubOustersSkillInfo = new SubOustersSkillInfo();
			pSubOustersSkillInfo->setSkillType(pOustersSkillSlot->getSkillType());
			pSubOustersSkillInfo->setExpLevel(pOustersSkillSlot->getExpLevel());
			pSubOustersSkillInfo->setSkillTurn(pOustersSkillSlot->getInterval());
			pSubOustersSkillInfo->setCastingTime(pOustersSkillSlot->getRemainTurn( currentTime ) );

			pOustersSkillInfo->addListElement(pSubOustersSkillInfo);

			SkillCount++;
		}
	}

	GCSkillInfo gcSkillInfo;
	gcSkillInfo.setPCType(PC_OUSTERS);
	SkillType_t LearnSkillType = g_pSkillInfoManager->getSkillTypeByLevel(SKILL_DOMAIN_OUSTERS , m_Level);

	// ÇöÀç ·¹º§¿¡¼­ ¹è¿ï ¼ö ÀÖ´Â ±â¼úÀÌ ÀÖ´ÂÁö º»´Ù.
	if (LearnSkillType != 0) 
	{
		// ¹è¿ï ¼ö ÀÖ´Â ±â¼úÀÌ ÀÖ°í ¹è¿ìÁö ¾ÊÀº »óÅÂ¶ó¸é ¹è¿ì¶ó°í ¾Ë·ÁÁØ´Ù.
		if (hasSkill(LearnSkillType) == NULL) 
		{
			pOustersSkillInfo->setLearnNewSkill(true);
		}
	}

	pOustersSkillInfo->setListNum(SkillCount);

	gcSkillInfo.addListElement(pOustersSkillInfo);

	m_pPlayer->sendPacket(&gcSkillInfo);

	__END_DEBUG
	__END_CATCH
}



////////////////////////////////////////////////////////////////////////////////
//
//
// ±âÅ¸ ÇÔ¼ö
//
//
////////////////////////////////////////////////////////////////////////////////
void Ousters::setGold(Gold_t gold)
	
{
	__BEGIN_TRY

    // MAX_MONEY ¸¦ ³Ñ¾î°¡´Â °É ¸·´Â´Ù
	// 2003.1.8  by bezz.
	m_Gold = min( (Gold_t)MAX_MONEY, gold );

	__END_CATCH
}

void Ousters::setGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY

	setGold(gold);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "Gold=%ld", m_Gold);
	tinysave(pField);

	__END_CATCH
}

void Ousters::increaseGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// MAX_MONEY ¸¦ ³Ñ¾î°¡´Â °É ¸·´Â´Ù
	// 2003.1.8  by bezz.
	if ( m_Gold + gold > MAX_MONEY )
		gold = MAX_MONEY - m_Gold;

	setGold(m_Gold+gold);

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Ousters SET Gold=Gold+%u WHERE NAME='%s'", gold, m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)


	__END_DEBUG
	__END_CATCH
}

void Ousters::decreaseGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// 0 ¹Ì¸¸ÀÌ µÇ´Â °É ¸·´Â´Ù. 0 ¹Ì¸¸ÀÌ µÇ¸é underflow µÇ¼­ ³­¸®°¡ ³­´Ù.
	// 2003.1.8  by bezz.
	if ( m_Gold < gold )
        gold = m_Gold;
	
	setGold(m_Gold-gold);

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Ousters SET Gold=Gold-%u WHERE NAME='%s'", gold, m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void Ousters::saveSilverDamage(Silver_t damage)
	    
{
	__BEGIN_TRY

	setSilverDamage(damage);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "SilverDamage=%d", m_SilverDamage);
	tinysave(pField);

	__END_CATCH
}

bool Ousters::checkGoldIntegrity()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	bool ret = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT Gold FROM Ousters WHERE NAME='%s'", m_Name.c_str());

		if ( pResult->next() )
		{
			ret = pResult->getInt(1) == m_Gold;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return ret;

	__END_CATCH
}

bool Ousters::checkStashGoldIntegrity()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	bool ret = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT StashGold FROM Ousters WHERE NAME='%s'", m_Name.c_str());

		if ( pResult->next() )
		{
			ret = pResult->getInt(1) == m_StashGold;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return ret;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ¼ÒÀ¯ ¾ÆÀÌÅÛ hearbeat
//////////////////////////////////////////////////////////////////////////////
void Ousters::heartbeat(const Timeval& currentTime)
    
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	PlayerCreature::heartbeat( currentTime );

	OustersSkillSlot* pDriftingSoul = hasSkill(SKILL_DRIFTING_SOUL);

	if ( pDriftingSoul != NULL && m_MPRegenTime < currentTime && !isFlag( Effect::EFFECT_CLASS_PLEASURE_EXPLOSION ) )
	{
		SkillLevel_t level = pDriftingSoul->getExpLevel();
		int bonus = 0;

		if ( getMP() < getMP(ATTR_MAX ) )
		{
			if ( level <= 15 ) bonus +=1;
			else if ( level <= 25 ) bonus += 2;
			else if ( level <= 29 ) bonus += 3;
			else if ( level <= 30 ) bonus += 4;

			MP_t oldMP = getMP();
			MP_t newMP = min( (int)getMP(ATTR_MAX), oldMP + bonus );

			if ( oldMP != newMP )
			{
				setMP(newMP);

				GCModifyInformation gcMI;
				gcMI.addShortData(MODIFY_CURRENT_MP, newMP);
				m_pPlayer->sendPacket(&gcMI);
			}
		}

		// 1ÃÊ ´ÜÀ§·Î ÇÏÆ®ºñÆ® ½ÃÅ²´Ù. 
		m_MPRegenTime.tv_sec = currentTime.tv_sec + 2;
		m_MPRegenTime.tv_usec = currentTime.tv_usec;
	}

	__END_DEBUG
	__END_CATCH
}

void Ousters::getOustersRecord(OUSTERS_RECORD& record) const
	
{
    __BEGIN_TRY

	record.pSTR[0]     = m_STR[0];
	record.pSTR[1]     = m_STR[1];
	record.pSTR[2]     = m_STR[2];

	record.pDEX[0]     = m_DEX[0];
	record.pDEX[1]     = m_DEX[1];
	record.pDEX[2]     = m_DEX[2];

	record.pINT[0]     = m_INT[0];
	record.pINT[1]     = m_INT[1];
	record.pINT[2]     = m_INT[2];

	record.pHP[0]      = m_HP[0];
	record.pHP[1]      = m_HP[1];

	record.pMP[0]      = m_MP[0];
	record.pMP[1]      = m_MP[1];

	record.pDamage[0]  = m_Damage[0];
	record.pDamage[1]  = m_Damage[1];

	record.Rank     = getRank();

	record.Defense     = m_Defense[0];
	record.ToHit       = m_ToHit[0];
	record.Protection  = m_Protection[0];
	record.AttackSpeed = m_AttackSpeed[0];

	__END_CATCH
}

void Ousters::setResurrectZoneIDEx(ZoneID_t id)
	
{
	__BEGIN_TRY

	setResurrectZoneID(id);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "ResurrectZone=%d", id);
	tinysave(pField);


	__END_CATCH
}

void Ousters::saveAlignment(Alignment_t alignment)
	    
{
	__BEGIN_TRY

	setAlignment(alignment);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "Alignment=%d", alignment);
	tinysave(pField);

	__END_CATCH
}


//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string Ousters::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Ousters("
		//<< "ObjectID:"   << (int)getObjectID()
		<< ",Name:"      << m_Name
		<< ",HairColor:" << (int)m_HairColor
		<< ",STR:"       << (int)m_STR[ATTR_CURRENT] << "/" << (int)m_STR[ATTR_MAX]
		<< ",DEX:"       << (int)m_DEX[ATTR_CURRENT] << "/" << (int)m_DEX[ATTR_MAX]
		<< ",INT:"       << (int)m_INT[ATTR_CURRENT] << "/" << (int)m_INT[ATTR_MAX]
		<< ",HP:"        << (int)m_HP[ATTR_CURRENT] << "/" << (int)m_HP[ATTR_MAX]
		<< ",MP:"        << (int)m_MP[ATTR_CURRENT] << "/" << (int)m_MP[ATTR_MAX]
		<< ",Fame:"      << (int)m_Fame
//		<< ",Exp:"       << (int)m_Exp
//		<< ",ExpOffset:" << (int)m_ExpOffset
		<< ",Rank:"       << (int)getRank()
		<< ",RankGoalExp:" << (int)getRankGoalExp()
		<< ",Level:"     << (int)m_Level
		<< ",Bonus:"     << (int)m_Bonus
		<< ",Gold:"      << (int)m_Gold
		<< ",ZoneID:"    << (int)getZoneID()
		<< ",XCoord:"    << (int)m_X
		<< ",YCoord:"    << (int)m_Y
		<< ",Sight:"     << (int)m_Sight
		<< ")";

	return msg.toString();

	__END_CATCH
}

void Ousters::saveSkills(void) const 
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::const_iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		OustersSkillSlot* pOustersSkillSlot = itr->second;
		Assert(pOustersSkillSlot != NULL);

		// ±âº» °ø°Ý ½ºÅ³ÀÌ ¾Æ´Ï¶ó¸é...
		if (pOustersSkillSlot->getSkillType() >= SKILL_DOUBLE_IMPACT)
		{
			pOustersSkillSlot->save(m_Name);
		}
	}

	__END_CATCH
}

Sight_t Ousters::getEffectedSight() 
{
	__BEGIN_TRY

	Sight_t sight = Creature::getEffectedSight();

	if ( sight == DEFAULT_SIGHT )
	{
//		if ( isFlag( Effect::EFFECT_CLASS_BLOOD_DRAIN ) )
//		{
//			sight = (Sight_t) 3;
//		}
	}

	return sight;

	__END_CATCH
}

IP_t Ousters::getIP(void) const
{
	Assert(m_pPlayer != NULL);
	Socket* pSocket = m_pPlayer->getSocket();
	Assert(pSocket != NULL);
	return pSocket->getHostIP();
}

void Ousters::saveGears(void) const
    
{
	__BEGIN_TRY

	// ÀåÂøÇÏ°í ÀÖ´Â ¾ÆÀÌÅÛµéÀ» ÀúÀåÇÑ´Ù.
	char pField[80];

	for (int i=0; i < Ousters::OUSTERS_WEAR_MAX; i++)
	{
		Item* pItem = m_pWearItem[i];
		if (pItem != NULL)
		{
			Durability_t maxDurability = computeMaxDurability(pItem);
			if (pItem->getDurability() < maxDurability)
			{
				//pItem->save(m_Name, STORAGE_GEAR, 0, i, 0);
				// itemÀúÀå ÃÖÀûÈ­. by sigi. 2002.5.13
				sprintf(pField, "Durability=%d", pItem->getDurability());
				pItem->tinysave(pField);
			}
		}
	}

	__END_CATCH
}


void Ousters::saveExps(void) const
    
{
	__BEGIN_TRY

	// ½ºÅ³ ÇÚµé·¯¿¡¼­ Äõ¸® ¼ýÀÚ¸¦ ÁÙÀÌ±â À§ÇØ¼­ 10À¸·Î ³ª´©´Â ºÎºÐµéÀº,
	// ¼­¹ö ´Ù¿îÀÌ µÇÁö ¾Ê°í, Á¤»óÀûÀ¸·Î ·Î±×¾Æ¿ôÇÏ´Â °æ¿ì¿¡ 
	// ¼¼ÀÌºê¸¦ ¸í½ÃÀûÀ¸·Î ÇØÁÖÁö ¾ÊÀ¸¸é 10 ÀÌÇÏ ¿Ã¶ó°£ ºÎºÐÀº ³¯¾Æ°¡ ¹ö¸®°Ô µÈ´Ù.
	// ±×·¯¹Ç·Î ¿©±â¼­ ¼¼ÀÌºê¸¦ ÇØ ÁØ´Ù. 
	Statement* pStmt = NULL;

/*	char silverDam[40];
	if (m_SilverDamage != 0)
	{
		sprintf(silverDam, ",SilverDamage = %d", m_SilverDamage);
	}
	else silverDam[0]='\0'; */

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "UPDATE Ousters SET Alignment=%d, Fame=%d, GoalExp=%lu, SilverDamage = %d, `Rank`=%d, RankGoalExp=%lu, AdvancementClass=%u, AdvancementGoalExp=%d WHERE Name='%s'",
							m_Alignment, m_Fame, m_GoalExp, m_SilverDamage, getRank(), getRankGoalExp(), getAdvancementClassLevel(), getAdvancementClassGoalExp(), m_Name.c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//----------------------------------------------------------------------
// getShapeInfo
//----------------------------------------------------------------------
// loginÇÒ¶§ Ã³¸®¸¦ »¡¸®ÇÏ±â À§ÇØ¼­´Ù.
//----------------------------------------------------------------------
// ÀÏ´Ü 32bit·Î 32°¡Áö¸¦ Ç¥ÇöÇÏ´Â°É·Îµµ ÃæºÐÇÏ´Ù°í º»´Ù.
// ¾ðÁ¨°¡? overµÇ¸é bitsetÀ» ½á¾ß°ÚÁö..
//
// (!) »ö±òÀº index»ö°ªÀÌ ¾Æ´Ï°í optionTypeÀ» ³Ö¾î¼­ »ç¿ëÇÑ´Ù.
//     Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¿É¼ÇÀ¸·Î »ö°ªÀ» Ã£¾Æ¼­ ¾´´Ù.
//
// colors[1]Àº coatColor¸¸ ÀÖ±â ¶§¹®ÀÌ´Ù.
//----------------------------------------------------------------------
/*void Ousters::getShapeInfo (DWORD& flag, Color_t colors[PCOustersInfo::OUSTERS_COLOR_MAX]) const
//	
{
	__BEGIN_DEBUG

	Item* 						pItem;
	//OptionInfo* 				pOptionInfo;
	int							oustersBit;
	int							oustersColor;
	WearPart					Part;

	// ÃÊ±âÈ­
	flag = 0;

	//-----------------------------------------------------------------
	// º¹Àå
	//-----------------------------------------------------------------
	Part = WEAR_COAT;
	pItem = m_pWearItem[Part];
	oustersBit = 0;
	oustersColor = 0;

	if (pItem!=NULL && m_pRealWearingCheck[Part])
	{
		ItemType_t IType = pItem->getItemType();

		colors[oustersColor] = getItemShapeColor( pItem );

		// itemTypeÀ» ³Ö¾îÁØ´Ù.
		flag = IType;
	} 
	else 
	{
		colors[oustersColor] = 377;
		flag = (m_Sex? 0 : 1);
	}

	__END_DEBUG
}*/


//----------------------------------------------------------------------
// save InitialRank
//----------------------------------------------------------------------
// Rank, RankExp, RankGoalExpÀÇ ÃÊ±â°ªÀ» ÀúÀåÇÑ´Ù.
//----------------------------------------------------------------------
void Ousters::saveInitialRank(void)
	
{
	OUSTERS_RECORD prev;
	getOustersRecord(prev);

	int curRank = max(1, (m_Level+3) / 4);
	m_pRank->SET_LEVEL(curRank);

/*	RankExp_t accumExp = 0;

	if (curRank!=1)
	{
		RankEXPInfo* pBeforeExpInfo = g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->getRankEXPInfo(curRank-1);
		accumExp = pBeforeExpInfo->getAccumExp();
	}
	
	RankEXPInfo* pNextExpInfo = g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->getRankEXPInfo(curRank);
	Exp_t NextGoalExp = pNextExpInfo->getGoalExp();

	setRankGoalExp(NextGoalExp);
*/
	char pField[80];
	sprintf(pField, "`Rank`=%d, RankExp=%lu, RankGoalExp=%lu",
					getRank(), getRankExp(), getRankGoalExp());
	tinysave(pField);
	setRankExpSaveCount(0);
}

bool
Ousters::addShape(Item::ItemClass IClass, ItemType_t IType, Color_t color)
{
	bool bisChange = false;

	switch (IClass)
	{
		/*case Item::ITEM_CLASS_OUSTERS_COAT:
		{
			bisChange = true;

			m_OustersInfo.setCoatColor( color );
			m_OustersInfo.setCoatType( IType );
		}
		break;
*/
		default:
			break;
	}

	return bisChange;
}


bool
Ousters::removeShape(Item::ItemClass IClass, bool bSendPacket)
{
    bool bisChange = false;

	switch (IClass)
	{
		/*case Item::ITEM_CLASS_OUSTERS_COAT :
		{
			m_OustersInfo.setCoatColor(377);
			m_OustersInfo.setCoatType( 0 );

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_COAT);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
		}
		break;
*/
		default :
			return false;
	}

	return bisChange;
}

Color_t 
Ousters::getItemShapeColor(Item* pItem, OptionInfo* pOptionInfo) const
{
	Color_t color;

	if (pItem->isTimeLimitItem())
	{
		color = QUEST_COLOR;
	}
	else if (pItem->isUnique())
	{
		// À¯´ÏÅ©´Â Æ¯Á¤ÇÑ »ö±ò·Î ´ëÃ¼ÇØ¼­ Ã³¸®ÇÑ´Ù.
		color = UNIQUE_COLOR;
	}
	// ¿ÜºÎ¿¡¼­ ÀÌ¹Ì OptionInfo¸¦ Ã£Àº °æ¿ì
	else if (pOptionInfo != NULL) 
	{
		color = pOptionInfo->getColor();
	}
	// ¾Æ´Ï¸é.. Ã¹¹øÂ° ¿É¼ÇÀÇ »ö±òÀ» ÁöÁ¤ÇÑ´Ù.
	else if (pItem->getFirstOptionType() != 0)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getFirstOptionType());
		color = pOptionInfo->getColor();
	}
	else 
	{
		// default »ö
		color = 377;
	}

	return color;
}

bool Ousters::canPlayFree()
	
{
	__BEGIN_TRY

	return m_Level <= g_pVariableManager->getVariable(FREE_PLAY_OUSTERS_LEVEL);

	__END_CATCH
}

bool Ousters::satisfySkillRequire( SkillInfo* pSkillInfo )
{
	if ( isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) )
		return false;
	if ( pSkillInfo->getRequireFire() > m_ElementalFire )
		return false;
	if ( pSkillInfo->getRequireWater() > m_ElementalWater )
		return false;
	if ( pSkillInfo->getRequireEarth() > m_ElementalEarth )
		return false;
	if ( pSkillInfo->getRequireWind() > m_ElementalWind )
		return false;
	if ( pSkillInfo->getRequireSum() > getElementalSum() )
		return false;

	if ( pSkillInfo->getRequireWristletElemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_LEFTHAND)
				|| m_pWearItem[WEAR_LEFTHAND]->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET )
			return false;

		OustersWristlet* pWristlet = dynamic_cast<OustersWristlet*>(m_pWearItem[WEAR_LEFTHAND]);
		Assert( pWristlet != NULL );

		if ( pSkillInfo->getRequireWristletElemental() != pWristlet->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone1Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE1)
				|| m_pWearItem[WEAR_STONE1]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE1]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone1Elemental() != pStone->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone2Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE2)
				|| m_pWearItem[WEAR_STONE2]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE2]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone2Elemental() != pStone->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone3Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE3)
				|| m_pWearItem[WEAR_STONE3]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE3]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone3Elemental() != pStone->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone4Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE4)
				|| m_pWearItem[WEAR_STONE4]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE4]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone4Elemental() != pStone->getElementalType() )
			return false;
	}

	return true;
}

SkillBonus_t Ousters::getSkillPointCount( ElementalDomain eDomain )
{
	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();
	SkillBonus_t ret = 0;

	for ( ; itr != m_SkillSlot.end() ; ++itr )
	{
		OustersSkillSlot* pSlot = itr->second;
		if ( pSlot->getSkillType() < SKILL_DOUBLE_IMPACT ) continue;
		SkillInfo* pInfo = g_pSkillInfoManager->getSkillInfo( pSlot->getSkillType() );
		if ( pInfo == NULL ) continue;
		if ( pInfo->getElementalDomain() == eDomain )
		{
			ret += (pInfo->getSkillPoint() + pInfo->getLevelUpPoint() * (pSlot->getExpLevel()-1));
		}
	}

	cout << (int)eDomain << "¿¡ ³ÖÀº ½ºÅ³Æ÷ÀÎÆ® : " << ret << endl;

	return ret;
}

bool Ousters::isPayPlayAvaiable() 
	
{
	__BEGIN_TRY

	if (m_pPlayer==NULL)
		return false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);

#ifdef __CONNECT_BILLING_SYSTEM__
	if (pGamePlayer->isPayPlaying())
	{
		// ¿ÏÀü ¹«·á »ç¿ëÀÚ. ¤»¤»
		if (pGamePlayer->getPayType()==PAY_TYPE_FREE)
			return true;

		// Á¦ÇÑµÈ ·¹º§±îÁö play°¡´É
		if (m_Level <= g_pVariableManager->getVariable(FREE_PLAY_OUSTERS_LEVEL))
		{
			return true;
		}
	}

	return false;

// ¾Öµåºô ºô¸µÀ» »ç¿ëÇÏÁö ¾Ê°í »ç¿ëÀÚ Á¦ÇÑÀ» ÇÏ´Â °æ¿ì
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)

	if (!pGamePlayer->isPayPlaying())
	{
		// Á¦ÇÑµÈ ·¹º§±îÁö play°¡´É
		if (m_Level <= g_pVariableManager->getVariable(FREE_PLAY_OUSTERS_LEVEL))
		{
			return true;
		}

		return false;
	}

	return true;

#else

	return pGamePlayer->isPayPlaying();

#endif


	__END_CATCH
}

void Ousters::initPetQuestTarget()
{
	int minClass = 1, maxClass = 1;

	if ( getLevel() <= 50 )
	{
		minClass = 6; maxClass = 7;
	}
	else if ( getLevel() <= 60 )
	{
		minClass = 7; maxClass = 8;
	}
	else if ( getLevel() <= 70 )
	{
		minClass = maxClass = 9;
	}
	else if ( getLevel() <= 80 )
	{
		minClass = 9; maxClass = 10;
	}
	else if ( getLevel() <= 90 )
	{
		minClass = maxClass = 10;
	}
	else if ( getLevel() <= 110 )
	{
		minClass = 10; maxClass = 11;
	}
	else if ( getLevel() <= 130 )
	{
		minClass = 11; maxClass = 12;
	}
	else
	{
		minClass = 12; maxClass = 13;
	}

	m_TargetMonster = g_pMonsterInfoManager->getRandomMonsterByClass( minClass, maxClass );
	m_TargetNum = 80;
	m_TimeLimit = 3600;
}

bool Ousters::canLearnSkill(SkillType_t skill)
{
    SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(skill);
    if ( pSkillInfo == NULL ) return false;

    if ( pSkillInfo->getLevel() >= 150 )
    {
        unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();

        for ( ; itr != m_SkillSlot.end() ; ++itr )
        {
            if ( itr->first < SKILL_DOUBLE_IMPACT ) continue;
            SkillInfo* pHasSkillInfo = g_pSkillInfoManager->getSkillInfo( itr->first );
            if ( pHasSkillInfo == NULL ) continue;
            //if ( pHasSkillInfo->getLevel() == pSkillInfo->getLevel() && !(pSkillInfo->getType() > 400 )) return false;
            if ( (skill >= 370 && skill <= 373) &&
                 (pHasSkillInfo->getType() >= 370 && pHasSkillInfo->getType() <= 373 ))
            {
                return false; // 20080701 ��ų �������� �ٲ۴�.
            }
        }
    }

    return true;
}
