//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneConnected.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_CONNECTED_H__
#define __GC_PHONE_CONNECTED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnected;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnected : public Packet {

public :
	
	// constructor
	GCPhoneConnected() ;
	
	// destructor
	~GCPhoneConnected() ;

	
public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_PHONE_CONNECTED; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szPhoneNumber + szSlotID + szBYTE + m_Name.size(); }

	// get packet's name
	string getPacketName() const  { return "GCPhoneConnected"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set PhoneNumber
	PhoneNumber_t getPhoneNumber() const  { return m_PhoneNumber; }
	void setPhoneNumber(PhoneNumber_t PhoneNumber)  { m_PhoneNumber = PhoneNumber; }

	// get/set SlotID
	SlotID_t getSlotID() const  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }

	// get/set Name
	string getName() const  { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

private :

	// PhoneNumber
	PhoneNumber_t m_PhoneNumber;

	// SlotID
	SlotID_t m_SlotID;

	// 전화 거는 상대의 이름
	string m_Name;

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectedFactory;
//
// Factory for GCPhoneConnected
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectedFactory : public PacketFactory {

public :
	
	// constructor
	GCPhoneConnectedFactory()  {}
	
	// destructor
	virtual ~GCPhoneConnectedFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCPhoneConnected(); }

	// get packet name
	string getPacketName() const  { return "GCPhoneConnected"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_PHONE_CONNECTED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szPhoneNumber + szSlotID + szBYTE + 20; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectedHandler {

public :

	// execute packet's handler
	static void execute(GCPhoneConnected* pGCPhoneConnected, Player* pPlayer) ;

};

#endif
