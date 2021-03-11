//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGQuestCancel.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGGQuestCancel.h"

void CGGQuestCancel::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_QuestID);

	__END_CATCH
}
		    
void CGGQuestCancel::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_QuestID);

	__END_CATCH
}

void CGGQuestCancel::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGGQuestCancelHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGGQuestCancel::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGGQuestCancel("
	    << "QuestID:"  << (int)m_QuestID << ","
	    << ")";
	
	return msg.toString();

	__END_CATCH
}
