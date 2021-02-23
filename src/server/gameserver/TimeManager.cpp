//////////////////////////////////////////////////////////////////////////////
// Filename   : TimeManager.cpp
// Written By : Reiot
//////////////////////////////////////////////////////////////////////////////

#include "TimeManager.h"
#include "Properties.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////////////
// initialize 
//////////////////////////////////////////////////////////////////////////////
void TimeManager::init () 
	throw (Error)
{
	__BEGIN_TRY

	try {

		// 기준 게임 시간, 기준 실제 시간을 환경 파일에서 읽어온다.
		string strBaseGameTime = g_pConfig->getProperty("BaseGameTime");
		string strBaseRealTime = g_pConfig->getProperty("BaseRealTime");

		int yearEnd = strBaseGameTime.find('-' , 0);
		int monEnd = strBaseGameTime.find('-' , yearEnd + 1);
		int dayEnd = strBaseGameTime.find_last_not_of(' ');

		string year = strBaseGameTime.substr(0 , yearEnd);
		string month = strBaseGameTime.substr(yearEnd + 1 , monEnd - yearEnd);
		string day = strBaseGameTime.substr(monEnd + 1 , dayEnd - monEnd);

		//cout << yearEnd << ":" << monEnd << ":" << dayEnd << endl;
		//cout << "BaseGameTime : " << year << "/" << month << "/" << day << endl;

		yearEnd = strBaseRealTime.find('-' , 0);
		monEnd = strBaseRealTime.find('-' , yearEnd + 1);
		dayEnd = strBaseRealTime.find_last_not_of(' ');

		year = strBaseRealTime.substr(0 , yearEnd);
		month = strBaseRealTime.substr(yearEnd + 1 , monEnd);
		day = strBaseRealTime.substr(monEnd + 1 , string::npos);

		//cout << yearEnd << ":" << monEnd << ":" << dayEnd << endl;
		//cout << "BaseRealTime : " << year << "/" << month << "/" << day << endl;

		// 기준 게임 시간 : 1999년 8월 18일
		// 기준 게임 시간 : 1990년 7월 20일
		// 년,일을 제외한 모든 시간값들은 0 부터 시작한다는 데 유의할 것.
		struct tm baseGameTime;
		baseGameTime.tm_year  = 90;		// 1990년
		baseGameTime.tm_mon   = 6;		// 7월
		baseGameTime.tm_mday  = 20;		// 20일
		baseGameTime.tm_hour  = 0;		// 0시
		baseGameTime.tm_min   = 0;		// 0분
		baseGameTime.tm_sec   = 0;		// 0초
		baseGameTime.tm_isdst = 0;		// !섬머타임
	
		// 기준 실제 시간 : 2003년 1월 1일
		struct tm baseRealTime;
		baseRealTime.tm_year  = 103;	// 2003년
		baseRealTime.tm_mon   = 9;		// 10월
		baseRealTime.tm_mday  = 1;		// 1일
		baseRealTime.tm_hour  = 0;		// 0시
		baseRealTime.tm_min   = 0;		// 0분
		baseRealTime.tm_sec   = 0;		// 0초
		baseRealTime.tm_isdst = 0;		// !섬머타임

		//cout << "asctime(m_BaseGameTime) : " << asctime(&baseGameTime);
		//cout << "asctime(m_BaseRealTime) : " << asctime(&baseRealTime);

		m_BaseGameTime = mktime(&baseGameTime);
		m_BaseRealTime = mktime(&baseRealTime);

		//cout << "BaseGameTime(" << m_BaseGameTime << ") :" << ctime(&m_BaseGameTime);
		//cout << "BaseRealTime(" << m_BaseRealTime << ") :" << ctime(&m_BaseRealTime);

	} catch (NoSuchElementException & nsee) {
		throw Error(nsee.toString());
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 현재 게임 시간을 알아낸다.
//////////////////////////////////////////////////////////////////////////////
GameTime TimeManager::getGameTime () const 
	throw ()
{
	__BEGIN_TRY
	// 현재 시간을 측정한다.
	time_t currentTime = time(0);

	//
	// 실시간이 게임시간에 비해서 5배 느리게 진행된다는 점을 이용해서
	// 게임 시간을 구한다.
	//
	// (게임시간 = 기준게임시간 + (현재실시간 - 기준실시간)* 5
	//
	//time_t gameTime = m_BaseGameTime + (currentTime - m_BaseRealTime)* 24;
	time_t gameTime = (currentTime - m_BaseRealTime)* 24;

//	ITV용 홍보용.
//	time_t gameTime = m_BaseGameTime + (currentTime - m_BaseRealTime)* 1440;

	// GameTime 객체를 초기화하기 위해서는, tm 스트럭처를 얻어내야 한다.
	// tm 스트럭처에서 년,일을 제외한 값들이 0부터 시작한다는 점에 유의할 것.
	tm ltm;
	localtime_r( &gameTime, &ltm );
	//struct tm* ptm = localtime(&gameTime);

	GameTime result;

	result.setYear(1930 + ltm.tm_year);
	result.setMonth(ltm.tm_mon + 1);
	result.setDay(ltm.tm_mday);
	result.setHour(ltm.tm_hour);
	result.setMinute(ltm.tm_min);
	result.setSecond(ltm.tm_sec);

	return result;
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 현재 게임 시간을 time_t 값으로 알아낸다.
//////////////////////////////////////////////////////////////////////////////
time_t TimeManager::getgametime () const 
	throw ()
{
	__BEGIN_TRY
	//
	// 실시간이 게임시간에 비해서 5배 느리게 진행된다는 점을 이용해서
	// 게임 시간을 구한다.
	//
	// (게임시간 = 기준게임시간 + (현재실시간 - 기준실시간)* 5
	//
	return m_BaseGameTime + (time(0) - m_BaseRealTime)* 24;
	// ITV 홍보용.
//	return m_BaseGameTime + (time(0) - m_BaseRealTime)* 1440;
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isDawnTime() const
	throw()
{
	__BEGIN_TRY

	if (getTimeband() == TIME_DAWN) return true;
	return false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isDayTime() const
	throw()
{
	__BEGIN_TRY

	if (getTimeband() == TIME_DAY) return true;
	return false;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isDuskTime() const
	throw()
{
	__BEGIN_TRY

	if (getTimeband() == TIME_DUSK) return true;
	return false;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isNightTime() const
	throw()
{
	__BEGIN_TRY

	if (getTimeband() == TIME_NIGHT) return true;
	return false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
uint TimeManager::getTimeband(void) const
	throw()
{
	__BEGIN_TRY

	GameTime gameTime = getGameTime();
	BYTE     hour     = gameTime.getHour();

	if (DAWN_START_HOUR < hour && hour <= DAWN_END_HOUR)
	{
		return TIME_DAWN;
	}
	else if (DAY_START_HOUR < hour && hour <= DAY_END_HOUR)
	{
		return TIME_DAY;
	}
	else if (DUSK_START_HOUR < hour && hour <= DUSK_END_HOUR)
	{
		return TIME_DUSK;
	}
	else return TIME_NIGHT;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string TimeManager::toString () const
	throw ()
{
	__BEGIN_TRY
	StringStream msg;

	msg << "TimeManager:(" 
			<< "BaseGameTime:" << (int)ctime(&m_BaseGameTime)
			<< "BaseRealTime:" << (int)ctime(&m_BaseRealTime)
			<< ")";

	return msg.toString();
	__END_CATCH
}

// global variable definition
TimeManager* g_pTimeManager = NULL;
