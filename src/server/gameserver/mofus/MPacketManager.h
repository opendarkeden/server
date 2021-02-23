/////////////////////////////////////////////////////////////////////////////
// Filename	: MPacketManager.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_MANAGER_H__
#define __MPACKET_MANAGER_H__

// include files
#include "MPacket.h"

// forward declaration
class MPlayer;
class MPacketHandler;


// class MPacketManager
class MPacketManager
{
public:
	MPacketManager();
	~MPacketManager();

public:
	void init();

public:
	// 패킷 생성자를 추가한다.
	void addCreator( MPacket* pPacket );

	// 패킷 핸들러를 추가한다.
	void addHandler( MPacketHandler* pHandler );

public:
	// 새로운 패킷을 생성해서 반환한다.
	MPacket* createPacket( MPacketID_t ID ) const;

	// 패킷의 핸들러를 실행한다.
	void execute( MPlayer* pPlayer, MPacket* pPacket );

	// 패킷의 핸들러가 있는지 확인한다.
	bool hasHandler( MPacketID_t ID ) const;

	// 패킷의 크기를 반환한다.
	MPacketSize_t getPacketSize( MPacketID_t ID ) const;

private:
	// 내부 구현 데이터
	struct IMPL;
	IMPL* m_pImpl;
};


// global variable
extern MPacketManager* g_pMPacketManager;

#endif

