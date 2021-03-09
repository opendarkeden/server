//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCSelectRankBonusOK.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SELECT_RANK_BONUS_OK_H__
#define __GC_SELECT_RANK_BONUS_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusOK;
//
//////////////////////////////////////////////////////////////////////

class GCSelectRankBonusOK : public Packet {

public :
	
	// constructor
	GCSelectRankBonusOK() ;
	
	// destructor
	~GCSelectRankBonusOK() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SELECT_RANK_BONUS_OK; }
	
	// get packet size
	PacketSize_t getPacketSize() const  { return szDWORD; }
	
	// get packet's name
	string getPacketName() const  { return "GCSelectRankBonusOK"; }
	
	// get packet's debug string
	string toString() const ;
	
	// get/set m_RankBonusType
	DWORD getRankBonusType() const  { return m_RankBonusType; }
	void setRankBonusType(DWORD rankBonusType)  { m_RankBonusType = rankBonusType; }

private : 

	// RankBonusType
	DWORD m_RankBonusType;
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusOKFactory;
//
// Factory for  GCSelectRankBonusOK
//
//////////////////////////////////////////////////////////////////////

class  GCSelectRankBonusOKFactory : public PacketFactory {

public :
	
	// constructor
	 GCSelectRankBonusOKFactory()  {}
	
	// destructor
	virtual ~GCSelectRankBonusOKFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSelectRankBonusOK(); }

	// get packet name
	string getPacketName() const  { return "GCSelectRankBonusOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SELECT_RANK_BONUS_OK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szDWORD; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCSelectRankBonusOKHandler {

public :

	// execute packet's handler
	static void execute(GCSelectRankBonusOK* pGCSelectRankBonusOK, Player* pPlayer) ;

};

#endif
