//////////////////////////////////////////////////////////////////////////////
// Filename    : CGCastingSkill.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGCastingSkill.h"

CGCastingSkill::CGCastingSkill () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}
	
CGCastingSkill::~CGCastingSkill () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGCastingSkill::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_SkillType);

	__END_CATCH
}
		    
void CGCastingSkill::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_SkillType);

	__END_CATCH
}

void CGCastingSkill::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGCastingSkillHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGCastingSkill::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGCastingSkill("
		<< "SkillType: " << (int)m_SkillType
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
