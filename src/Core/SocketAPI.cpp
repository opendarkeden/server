//////////////////////////////////////////////////////////////////////
//
// SocketAPI.cpp
//
// by Reiot, the Fallen Lord of MUDMANIA(TM)
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////

#include "SocketAPI.h"

#if __WINDOWS__
#elif __LINUX__
#include <sys/types.h>			// for accept()
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>			// for inet_xxx()
#include <netinet/in.h>
#include <errno.h>				// for errno
#endif

#include "FileAPI.h"


//////////////////////////////////////////////////
// external variable
//////////////////////////////////////////////////
#if __LINUX__
extern int errno;
#endif

using namespace FileAPI;

//////////////////////////////////////////////////////////////////////
//
// SOCKET SocketAPI::socket_ex ( int domain , int type , int protocol ) 
//		throw ( Error )
//
// exception version of socket()
//
// Parameters
//     domain - AF_INET(internet socket), AF_UNIX(internal socket), ...
//	   type  - SOCK_STREAM(TCP), SOCK_DGRAM(UDP), ...
//     protocol - 0
//
// Return 
//     socket descriptor
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
SOCKET SocketAPI::socket_ex ( int domain , int type , int protocol ) 
	throw ( Error )
{
	__BEGIN_TRY

	SOCKET s = ::socket(domain,type,protocol);

	if ( s == INVALID_SOCKET ) {
#if __LINUX__
		switch ( errno ) {
		case EPROTONOSUPPORT :
			throw Error("The protocol type or the specified protocol is not supported within this domain.");
		case EMFILE : 
			throw Error("The per-process descriptor table is full.");
		case ENFILE : 
			throw Error("The system file table is full.");
		case EACCES : 
			throw Error("Permission to create a socket of the specified type and/or protocol is denied.");
		case ENOBUFS : 
			throw Error("Insufficient buffer space is available. The socket cannot be created until sufficient resources are freed.");
		default : 
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem or the associated service provider has failed.");
		case WSAEAFNOSUPPORT : 
			throw Error("The specified address family is not supported.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEMFILE : 
			throw Error("No more socket descriptors are available.");
		case WSAENOBUFS : 
			throw Error("No buffer space is available. The socket cannot be created.");
		case WSAEPROTONOSUPPORT : 
			throw Error("The specified protocol is not supported.");
		case WSAEPROTOTYPE : 
			throw Error("The specified protocol is the wrong type for this socket.");
		case WSAESOCKTNOSUPPORT : 
			throw Error("The specified socket type is not supported in this address family.");
		default : 
			throw UnknownError("socket()");
		}//end of switch
#endif
	}

	return s;
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::bind_ex ( SOCKET s , const struct sockaddr * addr , uint addrlen ) 
//      throw ( MBindException , 
//              Error );
//
// exception version of bind()
//
// Parameters
//     s       - socket descriptor 
//     addr    - socket address structure ( normally struct sockaddr_in )
//     addrlen - length of socket address structure
//
// Return
//     none
//
// Exceptions
//     MBindException
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::bind_ex ( SOCKET s , const struct sockaddr * addr , uint addrlen ) 
     throw ( BindException , 
             Error )
{
	__BEGIN_TRY

	if ( bind ( s , addr , addrlen ) == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {
		case EADDRINUSE :
			throw BindException("The address is already in use. kill another server or use another port. 소켓의 주소 혹은 포트가 이미 사용중입니다. 기존의 서버 소켓을 종료하거나, 다른 포트를 사용하시기 바랍니다.");
		case EINVAL : 
			throw BindException("The socket is already bound to an address , or the addr_len was wrong, or the socket was not in the AF_UNIX family.");
		case EACCES : 
			throw BindException("The address is protected, and the user is not the super-user. or search permission is denied on a component of the path prefix.");
		case ENOTSOCK : 
			throw Error("Argument is a descriptor for a file, not a socket. The following errors are specific to UNIX domain (AF_UNIX) sockets:");
		case EBADF : 
			throw Error("sockfd is not a valid descriptor.");
		case EROFS : 
			throw Error("The socket inode would reside on a read-only file system.");
		case EFAULT : 
			throw Error("my_addr points outside your accessible address space.");
		case ENAMETOOLONG : 
			throw Error("my_addr is too long.");
		case ENOENT : 
			throw Error("The file does not exist.");
		case ENOMEM : 
			throw Error("Insufficient kernel memory was available.");
		case ENOTDIR : 
			throw Error("A component of the path prefix is not a directory.");
		case ELOOP : 
			throw Error("Too many symbolic links were encountered in resolving my_addr.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEADDRINUSE : 
			throw BindException("A process on the machine is already bound to the same fully-qualified address and the socket has not been marked to allow address re-use with SO_REUSEADDR. For example, IP address and port are bound in the af_inet case) . (See the SO_REUSEADDR socket option under setsockopt.)");
		case WSAEADDRNOTAVAIL : 
			throw BindException("The specified address is not a valid address for this machine.");
		case WSAEFAULT : 
			throw BindException("The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains incorrect address format for the associated address family, or the first two bytes of the memory block specified by name does not match the address family associated with the socket descriptor s.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEINVAL : 
			throw BindException("The socket is already bound to an address.");
		case WSAENOBUFS : 
			throw Error("Not enough buffers available, too many connections.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		default :
			throw UnknownError("bind()");
		}//end of switch
#endif
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::connect_ex ( SOCKET s , const struct sockaddr * addr , uint addrlen )
//      throw ( ConnectException , 
//              NonBlockingIOException , 
//              Error );
//
// exception version of connect() system call
//
// Parameters
//     s       - socket descriptor
//     addr    - socket address structure
//     addrlen - length of socket address structure
//
// Return
//     none
//
// Exceptions
//     ConnectException
//     NonBlockingIOException
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::connect_ex ( SOCKET s , const struct sockaddr * addr , uint addrlen )
     throw ( ConnectException , 
             NonBlockingIOException , 
             Error )
{
	__BEGIN_TRY

	if ( connect(s,addr,addrlen) == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {
		case EALREADY : 
			throw NonBlockingIOException("The socket is non-blocking and a previous connection attempt has not yet been completed.");
		case EINPROGRESS : 
			throw ConnectException("The socket is non-blocking and the connection can not be completed immediately.");
		case ECONNREFUSED : 
			throw ConnectException("Connection refused at server.");
		case EISCONN : 
			throw ConnectException("The socket is already connected.");
		case ETIMEDOUT : 
			throw ConnectException("Timeout while attempting connection.");
		case ENETUNREACH : 
			throw ConnectException("Network is unreachable.");
		case EADDRINUSE : 
			throw ConnectException("Address is already in use.");
		case EBADF : 
			throw Error("Bad descriptor.");
		case EFAULT : 
			throw Error("The socket structure address is outside your address space.");
		case ENOTSOCK : 
			throw Error("The descriptor is not associated with a socket.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEADDRINUSE : 
			throw Error("The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs when executing bind, but could be delayed until this function if the bind was to a partially wild-card address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function.");
		case WSAEINTR : 
			throw Error("The (blocking) Windows Socket 1.1 call was canceled through WSACancelBlockingCall.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEALREADY : 
			throw Error("A nonblocking connect call is in progress on the specified socket. Note In order to preserve backward compatibility, this error is reported as WSAEINVAL to Windows Sockets 1.1 applications that link to either WINSOCK.DLL or WSOCK32.DLL."); 
		case WSAEADDRNOTAVAIL : 
			throw ConnectException("The remote address is not a valid address (such as ADDR_ANY).");
		case WSAEAFNOSUPPORT : 
			throw Error("Addresses in the specified family cannot be used with this socket.");
		case WSAECONNREFUSED : 
			throw ConnectException("The attempt to connect was forcefully rejected.");
		case WSAEFAULT : 
			throw Error("The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, or the name parameter contains incorrect address format for the associated address family.");
		case WSAEINVAL : 
			throw Error("The parameter s is a listening socket, or the destination address specified is not consistent with that of the constrained group the socket belongs to.");
		case WSAEISCONN : 
			throw ConnectException("The socket is already connected (connection-oriented sockets only).");
		case WSAENETUNREACH : 
			throw ConnectException("The network cannot be reached from this host at this time.");
		case WSAENOBUFS : 
			throw Error("No buffer space is available. The socket cannot be connected.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		case WSAETIMEDOUT : 
			throw ConnectException("Attempt to connect timed out without establishing a connection.");
		case WSAEWOULDBLOCK  : 
			throw NonBlockingIOException("The socket is marked as nonblocking and the connection cannot be completed immediately.");
		default :
			throw UnknownError("connect()");
		}//end of switch
#endif
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::listen_ex ( SOCKET s , uint backlog )
//      throw ( Error );
//
// exception version of listen()
//
// Parameters
//     s       - socket descriptor
//     backlog - waiting queue length
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::listen_ex ( SOCKET s , uint backlog ) 
     throw ( Error )
{
	__BEGIN_TRY

	if ( listen( s , backlog ) == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {
		case EBADF : 
			throw Error("Bad descriptor.");
		case ENOTSOCK :
			throw Error("Not a socket.");
		case EOPNOTSUPP :
			throw Error("The socket is not of a type that supports the operation listen.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEADDRINUSE : 
			throw Error("The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind function, but could be delayed until this function if the bind was to a partially wild-card address (involving ADDR_ANY) and if a specific address needs to be 'committed' at the time of this function.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEINVAL : 
			throw Error("The socket has not been bound with bind.");
		case WSAEISCONN : 
			throw Error("The socket is already connected.");
		case WSAEMFILE : 
			throw Error("No more socket descriptors are available.");
		case WSAENOBUFS : 
			throw Error("No buffer space is available.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		case WSAEOPNOTSUPP : 
			throw Error("The referenced socket is not of a type that supports the listen operation.");
		default :
			throw UnknownError("listen()");
		}//end of switch
#endif
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
//SOCKET SocketAPI::accept_ex ( SOCKET s , struct sockaddr * addr , uint * addrlen ) 
//       throw ( NonBlockingIOException , 
//               ConnectException ,
//               Error );
//
// exception version of accept()
//
// Parameters
//     s       - socket descriptor
//     addr    - socket address structure
//     addrlen - length of socket address structure
//
// Return
//     none
//
// Exceptions
//     NonBlockingIOException
//     Error
//
//////////////////////////////////////////////////////////////////////
SOCKET SocketAPI::accept_ex ( SOCKET s , struct sockaddr * addr , uint * addrlen )
       throw ( NonBlockingIOException , ConnectException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	SOCKET client = accept( s , addr , addrlen );
#elif __WINDOWS__
	SOCKET client = accept( s , addr , (int*)addrlen );
#endif
	
	if ( client == INVALID_SOCKET ) {
#if __LINUX__
		switch ( errno ) {

		case EWOULDBLOCK : 
			throw NonBlockingIOException();

		case ECONNRESET :
		case ECONNABORTED :
		case EPROTO :
		case EINTR :
			// from UNIX Network Programming 2nd, 15.6
			// with nonblocking-socket, ignore above errors
			throw ConnectException(strerror(errno));

		case EBADF : 
		case ENOTSOCK : 
		case EOPNOTSUPP : 
		case EFAULT : 
			throw Error(strerror(errno));

		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this FUNCTION.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEFAULT : 
			throw Error("The addrlen parameter is too small or addr is not a valid part of the user address space.");
		case WSAEINTR : 
			throw Error("A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEINVAL : 
			throw Error("The listen function was not invoked prior to accept.");
		case WSAEMFILE : 
			throw Error("The queue is nonempty upon entry to accept and there are no descriptors available.");
		case WSAENOBUFS : 
			throw Error("No buffer space is available.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		case WSAEOPNOTSUPP : 
			throw Error("The referenced socket is not a type that supports connection-oriented service.");
		case WSAEWOULDBLOCK : 
			throw NonBlockingIOException();
		default :
			throw UnknownError("accept()");
		}//end of switch
#endif
	} else {
/*
		struct timeval tm;
		struct timeval tm2;

//		int time = getsockopt( client, SOL_SOCKET, SO_SNDTIMEO, &tm, &socklen );
//		int time2 = getsockopt( client, SOL_SOCKET, SO_RCVTIMEO, &tm2, &socklen2 );

//		cout << "Socket Option Time Out Sec Value : " << tm.tv_sec << endl;
//		cout << "Socket Option Time Out Usec Value : " << tm.tv_usec << endl;
		// Send Time out
//		tm.tv_sec = 0;
//		tm.tv_usec = 20;
//		socklen_t socklen = sizeof( tm );

		// Recv Time out
		tm2.tv_sec = 0;
		tm2.tv_usec = 10000;
		socklen_t socklen2 = sizeof( tm2 );

		socklen2 = sizeof( tm2 );
//		setsockopt( client, SOL_SOCKET, SO_SNDTIMEO, &tm, socklen );
		setsockopt( client, SOL_SOCKET, SO_RCVTIMEO, &tm2, socklen2 );
*/
	}

	return client;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::getsockopt_ex ( SOCKET s , int level , int optname , void * optval , uint * optlen )
//      throw ( Error );
//
// exception version of getsockopt()
//
// Parameters
//     s       - socket descriptor
//     level   - socket option level ( SOL_SOCKET , ... )
//     optname - socket option name ( SO_REUSEADDR , SO_LINGER , ... )
//     optval  - pointer to contain option value
//     optlen  - length of optval
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::getsockopt_ex ( SOCKET s , int level , int optname , void * optval , uint * optlen )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) {
		switch ( errno ) {
		case EBADF : 
			throw Error("Bad descriptor.");
		case ENOTSOCK : 
			throw Error("Not a socket.");
		case ENOPROTOOPT : 
			throw Error("The option is unknown at the level indicated.");
		case EFAULT : 
			throw Error("The address pointed to by optval is not in a valid part of the process address space. For getsockopt, this error may also be returned if optlen is not in a valid part of the process address space.");
		default :
			throw UnknownError(strerror(errno),errno);
		}//end of switch
	}
#elif __WINDOWS__
	if ( getsockopt( s , level , optname , (char*)optval , (int*)optlen ) == SOCKET_ERROR ) {
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEFAULT : 
			throw Error("One of the optval or the optlen parameters is not a valid part of the user address space, or the optlen parameter is too small.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEINVAL : 
			throw Error("The level parameter is unknown or invalid.");
		case WSAENOPROTOOPT : 
			throw Error("The option is unknown or unsupported by the indicated protocol family.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		default : 
			throw UnknownError("getsockopt()");
		}//end of switch
	}
#endif
	
	__END_CATCH
}

uint SocketAPI::getsockopt_ex2 ( SOCKET s , int level , int optname , void * optval , uint * optlen )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) {
		switch ( errno ) {
		case EBADF : 
			return 1;
		case ENOTSOCK : 
			return 2;
		case ENOPROTOOPT : 
			return 3;
		case EFAULT : 
			return 4;
		default :
			return 5;
		}//end of switch
	}
	return 0;
#endif

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::setsockopt_ex ( SOCKET s , int level , int optname , const void * optval , uint optlen )
//      throw ( Error );
//
// exception version of setsockopt()
//
// Parameters
//     s       - socket descriptor
//     level   - socket option level ( SOL_SOCKET , ... )
//     optname - socket option name ( SO_REUSEADDR , SO_LINGER , ... )
//     optval  - pointer to contain option value
//     optlen  - length of optval
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::setsockopt_ex ( SOCKET s , int level , int optname , const void * optval , uint optlen )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	if ( setsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) {
		switch ( errno ) {
			case EBADF : 
				throw Error("Bad descriptor.");
			case ENOTSOCK : 
				throw Error("Not a socket.");
			case ENOPROTOOPT : 
				throw Error("The option is unknown at the level indicated.");
			case EFAULT : 
				throw Error("The address pointed to by optval is not in a valid part of the process address space. For getsockopt, this error may also be returned if optlen is not in a valid part of the process address space.");
			default :
				throw UnknownError(strerror(errno),errno);
		}//end of switch
	}
#elif __WINDOWS__
	if ( setsockopt( s , level , optname , (char*)optval , optlen ) == SOCKET_ERROR ) {
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEFAULT : 
			throw Error("optval is not in a valid part of the process address space or optlen parameter is too small.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEINVAL : 
			throw Error("level is not valid, or the information in optval is not valid.");
		case WSAENETRESET : 
			throw Error("Connection has timed out when SO_KEEPALIVE is set.");
		case WSAENOPROTOOPT : 
			throw Error("The option is unknown or unsupported for the specified provider or socket (see SO_GROUP_PRIORITY limitations).");
		case WSAENOTCONN : 
			throw Error("Connection has been reset when SO_KEEPALIVE is set.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		default :
			throw UnknownError("setsockopt()");
		}//end of switch
	}
#endif
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// uint SocketAPI::send_ex ( SOCKET s , const void * buf , uint len , uint flags )
//      throw ( NonBlockingIOException , ConnectException , Error )
// 
// exception version of send()
// 
// Parameters 
//     s     - socket descriptor
//     buf   - input buffer
//     len   - input data length
//     flags - send flag (MSG_OOB,MSG_DONTROUTE)
// 
// Return 
//     length of bytes sent
// 
// Exceptions 
//     NonBlockingIOException
//     ConnectException
//     Error 
// 
//////////////////////////////////////////////////////////////////////
uint SocketAPI::send_ex ( SOCKET s , const void * buf , uint len , uint flags )
     throw ( NonBlockingIOException ,
             ConnectException ,
             Error,
			 ProtocolException )
{
	__BEGIN_TRY

	int nSent;

	try {

#if __LINUX__
	nSent = send(s,buf,len,flags);
#elif __WINDOWS__
	nSent = send(s,(const char *)buf,len,flags);
#endif

	if ( nSent == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {

		case EWOULDBLOCK : 
			//throw NonBlockingIOException();
			// by sigi. 2002.5.17
			return 0;

		case ECONNRESET :
		case EPIPE :
			throw ConnectException(strerror(errno));

		case EBADF : 
		case ENOTSOCK : 
		case EFAULT : 
		case EMSGSIZE : 
		case ENOBUFS : 
			throw Error(strerror(errno));

		default : 
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEACCES : 
			throw Error("The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST parameter to allow the use of the broadcast address.");
		case WSAEINTR : 
			throw Error("A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEFAULT : 
			throw Error("The buf parameter is not completely contained in a valid part of the user address space.");
		case WSAENETRESET : 
			throw ConnectException("The connection has been broken due to the 'keep-alive' activity detecting a failure while the operation was in progress.");
		case WSAENOBUFS : 
			throw Error("No buffer space is available.");
		case WSAENOTCONN : 
			throw Error("The socket is not connected.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		case WSAEOPNOTSUPP : 
			throw Error("MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, out-of-band data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations.");
		case WSAESHUTDOWN : 
			throw ConnectException("The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.");
		case WSAEWOULDBLOCK : 
			throw NonBlockingIOException("The socket is marked as nonblocking and the requested operation would block.");
		case WSAEMSGSIZE : 
			throw Error("The socket is message oriented, and the message is larger than the maximum supported by the underlying transport.");
		case WSAEHOSTUNREACH : 
			throw ConnectException("The remote host cannot be reached from this host at this time.");
		case WSAEINVAL : 
			throw Error("The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled.");
		case WSAECONNABORTED : 
			throw ConnectException("The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.");
		case WSAECONNRESET : 
			throw ConnectException("The virtual circuit was reset by the remote side executing a 'hard' or 'abortive' close. For UPD sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a 'Port Unreachable' ICMP packet. The application should close the socket as it is no longer usable.");
		case WSAETIMEDOUT : 
			throw ConnectException("The connection has been dropped, because of a network failure or because the system on the other end went down without notice.");
		default :
			throw UnknownError("send()");
		}//end of switch
#endif
	} 
	else if ( nSent == 0 )
	{
		throw ConnectException("connect closed.");
	}

	} catch ( Throwable & t ) {
		cout << "SocketAPI::send_ex Exception Check!" << endl;
		cout << t.toString() << endl;
		throw InvalidProtocolException("씨바 누가 끊기노");
	}

	return nSent;
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// exception version of sendto()
//////////////////////////////////////////////////////////////////////
uint SocketAPI::sendto_ex ( SOCKET s , const void * buf , int len , unsigned int flags , const struct sockaddr * to , int tolen )
    throw ( NonBlockingIOException , ConnectException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	int nSent = sendto(s,buf,len,flags,to,tolen);
#elif __WINDOWS__
	int nSent = sendto(s,(const char *)buf,len,flags,to,tolen);
#endif

	if ( nSent == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {

		case EWOULDBLOCK : 
			//throw NonBlockingIOException();
			// by sigi. 2002.5.17
			return 0;

		case ECONNRESET :
		case EPIPE :
			throw ConnectException(strerror(errno));

		case EBADF : 
		case ENOTSOCK : 
		case EFAULT : 
		case EMSGSIZE : 
		case ENOBUFS : 
			throw Error(strerror(errno));

		default : 
			//throw UnknownError(strerror(errno),errno);
			throw ConnectException(strerror(errno));
		}	
#elif __WINDOWS__
#endif
	}

	return nSent;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// uint SocketAPI::recv_ex ( SOCKET s , void * buf , uint len , uint flags )
//      throw ( NonBlockingIOException , ConnectException , Error )
//
// exception version of recv()
//
// Parameters 
//     s     - socket descriptor
//     buf   - input buffer
//     len   - input data length
//     flags - send flag (MSG_OOB,MSG_DONTROUTE)
// 
// Return 
//     length of bytes received
// 
// Exceptions 
//     NonBlockingIOException
//     ConnectException
//     Error 
//
//////////////////////////////////////////////////////////////////////
uint SocketAPI::recv_ex ( SOCKET s , void * buf , uint len , uint flags )
     throw ( NonBlockingIOException ,
             ConnectException ,
             Error )
{
	__BEGIN_TRY

#if __LINUX__
	int nrecv = recv(s,buf,len,flags);
#elif __WINDOWS__
	int nrecv = recv(s,(char*)buf,len,flags);
#endif

	if ( nrecv == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {

		case EWOULDBLOCK : 
			// by sigi. 2002.5.17
			return 0;
			//throw NonBlockingIOException();

		case ECONNRESET :
		case EPIPE :
			throw ConnectException(strerror(errno));

		case EBADF : 
		case ENOTCONN : 
		case ENOTSOCK : 
		case EINTR : 
		case EFAULT : 
			throw Error(strerror(errno));

		default : 
			throw UnknownError(strerror(errno),errno);
		}//end of switch

#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAEFAULT : 
			throw Error("The buf parameter is not completely contained in a valid part of the user address space.");
		case WSAENOTCONN : 
			throw Error("The socket is not connected.");
		case WSAEINTR : 
			throw Error("The (blocking) call was canceled through WSACancelBlockingCall.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAENETRESET : 
			throw ConnectException("The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		case WSAEOPNOTSUPP : 
			throw Error("MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, out-of-band data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.");
		case WSAESHUTDOWN : 
			throw Error("The socket has been shut down; it is not possible to recv on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.");
		case WSAEWOULDBLOCK : 
			throw NonBlockingIOException("The socket is marked as nonblocking and the receive operation would block.");
		case WSAEMSGSIZE : 
			throw Error("The message was too large to fit into the specified buffer and was truncated.");
		case WSAEINVAL : 
			throw Error("The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.");
		case WSAECONNABORTED : 
			throw ConnectException("The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.");
		case WSAETIMEDOUT : 
			throw ConnectException("The connection has been dropped because of a network failure or because the peer system failed to respond.");
		case WSAECONNRESET : 
			throw ConnectException("The virtual circuit was reset by the remote side executing a 'hard' or 'abortive' close. The application should close the socket as it is no longer usable. On a UDP datagram socket this error would indicate that a previous send operation resulted in an ICMP 'Port Unreachable' message.");
		default :
			throw UnknownError("recv()");
		}//end of switch
#endif
	} 
	else if ( nrecv == 0 )
	{
		throw ConnectException("connect closed.");
	}

	return nrecv;
	
	__END_CATCH
}


/////////////////////////////////////////////////////////////////////
// exception version of recvfrom()
/////////////////////////////////////////////////////////////////////
uint SocketAPI::recvfrom_ex ( SOCKET s , void * buf , int len , uint flags , struct sockaddr * from , uint * fromlen )
    throw ( NonBlockingIOException , ConnectException , Error )
{
	__BEGIN_TRY

#if __LINUX__
	int nReceived = recvfrom(s,buf,len,flags,from,fromlen);

	//SOCKADDR_IN* sa = (SOCKADDR_IN*)from;
	//cout << "recvfrom_ex : " << inet_ntoa(sa->sin_addr) << ":" << sa->sin_port << endl;

#elif __WINDOWS__
	int nReceived = recvfrom(s,(char*)buf,len,flags,from,(int*)fromlen);
#endif

	if ( nReceived == SOCKET_ERROR ) {
#if __LINUX__
		switch ( errno ) {

		case EWOULDBLOCK : 
			//throw NonBlockingIOException();
			// by sigi. 2002.5.17
			return 0;

		case ECONNRESET :
		case EPIPE :
			throw ConnectException(strerror(errno));

		case EBADF : 
		case ENOTCONN : 
		case ENOTSOCK : 
		case EINTR : 
		case EFAULT : 
			throw Error(strerror(errno));

		default : 
			throw UnknownError(strerror(errno),errno);
		}//end of switch
#elif __WINDOWS__
#endif
	}

	return nReceived;

	__END_CATCH
}


/////////////////////////////////////////////////////////////////////
//
// void SocketAPI::closesocket_ex ( SOCKET s )
//      throw ( Error )
//
// exception version of closesocket()
//
// Parameters
//     s - socket descriptor
//
// Return
//     none
//
// Exceptions
//     Error
//
/////////////////////////////////////////////////////////////////////
void SocketAPI::closesocket_ex ( SOCKET s )
     throw ( FileNotOpenedException, Error )
{
	__BEGIN_TRY

#if __LINUX__
	// using close_ex()
	FileAPI::close_ex(s);
#elif __WINDOWS__
	if ( closesocket(s) == SOCKET_ERROR ) {
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed.");
		case WSAENOTSOCK : 
			throw FileNotOpenedException("The descriptor is not a socket.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAEINTR : 
			throw Error("The (blocking) Windows Socket 1.1 call was canceled through WSACancelBlockingCall.");
		case WSAEWOULDBLOCK : 
			throw Error("The socket is marked as nonblocking and SO_LINGER is set to a nonzero time-out value.");
		default : 
			throw UnknownError("closesocket()");
		}//end of switch
	}
#endif
	
	__END_CATCH
}


/////////////////////////////////////////////////////////////////////
//
// void SocketAPI::ioctlsocket_ex ( SOCKET s , long cmd , ulong * argp )
//      throw ( Error )
//
// exception version of ioctlsocket()
//
/////////////////////////////////////////////////////////////////////
void SocketAPI::ioctlsocket_ex ( SOCKET s , long cmd , ulong * argp )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	throw UnsupportedError(__PRETTY_FUNCTION__);
#elif __WINDOWS__
	if ( ioctlsocket(s,cmd,argp) == SOCKET_ERROR ) {
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function. ");
		case WSAENETDOWN : 
			throw Error("The network subsystem has failed. ");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. ");
		case WSAENOTSOCK : 
			throw Error("The descriptor s is not a socket. ");
		case WSAEFAULT : 
			throw Error("The argp parameter is not a valid part of the user address space. ");
		default :
			throw UnknownError("ioctlsocket()");
		}
	}
#endif
	
	__END_CATCH
}
 

//////////////////////////////////////////////////////////////////////
//
// bool SocketAPI::getsocketnonblocking_ex ( SOCKET s ) 
//      throw ( Error );
//
// check if this socket is nonblocking mode
//
// Parameters
//     s - socket descriptor
//
// Return
//     true if nonblocking, false if blocking
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::getsocketnonblocking_ex ( SOCKET s )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	return FileAPI::getfilenonblocking_ex(s);
#elif __WINDOWS__
	throw UnsupportedError();
#endif
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::setsocketnonblocking_ex ( SOCKET s , bool on ) 
//      throw ( Error );
//
// make this socket blocking/nonblocking
//
// Parameters
//     s  - socket descriptor
//     on - true if nonblocking, false if blocking
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::setsocketnonblocking_ex ( SOCKET s , bool on )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	FileAPI::setfilenonblocking_ex(s,on);
#elif __WINDOWS__
	ulong argp = ( on == true ) ? 1 : 0;
	ioctlsocket_ex(s,FIONBIO,&argp);
#endif
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// uint SocketAPI::availablesocket_ex ( SOCKET s )
//      throw ( Error )
//
// get amount of data in socket input buffer
//
// Parameters
//    s - socket descriptor
//
// Return
//    amount of data in socket input buffer
//
// Exceptions
//    Error
//
//////////////////////////////////////////////////////////////////////
uint SocketAPI::availablesocket_ex ( SOCKET s )
     throw ( Error )
{
	__BEGIN_TRY

#if __LINUX__
	return availablefile_ex(s);
#elif __WINDOWS__
	ulong argp = 0;
	ioctlsocket_ex(s,FIONREAD,&argp);
	return argp;
#endif
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::shutdown_ex ( SOCKET s , uint how )
// 	    throw ( Error )
//
// shutdown all or part of connection of socket
//
// Parameters
//     s   - socket descriptor
//     how - how to close ( all , send , receive )
//
// Return
//     none
//
// Exceptions
//     Error
//
//////////////////////////////////////////////////////////////////////
void SocketAPI::shutdown_ex ( SOCKET s , uint how )
	 throw ( Error )
{
	__BEGIN_TRY

	if ( shutdown(s,how) < 0 ) {
#if __LINUX__
		switch ( errno ) {
		case EBADF : 
			throw Error("s is not a valid descriptor.");
		case ENOTSOCK : 
			throw Error("s is a file, not a socket.");
		case ENOTCONN : 
			throw Error("The specified socket is not connected.");
		default : 
			throw UnknownError(strerror(errno),errno);
		}
#elif __WINDOWS__
		switch ( WSAGetLastError() ) {
		case WSANOTINITIALISED : 
			throw Error("A successful WSAStartup must occur before using this function.");
		case WSAENETDOWN :
			throw Error("The network subsystem has failed.");
		case WSAEINVAL : 
			throw Error("The how parameter is not valid, or is not consistent with the socket type. For example, SD_SEND is used with a UNI_RECV socket type.");
		case WSAEINPROGRESS : 
			throw Error("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
		case WSAENOTCONN : 
			throw Error("The socket is not connected (connection-oriented sockets only).");
		case WSAENOTSOCK : 
			throw Error("The descriptor is not a socket.");
		default :
			throw UnknownError("shutdown()");
		}
#endif
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// int SocketAPI::select_ex ( int maxfdp1 , fd_set * readset , fd_set * writeset , fd_set * exceptset , struct timeval * timeout )
//		throw ( Error )
//
// system call for I/O multiplexing
//
// Parameters
//     maxfdp1   - 테스트할 파일 디스크립터중 가장 큰 값 + 1
//     readset   - 입력이 들어왔는지 테스트할 파일 디스크립터의 집합
//     writeset  - 출력을 할 수 있는지 테스트할 파일 디스크립터의 집합
//     exceptset - OOB 데이타가 들어왔는지 테스트할 파일 디스크립터의 집합
//     timeout   - 얼마나 기다릴 것인가? 
//
// Return
//     positive count of ready descriptors
//
// Exceptions
//     InterruptedException
//     TimeoutException
//     Error
//
//////////////////////////////////////////////////////////////////////
int SocketAPI::select_ex ( int maxfdp1 , fd_set * readset , fd_set * writeset , fd_set * exceptset , struct timeval * timeout )
	throw ( TimeoutException , InterruptedException , Error )
{
	__BEGIN_TRY
#if __LINUX__
	int result;

	try {

		result = select( maxfdp1 , readset , writeset , exceptset , timeout );

		if ( result == 0 )
			// by sigi. 2002.5.17
			return 0;
			//throw TimeoutException();

		/*
	    // 주석처리 by sigi. 2002.5.17
		if ( result < 0 ) {
			switch ( errno ) {
			case EINTR : 
				throw InterruptedException("A non blocked signal was caught.");
			case EBADF : 
				throw Error("An invalid file descriptor was given in one of the sets.");
			case EINVAL : 
				throw Error("parameter maxfdp1 is negative.");
			case ENOMEM : 
				throw Error("select was unable to allocate memory for internal tables.");
			default : 
				throw UnknownError(strerror(errno),errno);
			}
		}
		*/

	} catch ( Throwable & t ) {
		// 어떤 에러가 나든 무시한다.
//		cout << "셀렉트에서 이상한 에러가 난당.." << endl;
//		throw TimeoutException();
	}

	return result;

#elif __WINDOWS__

	throw UnsupportedError();

#endif
	
	__END_CATCH
}
