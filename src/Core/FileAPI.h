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
  int open_ex (const char* filename, int flags);

  int open_ex (const char* filename, int flags, int mode);

//
// exception version of close ()
//
  void close_ex (int fd);

//
// exception version of read ()
//
  uint read_ex (int fd, void* buf, uint len) ;

//
// exception version of write ()
//
  uint write_ex (int fd, const void* buf, uint len) ;

//
// exception version of fcntl ()
//
  int fcntl_ex (int fd, int cmd) ;

//
// exception version of fcntl ()
//
  int fcntl_ex (int fd, int cmd, long arg) ;

//
// is this stream is nonblocking?
//
// using fcntl_ex()
//
  bool getfilenonblocking_ex (int fd) ;

//
// make this strema blocking/nonblocking
//
// using fcntl_ex()
//
  void setfilenonblocking_ex (int fd, bool on) ;

//
// exception version of ioctl ()
//
  void ioctl_ex (int fd, int request, void* argp);
	
//
// make this stream blocking/nonblocking
//
// using ioctl_ex()
//
  void setfilenonblocking_ex2 (int fd, bool on);

//
// how much bytes available in this stream?
//
// using ioctl_ex()
//
  uint availablefile_ex (int fd);

//
// exception version of dup()
//
  int dup_ex (int fd);

//
// exception version of lseek()
//
  long lseek_ex(int fd, long offset, int whence);

};//end of namespace FileAPI

#endif
