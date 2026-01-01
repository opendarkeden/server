//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCActiveGuildList.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCActiveGuildList.h"
#include <list>
#include <exception>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCActiveGuildList::GCActiveGuildList()
	
{
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCActiveGuildList::~GCActiveGuildList()

{
	// Destructor must not throw; clear list defensively.
	try
	{
		clearGuildInfoList();
	}
	catch (const std::exception&)
	{
		// Ignore to avoid std::terminate in noexcept destructor.
	}
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCActiveGuildList::read (SocketInputStream & iStream ) 
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
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCActiveGuildList::write (SocketOutputStream & oStream ) const 
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
void GCActiveGuildList::clearGuildInfoList()
	
{
	__BEGIN_TRY

	// GuildInfoList �� �����Ѵ�
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
void GCActiveGuildList::execute (Player * pPlayer ) 
{
	__BEGIN_TRY
		
	GCActiveGuildListHandler::execute(this , pPlayer);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCActiveGuildList::getPacketSize() const
	
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
string GCActiveGuildList::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCActiveGuildList(";

	list<GuildInfo*>::const_iterator itr = m_GuildInfoList.begin();
	for (; itr != m_GuildInfoList.end(); itr++ )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}

