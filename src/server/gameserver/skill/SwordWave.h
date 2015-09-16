//////////////////////////////////////////////////////////////////////////////
// Filename    : SwordWave.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SWORD_WAVE_HANDLER_H__
#define __SKILL_SWORD_WAVE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SwordWave;
//////////////////////////////////////////////////////////////////////////////

class SwordWave : public SkillHandler 
{
public:
	SwordWave() throw();
	~SwordWave() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SwordWave"; }

	SkillType_t getSkillType() const throw() { return SKILL_SWORD_WAVE; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pSwordWaveMask[8][3]; // 각 방향에 따른 타격 마스크

};

// global variable declaration
extern SwordWave g_SwordWave;

#endif // __SKILL_SWORD_WAVE_HANDLER_H__
