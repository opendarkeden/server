//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTryJoinGuild.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTryJoinGuild.h"


void CGTryJoinGuild::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_GuildID);
	iStream.read(m_GuildMemberRank);

	__END_CATCH
}

void CGTryJoinGuild::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_GuildID);
	oStream.write(m_GuildMemberRank);

	__END_CATCH
}

void CGTryJoinGuild::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGTryJoinGuildHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGTryJoinGuild::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGTryJoinGuild("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
