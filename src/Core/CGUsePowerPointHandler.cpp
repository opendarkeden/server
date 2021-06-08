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
	#include "GCUsePowerPointResult.h"
	#include "GCCreateItem.h"

struct POWER_POINT_ITEM_TEMPLATE
{
	GCUsePowerPointResult::ITEM_CODE	ItemCode;
	Item::ItemClass						ItemClass;
	ItemType_t							ItemType;
	uint								Ratio;
	string								ItemName;
};
// edit by Coffee  2006-12-10  �޸Ĳ���ϵͳ����
const POWER_POINT_ITEM_TEMPLATE PowerPointItemTemplate[7] =
{
	{ GCUsePowerPointResult::CANDY,					Item::ITEM_CLASS_EVENT_ETC,			14,	20,	"�鵤" },
	{ GCUsePowerPointResult::RESURRECTION_SCROLL,	Item::ITEM_CLASS_RESURRECT_ITEM,	0,	20,	"�������" },
	{ GCUsePowerPointResult::ELIXIR_SCROLL,			Item::ITEM_CLASS_RESURRECT_ITEM,	1,	20,	"�������" },
	{ GCUsePowerPointResult::MEGAPHONE,				Item::ITEM_CLASS_EFFECT_ITEM,		0,	20,	"�Խ���1" },
	{ GCUsePowerPointResult::NAMING_PEN,			Item::ITEM_CLASS_EVENT_GIFT_BOX,	22,	14,	"�ǳ�ǩ����" },
	{ GCUsePowerPointResult::SIGNPOST,				Item::ITEM_CLASS_EVENT_STAR,		6,	1,	"����ʯ(����)" },
	{ GCUsePowerPointResult::BLACK_RICE_CAKE_SOUP,	Item::ITEM_CLASS_EVENT_STAR,		11, 5,	"��ɫף��" }

};
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUsePowerPointHandler::execute (CGUsePowerPoint* pPacket , Player* pPlayer)
	 
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

	// �Ŀ� ����Ʈ�� �ִ��� Ȯ��
	if ( pPC->getPowerPoint() < 300 )
	{
		// �Ŀ� ����Ʈ�� �����ϴ�.
		gcUsePowerPointResult.setErrorCode( GCUsePowerPointResult::NOT_ENOUGH_POWER_POINT );

		pGamePlayer->sendPacket( &gcUsePowerPointResult );

		return;
	}

	// �κ��丮�� ������ �ִ��� Ȯ���Ѵ�.
	_TPOINT pt;
	if ( !pPC->getInventory()->getEmptySlot( 1, 2, pt ) )
	{
		// �κ��丮�� ������ �����ϴ�.
		gcUsePowerPointResult.setErrorCode( GCUsePowerPointResult::NOT_ENOUGH_INVENTORY_SPACE );

		pGamePlayer->sendPacket( &gcUsePowerPointResult );

		return;
	}

	// ������ ���� ����
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
		// ������ ���� �� �߰�
		list<OptionType_t> nullOption;
		Item* pItem = g_pItemFactoryManager->createItem( itemClass, itemType, nullOption );

		pPC->getZone()->registerObject( pItem );

		if ( pPC->getInventory()->addItem( pItem, pt ) )
		{
			// DB �� ������ ����
			pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

			// ItemTraceLog �� �����.
			remainTraceLog( pItem, "Mofus", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC );

			// ����� Ŭ���̾�Ʈ�� �˸���	
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

			// ������ ������ �ʿ��� �Ŀ�¯ ����Ʈ
			static int RequirePowerPoint = -300;

			// �Ŀ�¯ ����Ʈ ����
			pPC->setPowerPoint( savePowerPoint( pPC->getName(), RequirePowerPoint ) );

			// ����� Ŭ���̾�Ʈ�� �˸���
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
			cout << "�κ��丮�� �ֱ� ����" << endl;
		}
	}
	else
	{
		cout << "���� ������ ���� ratio : " << ratio << endl;
	}

#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}

