//--------------------------------------------------------------------------------
// 
// Filename    : CLQueryCharacterName.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __CL_QUERY_CHARACTER_NAME_H__
#define __CL_QUERY_CHARACTER_NAME_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLQueryCharacterName;
//
// Packet sent by the client on login when requesting character name lookup.
// ID and password are encrypted.
//
//--------------------------------------------------------------------------------

class CLQueryCharacterName : public Packet {

public:
	CLQueryCharacterName() {};
    virtual ~CLQueryCharacterName() {};
	// Initialize packet by reading data from the incoming stream.
    void read(SocketInputStream & iStream) ;
		    
	// Serialize packet data to the outgoing stream.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  
	{ 
		return szBYTE + m_CharacterName.size(); 
	}

	// get packet name
	string getPacketName() const  { return "CLQueryCharacterName"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set player's id
	string getCharacterName() const  { return m_CharacterName; }
	void setCharacterName(const string & playerID)  { m_CharacterName = playerID; }

private :

	// Player ID (character name)
	string m_CharacterName;

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameFactory;
//
// Factory for CLQueryCharacterName
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLQueryCharacterName(); }

	// get packet name
	string getPacketName() const  { return "CLQueryCharacterName"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_QUERY_CHARACTER_NAME; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  
	{ 
		return szBYTE + 20; 
	}

};


//--------------------------------------------------------------------------------
//
// class CLQueryCharacterNameHandler;
//
//--------------------------------------------------------------------------------

class CLQueryCharacterNameHandler {

public:

	// execute packet's handler
	static void execute(CLQueryCharacterName* pPacket, Player* pPlayer) ;

};

#endif
