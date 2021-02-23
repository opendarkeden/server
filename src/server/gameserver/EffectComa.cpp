//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectComa.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectComa.h"
#include "Assert.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Tile.h"
#include "Zone.h"
#include "GamePlayer.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "IncomingPlayerManager.h"
#include "Event.h"
#include "EventResurrect.h"
#include "ResurrectLocationManager.h"
#include "ItemUtil.h"
#include "AlignmentManager.h"
#include "ItemFactoryManager.h"

#include "SlayerCorpse.h"
#include "VampireCorpse.h"
#include "LogClient.h"
#include "Thread.h"
    
#include "Gpackets/GCCreatureDied.h"
#include "Gpackets/GCGetOffMotorCycle.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

EffectComa::EffectComa(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

EffectComa::~EffectComa()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectComa::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);

	affect(pCreature);

	__END_CATCH 

}

void EffectComa::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectComa::unaffect(Creature* pDeadCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectComa " << "unaffect BEGIN(Creature)" << endl;
	
	Assert(pDeadCreature != NULL);
	//Assert(pDeadCreature->isDead());

	// 이펙트 플래그를 삭제해준다.
	pDeadCreature->removeFlag(Effect::EFFECT_CLASS_COMA);
	// 날아오면 강제로 죽이는 코드를 집어넣는다.
	if (pDeadCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pDeadCreature);
		pSlayer->setHP(0, ATTR_CURRENT);
	}
	else if (pDeadCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pDeadCreature);
		pVampire->setHP(0, ATTR_CURRENT);
	}
	else if (pDeadCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pDeadCreature);
		pOusters->setHP(0, ATTR_CURRENT);
	}

	//cout << "EffectComa " << "unaffect END(Creature)" << endl;

	__END_CATCH
}

void EffectComa::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectComa " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectComa " << "unaffect END" << endl;

	__END_CATCH
}

void EffectComa::create(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectComa::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectComa::save(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

// 스타팅 시간은 이펙트를 생성한 시간이자, 플레이어가 죽은 시간이다.
// 이 시간에다 5초를 더함으로써, canResurrect 함수에서 죽은 뒤 5초가 지나지
// 않은 사람이 Resurrect못하게 검사할 수 있다.
void EffectComa::setStartTime(void)
{
	getCurrentTime(m_StartTime);
	m_StartTime.tv_sec += 5;
}

bool EffectComa::canResurrect(void)
{
	Timeval currentTime;
	getCurrentTime(currentTime);

	if (m_StartTime < currentTime)
	{
		return true;
	}

	return false;
}

string EffectComa::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectComa("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

void EffectComaLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

EffectComaLoader* g_pEffectComaLoader = NULL;











