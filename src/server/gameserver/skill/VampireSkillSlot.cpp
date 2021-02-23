//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireSkillSlot.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "VampireSkillSlot.h"
#include "DB.h"

VampireSkillSlot::VampireSkillSlot()
	throw()
{
	__BEGIN_TRY
	m_SkillType = 0;
	m_Interval = 0;
	m_CastingTime = 0;
	__END_CATCH
}

VampireSkillSlot::VampireSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime)
	throw()
{
	__BEGIN_TRY

	m_SkillType = SkillType;
	m_Interval = Interval;
	m_CastingTime = CastingTime;

	__END_CATCH
}

VampireSkillSlot::~VampireSkillSlot()
	throw()
{
	__BEGIN_TRY

	m_SkillType = 0;
	m_Interval = 0;
	m_CastingTime = 0;

	__END_CATCH
}

void VampireSkillSlot::create(const string & OwnerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "INSERT INTO VampireSkillSave "
			<< "(OwnerID , SkillType , Delay , CastingTime , NextTime)"
			<< " VALUES ('" << OwnerID 
			<<"' , " << (int)m_SkillType
			<< " , " << (int)m_Interval
			<< " , " << (int)m_CastingTime
			<< " , " << (int)m_runTime.tv_sec
			<< ")";

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "INSERT INTO VampireSkillSave (OwnerID, SkillType, Delay, CastingTime, NextTime) VALUES ( '%s', %d, %d, %d, %d )",
								OwnerID.c_str(), m_SkillType, m_Interval, m_CastingTime, m_runTime.tv_sec );


		SAFE_DELETE(pStmt); 	// by sigi

	}
	END_DB(pStmt)

	__END_CATCH
}

void VampireSkillSlot::save(const string & OwnerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE VampireSkillSave SET "
			<< "Delay = " << (int)m_Interval
			<< " WHERE OwnerID = '" << OwnerID
			<< "' AND SkillType = " << (int)m_SkillType;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE VampireSkillSave SET Delay=%d WHERE OwnerID='%s' AND SkillType=%d",
								m_Interval, OwnerID.c_str(), m_SkillType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void VampireSkillSlot::save()
	throw(Error)
{
	__BEGIN_TRY

	Statement * pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE VampireSkillSave SET "
			<< "Delay = " << (int)m_Interval
			<< " WHERE OwnerID = '" << m_Name
			<< "' AND SkillType = " << (int)m_SkillType;

		pStmt->executeQuery(sql.toString());
		*/


		pStmt->executeQuery( "UPDATE VampireSkillSave SET Delay=%d WHERE OwnerID='%s' AND SkillType=%d",
								m_Interval, m_Name.c_str(), m_SkillType);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

Turn_t VampireSkillSlot::getRemainTurn( Timeval currentTime ) const
	throw()
{
	Turn_t remainTurn = ( m_runTime.tv_sec - currentTime.tv_sec ) * 10
					  + ( m_runTime.tv_usec - currentTime.tv_usec ) / 100000;

	return remainTurn;
}

void VampireSkillSlot::setRunTime()
	throw()
{
	// 현재 시간을 받아온다.
	getCurrentTime(m_runTime);

	// 다음 쓸 수 있는 시간을 세팅한다.
	m_runTime.tv_sec += m_Interval / 10;
	m_runTime.tv_usec += (m_Interval % 10) * 100000;
}

void VampireSkillSlot::setRunTime(Turn_t delay)
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

