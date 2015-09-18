//////////////////////////////////////////////////////////////////////
// 
// Filename    : GameServerPlayer.h 
// Written by  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_PLAYER_H__
#define __GAME_SERVER_PLAYER_H__

#include "Types.h"
#include "Exception.h"
#include "Player.h"

class GameServerPlayer: public Player {
public:
    GameServerPlayer() throw(Error) {};
    GameServerPlayer(Socket * pSocket) throw(Error);
    virtual ~GameServerPlayer() throw(Error);

    virtual void processInput() throw(IOException, Error);
    virtual void processOutput() throw(IOException, Error);
    virtual void processCommand() throw(IOException, Error);
    
    virtual void sendPacket(Packet* pPacket) throw(ProtocolException, Error);

    // disconnect
    // 플레이어의 연결을 종료할 때, 상대편이 적절하게 로그아웃하지 않을 경우 소켓의 연결이 
    // 이미 끊겨 있으므로 disconnect(DISCONNECTED) 를 사용해서 연결을 종료해야 한다. 반면, 
    // 정당하게 로그아웃을 한 경우에는 disconnect(UNDISCONNECTED) 를 사용해야 한다.
    virtual void disconnect(bool bDisconnected = DISCONNECTED) throw(InvalidProtocolException, Error);
    
    void setSocket(Socket* pSocket) throw();

    // get/set player ID
    //string getID () const throw() { return m_ID; }
    //void setID (const string & id) throw() { m_ID = id; }

    virtual string toString() const throw(Error);
    
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
