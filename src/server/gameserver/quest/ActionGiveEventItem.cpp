////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveEventItem.cpp
// Written By  : 장홍창
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionGiveEventItem.h"
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
#include "Gpackets/GCNPCResponse.h"

#include "VariableManager.h"

////////////////////////////////////////////////////////////////////////////////
// ActionGiveEventItem
////////////////////////////////////////////////////////////////////////////////
ActionGiveEventItem::ActionGiveEventItem()
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
ActionGiveEventItem::~ActionGiveEventItem()
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
void ActionGiveEventItem::load()
    
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
void ActionGiveEventItem::read(PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try
	{
		// read script id
		m_FlagSetType = (FlagSetType)propertyBuffer.getPropertyInt("FlagSetType");
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
void ActionGiveEventItem::execute(Creature * pCreature1 , Creature * pCreature2) 
	
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
	OptionType_t	OptionType2;

	Item*			pItem;

	// 이벤트 진행 기간이 아닌 경우
	if (!g_pVariableManager->isActiveGiveEventItem())
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL_NOW );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// 이 값과 관련해서
	// 캐릭터 생성시에 FlagSet을 바꿔줘야한다. (default ON 으로)
	// 이미 선물을 교환해 갔다면
	if ( pFlagSet->isOn( m_FlagSetType ) )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL );
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
	OptionType2	= pLuaSelectItem->getOptionType2();

	pLuaSelectItem->clear();

	if( ItemClass >= Item::ITEM_CLASS_MAX )
	//||  ItemType  >= ITEM_TYPE_MAX || ItemType  < 0
	//	|| OptionType == 0)
	{
		filelog( "GiveEventItemError.txt", "[ ItemInfo Error ] : ItemClass = %d , ItemType = %d , OptionType = %d", ItemClass, ItemType, OptionType );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}

	// 선물(Item)을 만든다.
	list<OptionType_t> optionTypeList;
	if ( OptionType != 0 ) optionTypeList.push_back( OptionType );
	if ( OptionType2 != 0 ) optionTypeList.push_back( OptionType2 );

	pItem = g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	Assert( pItem != NULL );

	_TPOINT pt;
	if (!pInventory->getEmptySlot(pItem, pt))
	{
		SAFE_DELETE(pItem);

		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_NO_EMPTY_SLOT );
		pPlayer->sendPacket( &response );

		GCNPCResponse quit;
		quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
		pPlayer->sendPacket( &quit );

		return;
	}
	 
	CoordInven_t X = pt.x;
	CoordInven_t Y = pt.y;

	// 선물을 인벤토리에 추가한다.
	pZone->getObjectRegistry().registerObject( pItem );
	pInventory->addItem( X, Y, pItem );
	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );

	// ItemTraceLog 를 남긴다
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);

		remainTraceLogNew( pItem, pCreature2->getName(), ITL_GET, ITLD_EVENTNPC, pCreature1->getZone()->getZoneID(), pCreature1->getX(), pCreature1->getY() );
	}

	// 클라이언트에 선물이 추가되었음을 알린다.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	// Flag을 켠다.
	pFlagSet->turnOn( m_FlagSetType );

	// Flag을 저장한다.
	pFlagSet->save( pPC->getName() );

	// 아이템 교환이 이루어 졌다고 클라이언트에 알린다.
	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_GIVE_EVENT_ITEM_OK );
	pPlayer->sendPacket( &response );

	GCNPCResponse quit;
	quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &quit );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveEventItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveEventItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
