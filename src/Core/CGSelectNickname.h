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
    CGSelectNickname() {};
    virtual ~CGSelectNickname() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_SELECT_NICKNAME; }
	PacketSize_t getPacketSize() const  { return szWORD; }
	string getPacketName() const  { return "CGSelectNickname"; }
	string toString() const ;

	WORD getNicknameID() const  { return m_NicknameID; }
	void setNicknameID(WORD NicknameID )  { m_NicknameID = NicknameID; }

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
	CGSelectNicknameFactory()  {}
	virtual ~CGSelectNicknameFactory()  {}

	
public:
	Packet* createPacket()  { return new CGSelectNickname(); }
	string getPacketName() const  { return "CGSelectNickname"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SELECT_NICKNAME; }
	PacketSize_t getPacketMaxSize() const  { return szWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectNicknameHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectNicknameHandler {

public:

	// execute packet's handler
	static void execute(CGSelectNickname* pCGSelectNickname, Player* pPlayer) ;

};

#endif
