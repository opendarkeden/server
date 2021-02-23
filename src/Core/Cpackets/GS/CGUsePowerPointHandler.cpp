//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePowerPointHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGUsePowerPoint.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "ItemFactoryManager.h"
	#include "Inventory.h"
	#include "Assert.h"

	#include "mofus/Mofus.h"
	#include "Gpackets/GCUsePowerPointResult.h"
	#include "Gpackets/GCCreateItem.h"

struct POWER_POINT_ITEM_TEMPLATE
{
	GCUsePowerPointResult::ITEM_CODE	ItemCode;
	Item::ItemClass						ItemClass;
	ItemType_t							ItemType;
	uint								Ratio;
	string								ItemName;
};
// edit by Coffee  2006-12-10  ÐÞ¸Ä²©²ÊÏµÍ³µÀ¾ß
const POWER_POINT_ITEM_TEMPLATE PowerPointItemTemplate[7] =
{
	{ GCUsePowerPointResult::CANDY,					Item::ITEM_CLASS_EVENT_ETC,			14,	20,	"Áéµ¤" },
	{ GCUsePowerPointResult::RESURRECTION_SCROLL,	Item::ITEM_CLASS_RESURRECT_ITEM,	0,	20,	"¸´»î¾íÖá" },
	{ GCUsePowerPointResult::ELIXIR_SCROLL,			Item::ITEM_CLASS_RESURRECT_ITEM,	1,	20,	"Á¶½ð¾íÖá" },
	{ GCUsePowerPointResult::MEGAPHONE,				Item::ITEM_CLASS_EFFECT_ITEM,		0,	20,	"¶Ô½²»ú1" },
	{ GCUsePowerPointResult::NAMING_PEN,			Item::ITEM_CLASS_EVENT_GIFT_BOX,	22,	14,	"êÇ³ÆÇ©Ãû±Ê" },
	{ GCUsePowerPointResult::SIGNPOST,				Item::ITEM_CLASS_EVENT_STAR,		6,	1,	"À¶±¦Ê¯(×ãÇò)" },
	{ GCUsePowerPointResult::BLACK_RICE_CAKE_SOUP,	Item::ITEM_CLASS_EVENT_STAR,		11, 5,	"ºÚÉ«×£¸£" }

};
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUsePowerPointHandler::execute (CGUsePowerPoint* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );


    cout << "--------------------------------------------------" << endl;
    cout << "RECV UsePowerPoint (Name:" << pCreature->getName() << ")" << endl;
    cout << "--------------------------------------------------" << endl;


#ifdef __MOFUS__

	GCUsePowerPointResult gcUsePowerPointResult;

	// ÆÄ¿ö Æ÷ÀÎÆ®°¡ ÀÖ´ÂÁö È®ÀÎ
	if ( pPC->getPowerPoint() < 300 )
	{
		// ÆÄ¿ö Æ÷ÀÎÆ®°¡ ºÎÁ·ÇÏ´Ù.
		gcUsePowerPointResult.setErrorCode( GCUsePowerPointResult::NOT_ENOUGH_POWER_POINT );

		pGamePlayer->sendPacket( &gcUsePowerPointResult );

		return;
	}

	// ÀÎº¥Åä¸®¿¡ °ø°£ÀÌ ÀÖ´ÂÁö È®ÀÎÇÑ´Ù.
	_TPOINT pt;
	if ( !pPC->getInventory()->getEmptySlot( 1, 2, pt ) )
	{
		// ÀÎº¥Åä¸®¿¡ °ø°£ÀÌ ºÎÁ·ÇÏ´Ù.
		gcUsePowerPointResult.setErrorCode( GCUsePowerPointResult::NOT_ENOUGH_INVENTORY_SPACE );

		pGamePlayer->sendPacket( &gcUsePowerPointResult );

		return;
	}

	// ¾ÆÀÌÅÛ ·£´ý »ý¼º
	int ratio = rand() % 100 + 1;
	
	GCUsePowerPointResult::ITEM_CODE itemCode;
	Item::ItemClass itemClass;
	ItemType_t itemType;
	string itemName;

	int sum = 0;
	bool bFind = false;
	for ( int i = 0; i < 7; ++i )
	{
		sum += PowerPointItemTemplate[i].Ratio;
		if ( sum >= ratio )
		{
			bFind = true;
			itemCode = PowerPointItemTemplate[i].ItemCode;
			itemClass = PowerPointItemTemplate[i].ItemClass;
			itemType = PowerPointItemTemplate[i].ItemType;
			itemName = PowerPointItemTemplate[i].ItemName;
			break;
		}
	}

	if ( bFind )
	{
		// ¾ÆÀÌÅÛ »ý¼º ¹× Ãß°¡
		list<OptionType_t> nullOption;
		Item* pItem = g_pItemFactoryManager->createItem( itemClass, itemType, nullOption );

		pPC->getZone()->registerObject( pItem );

		if ( pPC->getInventory()->addItem( pItem, pt ) )
		{
			// DB ¿¡ ¾ÆÀÌÅÛ »ý¼º
			pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

			// ItemTraceLog ¸¦ ¸¸±ä´Ù.
			remainTraceLog( pItem, "Mofus", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC );

			// °á°ú¸¦ Å¬¶óÀÌ¾ðÆ®¿¡ ¾Ë¸®±â	
            GCCreateItem gcCreateItem;
            gcCreateItem.setObjectID(pItem->getObjectID());
            gcCreateItem.setItemClass(pItem->getItemClass());
            gcCreateItem.setItemType(pItem->getItemType());
            gcCreateItem.setOptionType(pItem->getOptionTypeList());
            gcCreateItem.setDurability(pItem->getDurability());
            gcCreateItem.setItemNum(pItem->getNum());
            gcCreateItem.setInvenX(pt.x);
            gcCreateItem.setInvenY(pt.y);

            pPlayer->sendPacket(&gcCreateItem);

			// ¾ÆÀÌÅÛ »ý¼º¿¡ ÇÊ¿äÇÑ ÆÄ¿öÂ¯ Æ÷ÀÎÆ®
			static int RequirePowerPoint = -300;

			// ÆÄ¿öÂ¯ Æ÷ÀÎÆ® ÀúÀå
			pPC->setPowerPoint( savePowerPoint( pPC->getName(), RequirePowerPoint ) );

			// °á°ú¸¦ Å¬¶óÀÌ¾ðÆ®¿¡ ¾Ë¸®±â
			gcUsePowerPointResult.setErrorCode( GCUsePowerPointResult::NO_ERROR );
			gcUsePowerPointResult.setItemCode( itemCode );
			gcUsePowerPointResult.setPowerPoint( pPC->getPowerPoint() );

			pGamePlayer->sendPacket( &gcUsePowerPointResult );

			cout << "--------------------------------------------------" << endl;
			cout << "CREATE ITEM (name:" << pPC->getName()
				 << ",usepowerpoint:" << RequirePowerPoint
				 << ",createditem:" << itemName
				 << ")" << endl;
			cout << "--------------------------------------------------" << endl;

			filelog( MOFUS_LOG_FILE, "CREATE ITEM (name:%s,usepowerpoint:%d,createditem:%s",
										pPC->getName().c_str(),
										RequirePowerPoint,
										itemName.c_str() );
		}
		else
		{
			cout << "ÀÎº¥Åä¸®¿¡ ³Ö±â ½ÇÆÐ" << endl;
		}
	}
	else
	{
		cout << "·£´ý ±¼¸®±â ½ÇÆÐ ratio : " << ratio << endl;
	}

#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}

