//////////////////////////////////////////////////////////////////////
// 
// Filename    : VampireSkillInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "VampireSkillInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
VampireSkillInfo::VampireSkillInfo () 
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
VampireSkillInfo::~VampireSkillInfo () 
    throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_SubVampireSkillInfoList.empty() ) 
	{
		SubVampireSkillInfo * pSubVampireSkillInfo = m_SubVampireSkillInfoList.front();
		SAFE_DELETE(pSubVampireSkillInfo);
		m_SubVampireSkillInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void VampireSkillInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_bLearnNewSkill);
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		SubVampireSkillInfo * pSubVampireSkillInfo = new SubVampireSkillInfo();
		pSubVampireSkillInfo->read( iStream );
		m_SubVampireSkillInfoList.push_back( pSubVampireSkillInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void VampireSkillInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_bLearnNewSkill );
	oStream.write( m_ListNum );

    for ( list<SubVampireSkillInfo*>:: const_iterator itr = m_SubVampireSkillInfoList.begin(); itr!= m_SubVampireSkillInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t VampireSkillInfo::getSize()
	throw()
{

	PacketSize_t PacketSize = szBYTE + szBYTE;

	for ( list< SubVampireSkillInfo* >::const_iterator itr = m_SubVampireSkillInfoList.begin() ; itr != m_SubVampireSkillInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string VampireSkillInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "VampireSkillInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<SubVampireSkillInfo*>::const_iterator itr = m_SubVampireSkillInfoList.begin(); itr!= m_SubVampireSkillInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
