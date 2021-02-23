//----------------------------------------------------------------------
// 
// Filename    : GCAddVampireCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_VAMPIRE_CORPSE_H__
#define __GC_ADD_VAMPIRE_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCAddVampireCorpse;
//
// 로그인이나 포탈, 텔레포트 등으로 슬레이어가 존에 새로 들어갔을 경우, 또는
// 슬레이어가 존에서 이동할 경우,(1) 이미 이 슬레이어에 대한 정보를 갖고 있는
//(즉 이 슬레이어를 보고 있는..) 영역에 존재하는 PC들에게는 GCMove 패킷을
// 브로드캐스트한다. 그러나,(2) 이 슬레이어를 처음 보게 되는 영역에 존재하는
// PC들에게는 GCAddVampireCorpse 패킷을 브로드캐스트한다. 또한,(3) 이 슬레이어는
// 자신이 새로 개척한 시야(?) 안에 존재하는 슬레이어들의 정보를 GCAddVampireCorpse에
// 담아서 받게 된다.
//
//----------------------------------------------------------------------

class GCAddVampireCorpse : public Packet {

public :

	// constructor
	GCAddVampireCorpse() throw() { m_TreasureCount = 0; }
	GCAddVampireCorpse(const PCVampireInfo3 & vampireInfo) throw() : m_VampireInfo(vampireInfo) {}

	
public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_VAMPIRE_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return m_VampireInfo.getSize() + szBYTE; }

	// get packet's name
	string getPacketName() const throw() { return "GCAddVampireCorpse"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get vampire info
	PCVampireInfo3 & getVampireInfo() throw() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo() const throw() { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & vampireInfo) throw() { m_VampireInfo = vampireInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount() const throw() { return m_TreasureCount; }
	void setTreasureCount(BYTE Count) throw() { m_TreasureCount = Count; }
	
private :
	
	// 뱀파이어 외모 정보
	PCVampireInfo3 m_VampireInfo;

	BYTE m_TreasureCount;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddVampireCorpseFactory;
//
// Factory for GCAddVampireCorpse
//
//--------------------------------------------------------------------------------

class GCAddVampireCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddVampireCorpse(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddVampireCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_VAMPIRE_CORPSE; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() const throw() { return PCVampireInfo3::getMaxSize() + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class GCAddVampireCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddVampireCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddVampireCorpse* pPacket, Player* pPlayer) throw(Error);

};

#endif
