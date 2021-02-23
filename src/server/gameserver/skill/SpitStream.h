//////////////////////////////////////////////////////////////////////////////
// Filename    : SpitStream.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SPIT_STREAM_HANDLER_H__
#define __SKILL_SPIT_STREAM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SpitStream;
//////////////////////////////////////////////////////////////////////////////

class SpitStream : public SkillHandler 
{
public:
	SpitStream() throw() {}
	~SpitStream() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SpitStream"; }
	SkillType_t getSkillType() const throw() { return SKILL_SPIT_STREAM; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SpitStream g_SpitStream;

#endif // __SKILL_SPIT_STREAM_H__
