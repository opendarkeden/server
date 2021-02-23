//-------------------------------------------------------------------------------- // 
// Filename    : GCSkillInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GCSkillInfo.h"
#include "SlayerSkillInfo.h"
#include "VampireSkillInfo.h"
#include "OustersSkillInfo.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCSkillInfo::GCSkillInfo ()
	throw ()
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCSkillInfo::~GCSkillInfo ()
	throw ()
{
	while( !m_pPCSkillInfoList.empty() ) 
	{
		PCSkillInfo * pPCSkillInfo = m_pPCSkillInfoList.front();
		SAFE_DELETE(pPCSkillInfo);
		m_pPCSkillInfoList.pop_front();
	}
}

//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void GCSkillInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read pc type/info
	//--------------------------------------------------
	iStream.read( m_PCType );
	BYTE m_ListNum = 0;
	iStream.read( m_ListNum );

	switch ( m_PCType ) {

		case PC_SLAYER :
			for( int i = 0; i < m_ListNum; i++ ) {
				SlayerSkillInfo * pSlayerSkillInfo = new SlayerSkillInfo();
				pSlayerSkillInfo->read( iStream ); 
				m_pPCSkillInfoList.push_back( pSlayerSkillInfo );
			}
			break;

		case PC_VAMPIRE :
			for( int i = 0; i < m_ListNum; i++ ) {
				VampireSkillInfo * pVampireSkillInfo = new VampireSkillInfo();
				pVampireSkillInfo->read( iStream ); 
				m_pPCSkillInfoList.push_back( pVampireSkillInfo );
			}
			break;

		case PC_OUSTERS :
			for( int i = 0; i < m_ListNum; i++ ) {
				OustersSkillInfo * pOustersSkillInfo = new OustersSkillInfo();
				pOustersSkillInfo->read( iStream ); 
				m_pPCSkillInfoList.push_back( pOustersSkillInfo );
			}
			break;

		default :
			throw InvalidProtocolException("invalid pc type");
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCSkillInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write pc type
	//--------------------------------------------------
	oStream.write( m_PCType );

	BYTE szSkill = m_pPCSkillInfoList.size();
	oStream.write( szSkill );

	for (list<PCSkillInfo*>::const_iterator itr = m_pPCSkillInfoList.begin(); itr != m_pPCSkillInfoList.end(); itr++) {
		(*itr)->write( oStream );
    }

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GCSkillInfo::getPacketSize() const
	throw()
{

	PacketSize_t PacketSize = szBYTE;

	for ( list< PCSkillInfo * >::const_iterator itr = m_pPCSkillInfoList.begin() ; itr != m_pPCSkillInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}



//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCSkillInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCSkillInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCSkillInfo(";
	for (list<PCSkillInfo*>::const_iterator itr = m_pPCSkillInfoList.begin(); itr!= m_pPCSkillInfoList.end(); itr++) 
	{
		msg << (*itr)->toString()
			<< ",";
	}
	msg << ")";

	return msg.toString();

	__END_CATCH
}
