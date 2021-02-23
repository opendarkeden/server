//////////////////////////////////////////////////////////////////////////////
// Filename    : ShiftBreak.h 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHIFT_BREAK_HANDLER_H__
#define __SKILL_SHIFT_BREAK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShiftBreak;
//////////////////////////////////////////////////////////////////////////////

class ShiftBreak : public SkillHandler 
{
public:
	ShiftBreak() throw();
	~ShiftBreak() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ShiftBreak"; }
	SkillType_t getSkillType() const throw() { return SKILL_SHIFT_BREAK; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pShiftBreakMask[8][6];

};

// global variable declaration
extern ShiftBreak g_ShiftBreak;

#endif // __SKILL_SHIFT_BREAK_HANDLER_H__
