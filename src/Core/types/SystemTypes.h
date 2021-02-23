//////////////////////////////////////////////////////////////////////////////
// Filename    : SystemTypes.h
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEM_TYPES_H__
#define __SYSTEM_TYPES_H__

/* 테섭/본섭 패치를 위해 최종 빌드후 아래 BUILD_NUMBER 와 BUILD_INFO를 채워넣는다.
 * BUILD_NUMBER 년월일
 * BUILD_INFO  +Add (추가된 기능 간략 기술)
 *             -Delete (삭제된 기능 간략 기술)
 *             *Fix (버그패치/수정 간략 기술)
 * BUILD_INFO 는 간략하게 영문으로 기술
 */
#define BUILD_NUMBER 40518
#define BUILD_INFO   "<Version Information>\n
+Add ----- \n
-Delete -----\n
Fix -----\n
"


#if defined(__WINDOWS__)
	// 4786 - STL의 심볼명의 길이가 255를 넘어갈 때
	#pragma warning ( disable : 4786 )
	#include <Windows.h>
#elif defined(__LINUX__)
	#include <sys/types.h>
#endif
 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// built-in type redefinition
//////////////////////////////////////////////////////////////////////////////
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#if defined(__LINUX__) || defined(__WIN_CONSOLE__)
	typedef unsigned char  BYTE;
	typedef unsigned short WORD;
	typedef unsigned long DWORD;
	typedef unsigned long long ulonglong;
#else
	typedef unsigned __int64 ulonglong;
#endif

#if defined(__LINUX__)
	const char separatorChar = '/';
	const string separator = "/";
#elif defined(__WINDOWS__)
	const char separatorChar = '\\';
	const string separator = "\\";
#endif


//////////////////////////////////////////////////////////////////////////////
// built-in type size
//////////////////////////////////////////////////////////////////////////////
const unsigned int szbool   = sizeof(bool);
const unsigned int szchar   = sizeof(char);
const unsigned int szshort  = sizeof(short);
const unsigned int szint    = sizeof(int);
const unsigned int szlong   = sizeof(long);
const unsigned int szuchar  = sizeof(unsigned char);
const unsigned int szushort = sizeof(unsigned short);
const unsigned int szuint   = sizeof(unsigned int);
const unsigned int szulong  = sizeof(unsigned long);
const unsigned int szBYTE   = sizeof(BYTE);
const unsigned int szWORD   = sizeof(WORD);
const unsigned int szDWORD  = sizeof(DWORD);


//////////////////////////////////////////////////////////////////////////////
// ServerGroupInfo
//////////////////////////////////////////////////////////////////////////////
typedef BYTE ServerGroupID_t;
const uint szServerGroupID = sizeof(ServerGroupID_t);


//////////////////////////////////////////////////////////////////////////////
// SubServerInfo
//////////////////////////////////////////////////////////////////////////////
typedef WORD ServerID_t;
const uint szServerID = sizeof(ServerID_t);

typedef WORD UserNum_t;
const uint szUserNum = sizeof(UserNum_t);

//////////////////////////////////////////////////////////////////////////////
// SubServerInfo
//////////////////////////////////////////////////////////////////////////////
enum ServerStatus 
{
	SERVER_FREE = 0,
	SERVER_NORMAL,
	SERVER_BUSY,
	SERVER_VERY_BUSY,
	SERVER_FULL,
	SERVER_DOWN
};

enum WorldStatus
{
	WORLD_OPEN,
	WORLD_CLOSE	
};

typedef unsigned long IP_t;
const uint szIP = sizeof(IP_t);

typedef BYTE WorldID_t;
const uint szWorldID = sizeof(WorldID_t);

#endif
