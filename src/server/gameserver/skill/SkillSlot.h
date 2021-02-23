//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillSlot.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SLOT_H__
#define __SKILL_SLOT_H__

#include "Types.h"
#include "Timeval.h"
#include "Skill.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// Class SkillSlot;
//////////////////////////////////////////////////////////////////////////////

class SkillSlot 
{
public:
	SkillSlot() throw();
	SkillSlot(SkillType_t SkillType, DWORD Exp, ulong Interval) throw();
	virtual ~SkillSlot() throw();

public:
	virtual void save(const string & ownerID) throw(Error);
	virtual void save() throw(Error);

	virtual void create(const string & ownerID) throw(Error);

	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType(SkillType_t Type) throw() { m_SkillType = Type; }

	void setExp(Exp_t Exp) throw() { m_Exp = Exp; }
	Exp_t getExp() throw() { return m_Exp; }

	void setExpLevel(ExpLevel_t ExpLevel) throw() { m_ExpLevel = ExpLevel; }
	ExpLevel_t getExpLevel() throw() { return m_ExpLevel; }

	Turn_t getInterval() throw() { return m_Interval; }
	void setInterval(Turn_t Interval) throw() { m_Interval = Interval; }

	Turn_t getCastingTime() throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

	Timeval getRunTime() throw() { return m_runTime; }
	void setRunTime() throw();
	void setRunTime(Turn_t delay, bool bSave=true) throw();

	string getName() const throw() { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// 사용가능할 경우 true
	// 사용 불가능할 경우 false
	void setDisable() throw() { m_Enable = false; }
	void setEnable() throw() { m_Enable = true; }
	bool canUse() const throw() { return m_Enable; } 

	// 다음 캐스팅이 가능할때까지 남은 시간
	Turn_t getRemainTurn( Timeval currentTime ) const throw();

protected :
	string       m_Name;
	SkillType_t  m_SkillType;     // 마법, 기술의 종류
	Exp_t        m_Exp;           // 숙련도
	ExpLevel_t   m_ExpLevel;      // 숙련도 레벨
	Turn_t       m_Interval;      // 마법, 기술의 딜레이, 0.1 초 단위
	Turn_t       m_CastingTime;   // 캐스팅 타임... 0.1초 단위
	Timeval      m_runTime;       // 다음에 쓸 수 있는 시간
	bool         m_Enable;        // 사용 가능 한가 안한가
};

#endif // __SKILL_SLOT_H__
