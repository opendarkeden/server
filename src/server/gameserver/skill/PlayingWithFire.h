//////////////////////////////////////////////////////////////////////////////
// Filename    : PlayingWithFire.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PLAYING_WITH_FIRE_HANDLER_H__
#define __SKILL_PLAYING_WITH_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PlayingWithFire;
//////////////////////////////////////////////////////////////////////////////

class PlayingWithFire: public SkillHandler 
{
public:
	PlayingWithFire() throw();
	~PlayingWithFire() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PlayingWithFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_PLAYING_WITH_FIRE; }

	//void execute(Slayer* pSlayer, SlayerSkillSlot* pSlayerSkillSlot, CEffectID_t CEffectID) throw(Error);
	//void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	POINT	m_pPlayingWithFireMask[8];
};

// global variable declaration
extern PlayingWithFire g_PlayingWithFire;

#endif // __SKILL_HIDE_HANDLER_H__
