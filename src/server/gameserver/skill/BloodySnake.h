//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodySnake.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_SNAKE_HANDLER_H__
#define __SKILL_BLOODY_SNAKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodySnake;
//////////////////////////////////////////////////////////////////////////////

class BloodySnake : public SkillHandler 
{
public:
	BloodySnake() throw() {}
	~BloodySnake() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodySnake"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_SNAKE; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void execute(Monster*, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
};

// global variable declaration
extern BloodySnake g_BloodySnake;

#endif // __SKILL_BLOODY_SNAKE_HANDLER_H__
