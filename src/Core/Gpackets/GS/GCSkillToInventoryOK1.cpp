//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToInventoryOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK1::GCSkillToInventoryOK1 () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK1::~GCSkillToInventoryOK1 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_SkillType );
	iStream.read( m_ObjectID );
	iStream.read( m_ItemType );
	iStream.read( m_CEffectID );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Duration );

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_SkillType );
	oStream.write( m_ObjectID );
	oStream.write( m_ItemType );
	oStream.write( m_CEffectID );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Duration );
	ModifyInfo::write( oStream);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToInventoryOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToInventoryOK1::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToInventoryOK1("
		<< "SkillType:"  << (int)m_SkillType 
		<< ",ObjectID:"  << (int)m_ObjectID
		<< ",ItemType:"  << (int)m_ItemType
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",X:"         << (int)m_X
		<< ",Y:"         << (int)m_Y 
		<< ",Duration: " << (int)m_Duration;
	msg << ModifyInfo::toString();
	msg << ")";

	return msg.toString();

	__END_CATCH
}
