//--------------------------------------------------------------------------------
//
// Filename    : GameTime.h
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __GAME_TIME_H__
#define __GAME_TIME_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//--------------------------------------------------------------------------------
//
// 게임 내에서의 시간을 나타낸다.
//
//--------------------------------------------------------------------------------

class GameTime {

public :

	// 소켓에 embedding 되려는 객체는 다음과 같은 메쏘드를 구현해야 한다.
	// 나중에는 이거 인터페이스로 해결할 전망이다.

	// read from socket input stream
	void read (SocketInputStream & iStream) ;

	// write to socket output stream
	void write (SocketOutputStream & oStream) const ;

	// get size of object
	uint getSize () const  { return szWORD + szBYTE* 5; }
	static uint getMaxSize ()  { return szWORD + szBYTE* 5; }


public :


	// get/set year
	WORD getYear () const  { return m_Year; }
	void setYear (WORD year)  { m_Year = year; }

	// get/set month
	BYTE getMonth () const  { return m_Month; }
	void setMonth (BYTE month)  { m_Month = month; }

	// get/set day
	BYTE getDay () const  { return m_Day; }
	void setDay (BYTE day)  { m_Day = day; }

	// get/set hour
	BYTE getHour () const  { return m_Hour; }
	void setHour (BYTE hour)  { m_Hour = hour; }

	// get/set minute
	BYTE getMinute () const  { return m_Minute; }
	void setMinute (BYTE minute)  { m_Minute = minute; }

	// get/set second
	BYTE getSecond () const  { return m_Second; }
	void setSecond (BYTE second)  { m_Second = second; }

	// get english month string
	string getMonthString () const 
	{
		switch (m_Month) {
			case 1 : return "JAN";
			case 2 : return "FEB";
			case 3 : return "MAR";
			case 4 : return "APR";
			case 5 : return "MAY";
			case 6 : return "JUN";
			case 7 : return "JUL";
			case 8 : return "OUG";
			case 9 : return "SEP";
			case 10 : return "OCT";
			case 11 : return "NOV";
			case 12 : return "DEC";
		}
		return "???";
	}

	// get debug string
	string toString () const ;

private :

	// YYYY-MM-DD
	WORD m_Year;
	BYTE m_Month;
	BYTE m_Day;

	// HH:MM:SS
	BYTE m_Hour;
	BYTE m_Minute;
	BYTE m_Second;
	
};

#endif
