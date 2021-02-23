//--------------------------------------------------------------------------------
// 
// Filename    : UCUpdateList.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UC_UPDATE_LIST_H__
#define __UC_UPDATE_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "UpdateManager.h"

//--------------------------------------------------------------------------------
//
// class UCUpdateList;
//
//--------------------------------------------------------------------------------

class UCUpdateList : public Packet {

public :

	// constructor
	UCUpdateList () throw () : m_pUpdateManager(NULL) 
	{
		m_Old = false;
		m_pUpdateManager = new UpdateManager();
	}

	// destructor
	~UCUpdateList () throw ()
	{
		if ( m_pUpdateManager != NULL ) {
			delete m_pUpdateManager;
			m_pUpdateManager = NULL;
		}
	}


public :

	// 입력스트림(버퍼)으로부터 데이터를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error ) { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // 소켓으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( Socket * pSocket ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error ) { throw UnsupportedError(__PRETTY_FUNCTION__); }

	// 소켓으로 직접 패킷의 바이너리 이미지를 보낸다.
    void write ( Socket * pSocket ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_UC_UPDATE_LIST; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static UCUpdateListPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize () const throw () { return m_pUpdateManager->getSize() + ((m_Old)?0:szBYTE*10); }

	// get packet's max body size
	static PacketSize_t getPacketMaxSize () throw () { return UpdateManager::getMaxSize() + szBYTE*10; }
	
	// get packet's name
	string getPacketName () const throw () { return "UCUpdateList"; }
	
	// get packet's debug string
	string toString () const throw ();
	

public :

	// get/set update manager
	UpdateManager * getUpdateManager () throw () { return m_pUpdateManager; }
	void setUpdateManager ( UpdateManager * pUpdateManager ) throw () { m_pUpdateManager = pUpdateManager; }

	BYTE* getKeyArray() { return m_Key; }
	bool isOld() const { return m_Old; }
	void setOld( bool bOld = true ) { m_Old = bOld; }

	bool isFront() const { return m_Front; }
	void setFront( bool bFront = true ) { m_Front = bFront; }

private :

	// update manager
	UpdateManager * m_pUpdateManager;	
	BYTE m_Key[10];
	bool m_Old;
	bool m_Front;

};


//--------------------------------------------------------------------------------
//
// class UCUpdateListFactory;
//
// Factory for UCUpdateList
//
//--------------------------------------------------------------------------------

class UCUpdateListFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new UCUpdateList(); }

	// get packet name
	string getPacketName () const throw () { return "UCUpdateList"; }
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_UC_UPDATE_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () { return UpdateManager::getMaxSize() + szBYTE*10; }
	
};


//--------------------------------------------------------------------------------
//
// class UCUpdateListHandler;
//
//--------------------------------------------------------------------------------

class UCUpdateListHandler {

public :

	// execute packet's handler
	static void execute ( UCUpdateList * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
