//////////////////////////////////////////////////////////////////////////////
// Filename    : GCModifyNickname.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_NICKNAME_H__
#define __GC_MODIFY_NICKNAME_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

#include "NicknameInfo.h"

class GCModifyNickname : public Packet
{
public:
	GCModifyNickname() throw();
	virtual ~GCModifyNickname() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_MODIFY_NICKNAME; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + m_pNicknameInfo->getSize(); }
	string getPacketName() const throw() { return "GCModifyNickname"; }
	string toString() const throw();

public:
	void		setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	ObjectID_t	getObjectID() const { return m_ObjectID; }

//	NicknameInfo&	getNicknameInfo() { return m_NicknameInfo; }
	NicknameInfo*	getNicknameInfo() const { return m_pNicknameInfo; }
	void			setNicknameInfo(NicknameInfo* pNicknameInfo) { m_pNicknameInfo = pNicknameInfo; }
private:
	ObjectID_t		m_ObjectID;
	NicknameInfo*	m_pNicknameInfo;
};

class GCModifyNicknameFactory : public PacketFactory {

public :
	
	Packet* createPacket() throw() { return new GCModifyNickname(); }
	string getPacketName() const throw() { return "GCModifyNickname"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MODIFY_NICKNAME; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + NicknameInfo::getMaxSize(); }
};

class GCModifyNicknameHandler {
	
public :
	static void execute(GCModifyNickname* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif // __GC_MODIFY_NICKNAME_H__

