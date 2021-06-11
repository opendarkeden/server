
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectBloodBible.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_BLOOD_BIBLE_H__
#define __CG_SELECT_BLOOD_BIBLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBible;
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBible : public Packet
{
public:
	CGSelectBloodBible() {};
    virtual ~CGSelectBloodBible() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SELECT_BLOOD_BIBLE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szItemType; }

	// get packet name
	string getPacketName() const  { return "CGSelectBloodBible"; }

	// get packet's debug string
	string toString() const ;

	// get/set BloodBibleID
	ItemType_t getBloodBibleID() const  { return m_BloodBibleID; }
	void setBloodBibleID(ItemType_t BloodBibleID )  { m_BloodBibleID = BloodBibleID; }


private :

	// BloodBible ID
	ItemType_t m_BloodBibleID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBibleFactory;
//
// Factory for CGSelectBloodBible
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBibleFactory : public PacketFactory {

public:
	
	// constructor
	CGSelectBloodBibleFactory()  {}
	
	// destructor
	virtual ~CGSelectBloodBibleFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGSelectBloodBible(); }

	// get packet name
	string getPacketName() const  { return "CGSelectBloodBible"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SELECT_BLOOD_BIBLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szItemType; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBibleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBibleHandler {

public:

	// execute packet's handler
	static void execute(CGSelectBloodBible* pCGSelectBloodBible, Player* pPlayer) ;

};

#endif
