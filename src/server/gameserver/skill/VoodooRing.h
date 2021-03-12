//////////////////////////////////////////////////////////////////////////////
// Filename    : VoodooRing.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Voodoo_Ring_HANDLER_H__
#define __SKILL_Voodoo_Ring_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Voodoo Ring;
//////////////////////////////////////////////////////////////////////////////

class VoodooRing : public SkillHandler 
{
public:
	VoodooRing() throw();
	~VoodooRing() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "VoodooRing"; }
	SkillType_t getSkillType() const throw() { return SKILL_Voodoo_Ring; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);

};

// global variable declaration
extern VoodooRing g_VoodooRing;

#endif // __SKILL_Voodoo_Ring_HANDLER_H__
