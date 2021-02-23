//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectNickname.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_NICKNAME_H__
#define __CG_SELECT_NICKNAME_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectNickname;
//
//////////////////////////////////////////////////////////////////////

class CGSelectNickname : public Packet
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_SELECT_NICKNAME; }
	PacketSize_t getPacketSize() const throw() { return szWORD; }
	string getPacketName() const throw() { return "CGSelectNickname"; }
	string toString() const throw();

	WORD getNicknameID() const throw() { return m_NicknameID; }
	void setNicknameID( WORD NicknameID ) throw() { m_NicknameID = NicknameID; }

private :
	WORD m_NicknameID;
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectNicknameFactory;
//
// Factory for CGSelectNickname
//
//////////////////////////////////////////////////////////////////////

class CGSelectNicknameFactory : public PacketFactory {

public:
	CGSelectNicknameFactory() throw() {}
	virtual ~CGSelectNicknameFactory() throw() {}

	
public:
	Packet* createPacket() throw() { return new CGSelectNickname(); }
	string getPacketName() const throw() { return "CGSelectNickname"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SELECT_NICKNAME; }
	PacketSize_t getPacketMaxSize() const throw() { return szWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectNicknameHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectNicknameHandler {

public:

	// execute packet's handler
	static void execute(CGSelectNickname* pCGSelectNickname, Player* pPlayer) throw(Error);

};

#endif
