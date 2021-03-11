//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGQuestAccept.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGGQuestAccept.h"

void CGGQuestAccept::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_QuestID);

	__END_CATCH
}
		    
void CGGQuestAccept::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_QuestID);

	__END_CATCH
}

void CGGQuestAccept::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGGQuestAcceptHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGGQuestAccept::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGGQuestAccept("
	    << "QuestID:"  << (int)m_QuestID << ","
	    << ")";
	
	return msg.toString();

	__END_CATCH
}
