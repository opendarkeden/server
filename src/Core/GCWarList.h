//////////////////////////////////////////////////////////////////////////////
// Filename    : GCWarList.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_WAR_LIST_H__
#define __GC_WAR_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"
#include "GuildWarInfo.h"
#include "RaceWarInfo.h"
#include <list>

typedef list<WarInfo*> 					WarInfoList;
typedef WarInfoList::const_iterator 	WarInfoListItor;

class GCWarList : public Packet
{
public:
	GCWarList() ;
	virtual ~GCWarList() ;

	void	clear() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_WAR_LIST; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCWarList"; }
	string toString() const ;

public:
	int 	getSize() const  { return m_WarInfos.size(); }
	bool 	isEmpty() const  { return m_WarInfos.empty(); }

	void addWarInfo(WarInfo* pWarInfo )  { m_WarInfos.push_back(pWarInfo); }
	WarInfo* popWarInfo() ;

	void	operator = (const GCWarList& WL);

private:
	WarInfoList m_WarInfos;
};

class GCWarListFactory : public PacketFactory {

public :
	
	Packet* createPacket()  { return new GCWarList(); }
	string getPacketName() const  { return "GCWarList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_WAR_LIST; }
	PacketSize_t getPacketMaxSize() const  { return (RaceWarInfo::getMaxSize() + GuildWarInfo::getMaxSize()) * 12; }
};

class GCWarListHandler {
	
public :
	static void execute(GCWarList* pPacket, Player* pPlayer) ;

};



#endif // __GC_WAR_LIST_H__

