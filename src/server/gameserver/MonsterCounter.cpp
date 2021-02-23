//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterCounter.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MonsterCounter.h"
#include "Assert.h"

DWORD MonsterCounter::s_MonsterCounter = 0;

MonsterCounter::MonsterCounter(SpriteType_t spriteType, WORD maxMonsters, WORD currentMonsters) 
	throw()
{
	__BEGIN_TRY

	m_SpriteType      = spriteType;
	m_MaxMonsters     = maxMonsters;
	m_CurrentMonsters = currentMonsters;

	s_MonsterCounter += maxMonsters;

	__END_CATCH
}

void MonsterCounter::addMonster() 
	throw(Error) 
{ 
	__BEGIN_TRY

	//Assert(m_CurrentMonsters <= m_MaxMonsters); 
	m_CurrentMonsters++; 

	__END_CATCH
}

void MonsterCounter::addMonster(WORD Count) 
	throw() 
{ 
	__BEGIN_TRY

	//Assert(m_CurrentMonsters <= m_MaxMonsters); 
	m_CurrentMonsters += Count; 

	__END_CATCH
}

void MonsterCounter::deleteMonster() 
	throw(Error) 
{ 
	__BEGIN_TRY

	Assert(m_CurrentMonsters > 0); 
	m_CurrentMonsters--; 

	__END_CATCH
}

// get debug string
string MonsterCounter::toString() const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterCounter("
		<< "SpriteType:" << m_SpriteType
		<< "," << m_CurrentMonsters << "/" << m_MaxMonsters
		<< ")";
	return msg.toString();

	__END_CATCH
}

