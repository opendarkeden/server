//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToObject.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToObject.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGSkillToObject::CGSkillToObject () 
     throw ()
{
	__BEGIN_TRY
	m_CEffectID = 0;
	__END_CATCH
}

CGSkillToObject::~CGSkillToObject () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGSkillToObject::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_SkillType),
							pEIStream->readEncrypt(m_CEffectID),
							pEIStream->readEncrypt(m_TargetObjectID));
	}
	else
#endif
	{
		iStream.read((char*)&m_SkillType , szSkillType);
		iStream.read((char*)&m_CEffectID , szCEffectID);
		iStream.read((char*)&m_TargetObjectID , szObjectID);
	}

	__END_CATCH
}

void CGSkillToObject::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_SkillType),
							pEOStream->writeEncrypt(m_CEffectID),
							pEOStream->writeEncrypt(m_TargetObjectID));
	}
	else
#endif
	{
		oStream.write((char*)&m_SkillType , szSkillType);
		oStream.write((char*)&m_CEffectID , szCEffectID);
		oStream.write((char*)&m_TargetObjectID , szObjectID);
	}

	__END_CATCH
}

void CGSkillToObject::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSkillToObjectHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSkillToObject::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSkillToObject("
		<< "SkillType:"      << (int)m_SkillType 
		<< ",CEffectID:"     << (int)m_CEffectID 
		<< ",TargetSelfID :" << (int)m_TargetObjectID 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
