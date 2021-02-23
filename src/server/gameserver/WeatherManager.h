//--------------------------------------------------------------------------------
//
// Filename   : WeatherManager.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Assert.h"
#include <time.h>

class Zone;

//--------------------------------------------------------------------------------
//
// class WeatherManager;
//
// 존의 날씨를 관리하는 객체로서, 각 존은 하나의 WeatherManager를 가지고 있어야 한다. 
//
// 존의 날씨는 하루에 한번 결정이 된다. 우선, GameTime 에서 오늘이 몇월인지를
// 알아낸 다음, WeatherInfoManager 에서 해당되는 WeatherInfo 를 가져온다. 
// 이제 dice 를 굴려서, 오늘의 날씨를 결정짓는다. CLEAR-RAIN-SNOW 중 하나를 결정
// 지었으면, 이제 하루의 세부적인 날씨를 결정짓는다.
//
// 날씨의 기본 단위는 게임 시간 1 시간이다. 
//
// WEATHER_CLEAR : 이 경우, 비나 눈이 내리지 않는다.
// WEATHER_RAINY, WEATHER_SNOWY : 하루에 비가 내릴 확률을 바탕으로 매 시간마다
// 다이스를 굴려서 비를 내리게 한다. 이때, 비가 그칠 시간도 다이스로 계산해준다.
//(비가 내리는 시간 역시� 게임 시간 한시간을 단위로 한다.)
//
// 번개가 치는 기본 단위는 실시간 1분이며, 확률은(비의 레벨* 5 - 30) %이다.
//
//--------------------------------------------------------------------------------
class WeatherManager {

public:

	// constructor
	WeatherManager(Zone* pZone) throw(Error) : m_pZone(pZone) { Assert(m_pZone != NULL); }

	// destructor
	virtual ~WeatherManager() throw(Error);

	// initialize 
	void init() throw(Error);

	// 지정 시간이 되면 날씨를 알아서 바꿔준다. 존의 heartbeat 에서 호출되어야 한다.
	void heartbeat() throw(Error);

	// 오늘의 날씨를 리턴한다.
	Weather getTodayWeather() const throw() { return m_TodayWeather; }

	// 오늘 비나 눈이 올 확률을 리턴한다.
	uint getProbability() const throw() { return m_Probability; }

	// 현재의 날씨를 리턴한다.
	Weather getCurrentWeather() const throw() { return m_CurrentWeather; }

	// 현재의 날씨 레벨을 리턴한다.
	WeatherLevel_t getWeatherLevel() const throw() { return m_WeatherLevel; }

	void resetDarkLightInfo() throw() { m_Next10Min = time(0); }

	// get debug string
	string toString() const throw();

private:

	// 현재 연관되어 있는 존
	Zone* m_pZone;

	// 오늘의 날씨(CLEAR/RAINY/SNOWY)
	Weather m_TodayWeather;	

	// 비나 눈이 올 확률(0 - 100)
	uint m_Probability;

	// 현재의 날씨
	Weather m_CurrentWeather;

	// 날씨 레벨(1 - 20)
	WeatherLevel_t m_WeatherLevel;


//--------------------------------------------------
// 다음 XXX 할 시간(초단위도 충분하다)
//--------------------------------------------------
private:

	// 내일
	time_t m_Tomorrow;

	// 다음 날씨 변경 시간
	time_t m_NextWeatherChangingTime;

	// 다음 번개 시간
	time_t m_NextLightning;

	// 다음 10분대
	time_t m_Next10Min;

};

#endif
