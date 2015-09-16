//////////////////////////////////////////////////////////////////////////////
// Filename    : Sniping.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SNIPING_HANDLER_H__
#define __SKILL_SNIPING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Sniping;
//////////////////////////////////////////////////////////////////////////////

class Sniping: public SkillHandler 
{
public:
	Sniping() throw() {}
	~Sniping() throw() {}

public:
    string getSkillHandlerName() const throw() { return "Sniping"; }
	SkillType_t getSkillType() const throw() { return SKILL_SNIPING; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

public:
	void checkRevealRatio(Creature* pCreature, int base, int divisor);
};

// global variable declaration
extern Sniping g_Sniping;

#endif // __SKILL_SNIPING_HANDLER_H__
