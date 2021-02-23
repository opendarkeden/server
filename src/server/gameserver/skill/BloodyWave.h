//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyWave.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_WAVE_HANDLER_H__
#define __SKILL_BLOODY_WAVE_HANDLER_H__

#include "SkillHandler.h"

class VampireSkillSlot;
//////////////////////////////////////////////////////////////////////////////
// class BloodyWave;
//////////////////////////////////////////////////////////////////////////////
const int maxBloodyWaveMask = 12;

class BloodyWave : public SkillHandler 
{
public:
	BloodyWave() throw();
	~BloodyWave() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyWave"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_WAVE; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pBloodyWaveMask[maxBloodyWaveMask];
};

// global variable declaration
extern BloodyWave g_BloodyWave;

#endif // __SKILL_BLOODY_WAVE_HANDLER_H__
