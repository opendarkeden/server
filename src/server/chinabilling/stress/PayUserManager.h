
#ifndef __PAY_USER_MANAGER__
#define __PAY_USER_MANAGER__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"

#include "PayUser.h"

class PayUserManager : public Thread
{
public:
	PayUserManager();
	~PayUserManager();

public:
	void init() throw ( Error );
	void stop() throw ( Error ) {}
	void run() throw ();

public:
	PayUser* getUser( char* name );
	PayUser* getUser( int index ) { return m_User[index]; }

private:
	PayUser** m_User;
	int		m_Users;
};

extern PayUserManager* g_pPayUserManager;

#endif

