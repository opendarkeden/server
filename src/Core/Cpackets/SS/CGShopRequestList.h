//--------------------------------------------------------------------------------
// 
// Filename    : CGShopRequestList.h 
// Written By  : 김성민
// Description : 플레이어가 가지고 있는 상점 버전과 서버가 가지고 있는 상점의
//               버전이 다를 경우, 플레이어는 서버에게 상품의 리스트를 
//               요청하게 된다. 이 패킷은 그때 보내게 되는 패킷이다.
// 
//--------------------------------------------------------------------------------

#ifndef __CG_SHOP_REQUEST_LIST_H__
#define __CG_SHOP_REQUEST_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGShopRequestList;
//
//--------------------------------------------------------------------------------

class CGShopRequestList : public Packet {

public:
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_SHOP_REQUEST_LIST; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGShopRequestListPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szObjectID+szShopRackType; }

	// get packet name
	string getPacketName() const throw() { return "CGShopRequestList"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	ShopRackType_t getRackType(void) throw() { return m_RackType; }
	void setRackType(ShopRackType_t type) throw() { m_RackType = type; }

private :
	
	// ObjectID
	ObjectID_t     m_ObjectID;
	ShopRackType_t m_RackType;

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListFactory;
//
// Factory for CGShopRequestList
//
//--------------------------------------------------------------------------------

class CGShopRequestListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGShopRequestList(); }

	// get packet name
	string getPacketName() const throw() { return "CGShopRequestList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SHOP_REQUEST_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID+szShopRackType; }

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListHandler;
//
//--------------------------------------------------------------------------------

class CGShopRequestListHandler {
	
public:

	// execute packet's handler
	static void execute(CGShopRequestList* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
