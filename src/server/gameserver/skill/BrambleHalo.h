//////////////////////////////////////////////////////////////////////////////
// Filename    : BrambleHalo.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Bramble_Halo_HANDLER_H__
#define __SKILL_Bramble_Halo_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BrambleHalo;
//////////////////////////////////////////////////////////////////////////////

class BrambleHalo : public SkillHandler 
{
public:
	BrambleHalo() throw() {}
	~BrambleHalo() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BrambleHalo"; }
	SkillType_t getSkillType() const throw() { return SKILL_Bramble_Halo; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BrambleHalo g_BrambleHalo;

#endif // __SKILL_Bramble_Halo_HANDLER_H__
