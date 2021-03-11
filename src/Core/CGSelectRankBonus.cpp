//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectRankBonus.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectRankBonus.h"

void CGSelectRankBonus::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_RankBonusType);

	__END_CATCH
}
		    
void CGSelectRankBonus::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_RankBonusType);

	__END_CATCH
}

void CGSelectRankBonus::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSelectRankBonusHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectRankBonus::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;

	msg << "CGSelectRankBonus("
	    << "RankBonusType:"  << (int)m_RankBonusType
	    << ")";
	
	return msg.toString();

	__END_CATCH
}
