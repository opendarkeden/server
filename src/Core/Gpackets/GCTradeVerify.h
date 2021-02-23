////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeVerify.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_VERIFY_H__
#define __GC_TRADE_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 에러 코드
////////////////////////////////////////////////////////////////////////////////

enum
{
	// 교환 대상으로 아이템을 추가하는 것을 인증
	GC_TRADE_VERIFY_CODE_ADD_ITEM_WHEN_ACCEPT,

	// 교환 대상에서 아이템을 제거하는 것을 인증
	GC_TRADE_VERIFY_CODE_REMOVE_ITEM,

	// 교환 대상에서 돈을 추가하는 것을 인증
	GC_TRADE_VERIFY_CODE_MONEY_INCREASE,

	// 교환 대상에서 돈을 제거하는 것을 인증
	GC_TRADE_VERIFY_CODE_MONEY_DECREASE,

	// 교환 성립을 확인하는 것을 인증
	GC_TRADE_VERIFY_CODE_FINISH_ACCEPT,

	// 교환 성립을 취소하는 것을 인증
	GC_TRADE_VERIFY_CODE_FINISH_REJECT,

	// 교환 성립을 재고려하는 것을 인증
	GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER,

	// 교환을 하고 있을 때 마우스에 인벤토리로 아이템을 옮기는 것을 검증
	GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_OK,
	GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_FAIL,

	// 교환을 하고 있을 때 인벤토리에서 마우스로 아이템을 옮기는 것을 검증
	GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_OK,
	GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_FAIL,

	// 현재로서는 선물 상자인 경우...
	GC_TRADE_VERIFY_CODE_ADD_ITEM_OK,
	GC_TRADE_VERIFY_CODE_ADD_ITEM_FAIL,

	// 에러닷.
	GC_TRADE_VERIFY_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeVerify;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeVerify : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_VERIFY; }
	PacketSize_t getPacketSize() const throw() { return szBYTE ; }
	string getPacketName() const throw() { return "GCTradeVerify"; }
	string toString() const throw();

public:
	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	BYTE       m_Code;           // 코드

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeVerifyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeVerify(); }
	string getPacketName() const throw() { return "GCTradeVerify"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_VERIFY; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeVerifyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeVerifyHandler 
{
public:
	static void execute(GCTradeVerify* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
