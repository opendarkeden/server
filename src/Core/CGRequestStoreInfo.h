//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestStoreInfo.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_STORE_INFO_H__
#define __CG_REQUEST_STORE_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestStoreInfo;
//
//////////////////////////////////////////////////////////////////////

class CGRequestStoreInfo : public Packet
{
public:
	CGRequestStoreInfo() {};
    virtual ~CGRequestStoreInfo() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_REQUEST_STORE_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID; }

	// get packet name
	string getPacketName() const  { return "CGRequestStoreInfo"; }

	// get packet's debug string
	string toString() const ;

	ObjectID_t	getOwnerObjectID() const { return m_OwnerObjectID; }
	void		setOwnerObjectID(ObjectID_t oid) { m_OwnerObjectID = oid; }

private:
	ObjectID_t	m_OwnerObjectID;	// 0이면 자기 자신의 상점 정보
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestStoreInfoFactory;
//
// Factory for CGRequestStoreInfo
//
//////////////////////////////////////////////////////////////////////

class CGRequestStoreInfoFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestStoreInfoFactory()  {}
	
	// destructor
	virtual ~CGRequestStoreInfoFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGRequestStoreInfo(); }

	// get packet name
	string getPacketName() const  { return "CGRequestStoreInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_REQUEST_STORE_INFO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestStoreInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestStoreInfoHandler {

public:

	// execute packet's handler
	static void execute(CGRequestStoreInfo* pCGRequestStoreInfo, Player* pPlayer) ;

};

#endif
