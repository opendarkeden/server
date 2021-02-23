//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTimeLimitItemInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TIME_LIMIT_ITEM_INFO_H__
#define __GC_TIME_LIMIT_ITEM_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <map>

#define MAX_TIME_LIMIT_ITEM_INFO 100

//////////////////////////////////////////////////////////////////////
//
// class GCTimeLimitItemInfo;
//
//
//////////////////////////////////////////////////////////////////////

class GCTimeLimitItemInfo : public Packet {
public:
	typedef map<ObjectID_t,DWORD> ItemTimeLimitMap;

public :
	GCTimeLimitItemInfo() throw();
	~GCTimeLimitItemInfo() throw();

    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t getPacketID() const throw() { return PACKET_GC_TIME_LIMIT_ITEM_INFO; }
	PacketSize_t getPacketSize() const throw();

	string getPacketName() const throw() { return "GCTimeLimitItemInfo"; }
	string toString() const throw();

public:

	DWORD	getTimeLimit(ObjectID_t objectID) const throw(Error);
	void	addTimeLimit(ObjectID_t objectID, DWORD time) throw(Error);


private :
	
	ItemTimeLimitMap	m_TimeLimitItemInfos;
};


//////////////////////////////////////////////////////////////////////
//
// class GCTimeLimitItemInfoFactory;
//
// Factory for GCTimeLimitItemInfo
//
//////////////////////////////////////////////////////////////////////

class GCTimeLimitItemInfoFactory : public PacketFactory {

public :
	Packet* createPacket() throw() { return new GCTimeLimitItemInfo(); }
	string getPacketName() const throw() { return "GCTimeLimitItemInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TIME_LIMIT_ITEM_INFO; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + MAX_TIME_LIMIT_ITEM_INFO * ( szObjectID + szDWORD ); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCTimeLimitItemInfo;
//
//////////////////////////////////////////////////////////////////////

class GCTimeLimitItemInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCTimeLimitItemInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
