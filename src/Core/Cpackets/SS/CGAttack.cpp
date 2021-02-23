//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAttack.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAttack.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGAttack::CGAttack () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAttack::~CGAttack () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAttack::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_X),
							pEIStream->readEncrypt(m_Y),
							pEIStream->readEncrypt(m_Dir));
	}
	else
#endif
	{
		iStream.read((char*)&m_ObjectID , szObjectID);
		iStream.read((char*)&m_X , szCoord);
		iStream.read((char*)&m_Y , szCoord);
		iStream.read((char*)&m_Dir , szDir);
	}

	__END_CATCH
}

void CGAttack::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_X),
							pEOStream->writeEncrypt(m_Y),
							pEOStream->writeEncrypt(m_Dir));
	}
	else
#endif
	{
		oStream.write((char*)&m_ObjectID , szObjectID);
		oStream.write((char*)&m_X , szCoord);
		oStream.write((char*)&m_Y , szCoord);
		oStream.write((char*)&m_Dir , szDir);
	}

	__END_CATCH
}

void CGAttack::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAttackHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAttack::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAttack(" 
		<< "X:" << (int)m_X	
		<< ",Y:" << (int)m_Y 
		<< ",ObjectID :" << (int)m_ObjectID 
		<< ", Dir:" << (int)m_Dir 
		<< ")";
	return msg.toString();

	__END_CATCH
}
