/////////////////////////////////////////////////////////////////////////////
// Filename	: MPacketManager.cpp
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "MPacketManager.h"
#include "MPacketID.h"
#include "MPacketHandler.h"
#include "Assert.h"

// send 패킷
#include "PKTConnectAsk.h"
#include "PKTLogout.h"
#include "PKTUserInfo.h"
#include "PKTReceiveOK.h"
#include "PKTResult.h"
#include "PKTSError.h"

// receive 패킷
#include "PKTConnectAccept.h"
#include "PKTConnectAcceptHandler.h"
#include "PKTPowerPoint.h"
#include "PKTPowerPointHandler.h"
#include "PKTError.h"
#include "PKTErrorHandler.h"


// 패킷 ID 등록을 간단히 하기 위한 매크로
#define REGISTER_SEND_PACKET_ID( PACKET, PACKET_ID ) \
	MPacketID_t PACKET::getID() const { return PACKET_ID; }

// 패킷 핸들러 ID 등록을 간단히 하기 위한 매크로
#define REGISTER_RECV_PACKET_ID( PACKET, PACKET_ID ) \
	MPacketID_t PACKET::getID() const { return PACKET_ID; } \
	MPacketID_t PACKET##Handler::getID() const { return PACKET_ID; }

// 보내기용 패킷ID 등록
REGISTER_SEND_PACKET_ID( PKTConnectAsk,		PTC_CONNECT_ASK )
REGISTER_SEND_PACKET_ID( PKTLogout,			PTC_LOGOUT )
REGISTER_SEND_PACKET_ID( PKTUserInfo,		PTC_USERINFO )
REGISTER_SEND_PACKET_ID( PKTReceiveOK,		PTC_RECEIVE_OK )
REGISTER_SEND_PACKET_ID( PKTResult,			PTC_RESULT )
REGISTER_SEND_PACKET_ID( PKTSError,			PTC_ERROR )

// 받기용 패킷 ID 등록 및 핸들러 ID 등록
REGISTER_RECV_PACKET_ID( PKTConnectAccept,	PTS_CONNECT_ACCEPT )
REGISTER_RECV_PACKET_ID( PKTPowerPoint,		PTS_POWERPOINT )
REGISTER_RECV_PACKET_ID( PKTError,			PTS_ERROR )


// 내부 구현 데이터
struct MPacketManager::IMPL
{
	MPacket*		pCreators[PTC_MAX];
	MPacketHandler*	pHandlers[PTC_MAX];

	IMPL();
	~IMPL();

	// 패킷 생성자를 추가한다.
	void addCreator( MPacket* pPacket );

	// 패킷 핸들러를 추가한다.
	void addHandler( MPacketHandler* pHandler );
};


// 생성자
MPacketManager::MPacketManager()
	: m_pImpl( new IMPL )
{
	Assert( m_pImpl != NULL );
}

// 소멸자
MPacketManager::~MPacketManager()
{
	SAFE_DELETE( m_pImpl );
}

// 초기화
void MPacketManager::init()
{
	// 핸들러 및 크리에이터 추가
	m_pImpl->addCreator( new PKTConnectAccept );
	m_pImpl->addHandler( new PKTConnectAcceptHandler );
	m_pImpl->addCreator( new PKTPowerPoint );
	m_pImpl->addHandler( new PKTPowerPointHandler );
	m_pImpl->addCreator( new PKTError );
	m_pImpl->addHandler( new PKTErrorHandler );
}

// 패킷 생성자를 추가한다.
void MPacketManager::addCreator( MPacket* pPacket )
{
	Assert( pPacket != NULL );
	m_pImpl->addCreator( pPacket );
}

// 패킷 핸들러를 추가한다.
void MPacketManager::addHandler( MPacketHandler* pHandler )
{
	Assert( pHandler != NULL );
	m_pImpl->addHandler( pHandler );
}

// 새로운 패킷을 생성해서 반환한다.
MPacket* MPacketManager::createPacket( MPacketID_t ID ) const
{
	if ( ID < 0 || ID >= PTC_MAX )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::createPacket() out of ID" );
		Assert( false );
	}

	return m_pImpl->pCreators[ID]->create();
}

// 패킷을 실행한다.
void MPacketManager::execute( MPlayer* pPlayer, MPacket* pPacket )
{
	Assert( pPlayer != NULL );
	Assert( pPacket != NULL );

	MPacketID_t ID = pPacket->getID();

	if ( ID < 0 || ID >= PTC_MAX )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::createPacket() out of ID" );
		Assert( false );
	}

	if ( m_pImpl->pHandlers[ID] == NULL )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::execute() Handler is NULL" );
		Assert( false );
	}

	m_pImpl->pHandlers[ID]->execute( pPlayer, pPacket );
}

// 패킷을 실행한다.
bool MPacketManager::hasHandler( MPacketID_t ID ) const
{
	// 일단 범위 확인
	if ( ID < 0 || ID >= PTC_MAX )
	{
		return false;
	}

	// 핸들러가 있는지 확인
	if ( m_pImpl->pHandlers[ID] == NULL )
	{
		return false;
	}

	return true;
}

// 패킷의 크기를 반환한다.
MPacketSize_t MPacketManager::getPacketSize( MPacketID_t ID ) const
{
	if ( ID < 0 || ID >= PTC_MAX )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::createPacket() out of ID" );
		Assert( false );
	}

	return m_pImpl->pCreators[ID]->getSize();
}

// 생성자
MPacketManager::IMPL::IMPL()
{
	// 각 배열을 초기화한다.
	for ( MPacketID_t i = 0; i < PTC_MAX; ++i )
	{
		pCreators[i] = NULL;
		pHandlers[i] = NULL;
	}
}

// 소멸자
MPacketManager::IMPL::~IMPL()
{
	// 패킷 생성자 및 핸들러를 지운다.
	for ( MPacketID_t i = 0; i < PTC_MAX; ++i )
	{
		SAFE_DELETE( pCreators[i] );
		SAFE_DELETE( pHandlers[i] );
	}
}

// 패킷 생성자를 추가한다.
void MPacketManager::IMPL::addCreator( MPacket* pPacket )
{
	Assert( pPacket != NULL );

	// 중복 검사
	if ( pCreators[pPacket->getID()] != NULL )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::IMPL::addCreator() dup creator" );
		Assert( false );
	}
	
	// 생성자를 추가한다.
	pCreators[pPacket->getID()] = pPacket;
}

// 패킷 핸들러를 추가한다.
void MPacketManager::IMPL::addHandler( MPacketHandler* pHandler )
{
	Assert( pHandler != NULL );

	// 중복 검사
	if ( pHandlers[pHandler->getID()] != NULL )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::IMPL::addHandler() dup handler" );
		Assert( false );
	}

	// 핸들러를 추가한다.
	pHandlers[pHandler->getID()] = pHandler;
}

// global variable
MPacketManager* g_pMPacketManager = NULL;

