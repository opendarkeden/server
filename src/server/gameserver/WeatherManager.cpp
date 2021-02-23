//--------------------------------------------------------------------------------
//
// Filename   : WeatherManager.cpp
// Written By : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "WeatherManager.h"
#include "GameTime.h"
#include "TimeManager.h"
#include "WeatherInfo.h"
#include "LogClient.h"
#include "DarkLightInfo.h"
#include "Zone.h"
#include "PKZoneInfoManager.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCChangeWeather.h"
#include "Gpackets/GCLightning.h"

//--------------------------------------------------------------------------------
//
// destructor
//
// 컨테이너의 모든 객체들을 DB에 저장한 후, 삭제한다.
//
//--------------------------------------------------------------------------------
WeatherManager::~WeatherManager ()
	throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}


//--------------------------------------------------------------------------------
// initialize current zone's weather, darklevel, lightlevel
//--------------------------------------------------------------------------------
void WeatherManager::init ()
	throw (Error)
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// 오늘의 날씨를 설정한다.
	//--------------------------------------------------------------------------------

	// 오늘이 몇월인지 알기 위해서, GameTime 객체를 가져온다.
	GameTime gametime = g_pTimeManager->getGameTime();

	// 이번달의 날씨 정보를 받아온다.
	//const WeatherInfo & weatherInfo = g_pWeatherInfoManager->getWeatherInfo(gametime.getMonth());

	// 다이스를 굴려서, 오늘의 날씨를 지정한다.
	//m_TodayWeather = weatherInfo.getWeather(Dice(1,100));

	//--------------------------------------------------------------------------------
	// 내일 날짜를 설정한다.
	//--------------------------------------------------------------------------------
	
	// 게임시간을 time_t 로 받아온다.
	time_t gmtime = g_pTimeManager->getgametime();

	// tm 스트럭처로 변환, 시/분/초 값을 알아낸다.
	tm ltm;
	localtime_r( &gmtime, &ltm );
	//struct tm* ptm = localtime(&gmtime);

	// 게임 시간으로 내일까지 남은 초를 계산한다.
	int dSec = (23 - ltm.tm_hour)* 3600 + (59 - ltm.tm_min)* 60 + (60 - ltm.tm_sec);

	// (남은 게임 시간 / 5) 를 현재 실시간에 더하면, 내일의 실제 시간이 나온다.
	time_t currentTime = time(0);
	m_Tomorrow = currentTime + dSec / 5;

	//--------------------------------------------------------------------------------
	// 현재의 날씨, 날씨레벨, 다음날씨변경시간을 설정한다.
	//--------------------------------------------------------------------------------
	// 비/눈이 올 확률과 현재의 날씨를 결정한다.
	
	m_TodayWeather = WEATHER_CLEAR;
	m_Probability = 0;
	m_CurrentWeather = WEATHER_CLEAR; 
	m_WeatherLevel = 0;

	m_NextWeatherChangingTime = m_Tomorrow;
	m_NextLightning = m_Tomorrow;

	/*
	if (m_TodayWeather == WEATHER_CLEAR) 
	{
		// 맑은 날은 무조건 맑다.
		m_Probability = 0;
		m_CurrentWeather = WEATHER_CLEAR; 
		m_WeatherLevel = 0;

		m_NextWeatherChangingTime = m_Tomorrow;
		m_NextLightning = m_Tomorrow;
	}
	else 
	{
		m_Probability = Dice(3,100) / 3;		// 비나 눈이 올 확률
		m_CurrentWeather = (Dice(1,100) < m_Probability) ? m_TodayWeather : WEATHER_CLEAR ;
		m_WeatherLevel = (m_CurrentWeather != WEATHER_CLEAR) ? Dice(3,20) / 3 : 0;

		// 비/눈은 최대 20 분(실시간)동안 내린다.
		// 따라서, 다음 날씨 변경 시간은 현재 시간 + (1-20min)* 60sec 후가 된다.
		// 일단 테스트를 위해서 주기를 짧게
		//m_NextWeatherChangingTime = time(0) + Dice(1,20)* 60;
		m_NextWeatherChangingTime = time(0) + 60;	

		// 일단 테스트를 위해서 주기를 짧게
		//m_NextLightning = time(0) + 60;
		m_NextLightning = time(0) + 10;
	}
	*/

	//--------------------------------------------------------------------------------
	// 현재의 존의 밝기와 어둡기 레벨, 다음 변경시간을 설정한다.
	//--------------------------------------------------------------------------------
	DarkLightInfo* pDIInfo = g_pDarkLightInfoManager->getCurrentDarkLightInfo( m_pZone );
	m_pZone->setDarkLevel(pDIInfo->getDarkLevel());
	m_pZone->setLightLevel(pDIInfo->getLightLevel());

	// 게임 시간으로 다음 10분대가 게임시간 몇 초 후인지 계산한다.
	dSec = (9 - ltm.tm_min / 10)* 60 + (60 - ltm.tm_sec);
	m_Next10Min = currentTime + dSec / 5;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// 지정 시간이 되면 날씨를 알아서 바꿔준다. 존의 heartbeat 에서 호출되어야 한다.
