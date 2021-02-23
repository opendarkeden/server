/////////////////////////////////////////////////////////////////////////////
// DynamicZoneGroup.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_GROUP_H__
#define __DYNAMIC_ZONE_GROUP_H__

#include "Types.h"
#include <hash_map>

// forward declaration
class DynamicZone;

///////////////////////////////////////////////////////////
// class DynamicZoneGroup
///////////////////////////////////////////////////////////
class DynamicZoneGroup
{
public:
	typedef hash_map<ZoneID_t,DynamicZone*>		HashMapDynamicZone;
	typedef HashMapDynamicZone::iterator		HashMapDynamicZoneItor;
	typedef HashMapDynamicZone::const_iterator	HashMapDynamicZoneConstItor;

public:
	DynamicZoneGroup();
	~DynamicZoneGroup();

public:
	void clear();

public:
	int getDynamicZoneType() const { return m_DynamicZoneType; }
	void setDynamicZoneType( int dynamicZoneType ) { m_DynamicZoneType = dynamicZoneType; }

	ZoneID_t getTemplateZoneID() const { return m_TemplateZoneID; }
	void setTemplateZoneID( ZoneID_t templateZoneID ) { m_TemplateZoneID = templateZoneID; }

	bool canEnter();
	DynamicZone* getAvailableDynamicZone();

protected:
	void addDynamicZone( DynamicZone* pDynamicZone );
	uint getSize() { return m_DynamicZones.size(); }

private:
	int					m_DynamicZoneType;
	ZoneID_t			m_TemplateZoneID;	// 틀이 되는 존의 ID
	HashMapDynamicZone	m_DynamicZones;
	uint				m_MaxSize;
};

#endif

