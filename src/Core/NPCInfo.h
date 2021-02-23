//////////////////////////////////////////////////////////////////////////////
// Filename    : NPCInfo.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __NPCINFO_H__
#define __NPCINFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////////////
// class NPCInfo
//////////////////////////////////////////////////////////////////////////////

class NPCInfo
{

///// member methods /////

public:
	NPCInfo();
	~NPCInfo();

public:
	string getName(void) const { return m_Name; }
	void setName(string name) { m_Name = name; }

	NPCID_t getNPCID(void) const { return m_NPCID; }
	void setNPCID(NPCID_t id) { m_NPCID = id; }

	ZoneCoord_t getX(void) const { return m_X; }
	void setX(ZoneCoord_t x) { m_X = x; }

	ZoneCoord_t getY(void) const { return m_Y; }
	void setY(ZoneCoord_t y) { m_Y = y; }

	uint getSize(void) 
	{ 
		return szBYTE + 
			m_Name.size() + 
			szNPCID + 
			szZoneCoord + szZoneCoord; 
	}
	
	void read(SocketInputStream& iStream) throw (ProtocolException, Error);
	void write(SocketOutputStream& oStream) const throw (ProtocolException, Error);

	static uint getMaxSize(void) { return szBYTE + 30 + szNPCID + szZoneCoord + szZoneCoord; }

	string toString(void) const throw();

///// member data /////

protected:
	string      m_Name;
	NPCID_t     m_NPCID;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
};


#endif
