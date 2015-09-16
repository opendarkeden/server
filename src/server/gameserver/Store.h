#ifndef __STORE_H__
#define __STORE_H__

#include "Types.h"
#include "Exception.h"
#include "StoreInfo.h"
#include <vector>

class Item;

class StoreItem
{
public:
	StoreItem() : m_bExist(false), m_pItem(NULL), m_Price(0) { }

	bool	isExists() const { return m_bExist; }
	Item*	getItem() const { return m_pItem; }
	Gold_t	getPrice() const { return m_Price; }

	BYTE	removeItem();
	BYTE	setItem(Item* pItem, Gold_t price);

/*	void	setExist(bool exist) { m_bExist = exist; }

	void	setItem(Item* pItem) { m_pItem = pItem; }

	void	setPrice(Gold_t	price) { m_Price = price; }*/

	void	makeStoreItemInfo(StoreItemInfo& info);
private:
	bool	m_bExist;
	Item*	m_pItem;
	Gold_t	m_Price;
};

class Store
{
public:
	Store();

	string	getSign() const { return m_Sign; }
	void	setSign(const string& sign) { m_Sign = sign; m_StoreInfo.setSign(m_Sign); }

	bool	isOpen() const { return m_bOpen; }
	void	open() { m_bOpen = true; m_StoreInfo.setOpen((BYTE)m_bOpen); }
	void	close() { m_bOpen = false; m_StoreInfo.setOpen((BYTE)m_bOpen); }

	void	clearAll();

	StoreItem&	getStoreItem(BYTE index ) { return m_StoreItems[index]; }
	BYTE	setStoreItem(BYTE index, Item* pItem, Gold_t price);
	BYTE	removeStoreItem(BYTE index);

	const StoreInfo&	getStoreInfo() const { return m_StoreInfo; }
	StoreInfo&	getStoreInfo() { return m_StoreInfo; }

	bool	hasItem(Item* pItem) const;
	bool	hasItem(ObjectID_t oid) const;

	BYTE	getItemIndex(Item* pItem) const;
	BYTE	getItemIndex(ObjectID_t oid) const;

	void	updateStoreInfo();

private:
	bool				m_bOpen;
	string				m_Sign;
	vector<StoreItem>	m_StoreItems;

	StoreInfo			m_StoreInfo;
};

#endif
