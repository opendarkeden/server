//////////////////////////////////////////////////////////////////////////////
// Filename    : Mephisto.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MEPHISTO_HANDLER_H__
#define __SKILL_MEPHISTO_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Mephisto;
//////////////////////////////////////////////////////////////////////////////

class Mephisto : public SkillHandler 
{
public:
	Mephisto() throw() {}
	~Mephisto() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Mephisto"; }
	SkillType_t getSkillType() const throw() { return SKILL_MEPHISTO; }

	void execute(Vampire* pVampire ) ;
	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;


	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Mephisto g_Mephisto;

#endif // __SKILL_MEPHISTO_HANDLER_H__
