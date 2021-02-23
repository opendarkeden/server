////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradePrepare.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_PREPARE_H__
#define __GC_TRADE_PREPARE_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 교환 코드
////////////////////////////////////////////////////////////////////////////////

enum
{
	// 제일 처음 교환을 요청받은 플레이어에게 보내주는 코드
	GC_TRADE_PREPARE_CODE_REQUEST = 0,

	// 제일 처음 교환을 요청받은 플레이어가 취소했을 경우에 보내주는 코드
	GC_TRADE_PREPARE_CODE_CANCEL,

	// 교환을 요청받은 플레이어가 응했을 경우에, 요청자에게 보내준다.
	GC_TRADE_PREPARE_CODE_ACCEPT,

	// 교환을 요청받은 플레이어가 거부했을 경우에, 요청자에게 보내준다.
	GC_TRADE_PREPARE_CODE_REJECT,

	// 교환을 요청받은 플레이어가 현재 교환 중이다.
	GC_TRADE_PREPARE_CODE_BUSY,

	GC_TRADE_PREPARE_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepare;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepare : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_PREPARE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }
	string getPacketName() const throw() { return "GCTradePrepare"; }
	string toString() const throw();

public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private :
	ObjectID_t m_TargetObjectID; // 교환을 원하는 상대방의 OID
	BYTE       m_Code;           // 교환 코드

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradePrepare(); }
	string getPacketName() const throw() { return "GCTradePrepare"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_PREPARE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareHandler 
{
public:
	static void execute(GCTradePrepare* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
