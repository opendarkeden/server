//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_OK_H__
#define __GC_USE_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCUseOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseOK : public ModifyInfo {

public :

	// Constructor
	GCUseOK() throw();

	// Desctructor
	~GCUseOK() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_USE_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const throw() { return ModifyInfo::getPacketSize(); }

	// get packet name
	string getPacketName() const throw() { return "GCUseOK"; }
	
	// get packet's debug string
	string toString() const throw();

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKFactory;
//
// Factory for GCUseOK
//
//////////////////////////////////////////////////////////////////////

class GCUseOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUseOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCUseOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_USE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCUseOK* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
