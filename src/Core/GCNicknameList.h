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
	GCNicknameList() ;
	~GCNicknameList() ;
	
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_NICKNAME_LIST; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCNicknameList"; }
	string toString() const ;

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
	GCNicknameListFactory()  {}
	virtual ~GCNicknameListFactory()  {}
	
public:
	Packet* createPacket()  { return new GCNicknameList(); }
	string getPacketName() const  { return "GCNicknameList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_NICKNAME_LIST; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + NicknameInfo::getMaxSize() * MAX_NICKNAME_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCNicknameListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNicknameListHandler 
{
public:
	static void execute(GCNicknameList* pGCNicknameList, Player* pPlayer) ;

};

#endif
