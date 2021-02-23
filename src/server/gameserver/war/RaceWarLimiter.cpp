#include "RaceWarLimiter.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "VSDateTime.h"
#include <stdio.h>
#include <fstream>

//--------------------------------------------------------------------------------
//
// 					PCWarLimiter
//
//--------------------------------------------------------------------------------
PCWarLimiter::PCWarLimiter()
{
}

PCWarLimiter::~PCWarLimiter()
{
}

//--------------------------------------------------------------------------------
// load
//--------------------------------------------------------------------------------
void	PCWarLimiter::load() 
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT ID, MinLevel, MaxLevel, LimitNum, CurrentNum FROM %s WHERE Race=%d", 
				getTableName().c_str(), (int)getRace());

		while (pResult->next()) 
		{
			int 	ID 			= pResult->getInt(1);
			int 	MinLevel 	= pResult->getInt(2);
			int 	MaxLevel 	= pResult->getInt(3);
			int 	Limit 		= pResult->getInt(4);
			int 	Current 	= pResult->getInt(5);

			LevelLimitInfo lli( ID, MinLevel, MaxLevel, Limit );
			lli.setCurrent( Current );

			addLimitInfo( lli );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// saveCurrent
//
// lock걸린 상태에서 불려야 한다.
//--------------------------------------------------------------------------------
void	PCWarLimiter::clearCurrent()
	throw (Error)
{
	__BEGIN_TRY

	// 참가 인원을 0으로
	int num = m_LimitInfos.size();
	for (int i=0; i<num; i++)
	{
		LimitInfo_t* pLI = &(m_LimitInfos[i]);

		pLI->setCurrent( 0 );
	}

	// DB에도 0으로 바꿔준다.
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
			"UPDATE %s SET CurrentNum=0", getTableName().c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// saveCurrent
//
// lock걸린 상태에서 불려야 한다.
//--------------------------------------------------------------------------------
void	PCWarLimiter::saveCurrent(const LevelLimitInfo* pLI) const
	throw (Error)
{
	__BEGIN_TRY

	Assert(pLI!=NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
			"UPDATE %s SET CurrentNum=%d WHERE ID=%d", 
			getTableName().c_str(), pLI->getCurrent(), pLI->getID());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// join
//--------------------------------------------------------------------------------
bool 	PCWarLimiter::join(PlayerCreature* pPC) 
	throw (Error)
{
	__BEGIN_TRY

	bool isJoin = false;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	LimitInfo_t* pLI = getLimitInfo(pPC);

	if (pLI!=NULL
		&& !pLI->isLimit() )
	{
		pLI->increase();
		saveCurrent( pLI );

		isJoin = true;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return isJoin;

	__END_CATCH
}
	
//--------------------------------------------------------------------------------
// leave
//--------------------------------------------------------------------------------
bool	PCWarLimiter::leave(PlayerCreature* pPC) 
	throw (Error)
{
	__BEGIN_TRY

	bool isLeave = false;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	LimitInfo_t* pLI = getLimitInfo(pPC);

	if (pLI!=NULL)
	{
		pLI->decrease();
		saveCurrent( pLI );

		isLeave = true;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return isLeave;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// 					SlayerWarLimiter
//
//--------------------------------------------------------------------------------
SlayerWarLimiter::SlayerWarLimiter()
{
	m_Mutex.setName("SlayerWarLimiter");
}

SlayerWarLimiter::~SlayerWarLimiter()
{
}

//--------------------------------------------------------------------------------
// getLimitInfo( PC )
//--------------------------------------------------------------------------------
SlayerWarLimiter::LimitInfo_t*
SlayerWarLimiter::getLimitInfo(PlayerCreature* pPC)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);
	Assert(pPC->isSlayer());
	Assert(!m_LimitInfos.empty());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
	int SUM = pSlayer->getSTR(ATTR_BASIC) 
				+ pSlayer->getDEX(ATTR_BASIC) 
				+ pSlayer->getINT(ATTR_BASIC);
	int Level = SUM;

	int num = m_LimitInfos.size();
	for (int i=0; i<num; i++)
	{
		LimitInfo_t* pLI = &(m_LimitInfos[i]);

		if (pLI->isLevelInRange( Level ))
		{
			return pLI;
		}
	}

	return NULL;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// 					VampireWarLimiter
//
//--------------------------------------------------------------------------------
VampireWarLimiter::VampireWarLimiter()
{
	m_Mutex.setName("VampireWarLimiter");
}

VampireWarLimiter::~VampireWarLimiter()
{
}

//--------------------------------------------------------------------------------
// getLimitInfo( PC )
//--------------------------------------------------------------------------------
VampireWarLimiter::LimitInfo_t*
VampireWarLimiter::getLimitInfo(PlayerCreature* pPC)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);
	Assert(pPC->isVampire());
	Assert(!m_LimitInfos.empty());

	Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
	int Level = pVampire->getLevel();

	int num = m_LimitInfos.size();

	for (int i=0; i<num; i++)
	{
		LimitInfo_t* pLI = &(m_LimitInfos[i]);

		if (pLI->isLevelInRange( Level ))
		{
			return pLI;
		}
	}

	return NULL;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// 					OustersWarLimiter
//
//--------------------------------------------------------------------------------
OustersWarLimiter::OustersWarLimiter()
{
	m_Mutex.setName("OustersWarLimiter");
}

OustersWarLimiter::~OustersWarLimiter()
{
}

//--------------------------------------------------------------------------------
// getLimitInfo( PC )
//--------------------------------------------------------------------------------
OustersWarLimiter::LimitInfo_t*
OustersWarLimiter::getLimitInfo(PlayerCreature* pPC)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);
	Assert(pPC->isOusters());
	Assert(!m_LimitInfos.empty());

	Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
	int Level = pOusters->getLevel();

	int num = m_LimitInfos.size();

	for (int i=0; i<num; i++)
	{
		LimitInfo_t* pLI = &(m_LimitInfos[i]);

		if (pLI->isLevelInRange( Level ))
		{
			return pLI;
		}
	}

	return NULL;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//						RaceWarLimiter
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// clear
//--------------------------------------------------------------------------------
void	RaceWarLimiter::clearCurrent() 
	throw (Error)
{
	__BEGIN_TRY

	m_SlayerWarLimiter.clearCurrent();
	m_VampireWarLimiter.clearCurrent();
	m_OustersWarLimiter.clearCurrent();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// load
//--------------------------------------------------------------------------------
void	RaceWarLimiter::load() 
	throw (Error)
{
	__BEGIN_TRY

	m_SlayerWarLimiter.load();
	m_VampireWarLimiter.load();
	m_OustersWarLimiter.load();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// join
//--------------------------------------------------------------------------------
bool	RaceWarLimiter::join(PlayerCreature* pPC) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	bool isJoin = false;

	if (pPC->isSlayer())
	{
		isJoin = m_SlayerWarLimiter.join( pPC );
	}
	else if (pPC->isVampire())
	{
		Assert(pPC->isVampire());

		isJoin = m_VampireWarLimiter.join( pPC );
	}
	else if (pPC->isOusters())
	{
		Assert(pPC->isOusters());

		isJoin = m_OustersWarLimiter.join( pPC );
	}

	if (isJoin)
	{
		addPCList( pPC );
		pPC->setFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET );
	}

	return isJoin;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// leave
//--------------------------------------------------------------------------------
bool	RaceWarLimiter::leave(PlayerCreature* pPC) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	bool isLeave = false;

	if (pPC->isSlayer())
	{
		isLeave = m_SlayerWarLimiter.leave( pPC );
	}
	else if (pPC->isVampire())
	{
		Assert(pPC->isVampire());

		isLeave = m_VampireWarLimiter.leave( pPC );
	}
	else if (pPC->isOusters())
	{
		Assert(pPC->isOusters());

		isLeave = m_OustersWarLimiter.leave( pPC );
	}

	if (isLeave)
	{
		removePCList( pPC );
	}

	return isLeave;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get LimitInfo( race, index )
//--------------------------------------------------------------------------------
LevelLimitInfo*    RaceWarLimiter::getLimitInfo(Race_t race, int index) 
	throw (Error)
{
	__BEGIN_TRY

	if (race==RACE_SLAYER)
	{
		return m_SlayerWarLimiter.getLimitInfoByIndex( index );
	}
	else if (race==RACE_VAMPIRE)
	{
		return m_VampireWarLimiter.getLimitInfoByIndex( index );
	}

	Assert(race==RACE_OUSTERS);

	return m_OustersWarLimiter.getLimitInfoByIndex( index );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// clear PCList
//--------------------------------------------------------------------------------
void     RaceWarLimiter::clearPCList()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	VSDateTime current = VSDateTime::currentDateTime();
	char filename[128];
	sprintf(filename, "RaceWarPCList%s.txt", current.toString().c_str());
	ofstream file(filename, ios::out | ios::app);

	int num[3] = { 0, 0, 0 };

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery(
				"SELECT Name, Race FROM RaceWarPCList");

		while (pResult->next())
		{
			string 	Name 	= pResult->getString(1);
			int		Race	= pResult->getInt(1);

			file << "[" << Race << "] " << Name << endl;

			num[Race]++;
		}

		pStmt->executeQuery("DELETE FROM RaceWarPCList");

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	file << "NumSlayer = " << num[0] << endl;
	file << "NumVampire = " << num[1] << endl;
	file << "NumOusters = " << num[2] << endl;

	file.close();


	__END_CATCH
}

//--------------------------------------------------------------------------------
// add PCList
//--------------------------------------------------------------------------------
void     RaceWarLimiter::addPCList(PlayerCreature* pPC)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
			"INSERT IGNORE INTO RaceWarPCList (Name, Race) VALUES ('%s', %d)", pPC->getName().c_str(), (int)pPC->getRace());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)


	__END_CATCH
}

//--------------------------------------------------------------------------------
// isIn PCList
//--------------------------------------------------------------------------------
bool     RaceWarLimiter::isInPCList(PlayerCreature* pPC)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	bool bExist = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT count(*) FROM RaceWarPCList WHERE Name='%s'", pPC->getName().c_str());

		if (pResult->next())
		{
			int count = pResult->getInt(1);

			bExist = count > 0;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return bExist;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// remove PCList
//--------------------------------------------------------------------------------
void     RaceWarLimiter::removePCList(PlayerCreature* pPC)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			pStmt->executeQuery(
				"DELETE FROM RaceWarPCList WHERE Name='%s'",
					pPC->getName().c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)


	__END_CATCH
}
