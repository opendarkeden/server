//----------------------------------------------------------------------
//
// Filename    : SubSlayerSkillInfo.h
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_SLAYER_SKILL_INFO_H__
#define __SUB_SLAYER_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
// Inventory 정보를 담고 있는 객체.
//
// GCUpdateInfo 패킷에 담겨서 클라이언트에게 전송된다.
// 아이템이나 걸려있는 마법 같은 정보는 담겨있지 않다.
//
//----------------------------------------------------------------------

class SubSlayerSkillInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get size of object
	uint getSize () const throw () { return szSkillType + szExp + szExpLevel + szTurn + szTurn + szBYTE; }
	// get max size of object
	static uint getMaxSize () throw () { return szSkillType + szExp + szExpLevel + szTurn + szTurn + szBYTE; }

	// get debug string
	string toString () const throw ();

public :

	// get / set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Exp
	Exp_t getSkillExp() const throw() { return m_Exp; }
	void setSkillExp(Exp_t Exp) throw() { m_Exp = Exp; }

	// get / set ExpLevel
	ExpLevel_t getSkillExpLevel() const throw() { return m_ExpLevel; }
	void setSkillExpLevel(ExpLevel_t ExpLevel) throw() { m_ExpLevel = ExpLevel; }

	// get / set Turn
	Turn_t getSkillTurn() const throw() { return m_Interval ; }
	void setSkillTurn(Turn_t SkillTurn) throw() { m_Interval = SkillTurn; }

	// get / set CastingTime
	Turn_t getCastingTime() const throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

	// get / set Enable
	// true 일 경우 사용 가능, false일 경우 사용 불가능.
	bool getEnable() const throw() { return m_Enable; }
	void setEnable(bool Enable ) throw() { m_Enable = Enable; }

private :

	// 스킬 타입
	SkillType_t m_SkillType;

	// 스킬 경험치 
	Exp_t m_Exp;

	// 스킬 레벨 
	ExpLevel_t m_ExpLevel;

	// 한번쓰고 다음에 쓸 딜레이
	Turn_t m_Interval;

	// 캐스팅 타임
	Turn_t m_CastingTime;

	// 이 기술을 쓸 수 있는가 없는가의 여부
	bool m_Enable;

};

#endif
