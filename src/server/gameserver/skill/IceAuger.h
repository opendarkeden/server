//////////////////////////////////////////////////////////////////////////////
// Filename    : IceAuger.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_AUGER_HANDLER_H__
#define __SKILL_ICE_AUGER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceAuger;
//////////////////////////////////////////////////////////////////////////////

class IceAuger : public SkillHandler 
{
public:
	IceAuger() throw() {}
	~IceAuger() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "IceAuger"; }
	SkillType_t getSkillType() const throw() { return SKILL_ICE_AUGER; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern IceAuger g_IceAuger;

#endif // __SKILL_ICE_AUGER_HANDLER_H__
