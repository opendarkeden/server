//--------------------------------------------------------------------------------
//
// Filename   : Assert.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __ASSERT_H__
#define __ASSERT_H__

// include files
#include "Types.h"
#include "Exception.h"

//--------------------------------------------------------------------------------
//
// Config.h 에 NDEBUG 가 정의되면, 모든 Assert를 무시한다.
// 그렇지 않은 경우 Assert가 실패하면 파일에 로그를 한후, AssertError를 리턴한다.
//
//--------------------------------------------------------------------------------
void __assert__ (const char* file, uint line, const char* func, const char* expr) throw (AssertionError);

//--------------------------------------------------------------------------------
//
// ProtocolAssert 는 클라이언트 해킹시, 잘못된 데이터가 넘어올 때, 적절한 대처를 한 후, 
// 그 연결을 종료시키는 역할을 한다.
//
//--------------------------------------------------------------------------------
void __protocol_assert__ (const char* file, uint line, const char* func, const char* expr) throw (InvalidProtocolException);

#if defined(NDEBUG)
	#define Assert(expr) ((void)0)
#elif __LINUX__
	#define Assert(expr) ((void)((expr)?0:(__assert__(__FILE__,__LINE__,__PRETTY_FUNCTION__,#expr),0)))
	#define ProtocolAssert(expr) ((void)((expr)?0:(__protocol_assert__(__FILE__,__LINE__,__PRETTY_FUNCTION__,#expr),0)))
#elif __WIN_CONSOLE__ || __WIN32__
	#define Assert(expr) ((void)((expr)?0:(__assert__(__FILE__,__LINE__,"",#expr),0)))
#elif __MFC__
	#define Assert(expr) ASSERT(expr)
#endif

#endif
