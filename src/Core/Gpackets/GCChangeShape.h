//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeShape.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CHANGE_SHAPE_H__
#define __GC_CHANGE_SHAPE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include <list>

#define SHAPE_FLAG_QUEST 0x01

//////////////////////////////////////////////////////////////////////
//
// class GCChangeShape;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCChangeShape : public Packet {

public :
	
	// constructor
	GCChangeShape() throw();
	
	// destructor
	~GCChangeShape() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_CHANGE_SHAPE; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE + szItemType + szOptionType + szSpeed + szBYTE ; }

	// get packet's name
	string getPacketName() const throw() { return "GCChangeShape"; }
	
	// get packet's debug string
	string toString() const throw();

	// get Object ID 
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

	// get/set ItemClass
	BYTE getItemClass() const throw() { return m_ItemClass; }
	void setItemClass(BYTE ItemClass) throw() { m_ItemClass = ItemClass; }

	// get / set ItemType
	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType ; }

	// get / set OptionType
	void setOptionType(OptionType_t optionType) throw() { m_OptionType = optionType; }
	OptionType_t getOptionType() const throw() { return m_OptionType; }

	// get / set AttackSpeed
	Speed_t getAttackSpeed() const throw() { return m_AttackSpeed; }
	void setAttackSpeed(Speed_t AttackSpeed) throw() { m_AttackSpeed = AttackSpeed; }

	BYTE getFlag() const throw() { return m_Flag; }
	void setFlag( BYTE flag ) throw() { m_Flag = flag; }

private :

	// 크리처 아이디
	ObjectID_t m_ObjectID;
	
	// Item Class
	BYTE m_ItemClass;

	// Item Type
	ItemType_t m_ItemType;

	// Option Type
	OptionType_t m_OptionType;

	// Attack Speed
	Speed_t m_AttackSpeed;

	BYTE m_Flag;
};


//////////////////////////////////////////////////////////////////////
//
// class GCChangeShapeFactory;
//
// Factory for GCChangeShape
//
//////////////////////////////////////////////////////////////////////

class GCChangeShapeFactory : public PacketFactory {

public :
	
	// constructor
	GCChangeShapeFactory() throw() {}
	
	// destructor
	virtual ~GCChangeShapeFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCChangeShape(); }

	// get packet name
	string getPacketName() const throw() { return "GCChangeShape"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CHANGE_SHAPE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE + szItemType + szOptionType + szSpeed + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCChangeShapeHandler;
//
//////////////////////////////////////////////////////////////////////

class GCChangeShapeHandler {

public :

	// execute packet's handler
	static void execute(GCChangeShape* pGCChangeShape, Player* pPlayer) throw(Error);

};

#endif
