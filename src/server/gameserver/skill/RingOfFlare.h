//////////////////////////////////////////////////////////////////////////////
// Filename    : RingOfFlare.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RING_OF_FLARE_HANDLER_H__
#define __SKILL_RING_OF_FLARE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RingOfFlare;
//////////////////////////////////////////////////////////////////////////////

class RingOfFlare : public SkillHandler 
{
public:
	RingOfFlare() throw() {}
	~RingOfFlare() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "RingOfFlare"; }
	SkillType_t getSkillType() const throw() { return SKILL_RING_OF_FLARE; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RingOfFlare g_RingOfFlare;

#endif // __SKILL_RING_OF_FLARE_HANDLER_H__
