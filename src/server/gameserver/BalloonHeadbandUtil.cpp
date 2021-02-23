//////////////////////////////////////////////////////////////////////////////
// Filename    : BalloonHeadbandUtil.cpp
// Written By  : Bezz
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BalloonHeadbandUtil.h"
#include "Item.h"
#include "VariableManager.h"
#include "ItemUtil.h"
#include "OptionInfo.h"
#include "PlayerCreature.h"

#include "ItemFactoryManager.h"
#include "DB.h"

BalloonHeadband getBalloonHeadbandKind(PlayerCreature* pPC, Monster* pMonster )
{
	if (g_pVariableManager->getVariable(BALLOON_HEADBAND_RATIO ) == 0 )
		return NO_BALLOON_HEADBAND;

	int value = rand() % g_pVariableManager->getVariable(BALLOON_HEADBAND_RATIO);

	if (value == 0 )
	{
		BalloonHeadband kind = (BalloonHeadband)(rand() % 5 + 1);

		return kind;
	}

	return NO_BALLOON_HEADBAND;
}

Item* getBalloonHeadbandItem(BalloonHeadband kind )
{
	Item* ret = NULL;
	bool putInDB = false;

	switch (kind )
	{
		case NO_BALLOON_HEADBAND:
			break;

		case RED_BALLOON_HEADBAND:
			ret = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ITEM, 32, list<OptionType_t>());
			putInDB = true;
			break;

		case YELLOW_BALLOON_HEADBAND:
			ret = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ITEM, 33, list<OptionType_t>());
			putInDB = true;
			break;

		case BLUE_BALLOON_HEADBAND:
			ret = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ITEM, 34, list<OptionType_t>());
			putInDB = true;
			break;

		case PURPLE_BALLOON_HEADBAND:
			ret = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ITEM, 35, list<OptionType_t>());
			putInDB = true;
			break;

		case BLACK_BALLOON_HEADBAND:
			ret = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ITEM, 36, list<OptionType_t>());
			putInDB = true;
			break;

		default:
			break;
	}

	if (putInDB )
	{
		filelog("BalloonHeadband.log", "아이템이 나왔습니다. : %d", (int)kind);

		increaseEventItemCount(ret);
	}

	return ret;
}

BalloonHeadband getBalloonHeadbandKindByItemType(ItemType_t itemType )
{
	switch (itemType )
	{
		case 32:
			return RED_BALLOON_HEADBAND;
			break;

		case 33:
			return YELLOW_BALLOON_HEADBAND;
			break;

		case 34:
			return BLUE_BALLOON_HEADBAND;
			break;

		case 35:
			return PURPLE_BALLOON_HEADBAND;
			break;

		case 36:
			return BLACK_BALLOON_HEADBAND;
			break;

		default:
			break;
	}

	return NO_BALLOON_HEADBAND;
}

list<OptionType_t> getBalloonHeadbandOptionTypes(BalloonHeadband kind )
{
	list<OptionType_t> ret;

	switch (kind )
	{
		case RED_BALLOON_HEADBAND:
			ret.push_back(g_pOptionInfoManager->getOptionType("STR+1" ));		// STR +3
			ret.push_back(g_pOptionInfoManager->getOptionType("MP+2" ));			// MP +10
			ret.push_back(g_pOptionInfoManager->getOptionType("VIS+3" ));		// VIS +3
			break;

		case YELLOW_BALLOON_HEADBAND:
			ret.push_back(g_pOptionInfoManager->getOptionType("CURES+1" ));		// CURRES +5
			ret.push_back(g_pOptionInfoManager->getOptionType("ASPD+2" ));		// ASPD +10
			ret.push_back(g_pOptionInfoManager->getOptionType("CRI+2" ));		// CRI +4
			break;

		case BLUE_BALLOON_HEADBAND:
			ret.push_back(g_pOptionInfoManager->getOptionType("INT+1" ));		// INT +1
			ret.push_back(g_pOptionInfoManager->getOptionType("HP+5" ));			// HP +15
			ret.push_back(g_pOptionInfoManager->getOptionType("TOHIT+3" ));		// TOHIT +3
			break;

		case PURPLE_BALLOON_HEADBAND:
			ret.push_back(g_pOptionInfoManager->getOptionType("DEX+1" ));		// DEX +1
			ret.push_back(g_pOptionInfoManager->getOptionType("BLRES+1" ));		// BLRES +5
			ret.push_back(g_pOptionInfoManager->getOptionType("ATTR+1" ));		// ATTR +1
			break;

		case BLACK_BALLOON_HEADBAND:
			ret.push_back(g_pOptionInfoManager->getOptionType("DAM+2" ));		// DAM +2
			ret.push_back(g_pOptionInfoManager->getOptionType("PRO+3" ));		// PRO +3
			ret.push_back(g_pOptionInfoManager->getOptionType("LUCK+3" ));		// LUCK +3
			break;

		default:
			break;
	}

	return ret;
}

void applyBalloonHeadbandDefaultOption(PlayerCreature* pPC, ItemType_t itemType )
{
	list<OptionType_t> options = getBalloonHeadbandOptionTypes(getBalloonHeadbandKindByItemType(itemType ));

	list<OptionType_t>::iterator itr = options.begin();
	list<OptionType_t>::iterator end = options.end();

	for (; itr != end; ++itr )
	{
		pPC->addDefaultOptionType(*itr);
	}
}

