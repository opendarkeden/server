//////////////////////////////////////////////////////////////////////////////
// Filename    : CGThrowBomb.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_THROW_BOMB_H__
#define __CG_THROW_BOMB_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGThrowBomb;
//////////////////////////////////////////////////////////////////////////////

class CGThrowBomb : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_THROW_BOMB; }
	PacketSize_t getPacketSize() const throw() { return szCoord * 4 + szBYTE; }
	string getPacketName() const throw() { return "CGThrowBomb"; }
	string toString() const throw();

public:
	Coord_t getZoneX(void) const { return m_ZoneX; }
	void setZoneX(Coord_t X) { m_ZoneX = X; }

	Coord_t getZoneY(void) const { return m_ZoneY; }
	void setZoneY(Coord_t Y) { m_ZoneY = Y; }

	Coord_t getBombX(void) const { return m_BombX; }
	void setBombX(Coord_t X) { m_BombX = X; }

	Coord_t getBombY(void) const { return m_BombY; }
	void setBombY(Coord_t Y) { m_BombY = Y; }

	BYTE getAttackSlayerFlag(void) const { return m_AttackSlayerFlag; }
	void setAttackSlayerFlag(BYTE flag) { m_AttackSlayerFlag = flag; }

private:
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;
	Coord_t m_BombX;
	Coord_t m_BombY;
	BYTE    m_AttackSlayerFlag;
};

//////////////////////////////////////////////////////////////////////////////
// class CGThrowBombFactory;
// Factory for CGThrowBomb
//////////////////////////////////////////////////////////////////////////////

class CGThrowBombFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGThrowBomb(); }
	string getPacketName() const throw() { return "CGThrowBomb"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_THROW_BOMB; }
	PacketSize_t getPacketMaxSize() const throw() { return szCoord * 4 + szBYTE; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGThrowBombHandler;
//////////////////////////////////////////////////////////////////////////////

class CGThrowBombHandler 
{
public:
	static void execute(CGThrowBomb* pCGThrowBomb, Player* pPlayer) throw(Error);
};

#endif
