//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddMonsterFromTransformation.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#include "GCAddMonsterFromTransformation.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCAddMonsterFromTransformation::GCAddMonsterFromTransformation()
	throw( Error )
:m_pEffectInfo(NULL)
{
	__BEGIN_TRY
	__END_CATCH
}

//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCAddMonsterFromTransformation::~GCAddMonsterFromTransformation()
	throw( Error )
{
	__BEGIN_TRY

	SAFE_DELETE(m_pEffectInfo);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAddMonsterFromTransformation::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE name_length = 0;
		
	iStream.read( m_ObjectID );
	iStream.read( m_MonsterType );

	iStream.read(name_length);
	if (name_length != 0) iStream.read(m_MonsterName, name_length);

	iStream.read( m_MainColor );
	iStream.read( m_SubColor );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );

	m_pEffectInfo = new EffectInfo();
	m_pEffectInfo->read( iStream );

	iStream.read( m_CurrentHP );
	iStream.read( m_MaxHP );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAddMonsterFromTransformation::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE name_length = m_MonsterName.size();

	oStream.write( m_ObjectID );
	oStream.write( m_MonsterType );

	oStream.write( name_length );
	if (m_MonsterName.size() != 0) oStream.write( m_MonsterName );

	oStream.write( m_MainColor );
	oStream.write( m_SubColor );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );

	m_pEffectInfo->write( oStream );

	oStream.write( m_CurrentHP );
	oStream.write( m_MaxHP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddMonsterFromTransformation::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddMonsterFromTransformationHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddMonsterFromTransformation::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCAddMonsterFromTransformation("
		<< "ObjectID:"     << (int)m_ObjectID
		<< ",MonsterType:" << (int)m_MonsterType
		<< ",MonsterName:" << m_MonsterName
		<< ",MainColor:"   << (int)m_MainColor
		<< ",SubColor:"    << (int)m_SubColor
		<< ",X:"           << (int)m_X 
		<< ",Y:"           << (int)m_Y 
		<< ",Dir:"         << Dir2String[m_Dir]
		<< ",Effects:"     << m_pEffectInfo->toString()
		<< ",CurrentHP:"   << (int)m_CurrentHP
		<< ",MaxHP:"       << (int)m_MaxHP
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
