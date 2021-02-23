//////////////////////////////////////////////////////////////////////
// 
// Filename    : ExtraInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ExtraInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ExtraInfo::ExtraInfo () 
     throw ()
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ExtraInfo::~ExtraInfo () 
    throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_ExtraSlotInfoList.empty() ) 
	{
		ExtraSlotInfo * pExtraSlotInfo = m_ExtraSlotInfoList.front();
		SAFE_DELETE(pExtraSlotInfo);
		m_ExtraSlotInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void ExtraInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		ExtraSlotInfo * pExtraSlotInfo = new ExtraSlotInfo();
		pExtraSlotInfo->read( iStream );
		m_ExtraSlotInfoList.push_back( pExtraSlotInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void ExtraInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ListNum );

    for ( list<ExtraSlotInfo*>:: const_iterator itr = m_ExtraSlotInfoList.begin(); itr!= m_ExtraSlotInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t ExtraInfo::getSize()
	throw()
{

	PacketSize_t PacketSize = szBYTE;

	for ( list< ExtraSlotInfo* >::const_iterator itr = m_ExtraSlotInfoList.begin() ; itr != m_ExtraSlotInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ExtraInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ExtraInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<ExtraSlotInfo*>::const_iterator itr = m_ExtraSlotInfoList.begin(); itr!= m_ExtraSlotInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
