////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionNotGuildMember.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __NOT_GUILD_MEMBER_H__
#define __NOT_GUILD_MEMBER_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionNotGuildMember;
//////////////////////////////////////////////////////////////////////////////

class ConditionNotGuildMember : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_NOT_GUILD_MEMBER; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionNotGuildMemberFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionNotGuildMemberFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_NOT_GUILD_MEMBER; }
    virtual Condition* createCondition() const  { return new ConditionNotGuildMember(); }
    virtual string getConditionName() const  { return "NotGuildMember"; }
};

#endif
