//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToCodeSheetHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddItemToCodeSheet.h"

#ifdef __GAME_SERVER__
#include "PlayerCreature.h"
#include "Item.h"
#include "GamePlayer.h"
#include "Inventory.h"
#include "ItemUtil.h"

#include "Gpackets/GCCannotUse.h"
#include "Gpackets/GCUseOK.h"

#include <vector>
#include <list>
#include <cstdio>

uint getStoneNum( const vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y );
void setStoneNum( vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y, uint Num );
bool canPutStone( const vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y, uint StoneNum );
bool isComplete( const vector<OptionType_t>& OptionType );

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddItemToCodeSheetHandler::execute (CGAddItemToCodeSheet* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	CoordInven_t x,y;
	Item* pMouseItem = pPC->getExtraInventorySlotItem();
	Item* pTargetItem = pPC->getInventory()->findItemOID( pPacket->getObjectID(), x, y );

	GCCannotUse failpkt;
	failpkt.setObjectID( pPacket->getObjectID() );

	if ( pMouseItem == NULL || pTargetItem == NULL
		|| pMouseItem->getItemClass() != Item::ITEM_CLASS_EVENT_ITEM
		|| pTargetItem->getItemClass() != Item::ITEM_CLASS_CODE_SHEET
		|| pMouseItem->getItemType() > 26 || pMouseItem->getItemType() < 22
		|| pTargetItem->getItemType() != 0 )
	{
		pPlayer->sendPacket(&failpkt);
		return;
	}

	GCUseOK okpkt;
	uint StoneNum = pMouseItem->getItemType()-21;
	Assert( StoneNum >= 1 && StoneNum <= 5 );

	x = pPacket->getX();
	y = pPacket->getY();

	vector<OptionType_t> OptionType(pTargetItem->getOptionTypeList().begin(), pTargetItem->getOptionTypeList().end());
	if ( OptionType.size() < 30 )
	{
		pPlayer->sendPacket(&failpkt);
		return;
	}

	uint TargetStoneNum = getStoneNum( OptionType, x, y );
	if ( TargetStoneNum != 0xf || !canPutStone( OptionType, x, y, StoneNum ) )
	{
		pPlayer->sendPacket( &failpkt );
		return;
	}

	setStoneNum( OptionType, x, y, StoneNum );

	if ( isComplete( OptionType ) )
	{
		pTargetItem->setItemType(1);
		pTargetItem->tinysave("ItemType=1");
	}

	pTargetItem->setOptionType( list<OptionType_t>(OptionType.begin(), OptionType.end()) );

	string optionField;
	setOptionTypeToField( pTargetItem->getOptionTypeList(), optionField );

	char query[100];
	sprintf( query, "OptionType = '%s'", optionField.c_str() );
	pTargetItem->tinysave(query);

	pPC->deleteItemFromExtraInventorySlot();
	pMouseItem->destroy();
	SAFE_DELETE( pMouseItem );

	pPlayer->sendPacket(&okpkt);

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__
uint getStoneNum( const vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y )
{
	uint SerialNum = y * 10 + x;
	uint IndexNum = SerialNum / 2;
	uint LowerBit = SerialNum % 2;

	OptionType_t targetOption = OptionType[IndexNum];
	uint TargetStoneNum;

	if ( LowerBit )
	{
		TargetStoneNum = (targetOption & 0x0f);
	}
	else
	{
		TargetStoneNum = (targetOption & 0xf0)>>4;
	}

	return TargetStoneNum;
}

void setStoneNum( vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y, uint StoneNum )
{
	uint SerialNum = y * 10 + x;
	uint IndexNum = SerialNum / 2;
	uint LowerBit = SerialNum % 2;

	OptionType_t targetOption = OptionType[IndexNum];

	if ( LowerBit )
	{
		targetOption &= 0xf0;
		targetOption |= StoneNum;
	}
	else
	{
		targetOption &= 0x0f;
		targetOption |= (StoneNum << 4);
	}

	OptionType[IndexNum] = targetOption;
}

bool canPutStone( const vector<OptionType_t>& OptionType, CoordInven_t x, CoordInven_t y, uint StoneNum )
{
	if ( x > 0 )
	{
		if ( getStoneNum( OptionType, x-1, y ) == StoneNum ) return false;
	}

	if ( y > 0 )
	{
		if ( getStoneNum( OptionType, x, y-1 ) == StoneNum ) return false;
	}

	if ( x < 9 )
	{
		if ( getStoneNum( OptionType, x+1, y ) == StoneNum ) return false;
	}

	if ( y < 5 )
	{
		if ( getStoneNum( OptionType, x, y+1 ) == StoneNum ) return false;
	}

	return true;
}

bool isComplete( const vector<OptionType_t>& OptionType )
{
	for ( uint i=0; i < OptionType.size(); ++i )
	{
		if ( (OptionType[i]&0xf0) == 0xf0 || (OptionType[i]&0x0f) == 0x0f ) return false;
	}

	return true;
}
#endif
