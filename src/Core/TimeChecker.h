////////////////////////////////////////////////////////////////////
// Filename		: TimeChecker.h
// Written by	: Bezz
// Description	:
////////////////////////////////////////////////////////////////////

#ifndef __TIME_CHECKER_H__
#define __TIME_CHECKER_H__

#include "VSDateTime.h"
#include "../server/Timeval.h"

enum TIME_PERIOD
{
	TIME_PERIOD_CHILD_GUARD = 0,
	TIME_PERIOD_AFTER_SCHOOL,
	TIME_PERIOD_AFTER_WORK,
	TIME_PERIOD_MIDNIGHT,

	TIME_PERIOD_MAX
};

////////////////////////////////////////////////////////////////////
// class TimePeriod
////////////////////////////////////////////////////////////////////
class TimePeriod
{
public:
	// constructor/destructor
	TimePeriod( VSTime fromTime, VSTime toTime );
	~TimePeriod();

public:
	// is in period
	bool isInPeriod() { return m_bInPeriod; }

	// heartbeat
	void heartbeat( VSTime currentTime = VSTime::currentTime() );

private:
	VSTime		m_FromTime;
	VSTime		m_ToTime;
	bool		m_bInPeriod;
	bool		m_bDay;					// is day period? or midnight period?
};


////////////////////////////////////////////////////////////////////
// class TimeChecker
////////////////////////////////////////////////////////////////////
class TimeChecker
{
public:
	// constructor/destructor
	TimeChecker();
	~TimeChecker();

public:
	// initialize
	void init();

	// heartbeat
	void heartbeat();

	// is in period
	bool isInPeriod( int type );

private:
	TimePeriod*		m_pTimePeriods[TIME_PERIOD_MAX];
	Timeval			m_NextTime;
};


extern TimeChecker* g_pTimeChecker;

#endif

