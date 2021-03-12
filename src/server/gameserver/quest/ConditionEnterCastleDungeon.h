////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterCastleDungeon.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTER_CASTLE_DUNGEON_H__
#define __ENTER_CASTLE_DUNGEON_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterCastleDungeon;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterCastleDungeon : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_ENTER_CASTLE_DUNGEON; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;

	ZoneID_t getCastleZoneID() const	{ return m_CastleZoneID; }

	virtual string toString() const ;

public:
	ZoneID_t 	m_CastleZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterCastleDungeonFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterCastleDungeonFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_ENTER_CASTLE_DUNGEON; }
    virtual Condition* createCondition() const  { return new ConditionEnterCastleDungeon(); }
    virtual string getConditionName() const  { return "EnterCastleDungeon"; }
};

#endif
