//--------------------------------------------------------------------------------
// 
// Filename   : Assert.cpp 
// Written By : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Types.h"
#include "Assert.h"
#include "Exception.h"
#include <time.h>

//--------------------------------------------------------------------------------
//
// __assert__
//
// 이 함수에서는 __BEGIN_TRY , __END_CATCH로 wrapping할 필요가 없다.
//
//--------------------------------------------------------------------------------
void __assert__ ( const char * file , uint line , const char * func , const char * expr )
	throw ( AssertionError )
{
	StringStream msg;
	
	msg << "\n"
		<< "Assertion Failed : " << file << " : " << line;

	if ( func )
		msg << " : " << func;

	time_t currentTime = time(0);
	
	msg << expr << " at " << ctime(&currentTime);
	
	ofstream ofile("assertion_failed.log",ios::app);
	ofile << msg.toString() << endl;
	ofile.close();

	throw AssertionError( msg.toString() );
}

//--------------------------------------------------------------------------------
//
// 내부에 특정 유저를 BAN 하고, 로그를 남기는 코드가 들어갈 수 있을까?
//
//--------------------------------------------------------------------------------
void __protocol_assert__ ( const char * file , uint line , const char * func , const char * expr )
	throw ( InvalidProtocolException )
{
	StringStream msg;
	
	msg << "\n"
		<< "Protocol Assertion Failed : " << file << " : " << line;

	if ( func )
		msg << " : " << func;

	time_t currentTime = time(0);
	
	msg << expr << " at " << ctime(&currentTime);
	
	ofstream ofile("protocol_assertion_failed.log",ios::app);
	ofile << msg.toString() << endl;
	ofile.close();

	throw InvalidProtocolException( msg.toString() );
}
