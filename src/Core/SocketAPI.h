//////////////////////////////////////////////////////////////////////
//
// Filename    : SocketAPI.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_API_H__
#define __SOCKET_API_H__

// include files
#include "Types.h"
#include "Exception.h"

#if __WINDOWS__
#include <WinSock.h>
#elif __LINUX__
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif


//////////////////////////////////////////////////
//
// Windows에서는 SOCKET과 INVALID_SOCKET에 unsigned int를
// 사용한다. 만약 Windows라면 WinSock.h를 include했으므로
// SOCKET과 INVALID_SOCKET이 정의되어 있게 된다.
//
//////////////////////////////////////////////////
#if __LINUX__

	typedef int SOCKET;
	static const int INVALID_SOCKET = -1;
	static const int SOCKET_ERROR = -1;

#endif

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
static const uint szSOCKADDR_IN = sizeof(SOCKADDR_IN);

//////////////////////////////////////////////////////////////////////
//
// Platform Independent Socket API Collection (exception based)
//
//////////////////////////////////////////////////////////////////////

namespace SocketAPI {

//
// exception version of socket ()
//
SOCKET socket_ex (int domain, int type, int protocol) 
	throw (Error);


//
// exception version of bind ()
//
void bind_ex (SOCKET s, const struct sockaddr* name, uint namelen) 
	throw (BindException, Error);


//
// exception version of connect ()
//
void connect_ex (SOCKET s, const struct sockaddr* name, uint namelen)
	throw (ConnectException, NonBlockingIOException, Error);

//
// exception version of listen ()
//
void listen_ex (SOCKET s, uint backlog) 
	throw (Error);


//
// exception version of accept ()
//
SOCKET accept_ex (SOCKET s, struct sockaddr* addr, uint* addrlen)
	throw (NonBlockingIOException, ConnectException, Error);


//
// exception version of getsockopt ()
//
void getsockopt_ex (SOCKET s, int level, int optname, void* optval, uint* optlen)
	throw (Error);

uint getsockopt_ex2 (SOCKET s, int level, int optname, void* optval, uint* optlen)
	throw (Error);

//
// exception version of setsockopt ()
//
void setsockopt_ex (SOCKET s, int level, int optname, const void* optval, uint optlen)
	throw (Error);

//
// exception version of send()
//
uint send_ex (SOCKET s, const void* buf, uint len, uint flags)
	throw (NonBlockingIOException, ConnectException, Error, ProtocolException);


//
// exception version of sendto()
//
uint sendto_ex (SOCKET s, const void* buf, int len, unsigned int flags, const struct sockaddr* to, int tolen)
	throw (NonBlockingIOException, ConnectException, Error);

//
// exception version of recv()
//
uint recv_ex (SOCKET s, void* buf, uint len, uint flags)
	throw (NonBlockingIOException, ConnectException, Error);


//
// exception version of recvfrom()
//
uint recvfrom_ex (SOCKET s, void* buf, int len, uint flags, struct sockaddr* from, uint* fromlen)
	throw (NonBlockingIOException, ConnectException, Error);
 

//
// exception version of closesocket() 
//
// *CAUTION*
//
// in UNIX, close() used instead
//
void closesocket_ex (SOCKET s)
	throw (FileNotOpenedException, Error);


//
// exception version of ioctlsocket()
//
// *CAUTION*
//
// in UNIX, ioctl() used instead
//
void ioctlsocket_ex (SOCKET s, long cmd, ulong* argp)
	throw (Error);


//
// check if socket is nonblocking mode
//
bool getsocketnonblocking_ex (SOCKET s)
	throw (Error);


//
// make socket nonblocking mode
//
void setsocketnonblocking_ex (SOCKET s, bool on)
	throw (Error);


//
// get amount of data in socket input buffer
//
uint availablesocket_ex (SOCKET s)
	throw (Error);


//
// exception version of shutdown()
//
void shutdown_ex (SOCKET s, uint how)
	throw (Error);


//
// exception version of select()
//
int select_ex (int maxfdp1, fd_set* readset, fd_set* writeset, fd_set* exceptset, struct timeval* timeout)
	throw (TimeoutException, InterruptedException, Error);


};//end of namespace 

#endif
