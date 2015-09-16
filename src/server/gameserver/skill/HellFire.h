//////////////////////////////////////////////////////////////////////////////
// Filename    : HellFire.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HELLFIRE_HANDLER_H__
#define __SKILL_HELLFIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HellFire;
//////////////////////////////////////////////////////////////////////////////

class HellFire : public SkillHandler 
{
public:
	HellFire() throw();
	~HellFire() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HellFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_HELLFIRE; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT		m_HellFireMask[4][9];	// 4단계, 9개씩
	int			m_MaskNum[4];
};

// global variable declaration
extern HellFire g_HellFire;

#endif // __SKILL_HELLFIRE_HANDLER_H__
