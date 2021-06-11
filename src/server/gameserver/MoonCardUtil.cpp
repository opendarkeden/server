
#include "MoonCardUtil.h"
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
