//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddVampire.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCAddVampire.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCAddVampire::~GCAddVampire()
	throw()
{
	__BEGIN_TRY
	
	SAFE_DELETE(m_pEffectInfo);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCAddVampire::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	m_VampireInfo.read( iStream );

	m_pEffectInfo = new EffectInfo();
	m_pEffectInfo->read( iStream );

	m_pPetInfo = new PetInfo();
	m_pPetInfo->read( iStream );

	if ( m_pPetInfo->getPetType() == PET_NONE ) SAFE_DELETE( m_pPetInfo );

	m_pNicknameInfo = new NicknameInfo;
	m_pNicknameInfo->read(iStream);

	m_StoreOutlook.read(iStream);

	iStream.read(m_FromFlag );

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCAddVampire::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	static PetInfo NullPetInfo;

	m_VampireInfo.write( oStream );
	m_pEffectInfo->write( oStream );

	if ( m_pPetInfo == NULL ) 
		NullPetInfo.write( oStream );
	else
	{
		m_pPetInfo->setSummonInfo(0);
		m_pPetInfo->write( oStream );
	}

	if ( m_pNicknameInfo == NULL )
	{
		NicknameInfo noNick;
		noNick.setNicknameType( NicknameInfo::NICK_NONE );
		noNick.write( oStream );
	}
	else
	{
		m_pNicknameInfo->write( oStream );
	}

	m_StoreOutlook.write(oStream);
	oStream.write(m_FromFlag);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCAddVampire::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddVampireHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string GCAddVampire::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddVampire("
		<< "VampireInfo:" << m_VampireInfo.toString()
		<< ",EffectInfo:" << m_pEffectInfo->toString()
		<< ",FromFlag:" << (int)m_FromFlag
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
