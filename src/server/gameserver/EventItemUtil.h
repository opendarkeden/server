#ifndef __EVENT_ITEM_UTIL_H__
#define __EVENT_ITEM_UTIL_H__

#include "Types.h"
#include "Exception.h"

class Item;
class PlayerCreature;
class Monster;

enum MoonCard
{
	NO_CARD,
	FULL_MOON,
	OLD_MOON,
	HALF_MOON,
	NEW_MOON
};

MoonCard getCardKind( PlayerCreature* pPC, Monster* pMonster );
Item* getCardItem( MoonCard card );

enum LuckyBag
{
	NO_LUCKY_BAG,
	GREEN_LUCKY_BAG,
	BLUE_LUCKY_BAG,
	GOLD_LUCKY_BAG,
	RED_LUCKY_BAG
};

LuckyBag getLuckyBagKind( PlayerCreature* pPC, Monster* pMonster );
Item* getLuckyBagItem( LuckyBag luckybag );

enum GiftBox
{
	NO_GIFT_BOX,
	RED_GIFT_BOX,
	BLUE_GIFT_BOX,
	GREEN_GIFT_BOX,
	YELLOW_GIFT_BOX
};

GiftBox getGiftBoxKind( PlayerCreature* pPC, Monster* pMonster );
Item* getGiftBoxItem( GiftBox giftbox );

int getBlackGiftBoxType( int t1, int t2);
bool canGiveEventItem( PlayerCreature* pPC, Monster* pMonster );

enum NewYear2005Item
{
	NO_ITEM,
	BOKJORY,
	EVENT_RED_RICE_CAKE_SOUP,
	EVENT_GREEN_RICE_CAKE_SOUP,
	EVENT_BLUE_RICE_CAKE_SOUP,
	EVENT_BLACK_RICE_CAKE_SOUP,
	EVENT_MUGWORT_RICE_CAKE_SOUP,
};

NewYear2005Item getNewYear2005ItemKind( PlayerCreature* pPC, Monster* pMonster );
Item* getNewYear2005Item( NewYear2005Item kind );

void logEventItemCount(Item* pEventItem) throw(Error);

#endif// __EVENT_ITEM_UTIL_H__

