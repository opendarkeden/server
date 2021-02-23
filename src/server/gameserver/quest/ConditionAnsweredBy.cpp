////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAnsweredBy.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionAnsweredBy.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionAnsweredBy::isSatisfied(Creature* pCreature1, Creature* pCreature2, void* pParam) const throw ()
{
	// check parameter
	if (pParam == NULL) return false;

	COND_ANSWERED_BY* pCond = (COND_ANSWERED_BY*)pParam;
	
	// 스크립트 ID와 대답ID가 같다면 이 컨디션은 true	
	if (pCond->ScriptID == m_ScriptID && pCond->AnswerID == m_AnswerID) return true;
	return false;	
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionAnsweredBy::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		// read script & answer id
		m_ScriptID = propertyBuffer.getPropertyInt("ScriptID");
		m_AnswerID = propertyBuffer.getPropertyInt("AnswerID");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionAnsweredBy::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionAnsweredBy(" 
      << "ScriptID:" << (int)m_ScriptID << ","
      << "AnswerID:" << (int)m_AnswerID << ")"; 
	return msg.toString();

	__END_CATCH
}
