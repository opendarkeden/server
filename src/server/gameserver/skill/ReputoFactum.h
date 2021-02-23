//////////////////////////////////////////////////////////////////////////////
// Filename    : ReputoFactum.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REPUTO_FACTUM_HANDLER_H__
#define __SKILL_REPUTO_FACTUM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ReputoFactum;
//////////////////////////////////////////////////////////////////////////////

class ReputoFactum : public SkillHandler 
{
public:
	ReputoFactum() throw() {}
	~ReputoFactum() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ReputoFactum"; }
	SkillType_t getSkillType() const throw() { return SKILL_REPUTO_FACTUM; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ReputoFactum g_ReputoFactum;

#endif // __SKILL_REPUTO_FACTUM_HANDLER_H__
