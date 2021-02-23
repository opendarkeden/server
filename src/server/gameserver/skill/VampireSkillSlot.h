//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireSkillSlot.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_SKILL_SLOT_H__
#define __VAMPIRE_SKILL_SLOT_H__

#include "Types.h"
#include "Timeval.h"
#include "Skill.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// Class VampireSkillSlot;
//////////////////////////////////////////////////////////////////////////////

class VampireSkillSlot 
{
public:
    VampireSkillSlot() throw();
    VampireSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime) throw();
    virtual ~VampireSkillSlot() throw();

public:
	virtual void save(const string & ownerID) throw(Error);
	virtual void save() throw(Error);
	virtual void create(const string & ownerID) throw(Error);

    SkillType_t getSkillType() throw() { return m_SkillType; }

    void setSkillType(SkillType_t Type) throw() { m_SkillType = Type; }

    ulong getInterval() throw() { return m_Interval; }

    void setInterval(ulong Interval) throw() { m_Interval = Interval; }

	Turn_t getCastingTime() throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

    Timeval getRunTime() throw() { return m_runTime; }
	void setRunTime() throw();
	void setRunTime(Turn_t delay) throw();

	string getName() const throw() { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// 다음 캐스팅이 가능할때까지 남은 시간
	Turn_t getRemainTurn( Timeval currentTime ) const throw();

private:
	string       m_Name;
	SkillType_t  m_SkillType;   // 마법, 기술의 종류
	Turn_t       m_Interval;    // 마법, 기술의 딜레이, 초 단위
	Turn_t       m_CastingTime; // 캐스팅 타임... 0.1초 단위
	Timeval      m_runTime;     // 다음에 쓸 수 있는 시간
};

#endif // __VAMPIRE_SKILL_SLOT_H__
