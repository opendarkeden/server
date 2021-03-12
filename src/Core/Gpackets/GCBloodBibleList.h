//////////////////////////////////////////////////////////////////////////////
// Filename    : GCBloodBibleList.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_BIBLE_LIST_H__
#define __GC_BLOOD_BIBLE_LIST_H__

#include <vector>
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleList;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleList : public Packet
{
public:
	GCBloodBibleList()  { }
	virtual ~GCBloodBibleList() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_BLOOD_BIBLE_LIST; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCBloodBibleList"; }
	string toString() const ;

public:
	vector<ItemType_t>&	getList() { return m_BloodBibleList; }
	const vector<ItemType_t>&	getList() const { return m_BloodBibleList; }

private:
	vector<ItemType_t>	m_BloodBibleList;
};

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleListFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCBloodBibleList(); }
	string getPacketName() const  { return "GCBloodBibleList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_BLOOD_BIBLE_LIST; }
	PacketSize_t getPacketMaxSize() const 
	{
		return szBYTE
			 + szItemType * 12;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleListHandler 
{
public:
	static void execute(GCBloodBibleList* pPacket, Player* pPlayer) ;
};

#endif
