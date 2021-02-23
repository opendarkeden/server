//////////////////////////////////////////////////////////////////////////////
// Filename    : Flare.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FLARE_HANDLER_H__
#define __SKILL_FLARE_HANDLER_H__

#include "SkillHandler.h"
#include "Gpackets/GCChangeDarkLight.h"

//////////////////////////////////////////////////////////////////////////////
// class Flare;
//////////////////////////////////////////////////////////////////////////////

class Flare : public SkillHandler 
{
public:
	Flare() throw() {}
	~Flare() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Flare"; }
	SkillType_t getSkillType() const throw() { return SKILL_FLARE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Flare g_Flare;

#endif // __SKILL_FLARE_HANDLER_H__
