////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAttrComp.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_COMP_H__
#define __ATTR_COMP_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

enum
{
	CONDITION_ATTR_COMP_LOWER = 0,
	CONDITION_ATTR_COMP_EQUAL,
	CONDITION_ATTR_COMP_HIGHER,

	CONDITION_ATTR_COMP_MAX
};

const string ConditionAttrCompOperator2String[] = 
{
	"LOWER",
	"EQUAL",
	"HIGHER",

	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAttrComp;
//////////////////////////////////////////////////////////////////////////////

class ConditionAttrComp : public Condition 
{
public:
	ConditionAttrComp() throw();
	virtual ~ConditionAttrComp() throw();

public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_ATTR_COMP; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:
	void parseOperator(string& op, uint& var) throw();
	bool satisfy(uint op, uint current, uint restriction) const throw();

private:
	uint m_ReqSTR;        // 필요 STR
	uint m_ReqDEX;        // 필요 DEX
	uint m_ReqINT;        // 필요 INT
	uint m_ReqSum;        // 필요 능력치의 합
	uint m_ReqLevel;      // 필요 LEVEL

	uint m_STROperator;   // STR 연산자
	uint m_DEXOperator;   // DEX 연산자
	uint m_INTOperator;   // INT 연산자
	uint m_SumOperator;   // SUM 연산자
	uint m_LevelOperator; // LEVEL 연산자

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAttrCompFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionAttrCompFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_ATTR_COMP; }
    virtual Condition* createCondition() const throw() { return new ConditionAttrComp(); }
    virtual string getConditionName() const throw() { return "AttrComp"; }
};

#endif
