//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetStashList.h 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PET_STASH_LIST_H__
#define __GC_PET_STASH_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PetInfo.h"
#include <vector>

#define MAX_PET_STASH	20

struct PetStashItemInfo
{
	PetInfo* pPetInfo;
	DWORD KeepDays;

	PacketSize_t getPacketSize() const { return szBYTE + pPetInfo->getSize() + szDWORD; }
	static PacketSize_t	getPacketMaxSize() { return szBYTE + PetInfo::getMaxSize() + szDWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCPetStashList;
//////////////////////////////////////////////////////////////////////////////

class GCPetStashList : public Packet 
{
public:
	GCPetStashList() throw();
	virtual ~GCPetStashList() throw();

	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_PET_STASH_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCPetStashList"; }
	string toString() const throw();

public:
	BYTE	getCode() const { return m_Code; }
	void	setCode( BYTE code ) { m_Code = code; }

	vector<PetStashItemInfo*>& getPetStashItemInfos() { return m_PetStashItemInfos; }

private:
	BYTE						m_Code;
	vector<PetStashItemInfo*>	m_PetStashItemInfos;
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetStashListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPetStashListFactory : public PacketFactory 
{
public :
	Packet* createPacket() throw() { return new GCPetStashList(); }
	string getPacketName() const throw() { return "GCPetStashList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_PET_STASH_LIST; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + PetStashItemInfo::getPacketMaxSize() * MAX_PET_STASH; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetStashListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPetStashListHandler 
{
public :
	static void execute(GCPetStashList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
