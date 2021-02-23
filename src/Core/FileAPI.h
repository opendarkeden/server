//////////////////////////////////////////////////////////////////////
//
// FileAPI.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#ifndef __FILE_API_H__
#define __FILE_API_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// Exception based system-call(API) Collection
//
//////////////////////////////////////////////////////////////////////

namespace FileAPI {

//
// exception version of open ()
//
int open_ex (const char* filename, int flags)
    throw (IOException, Error);

int open_ex (const char* filename, int flags, int mode)
    throw (IOException, Error);

//
// exception version of close ()
//
void close_ex (int fd) 
	throw (FileNotOpenedException, Error);

//
// exception version of read ()
//
uint read_ex (int fd, void* buf, uint len) 
     throw (IOException, Error);

//
// exception version of write ()
//
uint write_ex (int fd, const void* buf, uint len) 
     throw (IOException, Error);

//
// exception version of fcntl ()
//
int fcntl_ex (int fd, int cmd) 
	throw (Error);

//
// exception version of fcntl ()
//
int fcntl_ex (int fd, int cmd, long arg) 
	throw (Error);

//
// is this stream is nonblocking?
//
// using fcntl_ex()
//
bool getfilenonblocking_ex (int fd) 
	throw (Error);

//
// make this strema blocking/nonblocking
//
// using fcntl_ex()
//
void setfilenonblocking_ex (int fd, bool on) 
	throw (Error);

//
// exception version of ioctl ()
//
void ioctl_ex (int fd, int request, void* argp)
    throw (Error);
	
//
// make this stream blocking/nonblocking
//
// using ioctl_ex()
//
void setfilenonblocking_ex2 (int fd, bool on)
     throw (Error);

//
// how much bytes available in this stream?
//
// using ioctl_ex()
//
uint availablefile_ex (int fd)
     throw (Error);

//
// exception version of dup()
//
int dup_ex (int fd)
    throw (Error);

//
// exception version of lseek()
//
long lseek_ex(int fd, long offset, int whence)
     throw (Error);

};//end of namespace FileAPI

#endif
