//////////////////////////////////////////////////////////////////////////////
// Filename    : IceLance.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_LANCE_HANDLER_H__
#define __SKILL_ICE_LANCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceLance;
//////////////////////////////////////////////////////////////////////////////

class IceLance : public SkillHandler 
{
public:
	IceLance() throw() {}
	~IceLance() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "IceLance"; }
	SkillType_t getSkillType() const throw() { return SKILL_ICE_LANCE; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern IceLance g_IceLance;

#endif // __SKILL_ICE_LANCE_HANDLER_H__
