//////////////////////////////////////////////////////////////////////////////
// Filename    : GCWarList.cpp 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCWarList.h"
#include "RaceWarInfo.h"
#include "LevelWarInfo.h"
#include "GuildWarInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCWarList::GCWarList() 
	throw ()
{
	__BEGIN_TRY 

	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCWarList::~GCWarList() 
	throw ()
{
	__BEGIN_TRY 

	clear();

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
// clear
//////////////////////////////////////////////////////////////////////////////
void
GCWarList::clear()
	throw ()
{
	__BEGIN_TRY 

	WarInfoList::iterator itr = m_WarInfos.begin();

	for( ; itr != m_WarInfos.end() ; itr++ )
	{
		WarInfo* pWarInfo = *itr;

		SAFE_DELETE(pWarInfo);
	}

	m_WarInfos.clear();
	
	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCWarList::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE count = 0;
	iStream.read( count );

	WarType_t warType;
	for( int i=0; i<count; i++ )
	{
		WarInfo* pWarInfo = NULL;
		iStream.read( warType );

		switch ((WarType)warType)
		{
			case WAR_GUILD :
				pWarInfo = new GuildWarInfo;
			break;

			case WAR_RACE :
				pWarInfo = new RaceWarInfo;
			break;

			case WAR_LEVEL :
				pWarInfo = new LevelWarInfo;
			break;

			default :
				throw Error("wrong WarType");
		}

		pWarInfo->read( iStream );

		addWarInfo( pWarInfo );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCWarList::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE count = m_WarInfos.size();
		
	oStream.write( count );

	WarInfoListItor itr = m_WarInfos.begin();

	for( ; itr != m_WarInfos.end(); itr++ )
	{
		WarInfo* pWarInfo = *itr;

		WarType_t warType = pWarInfo->getWarType();
		oStream.write( warType );

		pWarInfo->write( oStream );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCWarList::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCWarListHandler::execute(this , pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

PacketSize_t GCWarList::getPacketSize () const 
	throw ()
{ 
	__BEGIN_TRY

	PacketSize_t size = szBYTE;

	WarInfoListItor itr = m_WarInfos.begin();
	
	for( ; itr != m_WarInfos.end(); itr++ )
	{
		WarInfo* pWarInfo = *itr;
		size += szWarType;
		size += pWarInfo->getSize();
	}
		
	return size;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCWarList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCWarList(" 
		<< "WarNum : " << m_WarInfos.size();

	WarInfoListItor itr = m_WarInfos.begin();

	for( ; itr != m_WarInfos.end(); itr++ )
	{
		WarInfo* pWarInfo = *itr;
		msg << pWarInfo->toString();
	}

	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

WarInfo* GCWarList::popWarInfo() 
	throw()
{
	__BEGIN_TRY

	if( m_WarInfos.empty() ) return NULL;

	WarInfo* pWarInfo = m_WarInfos.front();
	m_WarInfos.pop_front();

	return pWarInfo;

	__END_CATCH
}

void GCWarList::operator = (const GCWarList& WL)
{
	clear();

	WarInfoListItor itr = WL.m_WarInfos.begin();

	for( ; itr != WL.m_WarInfos.end(); itr++ )
	{
		WarInfo* pWarInfo = *itr;
		WarInfo* pNewWarInfo = NULL;

		switch (pWarInfo->getWarType())
		{
			case WAR_GUILD 	: 
			{
				GuildWarInfo* pGWI = dynamic_cast<GuildWarInfo*>(pWarInfo);
				Assert(pGWI!=NULL);

				GuildWarInfo* pNewGWI = new GuildWarInfo; 	
				*pNewGWI = *pGWI;
				pNewWarInfo = pNewGWI;
			}
			break;

			case WAR_RACE 	: 
			{
				RaceWarInfo* pRWI = dynamic_cast<RaceWarInfo*>(pWarInfo);
				Assert(pRWI!=NULL);

				RaceWarInfo* pNewRWI = new RaceWarInfo; 	
				*pNewRWI = *pRWI;
				pNewWarInfo = pNewRWI;
			}
			break;

			case WAR_LEVEL	:
			{
				LevelWarInfo* pLWI = dynamic_cast<LevelWarInfo*>(pWarInfo);
				Assert(pLWI!=NULL);

				LevelWarInfo* pNewLWI = new LevelWarInfo;
				*pNewLWI = *pLWI;
				pNewWarInfo = pNewLWI;
			}
			break;

			default :
				throw Error("wrong WarType");
		}

		addWarInfo( pNewWarInfo );
//		cout << "GCWarList::operator = New ()" << pNewWarInfo->getStartTime() << endl;
//		cout << "GCWarList::operator = Ori ()" << pWarInfo->getStartTime() << endl;
	}
}

