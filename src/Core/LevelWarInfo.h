//--------------------------------------------------------------------------------
// 
// Filename    : LevelWarInfo.h 
// Written By  : 
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __LEVEL_WAR_LIST_H__
#define __LEVEL_WAR_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WarInfo.h"

//--------------------------------------------------------------------------------
//
// class WarInfo;
//
//--------------------------------------------------------------------------------

class LevelWarInfo : public WarInfo {

public :
	LevelWarInfo() {}
	~LevelWarInfo() {}
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	PacketSize_t getSize() const throw() 
	{ 
		return WarInfo::getSize() + szint;
	}

	static PacketSize_t getMaxSize() throw() 
	{
		return WarInfo::getMaxSize() + szint;
	}

	// get packet's debug string
	string toString() const throw();

public :
	WarType_t 			getWarType() const 			{ return WAR_LEVEL; }

	int 				getLevel() 				{ return m_Level; }
	void 				setLevel(int level) 	{ m_Level = level; }

	void	operator = (const LevelWarInfo& RWI)
	{
		m_StartTime = RWI.m_StartTime;
		m_RemainTime = RWI.m_RemainTime;
		m_Level = RWI.m_Level;
	}

private :
	int			m_Level;		// 몇 레벨 전쟁인가
};

#endif
