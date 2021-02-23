//////////////////////////////////////////////////////////////////////
// 
// Filename    : EffectInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 이펙트 정보 리스트 멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "EffectInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
EffectInfo::EffectInfo () 
     throw ()
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
EffectInfo::~EffectInfo () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void EffectInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ListNum );

	WORD m_Value;
	for( int i = 0; i < m_ListNum * 2 ; i++ ) {
		iStream.read( m_Value );
		m_EList.push_back(m_Value);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void EffectInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ListNum );

    for ( list<WORD>:: const_iterator itr = m_EList.begin(); itr!= m_EList.end(); itr++) {
		oStream.write(*itr);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// EffectInfo::addListElement()
// 
// ( 변화부위, 변화수치 ) 의 한 셋을 리스트에 넣기 위한 멤버 함수. 
//
//////////////////////////////////////////////////////////////////////
void EffectInfo::addListElement( EffectID_t EffectID , WORD Value )
	throw()
{
	__BEGIN_TRY

	// 변하는 것이 무엇인지 List에 넣는다.
	m_EList.push_back( EffectID );

	// 변하는 수치를 List에 넣는다.
	m_EList.push_back( Value );

	// 변화 셋의 갯수를 하나 증가 시킨다.
	m_ListNum++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string EffectInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectInfo( "
		<< ",ListNum: " << (int)m_ListNum 
		<< " ListSet(" ;
	for ( list<WORD>::const_iterator itr = m_EList.begin(); itr!= m_EList.end() ; itr++ ) {
		msg << (int)(*itr) << ",";
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}

