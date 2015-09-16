//////////////////////////////////////////////////////////////////////////////
// Filename    : IntimateGrail.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_INTIMATE_GRAIL_HANDLER_H__
#define __SKILL_INTIMATE_GRAIL_HANDLER_H__

#include "SkillHandler.h"
#include "Creature.h"
//////////////////////////////////////////////////////////////////////////////
// class IntimateGrail;
//////////////////////////////////////////////////////////////////////////////

class IntimateGrail : public SkillHandler 
{
public:
	IntimateGrail() throw() {}
	~IntimateGrail() throw() {}
	
public :
    string getSkillHandlerName() const throw() { return "IntimateGrail"; }
	SkillType_t getSkillType() const throw() { return SKILL_INTIMATE_GRAIL; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern IntimateGrail g_IntimateGrail;

#endif // __SKILL_INTIMATE_GRAIL_HANDLER_H__
