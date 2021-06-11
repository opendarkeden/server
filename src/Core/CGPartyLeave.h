//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyLeave.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_PARTY_LEAVE_H__
#define __CG_PARTY_LEAVE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGPartyLeave
//////////////////////////////////////////////////////////////////////////////

class CGPartyLeave : public Packet 
{
public:
    CGPartyLeave() {};
    ~CGPartyLeave() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_PARTY_LEAVE; }
	PacketSize_t getPacketSize() const  { return szBYTE + m_TargetName.size(); }
	string getPacketName() const  { return "CGPartyLeave"; }
	string toString() const ;
	
public:
	string getTargetName(void) const  { return m_TargetName; }
	void setTargetName(const string& name) { m_TargetName = name; }

private:
	string m_TargetName;
};


//////////////////////////////////////////////////////////////////////////////
// class CGPartyLeaveFactory;
//////////////////////////////////////////////////////////////////////////////

class CGPartyLeaveFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGPartyLeave(); }
	string getPacketName() const  { return "CGPartyLeave"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_PARTY_LEAVE; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + 10; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGPartyLeaveHandler
//////////////////////////////////////////////////////////////////////////////

class CGPartyLeaveHandler 
{
public:
	static void execute(CGPartyLeave* pPacket, Player* player) ;
};

#endif
