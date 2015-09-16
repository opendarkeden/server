//////////////////////////////////////////////////////////////////////////////
// Filename    : SweepVice.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SWEEP_VICE_HANDLER_H__
#define __SKILL_SWEEP_VICE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SweepVice;
//////////////////////////////////////////////////////////////////////////////

class SweepVice : public SkillHandler 
{
public:
	SweepVice(int level) throw() : m_Level(level) {}
	~SweepVice() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SweepVice"; }
	SkillType_t getSkillType() const throw() { return SKILL_SWEEP_VICE_1 + m_Level; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	int	m_Level;
};

// global variable declaration
extern SweepVice g_SweepVice1;
extern SweepVice g_SweepVice3;
extern SweepVice g_SweepVice5;

#endif // __SKILL_SWEEP_VICE_HANDLER_H__
