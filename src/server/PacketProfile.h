//////////////////////////////////////////////////////////////////////////////
// Filename    : PacketProfile.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PACKET_PROFILE_H__
#define __PACKET_PROFILE_H__

#include "Types.h"
#include "Timeval.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class PacketProfile
{
public:
	PacketProfile()
	{
		PacketName = "";
		CallCount  = 0;
		AccuTime.tv_sec = 0;
		AccuTime.tv_usec = 0;
	}

public:
	string  PacketName;
	int     CallCount;
	Timeval AccuTime;
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class PacketProfileManager
{
public:
	PacketProfileManager();
	~PacketProfileManager();

public:
	void init(void);
	void addAccuTime(const string& PacketName, const Timeval& start, const Timeval& end);
	void outputResultToFile(const string& filename);

protected:
	hash_map<string, PacketProfile*> m_NameMap;
};

extern PacketProfileManager g_PacketProfileManager;

#endif
