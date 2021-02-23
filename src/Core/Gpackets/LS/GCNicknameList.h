//////////////////////////////////////////////////////////////////////////////
// Filename	: GCNicknameList.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NICKNAME_LIST_H__
#define __GC_NICKNAME_LIST_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "NicknameInfo.h"

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class GCNicknameList;
//////////////////////////////////////////////////////////////////////////////

#define MAX_NICKNAME_NUM	500

class GCNicknameList : public Packet 
{
public:
	GCNicknameList() throw();
	~GCNicknameList() throw();
	
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_NICKNAME_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCNicknameList"; }
	string toString() const throw();

public:
	vector<NicknameInfo*>& getNicknames() { return m_Nicknames; }

private :
	vector<NicknameInfo*>	m_Nicknames;
};

//////////////////////////////////////////////////////////////////////////////
// class GCNicknameListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNicknameListFactory : public PacketFactory 
{
public :
	GCNicknameListFactory() throw() {}
	virtual ~GCNicknameListFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCNicknameList(); }
	string getPacketName() const throw() { return "GCNicknameList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NICKNAME_LIST; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + NicknameInfo::getMaxSize() * MAX_NICKNAME_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCNicknameListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNicknameListHandler 
{
public:
	static void execute(GCNicknameList* pGCNicknameList, Player* pPlayer) throw(Error);

};

#endif
