////////////////////////////////////////////////////////////////////////////////
// Filename    : DynamicZoneFactoryManager.cpp 
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneFactoryManager.h"
#include "DynamicZoneInfo.h"
#include "Assert1.h"
#include "StringStream.h"

#include "DynamicZoneGateOfAlter.h"
#include "DynamicZoneAlterOfBlood.h"
#include "DynamicZoneSlayerMirrorOfAbyss.h"
#include "DynamicZoneVampireMirrorOfAbyss.h"
#include "DynamicZoneOustersMirrorOfAbyss.h"

////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
DynamicZoneFactoryManager::DynamicZoneFactoryManager() 
: m_Factories(NULL) , m_Size(DYNAMIC_ZONE_MAX)
{
	Assert(m_Size > 0);
	
	// 컨디션팩토리배열을 생성한다.
	m_Factories = new DynamicZoneFactory*[m_Size];
	
	// 팩토리에 대한 포인터들을 NULL 로 초기화한다.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
}

	
////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
DynamicZoneFactoryManager::~DynamicZoneFactoryManager() 
{
	Assert(m_Factories != NULL);

	// 각각의 컨디션팩토리들을 삭제한다.
	for (int i = 0 ; i < m_Size ; i ++ )
	{
		if (m_Factories[i] != NULL )
		{
			delete m_Factories[i];
			m_Factories[i] = NULL;
		}
	}
	
	// 컨디션팩토리배열을 삭제한다.
	delete [] m_Factories;
	m_Factories = NULL;
}


////////////////////////////////////////////////////////////////////////////////
// 정의된 모든 컨디션팩토리들을 여기에 추가한다.
////////////////////////////////////////////////////////////////////////////////
void DynamicZoneFactoryManager::init()
{
	addFactory(new DynamicZoneGateOfAlterFactory());
	addFactory(new DynamicZoneAlterOfBloodFactory());
	addFactory(new DynamicZoneSlayerMirrorOfAbyssFactory());
	addFactory(new DynamicZoneVampireMirrorOfAbyssFactory());
	addFactory(new DynamicZoneOustersMirrorOfAbyssFactory());
}


////////////////////////////////////////////////////////////////////////////////
// add dynamiczone factory to factories array
////////////////////////////////////////////////////////////////////////////////
void DynamicZoneFactoryManager::addFactory(DynamicZoneFactory * pFactory ) 
{
	Assert(pFactory != NULL);

	if (m_Factories[pFactory->getDynamicZoneType()] != NULL )
	{
		StringStream msg;
		msg << "duplicate DynamicZone factories, " << pFactory->getDynamicZoneName() ;
		cout << msg.toString() << endl;
		Assert(false);
	}
	
	// 컨디션팩토리를 등록한다.
	m_Factories[pFactory->getDynamicZoneType()] = pFactory;
}

	
////////////////////////////////////////////////////////////////////////////////
// create dynamiczone object with dynamiczone type
////////////////////////////////////////////////////////////////////////////////
DynamicZone* DynamicZoneFactoryManager::createDynamicZone(int dynamicZoneType ) const
{
	if (dynamicZoneType >= m_Size || m_Factories[dynamicZoneType] == NULL ) 
	{
		StringStream msg;
		msg << "dynamiczone factory [" << dynamicZoneType << "] not exist.";
		cout << msg.toString() << endl;
		Assert(false);
	}

	return m_Factories[dynamicZoneType]->createDynamicZone();
}


////////////////////////////////////////////////////////////////////////////////
// get dynamiczone name with dynamiczone type
////////////////////////////////////////////////////////////////////////////////
string DynamicZoneFactoryManager::getDynamicZoneName(int dynamicZoneType ) const
{
	// 타입이 범위를 넘어섬으로 인해서 Seg.Fault 가 발생하지 않도록.
	// 이런 사용자는 당장 짤라야 한다.
	if (dynamicZoneType >= m_Size || m_Factories[dynamicZoneType] == NULL ) 
	{
		StringStream msg;
		msg << "invalid dynamiczone type (" << dynamicZoneType << ")";
		cout << msg.toString() << endl;
		Assert(false);
	}

	return m_Factories[dynamicZoneType]->getDynamicZoneName();
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int DynamicZoneFactoryManager::getDynamicZoneType(const string& dynamicZoneName ) const
{
	for (int i = 0 ; i < m_Size ; i++ )
	{
		if (m_Factories[i] != NULL )
		{
			if (m_Factories[i]->getDynamicZoneName() == dynamicZoneName )
			{
				return i;
			}
		}
	}

	string msg = "no such dynamiczone type : " + dynamicZoneName;
	cout << msg << endl;
	Assert(false);

	return DYNAMIC_ZONE_MAX;
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string DynamicZoneFactoryManager::toString() const
{
	StringStream msg;

	msg << "DynamicZoneFactoryManager(\n";

	for (int i = 0 ; i < m_Size ; i++ )
	{
		msg << "DynamicZoneFactories[" << i << "] == ";
		msg << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getDynamicZoneName()) ;
		msg << "\n";
	}

	msg << ")";

	return msg.toString();
}

// global variable declaration
DynamicZoneFactoryManager * g_pDynamicZoneFactoryManager = NULL;

