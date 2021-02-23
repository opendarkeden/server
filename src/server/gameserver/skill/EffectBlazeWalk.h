//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlazeWalk.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLAZE_WALK__
#define __EFFECT_BLAZE_WALK__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBlazeWalk
//////////////////////////////////////////////////////////////////////////////

class EffectBlazeWalk : public Effect 
{
public:
	EffectBlazeWalk(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLAZE_WALK; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	HP_t getPoint() const throw() { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

	uint getAttackNum() const { return m_AttackNum; }
	void setAttackNum( uint AttackNum ) { m_AttackNum = AttackNum; }

	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t SkillType ) { m_SkillType = SkillType; }

private:
	HP_t    m_Point;
	ObjectID_t m_UserObjectID;
	uint m_AttackNum;
	SkillType_t m_SkillType;
};

#endif // __EFFECT_BLAZE_WALK__
