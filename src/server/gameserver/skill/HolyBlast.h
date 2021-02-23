//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyBlast.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HOLY_BLAST_HANDLER_H__
#define __SKILL_HOLY_BLAST_HANDLER_H__

#include "SkillHandler.h"
#include "SimpleSkill.h"

//////////////////////////////////////////////////////////////////////////////
// class HolyBlast;
//////////////////////////////////////////////////////////////////////////////

class HolyBlast: public SkillHandler 
{
public:
	HolyBlast() throw() {}
	~HolyBlast() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HolyBlast"; }
	SkillType_t getSkillType() const throw() { return SKILL_HOLY_BLAST; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);



	void computeOutput(const SkillInput& input, SkillOutput& output);

	void execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
			    const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
				    CEffectID_t CEffectID=0) throw (Error);

};

// global variable declaration
extern HolyBlast g_HolyBlast;

#endif // __SKILL_HOLY_BLAST_HANDLER_H__
