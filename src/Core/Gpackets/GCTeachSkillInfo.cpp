//////////////////////////////////////////////////////////////////////////////
// Filename    : GCTeachSkillInfo.cpp 
// Written By  : 김성민
// Description : 
// NPC가 플레이어에게 스킬을 가르쳐 줄 때 제일 먼저 플레이어에게
// 전송되는 패킷이다. NPC가 가르쳐 줄 수 있는 기술의 범위를 기술하는 데 
// 쓰이는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#include "GCTeachSkillInfo.h"

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCTeachSkillInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_DomainType );
	iStream.read( m_TargetLevel );

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCTeachSkillInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_DomainType );
	oStream.write( m_TargetLevel );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCTeachSkillInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCTeachSkillInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCTeachSkillInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	string domain;

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

	msg << "GCTeachSkillInfo("
	    << "DomainType:"  << domain << ","
	    << "TargetLevel:" << (int)m_TargetLevel 
	    << ")";

	return msg.toString();
		
	__END_CATCH
}


