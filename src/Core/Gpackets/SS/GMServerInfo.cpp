//////////////////////////////////////////////////////////////////////
// 
// Filename    : GMServerInfo.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GMServerInfo.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GMServerInfo::GMServerInfo () 
     throw ()
{
	__BEGIN_TRY

	m_ZoneCount = 0;

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GMServerInfo::~GMServerInfo () 
    throw ()
{
	__BEGIN_TRY

	m_ZoneUserList.clear();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GMServerInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GMServerInfoHandler::execute( this );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GMServerInfo::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iDatagram.read(m_WorldID);
	iDatagram.read(m_ServerID);

	ZONEUSERDATA zoneuser_data;

	iDatagram.read(m_ZoneCount);

	for (BYTE s=0; s<m_ZoneCount; s++)
	{
		iDatagram.read(zoneuser_data.ZoneID);
		iDatagram.read(zoneuser_data.UserNum);

		m_ZoneUserList.push_back(zoneuser_data);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GMServerInfo::write ( Datagram & oDatagram ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	oDatagram.write(m_WorldID);
	oDatagram.write(m_ServerID);

	oDatagram.write(m_ZoneCount);
	list<ZONEUSERDATA>::const_iterator zoneuser_itr = m_ZoneUserList.begin();
	for (; zoneuser_itr != m_ZoneUserList.end(); zoneuser_itr++)
	{
		ZONEUSERDATA zoneuser_data = *zoneuser_itr;
		oDatagram.write(zoneuser_data.ZoneID);
		oDatagram.write((WORD)zoneuser_data.UserNum);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string GMServerInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "[GMServerInfo]"
		<< "ZoneNum:" << (int)m_ZoneCount
		<< ", ZoneUser(";

	int total = 0;

	list<ZONEUSERDATA>::const_iterator zoneuser_itr = m_ZoneUserList.begin();
	for (; zoneuser_itr != m_ZoneUserList.end(); zoneuser_itr++)
	{
		ZONEUSERDATA zoneuser_data = *zoneuser_itr;
		msg << (int)zoneuser_data.ZoneID << ":"
			<< (int)zoneuser_data.UserNum << ", ";

		total += zoneuser_data.UserNum;
	}

	msg << "), Total( " << total << " )";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GMServerInfo::addZoneUserData(ZoneID_t ZoneID, DWORD UserNum)
	    throw()
{
	__BEGIN_TRY

	ZONEUSERDATA zoneuser_data;
	zoneuser_data.ZoneID = ZoneID;
	zoneuser_data.UserNum = UserNum;

	m_ZoneUserList.push_back(zoneuser_data);

	m_ZoneCount++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GMServerInfo::popZoneUserData(ZONEUSERDATA& rData)
	    throw()
{
	__BEGIN_TRY

	ZONEUSERDATA zoneuser_data = m_ZoneUserList.front();

	rData.ZoneID = zoneuser_data.ZoneID;
	rData.UserNum = zoneuser_data.UserNum;

	m_ZoneUserList.pop_front();
	m_ZoneCount--;

	__END_CATCH
}
