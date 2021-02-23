//--------------------------------------------------------------------------------
//
// Filename    : Timeval.h
// Written By  : Reiot
// Description : struct timeval 에 관련된 operator 들을 모아놓은 파일
//
//--------------------------------------------------------------------------------

#ifndef __TIMEVAL_H__
#define __TIMEVAL_H__

// include files
#include <sys/time.h>
#include <unistd.h>

// type redefinition
typedef struct timeval Timeval;

extern Timeval gCurrentTime;

#ifdef __GAME_SERVER__
	#define getCurrentTime(t) t = gCurrentTime
	#define setCurrentTime() gettimeofday(&gCurrentTime,NULL)
#else
	#define getCurrentTime(t) gettimeofday((&t),NULL)
#endif

bool operator > ( const Timeval & left , const Timeval & right );
bool operator >= ( const Timeval & left , const Timeval & right );
bool operator == ( const Timeval & left , const Timeval & right );
bool operator <= ( const Timeval & left , const Timeval & right );
bool operator < ( const Timeval & left , const Timeval & right );

// timediff의 결과값끼리 더할 경우에 사용한다.
// (사실 현재 시간끼리 더한다는 것은 우스운 짓이다. - -; )
Timeval operator + ( const Timeval & left , const Timeval & right );

//
// 두 Timeval 간의 시간차를 구한다. 
//
Timeval timediff ( const Timeval & left , const Timeval & right );

void getCurrentYearTime ( unsigned long int & currentYearTime );

#endif
