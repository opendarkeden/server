//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCGetDamage.h 
// Written By  :  elca@ewestsoft.com
// Description :  클라이언트로 부터 CGMove 패킷이 날라 왔을때 
//                날린 클라이언트에게 무브해도 좋다는 허가를 낼때
//                보내주는 패킷 클래스이다.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_DAMAGE_H__
#define __GC_GET_DAMAGE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamage;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCGetDamage : public Packet {

public :
	
	// constructor
	GCGetDamage() throw();
	
	// destructor
	~GCGetDamage() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_GET_DAMAGE; }
	
	// get packet size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szWORD; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCGetDamage"; }
	
	// get packet's debug string
	string toString() const throw();
	
	// get/set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get/set Damage
	WORD getDamage() const throw() { return m_GetDamage; }
	void setDamage(WORD GetDamage) throw() { m_GetDamage = GetDamage; }
	
private : 
	ObjectID_t m_ObjectID;  // ObjectID..
	WORD m_GetDamage;   		// Damage..

};


//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamageFactory;
//
// Factory for  GCGetDamage
//
//////////////////////////////////////////////////////////////////////

class  GCGetDamageFactory : public PacketFactory {

public :
	
	// constructor
	 GCGetDamageFactory() throw() {}
	
	// destructor
	virtual ~GCGetDamageFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCGetDamage(); }

	// get packet name
	string getPacketName() const throw() { return "GCGetDamage"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GET_DAMAGE; }
	
	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamageHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCGetDamageHandler {

public :

	// execute packet's handler
	static void execute( GCGetDamage* pGCGetDamage, Player* pPlayer) throw(Error);

};

#endif
