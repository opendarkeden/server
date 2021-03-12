//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUsePotionFromInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_POTION_FROM_INVENTORY_H__
#define __CG_USE_POTION_FROM_INVENTORY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventory;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventory : public Packet {
public:

	// constructor
	CGUsePotionFromInventory() ;

	// destructor
	~CGUsePotionFromInventory() ;

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_USE_POTION_FROM_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromInventoryPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szObjectID + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName() const  { return "CGUsePotionFromInventory"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set Inventory X
	CoordInven_t getX() const  { return m_InvenX; }
	void setX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	// get / set Inventory Y
	CoordInven_t getY() const  { return m_InvenY; }
	void setY(CoordInven_t InvenY)  { m_InvenY = InvenY; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// Inventory의 X, Y 좌표
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventoryFactory;
//
// Factory for CGUsePotionFromInventory
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventoryFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGUsePotionFromInventory(); }

	// get packet name
	string getPacketName() const  { return "CGUsePotionFromInventory"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_USE_POTION_FROM_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromInventoryPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoordInven + szCoordInven; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventoryHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventoryHandler {
	
public:
	// execute packet's handler
	static void execute(CGUsePotionFromInventory* pPacket, Player* player) ;
};

#endif
