////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveTestServerReward.cpp
// Written By  : 장홍창
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionGiveTestServerReward.h"
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
#include "SpecialEventFlag.h"
#include <list>

#include "PacketUtil.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"


////////////////////////////////////////////////////////////////////////////////
// ActionGiveTestServerReward
////////////////////////////////////////////////////////////////////////////////
ActionGiveTestServerReward::ActionGiveTestServerReward()
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
ActionGiveTestServerReward::~ActionGiveTestServerReward()
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
void ActionGiveTestServerReward::load()
    
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
void ActionGiveTestServerReward::read(PropertyBuffer & propertyBuffer)
    
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
void ActionGiveTestServerReward::execute(Creature * pCreature1 , Creature * pCreature2) 
	
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

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	Item::ItemClass ItemClass;
	ItemType_t		ItemType;
	OptionType_t	OptionType;

	Item*			pItem;

	// 이미 보상을 받을 수 있는지 체크
	if ( !(pGamePlayer->getSpecialEventCount() & SPECIAL_EVENT_TEST_SERVER_REWARD) )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_REWARD_FAIL );
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

	// 루아의 계산 결과를 받아 아이템을 생성한다.
	pLuaSelectItem->prepare();
	
	int result = pLuaSelectItem->executeFile( luaFileName );
	LuaState::logError(result);

	ItemClass 	= pLuaSelectItem->getItemClass();
	ItemType  	= pLuaSelectItem->getItemType();
	OptionType	= pLuaSelectItem->getOptionType();

	pLuaSelectItem->clear();

	if( ItemClass >= Item::ITEM_CLASS_MAX )
	{
		filelog( "TestServerRewardError.txt", "[ ItemInfo Error ] : ItemClass = %d , ItemType = %d , OptionType = %d", ItemClass, ItemType, OptionType );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// 선물(Item)을 만든다.
	list<OptionType_t> optionTypeList;
	if ( OptionType != 0 )
		optionTypeList.push_back( OptionType );

	pItem = g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	Assert( pItem != NULL );

	// 인벤토리에 아이템을 넣을 빈 자리를 받아온다.
	TPOINT p;
	
	if (!pInventory->getEmptySlot(pItem, p)) 
	{
		SAFE_DELETE( pItem );

		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_NO_EMPTY_SLOT );
		pGamePlayer->sendPacket(&response);

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// 선물을 인벤토리에 추가한다.
	pZone->getObjectRegistry().registerObject( pItem );
	pInventory->addItem( p.x, p.y, pItem );
	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, p.x, p.y );

	// ItemTraceLog 를 남긴다
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
	}

	// 클라이언트에 선물이 추가되었음을 알린다.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );
	pPlayer->sendPacket(&gcCreateItem);

	// 선물을 받았다고 Flag 를 끈다.
	pGamePlayer->setSpecialEventCount( pGamePlayer->getSpecialEventCount() & ~(SPECIAL_EVENT_TEST_SERVER_REWARD) );
	// Flag 를 저장한다.
	pGamePlayer->saveSpecialEventCount();

	// 보상을 받았다고 클라이언트에 보낸다.
	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_REWARD_OK );
	pPlayer->sendPacket( &response );

	GCNPCResponse quit;
	quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &quit );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveTestServerReward::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveTestServerReward("
	    << ")";
	return msg.toString();

	__END_CATCH
}
