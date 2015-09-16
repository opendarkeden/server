//////////////////////////////////////////////////////////////////////////////
// Filename    : LandMineExplosion.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LAND_MINE_EXPLOSION_HANDLER_H__
#define __SKILL_LAND_MINE_EXPLOSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class LandMineExplosion;
//////////////////////////////////////////////////////////////////////////////

class LandMineExplosion: public SkillHandler 
{
public:
	LandMineExplosion() throw();
	~LandMineExplosion() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "LandMineExplosion"; }
	SkillType_t getSkillType() const throw() { return SKILL_LAND_MINE_EXPLOSION; }

	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	POINT	m_pLandMineExplosionMask[48];
};

// global variable declaration
extern LandMineExplosion g_LandMineExplosion;

#endif // __SKILL_HIDE_HANDLER_H__
