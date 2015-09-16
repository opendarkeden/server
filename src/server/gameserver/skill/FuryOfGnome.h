//////////////////////////////////////////////////////////////////////////////
// Filename    : FuryOfGnome.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FURY_OF_GNOME_HANDLER_H__
#define __SKILL_FURY_OF_GNOME_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FuryOfGnome;
//////////////////////////////////////////////////////////////////////////////

class FuryOfGnome: public SkillHandler 
{
public:
	FuryOfGnome() throw() {}
	~FuryOfGnome() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FuryOfGnome"; }

	SkillType_t getSkillType() const throw() { return SKILL_FURY_OF_GNOME; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FuryOfGnome g_FuryOfGnome;

#endif // __SKILL_FURY_OF_GNOME_HANDLER_H__
