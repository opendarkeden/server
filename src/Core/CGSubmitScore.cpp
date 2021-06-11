//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSubmitScore.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSubmitScore.h"

CGSubmitScore::CGSubmitScore () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGSubmitScore::~CGSubmitScore () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGSubmitScore::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_GameType);
	iStream.read(m_Level);
	iStream.read(m_Score);

	__END_CATCH
}
		    
void CGSubmitScore::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_GameType);
	oStream.write(m_Level);
	oStream.write(m_Score);

	__END_CATCH
}

void CGSubmitScore::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGSubmitScoreHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGSubmitScore::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSubmitScore("
		<< ")";
	return msg.toString();

	__END_CATCH
}
