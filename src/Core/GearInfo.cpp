//////////////////////////////////////////////////////////////////////
// 
// Filename    : GearInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GearInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GearInfo::GearInfo () 
     throw ()
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GearInfo::~GearInfo () 
    throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_GearSlotInfoList.empty() ) {
		GearSlotInfo * pGearSlotInfo = m_GearSlotInfoList.front();
		SAFE_DELETE(pGearSlotInfo);
		m_GearSlotInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GearInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		GearSlotInfo * pGearSlotInfo = new GearSlotInfo();
		pGearSlotInfo->read( iStream );
		m_GearSlotInfoList.push_back( pGearSlotInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GearInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ListNum );

    for ( list<GearSlotInfo*>:: const_iterator itr = m_GearSlotInfoList.begin(); itr!= m_GearSlotInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GearInfo::getSize()
	throw()
{

	PacketSize_t PacketSize = szBYTE;

	for ( list< GearSlotInfo* >::const_iterator itr = m_GearSlotInfoList.begin() ; itr != m_GearSlotInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GearInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GearInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<GearSlotInfo*>::const_iterator itr = m_GearSlotInfoList.begin(); itr!= m_GearSlotInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
