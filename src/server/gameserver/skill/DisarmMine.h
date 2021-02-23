//////////////////////////////////////////////////////////////////////////////
// Filename    : DisarmMine.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DISARM_MINE_HANDLER_H__
#define __SKILL_DISARM_MINE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DisarmMine;
//////////////////////////////////////////////////////////////////////////////

class DisarmMine: public SkillHandler 
{
public :
	DisarmMine () throw () {}
	~DisarmMine () throw () {}
	
public :
    string getSkillHandlerName () const throw () { return "DisarmMine"; }
	SkillType_t getSkillType () const throw () { return SKILL_DISARM_MINE; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID) throw (Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DisarmMine g_DisarmMine;

#endif // __SKILL_INSTALL_DISARM_MINE_HANDLER_H__
