//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyJoined.cpp 
// Written By  : 김성민
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPartyJoined.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class GCPartyJoined member methods
//////////////////////////////////////////////////////////////////////////////

GCPartyJoined::GCPartyJoined()
{
	m_MemberCount = 0;
}

GCPartyJoined::~GCPartyJoined()
{
	clear();
}

PacketSize_t GCPartyJoined::getPacketSize() const 
	throw() 
{ 
	__BEGIN_TRY

	PacketSize_t value = 0;

	value += szBYTE; // 멤버 카운트

	list<PARTY_MEMBER_INFO*>::const_iterator itr = m_MemberInfoList.begin();
	for (; itr != m_MemberInfoList.end(); itr++)
	{
		PARTY_MEMBER_INFO* pInfo = (*itr);

		value += szBYTE;               // 이름 길이
		value += (pInfo->name).size(); // 실제 이름
		value += szBYTE;               // 성별
		value += szBYTE;               // 헤어 스타일
		value += szIP;                 // IP
	}

	return value;

	__END_CATCH
}

void GCPartyJoined::addMemberInfo(PARTY_MEMBER_INFO* pInfo) 
	throw()
{
	__BEGIN_TRY

	Assert(pInfo != NULL);
	m_MemberInfoList.push_back(pInfo);
	m_MemberCount++;

	__END_CATCH
}

PARTY_MEMBER_INFO* GCPartyJoined::popMemberInfo(void) 
	throw()
{
	__BEGIN_TRY

	if (!m_MemberInfoList.empty())
	{
		PARTY_MEMBER_INFO* pInfo = m_MemberInfoList.front();
		m_MemberInfoList.pop_front();
		m_MemberCount--;

		return pInfo;
	}

	return NULL;

	__END_CATCH
}

void GCPartyJoined::clear(void)
	throw()
{
	__BEGIN_TRY

	m_MemberCount = 0;

	while (!m_MemberInfoList.empty())
	{
		PARTY_MEMBER_INFO* pInfo = m_MemberInfoList.front();

#ifdef __GAME_CLIENT__
		if (pInfo != NULL)
		{
			delete pInfo;
			pInfo = NULL;
		}
#else
		SAFE_DELETE(pInfo);
#endif

		m_MemberInfoList.pop_front();
	}

	m_MemberInfoList.clear();

	__END_CATCH
}

void GCPartyJoined::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// 먼저 리스트의 사이즈를 읽어들인다.
	iStream.read(m_MemberCount);

	for (uint i=0; i<m_MemberCount; i++)
	{
		PARTY_MEMBER_INFO* pInfo = new PARTY_MEMBER_INFO;

		BYTE name_length = 0;
		iStream.read(name_length);

		if (name_length > 0)
		{
			iStream.read(pInfo->name, name_length);
		}

		iStream.read(pInfo->sex);
		iStream.read(pInfo->hair_style);
		iStream.read(pInfo->ip);

		m_MemberInfoList.push_back(pInfo);
	}

	__END_CATCH
}
		    
void GCPartyJoined::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// 먼저 리스트의 사이즈를 쓴다.
	oStream.write(m_MemberCount);

	list<PARTY_MEMBER_INFO*>::const_iterator itr = m_MemberInfoList.begin();
	for (; itr != m_MemberInfoList.end(); itr++)
	{
		PARTY_MEMBER_INFO* pInfo = (*itr);
		Assert(pInfo != NULL);

		BYTE name_length = (pInfo->name).size();
		oStream.write(name_length);

		if (name_length > 0)
		{
			oStream.write(pInfo->name);
		}

		oStream.write(pInfo->sex);
		oStream.write(pInfo->hair_style);
		oStream.write(pInfo->ip);
	}

	__END_CATCH
}

void GCPartyJoined::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCPartyJoinedHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCPartyJoined::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCPartyJoined("
		<< "MemberCount:" << (int)m_MemberCount << ",";

	list<PARTY_MEMBER_INFO*>::const_iterator itr = m_MemberInfoList.begin();
	for (; itr != m_MemberInfoList.end(); itr++)
	{
		PARTY_MEMBER_INFO* pInfo = (*itr);
		msg << "("
			<< pInfo->name
			<< "),";
	}

	/*
	list<PARTY_MEMBER_INFO*>::const_iterator itr = m_MemberInfoList.begin();
	for (; itr != m_MemberInfoList.end(); itr++)
	{
		PARTY_MEMBER_INFO* pInfo = (*itr);
		msg << "Element("
			<< "Name:"       << pInfo->name
			<< ",Sex:"       << (int)pInfo->sex
			<< ",HairStyle:" << (int)pInfo->hair_style
			<< ",MainColor:" << (int)pInfo->main_color
			<< ",SubColor:"  << (int)pInfo->sub_color 
			<< "),";
	}
	*/

	msg << ")";
	return msg.toString();
		
	__END_CATCH
}


