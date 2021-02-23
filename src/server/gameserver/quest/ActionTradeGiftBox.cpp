////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeGiftBox.cpp
// Written By  : 장홍창
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionTradeGiftBox.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Item.h"
#include "ItemUtil.h"
#include "OptionInfo.h"
#include "Inventory.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Thread.h"
#include "Slayer.h"
#include "Vampire.h"
#include "FlagSet.h"
#include <list>

#include "PacketUtil.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCNPCResponse.h"

#include "PriceManager.h"

////////////////////////////////////////////////////////////////////////////////
// ActionTradeGiftBox
////////////////////////////////////////////////////////////////////////////////
ActionTradeGiftBox::ActionTradeGiftBox()
: m_pLuaState(NULL), m_pLuaSlayerItem(NULL), m_pLuaVampireItem(NULL)
{
	m_pLuaState = new LuaState;
	m_pLuaState->init();

	m_pLuaSlayerItem = new LuaTradeEventSlayerItem(m_pLuaState);
	m_pLuaVampireItem = new LuaTradeEventVampireItem(m_pLuaState);
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
ActionTradeGiftBox::~ActionTradeGiftBox()
{
    __BEGIN_TRY

	SAFE_DELETE(m_pLuaState);
	SAFE_DELETE(m_pLuaSlayerItem);
	SAFE_DELETE(m_pLuaVampireItem);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//  load
////////////////////////////////////////////////////////////////////////////////
void ActionTradeGiftBox::load()
    throw (Error)
{
    __BEGIN_TRY
	
	Assert(m_pLuaState!=NULL);

	int result = m_pLuaState->dofile(m_CommonFilename);
	LuaState::logError(result);

    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTradeGiftBox::read(PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try
	{
		// read script id
		m_CommonFilename = propertyBuffer.getProperty("CommonFilename");
		m_SlayerFilename = propertyBuffer.getProperty("SlayerFilename");
		m_VampireFilename = propertyBuffer.getProperty("VampireFilename");

		load();
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionTradeGiftBox::execute(Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	FlagSet* pFlagSet = pPC->getFlagSet();

	Item::ItemClass ItemClass;
	ItemType_t		ItemType;
	OptionType_t	OptionType;

	Item*			pItem;
	Item*			pGiftBoxItem;

	// 이미 선물을 교환해 갔다면
	if ( pFlagSet->isOn( FLAGSET_TRADE_GIFT_BOX_2002_12 ) )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_TRADE_GIFT_BOX_ALREADY_TRADE );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// 빨간 선물 상자가 있는지 확인한다.
	CoordInven_t X,Y;
	pGiftBoxItem = pInventory->findItem( Item::ITEM_CLASS_EVENT_GIFT_BOX, 1, X, Y );
	if ( pGiftBoxItem == NULL )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_TRADE_GIFT_BOX_NO_ITEM );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	LuaSelectItem*	pLuaSelectItem = NULL;
	string			luaFileName;

	if ( pPC->isSlayer() )
	{
		// 루아에 슬레이어 능력치의 합을 set한다.
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );

		Attr_t sum = pSlayer->getSTR( ATTR_BASIC )
				   + pSlayer->getDEX( ATTR_BASIC )
				   + pSlayer->getINT( ATTR_BASIC );

		m_pLuaSlayerItem->setSum(sum);
		pLuaSelectItem = m_pLuaSlayerItem;
		luaFileName = m_SlayerFilename;

	}
	else if ( pPC->isVampire() )
	{
		// 루아에 뱀파이어의 레벨을 set한다.
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		int level = pVampire->getLevel();
		m_pLuaVampireItem->setLevel(level);
		pLuaSelectItem = m_pLuaVampireItem;
		luaFileName = m_VampireFilename;
	}

	//--------------------------------------------------------
	// 속도 체크를 위해서 1000번 돌려보는 코드
	// 결과는.. 0.07초 정도 나왔다. 감덩~ -_-;
	/*
	Timeval beforeTime;
	getCurrentTime(beforeTime);

	for (int i=0; i<1000; i++)
	{
		// 루아의 계산 결과를 받아 아이템을 생성한다.
		pLuaSelectItem->prepare();
		
		int result = pLuaSelectItem->executeFile( luaFileName );
		LuaState::logError(result);
		pLuaSelectItem->clear();
	}

	Timeval afterTime;
	getCurrentTime(afterTime);

	cout << "luaExecute time before : " << beforeTime.tv_sec  << "." << beforeTime.tv_usec << endl;
	cout << "luaExecute time after  : " << afterTime.tv_sec  << "." << afterTime.tv_usec << endl;
	*/
	//--------------------------------------------------------

	// 루아의 계산 결과를 받아 아이템을 생성한다.
	pLuaSelectItem->prepare();
	
	int result = pLuaSelectItem->executeFile( luaFileName );
	LuaState::logError(result);

	ItemClass 	= pLuaSelectItem->getItemClass();
	ItemType  	= pLuaSelectItem->getItemType();
	OptionType	= pLuaSelectItem->getOptionType();

	pLuaSelectItem->clear();

	if( ItemClass >= Item::ITEM_CLASS_MAX )
	//||  ItemType  >= ITEM_TYPE_MAX || ItemType  < 0
	//	|| OptionType == 0)
	{
		filelog( "XMasEventError.txt", "[ ItemInfo Error ] : ItemClass = %d , ItemType = %d , OptionType = %d", ItemClass, ItemType, OptionType );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// 클라이언트에 선물상자를 지우도록 한다.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pGiftBoxItem->getObjectID() );
	pPlayer->sendPacket( &gcDeleteInventoryItem );

	// 선물상자를 지운다.
	pInventory->deleteItem( X, Y );
	// ItemTraceLog 를 남긴다
	if ( pGiftBoxItem != NULL && pGiftBoxItem->isTraceItem() )
	{
		remainTraceLog( pGiftBoxItem, pCreature2->getName(), pCreature1->getName(), ITEM_LOG_DELETE, DETAIL_EVENTNPC);
	}
	pGiftBoxItem->destroy();
	SAFE_DELETE( pGiftBoxItem );


	// 선물(Item)을 만든다.
	list<OptionType_t> optionTypeList;
	if ( OptionType != 0 )
		optionTypeList.push_back( OptionType );

	pItem = g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	Assert( pItem != NULL );


	// 선물을 인벤토리에 추가한다.
	pZone->getObjectRegistry().registerObject( pItem );
	pInventory->addItem( X, Y, pItem );
	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );

	// ItemTraceLog 를 남긴다
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
	}

	// 클라이언트에 선물이 추가되었음을 알린다.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	// Flag을 켠다.
	pFlagSet->turnOn( FLAGSET_TRADE_GIFT_BOX_2002_12 );

	// Flag을 저장한다.
	pFlagSet->save( pPC->getName() );

	// 아이템 교환이 이루어 졌다고 클라이언트에 알린다.
	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_TRADE_GIFT_BOX_OK );
	pPlayer->sendPacket( &response );

	GCNPCResponse quit;
	quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &quit );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTradeGiftBox::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTradeGiftBox("
	    << ")";
	return msg.toString();

	__END_CATCH
}
