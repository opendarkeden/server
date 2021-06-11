
#include "EventItemUtil.h"
#include "Item.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "VariableManager.h"

#include "ItemFactoryManager.h"
#include "DB.h"

#include <list>

MoonCard getCardKind( PlayerCreature* pPC, Monster* pMonster )
{
	int UserLevel, MonsterLevel = pMonster->getLevel();

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		UserLevel = pSlayer->getHighestSkillDomainLevel();
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		UserLevel = pVampire->getLevel();
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		UserLevel = pOusters->getLevel();
	}
	else return NO_CARD;

	if ( UserLevel > 100 ) UserLevel = 100;
	if ( UserLevel > MonsterLevel + 20 ) return NO_CARD;

	if ( rand() % g_pVariableManager->getVariable( FULL_MOON_CARD_RATIO ) == 0 )
	{
		return FULL_MOON;
	}
	else if ( rand() % g_pVariableManager->getVariable( OLD_MOON_CARD_RATIO ) == 0 )
	{
		return OLD_MOON;
	}
	else if ( rand() % g_pVariableManager->getVariable( NEW_MOON_CARD_RATIO ) == 0 )
	{
		return NEW_MOON;
	}
	else if ( rand() % g_pVariableManager->getVariable( HALF_MOON_CARD_RATIO ) == 0 )
	{
		return HALF_MOON;
	}

	return NO_CARD;
}

Item* getCardItem( MoonCard card )
{
	Item* ret = NULL;
	bool putInDB = false;

	switch ( card )
	{
		case NO_CARD:
			break;
		case FULL_MOON:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_QUEST_ITEM, 5, list<OptionType_t>() );
			putInDB = true;
			break;
		case OLD_MOON:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_QUEST_ITEM, 6, list<OptionType_t>() );
			putInDB = true;
			break;
		case HALF_MOON:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MOON_CARD, 0, list<OptionType_t>() );
			putInDB = true;
			break;
		case NEW_MOON:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_MOON_CARD, 1, list<OptionType_t>() );
			putInDB = true;
			break;
		default:
			break;
	}

	if ( putInDB )
	{
		filelog( "MoonCard.log", "아이템이 나왔습니다. : %d", (int)card );
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery("UPDATE CardCount SET CARDCOUNT = CARDCOUNT + 1 WHERE CARDKIND = %d", (int)card - 1);

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}

	return ret;
}

LuckyBag getLuckyBagKind( PlayerCreature* pPC, Monster* pMonster )
{
	int UserLevel, MonsterLevel = pMonster->getLevel();

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		UserLevel = pSlayer->getHighestSkillDomainLevel();
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		UserLevel = pVampire->getLevel();
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		UserLevel = pOusters->getLevel();
	}
	else return NO_LUCKY_BAG;

	if ( UserLevel > 100 ) UserLevel = 100;

	if ( UserLevel > MonsterLevel + 30 ) return NO_LUCKY_BAG;

	if ( rand() % g_pVariableManager->getVariable( GREEN_LUCKY_BAG_RATIO ) == 0 )
	{
		return GREEN_LUCKY_BAG;
	}
	else if ( rand() % g_pVariableManager->getVariable( BLUE_LUCKY_BAG_RATIO ) == 0 )
	{
		return BLUE_LUCKY_BAG;
	}
	else if ( rand() % g_pVariableManager->getVariable( GOLD_LUCKY_BAG_RATIO ) == 0 )
	{
		return GOLD_LUCKY_BAG;
	}
	else if ( rand() % g_pVariableManager->getVariable( RED_LUCKY_BAG_RATIO ) == 0 )
	{
		return RED_LUCKY_BAG;
	}

	return NO_LUCKY_BAG;
}

Item* getLuckyBagItem( LuckyBag luckybag )
{
	Item* ret = NULL;
	bool putInDB = false;

	switch ( luckybag )
	{
		case NO_LUCKY_BAG:
			break;
		case GREEN_LUCKY_BAG:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_LUCKY_BAG, 0, list<OptionType_t>() );
			putInDB = true;
			break;
		case BLUE_LUCKY_BAG:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_LUCKY_BAG, 1, list<OptionType_t>() );
			putInDB = true;
			break;
		case GOLD_LUCKY_BAG:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_LUCKY_BAG, 2, list<OptionType_t>() );
			putInDB = true;
			break;
		case RED_LUCKY_BAG:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_QUEST_ITEM, 7, list<OptionType_t>() );
			putInDB = true;
			break;
		default:
			break;
	}

	if ( putInDB )
	{
		filelog( "LuckyBag.log", "아이템이 나왔습니다. : %d", (int)luckybag );
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery("UPDATE LuckyBagCount SET BAGCOUNT = BAGCOUNT + 1 WHERE BAGKIND = %d", (int)luckybag - 1);

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}

	return ret;
}

