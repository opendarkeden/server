////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAttrComp.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionAttrComp.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ConditionAttrComp::ConditionAttrComp()
	throw()
{
	__BEGIN_TRY

	m_ReqSTR        = 0;
	m_ReqDEX        = 0;
	m_ReqINT        = 0;
	m_ReqSum        = 0;
	m_ReqLevel      = 0;
	m_STROperator   = CONDITION_ATTR_COMP_MAX;
	m_DEXOperator   = CONDITION_ATTR_COMP_MAX;
	m_INTOperator   = CONDITION_ATTR_COMP_MAX;
	m_SumOperator   = CONDITION_ATTR_COMP_MAX;
	m_LevelOperator = CONDITION_ATTR_COMP_MAX;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ConditionAttrComp::~ConditionAttrComp()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionAttrComp::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw() 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	uint current = 0;

	// STR을 비교한다.
	if (m_ReqSTR > 0)
	{
		if (pCreature2->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
			current = pSlayer->getSTR(ATTR_BASIC);
			if (!satisfy(m_STROperator, current, m_ReqSTR)) return false;
		}
		else if (pCreature2->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
			current = pVampire->getSTR(ATTR_BASIC);
			if (!satisfy(m_STROperator, current, m_ReqSTR)) return false;
		}
		else if (pCreature2->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
			current = pOusters->getSTR(ATTR_BASIC);
			if (!satisfy(m_STROperator, current, m_ReqSTR)) return false;
		}
	}

	// DEX를 비교한다.
	if (m_ReqDEX > 0)
	{
		if (pCreature2->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
			current = pSlayer->getDEX(ATTR_BASIC);
			if (!satisfy(m_DEXOperator, current, m_ReqDEX)) return false;
		}
		else if (pCreature2->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
			current = pVampire->getDEX(ATTR_BASIC);
			if (!satisfy(m_DEXOperator, current, m_ReqDEX)) return false;
		}
		else if (pCreature2->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
			current = pOusters->getDEX(ATTR_BASIC);
			if (!satisfy(m_DEXOperator, current, m_ReqDEX)) return false;
		}
	}

	// INT를 비교한다.
	if (m_ReqINT > 0)
	{
		if (pCreature2->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
			current = pSlayer->getINT(ATTR_BASIC);
			if (!satisfy(m_INTOperator, current, m_ReqINT)) return false;
		}
		else if (pCreature2->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
			current = pVampire->getINT(ATTR_BASIC);
			if (!satisfy(m_INTOperator, current, m_ReqINT)) return false;
		}
		else if (pCreature2->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
			current = pOusters->getINT(ATTR_BASIC);
			if (!satisfy(m_INTOperator, current, m_ReqINT)) return false;
		}
	}

	// Sum을 비교한다.
	if (m_ReqSum > 0)
	{
		if (pCreature2->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
			uint    curSTR  = pSlayer->getSTR(ATTR_BASIC);
			uint    curDEX  = pSlayer->getDEX(ATTR_BASIC);
			uint    curINT  = pSlayer->getINT(ATTR_BASIC);

			current = curSTR + curDEX + curINT;
			if (!satisfy(m_SumOperator, current, m_ReqSum)) return false;
		}
		else if (pCreature2->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
			uint     curSTR   = pVampire->getSTR(ATTR_BASIC);
			uint     curDEX   = pVampire->getDEX(ATTR_BASIC);
			uint     curINT   = pVampire->getINT(ATTR_BASIC);

			current = curSTR + curDEX + curINT;
			if (!satisfy(m_SumOperator, current, m_ReqSum)) return false;
		}
		else if (pCreature2->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
			uint     curSTR   = pOusters->getSTR(ATTR_BASIC);
			uint     curDEX   = pOusters->getDEX(ATTR_BASIC);
			uint     curINT   = pOusters->getINT(ATTR_BASIC);

			current = curSTR + curDEX + curINT;
			if (!satisfy(m_SumOperator, current, m_ReqSum)) return false;
		}
	}

	// Level을 비교한다.
	if (m_ReqLevel > 0)
	{
		if (pCreature2->isSlayer())
		{
			return true;
		}
		else if (pCreature2->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
			current = pVampire->getLevel();
			if (!satisfy(m_LevelOperator, current, m_ReqLevel)) return false;
		}
		else if (pCreature2->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
			current = pOusters->getLevel();
			if (!satisfy(m_LevelOperator, current, m_ReqLevel)) return false;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionAttrComp::read (PropertyBuffer & propertyBuffer) 
	throw(Error)
{
	try
	{
		string text = propertyBuffer.getProperty("Attr");

		uint a=0, b=0, c=0, d=0;

		while (d < text.size() - 1)
		{
			//////////////////////////////////////////////////
			// (STR,LOWER,30)
			//////////////////////////////////////////////////
			a = text.find_first_of('(', d);
			b = text.find_first_of(',', a+1);
			c = text.find_first_of(',', b+1);
			d = text.find_first_of(')', c+1);

			if (a > b || b > c || c > d) break;

			string attr   = trim(text.substr(a+1, b-a-1));
			string op     = trim(text.substr(b+1, c-b-1));
			string amount = trim(text.substr(c+1, d-c-1));

			if (attr == "STR")
			{
				m_ReqSTR = atoi(amount.c_str());
				parseOperator(op, m_STROperator);
			}
			else if (attr == "DEX")
			{
				m_ReqDEX = atoi(amount.c_str());
				parseOperator(op, m_DEXOperator);
			}
			else if (attr == "INT")
			{
				m_ReqINT = atoi(amount.c_str());
				parseOperator(op, m_INTOperator);
			}
			else if (attr == "SUM")
			{
				m_ReqSum = atoi(amount.c_str());
				parseOperator(op, m_SumOperator);
			}
			else if (attr == "LEVEL")
			{
				m_ReqLevel = atoi(amount.c_str());
				parseOperator(op, m_LevelOperator);
			}
			else
			{
				cout << "ConditionAttrComp::read() : Unknown attribute type[" << attr << "]" << endl;
				throw("ConditionAttrComp::read() : Unknown attribute type");
			}

		} // while (d < text.size() - 1)
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
// utility function
////////////////////////////////////////////////////////////////////////////////
void ConditionAttrComp::parseOperator(string& op, uint& var)
	throw()
{
	__BEGIN_TRY

	if (op == "LOWER")       var = CONDITION_ATTR_COMP_LOWER;
	else if (op == "EQUAL")  var = CONDITION_ATTR_COMP_EQUAL;
	else if (op == "HIGHER") var = CONDITION_ATTR_COMP_HIGHER;
	else
	{
		cout << "ConditionAttrComp::parseOperator() : Unknown operator[" << op << "]" << endl;
		throw("ConditionAttrComp::parseOperator() : Unknown operator");
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// utility function
////////////////////////////////////////////////////////////////////////////////
bool ConditionAttrComp::satisfy(uint op, uint current, uint restriction) const
	throw()
{
	__BEGIN_TRY

	switch (op)
	{
		case CONDITION_ATTR_COMP_LOWER:
			if (current <= restriction) return true;
			break;
		case CONDITION_ATTR_COMP_EQUAL:
			if (current == restriction) return true;
			break;
		case CONDITION_ATTR_COMP_HIGHER:
			if (current >= restriction) return true;
			break;
		default:
			break;
	}

	return false;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionAttrComp::toString () const 
	throw() 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionAttrComp("
		<< "ReqSTR:"          << (int)m_ReqSTR
		<< " ,ReqDEX:"        << (int)m_ReqDEX
		<< " ,ReqINT:"        << (int)m_ReqINT
		<< " ,ReqSum:"        << (int)m_ReqSum
		<< " ,ReqLevel:"      << (int)m_ReqLevel
		<< " ,STROperator:"   << ConditionAttrCompOperator2String[m_STROperator]
		<< " ,DEXOperator:"   << ConditionAttrCompOperator2String[m_DEXOperator]
		<< " ,INTOperator:"   << ConditionAttrCompOperator2String[m_INTOperator]
		<< " ,SumOperator:"   << ConditionAttrCompOperator2String[m_SumOperator]
		<< " ,LevelOperator:" << ConditionAttrCompOperator2String[m_LevelOperator]
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
