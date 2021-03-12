////////////////////////////////////////////////////////////////////////////////
// Filename    : WeatherInfo.h
// Written By  : Reiot
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __WEATHER_INFO_H__
#define __WEATHER_INFO_H__

#include "Types.h"
#include "Exception.h"

////////////////////////////////////////////////////////////////////////////////
// class WeatherInfo;
////////////////////////////////////////////////////////////////////////////////

class WeatherInfo 
{
public:
	// 확률값을 파라미터로 넘겨주면, 오늘의 날씨를 리턴한다.
	Weather getWeather(uint probability) const ;

	// 특정 날씨의 확률을 리턴한다.
	uint getProbability(Weather weather) const  { return m_Probabilities[weather]; }

	// 특정 날씨의 확률을 지정한다.
	void setProbability(Weather weather, uint prob)  { m_Probabilities[weather] = prob; }

	// get debug string
	string toString() const ;

private:
	uint m_Probabilities[WEATHER_MAX];

};


////////////////////////////////////////////////////////////////////////////////
// class WeatherInfoManager;
//
// 월별 날씨 정보를 관리하는 매니저 클래스이다.
////////////////////////////////////////////////////////////////////////////////

class WeatherInfoManager 
{
public:
	// init vision info
	void init()  { load(); }

	// load from database
	void load() ;

	// save to database
	void save()  { throw UnsupportedError(__PRETTY_FUNCTION__); }

	// get vision info
	const WeatherInfo & getWeatherInfo(int month) const 
	{
		if(month > 12) throw OutOfBoundException("too large month value");
		return m_WeatherInfos[ month - 1 ];
	}

	// get debug string
	string toString() const ;

private:
	// WeatherInfo의 이차원 배열
	WeatherInfo m_WeatherInfos[12];

};

// global variable declaration
extern WeatherInfoManager* g_pWeatherInfoManager;

#endif
