////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradePrepare.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_PREPARE_H__
#define __CG_TRADE_PREPARE_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 교환 코드
////////////////////////////////////////////////////////////////////////////////

enum
{
	// 제일 처음 교환을 원하는 플레이어가 이 코드로 패킷을 날린다.
	CG_TRADE_PREPARE_CODE_REQUEST = 0,

	// 제일 처음 교환을 요청한 플레이어가 취소를 했다.
	CG_TRADE_PREPARE_CODE_CANCEL,

	// 교환을 요청받은 플레이어가 교환에 응할 경우
	CG_TRADE_PREPARE_CODE_ACCEPT,

	// 교환을 요청받은 플레이어가 교환에 응하지 않을 경우
	CG_TRADE_PREPARE_CODE_REJECT,

	// 교환을 요청받은 플레이어가 지금 교환을 할 수 없는 경우
	CG_TRADE_PREPARE_CODE_BUSY,

	CG_TRADE_PREPARE_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradePrepare;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradePrepare : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_TRADE_PREPARE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }
	string getPacketName() const throw() { return "CGTradePrepare"; }
	string toString() const throw();
	
public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode(void) const throw() { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // 교환을 원하는 상대방의 OID
	BYTE       m_Code;           // 교환 코드

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradePrepareFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradePrepareFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTradePrepare(); }
	string getPacketName() const throw() { return "CGTradePrepare"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_TRADE_PREPARE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradePrepareHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradePrepareHandler 
{
public:
	static void execute(CGTradePrepare* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeSlayer(CGTradePrepare* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeVampire(CGTradePrepare* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeOusters(CGTradePrepare* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeError(CGTradePrepare* pPacket, Player* player, BYTE ErrorCode) throw(ProtocolException, Error);
};

#endif
