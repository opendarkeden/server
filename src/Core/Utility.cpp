//////////////////////////////////////////////////////////////////////////////
// Filename    : Utility.cpp
// Written by  : 김성민
// Description : 
// 여러 곳에서 사용되는 매크로 및 간단한 함수를 정의한 파일이다.
//////////////////////////////////////////////////////////////////////////////

#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
#include "Assert.h"
#include "VSDateTime.h"

//////////////////////////////////////////////////////////////////////////////
// 사각형 클래스
//////////////////////////////////////////////////////////////////////////////
/*
VSRect::VSRect(int l, int t, int r, int b)
{
	Assert(l <= r && t <= b);

	left   = l;
	top    = t;
	right  = r;
	bottom = b;
}

bool VSRect::ptInRect(const POINT& pt) const
{
	if(left <= pt.x && pt.x <= right && top <= pt.y && pt.y <= bottom) return true;
	return false;
}

bool VSRect::ptInRect(const int x, const int y) const
{
	if(left <= x && x <= right && top <= y && y <= bottom) return true;
	return false;
}

void VSRect::set(int l, int t, int r, int b)
{
	Assert(l <= r && t <= b);

	left   = l;
	top    = t;
	right  = r;
	bottom = b;
}
*/

//////////////////////////////////////////////////////////////////////////////
// 숫자를 문자열로 바꾸기
//////////////////////////////////////////////////////////////////////////////
string itos(int value)
{
	char buf[100] = {0, };
	sprintf(buf, "%d", value);
	return string(buf);
}

//////////////////////////////////////////////////////////////////////////////
// 방향 구하기
// origin에서 dest의 방향을 타일크기에 맞게 구한다. client에서 가져왔다.
//////////////////////////////////////////////////////////////////////////////
#define BASIS_DIRECTION_HIGH    2.0f
#define BASIS_DIRECTION_LOW     0.5f
Dir_t computeDirection(int originX, int originY, int destX, int destY)
{
	int   stepX = destX - originX;
	int   stepY = destY - originY;
	float k     =(stepX == 0) ? 0 :(float)(stepY) / stepX;

	if(stepY == 0)
	{
		if(stepX == 0)     return DOWN;
		else if(stepX > 0) return RIGHT;
		else                return LEFT;
	}
	else if(stepY < 0)
	{
		if(stepX == 0)
		{
			return UP;
		}
		else if(stepX > 0)
		{
			if(k < -BASIS_DIRECTION_HIGH)     return UP;
			else if(k < -BASIS_DIRECTION_LOW) return RIGHTUP;
			else                               return RIGHT;
		}
		else
		{
			if(k > BASIS_DIRECTION_HIGH)     return UP;
			else if(k > BASIS_DIRECTION_LOW) return LEFTUP;
			else                              return LEFT;
		}
	}
	else
	{
		if(stepX == 0)
		{
			return DOWN;
		}
		else if(stepX > 0)
		{
			if(k > BASIS_DIRECTION_HIGH)     return DOWN;
			else if(k > BASIS_DIRECTION_LOW) return RIGHTDOWN;
			else                              return RIGHT;
		}
		else
		{
			if(k < -BASIS_DIRECTION_HIGH)     return DOWN;
			else if(k < -BASIS_DIRECTION_LOW) return LEFTDOWN;
			else                               return LEFT;
		}
	}

	return DIR_NONE;
}

/*
Dir_t calcDirection(int originX, int originY, int destX, int destY)
{
	return computeDirection(originX, originY, destX, destY);
}

Dir_t getDirection(int originX, int originY, int destX, int destY)
{
	return computeDirection(originX, originY, destX, destY);
}

//////////////////////////////////////////////////////////////////////////////
// 랜덤 숫자 뽑아내기
//////////////////////////////////////////////////////////////////////////////
int Random(int Min, int Max)
{
	if(Max == 0 || Min > Max) return  0;
	return ((rand() %(int)((Max) -(Min) + 1)) +(Min));
}

//////////////////////////////////////////////////////////////////////////////
// 반올림하기
//////////////////////////////////////////////////////////////////////////////
int Round(float f) { return f - 0.5 >(int)f ?(int)f + 1 :(int)f; }

//////////////////////////////////////////////////////////////////////////////
// 다이스 함수
//////////////////////////////////////////////////////////////////////////////
uint Dice(uint num , uint dice)
{
	uint result = 0;
	for(uint i = 0 ; i < num ; i ++)
	result += rand() % dice + 1;
	return result;
}
*/

//////////////////////////////////////////////////////////////////////////////
// 긴 문자열에서 한 라인 가져오기
// pos 값은 \n 의 인덱스값이 된다.
//////////////////////////////////////////////////////////////////////////////
string getline(const string & str , uint & pos)
	throw()
{
	if(pos > str.size()) return "";

	uint oldpos = pos;
	pos = str.find_first_of('\n',oldpos);

	if(pos == string::npos) pos = str.size()+1;
	else                     pos = pos+1;

	return str.substr(oldpos ,(pos - 1) - oldpos);

	/*
	uint oldpos = pos;
	// 1 을 더해주면, 
	pos = str.find_first_of('\n',oldpos) + 1;
	return str.substr(oldpos ,(pos - 1) - oldpos);
	*/
}

