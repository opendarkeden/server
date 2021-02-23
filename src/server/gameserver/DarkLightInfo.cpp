//////////////////////////////////////////////////////////////////////////////
// Filename    : DarkLightInfo.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "DarkLightInfo.h"
#include "Assert.h"
#include "GameTime.h"
#include "TimeManager.h"
#include "DB.h"
#include "Zone.h"

const int DLIndexByTimeband[4] =
{
	// (month-1)*(24*6) + (hour)*6 + (minute/10)
	( 5 - 1 ) * ( 24 * 6 ) + (  5 ) * 6 + ( 50 / 10 ),	// TIME_DAWM
	( 5 - 1 ) * ( 24 * 6 ) + ( 12 ) * 6 + (  0 / 10 ),	// TIME_DAY
	( 5 - 1 ) * ( 24 * 6 ) + ( 18 ) * 6 + (  0 / 10 ),	// TIME_DUSK
	( 5 - 1 ) * ( 24 * 6 ) + (  0 ) * 6 + (  0 / 10 )	// TIME_NIGHT
};

//////////////////////////////////////////////////////////////////////////////
// class DarkLightInfo member methods
//////////////////////////////////////////////////////////////////////////////

DarkLightInfo::DarkLightInfo() 
	throw() 
{ 
	__BEGIN_TRY

	m_DarkLevel = 0; 
	m_LightLevel = 0; 

	__END_CATCH
}

DarkLightInfo::DarkLightInfo(const DarkLightInfo & dli) 
	throw() 
{ 
	__BEGIN_TRY

	m_DarkLevel = dli.m_DarkLevel; 
	m_LightLevel = dli.m_LightLevel; 

	__END_CATCH
}

string DarkLightInfo::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "DarkLightInfo("
	<< ",DarkLevel:" <<(int)m_DarkLevel
	<< ",LightLevel:" <<(int)m_LightLevel
	<< ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class DarkLightInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

DarkLightInfoManager::DarkLightInfoManager ()
	throw ()
{
	__BEGIN_TRY

	for (uint i = 0 ; i < nDarkLightInfos ; i ++) 
		m_DarkLightInfos[i] = NULL;
	
	__END_CATCH
}

DarkLightInfoManager::~DarkLightInfoManager ()
	throw ()
{
	__BEGIN_TRY

	for (uint i = 0 ; i < nDarkLightInfos ; i ++) 
		SAFE_DELETE(m_DarkLightInfos[i]);

	__END_CATCH
}

void DarkLightInfoManager::init () 
	throw (Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void DarkLightInfoManager::load () 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Month , Hour , Minute , DarkLevel , LightLevel FROM DarkLightInfo");

		while (pResult->next()) 
		{
			uint i = 0;

			BYTE month = pResult->getInt(++i);
			Assert(month != 0 && month <= 12);

			BYTE hour = pResult->getInt(++i);
			Assert(hour < 24);

			BYTE minute = pResult->getInt(++i);
			Assert(minute < 60 && minute % 10 == 0);

			DarkLightInfo* pDIInfo = new DarkLightInfo();
			pDIInfo->setDarkLevel(pResult->getInt(++i));
			pDIInfo->setLightLevel(pResult->getInt(++i));

			// 월은 1-12 이지만, 시간은 0-23 이며, 분은 0, 10, 20, 30, 40, 50 이다.
			int index = (month-1)*(24*6) + (hour)*6 + (minute/10);
			Assert(m_DarkLightInfos[index] == NULL);
			m_DarkLightInfos[ index ] = pDIInfo;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	// 지정되지 않은 빈칸은 이전값을 사용해서 복사한다.
	Assert(m_DarkLightInfos[0] != NULL);

	for (uint i = 1 ; i < nDarkLightInfos ; i ++) 
	{
		if (m_DarkLightInfos[i] == NULL) 
		{
			m_DarkLightInfos[i] = new DarkLightInfo(*m_DarkLightInfos[i-1]);
		}
	}

	__END_CATCH
}

DarkLightInfo* DarkLightInfoManager::getDarkLightInfo (BYTE month , BYTE hour , BYTE minute) 
	throw (OutOfBoundException , Error)
{
	__BEGIN_TRY

	if (month == 0 || month > 12)
		throw OutOfBoundException("invalid month");

	if (hour > 23)
		throw OutOfBoundException("invalid hour");

	if (minute > 59)
		throw OutOfBoundException("invalid minute");

	return m_DarkLightInfos[ (month-1)*(24*6) + (hour)*6 + (minute/10) ];

	__END_CATCH
}

const DarkLightInfo* DarkLightInfoManager::getDarkLightInfo (BYTE month , BYTE hour , BYTE minute) const 
	throw (OutOfBoundException , Error)
{
	__BEGIN_TRY

	if (month == 0 || month > 12)
		throw OutOfBoundException("invalid month");

	if (hour > 23)
		throw OutOfBoundException("invalid hour");

	if (minute > 59)
		throw OutOfBoundException("invalid minute");

	return m_DarkLightInfos[ (month-1)*(24*6) + (hour)*6 + (minute/10) ];

	__END_CATCH
}

const DarkLightInfo* DarkLightInfoManager::getCurrentDarkLightInfo ( Zone* pZone ) const
	throw (Error)
{
	__BEGIN_TRY

	// 존에 시간이 고정된 경우라면 적절한 DarkLight 정보를 리턴한다.
	if ( pZone != NULL && pZone->isTimeStop() )
	{
		return m_DarkLightInfos[ DLIndexByTimeband[ pZone->getTimeband() ] ];
	}

	// 글로벌 타임 매니저로부터 게임 시간을 받아온다.
	GameTime gametime = g_pTimeManager->getGameTime();

	return getDarkLightInfo(gametime.getMonth() , gametime.getHour() , gametime.getMinute());

	__END_CATCH
}

DarkLightInfo* DarkLightInfoManager::getCurrentDarkLightInfo ( Zone* pZone ) 
	throw (Error)
{
	__BEGIN_TRY

	// 존에 시간이 고정된 경우라면 적절한 DarkLight 정보를 리턴한다.
	if ( pZone != NULL && pZone->isTimeStop() )
	{
		return m_DarkLightInfos[ DLIndexByTimeband[ pZone->getTimeband() ] ];
	}

	// 글로벌 타임 매니저로부터 게임 시간을 받아온다.
	GameTime gametime = g_pTimeManager->getGameTime();

	return getDarkLightInfo(gametime.getMonth() , gametime.getHour() , gametime.getMinute());

	__END_CATCH
}

string DarkLightInfoManager::toString () const 
	throw ()
{
	__BEGIN_TRY
	StringStream msg;

	msg << "DarkLightInfoManager(";

	for (uint i = 0 ; i < nDarkLightInfos ; i ++) 
	{
		int month  = i / (24* 6 + 6);
		int hour   = (i % (24* 6 + 6)) / 6;
		int minute = ((i % (24* 6 + 6)) % 6)* 10;
		msg << month + 1 << "-" << hour << "-" << minute << " : " 
			<< (int)m_DarkLightInfos[i]->getDarkLevel() << "/" << (int)m_DarkLightInfos[i]->getLightLevel();
	}

	msg << ")";

	return msg.toString();
	__END_CATCH
}

// global variable definition
DarkLightInfoManager* g_pDarkLightInfoManager = NULL;
