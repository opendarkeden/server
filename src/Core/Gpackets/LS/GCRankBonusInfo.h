//--------------------------------------------------------------------------------
// 
// Filename    : GCRankBonusInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_RANK_BONUS_INFO_H__
#define __GC_RANK_BONUS_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Assert.h"

const DWORD EndOfRankBonus = 9999;


class GCRankBonusInfo : public Packet {

public :

	// constructor
	GCRankBonusInfo() throw();

	// destructor
	~GCRankBonusInfo() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RANK_BONUS_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + ( szDWORD * m_RankBonusInfoList.size() ); }

	// get packet name
	string getPacketName() const throw() { return "GCRankBonusInfo"; }
	
	// get packet's debug string
	string toString() const throw();

//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	BYTE getListNum() const throw() { return m_RankBonusInfoList.size(); }

    // add
	void addListElement( DWORD rankBonusType ) throw() { m_RankBonusInfoList.push_back( rankBonusType ); }
	
	// pop front Element in Status List
	DWORD popFrontListElement() throw()
	{
		if ( !m_RankBonusInfoList.empty() )
		{
			DWORD temp = m_RankBonusInfoList.front();
			m_RankBonusInfoList.pop_front();
			return temp;
		}
		else
			return EndOfRankBonus;
	}

private :

	// Rank Bonus List
	list<DWORD> m_RankBonusInfoList;

};


//--------------------------------------------------------------------------------
//
// class GCRankBonusInfoFactory;
//
// Factory for GCRankBonusInfo
//
//--------------------------------------------------------------------------------

class GCRankBonusInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRankBonusInfo(); }

	// get packet name
	string getPacketName() const throw() { return "GCRankBonusInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RANK_BONUS_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRankBonusInfoPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + ( szDWORD * 100 );
	}

};


//--------------------------------------------------------------------------------
//
// class GCRankBonusInfoHandler;
//
//--------------------------------------------------------------------------------

class GCRankBonusInfoHandler {

public :

	// execute packet's handler
	static void execute(GCRankBonusInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