//--------------------------------------------------------------------------------
void WeatherManager::heartbeat () 
	throw (Error)
{
	// 노멀 필드가 아니라면 아무 것도 할 필요가 없다.
	if (m_pZone->getZoneType() != ZONE_NORMAL_FIELD) return;

	// PK 존도 아무것도 할 필요가 없다.
	if ( g_pPKZoneInfoManager->isPKZone( m_pZone->getZoneID() ) )
		return;

	time_t currentTime = time(0);

	//--------------------------------------------------------------------------------
	// 하루가 지나간 경우, 오늘의 날씨를 바꾸고, 날씨별 확률을 계산한다.
	// 오늘의 날씨가 바뀌더라도, m_NextWeatherChangingTime 을 넘어서지
	// 않았다면 날씨는 바뀌지 않는다는 데 유의할 것.
	//--------------------------------------------------------------------------------
	if (currentTime > m_Tomorrow) 
	{
		// 오늘이 몇월인지 알기 위해서, GameTime 객체를 가져온다.
		GameTime gametime = g_pTimeManager->getGameTime();

		// 이번달의 날씨 정보를 받아온다.
		const WeatherInfo & weatherInfo = g_pWeatherInfoManager->getWeatherInfo(gametime.getMonth());

		// 다이스를 굴려서, 오늘의 날씨를 지정한다.
		m_TodayWeather = weatherInfo.getWeather(Dice(1,100));

		// 비/눈이 올 확률을 결정한다.
		// 현재 날씨는 다음날씨변경시간이 지나야만 변경된다.
		// 따라서 여기서 설정해줄 필요는 없다.
		if (m_TodayWeather == WEATHER_CLEAR) 
		{
			// 맑은 날은 무조건 맑다.
			m_Probability = 0;
		} 
		else 
		{
			m_Probability = Dice(3,100) / 3;
		}

		// 게임시간을 time_t 로 받아온다.
		time_t gmtime = g_pTimeManager->getgametime();

		// tm 스트럭처로 변환, 시/분/초 값을 알아낸다.
		tm ltm;
		localtime_r( &gmtime, &ltm );
		//struct tm* ptm = localtime(&gmtime);

		// 게임 시간으로 내일까지 남은 초를 계산한다.
		int dSec = (23 - ltm.tm_hour)* 3600 + (59 - ltm.tm_min)* 60 + (59 - ltm.tm_sec);

		// (남은 게임 시간 / 5) 를 현재 실시간에 더하면, 내일의 실제 시간이 나온다.
		m_Tomorrow = currentTime + dSec / 5;
	}

	//--------------------------------------------------------------------------------
	// 지정된 시간을 초과한 경우, 날씨를 바꿔줘야 한다.
	//--------------------------------------------------------------------------------
	if (currentTime > m_NextWeatherChangingTime) 
	{
		if (m_TodayWeather == WEATHER_CLEAR) 
		{
			// 맑은 날의 경우, 내일까지 아무런 날씨 변화도 발생하지 않는다.
			m_CurrentWeather = WEATHER_CLEAR;
			m_WeatherLevel = 0;
			m_NextWeatherChangingTime = m_Tomorrow;
			m_NextLightning = m_Tomorrow / 2;
		} 
		else 
		{
			m_CurrentWeather = (Dice(1,100) < m_Probability) ? m_TodayWeather : WEATHER_CLEAR ;
			m_WeatherLevel = (m_CurrentWeather!=WEATHER_CLEAR) ? Dice(3,20) / 3 : 0;

			// 일단 테스트를 위해서 주기를 짧게
			//m_NextWeatherChangingTime = time(0) + Dice(1,20)* 60;
			m_NextWeatherChangingTime = time(0) + 60;

			// 일단 테스트를 위해 주기를 짧게
			//m_NextLightning = time(0) + 60;
			m_NextLightning = time(0) + 20;
		}

		GCChangeWeather gcChangeWeather;
		gcChangeWeather.setWeather(m_CurrentWeather);
		gcChangeWeather.setWeatherLevel(m_WeatherLevel);

		StringStream msg;
		msg << "ZONE[" << m_pZone->getZoneID() << "] : " << gcChangeWeather.toString();
		log(LOG_DEBUG_MSG, "", "", msg.toString());

		m_pZone->broadcastPacket(&gcChangeWeather , NULL);
	}

	//--------------------------------------------------------------------------------
	// 오늘의 날씨가 '비' 이면서, 지정된 시간을 초과한 경우, 번개 체크를 해준다.
	//--------------------------------------------------------------------------------
	if (m_CurrentWeather == WEATHER_RAINY && currentTime > m_NextLightning) 
	{
		// 1d100 다이스를 굴려서, (비의 레벨* 5 - 30) 보다 작다면
		// 번개가 친 것으로 간주한다. 날씨 레벨이 최대 20 이므로,
		// 확률은 최대 70% 까지 도달할 수 있다.
		// 일단 무조건 비가 오면 번개가 치도록 한당..
		if (Dice(1 , 100) < (uint)max(0 , m_WeatherLevel* 5 - 30)) 
		{
			GCLightning gcLightning;
			gcLightning.setDelay(Dice(1,5));
			m_pZone->broadcastPacket(&gcLightning , NULL);
		}

		// 다음 번개 체크 시간을 설정한다.
		// (날씨가 맑을 경우에는 증가시켜줄 필요조차 없다.)
		m_NextLightning += 60;
	}

	//--------------------------------------------------------------------------------
	// 게임 시간 10분마다 존의 밝기와 어둡기 정보를 바꿔준다.
	//--------------------------------------------------------------------------------
	if (currentTime > m_Next10Min) 
	{
		DarkLightInfo* pDIInfo = g_pDarkLightInfoManager->getCurrentDarkLightInfo( m_pZone );

		DarkLevel_t darkLevel = pDIInfo->getDarkLevel();
		LightLevel_t lightLevel = pDIInfo->getLightLevel();

		// 어둡기나 밝기 중 하나라도 바뀌었다면.. 브로드캐스트한다.
		if (darkLevel != m_pZone->getDarkLevel() || lightLevel != m_pZone->getLightLevel()) 
		{
			m_pZone->setDarkLevel(darkLevel);
			m_pZone->setLightLevel(lightLevel);

			GCChangeDarkLight gcChangeDarkLight;
			gcChangeDarkLight.setDarkLevel(darkLevel);
			gcChangeDarkLight.setLightLevel(lightLevel);

			GCChangeDarkLight gcChangeDarkLight2;
			gcChangeDarkLight2.setDarkLevel(DARK_MAX - darkLevel);
			gcChangeDarkLight2.setLightLevel(LIGHT_MAX - lightLevel);

			m_pZone->broadcastDarkLightPacket(&gcChangeDarkLight, &gcChangeDarkLight2, NULL);

			//cout << "(DarkLevel/LightLevel) : (" << (int)darkLevel << "," << (int)lightLevel << ") at " << g_pTimeManager->getGameTime().toString() << endl;
		}
		else
		{
			//cout << "(DarkLevel/LightLevel) : (" << (int)darkLevel << "," << (int)lightLevel << ") at " << g_pTimeManager->getGameTime().toString() << endl;
		}

		m_Next10Min += 120;
	}
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string WeatherManager::toString () const 
	throw ()
{
	StringStream msg;

	msg << "WeatherManager(";
	msg << "    오늘의 날씨 : " << Weather2String[ m_TodayWeather ];
	msg << "      현재 날씨 : " << Weather2String[ m_CurrentWeather ];
	msg << "비/눈이 올 확률 : " << (int)m_Probability << "%";
	msg << "      날씨 레벨 : " << (int)m_WeatherLevel;

	time_t currentTime = time(0);

	msg << "       현재시간 : " << (int)ctime(&currentTime);
	msg << "  게임상의 내일 : " << (int)ctime(&m_Tomorrow);
	msg << "다음날씨변경시간: " << (int)ctime(&m_NextWeatherChangingTime);
	msg << "다음번개체크시간: " << (int)ctime(&m_NextLightning);

	return msg.toString();
}
