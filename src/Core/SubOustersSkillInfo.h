//----------------------------------------------------------------------
//
// Filename    : SubOustersSkillInfo.h
// Written By  :
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_OUSTERS_SKILL_INFO_H__
#define __SUB_OUSTERS_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class SubOustersSkillInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get size of object
	uint getSize () const throw () { return szSkillType + szTurn + szTurn; }
	// get max size of object
	static uint getMaxSize () throw () { return szSkillType + szTurn + szTurn; }

	// get debug string
	string toString () const throw ();

public :

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get /set Skill ExpLevel
	ExpLevel_t getExpLevel() const throw() { return m_ExpLevel; }
	void setExpLevel( ExpLevel_t ExpLevel ) throw() { m_ExpLevel = ExpLevel; }

	// get / set Turn
	Turn_t getSkillTurn() const throw() { return m_Interval ; }
	void setSkillTurn(Turn_t SkillTurn) throw() { m_Interval = SkillTurn; }

	// get / set CastingTime
	Turn_t getCastingTime() const throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

private :

	// 스킬 타입
	SkillType_t m_SkillType;

	// 스킬 레벨
	ExpLevel_t m_ExpLevel;

	// 한번쓰고 다음에 쓸 딜레이
	Turn_t m_Interval;

	// 캐스팅 타임
	Turn_t m_CastingTime;

};

#endif
