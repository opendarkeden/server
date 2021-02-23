//////////////////////////////////////////////////////////////////////////////
// Filename    : NooseOfWraith.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_NOOSE_OF_WRAITH_HANDLER_H__
#define __SKILL_NOOSE_OF_WRAITH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class NooseOfWraith;
//////////////////////////////////////////////////////////////////////////////

class NooseOfWraith : public SkillHandler 
{
public:
	NooseOfWraith() throw();
	~NooseOfWraith() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "NooseOfWraith"; }
	SkillType_t getSkillType() const throw() { return SKILL_NOOSE_OF_WRAITH; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

};

// global variable declaration
extern NooseOfWraith g_NooseOfWraith;

#endif // __SKILL_NOOSE_OF_WRAITH_HANDLER_H__
