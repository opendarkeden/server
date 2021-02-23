//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLearnSkill.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGLearnSkill.h"

void CGLearnSkill::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_SkillType);
	iStream.read(m_DomainType);

	__END_CATCH
}
		    
void CGLearnSkill::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_SkillType);
	oStream.write(m_DomainType);

	__END_CATCH
}

void CGLearnSkill::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGLearnSkillHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGLearnSkill::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	string       domain;
	switch (m_DomainType)
	{
		case SKILL_DOMAIN_BLADE:   domain = "BLADE";   break;
		case SKILL_DOMAIN_SWORD:   domain = "SWORD";   break;
		case SKILL_DOMAIN_GUN:     domain = "GUN";     break;
		//case SKILL_DOMAIN_RIFLE:   domain = "RIFLE";   break;
		case SKILL_DOMAIN_ENCHANT: domain = "ENCHANT"; break;
		case SKILL_DOMAIN_HEAL:    domain = "HEAL";    break;
		case SKILL_DOMAIN_ETC:     domain = "ETC";     break;
		case SKILL_DOMAIN_VAMPIRE: domain = "VAMPIRE"; break;
		default:                   domain = "UNKNOWN"; break;
	}

	msg << "CGLearnSkill("
	    << "SkillType:"  << (int)m_SkillType << ","
	    << "DomainType:" << domain 
	    << ")";
	
	return msg.toString();

	__END_CATCH
}
