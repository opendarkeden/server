////////////////////////////////////////////////////////////////////////////////
// Filename    : WeatherInfo.cpp
// Written By  : Reiot
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "WeatherInfo.h"
#include "DB.h"
#include "Assert.h"

////////////////////////////////////////////////////////////////////////////////
// global variable definition
////////////////////////////////////////////////////////////////////////////////
WeatherInfoManager* g_pWeatherInfoManager = NULL;

////////////////////////////////////////////////////////////////////////////////
// class WeatherInfo member methods
////////////////////////////////////////////////////////////////////////////////

Weather WeatherInfo::getWeather(uint probability) const
	
{
	__BEGIN_TRY

	Assert(m_Probabilities[WEATHER_CLEAR] + m_Probabilities[WEATHER_RAINY] + m_Probabilities[WEATHER_SNOWY] == 100);
	Assert(probability <= 100);

	if (probability < m_Probabilities[WEATHER_CLEAR])
		return WEATHER_CLEAR;
	else if (probability < + m_Probabilities[WEATHER_CLEAR] + m_Probabilities[WEATHER_RAINY])
		return WEATHER_RAINY;
	else
		return WEATHER_SNOWY;

	__END_CATCH
}

string WeatherInfo::toString() const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "WeatherInfo("
		<< "Clear:" << m_Probabilities[WEATHER_CLEAR] << "%"
		<< ",Rainy:" << m_Probabilities[WEATHER_RAINY] << "%"
		<< ",Snowy:" << m_Probabilities[WEATHER_SNOWY] << "%"
		<< ")";
	return msg.toString();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// class WeatherInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

void WeatherInfoManager::load () 
	
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		//pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt   = NEW_STMT;
		pResult = pStmt->executeQuery("SELECT Month, Clear, Rainy, Snowy FROM WeatherInfo");

		Assert(pResult->getRowCount() == 12);

		while (pResult->next()) {

			int month = pResult->getInt(1);
			m_WeatherInfos[ month - 1 ].setProbability(WEATHER_CLEAR , pResult->getInt(2));
			m_WeatherInfos[ month - 1 ].setProbability(WEATHER_RAINY , pResult->getInt(3));
			m_WeatherInfos[ month - 1 ].setProbability(WEATHER_SNOWY , pResult->getInt(4));
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH	
}

string WeatherInfoManager::toString () const
	
{
	__BEGIN_TRY
	StringStream msg;

	msg << "WeatherInfoManager(";

	for (int i=0 ; i < 12 ; i++) 
	{
		msg << (int)(i+1) << " ¿ù : " << m_WeatherInfos[i].toString();
	}

	msg << ")";

	return msg.toString();
	__END_CATCH	
}

