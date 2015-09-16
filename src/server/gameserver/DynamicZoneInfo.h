/////////////////////////////////////////////////////////////////////////////
// Dynamic Zone Info
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_INFO__
#define __DYNAMIC_ZONE_INFO__

#include "Types.h"
#include <map>

enum DYNAMIC_ZONE_TYPE
{
	DYNAMIC_ZONE_GATE_OF_ALTER = 0,
	DYNAMIC_ZONE_ALTER_OF_BLOOD,
	DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS,
	DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS,
	DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS,

	DYNAMIC_ZONE_MAX
};

///////////////////////////////////////////////////////////
// class DynamicZoneInfo
///////////////////////////////////////////////////////////
class DynamicZoneInfo
{
public:
	DynamicZoneInfo();
	~DynamicZoneInfo();

public:
	// get / set methods
	int getDynamicZoneType() const { return m_DynamicZoneType; }
	void setDynamicZoneType(int dynamicZoneType ) { m_DynamicZoneType = dynamicZoneType; }

	ZoneID_t getTemplateZoneID() const { return m_TemplateZoneID; }
	void setTemplateZoneID(ZoneID_t templateZoneID ) { m_TemplateZoneID = templateZoneID; }

private:
	int			m_DynamicZoneType;		// DynamicZoneType
	ZoneID_t	m_TemplateZoneID;		// 다이나믹 존의 틀이되는 존 ID
};


///////////////////////////////////////////////////////////
// class DynamicZoneInfoManager
///////////////////////////////////////////////////////////
class DynamicZoneInfoManager
{
public:
	typedef map<int,DynamicZoneInfo*>			HashMapDynamicZoneInfo;
	typedef HashMapDynamicZoneInfo::iterator		HashMapDynamicZoneInfoItor;
	typedef HashMapDynamicZoneInfo::const_iterator	HashMapDynamicZoneInfoConstItor;

	typedef map<ZoneID_t,int>					HashMapDynamicZoneType;
	typedef HashMapDynamicZoneType::iterator		HashMapDynamicZoneTypeItor;
	typedef HashMapDynamicZoneType::const_iterator	HashMapDynamicZoneTypeConstItor;

public:
	DynamicZoneInfoManager();
	~DynamicZoneInfoManager();

public:
	void init();
	void clear();
	void addDynamicZoneInfo(DynamicZoneInfo* pDynamicZoneInfo);
	DynamicZoneInfo* getDynamicZoneInfo(int DynamicZoneType ) const;

	int getDynamicZoneTypeByZoneID(ZoneID_t zoneID ) const;

private:
	HashMapDynamicZoneInfo	m_DynamicZoneInfos;
	HashMapDynamicZoneType	m_DynamicZoneTypes;
};

// global variable
extern DynamicZoneInfoManager* g_pDynamicZoneInfoManager;

#endif

