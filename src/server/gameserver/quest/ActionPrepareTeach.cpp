////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareTeach.cpp
// Written By  : 
// Description : 
// 교관 NPC가 가르쳐 줄 수 있는 기술의 종류를 정하는 액션이다.
// PrepareShop과 비슷하게 AtFirst 컨디션을 이용하여 처음
// 한번만 실행하고 다시는 실행하지 않는다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionPrepareTeach.h"
#include "Creature.h"
#include "NPC.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionPrepareTeach::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		// 이 NPC가 가르쳐 줄 수 있는 맥스 레벨을 읽어들인다.
		m_MaxLevel = (SkillLevel_t)propertyBuffer.getPropertyInt("MaxLevel");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionPrepareTeach::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	pNPC->setMaxSkillLevel(m_MaxLevel);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionPrepareTeach::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionPrepareTeach("
	    << "MaxLevel:" << (int)m_MaxLevel 
		<< ")";

	return msg.toString();

	__END_CATCH
}
