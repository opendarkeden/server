//----------------------------------------------------------------------
// 
// Filename    : LCServerList.cpp 
// Written By  : Reiot
// Description :
// 
//----------------------------------------------------------------------

// include files
#include "LCServerList.h"
#include "PCSlayerInfo.h"
#include "PCVampireInfo.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
LCServerList::LCServerList ()
	throw ()
{
	m_CurrentServerGroupID = 0;
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
LCServerList::~LCServerList ()
	throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_ServerGroupInfoList.empty() ) 
	{
		ServerGroupInfo * pServerGroupInfo = m_ServerGroupInfoList.front();
		SAFE_DELETE(pServerGroupInfo);
		m_ServerGroupInfoList.pop_front();
	}

	__END_CATCH
}


//----------------------------------------------------------------------
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//----------------------------------------------------------------------
void LCServerList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_CurrentServerGroupID );

	BYTE ListNum;

    // 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( ListNum );
	for( int i = 0; i < ListNum; i++ ) {
		ServerGroupInfo * pServerGroupInfo = new ServerGroupInfo();
		pServerGroupInfo->read( iStream );
		m_ServerGroupInfoList.push_back( pServerGroupInfo );
	}
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void LCServerList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_CurrentServerGroupID );

	BYTE ListNum = m_ServerGroupInfoList.size();
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( ListNum );

	for ( list<ServerGroupInfo*>:: const_iterator itr = m_ServerGroupInfoList.begin(); itr!= m_ServerGroupInfoList.end(); itr++) {
		(*itr)->write( oStream );
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCServerList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCServerListHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
PacketSize_t LCServerList::getPacketSize () const 
	throw ()
{
	__BEGIN_TRY

	// 리스트 인자의 갯수
	PacketSize_t PacketSize = szServerGroupID + szBYTE;

	for ( list< ServerGroupInfo* >::const_iterator itr = m_ServerGroupInfoList.begin() ; itr != m_ServerGroupInfoList.end() ; itr ++ ) {
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
string LCServerList::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "LCServerList( CurrentServerGroupID : " << (int)m_CurrentServerGroupID;
	for ( list< ServerGroupInfo* >::const_iterator itr = m_ServerGroupInfoList.begin() ; itr != m_ServerGroupInfoList.end() ; itr ++ ) {
		msg << (*itr)->toString();
	}
	msg << ")";

	return msg.toString();

	__END_CATCH
}
