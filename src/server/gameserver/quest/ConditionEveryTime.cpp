////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEveryTime.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionEveryTime.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionEveryTime::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	Timeval currentTime;

	getCurrentTime(currentTime);

	bool expired = pCreature1 != NULL && pCreature2 == NULL && currentTime > m_NextTurn;

	////////////////////////////////////////////////////////////////////////////////
	// 시간이 초과되었으면, 다음 실행시간을 m_Turn 이후로 재설정한다.
	////////////////////////////////////////////////////////////////////////////////
	if (expired)
	{
		Timeval delay;
		delay.tv_sec = m_Turn / 10;
		delay.tv_usec = (m_Turn % 10) * 100000;

		m_NextTurn = m_NextTurn + delay;
	}

	return expired;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionEveryTime::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_Turn = propertyBuffer.getPropertyInt("Turn");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

	// set next turn (current time + m_Turn)
	Timeval delay;
	delay.tv_sec = m_Turn / 10;		
	delay.tv_usec = (m_Turn % 10) * 100000;

	getCurrentTime(m_NextTurn);
	m_NextTurn = m_NextTurn + delay;
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionEveryTime::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionEveryTime("
			<< "Turn:"      << (int)m_Turn
			<< ",NextTurn:" << (int)m_NextTurn.tv_sec 
			<< "."          << (int)m_NextTurn.tv_usec
			<< ")"; 
	return msg.toString();

	__END_CATCH
}
