//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildRegist.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_REGIST_H__
#define __GC_SHOW_GUILD_REGIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegist;
//
// Shows the guild registration window to the client.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegist : public Packet {

public :
	GCShowGuildRegist() {};
    ~GCShowGuildRegist() {};
	// Initialize the packet by reading data from the input stream.
    void read(SocketInputStream & iStream) ;
		    
	// Serialize the packet into the output stream.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOW_GUILD_REGIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szGold; }

	// get packet name
	string getPacketName() const  { return "GCShowGuildRegist"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set Registration Fee
	Gold_t getRegistrationFee() const  { return m_RegistrationFee; }
	void setRegistrationFee(Gold_t registrationFee )  { m_RegistrationFee = registrationFee; }
	

private :
	
	// Registration Fee
	Gold_t m_RegistrationFee;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegistFactory;
//
// Factory for GCShowGuildRegist
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegistFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCShowGuildRegist(); }

	// get packet name
	string getPacketName() const  { return "GCShowGuildRegist"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOW_GUILD_REGIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// Use GCSystemMessagePacketMaxSize if that constant is defined.
	PacketSize_t getPacketMaxSize() const  { return szGold; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegist;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegistHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildRegist* pPacket, Player* pPlayer) ;

};

#endif
