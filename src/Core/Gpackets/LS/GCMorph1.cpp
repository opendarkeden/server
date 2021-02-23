//-------------------------------------------------------------------------------- // 
// Filename    : GCMorph1.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GCMorph1.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCMorph1::GCMorph1 ()
	throw ()
: m_pPCInfo(NULL), m_pInventoryInfo(NULL), m_pGearInfo(NULL), m_pExtraInfo(NULL)
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCMorph1::~GCMorph1 ()
	throw ()
{
	SAFE_DELETE(m_pPCInfo);
	SAFE_DELETE(m_pInventoryInfo);
	SAFE_DELETE(m_pGearInfo);
	SAFE_DELETE(m_pExtraInfo);
}

//--------------------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//--------------------------------------------------------------------------------
void GCMorph1::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read pc type/info
	//--------------------------------------------------
	char pcType;
	iStream.read( pcType );

	switch ( pcType ) {

		case 'S' :
			m_pPCInfo = new PCSlayerInfo2();
			break;

		case 'V' :
			m_pPCInfo = new PCVampireInfo2();
			break;

		default :
			throw InvalidProtocolException("invalid pc type");
	}

	m_pPCInfo->read( iStream ); 

	m_pInventoryInfo = new InventoryInfo();
	m_pInventoryInfo->read( iStream );

	m_pGearInfo = new GearInfo();
	m_pGearInfo->read( iStream );

	m_pExtraInfo = new ExtraInfo();
	m_pExtraInfo->read( iStream );

		
	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//--------------------------------------------------------------------------------
void GCMorph1::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write pc type
	//--------------------------------------------------
	Assert( m_pPCInfo != NULL );
	char pcType;
	switch ( m_pPCInfo->getPCType() ) {
		case PC_SLAYER : 
			pcType = 'S'; 
			break;

		case PC_VAMPIRE : 
			pcType = 'V'; 
			break;

		default : 
			throw InvalidProtocolException("invalid pc type");
	}
	
	oStream.write( pcType );

	m_pPCInfo->write( oStream );

	m_pInventoryInfo->write( oStream );

	m_pGearInfo->write( oStream );

	m_pExtraInfo->write( oStream );

		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCMorph1::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMorph1Handler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCMorph1::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCMorph1("
		<< "PC:" << m_pPCInfo->toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}


