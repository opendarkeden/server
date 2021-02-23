//////////////////////////////////////////////////////////////////////////////
// Filename    : VSDateTime.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "VSDateTime.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// constants definition
//////////////////////////////////////////////////////////////////////////////

static const uint FIRST_DAY      = 2361222;  // Julian day for 1752/09/14
static const int  FIRST_YEAR     = 1752;     // ### wrong for many countries
static const uint SECS_PER_DAY   = 86400;
static const uint MSECS_PER_DAY  = 86400000;
static const uint SECS_PER_HOUR  = 3600;
static const uint MSECS_PER_HOUR = 3600000;
static const uint SECS_PER_MIN   = 60;
static const uint MSECS_PER_MIN  = 60000;

static const short monthDays[] =
{
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const char* whiteSpaces = " \t\n";


//////////////////////////////////////////////////////////////////////////////
// class VSDate member methods
//////////////////////////////////////////////////////////////////////////////

VSDate::VSDate(int y, int m, int d)
{
	jd = 0;
	setYMD(y, m, d);
}

bool VSDate::isValid() const
{
	return jd >= FIRST_DAY;
}

int VSDate::year() const
{
	int y, m, d;
	jul2greg(jd, y, m, d);
	return y;
}

int VSDate::month() const
{
	int y, m, d;
	jul2greg(jd, y, m, d);
	return m;
}

int VSDate::day() const
{
	int y, m, d;
	jul2greg(jd, y, m, d);
	return d;
}

int VSDate::dayOfWeek() const
{
	return (((jd+1) % 7) + 6)%7 + 1;
}

int VSDate::dayOfYear() const
{
	return jd - greg2jul(year(), 1, 1) + 1;
}

int VSDate::daysInMonth() const
{
	int y, m, d;
	jul2greg(jd, y, m, d);
	if (m == 2 && leapYear(y)) return 29;
	else return monthDays[m];
}

int VSDate::daysInYear() const
{
	int y, m, d;
	jul2greg(jd, y, m, d);
	return leapYear(y) ? 366 : 365;
}

string VSDate::toString() const
{
	int    y, m, d;
	string result;
	char   buf1[10] = {0, };
	char   buf2[10] = {0, };
	char   buf3[10] = {0, };

	jul2greg(jd, y, m, d);

	sprintf(buf1, "%d", y);
	sprintf(buf2, "%d", m);
	sprintf(buf3, "%d", d);

	string year  = string(buf1);
	string month = string(buf2);
	string day   = string(buf3);

	if (month.size() == 1) month = "0" + month;
	if (day.size() == 1)   day   = "0" + day;

	result += year  + ".";
	result += month + ".";
	result += day;

	return result;
}

string VSDate::toStringforWeb() const
{
	int    y, m, d;
	string result;
	char   buf1[10] = {0, };
	char   buf2[10] = {0, };
	char   buf3[10] = {0, };

	jul2greg(jd, y, m, d);

	sprintf(buf1, "%d", y);
	sprintf(buf2, "%d", m);
	sprintf(buf3, "%d", d);

	string year  = string(buf1);
	string month = string(buf2);
	string day   = string(buf3);

	if (month.size() == 1) month = "0" + month;
	if (day.size() == 1)   day   = "0" + day;

	result += year.substr(3);
	result += month;
	result += day;

	return result;
}

bool VSDate::setYMD(int y, int m, int d)
{
	if (!isValid(y,m,d)) return false;

	jd = greg2jul(y, m, d);
	
	//Assert(year() == (y > 99 ? y : 1900+y) && month() == m && day() == d);
	
	return true;
}

VSDate VSDate::addDays(int ndays) const
{
	VSDate d;
	d.jd = jd + ndays;
	return d;
}

int VSDate::daysTo(const VSDate &d) const
{
	return d.jd - jd;
}

VSDate VSDate::currentDate()
{
	time_t ltime = time(NULL);
	tm     t;
	localtime_r( &ltime, &t );

	VSDate d;
	d.jd = greg2jul(t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
	return d;
}

VSDate VSDate::fromString(string text)
{
	VSDate vsd = VSDate::currentDate();

	// trim white space
    uint begin = text.find_first_not_of( whiteSpaces );
    uint end = text.find_last_not_of( whiteSpaces );
    text = text.substr( begin , end - begin + 1 );

	/////////////////////////////////////////
	// 2001.1.1
	/////////////////////////////////////////
	if (text.size() < 8) return vsd;

	uint a=0;
	uint b=0;

	a = text.find_first_of('.', 0  );
	b = text.find_first_of('.', a+1);

	if (a > b || b > text.size()) return vsd;

	int year  = atoi(text.substr(  0, a).c_str());
	int month = atoi(text.substr(a+1, b-a-1).c_str());
	int day   = atoi(text.substr(b+1, text.size()-b-1).c_str());

	vsd.setYMD(year, month, day);

	return vsd;
}

bool VSDate::isValid(int y, int m, int d)
{
	if (y >= 0 && y <= 99) y += 1900;
	else if (y < FIRST_YEAR || (y == FIRST_YEAR && (m < 9 || (m == 9 && d < 14)))) return false;
	return (d > 0 && m > 0 && m <= 12) && (d <= monthDays[m] || (d == 29 && m == 2 && leapYear(y)));
}

bool VSDate::leapYear(int y)
{
	return (y % 4 == 0 && y % 100 != 0 || y % 400 == 0);
}

uint VSDate::greg2jul(int y, int m, int d)
{
	uint c, ya;

	if (y <= 99) y += 1900;
	if (m > 2) 
	{
		m -= 3;
	} 
	else 
	{
		m += 9;
		y--;
	}
	
	c   = y;           // NOTE: Sym C++ 6.0 bug
	c  /= 100;
	ya  = y - 100*c;

	return 1721119 + d + (146097*c)/4 + (1461*ya)/4 + (153*m+2)/5;
}

void VSDate::jul2greg(uint jd, int &y, int &m, int &d)
{
	uint x;
	uint j = jd - 1721119;

	y = (j*4 - 1)/146097;
	j = j*4 - 146097*y - 1;
	x = j/4;
	j = (x*4 + 3) / 1461;
	y = 100*y + j;
	x = (x*4) + 3 - 1461*j;
	x = (x + 4)/4;
	m = (5*x - 3)/153;
	x = 5*x - 3 - 153*m;
	d = (x + 5)/5;

	if (m < 10) 
	{
		m += 3;
	} 
	else 
	{
		m -= 9;
		y++;
	}
}



//////////////////////////////////////////////////////////////////////////////
// class VSTime member methods
//////////////////////////////////////////////////////////////////////////////

VSTime::VSTime(int h, int m, int s, int ms)
{
	setHMS(h, m, s, ms);
}

bool VSTime::isValid() const
{
	return ds < MSECS_PER_DAY;
}

int VSTime::hour() const
{
	return ds / MSECS_PER_HOUR;
}

int VSTime::minute() const
{
	return (ds % MSECS_PER_HOUR)/MSECS_PER_MIN;
}

int VSTime::second() const
{
	return (ds / 1000)%SECS_PER_MIN;
}

int VSTime::msec() const
{
	return ds % 1000;
}

string VSTime::toString() const
{
	string result = "";
	char   buf1[10] = {0,};
	char   buf2[10] = {0,};
	char   buf3[10] = {0,};
	char   buf4[10] = {0,};

	sprintf(buf1, "%d", hour());
	sprintf(buf2, "%d", minute());
	sprintf(buf3, "%d", second());
	sprintf(buf4, "%d", msec());

	string hour   = string(buf1);
	string minute = string(buf2);
	string second = string(buf3);
	string msec   = string(buf4);

	if (hour.size() == 1)   hour   = "0"  + hour;
	if (minute.size() == 1) minute = "0"  + minute;
	if (second.size() == 1) second = "0"  + second;
	if (msec.size() == 1)   msec   = "00" + msec;
	if (msec.size() == 2)   msec   = "0"  + msec;

	result += hour   + ":"; // hour
	result += minute + ":"; // minute
	result += second + ":"; // second
	result += msec;         // msec

	return result;
}

string VSTime::toStringforWeb() const
{
	string result = "";
	char   buf1[10] = {0,};
	char   buf2[10] = {0,};

	sprintf(buf1, "%d", hour());
	sprintf(buf2, "%d", minute());

	string hour   = string(buf1);
	string minute = string(buf2);

	if (hour.size() == 1)   hour   = "0"  + hour;
	if (minute.size() == 1) minute = "0"  + minute;

	result += hour; // hour
	result += minute; // minute

	return result;
}

bool VSTime::setHMS(int h, int m, int s, int ms)
{
	if (!isValid(h,m,s,ms)) 
	{
		ds = MSECS_PER_DAY;// make this invalid
		return false;
	}
	ds = (h*SECS_PER_HOUR + m*SECS_PER_MIN + s)*1000 + ms;
	return true;
}

VSTime VSTime::addSecs(int nsecs) const
{
	return addMSecs(nsecs*1000);
}

int VSTime::secsTo(const VSTime &t) const
{
	return ((int)t.ds - (int)ds)/1000;
}

VSTime VSTime::addMSecs(int ms) const
{
	VSTime t;

	if (ms < 0) 
	{
		// % not well-defined for -ve, but / is.
		int negdays = (MSECS_PER_DAY-ms) / MSECS_PER_DAY;
		t.ds = ((int)ds + ms + negdays*MSECS_PER_DAY) % MSECS_PER_DAY;
	} 
	else 
	{
		t.ds = ((int)ds + ms) % MSECS_PER_DAY;
	}

	return t;
}

int VSTime::msecsTo(const VSTime &t) const
{
	return (int)t.ds - (int)ds;
}

VSTime VSTime::currentTime()
{
	VSTime ct;
	currentTime(&ct);
	return ct;
}

VSTime VSTime::fromString(string text)
{
	VSTime vst = VSTime::currentTime();

	// trim white space
    uint begin = text.find_first_not_of( whiteSpaces );
    uint end = text.find_last_not_of( whiteSpaces );
    text = text.substr( begin , end - begin + 1 );

	/////////////////////////////////////////
	// 1:1:1
	/////////////////////////////////////////
	if (text.size() < 5) return vst;

	uint a=0, b=0, c=0;

	a = text.find_first_of(':', 0  );
	b = text.find_first_of(':', a+1);
	c = text.find_first_of(':', b+1);

	if (a > b || b > text.size()) return vst;

	int hour    = atoi(text.substr(  0, a                  ).c_str());
	int minute  = atoi(text.substr(a+1, b           - a - 1).c_str());
	int second  = atoi(text.substr(b+1, c           - b - 1).c_str());
	int msecond = atoi(text.substr(c+1, text.size() - c - 1).c_str());

	vst.setHMS(hour, minute, second, msecond);

	return vst;
}

bool VSTime::currentTime(VSTime *ct)
{
	if (!ct) return false;
	struct timeval tv;
	gettimeofday(&tv, 0);
	time_t ltime = tv.tv_sec;
	tm t;
	//tm *t = localtime(&ltime);
	localtime_r( &ltime, &t );
	//ct->ds = (uint)(MSECS_PER_HOUR*t->tm_hour + MSECS_PER_MIN*t->tm_min + 1000*t->tm_sec + tv.tv_usec/1000);
	ct->ds = (uint)(MSECS_PER_HOUR*t.tm_hour + MSECS_PER_MIN*t.tm_min + 1000*t.tm_sec + tv.tv_usec/1000);
	return (t.tm_hour== 0 && t.tm_min == 0);
}

bool VSTime::isValid(int h, int m, int s, int ms)
{
	return (uint)h < 24 && (uint)m < 60 && (uint)s < 60 && (uint)ms < 1000;
}

void VSTime::start()
{
	*this = currentTime();
}

int VSTime::restart()
{
	VSTime t = currentTime();
	int n = msecsTo(t);
	if (n < 0) n += 86400*1000; // passed midnight
	*this = t;
	return n;
}

int VSTime::elapsed()
{
	int n = msecsTo(currentTime());
	if (n < 0) n += 86400*1000; // passed midnight
	return n;
}



//////////////////////////////////////////////////////////////////////////////
// class VSDateTime member methods
//////////////////////////////////////////////////////////////////////////////

VSDateTime::VSDateTime(const VSDate &date)
	: d(date)
{
}

VSDateTime::VSDateTime(const VSDate &date, const VSTime &time)
	: d(date), t(time)
{
}

VSDateTime::VSDateTime(const VSDateTime &dt)
: d(dt.d), t(dt.t)
{
}

// 0123456789012345678
// 2003-01-25 13:17:06
VSDateTime::VSDateTime(const string& DateTime)
{
	if (DateTime.size()==19)
	{
		int year  = atoi( DateTime.substr(0,4).c_str() );
		int month = atoi( DateTime.substr(5,2).c_str() );
		int day   = atoi( DateTime.substr(8,2).c_str() );
		int hour  = atoi( DateTime.substr(11,2).c_str() );
		int min   = atoi( DateTime.substr(14,2).c_str() );
		int sec   = atoi( DateTime.substr(17,2).c_str() );

		d.setYMD(year, month, day);
		t.setHMS(hour, min, sec);
	}
	else
	{
		d.setYMD(0, 0, 0);
		t.setHMS(0, 0, 0);
	}
}

string VSDateTime::toDateTime() const
{
	char str[20];
	sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d", 
					d.year(), d.month(), d.day(),
					t.hour(), t.minute(), t.second());

	return string(str);
}

void VSDateTime::setTime_t(uint secsSince1Jan1970UTC)
{
	time_t tmp = (time_t) secsSince1Jan1970UTC;
	tm *tM = localtime(&tmp);
	if (!tM) 
	{
		tM = gmtime(&tmp);
		if (!tM) 
		{
			d.jd = VSDate::greg2jul(1970, 1, 1);
			t.ds = 0;
			return;
		}
	}
	d.jd = VSDate::greg2jul(tM->tm_year + 1900, tM->tm_mon + 1, tM->tm_mday);
	t.ds = MSECS_PER_HOUR*tM->tm_hour + MSECS_PER_MIN*tM->tm_min + 1000*tM->tm_sec;
}

string VSDateTime::toString() const
{
	string rvalue  = d.toString() + "-" + t.toString();
	return rvalue;
}

string VSDateTime::toStringforWeb() const
{
	string rvalue  = d.toStringforWeb() + t.toStringforWeb();
	return rvalue;
}

VSDateTime VSDateTime::addDays(int ndays) const
{
	return VSDateTime(d.addDays(ndays), t);
}

VSDateTime VSDateTime::addSecs(int secs) const
{
	return addDays(secs/86400).addMSecs((secs%86400)*1000);
}

VSDateTime VSDateTime::addMSecs(int nsecs) const
{
	uint dd   = d.jd;
	int  tt   = t.ds;
	int  sign = 1;
	
	if (nsecs < 0) 
	{
		nsecs = -nsecs;
		sign = -1;
	}
	
	if (nsecs >= (int)MSECS_PER_DAY) 
	{
		dd += sign*(nsecs/MSECS_PER_DAY);
		nsecs %= MSECS_PER_DAY;
	}
	
	//tt += sign*nsecs*1000;
	tt += sign*nsecs;
	
	if (tt < 0) 
	{
		tt = MSECS_PER_DAY - tt - 1;
		dd -= tt / MSECS_PER_DAY;
		tt = tt % MSECS_PER_DAY;
		tt = MSECS_PER_DAY - tt - 1;
	} 
	else if (tt >= (int)MSECS_PER_DAY) 
	{
		dd += (tt / MSECS_PER_DAY);
		tt  = tt % MSECS_PER_DAY;
	}
	
	VSDateTime ret;
	ret.t.ds = tt;
	ret.d.jd = dd;

	return ret;
}

int VSDateTime::daysTo(const VSDateTime &dt) const
{
	return d.daysTo(dt.d);
}

int VSDateTime::secsTo(const VSDateTime &dt) const
{
	return t.secsTo(dt.t) + d.daysTo(dt.d)*SECS_PER_DAY;
}

int VSDateTime::msecsTo(const VSDateTime &dt) const
{
	return t.msecsTo(dt.t) + d.daysTo(dt.d)*MSECS_PER_DAY;
}

bool VSDateTime::operator==(const VSDateTime &dt) const
{
	return t == dt.t && d == dt.d;
}

bool VSDateTime::operator!=(const VSDateTime &dt) const
{
	return  t != dt.t || d != dt.d;
}

bool VSDateTime::operator<(const VSDateTime &dt) const
{
	if (d < dt.d) return true;
	return d == dt.d ? t < dt.t : false;
}

bool VSDateTime::operator<=(const VSDateTime &dt) const
{
	if (d < dt.d) return true;
	return d == dt.d ? t <= dt.t : false;
}

bool VSDateTime::operator>(const VSDateTime &dt) const
{
	if (d > dt.d)
return true;
	return d == dt.d ? t > dt.t : false;
}

bool VSDateTime::operator>=(const VSDateTime &dt) const
{
	if (d > dt.d) return true;
	return d == dt.d ? t >= dt.t : false;
}

VSDateTime VSDateTime::currentDateTime()
{
	VSDate cd = VSDate::currentDate();
	VSTime ct;

	if (VSTime::currentTime(&ct))   // too close to midnight?
		cd = VSDate::currentDate(); // YES! time for some midnight

	// voodoo, fetch date again
	return VSDateTime(cd, ct);
}

VSDateTime VSDateTime::fromString(string text)
{
	VSDateTime vsdt = VSDateTime::currentDateTime();
	uint       a    = 0;

    uint begin = text.find_first_not_of( whiteSpaces );
    uint end = text.find_last_not_of( whiteSpaces );
    text = text.substr( begin , end - begin + 1 );

	/////////////////////////////////////////
	// 2000.1.1-1:1:1:1
	/////////////////////////////////////////
	if (text.size() < 16) return vsdt;

	a = text.find_first_of('-', 0);

	if (a > text.size()) return vsdt;

	string date_text = text.substr(  0, a);
	string time_text = text.substr(a+1, text.size() - a -1);

	vsdt.d = VSDate::fromString(date_text);
	vsdt.t = VSTime::fromString(time_text);

	return vsdt;
}

////////////////////////////////////////////////////////////////////////////////
// return VSDateTime Object from YYYYMMDDHHMMSS style string
// 스트링의 형식이 지정한데 까지만 세팅한다.
// ( 단 YYYYMMDD 까지는 있어야 한다. 없으면 현재시간. 흠. 구리다.)
//  YYYYMMDD 형식의 스트링이라면 년,월,일 까지만 세팅
// 나머지 부분은 bEndOfDay 가 true 면 23시 59분 59초
// false 이면 0시 0분 0초
////////////////////////////////////////////////////////////////////////////////
VSDateTime VSDateTime::fromYYYYMMDDHHMMSS( string text, bool bEndOfDay )
{
	uint szText = text.size();

	if ( szText < 8 )
		return VSDateTime::currentDateTime();

	int year  = atoi( text.substr(0,4).c_str() );
	int month = atoi( text.substr(4,2).c_str() );
	int day   = atoi( text.substr(6,2).c_str() );
	int hour  = 23;
	int min   = 59;
	int sec   = 59;

	if ( !bEndOfDay )
	{
		hour = 0;
		min  = 0;
		sec  = 0;
	}

	if ( szText >= 10 )
		hour = atoi( text.substr(8,2).c_str() );
	
	if ( szText >= 12 )
		min = atoi( text.substr(10,2).c_str() );

	if ( szText >= 14 )
		sec = atoi( text.substr(12,2).c_str() );

	VSDate vsdate( year, month, day );
	VSTime vstime( hour, min, sec );

	VSDateTime vsdt( vsdate, vstime );

	return vsdt;
}
VSTime VSTime::fromStringHM(string text)
{
    VSTime vst = VSTime::currentTime();

    // trim white space
    uint begin = text.find_first_not_of( whiteSpaces );
    uint end = text.find_last_not_of( whiteSpaces );
    text = text.substr( begin , end - begin + 1 );

    /////////////////////////////////////////
    // 1:1
    /////////////////////////////////////////
    if (text.size() < 3) return vst;

    uint a=0;

    a = text.find_first_of(':', 0);

    if ( a == string::npos ) return vst;

    int hour    = atoi(text.substr(  0, a                  ).c_str());
    int minute  = atoi(text.substr(a+1, text.size() - a - 1).c_str());

    vst.setHMS(hour, minute, 0, 0);

    return vst;
}

