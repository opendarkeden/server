//////////////////////////////////////////////////////////////////////////////
// Filename    : Prominence.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PROMINENCE_HANDLER_H__
#define __SKILL_PROMINENCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Prominence;
//////////////////////////////////////////////////////////////////////////////

class Prominence : public SkillHandler 
{
public:
	Prominence() throw() {}
	~Prominence() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Prominence"; }
	SkillType_t getSkillType() const throw() { return SKILL_PROMINENCE; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Prominence g_Prominence;

#endif // __SKILL_PROMINENCE_HANDLER_H__
