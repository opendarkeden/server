//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyNickname.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_NICKNAME_H__
#define __CG_MODIFY_NICKNAME_H__

#include "Packet.h"
#include "PacketFactory.h"

#include "NicknameInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNickname;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNickname : public Packet 
{
public:
	CGModifyNickname() ;
	~CGModifyNickname() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_MODIFY_NICKNAME; }
	PacketSize_t getPacketSize() const  { return szObjectID + szBYTE + m_Nickname.size(); }
	string getPacketName() const  { return "CGModifyNickname"; }
	string toString() const ;
	
public:
	ObjectID_t	getItemObjectID() const { return m_ItemObjectID; }
	void		setItemObjectID(WORD id) { m_ItemObjectID = id; }

	string		getNickname() const { return m_Nickname; }
	void		setNickname(const string& name) { m_Nickname = name; }
private:
	ObjectID_t	m_ItemObjectID;
	string		m_Nickname;
};

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNicknameFactory;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNicknameFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGModifyNickname(); }
	string getPacketName() const  { return "CGModifyNickname"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_MODIFY_NICKNAME; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szBYTE + MAX_NICKNAME_SIZE; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNicknameHandler;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNicknameHandler 
{
public:
	static void execute(CGModifyNickname* pPacket, Player* player) ;
};

#endif
