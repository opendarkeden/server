//////////////////////////////////////////////////////////////////////////////
// Filename    : CoupleRingBase.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __COUPLE_RING_BASE_H__
#define __COUPLE_RING_BASE_H__

#include "Item.h"

class ItemInfo;

//////////////////////////////////////////////////////////////////////////////
// class CoupleRingBase;
//////////////////////////////////////////////////////////////////////////////
class CoupleRingBase : public Item 
{
public:
	CoupleRingBase() throw();
	virtual ~CoupleRingBase() {}
	
public:
	string 	getName() const { return m_Name; }
	void 	setName( string name ) { m_Name = name; }

	ItemID_t 	getPartnerItemID() const { return m_PartnerItemID; }
	void 		setPartnerItemID( ItemID_t partnerItemID ) throw(Error);

public:
	virtual bool	hasPartnerItem() throw(Error) = 0;

public:
	static ItemInfo*	getItemInfo( ItemType_t itemType, Race_t race ) throw(Error);

private:
	string		 		m_Name;
	ItemID_t			m_PartnerItemID;
};

#endif
