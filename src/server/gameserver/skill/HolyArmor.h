//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyArmor.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HOLY_ARMOR_HANDLER_H__
#define __SKILL_HOLY_ARMOR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HolyArmor;
//////////////////////////////////////////////////////////////////////////////

class HolyArmor : public SkillHandler 
{
public:
	HolyArmor() throw() {}
	~HolyArmor() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HolyArmor"; }
	SkillType_t getSkillType() const throw() { return SKILL_HOLY_ARMOR; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HolyArmor g_HolyArmor;

#endif // __SKILL_HOLY_ARMOR_HANDLER_H__
