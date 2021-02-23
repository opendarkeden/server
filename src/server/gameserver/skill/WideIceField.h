//////////////////////////////////////////////////////////////////////////////
// Filename    : WideIceField.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WIDE_ICE_FIELD_HANDLER_H__
#define __SKILL_WIDE_ICE_FIELD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WideIceField;
//////////////////////////////////////////////////////////////////////////////

class WideIceField : public SkillHandler 
{
public:
	WideIceField() throw() { }
	~WideIceField() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "WideIceField"; }
	SkillType_t getSkillType() const throw() { return SKILL_WIDE_ICE_FIELD; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WideIceField g_WideIceField;

#endif // __SKILL_WIDE_ICE_FIELD_HANDLER_H__
