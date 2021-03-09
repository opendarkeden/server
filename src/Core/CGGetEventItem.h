////////////////////////////////////////////////////////////////////////////////
// Filename    : CGGetEventItem.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_GET_EVENT_ITEM_H__
#define __CG_GET_EVENT_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 기부 종류
////////////////////////////////////////////////////////////////////////////////
enum EventType
{
	EVENT_TYPE_200501_COMBACK_ITEM = 0,			// 돌아온 사용자 링 아이템 주기 이벤트
	EVENT_TYPE_200501_COMBACK_PREMIUM_ITEM,		// 돌아온 사용자 결제 시 아이템 주기 이벤트
	EVENT_TYPE_200501_COMBACK_RECOMMEND_ITEM,	// 돌아온 사용자 결제 시 추천 받은 자 아이템 주기 이벤트

	EVENT_TYPE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGGetEventItem
//
////////////////////////////////////////////////////////////////////////////////
class CGGetEventItem : public Packet 
{
public:
    CGGetEventItem() {};
    ~CGGetEventItem() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_GET_EVENT_ITEM; }
	PacketSize_t getPacketSize() const  { return szBYTE; }
	string getPacketName() const  { return "CGGetEventItem"; }
	string toString() const ;
	
public:
	// get / set Event Type
	BYTE getEventType() const { return m_EventType; }
	void setEventType(BYTE eventType ) { m_EventType = eventType; }

private:
	BYTE		m_EventType;		// 이벤트 종류
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGGetEventItemFactory
//
////////////////////////////////////////////////////////////////////////////////

class CGGetEventItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGGetEventItem(); }
	string getPacketName() const  { return "CGGetEventItem"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_GET_EVENT_ITEM; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGGetEventItemHandler
//
////////////////////////////////////////////////////////////////////////////////
class CGGetEventItemHandler 
{
public:
	static void execute(CGGetEventItem* pPacket, Player* player) ;

#ifdef __GAME_SERVER__
	static void executeCombackItem(CGGetEventItem* pPacket, Player* pPlayer) ;
	static void executeCombackPremiumItem(CGGetEventItem* pPacket, Player* pPlayer) ;
	static void executeCombackRecommendItem(CGGetEventItem* pPacket, Player* pPlayer) ;
#endif
};

#endif

