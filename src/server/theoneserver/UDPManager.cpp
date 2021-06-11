//////////////////////////////////////////////////////////////////////
//
// Filename    : UDPManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "UDPManager.h"
#include "Assert.h"

#include "Datagram.h"
#include "DatagramPacket.h"

#include <unistd.h>
//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
UDPManager::UDPManager () 
	throw (Error)
: m_pDatagramSocket(NULL)
{
	__BEGIN_TRY

	// create datagram server socket
	m_pDatagramSocket = new DatagramSocket(19982);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
UDPManager::~UDPManager () 
	throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pDatagramSocket);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void UDPManager::sendDatagram (Datagram* pDatagram)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY

    m_pDatagramSocket->send(pDatagram);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// send datagram packet to login server
//////////////////////////////////////////////////////////////////////
void UDPManager::sendPacket (const string& host , uint port , DatagramPacket* pPacket)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try 
	{
		// 데이터그램 객체를 하나 두고, 전송할 peer 의 호스트와 포트를 지정한다.
		Datagram datagram;

			
		datagram.setHost(host);
		datagram.setPort(port);

		// 데이터그램 패킷을 데이터그램에 집어넣는다.
		datagram.write(pPacket);
		
		// 데이터그램 소켓을 통해서 데이터그램을 전송한다.
		m_pDatagramSocket->send(&datagram);
	} 
	catch (Throwable & t) 
	{
        //cerr << "====================================================================" << endl;
		//cerr << t.toString() << endl;
		//cerr << "====================================================================" << endl;
	}

	__END_DEBUG
	__END_CATCH
}

// global variable definition
UDPManager* g_pUDPManager = NULL;
