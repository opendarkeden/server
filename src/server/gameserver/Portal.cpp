//////////////////////////////////////////////////////////////////////////////
// Filename    : NormalPortal.cpp
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Portal.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "LogClient.h"
#include "Slayer.h"
#include "Vampire.h"
#include "TimeManager.h"
#include "WeatherManager.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketUtil.h"
#include "Slayer.h"
#include "Vampire.h"
#include "ZoneUtil.h"
#include "Properties.h"
#include "Guild.h"
#include "GuildManager.h"

#include "quest/Trigger.h"

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class isSameZoneID 
{
public:

	// constructor
	isSameZoneID(ZoneID_t ZoneID) : m_ZoneID(ZoneID) {}

	// operator
	bool operator () (PortalTargetInfo* pPortalTargetInfo) throw ()
	{
		return pPortalTargetInfo->getZoneID() == m_ZoneID;
	}

private:

	// EffectClass identifier
	ZoneID_t m_ZoneID;
};



//////////////////////////////////////////////////////////////////////////////
//
// class PrivatePortal member methods
//
//////////////////////////////////////////////////////////////////////////////

PrivatePortal::PrivatePortal(ObjectID_t objectID)
	throw()
: Portal(objectID)
{
	__BEGIN_TRY

	m_pTarget = new PortalTargetInfo();

	__END_CATCH
}

PrivatePortal::~PrivatePortal()
	throw()
{
	__BEGIN_TRY

	SAFE_DELETE(m_pTarget);

	__END_CATCH
}

ZoneID_t PrivatePortal::getZoneID() const 
	throw() 
{ 
	__BEGIN_TRY

	Assert(m_pTarget != NULL);
	return m_pTarget->getZoneID(); 

	__END_CATCH
}

void PrivatePortal::setZoneID(ZoneID_t zoneID) 
	throw() 
{ 
	__BEGIN_TRY

	Assert(m_pTarget != NULL);
	m_pTarget->setZoneID(zoneID); 

	__END_CATCH
}


ZoneCoord_t PrivatePortal::getX() const 
	throw() 
{ 
	__BEGIN_TRY

	Assert(m_pTarget != NULL);
	return m_pTarget->getX(); 

	__END_CATCH
}

void PrivatePortal::setX(ZoneCoord_t x) 
	throw() 
{ 
	__BEGIN_TRY

	Assert(m_pTarget != NULL);
	m_pTarget->setX(x); 

	__END_CATCH
}

ZoneCoord_t PrivatePortal::getY() const
	throw() 
{ 
	__BEGIN_TRY

	Assert(m_pTarget != NULL);
	return m_pTarget->getY(); 

	__END_CATCH
}

void PrivatePortal::setY(ZoneCoord_t y) 
	throw() 
{ 
	__BEGIN_TRY

	Assert(m_pTarget != NULL);
	m_pTarget->setY(y); 

	__END_CATCH
}


bool PrivatePortal::activate (Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(m_pTarget != NULL);
	Assert(pCreature->isPC());

	transportCreature(pCreature, m_pTarget->getZoneID(), m_pTarget->getX(), m_pTarget->getY(), true);

	return true;

	__END_DEBUG
	__END_CATCH
}

string PrivatePortal::toString () const
	throw ()
{
	StringStream msg;

	msg << "NormalPortal("
		<< "Type:"   << (int)m_PortalType
		<< "ZoneID:" << (int)m_pTarget->getZoneID()
		<< ",X:"     << (int)m_pTarget->getX()
		<< ",Y:"     << (int)m_pTarget->getY()
		<< ")";

	return msg.toString();
}




//////////////////////////////////////////////////////////////////////////////
//
// class NormalPortal member methods
//
//////////////////////////////////////////////////////////////////////////////

bool NormalPortal::activate (Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(m_pTarget != NULL);
	Assert(pCreature->isPC());

	switch ( getObjectType() )
	{
		case PORTAL_SLAYER:
			if ( !pCreature->isSlayer() && !pCreature->isFlag( Effect::EFFECT_CLASS_CAN_ENTER_SLAYER_PORTAL ) ) return false;
			if ( pCreature->isSlayer() && dynamic_cast<Slayer*>(pCreature)->hasRideMotorcycle() ) return false;
			break;
		case PORTAL_VAMPIRE:
			if ( !pCreature->isVampire() && !pCreature->isFlag( Effect::EFFECT_CLASS_CAN_ENTER_VAMPIRE_PORTAL ) ) return false;
			break;
		case PORTAL_OUSTERS:
			if ( !pCreature->isOusters() && !pCreature->isFlag( Effect::EFFECT_CLASS_CAN_ENTER_OUSTERS_PORTAL ) ) return false;
			break;
		case PORTAL_NORMAL:
			break;
		default:
			return false;
	}

	transportCreature(pCreature, m_pTarget->getZoneID(), m_pTarget->getX(), m_pTarget->getY(), true);

	return true;

	__END_DEBUG
	__END_CATCH
}

string NormalPortal::toString () const
	throw ()
{
	StringStream msg;

	msg << "NormalPortal("
		<< "Type:"   << (int)m_PortalType
		<< "ZoneID:" << (int)m_pTarget->getZoneID()
		<< ",X:"     << (int)m_pTarget->getX()
		<< ",Y:"     << (int)m_pTarget->getY()
		<< ")";

	return msg.toString();
}



