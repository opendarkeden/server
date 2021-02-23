//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectTileEffect.cpp 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectTileEffect.h"

void CGSelectTileEffect::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_EffectObjectID);

	__END_CATCH
}
		    
void CGSelectTileEffect::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_EffectObjectID);

	__END_CATCH
}

void CGSelectTileEffect::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGSelectTileEffectHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGSelectTileEffect::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGSelectTileEffect("
		<< "EffectObjectID:" << (int)m_EffectObjectID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
