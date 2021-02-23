//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDisplayItem.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DISPLAY_ITEM_H__
#define __CG_DISPLAY_ITEM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGDisplayItem;
//
//////////////////////////////////////////////////////////////////////

class CGDisplayItem : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_DISPLAY_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szCoordInven + szCoordInven + szObjectID + szGold + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "CGDisplayItem"; }

	// get packet's debug string
	string toString() const throw();

	CoordInven_t	getX() const { return m_X; }
	CoordInven_t	getY() const { return m_Y; }
	void			setXY(CoordInven_t x, CoordInven_t y) { m_X = x; m_Y = y; }

	ObjectID_t		getItemObjectID() const { return m_ItemObjectID; }
	void			setItemObjectID(ObjectID_t oid) { m_ItemObjectID = oid; }

	Gold_t			getPrice() const { return m_Price; }
	void			setPrice(Gold_t price) { m_Price = price; }

	BYTE			getIndex() const { return m_Index; }
	void			setIndex(BYTE index) { m_Index = index; }
private :

	CoordInven_t	m_X, m_Y;
	ObjectID_t		m_ItemObjectID;
	Gold_t			m_Price;
	BYTE			m_Index;
};


//////////////////////////////////////////////////////////////////////
//
// class CGDisplayItemFactory;
//
// Factory for CGDisplayItem
//
//////////////////////////////////////////////////////////////////////

class CGDisplayItemFactory : public PacketFactory {

public:
	
	// constructor
	CGDisplayItemFactory() throw() {}
	
	// destructor
	virtual ~CGDisplayItemFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGDisplayItem(); }

	// get packet name
	string getPacketName() const throw() { return "CGDisplayItem"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_DISPLAY_ITEM; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szCoordInven + szCoordInven + szObjectID + szGold + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGDisplayItemHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDisplayItemHandler {

public:

	// execute packet's handler
	static void execute(CGDisplayItem* pCGDisplayItem, Player* pPlayer) throw(Error);

};

#endif
