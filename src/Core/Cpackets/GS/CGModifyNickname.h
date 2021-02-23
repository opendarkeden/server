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
	CGModifyNickname() throw();
	~CGModifyNickname() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_MODIFY_NICKNAME; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE + m_Nickname.size(); }
	string getPacketName() const throw() { return "CGModifyNickname"; }
	string toString() const throw();
	
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
	Packet* createPacket() throw() { return new CGModifyNickname(); }
	string getPacketName() const throw() { return "CGModifyNickname"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_MODIFY_NICKNAME; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE + MAX_NICKNAME_SIZE; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNicknameHandler;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNicknameHandler 
{
public:
	static void execute(CGModifyNickname* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
