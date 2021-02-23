//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHolyLandBonusInfo.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCHolyLandBonusInfo.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCHolyLandBonusInfo::GCHolyLandBonusInfo()
	throw()
{
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCHolyLandBonusInfo::~GCHolyLandBonusInfo()
	throw()
{
	__BEGIN_TRY
	
	// 길드 리스트의 모든 객체를 삭제
	clearBloodBibleBonusInfoList();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCHolyLandBonusInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE ListNum;

	iStream.read( ListNum );
	for ( int i = 0; i < ListNum; i++ )
	{
		BloodBibleBonusInfo* pBloodBibleBonusInfo = new BloodBibleBonusInfo();
		pBloodBibleBonusInfo->read( iStream );
		m_BloodBibleBonusInfoList.push_back( pBloodBibleBonusInfo );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCHolyLandBonusInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE ListNum = m_BloodBibleBonusInfoList.size();
	oStream.write( ListNum );

	BloodBibleBonusInfoListConstItor itr = m_BloodBibleBonusInfoList.begin();
	for ( ; itr != m_BloodBibleBonusInfoList.end(); itr++ )
	{
		(*itr)->write( oStream );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCHolyLandBonusInfo::clearBloodBibleBonusInfoList()
	throw()
{
	__BEGIN_TRY

	// BloodBibleBonusInfoList 를 삭제한다
	while( !m_BloodBibleBonusInfoList.empty() )
	{
		BloodBibleBonusInfo* pBloodBibleBonusInfo = m_BloodBibleBonusInfoList.front();
		m_BloodBibleBonusInfoList.pop_front();
		SAFE_DELETE( pBloodBibleBonusInfo );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCHolyLandBonusInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCHolyLandBonusInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCHolyLandBonusInfo::getPacketSize() const
	throw()
{
	__BEGIN_TRY

	PacketSize_t PacketSize = szBYTE;

	BloodBibleBonusInfoListConstItor itr = m_BloodBibleBonusInfoList.begin();

	for ( ; itr != m_BloodBibleBonusInfoList.end(); itr++ )
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCHolyLandBonusInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCHolyLandBonusInfo(";

	BloodBibleBonusInfoListConstItor itr = m_BloodBibleBonusInfoList.begin();
	for ( ; itr != m_BloodBibleBonusInfoList.end(); itr++ )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}

