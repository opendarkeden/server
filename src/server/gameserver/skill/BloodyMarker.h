//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyMarker.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_MARKER_HANDLER_H__
#define __SKILL_BLOODY_MARKER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyMarker;
//////////////////////////////////////////////////////////////////////////////

class BloodyMarker: public SkillHandler 
{
public:
	BloodyMarker() throw() {}
	~BloodyMarker() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyMarker"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_MARKER; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyMarker g_BloodyMarker;

#endif // __SKILL_BLOODY_MARKER_HANDLER_H__
