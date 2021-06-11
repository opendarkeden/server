
#include "PayUser.h"
#include "SBillingPlayerManager.h"
#include "SProfile.h"
#include "Properties.h"

#include <stdlib.h>

PayUser::PayUser()
{
	m_Phase = PHASE_SET_LOGIN_TIME;
	getCurrentTime( m_ActionTime );
	m_LeftTime = 100;
}

PayUser::~PayUser()
{
}

void PayUser::execute()
{
	switch ( m_Phase )
	{
		case PHASE_SET_LOGIN_TIME:
			executeSetLoginTime();
			break;
		case PHASE_LOGIN:
			executeLogin();
			break;
		case PHASE_MINUS_POINT:
			executeMinusPoint();
			break;
		case PHASE_LOGOUT:
			executeLogout();
			break;
		default:
			cout << "error phase : " << m_Name.c_str() << endl;
			m_LeftTime = 0;
			break;
	}
}

void PayUser::executeSetLoginTime()
{
	static int interval = g_pSBillingPlayerManager->getMinusIntervalInt() * 60;
	static int maxLoginTime = g_pConfig->getPropertyInt( "MaxLoginTime" );

	int gap = rand() % ( maxLoginTime - 10 ) + 10;
	m_ActionTime.tv_sec += gap;
	m_Phase = PHASE_LOGIN;
}

void PayUser::executeLogin()
{
	static int interval = g_pSBillingPlayerManager->getMinusIntervalInt() * 60;
	static int logoutRatio = g_pConfig->getPropertyInt( "LogoutRatio" );

	g_pSBillingPlayerManager->sendLogin( this, m_ConID );

	int m_LogoutRatio = rand() % logoutRatio;

	if ( rand() % 100 < m_LogoutRatio )
	{
		// send logout
		int gap = rand() % ( interval - 10 ) + 10;
		m_ActionTime.tv_sec += gap;
		m_Phase = PHASE_LOGOUT;
	}
	else
	{
		// send minus point
		m_ActionTime.tv_sec += interval;
		m_Phase = PHASE_MINUS_POINT;
	}
}

void PayUser::executeLogout()
{
	static int maxLoginTime = g_pConfig->getPropertyInt( "MaxLoginTime" );

	g_pSBillingPlayerManager->sendLogout( this, m_ConID );

	int gap = rand() % ( maxLoginTime - 10 ) + 10;
	m_ActionTime.tv_sec += gap;
	m_Phase = PHASE_LOGIN;
}

void PayUser::executeMinusPoint()
{
	static int interval = g_pSBillingPlayerManager->getMinusIntervalInt() * 60;

	g_pSBillingPlayerManager->sendMinusPoint( this, m_ConID );

	if ( rand() % 100 < m_LogoutRatio )
	{
		// send logout
		int gap = rand() % ( interval - 10 ) + 10;
		m_ActionTime.tv_sec += gap;
		m_Phase = PHASE_LOGOUT;
	}
	else
	{
		// send minus point
		m_ActionTime.tv_sec += interval;
		m_Phase = PHASE_MINUS_POINT;
	}
}

void PayUser::setSendTime()
{
	getCurrentTime( m_SendTime );
}

void PayUser::setRecvTime()
{
	Timeval tv;
	getCurrentTime( tv );

	Timeval gap = timediff( m_SendTime, tv);
	g_pSProfile->addTime( gap );;
}

