//////////////////////////////////////////////////////////////////////
// 
// Filename    : ModifyItemInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ModifyItemInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ModifyItemInfo::ModifyItemInfo () 
     throw ()
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ModifyItemInfo::~ModifyItemInfo () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void ModifyItemInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ListNum );

	DWORD m_Value;
	for( int i = 0; i < m_ListNum; i++ ) {
		// ObjectID Read
		iStream.read( m_Value );
		m_SList.push_back(m_Value);

		// Modify identifier Read
		iStream.read( m_Value );
		m_SList.push_back(m_Value);

		// Value Read
		iStream.read( m_Value );
		m_SList.push_back(m_Value);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void ModifyItemInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ListNum );

    for ( list<DWORD>:: const_iterator itr = m_SList.begin(); itr!= m_SList.end(); itr++) {
		oStream.write(*itr);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// ModifyItemInfo::addListElement()
// 
// ( 변화부위, 변화수치 ) 의 한 셋을 리스트에 넣기 위한 멤버 함수. 
//
//////////////////////////////////////////////////////////////////////
void ModifyItemInfo::addListElement( ObjectID_t ObjectID, ModifyType List , DWORD Value )
	throw()
{
	__BEGIN_TRY

	m_SList.push_back( ObjectID );

	// 변하는 것이 무엇인지 List에 넣는다.
	m_SList.push_back( List );

	// 변하는 수치를 List에 넣는다.
	m_SList.push_back( Value );

	// 변화 셋의 갯수를 하나 증가 시킨다.
	m_ListNum++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ModifyItemInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ModifyItemInfo( "
		<< ",ListNum: " << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<DWORD>::const_iterator itr = m_SList.begin(); itr!= m_SList.end() ; itr++ ) {
		msg << (int)(*itr) << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

