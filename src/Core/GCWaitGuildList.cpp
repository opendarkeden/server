//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWaitGuildList.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCWaitGuildList.h"
#include <list>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCWaitGuildList::GCWaitGuildList()
	
{
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCWaitGuildList::~GCWaitGuildList()
	
{
	__BEGIN_TRY
	
	// Clear all guild info entries.
	clearGuildInfoList();

	__END_CATCH_NO_RETHROW
}

//////////////////////////////////////////////////////////////////////
// Initialize from the incoming stream.
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	WORD ListNum;

	iStream.read(ListNum);
	for (int i = 0; i < ListNum; i++ )
	{
		GuildInfo* pGuildInfo = new GuildInfo();
		pGuildInfo->read(iStream);
		m_GuildInfoList.push_front(pGuildInfo);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Write this packet to the outgoing stream.
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	WORD ListNum = m_GuildInfoList.size();
	oStream.write(ListNum);

	GuildInfoListConstItor itr = m_GuildInfoList.begin();
	for (; itr != m_GuildInfoList.end(); itr++ )
	{
		(*itr)->write(oStream);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::clearGuildInfoList()
	
{
	__BEGIN_TRY

	// Clear GuildInfoList
	while(!m_GuildInfoList.empty() )
	{
		GuildInfo* pGuildInfo = m_GuildInfoList.front();
		m_GuildInfoList.pop_front();
		SAFE_DELETE(pGuildInfo);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCWaitGuildListHandler::execute(this , pPlayer);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCWaitGuildList::getPacketSize() const
	
{
	__BEGIN_TRY

	PacketSize_t PacketSize = szWORD;

	GuildInfoListConstItor itr = m_GuildInfoList.begin();

	for (; itr != m_GuildInfoList.end(); itr++ )
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCWaitGuildList::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCWaitGuildList(";

	list<GuildInfo*>::const_iterator itr = m_GuildInfoList.begin();
	for (; itr != m_GuildInfoList.end(); itr++ )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}

