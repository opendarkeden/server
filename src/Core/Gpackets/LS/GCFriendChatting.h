//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFriendChatting.h 
// Written By  : alivviva@gmail.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_FRIENDCHATTING_H__
#define __GC_FRIENDCHATTING_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCFriendChatting;
//
//
//////////////////////////////////////////////////////////////////////

enum
{
	////////CG////////////////
	CG_ADD_FRIEND=0,
	CG_MESSAGE,
	CG_UPDATE,
	CG_ADD_FRIEND_AGREE, 
	CG_ADD_FRIEND_REFUSE,
	MAX_CG,
	/////////GC////////////////
	GC_ADD_FRIEND_REQUEST,
	GC_ADD_FRIEND_OK,
	GC_ADD_FRIEND_REFUSE,
	GC_ADD_FRIEND_WAIT,
	GC_ADD_FRIEND_ERROR,
	GC_ADD_FRIEND_EXIST,
	GC_MESSAGE,
	GC_UPDATE,
	GC_NO_ONLINE,
	MAX_GC
};

class GCFriendChatting : public Packet {

public :
	GCFriendChatting();
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_FRIEND_CHATTING; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szDWORD + szBYTE + m_PlayerName.size() + szWORD + m_Message.size() + szBYTE + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "GCFriendChatting"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set sender's creature id
	DWORD getCommand() const throw() { return m_Command; }
	void setCommand(const DWORD & Command) throw() { m_Command = Command; }

	//get/set text color
	string getPlayerName() const throw() { return m_PlayerName; }
	void setPlayerName(const string& PlayerName ) throw() { m_PlayerName = PlayerName; }

	// get/set chatting message
	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	
	BYTE getIsBlack() const throw() { return m_IsBlack; }
	void setIsBlack(const BYTE& IsBlack) throw() { m_IsBlack = IsBlack; };

	BYTE getIsOnLine() const throw() { return m_IsOnLine; }
	void setIsOnLine(const BYTE& IsOnLine) throw() { m_IsOnLine = IsOnLine; };

private :
	
	// character's creature id
	DWORD m_Command;

	// chatting playername
	string m_PlayerName;		//max size 32
	
	// chatting message
	string m_Message;		//max size 512

	BYTE m_IsBlack;

	BYTE m_IsOnLine;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCSayFactory;
//
// Factory for GCSay
//
//////////////////////////////////////////////////////////////////////

class GCFriendChattingFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCFriendChatting(); }

	// get packet name
	string getPacketName() const throw() { return "GCFriendChatting"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_FRIEND_CHATTING; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSayPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szDWORD + szBYTE + 32 + szWORD + 512 + szBYTE + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFriendChattingHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCFriendChatting* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
