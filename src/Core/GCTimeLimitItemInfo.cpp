#include "GCTimeLimitItemInfo.h"
#include "Assert1.h"

GCTimeLimitItemInfo::GCTimeLimitItemInfo()
	
{
	m_TimeLimitItemInfos.clear();
}

GCTimeLimitItemInfo::~GCTimeLimitItemInfo()
	
{
}

void GCTimeLimitItemInfo::read(SocketInputStream& iStream)
	
{
	__BEGIN_TRY

	BYTE	szInfo;

	iStream.read(szInfo);
	Assert(szInfo <= MAX_TIME_LIMIT_ITEM_INFO);

	m_TimeLimitItemInfos.clear();

	for (int count = 0; count < szInfo; ++count )
	{
		ObjectID_t objectID;
		DWORD time;
		iStream.read(objectID);
		iStream.read(time);

		if (m_TimeLimitItemInfos.find(objectID) == m_TimeLimitItemInfos.end() )
		{
			m_TimeLimitItemInfos[objectID] = time;
		}
	}

	__END_CATCH
}

void GCTimeLimitItemInfo::write(SocketOutputStream& oStream ) const
	
{
	__BEGIN_TRY

	BYTE szInfo = m_TimeLimitItemInfos.size();

	Assert(szInfo <= MAX_TIME_LIMIT_ITEM_INFO);

	oStream.write(szInfo);

	ItemTimeLimitMap::const_iterator	itr = m_TimeLimitItemInfos.begin();
	ItemTimeLimitMap::const_iterator	endItr = m_TimeLimitItemInfos.end();

	for(; itr != endItr ; ++itr )
	{
		oStream.write(itr->first);
		oStream.write(itr->second);
	}

	__END_CATCH
}

void GCTimeLimitItemInfo::execute(Player* pPlayer)
	
{
	__BEGIN_TRY

	GCTimeLimitItemInfoHandler::execute(this, pPlayer);

	__END_CATCH
}

PacketSize_t GCTimeLimitItemInfo::getPacketSize() const
	
{
	__BEGIN_TRY

	return szBYTE + m_TimeLimitItemInfos.size() * (szObjectID + szDWORD);

	__END_CATCH
}

DWORD GCTimeLimitItemInfo::getTimeLimit(ObjectID_t objectID) const
	
{
	__BEGIN_TRY

	ItemTimeLimitMap::const_iterator	itr = m_TimeLimitItemInfos.find(objectID);

	if (itr != m_TimeLimitItemInfos.end() ) return itr->second;

	return 0xffff;

	__END_CATCH
}

void GCTimeLimitItemInfo::addTimeLimit(ObjectID_t objectID, DWORD time)
	
{
	__BEGIN_TRY

	ItemTimeLimitMap::const_iterator	itr = m_TimeLimitItemInfos.find(objectID);

	if (itr != m_TimeLimitItemInfos.end() ) throw Error("GCTimeLimitItemInfo addTimeLimit error");

	m_TimeLimitItemInfos[ objectID ] = time;

	__END_CATCH
}

string GCTimeLimitItemInfo::toString() const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCTimeLimitItemInfoHandler(";

	ItemTimeLimitMap::const_iterator	itr = m_TimeLimitItemInfos.begin();
	ItemTimeLimitMap::const_iterator	endItr = m_TimeLimitItemInfos.end();

	for(; itr != endItr ; ++itr )
	{
		msg << "(" << itr->first
			<< "," << itr->second
			<< ") ";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
