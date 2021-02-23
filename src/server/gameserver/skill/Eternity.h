//////////////////////////////////////////////////////////////////////////////
// Filename    : Eternity.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ETERNITY_HANDLER_H__
#define __SKILL_ETERNITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Eternity;
//////////////////////////////////////////////////////////////////////////////

class Eternity : public SkillHandler 
{
public:
	Eternity() throw() {}
	~Eternity() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Eternity"; }
	SkillType_t getSkillType() const throw() { return SKILL_ETERNITY; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Eternity g_Eternity;

#endif // __SKILL_ETERNITY_HANDLER_H__
