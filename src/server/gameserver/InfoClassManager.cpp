//--------------------------------------------------------------------
//
// Filename    : InfoClassManager.cpp
// Written By  : Elca
//
//--------------------------------------------------------------------

// include files
#include "InfoClassManager.h"
#include "ItemInfo.h"
#include "VariableManager.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
InfoClassManager::InfoClassManager () 
	throw()
: m_InfoCount(0), m_pItemInfos(NULL), m_TotalRatio(0), m_AveragePrice(0)
{
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
InfoClassManager::~InfoClassManager() 
	throw()
{
	if (m_pItemInfos != NULL) 
	{
		for (uint i = 0 ; i <= m_InfoCount ; i ++) 
			SAFE_DELETE(m_pItemInfos[i]);

		SAFE_DELETE_ARRAY(m_pItemInfos);
	}
}


//--------------------------------------------------------------------------------
// init
//--------------------------------------------------------------------------------
void InfoClassManager::init () 
	throw(Error)
{
	__BEGIN_TRY

	load();

	//Assert(m_InfoCount>0);

	m_TotalRatio = 0;
	m_AveragePrice = 0;
	int count = 0;

	for (uint i=0; i<=m_InfoCount; i++)
	{
		Ratio_t itemRatio = m_pItemInfos[i]->getRatio();

		if (itemRatio > 0)
		{
			// item type들의 total ratio를 구한다.
			m_TotalRatio += itemRatio;

			// 가격 총합
			m_AveragePrice += m_pItemInfos[i]->getPrice();

			count ++;
		}
	}

	// 가격 평균
	if (count > 1)
	{
		m_AveragePrice /= count;
	}

	Assert(m_pItemInfos[0]!=NULL);

	// 가격 증가치
	m_AveragePrice /= 1000;
	m_AveragePrice *= 100;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// reload item infos
//--------------------------------------------------------------------------------
void InfoClassManager::reload()
	throw(Error )
{
	__BEGIN_TRY

	removeAllItemInfo();

	init();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// add item info
//--------------------------------------------------------------------------------
void InfoClassManager::addItemInfo (ItemInfo* pItemInfo) 
	throw(DuplicatedException , Error)
{
	__BEGIN_TRY

	Assert(pItemInfo != NULL);
	Assert(pItemInfo->getItemType() < Item::ITEM_CLASS_MAX);
	Assert(m_pItemInfos[pItemInfo->getItemType()] == NULL);

	m_pItemInfos[pItemInfo->getItemType()] = pItemInfo;
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get item info
//--------------------------------------------------------------------------------
ItemInfo* InfoClassManager::getItemInfo (ItemType_t itemType) const 
	throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	//Assert(itemType < Item::ITEM_CLASS_MAX);
	Assert(m_pItemInfos[itemType] != NULL);

	return m_pItemInfos[itemType];
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// remove all item infos
//--------------------------------------------------------------------------------
void InfoClassManager::removeAllItemInfo()
	throw(Error )
{
	__BEGIN_TRY

	if (m_pItemInfos != NULL )
	{
		for (uint i = 0; i <= m_InfoCount ; i++ )
			SAFE_DELETE(m_pItemInfos[i]);
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get Random ItemType
//--------------------------------------------------------------------------------
ItemType_t  InfoClassManager::getRandomItemType() const
	throw(Error)
{
	__BEGIN_TRY

	// DB에 잘못 들어가있을수도 있으므로 확인해봐야한다.
	if (m_TotalRatio==0 || m_InfoCount==0)
		return 0;

	int gambleRatio 	= g_pVariableManager->getGambleItemTypeRatio();	// 200%
	int failRatio 		= m_pItemInfos[0]->getRatio();	// 0번 아이템의 확률이 실패할 확률이다.
	int succeedRatio 	= m_TotalRatio - failRatio;		// 0번 아이템을 제외한게 성공할 확률이다.
	int newTotalRatio 	= failRatio + getPercentValue(succeedRatio, gambleRatio);	// 실패 + 성공*gambleRatio
	int itemTypeRatio 	= rand()%newTotalRatio;
	int ratio;
	int ratioSum      = 0;

	// 0번은 실패로 보고..
	for (uint i=0; i<=m_InfoCount; i++)
	{
		ItemInfo* pInfo = m_pItemInfos[i];
		ratio = pInfo->getRatio();

		// 0이 아닌 경우에만 gambleRatio를 적용한다.
		// 0은 실패아이템으로 보고.. 나머지만 확률을 증가시킨다.
		if (i!=0)
			ratio = getPercentValue(ratio, gambleRatio);

		ratioSum += ratio;

		if (itemTypeRatio < ratioSum) {
			// i번째 type을 선택한다. 아마 pInfo->getItemType()==i 이겠지만..
			return pInfo->getItemType();
		}
	}

	// 이럴 수 있을까?  -_-;
	// getPercentValue에 따라서... 전체와 각각할때 오차가 있을 수 있으므로 가능하다.
	return 0;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// toString for debug
//--------------------------------------------------------------------------------
string InfoClassManager::toString() const 
	throw()
{
	StringStream msg;

	msg << "InfoClassManager(";

	for (uint i = 0 ; i <= m_InfoCount ; i ++)
		msg << m_pItemInfos[i]->toString();

	msg << ")";

	return msg.toString();
}
