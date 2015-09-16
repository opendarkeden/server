//////////////////////////////////////////////////////////////////////////////
// Filename    : Armageddon.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ARMAGEDDON_HANDLER_H__
#define __SKILL_ARMAGEDDON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Armageddon;
//////////////////////////////////////////////////////////////////////////////

class Armageddon: public SkillHandler 
{
public:
	Armageddon() throw() {}
	~Armageddon() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Armageddon"; }
	SkillType_t getSkillType() const throw() { return SKILL_ARMAGEDDON; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Armageddon g_Armageddon;

#endif // __SKILL_ARMAGEDDON_HANDLER_H__
