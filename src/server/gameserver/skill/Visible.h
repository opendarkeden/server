//////////////////////////////////////////////////////////////////////////////
// Filename    : Visible.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_VISIBLE_HANDLER_H__
#define __SKILL_VISIBLE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Visible;
//////////////////////////////////////////////////////////////////////////////

class Visible: public SkillHandler 
{
public:
	Visible() throw() {}
	~Visible() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Visible"; }
	SkillType_t getSkillType() const throw() { return SKILL_VISIBLE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Visible g_Visible;

#endif // __SKILL_VISIBLE_HANDLER_H__
