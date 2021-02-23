//----------------------------------------------------------------------
// 
// Filename    : GGCommand.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GG_COMMAND_H__
#define __GG_COMMAND_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GGCommand;
//
// 로그인 서버에서 사용자가 게임 서버로 접속하려고 할 때, 로그인 서버는
// 그 게임 서버에게 어떤 주소에서 어떤 사용자가 어떤 크리처로 로그인할
// 것이다.. 라고 알려주는 패킷이다.
//
// *CAUTION*
//
// 굳이 크리처 이름이 필요한가? 하는 의문이 있을 수 있겠는데, 다음과 같은
// 경우를 고려했을때 필요하게 된다. 로그인 서버로부터 Slot3 캐릭터를 선택
// 해놓고, 실제로 게임 서버에 접속해서는 SLOT2 캐릭터를 로딩해달라고 할
// 수가 있는 것이다. 이를 막기 위해서, CLSelectPC로 선택한 캐릭터를 
// 게임 서버에게 알려줘야 하며, CGConnect 에서도 캐릭터 아이디를 포함해서
// 바로 로딩하도록 해야 한다.
//
//----------------------------------------------------------------------

class GGCommand : public DatagramPacket {

public :
	
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GG_COMMAND; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_Command.size();
	}

	// get packet name
	string getPacketName() const throw() { return "GGCommand"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set playerID
	const string& getCommand() const throw() { return m_Command; }
	void setCommand(const string& command) throw() { m_Command = command; }
	
private :

	string m_Command;
};


//////////////////////////////////////////////////////////////////////
//
// class GGCommandFactory;
//
// Factory for GGCommand
//
//////////////////////////////////////////////////////////////////////

class GGCommandFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GGCommand(); }

	// get packet name
	string getPacketName() const throw() { return "GGCommand"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GG_COMMAND; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GGCommandPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + 80;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GGCommandHandler;
//
//////////////////////////////////////////////////////////////////////

class GGCommandHandler {
	
public :

	// execute packet's handler
	static void execute(GGCommand* pPacket) throw(ProtocolException, Error);

};

#endif
