//////////////////////////////////////////////////////////////////////
//
// Filename    : GameServerPlayer.h
// Written by  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_PLAYER_H__
#define __GAME_SERVER_PLAYER_H__

// include files
#include "Exception.h"
#include "Player.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////
//
// class GameServerPlayer
//
//////////////////////////////////////////////////////////////////////

class GameServerPlayer : public Player {
public:
    // constructor
    GameServerPlayer() noexcept(false);
    GameServerPlayer(Socket* pSocket);

    // destructor
    virtual ~GameServerPlayer();

    virtual void processInput() noexcept(false);

    virtual void processOutput() noexcept(false);

    // parse packet and execute handler for the packet
    virtual void processCommand() noexcept(false);

    // send packet to player's output buffer
    virtual void sendPacket(Packet* pPacket) noexcept(false);

    // disconnect
    // �÷��̾��� ������ ������ ��, ������� �����ϰ�
    // �α׾ƿ����� ���� ��� ������ ������ �̹� ���� �����Ƿ� disconnect(DISCONNECTED) �� ����ؼ� ������ �����ؾ�
    // �Ѵ�. �ݸ�, �����ϰ� �α׾ƿ��� �� ��쿡�� disconnect(UNDISCONNECTED) �� ����ؾ�
    // �Ѵ�.
    virtual void disconnect(bool bDisconnected = DISCONNECTED) noexcept(false);

    // get/set socket
    // Socket* getSocket () throw () { return m_pSocket; }
    void setSocket(Socket* pSocket) noexcept;

    // get/set player ID
    // string getID () const throw () { return m_ID; }
    // void setID (const string & id) throw () { m_ID = id; }

    // get debug string
    virtual string toString() const noexcept(false);

protected:
    /*
    // player id
    string m_ID;

    // TCP client socket
    Socket* m_pSocket;

    // buffered socket input stream
    SocketInputStream* m_pInputStream;

    // buffered socket output stream
    SocketOutputStream* m_pOutputStream;
    */
};

#endif
