#ifndef __VAMPIRE_CASTLE_SKILL_SLOT_H__
#define __VAMPIRE_CASTLE_SKILL_SLOT_H__

#include "VampireSkillSlot.h"

class VampireCastleSkillSlot : public VampireSkillSlot
{
public:
	VampireCastleSkillSlot() throw()
		: VampireSkillSlot() { }
	VampireCastleSkillSlot( SkillType_t SkillType, ulong Interval, ulong CastingTime ) throw()
		: VampireSkillSlot( SkillType, Interval, CastingTime ) { }
	~VampireCastleSkillSlot() throw() { }

public:
	virtual void save(const string & ownerID) { }
	virtual void save() { } 
	virtual void create(const string & ownerID) { }
};

#endif// __VAMPIRE_CASTLE_SKILL_SLOT_H__
