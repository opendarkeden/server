//----------------------------------------------------------------------
//
// Filename    : PacketValidator
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PACKET_VALIDATOR_H__
#define __PACKET_VALIDATOR_H__

// include files
#include "PacketIDSet.h"
#include "PlayerStatus.h"
#include <vector>

//----------------------------------------------------------------------
//
// class PacketValidator;
//
// �÷��̾��� Ư�� ���¿��� ���Ǵ� ��Ŷ���� ����Ʈ�� ������.
// XXXPlayer::processCommand() ���� ��Ŷ ���̵� ������ ���
// �� ���̵� �÷��̾��� ���¿� ���� �����غ���. �̶� ������
// ��� ó���ϸ� ������ Ʋ���� ������ �����ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class PacketValidator {

public :

	// constructor
	PacketValidator () ;

	// destructor
	~PacketValidator () noexcept;

	// init
	void init () ;

	// add packet id set
	void addPacketIDSet (PlayerStatus playerStatus, PacketIDSet* pPacketID);

	// delete packet id
	void deletePacketIDSet (PlayerStatus playerStatus, PacketIDSet* pPacketID);

	// is valid packet?
	bool isValidPacketID (PlayerStatus playerStatus, PacketID_t packetID);

	// get debug string
	string toString () const ;

private :

	vector< PacketIDSet* > m_PacketIDSets;

};

//----------------------------------------------------------------------
// global variable declaration
//----------------------------------------------------------------------
extern PacketValidator* g_pPacketValidator;

#endif
