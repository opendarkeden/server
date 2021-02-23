//////////////////////////////////////////////////////////////////////////////
// Filename    : PacketProfile.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PacketProfile.h"
#include "VSDateTime.h"
#include <fstream>
#include <iomanip.h>
#include <stdio.h>

PacketProfileManager g_PacketProfileManager;

//////////////////////////////////////////////////////////////////////////////
// class PacketProfileManager
//////////////////////////////////////////////////////////////////////////////

PacketProfileManager::PacketProfileManager()
{
}

PacketProfileManager::~PacketProfileManager()
{
}

void PacketProfileManager::init(void)
{
	hash_map<string, PacketProfile*>::iterator itr = m_NameMap.begin();
	for (; itr != m_NameMap.end(); itr++)
	{
		PacketProfile* pProfile = itr->second;
		pProfile->CallCount = 0;
		pProfile->AccuTime.tv_sec = 0;
		pProfile->AccuTime.tv_usec = 0;
	}
}

void PacketProfileManager::addAccuTime(const string& PacketName, const Timeval& start, const Timeval& end)
{
	PacketProfile* pProfile = NULL;

	hash_map<string, PacketProfile*>::iterator itr = m_NameMap.find(PacketName);
	if (itr != m_NameMap.end())
	{
		pProfile = itr->second;
	}
	else
	{
		pProfile = new PacketProfile;
		pProfile->PacketName = PacketName;
		m_NameMap[PacketName] = pProfile;
	}

	Timeval offset = timediff(start, end);
	pProfile->AccuTime = pProfile->AccuTime + offset;
	pProfile->CallCount += 1;
}

void PacketProfileManager::outputResultToFile(const string& filename)
{
	ofstream file(filename.c_str(), ios::out | ios::app);
	if (!file) return;

	file << VSDateTime::currentDateTime().toString() << endl;
	file << setiosflags(ios::left)
		 << setw(20) << "AvgTime" 
		 << setw(20) << "AccuTime"
		 << setw(10) << "CallCount"
		 << setw(30) << "Name"
		 << endl;

	hash_map<string, PacketProfile*>::iterator itr = m_NameMap.begin();
	for (; itr != m_NameMap.end(); itr++)
	{
		PacketProfile* pProfile = itr->second;

		char buf[256] = {0, };
		sprintf(buf, "%ld.%06lds", pProfile->AccuTime.tv_sec, pProfile->AccuTime.tv_usec);

		char buf2[256] = {0, };
		double accu_time = (pProfile->AccuTime.tv_sec + (double)pProfile->AccuTime.tv_usec/1000000) / pProfile->CallCount;
		sprintf(buf2, "%5.9fs", accu_time);

		file << setiosflags(ios::left)
			<< setw(20) << string(buf2)
			<< setw(20) << string(buf)
			<< setw(10) << pProfile->CallCount
			<< setw(30) << pProfile->PacketName
			<< endl;
	}

	file << endl << endl;
}
