//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherModifyInfo.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_MODIFY_INFO_H__
#define __GC_OTHER_MODIFY_INFO_H__

#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfo;
//////////////////////////////////////////////////////////////////////////////

class GCOtherModifyInfo : public ModifyInfo 
{
public:
    GCOtherModifyInfo() {};
    ~GCOtherModifyInfo() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_OTHER_MODIFY_INFO; }
	PacketSize_t getPacketSize() const  { return szObjectID + ModifyInfo::getPacketSize(); }
	string getPacketName() const  { return "GCOtherModifyInfo"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private:
	ObjectID_t m_ObjectID;
};


//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCOtherModifyInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCOtherModifyInfo(); }
	string getPacketName() const  { return "GCOtherModifyInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_OTHER_MODIFY_INFO; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCOtherModifyInfoHandler 
{
public:
	static void execute(GCOtherModifyInfo* pGCOtherModifyInfo, Player* pPlayer) ;
};

#endif
