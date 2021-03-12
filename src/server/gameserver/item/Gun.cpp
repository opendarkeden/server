//////////////////////////////////////////////////////////////////////////////
// Filename    : Gun.cpp
// Written By  : Sigi
// Description :
//////////////////////////////////////////////////////////////////////////////

// include files
#include "Gun.h"
#include "ItemUtil.h"

#include "PCItemInfo.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Gun::Gun()
	
{
	m_ItemType    = 0;
	m_Durability  = 0;
	m_EnchantLevel = 0;
	m_BulletCount = 0;
	m_BonusDamage = 0;
	m_Silver      = 0;
}

Gun::Gun(ItemType_t itemType, const list<OptionType_t>& optionType)
	
: m_OptionType( optionType )
{
	m_ItemType    = itemType;
	m_BulletCount = 0;
	m_BonusDamage = 0;
	m_Silver      = 0;

	m_EnchantLevel = 0;
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
Gun::~Gun()
	
{
}

void Gun::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);
	result.setItemNum( getBulletCount() );
}
