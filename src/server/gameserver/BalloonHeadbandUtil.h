//////////////////////////////////////////////////////////////////////////////
// Filename    : BalloonHeadbandUtil.h
// Written By  : Bezz
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __BALLOON_HEADBAND_UTIL_H__
#define __BALLOON_HEADBAND_UTIL_H__

class Item;
class PlayerCreature;
class Monster;

#include "Types.h"
#include <list>

enum BalloonHeadband
{
	NO_BALLOON_HEADBAND = 0,
	RED_BALLOON_HEADBAND,		// 1
	YELLOW_BALLOON_HEADBAND,	// 2
	BLUE_BALLOON_HEADBAND,		// 3
	PURPLE_BALLOON_HEADBAND,	// 4
	BLACK_BALLOON_HEADBAND,		// 5

	BALLOON_HEADBAND_MAX
};

BalloonHeadband getBalloonHeadbandKind(PlayerCreature* pPC, Monster* pMonster);
Item* getBalloonHeadbandItem(BalloonHeadband kind);

BalloonHeadband getBalloonHeadbandKindByItemType(ItemType_t itemType);
list<OptionType_t> getBalloonHeadbandOptionTypes(BalloonHeadband kind);

void applyBalloonHeadbandDefaultOption(PlayerCreature* pPC, ItemType_t itemType);

#endif// __BALLOON_HEADBAND_UTIL_H__

