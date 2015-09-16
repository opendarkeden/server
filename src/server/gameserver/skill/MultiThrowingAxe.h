//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiThrowingAxe.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MULTI_THROWING_AXE_HANDLER_H__
#define __SKILL_MULTI_THROWING_AXE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MultiThrowingAxe;
//////////////////////////////////////////////////////////////////////////////

class MultiThrowingAxe : public SkillHandler 
{
public:
	MultiThrowingAxe() throw() {}
	~MultiThrowingAxe() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MultiThrowingAxe"; }
	SkillType_t getSkillType() const throw() { return SKILL_MULTI_THROWING_AXE; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MultiThrowingAxe g_MultiThrowingAxe;

#endif // __SKILL_MULTI_THROWING_AXE_HANDLER_H__
