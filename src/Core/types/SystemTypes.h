//////////////////////////////////////////////////////////////////////////////
// Filename    : SystemTypes.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEM_TYPES_H__
#define __SYSTEM_TYPES_H__

/* �׼�/���� ��ġ�� ���� ���� ������ �Ʒ� BUILD_NUMBER ��
 * BUILD_INFO�� ä���ִ´�. BUILD_NUMBER ����� BUILD_INFO  +Add (�߰��� ��� ���� ���) -Delete (������ ��� ���� ���) *Fix
 * (������ġ/���� ���� ���) BUILD_INFO �� �����ϰ� �������� ���
 */
#define BUILD_NUMBER 40518
#define BUILD_INFO "<Version Information>\n+Add ----- \n-Delete -----\nFix -----\n"


#if defined(__WINDOWS__)
// 4786 - STL�� �ɺ����� ���̰� 255�� �Ѿ ��
#pragma warning(disable : 4786)
#include <Windows.h>
#elif defined(__LINUX__) || defined(__APPLE__)
#include <sys/types.h>
#endif

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// built-in type redefinition
//////////////////////////////////////////////////////////////////////////////
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#if defined(__LINUX__) || defined(__APPLE__) || defined(__WIN_CONSOLE__)
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long long ulonglong;
#else
typedef unsigned __int64 ulonglong;
#endif

#if defined(__LINUX__) || defined(__APPLE__)
const char separatorChar = '/';
const string separator = "/";
#elif defined(__WINDOWS__)
const char separatorChar = '\\';
const string separator = "\\";
#endif


//////////////////////////////////////////////////////////////////////////////
// built-in type size
//////////////////////////////////////////////////////////////////////////////
const unsigned int szbool = sizeof(bool);
const unsigned int szchar = sizeof(char);
const unsigned int szshort = sizeof(short);
const unsigned int szint = sizeof(int);
const unsigned int szlong = sizeof(long);
const unsigned int szuchar = sizeof(unsigned char);
const unsigned int szushort = sizeof(unsigned short);
const unsigned int szuint = sizeof(unsigned int);
const unsigned int szulong = sizeof(unsigned long);
const unsigned int szBYTE = sizeof(BYTE);
const unsigned int szWORD = sizeof(WORD);
const unsigned int szDWORD = sizeof(DWORD);


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
enum ServerStatus { SERVER_FREE = 0, SERVER_NORMAL, SERVER_BUSY, SERVER_VERY_BUSY, SERVER_FULL, SERVER_DOWN };

enum WorldStatus { WORLD_OPEN, WORLD_CLOSE };

typedef unsigned int IP_t;
const uint szIP = sizeof(IP_t);

typedef BYTE WorldID_t;
const uint szWorldID = sizeof(WorldID_t);

#endif
