//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitGuild.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitGuild.h"


void CGQuitGuild::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_GuildID);

	__END_CATCH
}

void CGQuitGuild::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_GuildID);

	__END_CATCH
}

void CGQuitGuild::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGQuitGuildHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGQuitGuild::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGQuitGuild()";
	return msg.toString();

	__END_CATCH
}
