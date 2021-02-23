//////////////////////////////////////////////////////////////////////
//
// FileAPI.cpp
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////

#include "FileAPI.h"
#include "Assert.h"


#if __WINDOWS__
#include <io.h>			// for _open()
#include <fcntl.h>		// for _open()/_close()/_read()/_write()...
#include <string.h>		// for memcpy()
#elif __LINUX__
#include <sys/types.h>	// for open()
#include <sys/stat.h>	// for open()
#include <unistd.h>		// for fcntl()
#include <fcntl.h>		// for fcntl()
#include <sys/ioctl.h>	// for ioctl()
#include <errno.h>		// for errno
#endif


//////////////////////////////////////////////////
// external variables
//////////////////////////////////////////////////
#if __LINUX__
extern int errno;
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int FileAPI::open_ex ( const char * filename , int flags ) 
    throw ( IOException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	int fd = open(filename,flags);
#elif __WINDOWS__
	int fd = _open(filename,flags);
#endif
	if ( fd < 0 ) {

#if __LINUX__
		switch ( errno ) {
		case EEXIST : 
			throw FileAlreadyExistException(filename);
		case ENOENT  : 
			throw FileNotExistException(filename);
		case EISDIR : 
			throw Error("pathname refers to a directory and the access requested involved writing.");
		case EACCES : 
			throw FileNotOpenedException(filename);
		case ENAMETOOLONG : 
			throw Error("pathname was too long.");
		case ENOTDIR : 
			throw Error("A component used as a directory in pathname is not, in fact, a  directory, or O_DIRECTORY was specified and pathname was not a directory.");
		case ENXIO   : 
			throw Error("O_NONBLOCK | O_WRONLY is set, the named file id a FIFO and no process has the file open for reading. Or, the file is a device special file and no corresponding device exists.");
		case ENODEV  : 
			throw Error("pathname refers to a device special file and no corresponding device exists.");
		case EROFS   : 
			throw Error("pathname refers to a file on a read-only filesystem and write access was requested.");
		case ETXTBSY : 
			throw Error("pathname refers to an executable image which is currently being executed and write access was requested.");
		case EFAULT  : 
			throw Error("pathname points outside your accessible address space.");
		case ELOOP   : 
			throw Error("Too many symbolic links were encountered in resolving pathname, or O_NOFOLLOW was specified but pathname was a symbolic link.");
		case ENOSPC  : 
			throw Error("pathname was to be created but the device containing pathname has no room for the new file.");
		case ENOMEM  : 
			throw Error("Insufficient kernel memory was available.");
		case EMFILE  : 
			throw Error("The process already has the maximum number of files open.");
		case ENFILE  : 
			throw Error("The limit on the total number of files open on the system has been reached.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
	// ...
#endif
	}

	return fd;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int FileAPI::open_ex ( const char * filename , int flags , int mode ) 
    throw ( IOException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	int fd = open(filename,flags,mode);
#elif __WINDOWS__
	int fd = _open(filename,flags,mode);
#endif

	if ( fd < 0 ) {
#if __LINUX__
		switch ( errno ) {
		case EEXIST : 
			throw FileAlreadyExistException("pathname already exists and O_CREAT and O_EXCL were used.");
		case EISDIR : 
			throw Error("pathname refers to a directory and the access requested involved writing.");
		case EACCES : 
			throw FileNotOpenedException("The requested access to the file is not allowed, or one of the directories in pathname did not allow search (execute) permission, or the file did not exist yet and write access to the parent directory is not allowed.");
		case ENAMETOOLONG : 
			throw Error("pathname was too long.");
		case ENOENT  : 
			throw Error("A directory component in pathname does not exist or is a dangling symbolic link.");
		case ENOTDIR : 
			throw Error("A component used as a directory in pathname is not, in fact, a  directory, or O_DIRECTORY was specified and pathname was not a directory.");
		case ENXIO   : 
			throw Error("O_NONBLOCK | O_WRONLY is set, the named file id a FIFO and no process has the file open for reading. Or, the file is a device special file and no corresponding device exists.");
		case ENODEV  : 
			throw Error("pathname refers to a device special file and no corresponding device exists.");
		case EROFS   : 
			throw Error("pathname refers to a file on a read-only filesystem and write access was requested.");
		case ETXTBSY : 
			throw Error("pathname refers to an executable image which is currently being executed and write access was requested.");
		case EFAULT  : 
			throw Error("pathname points outside your accessible address space.");
		case ELOOP   : 
			throw Error("Too many symbolic links were encountered in resolving pathname, or O_NOFOLLOW was specified but pathname was a symbolic link.");
		case ENOSPC  : 
			throw Error("pathname was to be created but the device containing pathname has no room for the new file.");
		case ENOMEM  : 
			throw Error("Insufficient kernel memory was available.");
		case EMFILE  : 
			throw Error("The process already has the maximum number of files open.");
		case ENFILE  : 
			throw Error("The limit on the total number of files open on the system has been reached.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
	// ...
#endif
	}

	return fd;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// uint FileAPI::read_ex ( int fd , void * buf , uint len ) 
//      throw ( IOException , Error );
//
// exception version of read()
//
// Parameters 
//     fd  - file descriptor
//     buf - reading buffer
//     len - reading length
//
// Return
//     length of reading bytes
//
// Exceptions
//     ...
//
//////////////////////////////////////////////////////////////////////
uint FileAPI::read_ex ( int fd , void * buf , uint len ) 
	throw ( IOException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	int result = read ( fd , buf , len );
#elif __WINDOWS__
	int result = _read ( fd , buf , len );
#endif

	if ( result < 0 ) {

#if __LINUX__
		switch ( errno ) {
			case EINTR : 
				throw InterruptedIOException("The call was interrupted by a signal before any data was read.");
			case EAGAIN : 
				throw NonBlockingIOException("Non-blocking I/O has been selected using O_NONBLOCK and no data was immediately available for reading.");
			case EBADF : 
				throw Error("fd is not a valid file descriptor or is not open for reading.");
			case EIO : 
				throw Error("I/O error."); 
			case EISDIR : 
				throw Error("fd refers to a directory.");
			case EINVAL : 
				throw Error("fd is attached to an object which is unsuitable for reading.");
			case EFAULT : 
				throw Error("buf is outside your accessible address space.");
			case ECONNRESET :
				throw ConnectException("Connection reset by peer.");
			default : 
				throw UnknownError(strerror(errno),errno);
		}
#elif __WINDOWS__
	// ...
#endif
	} else if ( result == 0 ) {
		throw EOFException();
	}

	return result;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// uint FileAPI::write_ex ( int fd , void * buf , uint len ) 
//      throw ( IOException );
//
// exception version of write()
//
// Parameters 
//     fd  - file descriptor
//     buf - writing buffer
//     len - writing length
//
// Return
//     length of reading bytes
//
// Exceptions
//     ...
//
//////////////////////////////////////////////////////////////////////
uint FileAPI::write_ex ( int fd , const void * buf , uint len ) 
     throw ( IOException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	int result = write ( fd , buf , len );
#elif __WINDOWS__
	int result = _write ( fd , buf , len );
#endif

	if ( result < 0 ) {
		
#if __LINUX__
		switch ( errno ) {
			case EAGAIN : 
				throw NonBlockingIOException("Non-blocking I/O has been selected using O_NONBLOCK and there was no room in the pipe or socket connected to fd to write the data immediately.");
			case EINTR : 
				throw InterruptedIOException("The call was interrupted by a signal before any data was written. ");
			case EBADF : 
				throw Error("fd is not a valid file descriptor or is not open for writing.");
			case EPIPE : 
				throw Error("fd is connected to a pipe or socket whose reading end is closed."); 
			case EINVAL: 
				throw Error("fd is attached to an object which is unsuitable for writing.");
			case EFAULT: 
				throw Error("buf is outside your accessible address space.");
			case ENOSPC : 
				throw Error("The device containing the file referred to by fd has no room for the data. ");
			case EIO : 
				throw Error("A low-level I/O error occurred while modifying the inode.");
			case ECONNRESET :
				throw ConnectException("Connection reset by peer.");
			default : 
				throw UnknownError(strerror(errno),errno);
		}
#elif __WINDOWS__
	//...
#endif
	}

	return result;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void FileAPI::close_ex ( int fd ) 
//      throw ( FileNotOpenedException , Error )
//
// exception version of close()
//
// Parameters
//     fd - file descriptor
//
// Return
//     none
//
// Exceptions
//     FileNotOpenedException - thrown when try to close file already closed
//     Error
//
//////////////////////////////////////////////////////////////////////
void FileAPI::close_ex ( int fd ) 
     throw ( FileNotOpenedException , Error )
{
	__BEGIN_TRY

	if ( close(fd) < 0 ) {
#if __LINUX__
		switch ( errno ) {
			case EBADF : 
				throw FileNotOpenedException("fd isn't a valid open file descriptor.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
#elif __WINDOWS__
#endif
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// int FileAPI::fcntl_ex ( int fd , int cmd ) 
//     throw ( Error );
//
// Parameters
//     fd  - file descriptor
//     cmd - file control command
//
// Return
//     various according to cmd
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
int FileAPI::fcntl_ex ( int fd , int cmd ) 
	throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	int result = fcntl ( fd , cmd );
	if ( result < 0 ) {
		switch ( errno ) {
			case EINTR : 
				throw Error("The F_SETLKW command was interrupted by a signal.");
			case EBADF : 
				throw Error("fd is not an open file descriptor.");
			case EACCES : 
				throw Error("Operation is prohibited by locks held by other processes.");
			case EAGAIN : 
				throw Error("Operation is prohibited because the file has been memory-mapped by another process.");
			case EDEADLK : 
				throw Error("It was detected that the specified F_SETLKW command would cause a deadlock.");
			case EMFILE  : 
				throw Error("For F_DUPFD, the process already has the maximum number of file descriptors open.");
			case ENOLCK : 
				throw Error("Too many segment locks open, lock table is full.");
			default : 
				throw UnknownError(strerror(errno),errno);
		}
	}
	return result;
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// int FileAPI::fcntl_ex ( int fd , int cmd , long arg ) 
//     throw ( Error );
//
// Parameters
//     fd  - file descriptor
//     cmd - file control command
//     arg - command argument
//
// Return
//     various according to cmd
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
int FileAPI::fcntl_ex ( int fd , int cmd , long arg ) 
	throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	int result = fcntl ( fd , cmd , arg );
	if ( result < 0 ) {
		switch ( errno ) {
			case EINTR : 
				throw Error("The F_SETLKW command was interrupted by a signal.");
			case EINVAL : 
				throw Error("For F_DUPFD, arg is negative or is greater than the maximum allowable value.");
			case EBADF : 
				throw Error("fd is not an open file descriptor.");
			case EACCES : 
				throw Error("Operation is prohibited by locks held by other processes.");
			case EAGAIN : 
				throw Error("Operation is prohibited because the file has been memory-mapped by another process.");
			case EDEADLK : 
				throw Error("It was detected that the specified F_SETLKW command would cause a deadlock.");
			case EMFILE  : 
				throw Error("For F_DUPFD, the process already has the maximum number of file descriptors open.");
			case ENOLCK : 
				throw Error("Too many segment locks open, lock table is full.");
			default : 
				throw UnknownError(strerror(errno),errno);
		}
	}
	return result;
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// bool getfilenonblocking_ex ( int fd ) 
//      throw ( Error );
//
// check if this file is nonblocking mode
//
// Parameters
//     fd - file descriptor
//
// Return
//     true if nonblocking, false if blocking
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
bool FileAPI::getfilenonblocking_ex ( int fd ) 
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	int flags = fcntl_ex( fd , F_GETFL , 0 );
	return flags | O_NONBLOCK;
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// void setfilenonblocking_ex ( int fd , bool on ) 
//      throw ( Error );
//
// make this file blocking/nonblocking
//
// Parameters
//     fd - file descriptor
//     on - true if nonblocking, false if blocking
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void FileAPI::setfilenonblocking_ex ( int fd , bool on ) 
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	int flags = fcntl_ex( fd , F_GETFL , 0 );

	if ( on )
		// make nonblocking fd
		flags |= O_NONBLOCK;
	else
		// make blocking fd
		flags &= ~O_NONBLOCK;

	fcntl_ex( fd , F_SETFL , flags );
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// void FileAPI::ioctl_ex ( int fd , int request , void * argp )
//     throw ( Error )
//
// exception version of ioctl()
//
// Parameters
//     fd      - file descriptor
//     request - i/o control request
//     argp    - argument
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void FileAPI::ioctl_ex ( int fd , int request , void * argp )
    throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	if ( ioctl(fd,request,argp) < 0 ) {
		switch ( errno ) {
		case EBADF : 
			throw Error("fd is not a valid descriptor.");
		case ENOTTY : 
			throw Error("fd is not associated with a character special device. or The specified request does not apply to the kind of object that the descriptor fd references.");
		case EINVAL : 
			throw Error("Request or argp is not valid.");
		default :
			throw UnknownError(strerror(errno),errno);
		}
	}
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////
//
// void FileAPI::setfilenonblocking_ex2 ( int fd , bool on )
//      throw ( Error )
//
// make this stream blocking/nonblocking using ioctl_ex()
//
// Parameters
//     fd - file descriptor
//     on - true if nonblocking, false else
//
// Return
//     none
//
// Exception
//     Error
//
//////////////////////////////////////////////////////////////////////
void FileAPI::setfilenonblocking_ex2 ( int fd , bool on )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	ulong arg = ( on == true ? 1 : 0 );
	ioctl_ex(fd,FIONBIO,&arg);
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// uint FileAPI::available_ex ( int fd )
//      throw ( Error )
//
// how much bytes available in this stream? using ioctl_ex()
//
// Parameters
//     fd - file descriptor
//
// Return
//     #bytes available
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
uint FileAPI::availablefile_ex ( int fd )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	// 실수로 FIONBIO 파라미터를 주는 바람에 프로그램이 개가 되었다.
	// 값을 받아오므로 0 으로 초기화시켜주면 훨씬 안전할 것 같다.
	uint arg = 0;
	ioctl_ex(fd,FIONREAD,&arg);
	return arg;
#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// int FileAPI::dup_ex ( int fd )
//     throw ( Error )
//
//////////////////////////////////////////////////////////////////////
int FileAPI::dup_ex ( int fd )
    throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	int newfd = dup(fd);
#elif __WINDOWS__
	int newfd = _dup(fd);
#endif

	if ( newfd < 0 ) {
#if __LINUX__
		switch ( errno ) {
		case EBADF : 
			throw Error("oldfd isn't an open file descriptor, or newfd is out of the allowed range for file descriptors.");
		case EMFILE : 
			throw Error("The process already has the maximum number of file descriptors open and tried to open a new one.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
#endif
	}

	return newfd;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// long FileAPI::lseek_ex ( int fd , long offset , int whence )
//      throw ( Error );
//
//////////////////////////////////////////////////////////////////////
long FileAPI::lseek_ex ( int fd , long offset , int whence )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	long result = lseek(fd,offset,whence);
	if ( result < 0 ) {
		switch ( errno ) {
		case EBADF : 
			throw Error("Fildes is not an open file descriptor.");
		case ESPIPE : 
			throw Error("Fildes is associated with a pipe, socket, or FIFO.");
		case EINVAL : 
			throw Error("Whence is not a proper value.");
		default :
			throw UnknownError(strerror(errno),errno);
		}
	}
#elif __WINDOWS__
	long result = _lseek(fd,offset,whence);
	if ( result < 0 ) {
	}
#endif

	return result;

	__END_CATCH

}
