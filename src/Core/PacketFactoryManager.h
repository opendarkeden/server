//////////////////////////////////////////////////////////////////////
// 
// Filename    : PacketFactoryManager.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __PACKET_FACTORY_MANAGER_H__
#define __PACKET_FACTORY_MANAGER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class PacketFactoryManager
//
//////////////////////////////////////////////////////////////////////

class PacketFactoryManager {

public :
	
	// constructor
	PacketFactoryManager () ;
	
	// destructor
	~PacketFactoryManager () noexcept;

	// ��Ŷ���丮�Ŵ����� �ʱ�ȭ�Ѵ�.
	// ���Ӽ�����ü�� init()���� ȣ��ȴ�.
	void init () ;
	
	// ���丮 ��ü�� Ư�� �ε����� �߰��Ѵ�.
	void addFactory (PacketFactory* pFactory) ;
	
	// ��Ŷ���̵�� ��Ŷ��ü�� �����Ѵ�.
	Packet* createPacket (PacketID_t packetID);

	// Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
	string getPacketName (PacketID_t packetID);

	// Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
	PacketSize_t getPacketMaxSize (PacketID_t packetID);

	// get debug string
	string toString () const ;

private :
	
	// ��Ŷ���丮�� �迭
	PacketFactory ** m_Factories;
	
	// ��Ŷ���丮�迭�� ũ��
	ushort m_Size;

};

extern PacketFactoryManager* g_pPacketFactoryManager;

#endif
