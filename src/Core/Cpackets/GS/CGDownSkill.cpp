//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDownSkill.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDownSkill.h"

void CGDownSkill::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_SkillType);

	__END_CATCH
}
		    
void CGDownSkill::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_SkillType);

	__END_CATCH
}

void CGDownSkill::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGDownSkillHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGDownSkill::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGDownSkill("
	    << "SkillType:"  << (int)m_SkillType << ","
	    << ")";
	
	return msg.toString();

	__END_CATCH
}
