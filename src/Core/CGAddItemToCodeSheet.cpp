//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToCodeSheet.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddItemToCodeSheet.h"

void CGAddItemToCodeSheet::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_X);
	iStream.read(m_Y);

	__END_CATCH
}

void CGAddItemToCodeSheet::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write(m_ObjectID);
	oStream.write(m_X);
	oStream.write(m_Y);

	__END_CATCH
}

void CGAddItemToCodeSheet::execute (Player* pPlayer) 
	
{
	__BEGIN_TRY
		
	CGAddItemToCodeSheetHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGAddItemToCodeSheet::toString () const
	
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddItemToCodeSheet("
		<< ",ObjectID:"  << (int)m_ObjectID 
		<< ",X:"         << (int)m_X 
		<< ",Y:"         << (int)m_Y 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
