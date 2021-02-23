//////////////////////////////////////////////////////////////////////////////
// Filename    : Peace.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PEACE_HANDLER_H__
#define __SKILL_PEACE_HANDLER_H__

#include "SimpleSkill.h"
#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Peace;
//////////////////////////////////////////////////////////////////////////////

class Peace: public SkillHandler 
{
public:
	Peace() throw() {}
	~Peace() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Peace"; }
	SkillType_t getSkillType() const throw() { return SKILL_PEACE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot,
			    const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
				    CEffectID_t CEffectID)
		    throw (Error);



	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Peace g_Peace;

#endif // __SKILL_PEACE_HANDLER_H__
