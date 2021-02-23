//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseMessageItemFromInventory.cpp 
// Written By  : excel96
// Description : 
// 인벤토리 안의 아이템을 사용할 때, 클라이언트가 X, Y 및 ObjectID를
// 보내면 아이템 클래스에 따라서, 서버가 이에 맞는 코드를 처리한다.
//////////////////////////////////////////////////////////////////////////////

#include "CGUseMessageItemFromInventory.h"
#include "Assert.h"


void CGUseMessageItemFromInventory::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGUseItemFromInventory::read(iStream);

	BYTE szMessage;

	// message
	iStream.read(szMessage);

	if (szMessage == 0)
		throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128)
		throw InvalidProtocolException("too large message length");

	iStream.read(m_Message , szMessage);


	__END_CATCH
}
		    
void CGUseMessageItemFromInventory::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGUseItemFromInventory::write(oStream);
	
	// message
	BYTE szMessage = m_Message.size();

	if (szMessage == 0)
		throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128)
		throw InvalidProtocolException("too large message length");

	oStream.write(szMessage);

	oStream.write(m_Message);


	__END_CATCH
}

void CGUseMessageItemFromInventory::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGUseMessageItemFromInventoryHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGUseMessageItemFromInventory::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseMessageItemFromInventory("
		<< "ObjectID:" << (int)getObjectID()
		<< ",InvenX:" << (int)getX()
		<< ",InvenY:" << (int)getY()
		<< ",msg:" << m_Message.c_str() 
		<< ")";
	return msg.toString();

	__END_CATCH
}