GiftBox getGiftBoxKind( PlayerCreature* pPC, Monster* pMonster )
{
	int UserLevel, MonsterLevel = pMonster->getLevel();

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		UserLevel = pSlayer->getHighestSkillDomainLevel();
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		UserLevel = pVampire->getLevel();
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		UserLevel = pOusters->getLevel();
	}
	else return NO_GIFT_BOX;

	if ( UserLevel > 100 ) UserLevel = 100;

	if ( UserLevel > MonsterLevel + 30 ) return NO_GIFT_BOX;


	if ( rand() % g_pVariableManager->getVariable( RED_GIFT_BOX_RATIO ) == 0 )
	{
		return RED_GIFT_BOX;
	}
	else if ( rand() % g_pVariableManager->getVariable( BLUE_GIFT_BOX_RATIO ) == 0 )
	{
		return BLUE_GIFT_BOX;
	}
	else if ( rand() % g_pVariableManager->getVariable( GREEN_GIFT_BOX_RATIO ) == 0 )
	{
		return GREEN_GIFT_BOX;
	}
	else if ( rand() % g_pVariableManager->getVariable( YELLOW_GIFT_BOX_RATIO ) == 0 )
	{
		return YELLOW_GIFT_BOX;
	}

	return NO_GIFT_BOX;
}

Item* getGiftBoxItem( GiftBox giftbox )
{
	Item* ret = NULL;
	bool putInDB = false;

	switch ( giftbox )
	{
		case NO_GIFT_BOX:
			break;
		case RED_GIFT_BOX:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 2, list<OptionType_t>() );
			putInDB = true;
			break;
		case BLUE_GIFT_BOX:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 3, list<OptionType_t>() );
			putInDB = true;
			break;
		case GREEN_GIFT_BOX:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 4, list<OptionType_t>() );
			putInDB = true;
			break;
		case YELLOW_GIFT_BOX:
			ret = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 5, list<OptionType_t>() );
			putInDB = true;
			break;
		default:
			break;
	}

	if ( putInDB )
	{
		filelog( "GiftBox.log", "아이템이 나왔습니다. : %d", (int)giftbox + 1 );
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery("UPDATE GiftBoxCount SET BOXCOUNT = BOXCOUNT + 1 WHERE BOXKIND = %d", (int)giftbox + 1 );

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}

	return ret;
}

int getBlackGiftBoxType( int t1, int t2)
{

	// 필살 하드코딩이다 -ㅠ-
	int min = 0;
	int max = 0;

	if ( t1 > t2 )
	{
		min = t2;
		max = t1;
	}
	else
	{
		min = t1;
		max = t2;
	}


	if ( min == 2 && max == 2 )
		return 6;
	else if ( min == 2 && max == 3 )
		return 7;
	else if ( min == 2 && max == 4 )
		return 8;
	else if ( min == 2 && max == 5 )
		return 9;
	else if ( min == 3 && max == 3 )
		return 10;
	else if ( min == 3 && max == 4 )
		return 11;
	else if ( min == 3 && max == 5 )
		return 12;
	else if ( min == 4 && max == 4 )
		return 13;
	else if ( min == 4 && max == 5 )
		return 14;
	else if ( min == 5 && max == 5 )
		return 15;

	return 0;
}

bool canGiveEventItem( PlayerCreature* pPC, Monster* pMonster )
{
	int UserLevel, MonsterLevel = pMonster->getLevel();

	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		UserLevel = pSlayer->getHighestSkillDomainLevel();
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		UserLevel = pVampire->getLevel();
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		UserLevel = pOusters->getLevel();
	}
	else return false;

	if ( UserLevel > 120 ) UserLevel = 120;

	if ( UserLevel > MonsterLevel + 30 ) return false;

	return true;
}

void logEventItemCount(Item* pEventItem)
	
{
	if ( pEventItem == NULL ) return;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE EventItemCount SET Count = Count + 1 WHERE ItemClass=%u AND ItemType=%u",
				(uint)pEventItem->getItemClass(), 
				(uint)pEventItem->getItemType());

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)
}
