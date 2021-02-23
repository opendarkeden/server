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
	throw()
{
	__BEGIN_TRY

	for (int i=0; i<8; i++)
		m_pNearbySectors[i] = NULL;

	__END_CATCH
}

Sector::~Sector() 
	throw()
{
	__BEGIN_TRY

	m_Objects.clear();

	__END_CATCH
}

void Sector::addObject(Object* pObject) 
	throw (DuplicatedException, Error)
{
	__BEGIN_TRY

	Assert(pObject != NULL);

	hash_map<ObjectID_t, Object*>::iterator itr = m_Objects.find(pObject->getObjectID());
	if (itr != m_Objects.end())
	{
		cerr << "Sector::addObjectID() : DuplicatedException" << endl;
		throw DuplicatedException();
	}

	m_Objects[pObject->getObjectID()] = pObject;

	__END_CATCH
}

void Sector::deleteObject(ObjectID_t id) 
	throw (NoSuchElementException, Error)
{
	__BEGIN_TRY

	hash_map<ObjectID_t, Object*>::iterator itr = m_Objects.find(id);
	if (itr == m_Objects.end())
	{
		cerr << "Sector::deleteObjectID() : NoSuchElementException" << endl;
		throw NoSuchElementException();
	}

	m_Objects.erase(itr);

	__END_CATCH
}

Object* Sector::getObject(ObjectID_t id) 
	throw (NoSuchElementException, Error)
{
	__BEGIN_TRY

	hash_map<ObjectID_t, Object*>::iterator itr = m_Objects.find(id);
	if (itr == m_Objects.end())
	{
		cerr << "Sector::getObjectID() : NoSuchElementException" << endl;
		throw NoSuchElementException();
	}

	return itr->second;

	__END_CATCH
}

Sector* Sector::getNearbySector(uint dir) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(dir <= DIR_MAX);
	return m_pNearbySectors[dir];

	__END_CATCH
}

void Sector::setNearbySector(uint dir, Sector* pSector) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(dir <= DIR_MAX);
	m_pNearbySectors[dir] = pSector;

	__END_CATCH
}

string Sector::toString(void) const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "Sector("
		<< "Size:" << (int)m_Objects.size() << ",";

	hash_map<ObjectID_t, Object*>::const_iterator itr = m_Objects.begin();
	for (; itr != m_Objects.end(); itr++)
	{
		msg << itr->second->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

