#ifndef __STORE_INFO_H__
#define __STORE_INFO_H__

#include "Types.h"
#include "Packet.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

#include <string>
#include <vector>

#define MAX_SIGN_SIZE	80
#define MAX_ITEM_NUM	20

class StoreItemInfo : public PCItemInfo
{
public:
	StoreItemInfo() : m_ItemExist(0), m_Price(0) { }

	uint getSize() const throw() { return szBYTE + ((m_ItemExist)?(PCItemInfo::getSize() + szGold):0); }
	static uint getMaxSize() throw() { return szBYTE + PCItemInfo::getMaxSize() + szGold; }

	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	BYTE	isItemExist() const { return m_ItemExist; }
	void	setItemExist(BYTE exist) { m_ItemExist = exist; }

	Gold_t	getPrice() const { return m_Price; }
	void	setPrice(Gold_t price) { m_Price = price; }
private:
	BYTE	m_ItemExist;
	Gold_t	m_Price;
};

class StoreOutlook
{
public:
	StoreOutlook() : m_Open(0) { }

	PacketSize_t getSize() const { return szBYTE + ( (m_Open==0)?0:(szBYTE+m_Sign.size()) ); }
	static PacketSize_t getMaxSize() { return szBYTE + szBYTE + MAX_SIGN_SIZE; }

	void read(SocketInputStream& iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	BYTE	isOpen() const { return m_Open; }
	void	setOpen(BYTE open) { m_Open = open; }

	string	getSign() const { return m_Sign; }
	void	setSign(const string& sign) { m_Sign = sign; }

private:
	BYTE	m_Open;
	string	m_Sign;
};

class StoreInfo
{
public:
	StoreInfo() : m_Open(0), m_Items(MAX_ITEM_NUM) { }

	PacketSize_t		getSize(bool toOther) const;
	static PacketSize_t	getMaxSize() { return szBYTE + szBYTE + MAX_SIGN_SIZE + szBYTE + MAX_ITEM_NUM * StoreItemInfo::getMaxSize(); }

	void read(SocketInputStream& iStream, bool toOther) throw(ProtocolException, Error);
	void write(SocketOutputStream& oStream, bool toOther) const throw(ProtocolException, Error);

	BYTE	isOpen() const { return m_Open; }
	void	setOpen(BYTE open) { m_Open = open; }

	string	getSign() const { return m_Sign; }
	void	setSign(const string& sign) { m_Sign = sign; }

	vector<StoreItemInfo>&	getItems() { return m_Items; }
	const vector<StoreItemInfo>&	getItems() const { return m_Items; }

	StoreItemInfo&	getStoreItemInfo(BYTE index) { return m_Items[index]; }
	void	makeStoreOutlook(StoreOutlook& outlook) { outlook.setOpen(m_Open); outlook.setSign(m_Sign); }

private:
	BYTE	m_Open;
	string	m_Sign;
	vector<StoreItemInfo>	m_Items;
};

#endif
