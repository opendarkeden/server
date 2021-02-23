//////////////////////////////////////////////////////////////////////
// 
// Filename    : SlayerSkillInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "SlayerSkillInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SlayerSkillInfo::SlayerSkillInfo () 
     throw ()
{
	__BEGIN_TRY
	m_bLearnNewSkill = false;
	m_DomainType = 0;
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SlayerSkillInfo::~SlayerSkillInfo () 
    throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_SubSlayerSkillInfoList.empty() ) {
		SubSlayerSkillInfo * pSubSlayerSkillInfo = m_SubSlayerSkillInfoList.front();
		SAFE_DELETE(pSubSlayerSkillInfo);
		m_SubSlayerSkillInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void SlayerSkillInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_bLearnNewSkill);
	iStream.read( m_DomainType );
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		SubSlayerSkillInfo * pSubSlayerSkillInfo = new SubSlayerSkillInfo();
		pSubSlayerSkillInfo->read( iStream );
		m_SubSlayerSkillInfoList.push_back( pSubSlayerSkillInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void SlayerSkillInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_bLearnNewSkill );
	oStream.write( m_DomainType );
	oStream.write( m_ListNum );

    for ( list<SubSlayerSkillInfo*>:: const_iterator itr = m_SubSlayerSkillInfoList.begin(); itr!= m_SubSlayerSkillInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t SlayerSkillInfo::getSize()
	throw()
{

	PacketSize_t PacketSize = szBYTE + szSkillDomainType + szBYTE;

	for ( list< SubSlayerSkillInfo* >::const_iterator itr = m_SubSlayerSkillInfoList.begin() ; itr != m_SubSlayerSkillInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string SlayerSkillInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SlayerSkillInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<SubSlayerSkillInfo*>::const_iterator itr = m_SubSlayerSkillInfoList.begin(); itr!= m_SubSlayerSkillInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
