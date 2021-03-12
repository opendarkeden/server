//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBuyFail.h 
// Written By  : excel96
// Description :
// 플레이어가 상점에서 아이템을 구입하려고 했는데, 
// 정상적인 구매가 실패했을 경우에 플레이어에게 보내는 패킷.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOP_BUY_FAIL_H__
#define __GC_SHOP_BUY_FAIL_H__

#include "Packet.h"
#include "PacketFactory.h"

enum GCShopBuyFailCode
{
	// 돈이 모자란다. 
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY = 0,

	// 자리가 모자란다.
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE,

	// NPC가 존재하지 않는다.
	GC_SHOP_BUY_FAIL_NPC_NOT_EXIST,

	// NPC라고 보내온 놈이 NPC가 아니다.
	GC_SHOP_BUY_FAIL_NOT_NPC,

	// 지정한 위치에 아이템이 존재하지 않는다.
	GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST,

	GC_SHOP_BUY_FAIL_NOT_ENOUGH_BLACK_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_RED_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_BLUE_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_GREEN_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_CYAN_STAR,

	GC_SHOP_BUY_FAIL_MAX
};

const string GCShopBuyFailCode2String[] =
{
	"NOT_ENOUGH_MONEY",
	"NOT_ENOUGH_SPACE",
	"NPC_NOT_EXIST",
	"NOT_NPC",
	"ITEM_NOT_EXIST",
	"NOT_ENOUGH_BLACK_STAR",
	"NOT_ENOUGH_RED_STAR",
	"NOT_ENOUGH_BLUE_STAR",
	"NOT_ENOUGH_GREEN_STAR",
	"NOT_ENOUGH_CYAN_STAR",
	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyFail;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyFail : public Packet 
{
public:
	GCShopBuyFail();
	~GCShopBuyFail();

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SHOP_BUY_FAIL; }
	PacketSize_t getPacketSize() const  { return szObjectID;}
	string getPacketName() const  { return "GCShopBuyFail"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	BYTE getCode(void) const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

	uint getAmount(void) const { return m_Amount; }
	void setAmount(uint amount) { m_Amount = amount; }

private :
	ObjectID_t m_ObjectID;
	BYTE       m_Code;
	uint       m_Amount;
};

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyFailFactory;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyFailFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCShopBuyFail(); }
	string getPacketName() const  { return "GCShopBuyFail"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOP_BUY_FAIL; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyFailHandler;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyFailHandler 
{
public:
	static void execute(GCShopBuyFail* pPacket, Player* pPlayer) ;
};

#endif
