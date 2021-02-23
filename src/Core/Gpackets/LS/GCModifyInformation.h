//////////////////////////////////////////////////////////////////////////////
// Filename    : GCModifyInformation.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_INFORMATION_H__
#define __GC_MODIFY_INFORMATION_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCModifyInformation;
//////////////////////////////////////////////////////////////////////////////

class GCModifyInformation : public ModifyInfo
{
public:
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_MODIFY_INFORMATION; }
	string getPacketName() const throw() { return "GCModifyInformation"; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCModifyInformationFactory;
//////////////////////////////////////////////////////////////////////////////

class GCModifyInformationFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCModifyInformation(); }
	string getPacketName() const throw() { return "GCModifyInformation"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MODIFY_INFORMATION; }
	PacketSize_t getPacketMaxSize() const throw() { return ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////////////
// class GCModifyInformationHandler;
//////////////////////////////////////////////////////////////////////////////

class GCModifyInformationHandler 
{
public:
	static void execute(GCModifyInformation* pGCModifyInformation, Player* pPlayer) throw(Error);

};

#endif
