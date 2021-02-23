
#include "QuestStatus.h"
#include "QuestManager.h"

#include "StringStream.h"

string QuestStatus::toString() const throw(Error)
{
	__BEGIN_TRY

	StringStream msg;
	msg << "QuestStatus("
		<< "QuestID : " << (unsigned long)m_QuestID
		<< "Deadline : " << m_Deadline.toString().c_str()
		<< ")";

	return msg.toString();

	__END_CATCH
}

PlayerCreature* QuestStatus::getOwnerPC() const { return m_pOwnerQM->getOwner(); }
