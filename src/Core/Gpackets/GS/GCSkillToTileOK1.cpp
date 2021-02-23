//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToTileOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToTileOK1::GCSkillToTileOK1 () 
     throw ()
{
	__BEGIN_TRY

	m_CListNum = 0;
	m_Grade = 0;


	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToTileOK1::~GCSkillToTileOK1 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_SkillType );
	iStream.read( m_CEffectID );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Duration );
	iStream.read( m_Range);
	iStream.read( m_Grade );
	
	iStream.read( m_CListNum );

	ObjectID_t m_Value;
	int i;

	for( i = 0; i < m_CListNum; i++ ) {
		iStream.read( m_Value );
		m_CList.push_back( m_Value );
	}

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_SkillType );
	oStream.write( m_CEffectID );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Duration );
	oStream.write( m_Range);
	oStream.write( m_Grade );
	
	oStream.write( m_CListNum );
	for ( list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
		oStream.write( *itr );
	}

	ModifyInfo::write( oStream);
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK1::addListElement()
// 
// ( 변화부위, 변화수치 ) 의 한 셋을 리스트에 넣기 위한 멤버 함수. 
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::addCListElement( ObjectID_t ObjectID )
	throw()
{
	__BEGIN_TRY

	// Creature ID를 추가한다.
	m_CList.push_back( ObjectID );

	// 크리처 ID count를 증가시킨다.
	m_CListNum++;

	__END_CATCH

}

/*
//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK1::deleteCListElement()
// 
// Creature List의 요소를 지울때 필요한 멤버 함수.
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::deleteCListElement()
	throw()
{
	__BEGIN_TRY

	// 크리쳐 아이디를 하나 지운다.
	m_CList.pop_front();
	
	// 크리처 리스트 카운터를 하나 지운다.
	m_CListNum--;

	__END_CATCH
}
*/

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToTileOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToTileOK1::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCSkillToTileOK1("
		<< "SkillType:" << (int)m_SkillType 
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",X:"  << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",Duration:" << (int)m_Duration 
		<< ",Range:"<< (int)m_Range 
		<< ",Grade:" << (int)m_Grade 
		<< ",CListNum:" << (int)m_CListNum 
		<< "CListSet(";

	for ( list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
		msg << (int)(*itr) << ","; 
	}

	msg << ")";

	msg << ModifyInfo::toString();

	msg << ")";

	return msg.toString();

	__END_CATCH
}


