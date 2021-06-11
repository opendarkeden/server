
#include "Types.h"
#include "SProfile.h"
#include <stdio.h>

SProfile::SProfile()
{
	m_Total.tv_sec = 0;
	m_Total.tv_usec = 0;
	m_Max.tv_sec = 0;
	m_Max.tv_usec = 0;
	m_Min.tv_sec = 60;
	m_Min.tv_usec = 0;
	m_IntervalTotal.tv_sec = 0;
	m_IntervalTotal.tv_usec = 0;
	m_Count = 0;
	m_IntervalCount = 0;
}

void SProfile::addTime( Timeval tv )
{
	m_Total = m_Total + tv;
	m_IntervalTotal = m_IntervalTotal + tv;

	m_Count++;
	m_IntervalCount++;

	if ( tv > m_Max )
		m_Max = tv;

	if ( tv < m_Min )
		m_Min = tv;
}

void SProfile::print()
{
	Timeval avg, totalavg;
	if ( m_Count > 0 && m_IntervalCount > 0 )
	{
		avg.tv_sec = m_IntervalTotal.tv_sec / m_IntervalCount;
		avg.tv_usec = (int)( ( (float)m_IntervalTotal.tv_sec / (float)m_IntervalCount ) * 1000000 + m_IntervalTotal.tv_usec / m_IntervalCount );

		totalavg.tv_sec = m_Total.tv_sec / m_Count;
		totalavg.tv_usec = (int)( ( (float)m_Total.tv_sec / (float)m_Count ) * 1000000 + m_Total.tv_usec / m_Count );
	}

	char msg[200];

	sprintf( msg, "avg : %d.%06d count : %d time : %d.%06d\n", (int)avg.tv_sec, (int)avg.tv_usec, m_IntervalCount, (int)m_IntervalTotal.tv_sec, (int)m_IntervalTotal.tv_usec );
	printf( msg );
	filelog( "perform.txt", msg );
	sprintf( msg, "total avg : %d.%06d max : %d.%06d min : %d.%06d total count : %d total time : %d.%06d\n", (int)totalavg.tv_sec, (int)totalavg.tv_usec, (int)m_Max.tv_sec, (int)m_Max.tv_usec, (int)m_Min.tv_sec, (int)m_Min.tv_usec, m_Count, (int)m_Total.tv_sec, (int)m_Total.tv_usec );
	printf( msg );
	filelog( "perform.txt", msg );

	m_IntervalCount = 0;
	m_IntervalTotal.tv_sec = 0;
	m_IntervalTotal.tv_usec = 0;

}

SProfile* g_pSProfile = NULL;

