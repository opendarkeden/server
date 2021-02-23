//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSellOK.h 
// Written By  : 김성민
// Description : 플레이어가 상점 NPC에게 물건 구입을 요청했을 때, 제대로
//               인증이 되면 이 패킷이 플레이어에게 날아간다.
//               클라이언트는 이 패킷을 받아서 상점 버전을 업데이트하고,
//               오브젝트 ID로 아이템 정보를 체크해 놓고, 가격을 이용해
//               플레이어의 돈을 업데이트한다.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SELL_OK_H__
#define __GC_SHOP_SELL_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSellOK;
//
//--------------------------------------------------------------------------------

class GCShopSellOK : public Packet 
{

public :

	GCShopSellOK() throw();
	virtual ~GCShopSellOK() throw();
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_SELL_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID + szShopVersion + szObjectID + szPrice;
	}

	// get packet name
	string getPacketName() const throw() { return "GCShopSellOK"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set shop version	
	ShopVersion_t getShopVersion(void) const throw() { return m_Version;}
	void setShopVersion(const ShopVersion_t ver) throw() { m_Version = ver;}

	// get/set item object id
	ObjectID_t getItemObjectID() const throw() { return m_ItemObjectID;}
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id;}

	// get/set price
	Price_t getPrice() const throw() { return m_Price;}
	void setPrice(Price_t price) { m_Price = price;}

private :
	

	// NPC's object id
	ObjectID_t m_ObjectID;
	
	// 상점 버젼
	ShopVersion_t m_Version;
	
	// 아이템 정보
	ObjectID_t    m_ItemObjectID;

	// 가격
	Price_t       m_Price;

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellOKFactory;
//
// Factory for GCShopSellOK
//
//////////////////////////////////////////////////////////////////////

class GCShopSellOKFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShopSellOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCShopSellOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_SELL_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID + szShopVersion + szObjectID + szPrice;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSellOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSellOKHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopSellOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
