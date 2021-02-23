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
	VolumeInfo(VolumeType_t volumeType, VolumeWidth_t volumeWidth, VolumeHeight_t volumeHeight) throw();
	~VolumeInfo() throw();

public:
	// get/set volume width
	VolumeWidth_t getVolumeWidth() const throw() { return m_VolumeWidth; }
	void setVolumeWidth(VolumeWidth_t volumeWidth) throw() { m_VolumeWidth = volumeWidth; }

	// get/set volume height
	VolumeHeight_t getVolumeHeight() const throw() { return m_VolumeHeight; }
	void setVolumeHeight(VolumeHeight_t volumeHeight) throw() { m_VolumeHeight = volumeHeight; }

	// get debug string
	string toString() throw();

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
	VolumeInfoManager() throw();
	~VolumeInfoManager() throw();
	
public:
	void init() throw();
	VolumeInfo* getVolumeInfo(VolumeType_t VolumeType) const throw() { return m_VolumeInfo[VolumeType]; }
	string toString() throw();

private:
	VolumeInfo* m_VolumeInfo[MAX_VOLUME_TYPE];

};

extern VolumeInfoManager* g_pVolumeInfoManager;

#endif	// __VOLUME_INFO_MANAGER_H__
