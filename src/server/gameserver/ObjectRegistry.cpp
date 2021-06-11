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
	  
{ 
	m_ObjectIDKey = 10000;
	m_Mutex.setName("ObjectRegistry"); 
}

void ObjectRegistry::registerObject(Object* pObject) 
	 
{ 
	__ENTER_CRITICAL_SECTION(m_Mutex);		

	pObject->setObjectID(++m_ObjectIDKey);

	__LEAVE_CRITICAL_SECTION(m_Mutex);		
}

void ObjectRegistry::registerObject_NOLOCKED(Object* pObject) 
	
{
	pObject->setObjectID(++m_ObjectIDKey);
}

void ObjectRegistry::lock() 
	 
{ 
	m_Mutex.lock(); 
}

void ObjectRegistry::unlock() 
	 
{ 
	m_Mutex.unlock(); 
}


	
