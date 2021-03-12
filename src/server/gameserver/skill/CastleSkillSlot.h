//////////////////////////////////////////////////////////////////////////////
// Filename    : CastleSkillSlot.h
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CASTLE_SKILL_SLOT_H__
#define __CASTLE_SKILL_SLOT_H__

#include "SkillSlot.h"

//////////////////////////////////////////////////////////////////////////////
// Class CastleSkillSlot;
//////////////////////////////////////////////////////////////////////////////

class CastleSkillSlot : public SkillSlot
{
public:
	CastleSkillSlot() throw()
		: SkillSlot() {}
	CastleSkillSlot(SkillType_t SkillType, DWORD Exp, ulong Interval) throw()
		: SkillSlot( SkillType, Exp, Interval ) {}
	~CastleSkillSlot() throw();

public:
	virtual void save(const string & ownerID) ;
	virtual void save() ;

	virtual void create(const string & ownerID) ;
};

#endif // __CASTLE_SKILL_SLOT_H__
