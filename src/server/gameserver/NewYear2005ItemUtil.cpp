
#include "EventItemUtil.h"
#include "Item.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "VariableManager.h"

#include "ItemFactoryManager.h"

#include <list>

NewYear2005Item getNewYear2005ItemKind( PlayerCreature* pPC, Monster* pMonster )
{
	if ( rand() % g_pVariableManager->getVariable( BOKJORY_RATIO ) == 0 )
	{
		return BOKJORY;
	}
	else if ( rand() % g_pVariableManager->getVariable( EVENT_BLACK_RICE_CAKE_SOUP_RATIO ) == 0 )
	{
		return EVENT_BLACK_RICE_CAKE_SOUP;
	}
	else if ( rand() % g_pVariableManager->getVariable( EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO ) == 0 )
	{
		return EVENT_MUGWORT_RICE_CAKE_SOUP;
	}
	else if ( rand() % g_pVariableManager->getVariable( EVENT_RED_RICE_CAKE_SOUP_RATIO ) == 0 )
	{
		return EVENT_RED_RICE_CAKE_SOUP;
	}
	else if ( rand() % g_pVariableManager->getVariable( EVENT_GREEN_RICE_CAKE_SOUP_RATIO ) == 0 )
	{
		return EVENT_GREEN_RICE_CAKE_SOUP;
	}
	else if ( rand() % g_pVariableManager->getVariable( EVENT_BLUE_RICE_CAKE_SOUP_RATIO ) == 0 )
	{
		return EVENT_BLUE_RICE_CAKE_SOUP;
	}

	return NO_ITEM;
}

Item* getNewYear2005Item( NewYear2005Item kind )
{
	Item* ret = NULL;

	switch ( kind )
	{
		case NO_ITEM:
			break;

		case BOKJORY:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MIXING_ITEM, 18, list<OptionType_t>() );
			break;

		case EVENT_RED_RICE_CAKE_SOUP:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 17, list<OptionType_t>() );
			break;

		case EVENT_GREEN_RICE_CAKE_SOUP:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 18, list<OptionType_t>() );
			break;

		case EVENT_BLUE_RICE_CAKE_SOUP:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 19, list<OptionType_t>() );
			break;

		case EVENT_BLACK_RICE_CAKE_SOUP:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 20, list<OptionType_t>() );
			break;

		case EVENT_MUGWORT_RICE_CAKE_SOUP:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_STAR, 21, list<OptionType_t>() );
			break;

		default:
			break;
	}

	return ret;
}

