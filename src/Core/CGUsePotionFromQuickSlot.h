//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUsePotionFromQuickSlot.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_POTION_FROM_QUICKSLOT_H__
#define __CG_USE_POTION_FROM_QUICKSLOT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromQuickSlot;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromQuickSlot : public Packet {
public:

	// constructor
	CGUsePotionFromQuickSlot() throw();

	// destructor
	~CGUsePotionFromQuickSlot() throw();

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_USE_POTION_FROM_QUICKSLOT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromQuickSlotPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szSlotID; }

	// get packet name
	string getPacketName() const throw() { return "CGUsePotionFromQuickSlot"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set QuickSlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// QuickSlot의 ID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromQuickSlotFactory;
//
// Factory for CGUsePotionFromQuickSlot
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromQuickSlotFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGUsePotionFromQuickSlot(); }

	// get packet name
	string getPacketName() const throw() { return "CGUsePotionFromQuickSlot"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_USE_POTION_FROM_QUICKSLOT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromQuickSlotPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromQuickSlotHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromQuickSlotHandler {
	
public:

	// execute packet's handler
	static void execute(CGUsePotionFromQuickSlot* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
