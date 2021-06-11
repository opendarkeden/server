//////////////////////////////////////////////////////////////////////////////
// Filename    : CGJoinGuild.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGJoinGuild.h"


void CGJoinGuild::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	BYTE szGuildMemberIntro;

	iStream.read(m_GuildID);
	iStream.read(m_GuildMemberRank);
	iStream.read(szGuildMemberIntro);

	if (szGuildMemberIntro != 0 )
		iStream.read(m_GuildMemberIntro, szGuildMemberIntro);
	else
		m_GuildMemberIntro = "";

	__END_CATCH
}

void CGJoinGuild::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	BYTE szGuildMemberIntro = m_GuildMemberIntro.size();

	oStream.write(m_GuildID);
	oStream.write(m_GuildMemberRank);
	oStream.write(szGuildMemberIntro);

	if (szGuildMemberIntro != 0 )
		oStream.write(m_GuildMemberIntro);

	__END_CATCH
}

void CGJoinGuild::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGJoinGuildHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGJoinGuild::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGJoinGuild("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< "GuildMemberIntro:" << m_GuildMemberIntro
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
