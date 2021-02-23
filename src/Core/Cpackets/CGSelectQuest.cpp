// Filename    : CGSelectQuest.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectQuest.h"


void CGSelectQuest::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read( m_QuestID );
	iStream.read( m_NPCOID );

	__END_CATCH
}

void CGSelectQuest::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write( m_QuestID );
	oStream.write( m_NPCOID );

	__END_CATCH
}

void CGSelectQuest::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSelectQuestHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectQuest::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectQuest("
		<< "QuestID:" << m_QuestID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
