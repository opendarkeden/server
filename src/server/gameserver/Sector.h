//////////////////////////////////////////////////////////////////////////////
// Filename    : Sector.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SECTOR_H__
#define __SECTOR_H__

#include "Types.h"
#include "Exception.h"
#include <unordered_map>

const int SECTOR_SIZE = 13;

//////////////////////////////////////////////////////////////////////////////
// class Sector
//////////////////////////////////////////////////////////////////////////////

class Object;

class Sector
{
public:
	Sector() ;
	~Sector() ;

public:
	void addObject(Object* pObject) ;
	void deleteObject(ObjectID_t id) ;
	Object* getObject(ObjectID_t id) ;

	Sector* getNearbySector(uint dir) ;
	void setNearbySector(uint dir, Sector* pSector) ;

	const unordered_map<ObjectID_t, Object*>& getObjects(void) const { return m_Objects; }
	uint getSize(void) const  { return m_Objects.size(); }

	string toString(void) const ;

protected:
	unordered_map<ObjectID_t, Object*> m_Objects;
	Sector* m_pNearbySectors[9];
};

#endif
