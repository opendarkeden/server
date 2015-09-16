//////////////////////////////////////////////////////////////////////////////
// Filename    : MagicElusion.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGIC_ELUSION_HANDLER_H__
#define __SKILL_MAGIC_ELUSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MagicElusion;
//////////////////////////////////////////////////////////////////////////////

class MagicElusion : public SkillHandler 
{
public:
	MagicElusion() throw() {}
	~MagicElusion() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MagicElusion"; }
	SkillType_t getSkillType() const throw() { return SKILL_MAGIC_ELUSION; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
 	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagicElusion g_MagicElusion;

#endif // __SKILL_MAGIC_ELUSION_HANDLER_H__
