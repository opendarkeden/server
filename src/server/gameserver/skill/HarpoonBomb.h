//////////////////////////////////////////////////////////////////////////////
// Filename    : HarpoonBomb.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HARPOON_BOMB_HANDLER_H__
#define __SKILL_HARPOON_BOMB_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HarpoonBomb;
//////////////////////////////////////////////////////////////////////////////

class HarpoonBomb : public SkillHandler 
{
public:
	HarpoonBomb() throw() {}
	~HarpoonBomb() throw() {}

public:
    string getSkillHandlerName() const throw() { return "HarpoonBomb"; }
	SkillType_t getSkillType() const throw() { return SKILL_HARPOON_BOMB; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HarpoonBomb g_HarpoonBomb;

#endif // __SKILL_HARPOON_BOMB_HANDLER_H__
