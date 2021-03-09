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
	GCTimeLimitItemInfo() ;
	~GCTimeLimitItemInfo() ;

    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;

	PacketID_t getPacketID() const  { return PACKET_GC_TIME_LIMIT_ITEM_INFO; }
	PacketSize_t getPacketSize() const ;

	string getPacketName() const  { return "GCTimeLimitItemInfo"; }
	string toString() const ;

public:

	DWORD	getTimeLimit(ObjectID_t objectID) const ;
	void	addTimeLimit(ObjectID_t objectID, DWORD time) ;


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
	Packet* createPacket()  { return new GCTimeLimitItemInfo(); }
	string getPacketName() const  { return "GCTimeLimitItemInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_TIME_LIMIT_ITEM_INFO; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + MAX_TIME_LIMIT_ITEM_INFO * (szObjectID + szDWORD); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCTimeLimitItemInfo;
//
//////////////////////////////////////////////////////////////////////

class GCTimeLimitItemInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCTimeLimitItemInfo* pPacket, Player* pPlayer) ;

};

#endif
