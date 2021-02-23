//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyMasterWave.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_MASTER_WAVE_HANDLER_H__
#define __SKILL_BLOODY_MASTER_WAVE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyMasterWave;
//////////////////////////////////////////////////////////////////////////////
const int maxBloodyMasterWaveMask = 24;

class BloodyMasterWave : public SkillHandler 
{
public:
	BloodyMasterWave() throw();
	~BloodyMasterWave() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyMasterWave"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_MASTER_WAVE; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pBloodyMasterWaveMask[maxBloodyMasterWaveMask];
};

// global variable declaration
extern BloodyMasterWave g_BloodyMasterWave;

#endif // __SKILL_BLOODY_MASTER_WAVE_HANDLER_H__
