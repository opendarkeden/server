//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopListMysterious.cpp 
// Written By  : 김성민
// Description :
// 플레이어가 가진 상점 버전이 서버에 있는 것과 다를 경우,
// 플레이어는 서버에 상점에 있는 상품 목록을 요구하게 된다.
// 이 패킷은 그 때 플레이어에게 전달하게 되는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#include "GCShopListMysterious.h"
#include "Assert.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCShopListMysterious::GCShopListMysterious() 
	throw ()
{
	__BEGIN_TRY 

	for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
		m_pBuffer[i].bExist = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCShopListMysterious::~GCShopListMysterious() 
	throw ()
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE i      = 0;
	BYTE nTotal = 0;
	BYTE index  = 0;
	
	// read NPC id & version & rack type & number of item
	iStream.read(m_ObjectID);
	iStream.read(m_Version);
	iStream.read(m_RackType);
	iStream.read(nTotal);

	// read each item info
	for (i=0; i<nTotal; i++)
	{
		iStream.read(index);
		iStream.read(m_pBuffer[index].itemClass);
		iStream.read(m_pBuffer[index].itemType);

		m_pBuffer[index].bExist = true;
	}

	// read market condition
	iStream.read(m_MarketCondBuy);
	iStream.read(m_MarketCondSell);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE i      = 0;
	BYTE nTotal = 0;
	
	// calculate total number of items
	for (i=0; i<SHOP_RACK_INDEX_MAX; i++)
		if (m_pBuffer[i].bExist) nTotal++;
		
	// write NPC id & version & rack type & number of item
	oStream.write(m_ObjectID);
	oStream.write(m_Version);
	oStream.write(m_RackType);
	oStream.write(nTotal);

	// write each item info
	for (i=0; i<SHOP_RACK_INDEX_MAX; i++)
	{
		if (m_pBuffer[i].bExist)
		{
			oStream.write(i);
			oStream.write(m_pBuffer[i].itemClass);
			oStream.write(m_pBuffer[i].itemType);
		}
	}

	oStream.write(m_MarketCondBuy);
	oStream.write(m_MarketCondSell);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopListMysteriousHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
PacketSize_t GCShopListMysterious::getPacketSize () const 
	throw ()
{ 
	PacketSize_t unit_size = szBYTE + szItemType;
	PacketSize_t rValue    = 0;

	rValue += szObjectID;     // NPC id
	rValue += szShopVersion;  // shop version
	rValue += szShopRackType; // rack type
	rValue += szBYTE;         // total number of item

	for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
	{
		if (m_pBuffer[i].bExist) 
		{
			rValue += szBYTE;    // Item index in shop rack
			rValue += unit_size; // actual item info
		}
	}

	rValue += szMarketCond*2; // market condition

	return rValue;
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCShopListMysterious::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShopListMysterious(" << "ObjectID:" << m_ObjectID << ","
	    << "ShopVersion:" << m_Version << ","
	    << "RackType:" << m_RackType << ",";
	
	for (int i=0; i<SHOP_RACK_INDEX_MAX; i++)
	{
		msg << "(Item" << i << ":";
		if (m_pBuffer[i].bExist)
		{
			msg << "ItemClass:" << (int)(m_pBuffer[i].itemClass) 
			    << "ItemType:"  << (int)(m_pBuffer[i].itemType);
		}
		msg << ")";
	}

	msg << "MarketCondBuy:"  << (int)m_MarketCondBuy
	    << "MarketCondSell:" << (int)m_MarketCondSell;

	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SHOPLISTITEM_MYSTERIOUS GCShopListMysterious::getShopItem(BYTE index) const
	throw()
{
	// check bound
	if (index >= SHOP_RACK_INDEX_MAX) throw ("GCShopListMysterious::getShopItem() : Out of Bound!");

	// return shop item info
	return m_pBuffer[index];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCShopListMysterious::setShopItem(BYTE index, const Item* pItem) 
	throw()
{
	// check bound
	if (index >= SHOP_RACK_INDEX_MAX) throw ("GCShopListMysterious::setShopItem() : Out of Bound!");

	// check pointer 
	Assert(pItem != NULL);

	// set shop item info
	m_pBuffer[index].bExist     = true;
	m_pBuffer[index].itemClass  = pItem->getItemClass();
	m_pBuffer[index].itemType   = pItem->getItemType();
}
