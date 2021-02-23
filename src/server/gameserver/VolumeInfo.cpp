////////////////////////////////////////////////////////////////////////////////
// Filename    : VolumeInfoManager.cpp
// Written By  : elca@mail.metrotech.co.kr
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "VolumeInfo.h"
#include "Exception.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declaration
////////////////////////////////////////////////////////////////////////////////
VolumeInfoManager* g_pVolumeInfoManager = NULL;

////////////////////////////////////////////////////////////////////////////////
// class VolumeInfo member methods
////////////////////////////////////////////////////////////////////////////////

VolumeInfo::VolumeInfo(VolumeType_t type, VolumeWidth_t width, VolumeHeight_t height)
	throw()
{
	__BEGIN_TRY

	m_VolumeType   = type;
	m_VolumeWidth  = width;
	m_VolumeHeight = height;

	__END_CATCH
}

VolumeInfo::~VolumeInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string VolumeInfo::toString()
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "VolumeInfo(" 
		<< "TYPE:" << (int)m_VolumeType
		<< "WIDTH:" << (int)m_VolumeWidth
		<< "HEIGHT:" << (int)m_VolumeHeight
		<< ")";
	return msg.toString();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class VolumeInfoManager member methods
////////////////////////////////////////////////////////////////////////////////
VolumeInfoManager::VolumeInfoManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

VolumeInfoManager::~VolumeInfoManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void VolumeInfoManager::init()
	throw()
{
	__BEGIN_TRY

	// initialize VolumeInfoManager
	m_VolumeInfo[0] = new VolumeInfo(0, 0, 0);
	m_VolumeInfo[1] = new VolumeInfo(1, 1, 1);
	m_VolumeInfo[2] = new VolumeInfo(2, 1, 2);
	m_VolumeInfo[3] = new VolumeInfo(3, 1, 3);
	m_VolumeInfo[4] = new VolumeInfo(4, 2, 1);
	m_VolumeInfo[5] = new VolumeInfo(5, 2, 2);
	m_VolumeInfo[6] = new VolumeInfo(6, 2, 3);

	__END_CATCH
}

string VolumeInfoManager::toString() 
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "VolumeInfoManager (";
	for(int i = 0; i < MAX_VOLUME_TYPE; i++) 
	{
		msg << m_VolumeInfo[i]->toString();
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}

