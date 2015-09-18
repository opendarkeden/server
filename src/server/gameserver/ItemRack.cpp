//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemRack.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Assert1.h"
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
	// ������ �迭 �Ҵ�
	m_ppItem = new Item*[size];
	Assert(m_ppItem != NULL);

	// ������ �迭 �ʱ�ȭ
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
				// �� �����ϰ� �̾ȿ��� �˾Ƽ� ������ ���� �ֵ��� ����.
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
	// ���� �մ� ������ �����ش�.
	if (m_ppItem != NULL)
	{
		for (int i=0; i<m_nSize; i++) SAFE_DELETE(m_ppItem[i]);

		SAFE_DELETE_ARRAY(m_ppItem);
	}
	
	// ������ �迭 �Ҵ�
	m_ppItem = new Item*[size];
	Assert(m_ppItem != NULL);

	// ������ �迭 �ʱ�ȭ
	for (int i=0; i<size; i++)
		m_ppItem[i] = NULL;

	m_nSize = size;
}

bool ItemRack::isFull(void) const
{
	// �������� �ϳ����� ������ �� �� ���� �ƴ���. 
	for (int i=0; i<m_nSize; i++)
		if (m_ppItem[i] == NULL) return false;
	
	return true;
}

bool ItemRack::isEmpty(void) const
{
	// �������� �ϳ����� ������ �� ���� �ƴ���.
	for (int i=0; i<m_nSize; i++)
		if (m_ppItem[i] != NULL) return false;

	return true;
}

bool ItemRack::isExist(BYTE index) const
{	
	// �߸��� �ε��� ����
	Assert(verifyIndex(index));

	// �������� ���ٸ� false, �ִٸ� true
	return (m_ppItem[index] == NULL ? false : true);
}

void ItemRack::insert(BYTE index, Item* pItem)
{	
	// �߸��� �ε��� ����
	Assert(verifyIndex(index));

	// ���� �������� �����ִ��� �˻�
	// Assert(m_ppItem[index] == NULL);

	// �����ִ´�.
	m_ppItem[index] = pItem;
}

void ItemRack::remove(BYTE index)
{
	// �߸��� �ε��� ����
	Assert(verifyIndex(index));

	// ������ ������.
	m_ppItem[index] = NULL;
}

Item* ItemRack::get(BYTE index)
{	
	// �߸��� �ε��� ����
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
	// ó������ �˻��Ѵ�.
	for (int i=0; i<m_nSize; i++)
		if (m_ppItem[i] == NULL) return i;

	return m_nSize;
}

BYTE ItemRack::getLastEmptySlot(void) const
{
	// �ں��� �˻��Ѵ�.
	for (int i=m_nSize-1; i>=0; i--)
		if (m_ppItem[i] == NULL) return i;

	return m_nSize;
}

bool ItemRack::verifyIndex(BYTE index) const
{
	if (index >= m_nSize) return false;
	return true;
}

