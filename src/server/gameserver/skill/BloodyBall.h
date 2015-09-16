//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyBall.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_BALL_HANDLER_H__
#define __SKILL_BLOODY_BALL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyBall;
//////////////////////////////////////////////////////////////////////////////

class BloodyBall : public SkillHandler 
{
public:
	BloodyBall() throw();
	~BloodyBall() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyBall"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_BALL; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pBloodyBallMask[9];
};

// global variable declaration
extern BloodyBall g_BloodyBall;

#endif // __SKILL_BLOODY_BALL_HANDLER_H__
