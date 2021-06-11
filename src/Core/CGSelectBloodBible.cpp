//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectBloodBible.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectBloodBible.h"


void CGSelectBloodBible::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_BloodBibleID);

	__END_CATCH
}

void CGSelectBloodBible::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_BloodBibleID);

	__END_CATCH
}

void CGSelectBloodBible::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSelectBloodBibleHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectBloodBible::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectBloodBible("
		<< "BloodBibleID:" << m_BloodBibleID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
