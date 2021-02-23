//////////////////////////////////////////////////////////////////////////////
// Filename    : ThunderSpark.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THUNDER_SPARK_HANDLER_H__
#define __SKILL_THUNDER_SPARK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ThunderSpark;
//////////////////////////////////////////////////////////////////////////////

class ThunderSpark : public SkillHandler 
{
public:
	ThunderSpark() throw() {}
	~ThunderSpark() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ThunderSpark"; }
	SkillType_t getSkillType() const throw() { return SKILL_THUNDER_SPARK; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ThunderSpark g_ThunderSpark;

#endif // __SKILL_THUNDER_SPARK_HANDLER_H__
