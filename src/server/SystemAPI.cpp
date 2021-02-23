//--------------------------------------------------------------------------------
//
// Filename   : SystemAPI.cpp
// Written By : by Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Types.h"
#include "SystemAPI.h"
#include <errno.h>

#if __LINUX__
	#include <unistd.h>		// fork()
	extern int errno;
#endif

//--------------------------------------------------------------------------------
//
// exception version of fork()
//
//--------------------------------------------------------------------------------
int SystemAPI::fork_ex () 
    throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	int fd = fork();
	
	if ( fd < 0 ) {
		switch ( errno ) {
			case EAGAIN : 
				throw Error("fork  cannot  allocate  sufficient memory to copy the parent's page tables and allocate a task structure for the child.");
			case ENOMEM : 
				throw Error("fork failed to allocate the necessary kernel structures because memory is tight.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}
	
	return fd;
#elif __WINDOWS__
	throw UnsupportedError();
#endif
	__END_CATCH
}
