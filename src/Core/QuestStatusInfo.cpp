#include "QuestStatusInfo.h"

void QuestStatusInfo::read(SocketInputStream& iStream) throw(ProtocolException, Error)
{
	iStream.read(m_QuestID);
	iStream.read(m_Status);
	BYTE size;
	iStream.read(size);
	for ( int i=0; i<size; ++i )
	{
		MissionInfo* temp = new MissionInfo;
		temp->read(iStream);
		m_Missions.push_back(temp);
	}
}

void QuestStatusInfo::write(SocketOutputStream& oStream) const throw(ProtocolException, Error)
{
	oStream.write(m_QuestID);
	oStream.write(m_Status);
	BYTE size = m_Missions.size();
	oStream.write(size);

	list<MissionInfo*>::const_iterator itr = m_Missions.begin();
	for ( ; itr != m_Missions.end(); ++itr )
	{
		(*itr)->write(oStream);
	}
}

PacketSize_t QuestStatusInfo::getSize() const
{
	PacketSize_t ret = szDWORD + szBYTE + szBYTE;
	list<MissionInfo*>::const_iterator itr = m_Missions.begin();
	for ( ; itr != m_Missions.end(); ++itr )
	{
		ret += (*itr)->getSize();
	}

	return ret;
}

PacketSize_t QuestStatusInfo::getMaxSize()
{
	return szDWORD + szBYTE + szBYTE + MissionInfo::getMaxSize()*MAX_MISSION_NUM;
}
