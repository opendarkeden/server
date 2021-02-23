//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNotifyWin.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NOTIFY_WIN_H__
#define __GC_NOTIFY_WIN_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWin;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

class GCNotifyWin : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_NOTIFY_WIN; }
	PacketSize_t getPacketSize() const throw() { return szDWORD + szBYTE + m_Name.size(); }
	string getPacketName() const throw() { return "GCNotifyWin"; }
	string toString() const throw();

	DWORD getGiftID() const throw() { return m_GiftID; }
	void setGiftID(DWORD gID) throw() { m_GiftID = gID; }

	string getName() const throw() { return m_Name; }
	void setName(const string & msg) throw() { m_Name = msg; }

private:
	DWORD		m_GiftID; // NPC's object id
	string		m_Name;  // chatting message
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWinFactory;
//////////////////////////////////////////////////////////////////////////////


class GCNotifyWinFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNotifyWin(); }
	string getPacketName() const throw() { return "GCNotifyWin"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NOTIFY_WIN; }
	PacketSize_t getPacketMaxSize() const throw() { return szDWORD + szBYTE + 2048 ; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWinHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNotifyWinHandler 
{
public:
	static void execute(GCNotifyWin* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
