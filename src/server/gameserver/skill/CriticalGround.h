//////////////////////////////////////////////////////////////////////////////
// Filename    : CriticalGround.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CRITICAL_GROUND_HANDLER_H__
#define __SKILL_CRITICAL_GROUND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CriticalGround;
//////////////////////////////////////////////////////////////////////////////

class CriticalGround: public SkillHandler 
{
public:
	CriticalGround() throw();
	~CriticalGround() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CriticalGround"; }
	SkillType_t getSkillType() const throw() { return SKILL_CRITICAL_GROUND; }

	//void execute(Slayer* pSlayer, SlayerSkillSlot* pSlayerSkillSlot, CEffectID_t CEffectID) throw(Error);
	//void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	POINT	m_pCriticalGroundMask[8];
};

// global variable declaration
extern CriticalGround g_CriticalGround;

#endif // __SKILL_HIDE_HANDLER_H__
