//////////////////////////////////////////////////////////////////////////////
// Filename    : InfoClassManager.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INFO_CLASS_MANAGER_H__
#define __INFO_CLASS_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class InfoClassManager;
//////////////////////////////////////////////////////////////////////////////

class ItemInfo;

struct OPTION_RATIO
{
	OptionType_t	optionType;
	int				ratioSum;
};

class InfoClassManager 
{
public:
	InfoClassManager() ;
	virtual ~InfoClassManager() ;

public:
	virtual Item::ItemClass getItemClass() const  = 0;
	
	void init() ;
	void reload() ;

	virtual void load()  = 0;

	void addItemInfo(ItemInfo* pItemInfo) ;
	ItemInfo* getItemInfo(ItemType_t ItemType) const ;
	uint getInfoCount() const  { return m_InfoCount + 1; }

	void removeAllItemInfo() ;

	// for Mysterious Item
	ItemType_t  getRandomItemType() const ;

	Price_t		getAveragePrice() const 	{ return m_AveragePrice; }


	string toString() const ;

protected:
	uint       m_InfoCount;  // #아이템정보
	ItemInfo** m_pItemInfos; // array of item info

	int        m_TotalRatio;	// item type들의 total Ratio
	Price_t	   m_AveragePrice;	// 이 item class의 모든 item 가격의 평균
};

#endif
