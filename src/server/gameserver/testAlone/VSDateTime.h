#ifndef __VSDATETIME_H__
#define __VSDATETIME_H__

#include <string>


class VSDateTime
{
public :
	VSDateTime(int t) : m_Time(t)	{}
	VSDateTime(const VSDateTime& vt) : m_Time(vt.m_Time)	{}

	void		setTime(int t)	{ m_Time = t; }
	int			getTime() const	{ return m_Time; }

	VSDateTime	addSecs(int t)	{ return VSDateTime(m_Time+t); }

	bool operator <= (const VSDateTime& t) const	{ return m_Time <= t.m_Time; }
	bool operator >= (const VSDateTime& t) const	{ return m_Time >= t.m_Time; }
	bool operator < (const VSDateTime& t) const		{ return m_Time < t.m_Time; }
	bool operator > (const VSDateTime& t) const		{ return m_Time > t.m_Time; }
	bool operator != (const VSDateTime& t) const		{ return m_Time != t.m_Time; }
	bool operator == (const VSDateTime& t) const		{ return m_Time == t.m_Time; }

	string toString() const	{ return "VSDateTime"; } 

public :
	static void			setCurrentDateTime(int t)	{ s_CurrentDateTime = VSDateTime(t); }
	static VSDateTime&	currentDateTime()			{ return s_CurrentDateTime; }

public :
	int 				m_Time;
	static VSDateTime 	s_CurrentDateTime;
};

#endif
