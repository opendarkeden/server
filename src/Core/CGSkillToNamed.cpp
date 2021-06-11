//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToNamed.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToNamed.h"

CGSkillToNamed::CGSkillToNamed () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGSkillToNamed::~CGSkillToNamed () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGSkillToNamed::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	BYTE szTargetName;
		
	iStream.read((char*)&m_SkillType , szSkillType);
	iStream.read((char*)&m_CEffectID , szCEffectID);
	iStream.read(szTargetName);

	if (szTargetName == 0 )
		throw InvalidProtocolException("szTargetName == 0");
	if (szTargetName > 20 )
		throw InvalidProtocolException("too long target name length");

	iStream.read(m_TargetName, szTargetName);

	__END_CATCH
}

void CGSkillToNamed::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	BYTE szTargetName = m_TargetName.size();

	if (szTargetName == 0 )
		throw InvalidProtocolException("szTargetName == 0");
	if (szTargetName > 20 )
		throw InvalidProtocolException("too long target name");

	oStream.write((char*)&m_SkillType , szSkillType);
	oStream.write((char*)&m_CEffectID , szCEffectID);
	oStream.write(szTargetName);
	oStream.write(m_TargetName);

	__END_CATCH
}

void CGSkillToNamed::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGSkillToNamedHandler::execute(this , pPlayer);

	__END_CATCH
}


string CGSkillToNamed::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGSkillToNamed("
		<< "SkillType:" << (int)m_SkillType 
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",TargetName:" << m_TargetName
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
