
#include "ItemRewardInfo.h"
#include "RewardClass.h"

#include "PlayerCreature.h"
#include "Inventory.h"
#include "ItemInfoManager.h"
#include "ItemFactoryManager.h"
#include "Player.h"
#include "Zone.h"

#include "DB.h"

#include "ItemUtil.h"
#include "PacketUtil.h"
#include "StringStream.h"

#include "PetInfo.h"
#include "item/PetItem.h"
#include "PetTypeInfo.h"
#include "VSDateTime.h"

#include "Gpackets/GCCreateItem.h"

ItemRewardInfo::ItemRewardInfo( RewardID_t rID, RewardClass_t rClass, Item::ItemClass iClass, ItemType_t iType, const string& option, DWORD time )
	: RewardInfo( rID, rClass )
{
	m_IClass = iClass;
	m_IType = iType;
	makeOptionList( option, m_OptionType );

	m_TimeLimit = time;
}

ItemRewardInfo::~ItemRewardInfo()
{
}

QuestMessage ItemRewardInfo::canGiveReward( PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	Inventory* pInventory = pPC->getInventory();
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( m_IClass, m_IType );

	_TPOINT tp;

	if ( pItemInfo == NULL ) return FAIL_BUG;

	if ( pInventory->getEmptySlot( pItemInfo->getVolumeWidth(), pItemInfo->getVolumeHeight(), tp ) ) return COMPLETE_SUCCESS;

	return COMPLETE_FAIL_NO_INVENTORY_SPACE;

	__END_CATCH
}

QuestMessage ItemRewardInfo::giveReward( PlayerCreature *pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	_TPOINT tp;

	GenderRestriction gender = GENDER_BOTH;
	switch( pPC->getSex() )
	{
		case MALE:
			gender = GENDER_MALE;
			break;
		case FEMALE:
			gender = GENDER_FEMALE;
			break;
		default:
			break;
	}

	Item* pItem = g_pItemFactoryManager->createItem( m_IClass, m_IType, m_OptionType );
	if ( pItem == NULL )
	{
		return FAIL_BUG;
	}

	if ( m_IClass == Item::ITEM_CLASS_PET_ITEM )
	{
		PetInfo* pPetInfo = new PetInfo;

		pPetInfo->setPetType(m_IType);
		pPetInfo->setPetLevel(0);
		pPetInfo->setPetAttr(0xff);
		pPetInfo->setPetExp(0);
		pPetInfo->setPetAttrLevel(0);
		pPetInfo->setFoodType(m_IType*4-6);
		pPetInfo->setPetHP(360);
		pPetInfo->setFeedTime( VSDateTime::currentDateTime() );
		pPetInfo->setGamble(0);
		pPetInfo->setCutHead(0);

		PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo( pPetInfo->getPetType() );
		if ( pPetTypeInfo != NULL )
		{
			pPetInfo->setPetCreatureType( pPetTypeInfo->getPetCreatureType( pPetInfo->getPetLevel() ) );
		}

		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
		Assert( pPetItem != NULL );

		pPetItem->setPetInfo( pPetInfo );
		pPetInfo->setPetItem( pPetItem );
	}

	setItemGender( pItem, gender );

	Inventory* pInventory = pPC->getInventory();

	pPC->getZone()->registerObject( pItem );
	
	if ( !pInventory->addItem( pItem, tp ) )
	{
		SAFE_DELETE( pItem );
		filelog("Quest.log", "ItemRewardInfo::giveReward() : canGiveReward() 를 확인하지 않았거나 먼가 꼬였습니다.");
		return COMPLETE_FAIL_NO_INVENTORY_SPACE;
	}

	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y );

	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, tp.x, tp.y );
	pPC->getPlayer()->sendPacket( &gcCreateItem );

	if ( m_TimeLimit != 0 )
	{
		pPC->addTimeLimitItem( pItem, m_TimeLimit );
		pPC->sendTimeLimitItemInfo();
	}

	pItem->whenPCTake(pPC);

	return COMPLETE_SUCCESS;

	__END_CATCH
}

/*void ItemRewardInfo::loadRewardClass( RewardClass& rClass )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT RewardID, IClass, IType, OptionType, TimeLimit FROM ItemRewardInfo where RewardClass=%u", rClass.getRewardClass() );

		while ( pResult->next() ) 
		{
			int index = 0;

			RewardID_t		rID			= (RewardID_t)		pResult->getInt( ++index );
			Item::ItemClass	iClass		= (Item::ItemClass)	pResult->getInt( ++index );
			ItemType_t		iType		= (ItemType_t)		pResult->getInt( ++index );
			string			options		= 					pResult->getString( ++index );
			DWORD			timeLimit	= (DWORD)			pResult->getInt( ++index );

			ItemRewardInfo* pIRewardInfo = new ItemRewardInfo( rID, rClass.getRewardClass(), iClass, iType, options, timeLimit );
			rClass.addRewardInfo( pIRewardInfo );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}*/

string ItemRewardInfo::toString() const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ItemRewardInfo("
		<< "ItemClass : " << (int) m_IClass
		<< ", ItemType : " << (int) m_IType
		<< ", ItemOption : " << getOptionTypeToString( m_OptionType ).c_str()
		<< ", TimeLimitSec : " << m_TimeLimit
		<< ") : " << endl << RewardInfo::toString().c_str();

	return msg.toString();

	__END_CATCH
}
