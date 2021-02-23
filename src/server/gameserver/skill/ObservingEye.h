//////////////////////////////////////////////////////////////////////////////
// Filename    : ObservingEye.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_OBSERVING_EYE_HANDLER_H__
#define __SKILL_OBSERVING_EYE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ObservingEye;
//////////////////////////////////////////////////////////////////////////////

class ObservingEye : public SkillHandler 
{
public:
	ObservingEye() throw() {}
	~ObservingEye() throw() {}
	
public :
    string getSkillHandlerName() const throw() { return "ObservingEye"; }
	SkillType_t getSkillType() const throw() { return SKILL_OBSERVING_EYE; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ObservingEye g_ObservingEye;

#endif // __SKILL_OBSERVING_EYE_HANDLER_H__
