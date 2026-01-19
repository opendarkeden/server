//////////////////////////////////////////////////////////////////////////////
// Filename    : DeadlyClaw.h
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Deadly_Claw_HANDLER_H__
#define __SKILL_Deadly_Claw_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DeadlyClaw;
//////////////////////////////////////////////////////////////////////////////

class DeadlyClaw : public SkillHandler {
public:
    DeadlyClaw() throw();
    ~DeadlyClaw() throw() {}

public:
    string getSkillHandlerName() const throw() {
        return "DeadlyClaw";
    }
    SkillType_t getSkillType() const throw() {
        return SKILL_Deadly_Claw;
    }

    void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID);
    void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot,
                 CEffectID_t CEffectID);

    void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y);

    void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
    POINT m_pDeadlyClawMask[9];
};

// global variable declaration
extern DeadlyClaw g_DeadlyClaw;

#endif // __SKILL_Deadly_Claw_HANDLER_H__
