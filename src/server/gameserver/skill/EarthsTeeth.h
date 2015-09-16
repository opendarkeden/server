//////////////////////////////////////////////////////////////////////////////
// Filename    : EarthsTeeth.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EARTHS_TEETH_HANDLER_H__
#define __SKILL_EARTHS_TEETH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class EarthsTeeth;
//////////////////////////////////////////////////////////////////////////////

class EarthsTeeth : public SkillHandler 
{
public:
	EarthsTeeth() throw() {}
	~EarthsTeeth() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "EarthsTeeth"; }
	SkillType_t getSkillType() const throw() { return SKILL_EARTHS_TEETH; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern EarthsTeeth g_EarthsTeeth;

#endif // __SKILL_EARTHS_TEETH_HANDLER_H__
