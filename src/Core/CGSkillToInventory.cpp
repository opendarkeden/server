//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToInventory.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert1.h"

CGSkillToInventory::CGSkillToInventory ()
{
  __BEGIN_TRY

    m_InventoryItemObjectID = 0; 

  __END_CATCH  

}


void CGSkillToInventory::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_5(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_SkillType),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_X),
							pEIStream->readEncrypt(m_Y),
							pEIStream->readEncrypt(m_TargetX));
		pEIStream->readEncrypt(m_TargetY);
		// pEIStream->readEncrypt(m_InventoryItemObjectID);
	}
	else
#endif
	{
		iStream.read(m_SkillType);
		iStream.read(m_ObjectID);
		iStream.read(m_X);
		iStream.read(m_Y);
		iStream.read(m_TargetX);
		iStream.read(m_TargetY);
		// iStream.read(m_InventoryItemObjectID);
	}

	__END_CATCH
}

void CGSkillToInventory::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_5(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_SkillType),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_X),
							pEOStream->writeEncrypt(m_Y),
							pEOStream->writeEncrypt(m_TargetX));
		pEOStream->writeEncrypt(m_TargetY);
		// pEOStream->writeEncrypt(m_InventoryItemObjectID);
	}
	else
#endif
	{
		oStream.write(m_SkillType);
		oStream.write(m_ObjectID);
		oStream.write(m_X);
		oStream.write(m_Y);
		oStream.write(m_TargetX);
		oStream.write(m_TargetY);
		// oStream.write(m_InventoryItemObjectID);
	}

	__END_CATCH
}

void CGSkillToInventory::execute (Player* pPlayer) 
	
{
	__BEGIN_TRY
		
	CGSkillToInventoryHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSkillToInventory::toString () const
	
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSkillToInventory("
		<< "SkillType:"  << (int)m_SkillType 
		<< ",ObjectID:"  << (int)m_ObjectID 
		<< ",X:"         << (int)m_X 
		<< ",Y:"         << (int)m_Y 
		<< ",TargetX:"   << (int)m_TargetX 
		<< ",TargetY:"   << (int)m_TargetY 
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
