//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToSelf.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToSelf.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGSkillToSelf::CGSkillToSelf () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGSkillToSelf::~CGSkillToSelf () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGSkillToSelf::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_2(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_SkillType),
							pEIStream->readEncrypt(m_CEffectID));
	}
	else
#endif
	{
		iStream.read((char*)&m_SkillType , szSkillType);
		iStream.read((char*)&m_CEffectID , szCEffectID);
	}

	__END_CATCH
}

void CGSkillToSelf::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_2(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_SkillType),
							pEOStream->writeEncrypt(m_CEffectID));
	}
	else
#endif
	{
		oStream.write((char*)&m_SkillType , szSkillType);
		oStream.write((char*)&m_CEffectID , szCEffectID);
	}

	__END_CATCH
}

void CGSkillToSelf::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSkillToSelfHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSkillToSelf::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSkillToSelf("
		<< "SkillType:" << (int)m_SkillType 
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
