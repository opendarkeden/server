//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGQuestInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : Packet notifying the client of its quest-item inventory.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCGQuestInventory.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGQuestInventory::GCGQuestInventory () 
     
{
	__BEGIN_TRY
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCGQuestInventory::~GCGQuestInventory () 
    
{
	__BEGIN_TRY
	__END_CATCH_NO_RETHROW
}

void GCGQuestInventory::read(SocketInputStream & iStream) 
{
	__BEGIN_TRY

	BYTE size;
	iStream.read(size);

	for (int i=0; i<size; ++i )
	{
		ItemType_t item;
		iStream.read(item);
		m_ItemList.push_back(item);
	}

	__END_CATCH
}

void GCGQuestInventory::write(SocketOutputStream & oStream) const 
{
	__BEGIN_TRY

	BYTE size = m_ItemList.size();
	oStream.write(size);

	//cout << "Quest inventory size : " << (int)size << endl;

	list<ItemType_t>::const_iterator itr = m_ItemList.begin();
	list<ItemType_t>::const_iterator endItr = m_ItemList.end();

	for (; itr != endItr ; ++itr )
	{
		oStream.write((*itr));
		//cout << "	Quest item code : " << (int)(*itr) << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCGQuestInventory::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCGQuestInventoryHandler::execute(this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCGQuestInventory::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCGQuestInventory("
		<< ")";
	return msg.toString();

	__END_CATCH
}

