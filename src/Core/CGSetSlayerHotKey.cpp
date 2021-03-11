//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSetSlayerHotKey.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSetSlayerHotKey.h"

void CGSetSlayerHotKey::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	for(int i = 0; i < 4; i++) 
	{
		iStream.read(m_HotKey[i]);
	}

	__END_CATCH
}
		    
void CGSetSlayerHotKey::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	for (int i = 0; i < 4; i++) 
	{
		oStream.write(m_HotKey[i]);
	}

	__END_CATCH
}

void CGSetSlayerHotKey::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSetSlayerHotKeyHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGSetSlayerHotKey::toString () const
    
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSetSlayerHotKey("
		<< "F9:" << (int)m_HotKey[0]
		<< ",F10:" << (int)m_HotKey[1]
		<< ",F11:" << (int)m_HotKey[2]
		<< ",F12:" << (int)m_HotKey[3]
		<< ")";

	return msg.toString();

	__END_CATCH
}
