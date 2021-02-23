////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveNewbieItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveNewbieItem.h"
#include "Slayer.h"
#include "FlagSet.h"
#include "Item.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "item/Magazine.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveNewbieItem::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script type
		string ItemType = propertyBuffer.getProperty("Type");

		if      (ItemType == "SWORD") m_ItemClass = Item::ITEM_CLASS_SWORD;
		else if (ItemType == "BLADE") m_ItemClass = Item::ITEM_CLASS_BLADE;
		else if (ItemType == "AR")    m_ItemClass = Item::ITEM_CLASS_AR;
		else if (ItemType == "SR")    m_ItemClass = Item::ITEM_CLASS_SR;
		else if (ItemType == "SG")    m_ItemClass = Item::ITEM_CLASS_SG;
		else if (ItemType == "SMG")   m_ItemClass = Item::ITEM_CLASS_SMG;
		else if (ItemType == "CROSS") m_ItemClass = Item::ITEM_CLASS_CROSS;
		else if (ItemType == "MACE")  m_ItemClass = Item::ITEM_CLASS_MACE;
		else
		{
			cout << "ActionGiveNewbieItem::read() : Unknown item type" << endl;
			throw ("ActionGiveNewbieItem::read() : Unknown item type");
		}
	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveNewbieItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	// 먼저 클라이언트를 위해 GCNPCResponse를 보내준다.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	// 초보자가 슬레이어가 아닌 경우는 없다.
	if (!pCreature2->isSlayer()) return;

	Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature2);
	FlagSet*   pFlagSet   = pSlayer->getFlagSet();
	Inventory* pInventory = pSlayer->getInventory();
	Zone*      pZone      = pSlayer->getZone();

	////////////////////////////////////////////////////////////
	// 진짜 초보인지를 검사한다.
	// 0번을 초보 아이템 받았다 플래그로 정했다.
	// 이것은 어디까지나 땜빵 코드다.
	////////////////////////////////////////////////////////////
	
	if (pFlagSet->isOn(0)) return;

	////////////////////////////////////////////////////////////
	// 각 아이템 클래스에 따라 아이템을 생성한다.
	////////////////////////////////////////////////////////////
	Item* pItem[10] = { NULL, };
	int   i         = 0;

	for (i=0; i<10; i++) pItem[i] = NULL;

	list<OptionType_t> nullList;

	if (m_ItemClass == Item::ITEM_CLASS_SWORD)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SWORD, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_BLADE)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_BLADE, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_CROSS)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_CROSS, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_MACE)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_MACE, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_AR)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_AR, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 2, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_SR)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SR, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 6, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_SG)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SG, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 0, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_SMG)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SMG, 0, nullList);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 4, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else
	{
		return;
	}

	////////////////////////////////////////////////////////////
	// 생성한 아이템을 등록하고, DB에 저장하고,
	// 클라이언트에게 정보를 날려준다.
	////////////////////////////////////////////////////////////
	ObjectRegistry& OR = pZone->getObjectRegistry();
	TPOINT           pt;
	GCCreateItem     gcCreateItem;

	for (i=0; i<10; i++)
	{
		if (pItem[i] != NULL)
		{
			OR.registerObject(pItem[i]);

			if (pInventory->addItem(pItem[i], pt))
			{
				pItem[i]->create(pSlayer->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

				gcCreateItem.setObjectID(pItem[i]->getObjectID());
				gcCreateItem.setItemClass(pItem[i]->getItemClass());
				gcCreateItem.setItemType(pItem[i]->getItemType());
				gcCreateItem.setOptionType(pItem[i]->getOptionTypeList());
				gcCreateItem.setDurability(pItem[i]->getDurability());
				gcCreateItem.setSilver(pItem[i]->getSilver());

				if (pItem[i]->getItemClass() == Item::ITEM_CLASS_MAGAZINE)
				{
					Magazine* pMag = dynamic_cast<Magazine*>(pItem[i]);
					gcCreateItem.setItemNum(pMag->getNum());
				}
				else
				{
					gcCreateItem.setItemNum(pItem[i]->getNum());
				}

				gcCreateItem.setInvenX(pt.x);
				gcCreateItem.setInvenY(pt.y);

				pPlayer->sendPacket(&gcCreateItem);
			}
			else
			{
				SAFE_DELETE(pItem[i]);
			}
		}
	}

	// 돈도 준다네...
	//pSlayer->setGoldEx(pSlayer->getGold() + 500);
	// by sigi. 2002.9.18
	pSlayer->increaseGoldEx(500);
	GCModifyInformation gcModifyInformation;
	gcModifyInformation.addLongData(MODIFY_GOLD, pSlayer->getGold());
	pPlayer->sendPacket(&gcModifyInformation);

	////////////////////////////////////////////////////////////
	// 아이템을 받았으니, 현재 FlagSet을 저장한다.
	// 0번을 초보 아이템 받았다 플래그로 정했다.
	// 이것은 어디까지나 땜빵 코드다.
	////////////////////////////////////////////////////////////
	pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM);

	if (m_ItemClass == Item::ITEM_CLASS_SWORD || m_ItemClass == Item::ITEM_CLASS_BLADE)
	{
		// 무사일 경우 1
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_FIGHTER);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_CROSS || m_ItemClass == Item::ITEM_CLASS_MACE)
	{
		// 성직자일 경우 2
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_CLERIC);
	}
	else
	{
		// 군인일 경우 3
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_GUNNER);
	}

	pFlagSet->save(pSlayer->getName());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveNewbieItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveNewbieItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}






