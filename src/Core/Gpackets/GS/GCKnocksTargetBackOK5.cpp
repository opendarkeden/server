//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK5.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCKnocksTargetBackOK5.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK5::GCKnocksTargetBackOK5 ()
     throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	__END_DEBUG
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK5::~GCKnocksTargetBackOK5 ()
    throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5::read ( SocketInputStream & iStream )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
//	iStream.read( m_X);
//	iStream.read( m_Y );
	iStream.read( m_bSuccess);

	iStream.read( m_SkillType);
	iStream.read( m_dir);
	iStream.read( m_X);
	iStream.read( m_Y);
	__END_DEBUG
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5::write ( SocketOutputStream & oStream )
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
//	oStream.write( m_X);
//	oStream.write( m_Y);
	oStream.write( m_bSuccess);
	
	oStream.write( m_SkillType);
	oStream.write( m_dir);
	oStream.write( m_X);
	oStream.write( m_Y);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCKnocksTargetBackOK5Handler::execute( this , pPlayer );
		
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCKnocksTargetBackOK5::toString () 
	const throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	StringStream msg;
	msg << "GCKnocksTargetBackOK5("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",TargetObjectID: " << (int)m_TargetObjectID 
		<< ",Success:"<< (int)m_bSuccess
		<< ",(Dir,X,Y) : " << (int)m_dir << "," << (int)m_X << "," << (int)m_Y
		<< ")";
	return msg.toString();

	__END_DEBUG
	__END_CATCH
}
