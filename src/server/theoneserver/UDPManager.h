//////////////////////////////////////////////////////////////////////////////
// Filename    : UDPManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __UDP_MANAGER_H__
#define __UDP_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "DatagramSocket.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class UDPManager;
//
// 로그인 서버와의 통신을 전담하는 쓰레드이다.
// 내부에 데이터그램 서버소켓을 하나 가지고 블로킹 기반으로 동작한다.
//////////////////////////////////////////////////////////////////////////////

class UDPManager 
{
public:
	UDPManager() throw(Error);
	~UDPManager() throw(Error);

public:
	void sendDatagram(Datagram* pDatagram) throw(ProtocolException, Error);

	void sendPacket(const string& host, uint port, DatagramPacket* pPacket) throw(ProtocolException, Error);


private:
	DatagramSocket* m_pDatagramSocket; // UDP 서버 소켓

};

// global variable declaration
extern UDPManager* g_pUDPManager;

#endif
