//////////////////////////////////////////////////////////////////////////////
// Filename    : ObjectRegistry.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ObjectRegistry.h"

ObjectRegistry* g_pObjectRegistry = NULL;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ObjectRegistry::ObjectRegistry()
	throw()  
{ 
	m_ObjectIDKey = 10000;
	m_Mutex.setName("ObjectRegistry"); 
}

void ObjectRegistry::registerObject(Object* pObject) 
	throw() 
{ 
	__ENTER_CRITICAL_SECTION(m_Mutex);		

	pObject->setObjectID(++m_ObjectIDKey);

	__LEAVE_CRITICAL_SECTION(m_Mutex);		
}

void ObjectRegistry::registerObject_NOLOCKED(Object* pObject) 
	throw()
{
	pObject->setObjectID(++m_ObjectIDKey);
}

void ObjectRegistry::lock() 
	throw(Error) 
{ 
	m_Mutex.lock(); 
}

void ObjectRegistry::unlock() 
	throw(Error) 
{ 
	m_Mutex.unlock(); 
}


	
