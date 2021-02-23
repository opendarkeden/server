//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterRangeSkill.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_RANGE_SKILL_HANDLER_H__
#define __MONSTER_RANGE_SKILL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterRangeSkill;
//////////////////////////////////////////////////////////////////////////////

class MonsterRangeSkill : public SkillHandler 
{
public:
	MonsterRangeSkill(SkillType_t skillType, Damage_t damage = 0, bool magic = true, bool add = true) throw() : m_SkillType(skillType), m_Damage(damage), m_bMagic(magic), m_bAdd(add) {}
	~MonsterRangeSkill() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MonsterRangeSkill "; }
	SkillType_t getSkillType() const throw() { return m_SkillType; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) { }

private:
	SkillType_t	m_SkillType;
	Damage_t	m_Damage;
	bool		m_bMagic;
	bool		m_bAdd;
};

#endif // __MONSTER_RANGE_SKILL_HANDLER_H__
