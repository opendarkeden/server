//////////////////////////////////////////////////////////////////////////////
// Filename    : CoupleRingBase.cpp
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CoupleRingBase.h"
#include "CoupleRing.h"
#include "VampireCoupleRing.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "StringStream.h"

//////////////////////////////////////////////////////////////////////////////
// class CoupleRingBase member methods
//////////////////////////////////////////////////////////////////////////////

CoupleRingBase::CoupleRingBase()
	
{
	m_PartnerItemID = 0;
}

void CoupleRingBase::setPartnerItemID( ItemID_t partnerItemID )
	
{
	__BEGIN_TRY

	m_PartnerItemID = partnerItemID;
	StringStream msg;
	msg << "PartnerItemID=" << (uint)partnerItemID;

	tinysave( msg.toString().c_str() );

	__END_CATCH
}

ItemInfo* CoupleRingBase::getItemInfo( ItemType_t itemType, Race_t race )
	
{
	__BEGIN_TRY

	switch( race )
	{
		case RACE_SLAYER:
			return g_pCoupleRingInfoManager->getItemInfo( itemType );
			break;
		case RACE_VAMPIRE:
			return g_pVampireCoupleRingInfoManager->getItemInfo( itemType );
			break;
		default:
			Assert(false);
	}
	
	__END_CATCH
}
