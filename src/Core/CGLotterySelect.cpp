//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLotterySelect.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGLotterySelect.h"


void CGLotterySelect::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Type);
	iStream.read(m_QuestLevel);
	iStream.read(m_GiftID);

	__END_CATCH
}

void CGLotterySelect::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_Type);
	oStream.write(m_QuestLevel);
	oStream.write(m_GiftID);

	__END_CATCH
}

void CGLotterySelect::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGLotterySelectHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGLotterySelect::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGLotterySelect("
		<< "QuestLevel:" << m_QuestLevel
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
