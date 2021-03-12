//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonCasket.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_CASKET_HANDLER_H__
#define __SKILL_SUMMON_CASKET_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonCasket;
//////////////////////////////////////////////////////////////////////////////

class SummonCasket: public SkillHandler 
{
public:
	SummonCasket() throw() {}
	~SummonCasket() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonCasket"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_CASKET; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Monster* pMonster) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonCasket g_SummonCasket;

#endif // __SKILL_SUMMON_CASKET_HANDLER_H__
