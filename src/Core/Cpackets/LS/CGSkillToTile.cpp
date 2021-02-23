//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToTile.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToTile.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGSkillToTile::CGSkillToTile () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGSkillToTile::~CGSkillToTile () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGSkillToTile::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_SkillType),
							pEIStream->readEncrypt(m_CEffectID),
							pEIStream->readEncrypt(m_X),
							pEIStream->readEncrypt(m_Y));
	}
	else
#endif
	{
		iStream.read((char*)&m_SkillType , szSkillType);
		iStream.read((char*)&m_CEffectID , szCEffectID);
		iStream.read((char*)&m_X , szCoord);
		iStream.read((char*)&m_Y , szCoord);
	}


	__END_CATCH
}

void CGSkillToTile::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_SkillType),
							pEOStream->writeEncrypt(m_CEffectID),
							pEOStream->writeEncrypt(m_X),
							pEOStream->writeEncrypt(m_Y));
	}
	else
#endif
	{
		oStream.write((char*)&m_SkillType , szSkillType);
		oStream.write((char*)&m_CEffectID , szCEffectID);
		oStream.write((char*)&m_X , szCoord);
		oStream.write((char*)&m_Y , szCoord);
	}

	__END_CATCH
}

void CGSkillToTile::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSkillToTileHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSkillToTile::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSkillToTile("
		<< "SkillType:" << (int)m_SkillType 
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",X:" << (int)m_X 
		<< ",Y: " << (int)m_Y 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
