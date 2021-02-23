//////////////////////////////////////////////////////////////////////////////
// Filename    : TurnUndead.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TURN_UNDEAD_HANDLER_H__
#define __SKILL_TURN_UNDEAD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TurnUndead;
//////////////////////////////////////////////////////////////////////////////

class TurnUndead : public SkillHandler 
{
public:
	TurnUndead() throw() {}
	~TurnUndead() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TurnUndead"; }
	SkillType_t getSkillType() const throw() { return SKILL_TURN_UNDEAD; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TurnUndead g_TurnUndead;

#endif // __SKILL_TURN_UNDEAD_HANDLER_H__
