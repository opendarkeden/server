//////////////////////////////////////////////////////////////////////////////
// Filename    : ShopRack.h
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHOPRACK_H__
#define __SHOPRACK_H__

#include "Types.h"
#include "ItemRack.h"

//////////////////////////////////////////////////////////////////////////////
// class ShopRack
//////////////////////////////////////////////////////////////////////////////

class ShopRack : public ItemRack
{
public:
	ShopRack();
	virtual ~ShopRack();

public:
	ShopVersion_t getVersion(void) const throw() { return m_Version; }
	void setVersion(const ShopVersion_t ver) throw() { m_Version = ver; }
	void increaseVersion(void) throw() { m_Version++; }

protected:
	ShopVersion_t m_Version;
};

#endif


