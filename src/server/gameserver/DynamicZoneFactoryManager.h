//////////////////////////////////////////////////////////////////////////////
// Filename    : DynamicZoneFactoryManager.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_FACTORY_MANAGER_H__
#define __DYNAMIC_ZONE_FACTORY_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "DynamicZone.h"

//////////////////////////////////////////////////////////////////////////////
// class DynamicZoneFactoryManager
//////////////////////////////////////////////////////////////////////////////

class DynamicZoneFactoryManager 
{
public:
	DynamicZoneFactoryManager();
	~DynamicZoneFactoryManager();

public:
	void init();
	void addFactory( DynamicZoneFactory* pFactory );
	DynamicZone* createDynamicZone( int dynamicZoneType ) const;
	string getDynamicZoneName( int dynamicZoneType ) const;
	int getDynamicZoneType( const string & dynamicZoneName ) const;
	string toString() const;

private:
	DynamicZoneFactory**	m_Factories;
	ushort					m_Size;

};

extern DynamicZoneFactoryManager* g_pDynamicZoneFactoryManager;

#endif
