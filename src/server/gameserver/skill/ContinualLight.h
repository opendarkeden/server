//////////////////////////////////////////////////////////////////////////////
// Filename    : ContinualLight.h 
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CONTINUAL_LIGHT_HANDLER_H__
#define __SKILL_CONTINUAL_LIGHT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ContinualLight;
//////////////////////////////////////////////////////////////////////////////

class ContinualLight: public SkillHandler 
{
public:
	ContinualLight() throw() {}
	~ContinualLight() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ContinualLight"; }
	SkillType_t getSkillType() const throw() { return SKILL_CONTINUAL_LIGHT; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ContinualLight g_ContinualLight;

#endif // __SKILL_CONTINUAL_LIGHT_HANDLER_H__
