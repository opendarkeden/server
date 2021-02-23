//////////////////////////////////////////////////////////////////////////////
// Filename    : CGWhisper.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGWhisper.h"

void CGWhisper::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// 이름 읽기
	BYTE szName;

	iStream.read(szName);

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 10)
		throw InvalidProtocolException("too large name length");

	iStream.read(m_Name , szName);
	iStream.read( m_Color );

	// 메세지 읽기
	BYTE szMessage;

	iStream.read(szMessage);

	if (szMessage == 0)
		throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128)
		throw InvalidProtocolException("too large message length");

	iStream.read(m_Message , szMessage);

	__END_CATCH
}
		    
void CGWhisper::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// 이름 쓰기
	BYTE szName = m_Name.size();

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 128)
		throw InvalidProtocolException("too large name length");

	oStream.write(szName);

	oStream.write(m_Name);

	oStream.write( m_Color );

	// 메세지 쓰기
	BYTE szMessage = m_Message.size();

	if (szMessage == 0)
		throw InvalidProtocolException("szMessage == 0");

	if (szMessage > 128)
		throw InvalidProtocolException("too large message length");

	oStream.write(szMessage);

	oStream.write(m_Message);

	__END_CATCH
}

void CGWhisper::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGWhisperHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGWhisper::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGWhisper(Name :" << m_Name 
		<< ", Color : " << m_Color
		<< ", Message : " << m_Message
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
