////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeError.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_ERROR_H__
#define __GC_TRADE_ERROR_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 에러 코드
////////////////////////////////////////////////////////////////////////////////

enum
{
	// 교환을 요구한 대상이 존재하지 않는다
	GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST = 0,

	// 교환을 요구한 대상이 다른 종족이다
	GC_TRADE_ERROR_CODE_RACE_DIFFER,

	// 교환을 하려고 하는 곳이 안전 지대가 아니다.
	GC_TRADE_ERROR_CODE_NOT_SAFE,

	// 모터사이클을 탄 채로 교환을 시도하고 있다.
	GC_TRADE_ERROR_CODE_MOTORCYCLE,

	// 늑대나 박쥐 상태에서는 교환을 할 수 없다.
	GC_TRADE_ERROR_CODE_BAT_OR_WOLF,

	// 교환 중이면서 다시 교환을 하려고 한다
	GC_TRADE_ERROR_CODE_ALREADY_TRADING,

	// 교환 중이 아닌데, 교환 관련 패킷이 날아왔다.
	GC_TRADE_ERROR_CODE_NOT_TRADING,

	// 교환 대상에 더하려고 하는 아이템을 가지고 있지 않다
	GC_TRADE_ERROR_CODE_ADD_ITEM,

	// 교환 대상에서 빼려고 하는 아이템을 가지고 있지 않다
	GC_TRADE_ERROR_CODE_REMOVE_ITEM,

	// 교환 대상에 더하려고 하는 돈을 가지고 있지 않다.
	GC_TRADE_ERROR_CODE_INCREASE_MONEY,

	// 교환 대상에서 빼려고 하는 돈을 가지고 있지 않다.
	GC_TRADE_ERROR_CODE_DECREASE_MONEY,

	// 교환을 했는데, 자리가 모자라서 실패했다
	GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE,

	// 교환을 했는데, 선물 상자 교환 조건 때문에 실패했다
	GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX,

	// 알 수 없는 에러이다...
	GC_TRADE_ERROR_CODE_UNKNOWN,

	GC_TRADE_ERROR_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeError;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeError : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_ERROR; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE ; }
	string getPacketName() const throw() { return "GCTradeError"; }
	string toString() const throw();

public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // 교환의 대상 아이디
	BYTE       m_Code;           // 코드

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeErrorFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeErrorFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeError(); }
	string getPacketName() const throw() { return "GCTradeError"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_ERROR; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeErrorHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeErrorHandler 
{
public:
	static void execute(GCTradeError* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
