//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseMessageItemFromInventory.h 
// Written By  : excel96
// Description : 
// 인벤토리 안의 아이템을 사용할 때, 클라이언트가 X, Y 및 ObjectID를
// 보내면 아이템 클래스에 따라서, 서버가 이에 맞는 코드를 처리한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_MESSAGE_ITEM_FROM_INVENTORY_H__
#define __CG_USE_MESSAGE_ITEM_FROM_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "CGUseItemFromInventory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventory : public CGUseItemFromInventory 
{
public:
    void read(SocketInputStream & iStream);
    void write(SocketOutputStream & oStream) const;
	void execute(Player* pPlayer);
	PacketID_t getPacketID() const  { return PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketSize() const  
	{ 
		return CGUseItemFromInventory::getPacketSize() 
				+ szBYTE + m_Message.size(); 
	}
	string getPacketName() const  { return "CGUseMessageItemFromInventory"; }
	string toString() const ;
	
public:
	const string& getMessage() const  { return m_Message; }
	void setMessage(const string& msg)  { m_Message = msg; }

private:
	string m_Message;
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventoryFactory : public CGUseItemFromInventoryFactory 
{
public:
	Packet* createPacket()  { return new CGUseMessageItemFromInventory(); }
	string getPacketName() const  { return "CGUseMessageItemFromInventory"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketMaxSize() const  
	{ 
		return CGUseItemFromInventoryFactory::getPacketMaxSize() 
				+ szBYTE + 128; 
	}
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventoryHandler 
{
public:
	static void execute(CGUseMessageItemFromInventory* pPacket, Player* player) ;

protected:
	static void executeEventTree(CGUseMessageItemFromInventory* pPacket, Player* player) ;
	// add by Coffee
	static void executeEventFromMessage(CGUseMessageItemFromInventory* pPacket, Player* player) ;
};

#endif
