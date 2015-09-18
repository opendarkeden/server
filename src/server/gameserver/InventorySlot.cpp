//////////////////////////////////////////////////////////////////////////////
// Filename    : InventorySlot.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "InventorySlot.h"

//////////////////////////////////////////////////////////////////////////////
// class InventorySlot member methods
//////////////////////////////////////////////////////////////////////////////

/*
InventorySlot::InventorySlot() 
	throw() 
{ 
	__BEGIN_TRY

	m_pItem = NULL; 

	__END_CATCH
}
*/

InventorySlot::~InventorySlot() 
	throw(Error) 
{ 
	__BEGIN_TRY

	Assert(m_pItem == NULL);

	__END_CATCH
}

/*
Item* InventorySlot::getItem() 
	throw() 
{ 
	__BEGIN_TRY

	return m_pItem; 

	__END_CATCH
}
*/

void InventorySlot::addItem(Item* pItem) 
	throw() 
{ 
	__BEGIN_TRY

	Assert(pItem != NULL);
	m_pItem = pItem; 

	__END_CATCH
}

void InventorySlot::deleteItem() 
	throw(Error) 
{ 
	__BEGIN_TRY

	Assert(m_pItem != NULL); 
	m_pItem = NULL; 

	__END_CATCH
}

