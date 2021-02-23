
//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMixItem.cpp 
// Written By  : excel96
// Description : 
// 인벤토리 안의 아이템을 사용할 때, 클라이언트가 X, Y 및 ObjectID를
// 보내면 아이템 클래스에 따라서, 서버가 이에 맞는 코드를 처리한다.
//////////////////////////////////////////////////////////////////////////////

#include "CGMixItem.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


void CGMixItem::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);
	iStream.read(m_TargetObjectID[0]);
	iStream.read(m_TargetObjectID[1]);

	__END_CATCH
}
		    
void CGMixItem::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_InvenX);
	oStream.write(m_InvenY);
	oStream.write(m_TargetObjectID[0]);
	oStream.write(m_TargetObjectID[1]);

	__END_CATCH
}

void CGMixItem::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGMixItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGMixItem::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGMixItem("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",InvenX:" << (int)m_InvenX
		<< ",InvenY:" << (int)m_InvenY
		<< ",ObjectID:" << (int)m_TargetObjectID[0]
		<< ",ObjectID:" << (int)m_TargetObjectID[1]
		<< ")";
	return msg.toString();

	__END_CATCH
}
