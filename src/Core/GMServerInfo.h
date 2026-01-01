//----------------------------------------------------------------------
// 
// Filename    : GMServerInfo.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GM_SERVER_INFO_H__
#define __GM_SERVER_INFO_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"

typedef struct _ZONEUSERDATA {
	ZoneID_t ZoneID;
	WORD UserNum;

} ZONEUSERDATA;

//----------------------------------------------------------------------
//
// class GMServerInfo;
//
// �α��� �������� ����ڰ� ���� ������ �����Ϸ��� �� ��, �α��� ������
// �� ���� �������� � �ּҿ��� � ����ڰ� � ũ��ó�� �α�����
// ���̴�.. ��� �˷��ִ� ��Ŷ�̴�.
//
// *CAUTION*
//
// ���� ũ��ó �̸��� �ʿ��Ѱ�? �ϴ� �ǹ��� ���� �� �ְڴµ�, ������ ����
// ��츦 ���������� �ʿ��ϰ� �ȴ�. �α��� �����κ��� Slot3 ĳ���͸� ����
// �س���, ������ ���� ������ �����ؼ��� SLOT2 ĳ���͸� �ε��ش޶�� ��
// ���� �ִ� ���̴�. �̸� ���� ���ؼ�, CLSelectPC�� ������ ĳ���͸� 
// ���� �������� �˷���� �ϸ�, CGConnect ������ ĳ���� ���̵� �����ؼ�
// �ٷ� �ε��ϵ��� �ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class GMServerInfo : public DatagramPacket {

public :
	GMServerInfo() ;
	~GMServerInfo() noexcept;
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GM_SERVER_INFO; }
	
	// get packet name
	string getPacketName() const  { return "GMServerInfo"; }
	
	PacketSize_t getPacketSize () const  { return szWorldID + szBYTE + m_ZoneCount*(szBYTE+szDWORD); }

	// get packet's debug string
	string toString() const ;

public:

	// get/set playerID
	WorldID_t getWorldID() const  { return m_WorldID; }
	void setWorldID(WorldID_t WorldID)  { m_WorldID= WorldID; }
	
	// get/set playerID
	BYTE getServerID() const  { return m_ServerID; }
	void setServerID(BYTE ServerID)  { m_ServerID= ServerID; }
	
	BYTE getZoneUserCount(void) const  { return m_ZoneCount; }

	void addZoneUserData(ZoneID_t ZoneID, DWORD value) ;

	void popZoneUserData(ZONEUSERDATA& rData) ;

	void clearList(void)  { m_ZoneCount = 0; m_ZoneUserList.clear(); }

private :

	// WorldID
	WorldID_t m_WorldID;

	// ServerID
	BYTE m_ServerID;

	BYTE            m_ZoneCount;
	list<ZONEUSERDATA> m_ZoneUserList;

	// Ŭ���̾�Ʈ�� IP

};


//////////////////////////////////////////////////////////////////////
//
// class GMServerInfoFactory;
//
// Factory for GMServerInfo
//
//////////////////////////////////////////////////////////////////////

class GMServerInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GMServerInfo(); }

	// get packet name
	string getPacketName() const  { return "GMServerInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GM_SERVER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GMServerInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const  { return szWorldID + szBYTE + 255*(szBYTE+szDWORD); }

};


//////////////////////////////////////////////////////////////////////
//
// class GMServerInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GMServerInfoHandler {
	
public :

	// execute packet's handler
	static void execute(GMServerInfo* pPacket) ;

};

#endif
