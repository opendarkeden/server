////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeMoney.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_MONEY_H__
#define __GC_TRADE_MONEY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 교환 코드
////////////////////////////////////////////////////////////////////////////////

enum
{
	// 상대방이 교환할 돈의 액수를 늘렸다.
	GC_TRADE_MONEY_INCREASE = 0,

	// 상대방이 교환할 돈의 액수를 줄였다.
	GC_TRADE_MONEY_DECREASE,

	// 실제로 인벤토리에서 빼낸 금액
	GC_TRADE_MONEY_INCREASE_RESULT,

	// 실제로 인벤토리에다 더한 금액
	GC_TRADE_MONEY_DECREASE_RESULT
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoney;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoney : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_MONEY; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szGold + szBYTE ; }
	string getPacketName() const throw() { return "GCTradeMoney"; }
	string toString() const throw();

public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	Gold_t getAmount() const throw() { return m_Gold; }
	void setAmount(Gold_t gold) throw() { m_Gold = gold; }

	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // 교환을 원하는 상대방의 ObjectID
	Gold_t     m_Gold;           // 원하는 액수
	BYTE       m_Code;           // 코드

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoneyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoneyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeMoney(); }
	string getPacketName() const throw() { return "GCTradeMoney"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_MONEY; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szGold + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoneyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoneyHandler 
{
public:
	static void execute(GCTradeMoney* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
