//////////////////////////////////////////////////////////////////////////////
// Filename    : GCWarScheduleList.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_WAR_SCHEDULE_LIST_H__
#define __GC_WAR_SCHEDULE_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"
#include <list>

#define MAX_WAR_NUM 20

struct WarScheduleInfo {
	BYTE warType;		// 0 : 동족간 1 : 종족간
	WORD year;
	BYTE month;
	BYTE day;
	BYTE hour;
	GuildID_t challengerGuildID[5];
	string challengerGuildName[5];
	GuildID_t reinforceGuildID;
	string reinforceGuildName;
};

typedef list<WarScheduleInfo*> WarScheduleInfoList;
typedef WarScheduleInfoList::const_iterator WarScheduleInfoListItor;

class GCWarScheduleList : public Packet
{
public:
	GCWarScheduleList() ;
	virtual ~GCWarScheduleList() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_WAR_SCHEDULE_LIST; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCWarScheduleList"; }
	string toString() const ;

public:
	void addWarScheduleInfo(WarScheduleInfo* warInfo )  { m_WarScheduleList.push_back(warInfo); }
	WarScheduleInfo* popWarScheduleInfo() ;

private:
	WarScheduleInfoList m_WarScheduleList;
};

class GCWarScheduleListFactory : public PacketFactory {

public :
	
	Packet* createPacket()  { return new GCWarScheduleList(); }
	string getPacketName() const  { return "GCWarScheduleList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_WAR_SCHEDULE_LIST; }
	PacketSize_t getPacketMaxSize() const  {
		return (
			szBYTE + 
			(szBYTE+szWORD+szBYTE+szBYTE+szBYTE+szGuildID*6+(szBYTE*16)*6 ) * MAX_WAR_NUM
		);
	}
};

class GCWarScheduleListHandler {
public :
	static void execute(GCWarScheduleList* pPacket, Player* pPlayer) ;
};

#endif // __GC_WAR_SCHEDULE_LIST_H__
