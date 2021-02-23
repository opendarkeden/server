//////////////////////////////////////////////////////////////////////////////
// Filename    : VSDateTime.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __VSDATETIME_H__
#define __VSDATETIME_H__

#include <sys/types.h>
#include <string>

using namespace std;

#ifndef uint
	typedef unsigned int   uint;
#endif

//////////////////////////////////////////////////////////////////////////////
// class VSDate
//////////////////////////////////////////////////////////////////////////////

class VSDate
{

///// Friend class definition /////
private:
    friend class VSDateTime;

///// Member methods
public: 
    VSDate(){ jd=0; } 
    VSDate(int y, int m, int d); 
	
public:
    bool   isNull() const { return jd == 0; }
    bool   isValid() const;

    int    year() const;        // 1752..
    int    month() const;       // 1..12
    int    day() const;         // 1..31

    int    dayOfWeek() const;   // 1..7 (monday==1)
    int    dayOfYear() const;   // 1..365
    int    daysInMonth() const; // 28..31
    int    daysInYear() const;  // 365 or 366

    string toString() const;
    string toStringforWeb() const;

    bool   setYMD(int y, int m, int d);

    VSDate addDays(int days) const;
    int    daysTo(const VSDate &) const;

public:
    bool operator == (const VSDate &d) const { return jd == d.jd; }
    bool operator != (const VSDate &d) const { return jd != d.jd; }
    bool operator <  (const VSDate &d) const { return jd <  d.jd; }
    bool operator <= (const VSDate &d) const { return jd <= d.jd; }
    bool operator >  (const VSDate &d) const { return jd >  d.jd; }
    bool operator >= (const VSDate &d) const { return jd >= d.jd; }

public:
    static VSDate currentDate();
	static VSDate fromString(string text);
    static bool   isValid(int y, int m, int d);
    static bool   leapYear(int year);

protected:
    static uint greg2jul(int y, int m, int d);
    static void jul2greg(uint jd, int &y, int &m, int &d);


///// Member data /////
private:
    uint jd;

};


//////////////////////////////////////////////////////////////////////////////
// class VSTime
//////////////////////////////////////////////////////////////////////////////

class VSTime
{

//// Friend class definition /////
private:
    friend class VSDateTime;

///// Member methods /////
public:
    VSTime() { ds=0; }
    VSTime(int h, int m, int s=0, int ms=0);

public:
    bool   isNull() const { return ds == 0; }
    bool   isValid() const;

    int    hour() const;    // 0..23
    int    minute() const;  // 0..59
    int    second() const;  // 0..59
    int    msec() const;    // 0..999

    string toString() const;
    string toStringforWeb() const;

    bool   setHMS(int h, int m, int s, int ms=0);

    VSTime addSecs(int secs) const;
    int    secsTo(const VSTime &) const;
    VSTime addMSecs(int ms) const;
    int    msecsTo(const VSTime &) const;

public:
    bool operator == (const VSTime &d) const { return ds == d.ds; }
    bool operator != (const VSTime &d) const { return ds != d.ds; }
    bool operator <  (const VSTime &d) const { return ds <  d.ds; }
    bool operator <= (const VSTime &d) const { return ds <= d.ds; }
    bool operator >  (const VSTime &d) const { return ds >  d.ds; }
    bool operator >= (const VSTime &d) const { return ds >= d.ds; }

public:
	//////////////////////////////////////////////////
	// start()로써 시작점을 저장해 두고,
	// elapsed로 몇 milli-second가 지났는지
	// 알아내면 딜레이 조사하는 부분 같은 곳에 
	// 쓸 수 있다.
	//////////////////////////////////////////////////
    void start();
    int  restart();
    int  elapsed();

public:
    static VSTime currentTime();
	static VSTime fromString(string text);
	static VSTime fromStringHM(string text);
    static bool isValid(int h, int m, int s, int ms=0);

private:
    static bool currentTime(VSTime *);


///// Member data /////
private:
    uint ds;
};


//////////////////////////////////////////////////////////////////////////////
// class VSDateTime
//////////////////////////////////////////////////////////////////////////////

class VSDateTime
{

///// Member methods /////
public:
    VSDateTime() {}
    VSDateTime(const VSDate &);
    VSDateTime(const VSDate &, const VSTime &);
    VSDateTime(const VSDateTime &);
    VSDateTime(const string& DateTime);

    bool       isNull() const { return d.isNull() && t.isNull(); }
    bool       isValid() const { return d.isValid() && t.isValid(); }

    const VSDate&    date() const { return d; }
    const VSTime&    time() const { return t; }

    void       setDate(const VSDate &date) { d=date; }
    void       setTime(const VSTime &time) { t=time; }

    void       setTime_t(uint secsSince1Jan1970UTC);

    string     toString() const;
    string     toStringforWeb() const;
    string     toDateTime() const;

    VSDateTime addDays(int days) const;
    VSDateTime addSecs(int secs) const;
    VSDateTime addMSecs(int secs) const;
    int        daysTo(const VSDateTime &) const;
    int        secsTo(const VSDateTime &) const;
    int        msecsTo(const VSDateTime &) const;

public:
    bool operator == (const VSDateTime &dt) const;
    bool operator != (const VSDateTime &dt) const;
    bool operator <  (const VSDateTime &dt) const;
    bool operator <= (const VSDateTime &dt) const;
    bool operator >  (const VSDateTime &dt) const;
    bool operator >= (const VSDateTime &dt) const;

public:
    static VSDateTime currentDateTime();
	static VSDateTime fromString(string text);
	static VSDateTime fromYYYYMMDDHHMMSS( string text, bool bEndOfDay = true );


///// Member data /////
private:
    VSDate d;
    VSTime t;
};

#endif // #ifndef __VSDATETIME_H__





