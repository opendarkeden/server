//////////////////////////////////////////////////////////////////////////////
// Filename    : BiteOfDeath.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BITE_OF_DEATH_HANDLER_H__
#define __SKILL_BITE_OF_DEATH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BiteOfDeath;
//////////////////////////////////////////////////////////////////////////////

class BiteOfDeath : public SkillHandler 
{
public:
	BiteOfDeath() throw() {}
	~BiteOfDeath() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BiteOfDeath"; }
	SkillType_t getSkillType() const throw() { return SKILL_BITE_OF_DEATH; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) { }
};

// global variable declaration
extern BiteOfDeath g_BiteOfDeath;

#endif // __SKILL_BITE_OF_DEATH_HANDLER_H__
