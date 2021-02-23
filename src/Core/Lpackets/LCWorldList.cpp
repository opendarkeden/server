//----------------------------------------------------------------------
// 
// Filename    : LCWorldList.cpp 
// Written By  : Reiot
// Description :
// 
//----------------------------------------------------------------------

// include files
#include "LCWorldList.h"
#include "PCSlayerInfo.h"
#include "PCVampireInfo.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
LCWorldList::LCWorldList ()
	throw ()
{
	m_CurrentWorldID = 1;
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
LCWorldList::~LCWorldList ()
	throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_WorldInfoList.empty() ) 
	{
		WorldInfo * pWorldInfo = m_WorldInfoList.front();
		SAFE_DELETE(pWorldInfo);
		m_WorldInfoList.pop_front();
	}

	__END_CATCH
}


//----------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//----------------------------------------------------------------------
void LCWorldList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_CurrentWorldID );

	BYTE ListNum;

    // 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( ListNum );
	for( int i = 0; i < ListNum; i++ ) {
		WorldInfo * pWorldInfo = new WorldInfo();
		pWorldInfo->read( iStream );
		m_WorldInfoList.push_back( pWorldInfo );
	}
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void LCWorldList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_CurrentWorldID );

	BYTE ListNum = m_WorldInfoList.size();
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( ListNum );

	for ( list<WorldInfo*>:: const_iterator itr = m_WorldInfoList.begin(); itr!= m_WorldInfoList.end(); itr++) {
		(*itr)->write( oStream );
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCWorldList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCWorldListHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
PacketSize_t LCWorldList::getPacketSize () const 
	throw ()
{
	__BEGIN_TRY

	// 리스트 인자의 갯수
	PacketSize_t PacketSize = szWorldID + szBYTE;

	for ( list< WorldInfo* >::const_iterator itr = m_WorldInfoList.begin() ; itr != m_WorldInfoList.end() ; itr ++ ) {
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string LCWorldList::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "LCWorldList( CurrentWorldID : " << (int)m_CurrentWorldID;
	for ( list< WorldInfo* >::const_iterator itr = m_WorldInfoList.begin() ; itr != m_WorldInfoList.end() ; itr ++ ) {
		msg << (*itr)->toString();
	}
	msg << ")";

	return msg.toString();

	__END_CATCH
}
