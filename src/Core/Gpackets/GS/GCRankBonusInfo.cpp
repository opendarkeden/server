//-------------------------------------------------------------------------------- // 
// Filename    : GCRankBonusInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GCRankBonusInfo.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCRankBonusInfo::GCRankBonusInfo ()
	throw ()
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCRankBonusInfo::~GCRankBonusInfo ()
	throw ()
{
	m_RankBonusInfoList.clear();
}

//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void GCRankBonusInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE ListNum;
	iStream.read( ListNum );

	for ( WORD i = 0; i < ListNum; i++ )
	{
		DWORD rankBonusType;
		iStream.read( rankBonusType );
		m_RankBonusInfoList.push_back( rankBonusType );
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCRankBonusInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write pc type
	//--------------------------------------------------
	BYTE size = m_RankBonusInfoList.size();
	oStream.write( size );

	for (list<DWORD>::const_iterator itr = m_RankBonusInfoList.begin(); itr!= m_RankBonusInfoList.end(); itr++) 
	{
		oStream.write( (*itr) );
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCRankBonusInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCRankBonusInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCRankBonusInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCRankBonusInfo(";
	for (list<DWORD>::const_iterator itr = m_RankBonusInfoList.begin(); itr!= m_RankBonusInfoList.end(); itr++) 
	{
		msg << (*itr) << ",";
	}
	msg << ")";

	return msg.toString();

	__END_CATCH
}
