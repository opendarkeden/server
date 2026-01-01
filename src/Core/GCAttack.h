//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttack.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_H__
#define __GC_ATTACK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttack;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCAttack : public Packet {

public :
	
	// constructor
	GCAttack() ;
	
	// destructor
	~GCAttack() noexcept;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_ATTACK; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord + szCoord + szDir ; }

	// get packet's name
	string getPacketName() const  { return "GCAttack"; }
	
	// get packet's debug string
	string toString() const ;

	// get Object ID 
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID)  { m_ObjectID = objectID; }

	// get/set X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	// get/set Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	// get/set Dir
	Dir_t getDir() const  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }


private :

	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_X;				// X ��ǥ
	Coord_t m_Y;				// Y ��ǥ
	Dir_t m_Dir;				// ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackFactory;
//
// Factory for GCAttack
//
//////////////////////////////////////////////////////////////////////

class GCAttackFactory : public PacketFactory {

public :
	
	// constructor
	GCAttackFactory()  {}
	
	// destructor
	virtual ~GCAttackFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCAttack(); }

	// get packet name
	string getPacketName() const  { return "GCAttack"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ATTACK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord + szCoord + szDir ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackHandler {

public :

	// execute packet's handler
	static void execute(GCAttack* pGCAttack, Player* pPlayer) ;

};

#endif
