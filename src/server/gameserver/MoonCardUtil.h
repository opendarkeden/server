#ifndef __MOON_CARD_H__
#define __MOON_CARD_H__

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

#endif// __MOON_CARD_H__