//////////////////////////////////////////////////////////////////////////////
// 문자열 앞 뒤의 공백 제거하기
//////////////////////////////////////////////////////////////////////////////
string trim(const string & str)
	throw()
{
	if(str.size() == 0) return "";

	static const char * WhiteSpaces = " \t\n\r";
	uint begin = str.find_first_not_of(WhiteSpaces);
	uint end = str.find_last_not_of(WhiteSpaces);

	if(begin == string::npos) begin = 0;
	if(end   == string::npos) end   = str.size();

	return str.substr(begin , end - begin + 1);
}

//////////////////////////////////////////////////////////////////////////////
// 현재 시간 얻어내기
//////////////////////////////////////////////////////////////////////////////
void getCurrentTimeEx(int& year, int& month, int& day, int& hour, int& minute, int& sec) 
	throw()
{
	time_t cur_time = time(NULL);
	tm     cur_tm;
	localtime_r( &cur_time, &cur_tm );
	//tm*    cur_tm   = localtime(&cur_time);

	year   = cur_tm.tm_year + 1900;
	month  = cur_tm.tm_mon  + 1;
	day    = cur_tm.tm_mday;
	hour   = cur_tm.tm_hour;
	minute = cur_tm.tm_min;
	sec    = cur_tm.tm_sec;
}

string getCurrentTimeStringEx(void) 
	throw()
{
	int year, month, day, hour, minute, second;

	getCurrentTimeEx(year, month, day, hour, minute, second);

	string rValue;
	rValue += itos(year)   + ". ";
	rValue += itos(month)  + ". ";
	rValue += itos(day)    + ". ";
	rValue += itos(hour)   + ". ";
	rValue += itos(minute) + ". ";
	rValue += itos(second) + ". ";
	return rValue;
}

//////////////////////////////////////////////////////////////////////////////
// 워드 상위 바이트와 하위 바이트로 분리시키기
//////////////////////////////////////////////////////////////////////////////
/*
void splitWord(WORD value, int& high, int& low) 
	throw()
{
	high = value >> 8;
	low  = value & 0xFF;
}

//////////////////////////////////////////////////////////////////////////////
// 0으로 초기화시키기
//////////////////////////////////////////////////////////////////////////////
void zerofill(void* pointer, size_t size)
	throw()
{
	memset(pointer, 0, size);
}

//////////////////////////////////////////////////////////////////////////////
// range 내에 있는지 검사하기
//////////////////////////////////////////////////////////////////////////////
bool isInRange(int value, int min, int max)
	throw()
{
	if(min <= value && value <= max) return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 주어진 숫자의 %값 알아내기
//////////////////////////////////////////////////////////////////////////////
int getPercentValue(int value, int percent)
{
	return(int)((float)value *(float)percent / 100.0);
}
*/

//////////////////////////////////////////////////////////////////////////////
// 주어진 숫자의 %값 알아내기  -  소수 첫재자리 보정
//////////////////////////////////////////////////////////////////////////////
int getPercentValueEx( int value, int percent )
{
	static int tick = 0;
	
	int thousand = getPercentValue( value, percent * 10 );
	int ret = ( thousand + tick ) / 10;

	tick++;
	if ( tick > 9 ) tick = 0;

	return ret;
}

//////////////////////////////////////////////////////////////////////////////
// 파일에다 로그하기
//////////////////////////////////////////////////////////////////////////////
void filelog(const char* szFilename, const char* fmt, ...)
    throw()
{
    __BEGIN_TRY

    va_list valist;

    va_start(valist, fmt);

    char buffer[30000];

    int nchars = vsnprintf(buffer, 30000, fmt, valist);

    if(nchars == -1 || nchars > 30000)
	{
        throw("filelog() : more buffer size needed for log");
	}

    va_end(valist);

	VSDateTime current = VSDateTime::currentDateTime();

    ofstream file(szFilename, ios::out | ios::app);
    file << current.toString() << " : " << buffer << endl;
    file.close();

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 2개의 WORD 를 DWORD 로 바꿔준다. HIWORD, LOWORD
//////////////////////////////////////////////////////////////////////////////
DWORD makeDWORD( WORD hiWord, WORD loWord )
{
	DWORD dwResult = ( (DWORD)hiWord << 16 ) | loWord;

	return dwResult;
}

//////////////////////////////////////////////////////////////////////////////
// DWORD 의 HIWORD, LOWORD 가져오기
//////////////////////////////////////////////////////////////////////////////
WORD getHIWORD( DWORD dwValue )
{
	WORD wResult = (WORD)( dwValue >> 16 );

	return wResult;
}

WORD getLOWORD( DWORD dwValue )
{
	DWORD dwMask = 0x00FF;

	WORD wResult = (WORD)( dwMask & dwValue );

	return wResult;
}

