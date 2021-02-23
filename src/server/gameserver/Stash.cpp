//////////////////////////////////////////////////////////////////////
// Filename    : Stash.h
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////

#include "Stash.h"
#include "Item.h"
#include "ItemRack.h"

Stash::Stash() 
	throw()
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	m_pRack = new ItemRack[STASH_RACK_MAX];
	Assert(m_pRack);

	for (int i=0; i<STASH_RACK_MAX; i++)
		m_pRack[i].init(STASH_INDEX_MAX);

	__END_DEBUG 
	__END_CATCH
}

Stash::~Stash() 
	throw()
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	SAFE_DELETE_ARRAY(m_pRack);

	__END_DEBUG 
	__END_CATCH
}

bool Stash::isExist(BYTE rack, BYTE index) const 

{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (rack >= STASH_RACK_MAX) throw Error("Stash::() : OutOfBounds!");
	return m_pRack[rack].isExist(index);

	__END_DEBUG 
	__END_CATCH
}

void Stash::insert(BYTE rack, BYTE index, Item* pItem) 

{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (rack >= STASH_RACK_MAX) throw Error("Stash::() : OutOfBounds!");
	m_pRack[rack].insert(index, pItem);

	__END_DEBUG 
	__END_CATCH
}

void Stash::remove(BYTE rack, BYTE index) 
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (rack >= STASH_RACK_MAX) throw ("Stash::() : OutOfBounds!");
	m_pRack[rack].remove(index);
	
	__END_DEBUG 
	__END_CATCH
}

Item* Stash::get(BYTE rack, BYTE index) 
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (rack >= STASH_RACK_MAX) throw Error("Stash::() : OutOfBounds!");
	return m_pRack[rack].get(index);

	__END_DEBUG 
	__END_CATCH
}

void Stash::clear(void) 
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	for (int i=0; i<STASH_RACK_MAX; i++)
		m_pRack[i].clear();

	__END_DEBUG 
	__END_CATCH
}

BYTE Stash::getFirstEmptySlot(BYTE rack) const 
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (rack >= STASH_RACK_MAX) throw Error("Stash::() : OutOfBounds!");
	return m_pRack[rack].getFirstEmptySlot();

	__END_DEBUG 
	__END_CATCH
}

BYTE Stash::getLastEmptySlot(BYTE rack) const 
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (rack >= STASH_RACK_MAX) throw Error("Stash::() : OutOfBounds!");
	return m_pRack[rack].getLastEmptySlot();

	__END_DEBUG 
	__END_CATCH
}
