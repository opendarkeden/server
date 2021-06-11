//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTypeStringList.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TYPE_STRING_LIST_H__
#define __CG_TYPE_STRING_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"

#include <list>

#define MAX_STRING_LENGTH 50
#define MAX_STRING_NUM 20

//////////////////////////////////////////////////////////////////////////////
// class CGTypeStringList;
//////////////////////////////////////////////////////////////////////////////

class CGTypeStringList : public Packet 
{
public:
	enum StringType
	{
		STRING_TYPE_WAIT_FOR_MEET,
		STRING_TYPE_WAIT_FOR_APART,
		STRING_TYPE_FORCE_APART_COUPLE
	};
public:
	CGTypeStringList() ;
	~CGTypeStringList() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_TYPE_STRING_LIST; }
	PacketSize_t getPacketSize() const 
	{
		PacketSize_t ret = szBYTE;

		ret+=szBYTE;

		list<string>::const_iterator itr = m_StringList.begin();
		for(; itr != m_StringList.end(); ++itr )
		{
			ret += szBYTE + (*itr).size();
		}
		ret += szDWORD;

		return ret; 
	}
	string getPacketName() const  { return "CGTypeStringList"; }
	string toString() const ;
	
public:
	void	setType(StringType type ) { m_StringType = type; }
	BYTE	getType() const { return m_StringType; }

	void	addString(string str ) { m_StringList.push_back(str); }
	void	clearString() { m_StringList.clear(); }
	int		getSize() const { return m_StringList.size(); }
	string	popString() { string ret = m_StringList.front(); m_StringList.pop_front(); return ret; }

	void	setParam(DWORD param ) { m_Param = param; }
	DWORD	getParam() const		{ return m_Param; }

private:
	BYTE			m_StringType;
	list<string>	m_StringList;
	DWORD			m_Param;
};

//////////////////////////////////////////////////////////////////////////////
// class CGTypeStringListFactory;
//////////////////////////////////////////////////////////////////////////////

class CGTypeStringListFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGTypeStringList(); }
	string getPacketName() const  { return "CGTypeStringList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_TYPE_STRING_LIST; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szBYTE + (szBYTE + MAX_STRING_LENGTH ) * MAX_STRING_NUM + szDWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGTypeStringListHandler;
//////////////////////////////////////////////////////////////////////////////

class CGTypeStringListHandler 
{
public:
	static void execute(CGTypeStringList* pPacket, Player* player) ;

private:
	static void executeWaitForMeet(CGTypeStringList* pPacket, Player* player) ;
	static void executeWaitForApart(CGTypeStringList* pPacket, Player* player) ;
	static void	executeApartForce(CGTypeStringList* pPacket, Player* pPlayer ) ;
};

#endif
