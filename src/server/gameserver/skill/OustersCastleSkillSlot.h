#ifndef __OUSTERS_CASTLE_SKILL_SLOT_H__
#define __OUSTERS_CASTLE_SKILL_SLOT_H__

#include "OustersSkillSlot.h"

class OustersCastleSkillSlot : public OustersSkillSlot
{
public:
	OustersCastleSkillSlot() throw()
		: OustersSkillSlot() { }
	OustersCastleSkillSlot( SkillType_t SkillType, ulong Interval, ulong CastingTime ) throw()
		: OustersSkillSlot( SkillType, Interval, CastingTime ) { }
	~OustersCastleSkillSlot() throw() { }

public:
	virtual void save(const string & ownerID) throw(Error){ }
	virtual void save() throw(Error){ } 
	virtual void create(const string & ownerID) throw(Error){ }
};

#endif// __OUSTERS_CASTLE_SKILL_SLOT_H__
