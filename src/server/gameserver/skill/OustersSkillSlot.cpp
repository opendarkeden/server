//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersSkillSlot.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "OustersSkillSlot.h"
#include "DB.h"

OustersSkillSlot::OustersSkillSlot()
	throw()
{
	__BEGIN_TRY
	m_SkillType = 0;
	m_Interval = 0;
	m_CastingTime = 0;
	__END_CATCH
}

OustersSkillSlot::OustersSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime)
	throw()
{
	__BEGIN_TRY

	m_SkillType = SkillType;
	m_Interval = Interval;
	m_CastingTime = CastingTime;

	__END_CATCH
}

OustersSkillSlot::~OustersSkillSlot()
	throw()
{
	__BEGIN_TRY

	m_SkillType = 0;
	m_Interval = 0;
	m_CastingTime = 0;

	__END_CATCH
}

void OustersSkillSlot::create(const string & OwnerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "INSERT INTO OustersSkillSave (OwnerID, SkillType, Delay, CastingTime, NextTime, SkillLevel) VALUES ( '%s', %d, %d, %d, %d, %d )",
								OwnerID.c_str(), m_SkillType, m_Interval, m_CastingTime, m_runTime.tv_sec, m_ExpLevel );

		SAFE_DELETE(pStmt);

	}
	END_DB(pStmt)

	__END_CATCH
}

void OustersSkillSlot::save(const string & OwnerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE OustersSkillSave SET SkillLevel=%d, Delay=%d WHERE OwnerID='%s' AND SkillType=%d",
								m_ExpLevel, m_Interval, OwnerID.c_str(), m_SkillType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void OustersSkillSlot::destroy(const string & OwnerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "DELETE FROM OustersSkillSave WHERE OwnerID='%s' AND SkillType=%u",
								OwnerID.c_str(), m_SkillType );

		SAFE_DELETE(pStmt);

	}
	END_DB(pStmt)

	__END_CATCH
}

void OustersSkillSlot::save()
	throw(Error)
{
	__BEGIN_TRY

	save( m_Name );

	__END_CATCH
}

Turn_t OustersSkillSlot::getRemainTurn( Timeval currentTime ) const
	throw()
{
	Turn_t remainTurn = ( m_runTime.tv_sec - currentTime.tv_sec ) * 10
					  + ( m_runTime.tv_usec - currentTime.tv_usec ) / 100000;

	return remainTurn;
}

void OustersSkillSlot::setRunTime()
	throw()
{
	// 현재 시간을 받아온다.
	getCurrentTime(m_runTime);

	// 다음 쓸 수 있는 시간을 세팅한다.
	m_runTime.tv_sec += m_Interval / 10;
	m_runTime.tv_usec += (m_Interval % 10) * 100000;
}

void OustersSkillSlot::setRunTime(Turn_t delay)
	throw()
{
	// 현재 시간을 받아온다.
	getCurrentTime(m_runTime);

	// 다음 쓸 수 있는 시간을 세팅한다.
	m_runTime.tv_sec  += delay / 10;
	m_runTime.tv_usec += (delay % 10) * 100000;

	if (m_Interval != delay)
	{
		m_Interval = delay;

		switch (m_SkillType)
		{
			case SKILL_ATTACK_MELEE:
			case SKILL_ATTACK_ARMS:
			case SKILL_SELF:
			case SKILL_TILE:
			case SKILL_OBJECT:
			case SKILL_BLOOD_DRAIN:
			case SKILL_UN_BURROW:
			case SKILL_UN_TRANSFORM:
			case SKILL_UN_INVISIBILITY:
			case SKILL_THROW_HOLY_WATER:
			case SKILL_EAT_CORPSE:
			case SKILL_HOWL:
				break;
			default:
				save(m_Name); // 달리진 딜레이를 세이브한다. 
				break;
		}
	}
}

