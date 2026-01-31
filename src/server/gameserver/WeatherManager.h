//--------------------------------------------------------------------------------
//
// Filename   : WeatherManager.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__

// include files
#include <time.h>

#include "Assert.h"
#include "Exception.h"
#include "Types.h"

class Zone;

//--------------------------------------------------------------------------------
//
// class WeatherManager;
//
// Á¸ÀÇ ³¯¾¾¸¦ °ü¸®ÇÏ´Â °´Ã¼·Î¼­, °¢ Á¸Àº ÇÏ³ªÀÇ WeatherManager¸¦ °¡Áö°í ÀÖ¾î¾ß ÇÑ´Ù.
//
// Á¸ÀÇ ³¯¾¾´Â ÇÏ·ç¿¡ ÇÑ¹ø °áÁ¤ÀÌ µÈ´Ù. ¿ì¼±, GameTime ¿¡¼­ ¿À´ÃÀÌ ¸î¿ùÀÎÁö¸¦
// ¾Ë¾Æ³½ ´ÙÀ½, WeatherInfoManager ¿¡¼­ ÇØ´çµÇ´Â WeatherInfo ¸¦ °¡Á®¿Â´Ù.
// ÀÌÁ¦ dice ¸¦ ±¼·Á¼­, ¿À´ÃÀÇ ³¯¾¾¸¦ °áÁ¤Áþ´Â´Ù. CLEAR-RAIN-SNOW Áß ÇÏ³ª¸¦ °áÁ¤
// Áö¾úÀ¸¸é, ÀÌÁ¦ ÇÏ·çÀÇ ¼¼ºÎÀûÀÎ ³¯¾¾¸¦ °áÁ¤Áþ´Â´Ù.
//
// ³¯¾¾ÀÇ ±âº» ´ÜÀ§´Â °ÔÀÓ ½Ã°£ 1 ½Ã°£ÀÌ´Ù.
//
// WEATHER_CLEAR : ÀÌ °æ¿ì, ºñ³ª ´«ÀÌ ³»¸®Áö ¾Ê´Â´Ù.
// WEATHER_RAINY, WEATHER_SNOWY : ÇÏ·ç¿¡ ºñ°¡ ³»¸± È®·üÀ» ¹ÙÅÁÀ¸·Î ¸Å ½Ã°£¸¶´Ù
// ´ÙÀÌ½º¸¦ ±¼·Á¼­ ºñ¸¦ ³»¸®°Ô ÇÑ´Ù. ÀÌ¶§, ºñ°¡ ±×Ä¥ ½Ã°£µµ ´ÙÀÌ½º·Î °è»êÇØÁØ´Ù.
//(ºñ°¡ ³»¸®´Â ½Ã°£ ¿ª½Ãº °ÔÀÓ ½Ã°£ ÇÑ½Ã°£À» ´ÜÀ§·Î ÇÑ´Ù.)
//
// ¹ø°³°¡ Ä¡´Â ±âº» ´ÜÀ§´Â ½Ç½Ã°£ 1ºÐÀÌ¸ç, È®·üÀº(ºñÀÇ ·¹º§* 5 - 30) %ÀÌ´Ù.
//
//--------------------------------------------------------------------------------
class WeatherManager {
public:
    // constructor
    WeatherManager(Zone* pZone) : m_pZone(pZone) {
        Assert(m_pZone != NULL);
    }

    // destructor
    virtual ~WeatherManager();

    // initialize
    void init();

    // ÁöÁ¤ ½Ã°£ÀÌ µÇ¸é ³¯¾¾¸¦ ¾Ë¾Æ¼­ ¹Ù²ãÁØ´Ù. Á¸ÀÇ heartbeat ¿¡¼­ È£ÃâµÇ¾î¾ß ÇÑ´Ù.
    void heartbeat();

    // ¿À´ÃÀÇ ³¯¾¾¸¦ ¸®ÅÏÇÑ´Ù.
    Weather getTodayWeather() const {
        return m_TodayWeather;
    }

    // ¿À´Ã ºñ³ª ´«ÀÌ ¿Ã È®·üÀ» ¸®ÅÏÇÑ´Ù.
    uint getProbability() const {
        return m_Probability;
    }

    // ÇöÀçÀÇ ³¯¾¾¸¦ ¸®ÅÏÇÑ´Ù.
    Weather getCurrentWeather() const {
        return m_CurrentWeather;
    }

    // ÇöÀçÀÇ ³¯¾¾ ·¹º§À» ¸®ÅÏÇÑ´Ù.
    WeatherLevel_t getWeatherLevel() const {
        return m_WeatherLevel;
    }

    void resetDarkLightInfo() {
        m_Next10Min = time(0);
    }

    // get debug string
    string toString() const;

private:
    // ÇöÀç ¿¬°üµÇ¾î ÀÖ´Â Á¸
    Zone* m_pZone;

    // ¿À´ÃÀÇ ³¯¾¾(CLEAR/RAINY/SNOWY)
    Weather m_TodayWeather;

    // ºñ³ª ´«ÀÌ ¿Ã È®·ü(0 - 100)
    uint m_Probability;

    // ÇöÀçÀÇ ³¯¾¾
    Weather m_CurrentWeather;

    // ³¯¾¾ ·¹º§(1 - 20)
    WeatherLevel_t m_WeatherLevel;


    //--------------------------------------------------
    // ´ÙÀ½ XXX ÇÒ ½Ã°£(ÃÊ´ÜÀ§µµ ÃæºÐÇÏ´Ù)
    //--------------------------------------------------
private:
    // ³»ÀÏ
    time_t m_Tomorrow;

    // ´ÙÀ½ ³¯¾¾ º¯°æ ½Ã°£
    time_t m_NextWeatherChangingTime;

    // ´ÙÀ½ ¹ø°³ ½Ã°£
    time_t m_NextLightning;

    // ´ÙÀ½ 10ºÐ´ë
    time_t m_Next10Min;
};

#endif
