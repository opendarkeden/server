//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowUnionInfo.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShowUnionInfo.h"

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCShowUnionInfo::~GCShowUnionInfo()
    throw ()
{
    __BEGIN_TRY
    while (!m_GuildList.empty())
    {
        SingleGuildInfo* pGuildInfo = m_GuildList.front();

        SAFE_DELETE(pGuildInfo);

        m_GuildList.pop_front();
    }

    m_GuildList.clear();

    __END_CATCH
}

PacketSize_t GCShowUnionInfo::getPacketSize() const throw()
{
	PacketSize_t ret = m_MasterGuildInfo.getSize() + szBYTE;

	list<SingleGuildInfo*>::const_iterator itr = m_GuildList.begin();

	for ( ; itr != m_GuildList.end() ; ++itr )
	{
		ret += (*itr)->getSize();
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCShowUnionInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_MasterGuildInfo.read(iStream);

	BYTE szNum;
	iStream.read(szNum);
	for ( int i=0; i<szNum; ++i )
	{
		SingleGuildInfo* pInfo = new SingleGuildInfo;
		pInfo->read(iStream);
		m_GuildList.push_back(pInfo);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCShowUnionInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_MasterGuildInfo.write(oStream);

	BYTE szNum = m_GuildList.size();
	oStream.write(szNum);

	list<SingleGuildInfo*>::const_iterator itr = m_GuildList.begin();

	for ( ; itr != m_GuildList.end() ; ++itr )
	{
		(*itr)->write(oStream);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCShowUnionInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShowUnionInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCShowUnionInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShowUnionInfo("
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

