//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemRack.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "ItemRack.h"
#include "Item.h"

#include "ParkingCenter.h"
#include "item/Key.h"

//////////////////////////////////////////////////////////////////////////////
// class ItemRack member methods
//////////////////////////////////////////////////////////////////////////////

ItemRack::ItemRack()
{
	m_ppItem = NULL;
	m_nSize  = 0;
}

ItemRack::ItemRack(int size)
{
	// 포인터 배열 할당
	m_ppItem = new (Item*)[size];
	Assert(m_ppItem != NULL);

	// 포인터 배열 초기화
	for (int i=0; i<size; i++)
		m_ppItem[i] = NULL;

	m_nSize = size;
}

ItemRack::~ItemRack()
{
	if (m_ppItem != NULL)
	{
		for (int i=0; i<m_nSize; i++) 
		{
			Item* pItem = m_ppItem[i];

			if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_KEY) 
			{
				Key* pKey = dynamic_cast<Key*>(pItem);
				// 걍 간단하게 이안에서 알아서 존에서 지워 주도록 하자.
				if (g_pParkingCenter->hasMotorcycleBox(pKey->getTarget())) 
				{
					g_pParkingCenter->deleteMotorcycleBox(pKey->getTarget());
				}
			}

			SAFE_DELETE(m_ppItem[i]);
		}

		SAFE_DELETE_ARRAY(m_ppItem);
	}
}

void ItemRack::init(int size)
{
	// 먼저 잇던 내용을 지워준다.
	if (m_ppItem != NULL)
	{
		for (int i=0; i<m_nSize; i++) SAFE_DELETE(m_ppItem[i]);

		SAFE_DELETE_ARRAY(m_ppItem);
	}
	
	// 포인터 배열 할당
	m_ppItem = new (Item*)[size];
	Assert(m_ppItem != NULL);

	// 포인터 배열 초기화
	for (int i=0; i<size; i++)
		m_ppItem[i] = NULL;

	m_nSize = size;
}

bool ItemRack::isFull(void) const
{
	// 아이템이 하나라도 없으면 꽉 찬 것은 아니지. 
	for (int i=0; i<m_nSize; i++)
		if (m_ppItem[i] == NULL) return false;
	
	return true;
}

bool ItemRack::isEmpty(void) const
{
	// 아이템이 하나라도 있으면 빈 것은 아니지.
	for (int i=0; i<m_nSize; i++)
		if (m_ppItem[i] != NULL) return false;

	return true;
}

bool ItemRack::isExist(BYTE index) const
{	
	// 잘못된 인덱싱 검증
	Assert(verifyIndex(index));

	// 아이템이 없다면 false, 있다면 true
	return (m_ppItem[index] == NULL ? false : true);
}

void ItemRack::insert(BYTE index, Item* pItem)
{	
	// 잘못된 인덱싱 검증
	Assert(verifyIndex(index));

	// 먼저 아이템이 들어있는지 검사
	Assert(m_ppItem[index] == NULL);

	// 집어넣는다.
	m_ppItem[index] = pItem;
}

void ItemRack::remove(BYTE index)
{
	// 잘못된 인덱싱 검증
	Assert(verifyIndex(index));

	// 포인터 지운다.
	m_ppItem[index] = NULL;
}

Item* ItemRack::get(BYTE index)
{	
	// 잘못된 인덱싱 검증
	Assert(verifyIndex(index));

	return m_ppItem[index];
}

void ItemRack::clear(void) 
{
	for (int i=0; i<m_nSize; i++)
		SAFE_DELETE(m_ppItem[i]);
}

BYTE ItemRack::getFirstEmptySlot(void) const
{
	// 처음부터 검색한다.
	for (int i=0; i<m_nSize; i++)
		if (m_ppItem[i] == NULL) return i;

	return m_nSize;
}

BYTE ItemRack::getLastEmptySlot(void) const
{
	// 뒤부터 검색한다.
	for (int i=m_nSize-1; i>=0; i--)
		if (m_ppItem[i] == NULL) return i;

	return m_nSize;
}

bool ItemRack::verifyIndex(BYTE index) const
{
	if (index >= m_nSize) return false;
	return true;
}

