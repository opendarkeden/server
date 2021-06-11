//////////////////////////////////////////////////////////////////////////////
// Filename    : Sector.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Sector.h"
#include "Object.h"

//////////////////////////////////////////////////////////////////////////////
// class Sector member methods
//////////////////////////////////////////////////////////////////////////////

Sector::Sector() 
	
{
	__BEGIN_TRY

	for (int i=0; i<8; i++)
		m_pNearbySectors[i] = NULL;

	__END_CATCH
}

Sector::~Sector() 
	
{
	__BEGIN_TRY

	m_Objects.clear();

	__END_CATCH
}

void Sector::addObject(Object* pObject) 
	
{
	__BEGIN_TRY

	Assert(pObject != NULL);

	unordered_map<ObjectID_t, Object*>::iterator itr = m_Objects.find(pObject->getObjectID());
	if (itr != m_Objects.end())
	{
		cerr << "Sector::addObjectID() : DuplicatedException" << endl;
		throw DuplicatedException();
	}

	m_Objects[pObject->getObjectID()] = pObject;

	__END_CATCH
}

void Sector::deleteObject(ObjectID_t id) 
	
{
	__BEGIN_TRY

	unordered_map<ObjectID_t, Object*>::iterator itr = m_Objects.find(id);
	if (itr == m_Objects.end())
	{
		cerr << "Sector::deleteObjectID() : NoSuchElementException" << endl;
		throw NoSuchElementException();
	}

	m_Objects.erase(itr);

	__END_CATCH
}

Object* Sector::getObject(ObjectID_t id) 
	
{
	__BEGIN_TRY

	unordered_map<ObjectID_t, Object*>::iterator itr = m_Objects.find(id);
	if (itr == m_Objects.end())
	{
		cerr << "Sector::getObjectID() : NoSuchElementException" << endl;
		throw NoSuchElementException();
	}

	return itr->second;

	__END_CATCH
}

Sector* Sector::getNearbySector(uint dir) 
	
{
	__BEGIN_TRY

	Assert(dir <= DIR_MAX);
	return m_pNearbySectors[dir];

	__END_CATCH
}

void Sector::setNearbySector(uint dir, Sector* pSector) 
	
{
	__BEGIN_TRY

	Assert(dir <= DIR_MAX);
	m_pNearbySectors[dir] = pSector;

	__END_CATCH
}

string Sector::toString(void) const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "Sector("
		<< "Size:" << (int)m_Objects.size() << ",";

	unordered_map<ObjectID_t, Object*>::const_iterator itr = m_Objects.begin();
	for (; itr != m_Objects.end(); itr++)
	{
		msg << itr->second->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

