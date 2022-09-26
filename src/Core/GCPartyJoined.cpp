//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyJoined.cpp 
// Written By  : �輺��
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCPartyJoined.h"
#include "Assert1.h"

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
	 
{ 
	__BEGIN_TRY

	PacketSize_t value = 0;

	value += szBYTE; // ��� ī��Ʈ

	list<PARTY_MEMBER_INFO*>::const_iterator itr = m_MemberInfoList.begin();
	for (; itr != m_MemberInfoList.end(); itr++)
	{
		PARTY_MEMBER_INFO* pInfo = (*itr);

		value += szBYTE;               // �̸� ����
		value += (pInfo->name).size(); // ���� �̸�
		value += szBYTE;               // ����
		value += szBYTE;               // ��� ��Ÿ��
		value += szIP;                 // IP
	}

	return value;

	__END_CATCH
}

void GCPartyJoined::addMemberInfo(PARTY_MEMBER_INFO* pInfo) 
	
{
	__BEGIN_TRY

	Assert(pInfo != NULL);
	m_MemberInfoList.push_back(pInfo);
	m_MemberCount++;

	__END_CATCH
}

PARTY_MEMBER_INFO* GCPartyJoined::popMemberInfo(void) 
	
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
	 
{
	__BEGIN_TRY

	// ���� ����Ʈ�� ����� �о���δ�.
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
     
{
	__BEGIN_TRY

	// ���� ����Ʈ�� ����� ����.
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
	 
{
	__BEGIN_TRY
		
	GCPartyJoinedHandler::execute(this , pPlayer);

	__END_CATCH
}

string GCPartyJoined::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCPartyJoined("
		<< "MemberCount:" << (int)m_MemberCount << ",";

	list<PARTY_MEMBER_INFO*>::const_iterator itr = m_MemberInfoList.begin();
	for (; itr != m_MemberInfoList.end(); itr++)
	{
		PARTY_MEMBER_INFO* pInfo = (*itr);
		msg << "Element("
			<< "Name:"       << pInfo->name
			<< ",Sex:"       << (int)pInfo->sex
			<< ",HairStyle:" << (int)pInfo->hair_style
			<< ",IP:"  << (int)pInfo->ip
			<< "),";
	}

	msg << ")";
	return msg.toString();
		
	__END_CATCH
}


