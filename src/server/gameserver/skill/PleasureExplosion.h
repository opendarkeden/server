//////////////////////////////////////////////////////////////////////////////
// Filename    : PleasureExplosion.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PLEASURE_EXPLOSION_HANDLER_H__
#define __SKILL_PLEASURE_EXPLOSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PleasureExplosion;
//////////////////////////////////////////////////////////////////////////////

class PleasureExplosion: public SkillHandler 
{
public:
	PleasureExplosion() throw();
	~PleasureExplosion() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PleasureExplosion"; }
	SkillType_t getSkillType() const throw() { return SKILL_PLEASURE_EXPLOSION; }

	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PleasureExplosion g_PleasureExplosion;

#endif // __SKILL_HIDE_HANDLER_H__
