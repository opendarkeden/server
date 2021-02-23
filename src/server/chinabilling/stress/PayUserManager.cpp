
#include "PayUserManager.h"
#include "Properties.h"
#include "Assert.h"
#include <stdio.h>

PayUserManager::PayUserManager()
{
	int stressUser = g_pConfig->getPropertyInt( "StressUser" );
	Assert( stressUser > 0 && stressUser <= 8000 );

	m_Users = stressUser;
	m_User = new (PayUser*)[m_Users];

	for ( int i = 0; i < m_Users; i++ )
	{
		m_User[i] = new PayUser;
	}
}

PayUserManager::~PayUserManager()
{
}

void PayUserManager::init()
	throw ( Error )
{
	__BEGIN_TRY

	int connections = g_pConfig->getPropertyInt( "Connections" );
	Assert( connections > 0 && connections <= 15 );

	char name[10];

	for ( int i = 0; i < m_Users; i++ )
	{
		sprintf( name, "user%04d", i );
		string sName(name);
		m_User[i]->setName( sName );
		m_User[i]->setConID( i / ( m_Users / connections ) );
	}

	__END_CATCH
}

void PayUserManager::run()
	throw ()
{
	__BEGIN_TRY

	while ( true )
	{
		usleep( 100 );

		Timeval currentTime;
		getCurrentTime( currentTime );

		for ( int i = 0; i < m_Users; i++ )
		{
			if ( !m_User[i]->isPayEnd() && m_User[i]->getActionTime() < currentTime )
			{
				m_User[i]->execute();
			}
		}
	}

	__END_CATCH
}

PayUser* PayUserManager::getUser( char* name )
{
	int index = atoi( (char*)&name[4] );

	return getUser( index );
}

PayUserManager* g_pPayUserManager = NULL;

