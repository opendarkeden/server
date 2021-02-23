//--------------------------------------------------------------------------------
// 
// Filename    : GCDeleteObject.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_DELETE_OBJECT_H__
#define __GC_DELETE_OBJECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class GCDeleteObject;
//
// 존의 특정 객체가 시야에서 사라진 경우에 전송되며, 클라이언트는 이 패킷을 받으면
// 패킷 내부의 OID를 사용해서 해당되는 객체를 찾아서 클라이언트의 존에서 삭제해야 한다.
//
// 다음은 이 패킷이 전송되는 구체적인 상황의 예시이다.
//
//(1) PC가 로그아웃한 경우
//(2) 아이템을 크리처가 줍는 경우
//(3) 특정 이펙트가 사라진 경우
//(4) 시체가 사라진 경우
//
// *CAUTION*
//
//(3) 특정 이펙트가 사라진 경우.. 는 이펙트가 생성될 때, 사라지는 시간이 전송되기
// 때문에, 삭제되어도 무방할 것이다. -_-;
//
//--------------------------------------------------------------------------------

class GCDeleteObject : public Packet {

public :

	// constructor
	GCDeleteObject() throw()
	{
	}

	GCDeleteObject(ObjectID_t objectID) throw()
		: m_ObjectID(objectID)
	{
	}


public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_DELETE_OBJECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID; 
	}

	// get packet name
	string getPacketName() const throw() { return "GCDeleteObject"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

private :

	// object id
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteObjectFactory;
//
// Factory for GCDeleteObject
//
//////////////////////////////////////////////////////////////////////

class GCDeleteObjectFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDeleteObject(); }

	// get packet name
	string getPacketName() const throw() { return "GCDeleteObject"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_DELETE_OBJECT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteObjectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteObjectHandler {

public :

	// execute packet's handler
	static void execute(GCDeleteObject* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