//////////////////////////////////////////////////////////////////////////////
//
// class GuildPortal member methods
//
//////////////////////////////////////////////////////////////////////////////

bool GuildPortal::activate (Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(m_pTarget != NULL);
	Assert(pCreature->isPC());

	static const uint TEAM_ZONEID = 20001;
	static const uint CLAN_ZONEID = 20001;

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPlayerCreature != NULL );

	Guild* pGuild = g_pGuildManager->getGuild( pPlayerCreature->getGuildID() );

	// 소속된 길드가 없으면 걍 무시
	if ( pGuild == NULL )
		return false;

	// 소속된 길드의 아지트가 이 서버에 없으면 무시
	if ( pGuild->getServerGroupID() != g_pConfig->getPropertyInt( "ServerID" ) )
		return false;

	// 길드의 상태가 active가 아니면 무시
	if ( pGuild->getState() != Guild::GUILD_STATE_ACTIVE )
		return false;

	// Guild Portal 종류를 Slayer, Vampire 두가지로 바꿔야 하는데 시간이 없어서 그냥 Zone ID 를 보고 구별한다.
	// 자기 종족의 길드 포탈인지 확인한다.
	if ( ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER  && m_pTarget->getZoneID() == TEAM_ZONEID )
	  || ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE && m_pTarget->getZoneID() == CLAN_ZONEID ) )
	{
		transportCreature(pCreature, pGuild->getZoneID(), m_pTarget->getX(), m_pTarget->getY(), true);
	}
	else
	{
		return false;
	}

	return true;

	__END_DEBUG
	__END_CATCH
}

string GuildPortal::toString () const
	throw ()
{
	StringStream msg;

	msg << "GuildPortal("
		<< "Type:"   << (int)m_PortalType
		<< ",X:"     << (int)m_pTarget->getX()
		<< ",Y:"     << (int)m_pTarget->getY()
		<< ")";

	return msg.toString();
}




//////////////////////////////////////////////////////////////////////////////
//
// class MultiPortal member methods
//
//////////////////////////////////////////////////////////////////////////////

bool MultiPortal::activate (Creature* pCreature, ZoneID_t ZoneID) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature->isPC());

	list<PortalTargetInfo*>::iterator itr = find_if (m_Targets.begin(), m_Targets.end(), isSameZoneID(ZoneID)); 

	if (itr == m_Targets.end()) 
	{
		// 못 찾았지렁.
		return false;
	}

	Assert((*itr) != NULL);
	
	PortalTargetInfo* pPortalTargetInfo = *itr;	// by sigi. 2002.5.8

	transportCreature(pCreature, 
						pPortalTargetInfo->getZoneID(), 
						pPortalTargetInfo->getX(), 
						pPortalTargetInfo->getY(), 
						true);

	return true;

	__END_DEBUG
	__END_CATCH
}

string MultiPortal::toString () const
	throw ()
{
	StringStream msg;

	msg << "MultiPortal("
		<< "Type:"   << (int)m_PortalType;
	for(list<PortalTargetInfo*>::const_iterator itr = m_Targets.begin() ; itr != m_Targets.end() ; itr++) {
		msg	<< ",ZoneID:" << (int)(*itr)->getZoneID()
			<< ",X:"     << (int)(*itr)->getX()
			<< ",Y:"     << (int)(*itr)->getY();
	}
	msg << ")";

	return msg.toString();
}




//////////////////////////////////////////////////////////////////////////////
//
// class TriggeredPortal member methods
//
//////////////////////////////////////////////////////////////////////////////

bool TriggeredPortal::activate(Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	list<Trigger*>&          triggers = m_TriggerManager.getTriggers();
	list<Trigger*>::iterator itr      = triggers.begin();

	// 사실 for를 반복하는 것은 무의미하다.
	// 제일 첫번째 트리거에서 조건을 만족시키지 못하면,
	// 카운터 액션이 실행되면서 리턴되어버리기 때문이다.
	for (; itr != triggers.end(); itr++)
	{
		Trigger* pTrigger = *itr;

		if (pTrigger->isAllSatisfied(Trigger::PASSIVE_TRIGGER, NULL, pCreature))
		{
			if (pTrigger->activate(NULL, pCreature)) 
			{
				return true;
			}
		}
		else
		{
			if (pTrigger->activateCounter(NULL, pCreature))
			{
				return false;
			}
		}
	}

	return false;

	__END_CATCH
}

void TriggeredPortal::load(ZoneID_t zoneid, int left, int top, int right, int bottom) 
	throw ()
{
	__BEGIN_TRY

	m_TriggerManager.load(zoneid, left, top, right, bottom);

	/*
	// AtFirst 컨디션이 있으면, 실행하고, 삭제한다.
	if (m_TriggerManager.hasCondition(Condition::CONDITION_AT_FIRST))
	{
		list<Trigger*>&          triggers = m_TriggerManager.getTriggers();
		list<Trigger*>::iterator itr      = triggers.begin();

		for (; itr != triggers.end(); itr++)
		{
			Trigger* pTrigger = *itr;
			if (pTrigger->hasCondition(Condition::CONDITION_AT_FIRST))
			{
				pTrigger->activate(NULL);
				triggers.erase(itr);
				break;
			}
		}
	}
	*/

	__END_CATCH
}

string TriggeredPortal::toString() const throw()
{
	__BEGIN_TRY

	StringStream msg;
	return msg.toString();

	__END_CATCH
}
