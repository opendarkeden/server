//////////////////////////////////////////////////////////////////////
// 
// Filename    : OustersSkillInfo.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "OustersSkillInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
OustersSkillInfo::OustersSkillInfo () 
     throw ()
{
	__BEGIN_TRY
	m_bLearnNewSkill = false;
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
OustersSkillInfo::~OustersSkillInfo () 
    throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_SubOustersSkillInfoList.empty() ) 
	{
		SubOustersSkillInfo * pSubOustersSkillInfo = m_SubOustersSkillInfoList.front();
		SAFE_DELETE(pSubOustersSkillInfo);
		m_SubOustersSkillInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void OustersSkillInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_bLearnNewSkill);
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		SubOustersSkillInfo * pSubOustersSkillInfo = new SubOustersSkillInfo();
		pSubOustersSkillInfo->read( iStream );
		m_SubOustersSkillInfoList.push_back( pSubOustersSkillInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void OustersSkillInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_bLearnNewSkill );
	oStream.write( m_ListNum );

    for ( list<SubOustersSkillInfo*>:: const_iterator itr = m_SubOustersSkillInfoList.begin(); itr!= m_SubOustersSkillInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t OustersSkillInfo::getSize()
	throw()
{

	PacketSize_t PacketSize = szBYTE + szBYTE;

	for ( list< SubOustersSkillInfo* >::const_iterator itr = m_SubOustersSkillInfoList.begin() ; itr != m_SubOustersSkillInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string OustersSkillInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "OustersSkillInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<SubOustersSkillInfo*>::const_iterator itr = m_SubOustersSkillInfoList.begin(); itr!= m_SubOustersSkillInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
