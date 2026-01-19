//////////////////////////////////////////////////////////////////////////////
// Filename   : TimeManager.cpp
// Written By : Reiot
//////////////////////////////////////////////////////////////////////////////

#include "TimeManager.h"

#include <time.h>

#include "Properties.h"

//////////////////////////////////////////////////////////////////////////////
// initialize
//////////////////////////////////////////////////////////////////////////////
void TimeManager::init()

{
    __BEGIN_TRY

    try {
        // ���� ���� �ð�, ���� ���� �ð��� ȯ�� ���Ͽ��� �о�´�.
        string strBaseGameTime = g_pConfig->getProperty("BaseGameTime");
        string strBaseRealTime = g_pConfig->getProperty("BaseRealTime");

        size_t yearEnd = strBaseGameTime.find('-', 0);
        size_t monEnd = strBaseGameTime.find('-', yearEnd + 1);
        size_t dayEnd = strBaseGameTime.find_last_not_of(' ');

        string year = strBaseGameTime.substr(0, yearEnd);
        string month = strBaseGameTime.substr(yearEnd + 1, monEnd - yearEnd);
        string day = strBaseGameTime.substr(monEnd + 1, dayEnd - monEnd);

        // cout << yearEnd << ":" << monEnd << ":" << dayEnd << endl;
        // cout << "BaseGameTime : " << year << "/" << month << "/" << day << endl;

        yearEnd = strBaseRealTime.find('-', 0);
        monEnd = strBaseRealTime.find('-', yearEnd + 1);
        dayEnd = strBaseRealTime.find_last_not_of(' ');

        year = strBaseRealTime.substr(0, yearEnd);
        month = strBaseRealTime.substr(yearEnd + 1, monEnd);
        day = strBaseRealTime.substr(monEnd + 1, string::npos);

        // cout << yearEnd << ":" << monEnd << ":" << dayEnd << endl;
        // cout << "BaseRealTime : " << year << "/" << month << "/" << day << endl;

        // ���� ���� �ð� : 1999�� 8�� 18��
        // ���� ���� �ð� : 1990�� 7�� 20��
        // ��,���� ������ ��� �ð������� 0 ���� �����Ѵٴ� �� ������ ��.
        struct tm baseGameTime;
        baseGameTime.tm_year = 90; // 1990��
        baseGameTime.tm_mon = 6;   // 7��
        baseGameTime.tm_mday = 20; // 20��
        baseGameTime.tm_hour = 0;  // 0��
        baseGameTime.tm_min = 0;   // 0��
        baseGameTime.tm_sec = 0;   // 0��
        baseGameTime.tm_isdst = 0; // !����Ÿ��

        // ���� ���� �ð� : 2003�� 1�� 1��
        struct tm baseRealTime;
        baseRealTime.tm_year = 103; // 2003��
        baseRealTime.tm_mon = 9;    // 10��
        baseRealTime.tm_mday = 1;   // 1��
        baseRealTime.tm_hour = 0;   // 0��
        baseRealTime.tm_min = 0;    // 0��
        baseRealTime.tm_sec = 0;    // 0��
        baseRealTime.tm_isdst = 0;  // !����Ÿ��

        // cout << "asctime(m_BaseGameTime) : " << asctime(&baseGameTime);
        // cout << "asctime(m_BaseRealTime) : " << asctime(&baseRealTime);

        m_BaseGameTime = mktime(&baseGameTime);
        m_BaseRealTime = mktime(&baseRealTime);

        // cout << "BaseGameTime(" << m_BaseGameTime << ") :" << ctime(&m_BaseGameTime);
        // cout << "BaseRealTime(" << m_BaseRealTime << ") :" << ctime(&m_BaseRealTime);

    } catch (NoSuchElementException& nsee) {
        throw Error(nsee.toString());
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ���� ���� �ð��� �˾Ƴ���.
//////////////////////////////////////////////////////////////////////////////
GameTime TimeManager::getGameTime() const

{
    __BEGIN_TRY
    // ���� �ð��� �����Ѵ�.
    time_t currentTime = time(0);

    //
    // �ǽð��� ���ӽð��� ���ؼ� 5�� ������ ����ȴٴ� ���� �̿��ؼ�
    // ���� �ð��� ���Ѵ�.
    //
    // (���ӽð� = ���ذ��ӽð� + (����ǽð� - ���ؽǽð�)* 5
    //
    // time_t gameTime = m_BaseGameTime + (currentTime - m_BaseRealTime)* 24;
    time_t gameTime = (currentTime - m_BaseRealTime) * 24;

    //	ITV�� ȫ����.
    //	time_t gameTime = m_BaseGameTime + (currentTime - m_BaseRealTime)* 1440;

    // GameTime ��ü�� �ʱ�ȭ�ϱ� ���ؼ���, tm ��Ʈ��ó�� ����
    // �Ѵ�. tm ��Ʈ��ó���� ��,���� ������ ������ 0���� �����Ѵٴ� ���� ������ ��.
    tm ltm;
    localtime_r(&gameTime, &ltm);
    // struct tm* ptm = localtime(&gameTime);

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
// ���� ���� �ð��� time_t ������ �˾Ƴ���.
//////////////////////////////////////////////////////////////////////////////
time_t TimeManager::getgametime() const

{
    __BEGIN_TRY
    //
    // �ǽð��� ���ӽð��� ���ؼ� 5�� ������ ����ȴٴ� ���� �̿��ؼ�
    // ���� �ð��� ���Ѵ�.
    //
    // (���ӽð� = ���ذ��ӽð� + (����ǽð� - ���ؽǽð�)* 5
    //
    return m_BaseGameTime + (time(0) - m_BaseRealTime) * 24;
    // ITV ȫ����.
    //	return m_BaseGameTime + (time(0) - m_BaseRealTime)* 1440;
    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isDawnTime() const

{
    __BEGIN_TRY

    if (getTimeband() == TIME_DAWN)
        return true;
    return false;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isDayTime() const

{
    __BEGIN_TRY

    if (getTimeband() == TIME_DAY)
        return true;
    return false;

    __END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isDuskTime() const

{
    __BEGIN_TRY

    if (getTimeband() == TIME_DUSK)
        return true;
    return false;

    __END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool TimeManager::isNightTime() const

{
    __BEGIN_TRY

    if (getTimeband() == TIME_NIGHT)
        return true;
    return false;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
uint TimeManager::getTimeband(void) const

{
    __BEGIN_TRY

    GameTime gameTime = getGameTime();
    BYTE hour = gameTime.getHour();

    if (DAWN_START_HOUR < hour && hour <= DAWN_END_HOUR) {
        return TIME_DAWN;
    } else if (DAY_START_HOUR < hour && hour <= DAY_END_HOUR) {
        return TIME_DAY;
    } else if (DUSK_START_HOUR < hour && hour <= DUSK_END_HOUR) {
        return TIME_DUSK;
    } else
        return TIME_NIGHT;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string TimeManager::toString() const

{
    __BEGIN_TRY
    StringStream msg;

    msg << "TimeManager:("
        << "BaseGameTime:" << ctime(&m_BaseGameTime) << "BaseRealTime:" << ctime(&m_BaseRealTime) << ")";

    return msg.toString();
    __END_CATCH
}

// global variable definition
TimeManager* g_pTimeManager = NULL;
