////////////////////////////////////////////////////////////////////////////////
// Filename    : VolumeInfo.h
// Written By  : Elca
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VOLUMEINFO_H__
#define __VOLUMEINFO_H__

#include "Types.h"

#define MAX_VOLUME_TYPE	7

////////////////////////////////////////////////////////////////////////////////
// Class VolumeInfo
////////////////////////////////////////////////////////////////////////////////

class VolumeInfo 
{
public:
	VolumeInfo(VolumeType_t volumeType, VolumeWidth_t volumeWidth, VolumeHeight_t volumeHeight) ;
	~VolumeInfo() ;

public:
	// get/set volume width
	VolumeWidth_t getVolumeWidth() const  { return m_VolumeWidth; }
	void setVolumeWidth(VolumeWidth_t volumeWidth)  { m_VolumeWidth = volumeWidth; }

	// get/set volume height
	VolumeHeight_t getVolumeHeight() const  { return m_VolumeHeight; }
	void setVolumeHeight(VolumeHeight_t volumeHeight)  { m_VolumeHeight = volumeHeight; }

	// get debug string
	string toString() ;

private:
	VolumeType_t   m_VolumeType;
	VolumeWidth_t  m_VolumeWidth;
	VolumeHeight_t m_VolumeHeight;

};


////////////////////////////////////////////////////////////////////////////////
// Class VolumeInfoManager
////////////////////////////////////////////////////////////////////////////////

class VolumeInfoManager 
{
public:
	VolumeInfoManager() ;
	~VolumeInfoManager() ;
	
public:
	void init() ;
	VolumeInfo* getVolumeInfo(VolumeType_t VolumeType) const  { return m_VolumeInfo[VolumeType]; }
	string toString() ;

private:
	VolumeInfo* m_VolumeInfo[MAX_VOLUME_TYPE];

};

extern VolumeInfoManager* g_pVolumeInfoManager;

#endif	// __VOLUME_INFO_MANAGER_H__
