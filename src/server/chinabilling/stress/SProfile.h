
#ifndef __SPROFILE_H__
#define __SPROFILE_H__

#include "Timeval.h"

class SProfile
{
public:
	SProfile();
	~SProfile() {}

public:
	void addTime( Timeval tv );

	void print();

private:
	Timeval		m_Total;
	Timeval		m_Max;
	Timeval		m_Min;
	int			m_Count;
	Timeval		m_IntervalTotal;
	int			m_IntervalCount;
};

extern SProfile* g_pSProfile;

#endif

