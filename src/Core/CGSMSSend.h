//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSMSSend.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SMS_SEND_H__
#define __CG_SMS_SEND_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#include <list>
#include <string>

#define MAX_NUMBER_LENGTH	11
#define MAX_RECEVIER_NUM	5
#define MAX_MESSAGE_LENGTH	80

//////////////////////////////////////////////////////////////////////
//
// class CGSMSSend;
//
//////////////////////////////////////////////////////////////////////

class CGSMSSend : public Packet {

public:
    CGSMSSend() {};
    virtual ~CGSMSSend() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_SMS_SEND; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "CGSMSSend"; }
	string toString() const ;
	
public:
	list<string>& getNumbersList() { return m_Numbers; }

	const string&	getCallerNumber() const { return m_CallerNumber; }
	void			setCallerNumber(const string& Num ) { m_CallerNumber = Num; }

	const string&	getMessage() const { return m_Message; }
	void			setMessage(const string& msg ) { m_Message = msg; }

private:
	list<string>	m_Numbers;
	string			m_CallerNumber;
	string			m_Message;
};


//////////////////////////////////////////////////////////////////////
//
// class CGSMSSendFactory;
//
// Factory for CGSMSSend
//
//////////////////////////////////////////////////////////////////////

class CGSMSSendFactory : public PacketFactory {
public:
	Packet* createPacket()  { return new CGSMSSend(); }
	string getPacketName() const  { return "CGSMSSend"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SMS_SEND; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + (szBYTE + MAX_NUMBER_LENGTH)*MAX_RECEVIER_NUM + szBYTE + MAX_RECEVIER_NUM + szBYTE + MAX_MESSAGE_LENGTH; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSMSSendHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSMSSendHandler {
public:
	static void execute(CGSMSSend* pPacket, Player* player) ;
};

#endif
