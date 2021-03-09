//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCSelectRankBonusFailed.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SELECT_RANK_BONUS_FAILED_H__
#define __GC_SELECT_RANK_BONUS_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusFailed;
//
//////////////////////////////////////////////////////////////////////

class GCSelectRankBonusFailed : public Packet 
{

public: 

	GCSelectRankBonusFailed() ;
	virtual ~GCSelectRankBonusFailed() ;

	
public:
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) ;
			
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SELECT_RANK_BONUS_FAILED; }
	
	// get packet size
	PacketSize_t getPacketSize() const  { return szDWORD + szBYTE; }
	
	// get packet's name
	string getPacketName() const  { return "GCSelectRankBonusFailed"; }
	
	// get packet's debug string
	string toString() const ;
	
	// get/set skill type
	DWORD getRankBonusType() const  { return m_RankBonusType; }
	void setRankBonusType(DWORD rankBonusType)  { m_RankBonusType = rankBonusType; }

	// get/set description
	BYTE getDesc(void) const  { return m_Desc;}
	void setDesc(BYTE desc)  { m_Desc = desc;}

private:

	DWORD 		m_RankBonusType;
	BYTE        m_Desc;       // 실패코드

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusFailedFactory;
//
// Factory for  GCSelectRankBonusFailed
//
//////////////////////////////////////////////////////////////////////

class  GCSelectRankBonusFailedFactory : public PacketFactory {

public :
	
	// constructor
	 GCSelectRankBonusFailedFactory()  {}
	
	// destructor
	virtual ~GCSelectRankBonusFailedFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSelectRankBonusFailed(); }

	// get packet name
	string getPacketName() const  { return "GCSelectRankBonusFailed"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SELECT_RANK_BONUS_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szDWORD + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCSelectRankBonusFailedHandler {

public :

	// execute packet's handler
	static void execute(GCSelectRankBonusFailed* pGCSelectRankBonusFailed, Player* pPlayer) ;

};

#endif	// __GC_LEARN_SKILL_FAILED_H__
