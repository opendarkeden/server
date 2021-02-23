//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSMSSend.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSMSSend.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


void CGSMSSend::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE size;

	iStream.read(size);
	Assert( size <= MAX_RECEVIER_NUM );

	m_Numbers.clear();
	for ( int i=0; i<size; ++i )
	{
		BYTE strSize;
		string number;
		iStream.read(strSize);
		Assert( strSize <= MAX_NUMBER_LENGTH );
		iStream.read(number, strSize);
		m_Numbers.push_back(number);
	}

	iStream.read(size);
	Assert( size <= MAX_NUMBER_LENGTH );
	iStream.read(m_CallerNumber, size);

	iStream.read(size);
	Assert( size <= MAX_MESSAGE_LENGTH );
	iStream.read(m_Message, size);
		
	__END_CATCH
}

void CGSMSSend::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE size;
	
	size = m_Numbers.size();
	oStream.write(size);

	list<string>::const_iterator itr = m_Numbers.begin();
	list<string>::const_iterator endItr = m_Numbers.end();

	for ( ; itr != endItr ; ++itr )
	{
		size = itr->size();
		oStream.write(size);
		oStream.write(*itr);
	}

	size = m_CallerNumber.size();
	oStream.write(size);
	oStream.write(m_CallerNumber);

	size = m_Message.size();
	oStream.write(size);
	oStream.write(m_Message);

	__END_CATCH
}

PacketSize_t CGSMSSend::getPacketSize() const throw()
{
	__BEGIN_TRY

	PacketSize_t ret = szBYTE;

	list<string>::const_iterator itr = m_Numbers.begin();
	list<string>::const_iterator endItr = m_Numbers.end();

	for ( ; itr != endItr ; ++itr )
	{
		ret += szBYTE + itr->size();
	}

	ret += szBYTE + m_CallerNumber.size();
	ret += szBYTE + m_Message.size();

	return ret;

	__END_CATCH
}

void CGSMSSend::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSMSSendHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGSMSSend::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSMSSend("
		<< "Caller : " << m_CallerNumber
		<< ", Receivers : (";

	list<string>::const_iterator itr = m_Numbers.begin();
	list<string>::const_iterator endItr = m_Numbers.end();

	for ( ; itr != endItr ; ++itr )
	{
		msg << *itr << ", ";
	}

	msg << "), Message : " << m_Message << ")";

	return msg.toString();

	__END_CATCH
}
