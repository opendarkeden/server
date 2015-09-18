/////////////////////////////////////////////////////////////////////////////
// DynamicZoneInfo.cpp
/////////////////////////////////////////////////////////////////////////////

// include files
#include "DynamicZoneInfo.h"
#include "Assert1.h"

///////////////////////////////////////////////////////////
// class DynamicZoneInfo
///////////////////////////////////////////////////////////
DynamicZoneInfo::DynamicZoneInfo()
{
	m_DynamicZoneType = DYNAMIC_ZONE_MAX;
	m_TemplateZoneID = 0;
}

DynamicZoneInfo::~DynamicZoneInfo()
{
}

// global variable
DynamicZoneInfoManager* g_pDynamicZoneInfoManager = NULL;

///////////////////////////////////////////////////////////
// class DynamicZoneInfoManager
///////////////////////////////////////////////////////////
DynamicZoneInfoManager::DynamicZoneInfoManager()
{
}

DynamicZoneInfoManager::~DynamicZoneInfoManager()
{
	clear();
}

void DynamicZoneInfoManager::init()
{
	// 제단 입구 존 추가
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType(DYNAMIC_ZONE_GATE_OF_ALTER);
		pDynamicZoneInfo->setTemplateZoneID(4001);

		addDynamicZoneInfo(pDynamicZoneInfo);
	}

	// 피의 제단 존 추가
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType(DYNAMIC_ZONE_ALTER_OF_BLOOD);
		pDynamicZoneInfo->setTemplateZoneID(4002);

		addDynamicZoneInfo(pDynamicZoneInfo);
	}

	// 슬레이어 심연의 거울 존 추가
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType(DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS);
		pDynamicZoneInfo->setTemplateZoneID(4003);

		addDynamicZoneInfo(pDynamicZoneInfo);
	}

	// 뱀파이어 심연의 거울 존 추가
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType(DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS);
		pDynamicZoneInfo->setTemplateZoneID(4004);

		addDynamicZoneInfo(pDynamicZoneInfo);
	}

	// 아우스터즈 심연의 거울 존 추가
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType(DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS);
		pDynamicZoneInfo->setTemplateZoneID(4005);

		addDynamicZoneInfo(pDynamicZoneInfo);
	}
}

void DynamicZoneInfoManager::clear()
{
	HashMapDynamicZoneInfoItor itr = m_DynamicZoneInfos.begin();
	HashMapDynamicZoneInfoItor endItr = m_DynamicZoneInfos.end();

	for (; itr != endItr; ++itr )
	{
		SAFE_DELETE(itr->second);
	}

	m_DynamicZoneInfos.clear();
}

void DynamicZoneInfoManager::addDynamicZoneInfo(DynamicZoneInfo* pDynamicZoneInfo )
{
	Assert(pDynamicZoneInfo != NULL);

	HashMapDynamicZoneInfoConstItor itr = m_DynamicZoneInfos.find(pDynamicZoneInfo->getDynamicZoneType());

	if (itr != m_DynamicZoneInfos.end() )
	{
		cerr << "Duplicated DynamicZoneInfo" << endl;
		Assert(false);
	}

	m_DynamicZoneInfos[ pDynamicZoneInfo->getDynamicZoneType() ] = pDynamicZoneInfo;

	HashMapDynamicZoneTypeConstItor itr2 = m_DynamicZoneTypes.find(pDynamicZoneInfo->getTemplateZoneID());

	if (itr2 != m_DynamicZoneTypes.end() )
	{
		cerr << "Duplicated DynamicZoneInfo" << endl;
		Assert(false);
	}

	m_DynamicZoneTypes[ pDynamicZoneInfo->getTemplateZoneID() ] = pDynamicZoneInfo->getDynamicZoneType();
}

DynamicZoneInfo* DynamicZoneInfoManager::getDynamicZoneInfo(int DynamicZoneType ) const
{
	HashMapDynamicZoneInfoConstItor itr = m_DynamicZoneInfos.find(DynamicZoneType);

	if (itr == m_DynamicZoneInfos.end() )
	{
		cerr << "No such element given DynamicZoneType" << endl;
		return NULL;
	}

	return itr->second;
}

int DynamicZoneInfoManager::getDynamicZoneTypeByZoneID(ZoneID_t zoneID ) const
{
	HashMapDynamicZoneTypeConstItor itr = m_DynamicZoneTypes.find(zoneID);

	if (itr == m_DynamicZoneTypes.end() )
	{
		cerr << "No such element given ZoneID" << endl;
		return DYNAMIC_ZONE_MAX;
	}

	return itr->second;
}

