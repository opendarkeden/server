//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMiniGameScores.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MINI_GAME_SCORES_H__
#define __GC_MINI_GAME_SCORES_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "Assert.h"

#include <list>

enum GameType
{
	GAME_MINE = 0,
	GAME_NEMO,
	GAME_PUSH,
	GAME_ARROW
};

//////////////////////////////////////////////////////////////////////////////
// class GCMiniGameScores;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCMiniGameScores : public Packet 
{
public:
	GCMiniGameScores() throw();
	~GCMiniGameScores() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_MINI_GAME_SCORES; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCMiniGameScores"; }
	string toString() const throw();

public:
	BYTE getGameType() const { return m_GameType; }
	void setGameType( GameType type ) { m_GameType = (BYTE)type; }

	BYTE getLevel() const { return m_Level; }
	void setLevel( BYTE level ) { m_Level = (BYTE)level; }

	const pair<string,WORD> popScore() { pair<string,WORD> ret = m_Scores.front(); m_Scores.pop_front(); return ret; }
	void addScore(const string& name, WORD score) { m_Scores.push_back( pair<string,WORD>(name,score) ); }
	list<pair<string,WORD> >::size_type getSize() const { return m_Scores.size(); }

private:
	BYTE m_GameType;
	BYTE m_Level;
	list<pair<string,WORD> > m_Scores;
};


//////////////////////////////////////////////////////////////////////////////
// class GCMiniGameScoresFactory;
//////////////////////////////////////////////////////////////////////////////

class GCMiniGameScoresFactory : public PacketFactory 
{
public :
	GCMiniGameScoresFactory() throw() {}
	virtual ~GCMiniGameScoresFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCMiniGameScores(); }
	string getPacketName() const throw() { return "GCMiniGameScores"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MINI_GAME_SCORES; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szBYTE + szBYTE + (szWORD+21) * 10; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCMiniGameScoresHandler;
//////////////////////////////////////////////////////////////////////////////

class GCMiniGameScoresHandler 
{
public:
	static void execute(GCMiniGameScores* pGCMiniGameScores, Player* pPlayer) throw(Error);

};

#endif
