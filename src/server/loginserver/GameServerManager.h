//////////////////////////////////////////////////////////////////////
//
// Filename    : GameServerManager.h
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_MANANGER_H__
#define __GAME_SERVER_MANANGER_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "DatagramSocket.h"

class Datagram;
class DatagramPacket;

class GameServerManager: public Thread {
public:
    GameServerManager() throw(Error);
    ~GameServerManager() throw(Error);

    void init() throw(Error) {}
    void stop() throw(Error);
    void run();

    void sendDatagram(Datagram * pDatagram) throw(ConnectException, Error);
    void sendPacket(string host, uint port, DatagramPacket * pPacket) throw(ConnectException, Error);

private:
    DatagramSocket * m_pDatagramSocket;
};

extern GameServerManager * g_pGameServerManager;
#endif
