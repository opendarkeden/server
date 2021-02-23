//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToInventory.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SKILL_TO_INVENTORY_H__
#define __CG_SKILL_TO_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSkillToInventory;
//////////////////////////////////////////////////////////////////////////////

class CGSkillToInventory : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_SKILL_TO_INVENTORY; }
	PacketSize_t getPacketSize() const throw() { return szSkillType + szObjectID + szCoordInven*4; }
	string getPacketName() const throw() { return "CGSkillToInventory"; }
	string toString() const throw();

public:
	SkillType_t getSkillType() const throw()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	CoordInven_t getX() const throw() { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	CoordInven_t getY() const throw() { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }

	CoordInven_t getTargetX() const throw() { return m_TargetX; }
	void setTargetX(Coord_t TargetX) throw() { m_TargetX = TargetX; }

	CoordInven_t getTargetY() const throw() { return m_TargetY; }
	void setTargetY(Coord_t TargetY) throw() { m_TargetY = TargetY; }

private :
	SkillType_t  m_SkillType;	// SkillType
	ObjectID_t   m_ObjectID;	// ObjectID
	CoordInven_t m_X;			// Coord X
	CoordInven_t m_Y;			// Coord Y
	CoordInven_t m_TargetX;		// Target X
	CoordInven_t m_TargetY;		// Target Y
};

//////////////////////////////////////////////////////////////////////////////
// class CGSkillToInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSkillToInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGSkillToInventory(); }
	string getPacketName() const throw() { return "CGSkillToInventory"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SKILL_TO_INVENTORY; }
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szObjectID + szCoordInven*4; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGSkillToInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSkillToInventoryHandler 
{
public:
	static void execute(CGSkillToInventory* pCGSkillToInventory, Player* pPlayer) throw(Error);
};

#endif
