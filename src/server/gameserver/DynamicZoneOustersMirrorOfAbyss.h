/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS_H__
#define __DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneOustersMirrorOfAbyss
///////////////////////////////////////////////////////////
class DynamicZoneOustersMirrorOfAbyss : public DynamicZone
{
public:
	DynamicZoneOustersMirrorOfAbyss();
	virtual ~DynamicZoneOustersMirrorOfAbyss();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkMono();

	void processEntering();
	void killPC();

private:
	int m_OMOAStatus;
	ObjectID_t m_MonoObjectID;
	Timeval m_EndTime;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneOustersMirrorOfAbyss )

#endif

