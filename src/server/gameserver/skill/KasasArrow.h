//////////////////////////////////////////////////////////////////////////////
// Filename    : KasasArrow.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_KASAS_ARROW_HANDLER_H__
#define __SKILL_KASAS_ARROW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class KasasArrow;
//////////////////////////////////////////////////////////////////////////////

class KasasArrow : public SkillHandler 
{
public:
	KasasArrow() throw() {}
	~KasasArrow() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "KasasArrow"; }
	SkillType_t getSkillType() const throw() { return SKILL_KASAS_ARROW; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern KasasArrow g_KasasArrow;

#endif // __SKILL_KASAS_ARROW_HANDLER_H__
