#include "UserGateway.h"

string
UserGateway::s_UserGatewayTypeToString[MAX_USER_GATEWAY_TYPE] = 
{
	"IN_NORMAL" ,
	"OUT_NORMAL" ,
	"KICKED" ,
	"I_I_ERROR" ,
	"I_I_DISCONNECT" ,
	"I_C_ERROR" ,
	"I_C_DISCONNECT" ,
	"I_O_ERROR" ,
	"I_O_DISCONNECT" ,
	"I_O_DISCONNECT2" ,
	"I_EXCEPTION" ,
	"ZPM_I_ERROR" ,
	"ZPM_I_DISCONNECT" ,
	"ZPM_I_DISCONNECT2" ,
	"ZPM_C_PAYPLAY_END" ,
	"ZPM_C_ERROR" ,
	"ZPM_O_ERROR" ,
	"ZPM_O_DISCONNECT" ,
	"ZPM_O_DISCONNECT2" ,
	"ZPM_EXCEPTION" ,
};

UserGateway::UserGateway()
	throw (Error)
{
	__BEGIN_TRY

	m_Mutex.setName("UserGateway");

	clear();

	__END_CATCH
}

UserGateway::~UserGateway()
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


void 	
UserGateway::clear()
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_UserInfos.clear();
	m_UserInfos.reserve( MAX_USER_GATEWAY_TYPE );

	for (int i=0; i<MAX_USER_GATEWAY_TYPE; i++)
	{
		m_UserInfos[i] = 0;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void    UserGateway::passUser(UserGatewayType ugt)
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_UserInfos[ugt]++;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

int     UserGateway::getInfo(UserGatewayType ugt) const 
	throw (Error)
{
	__BEGIN_TRY

	int userInfo = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	userInfo = m_UserInfos[ugt];

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return userInfo;

	__END_CATCH
}

int     UserGateway::getTotalInfo() const 
	throw (Error)
{
	__BEGIN_TRY

	int totalUserInfo = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for (int i=0; i<MAX_USER_GATEWAY_TYPE; i++)
	{
		totalUserInfo += m_UserInfos[i];
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return totalUserInfo;

	__END_CATCH
}


string	
UserGateway::toString()
	throw (Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "UserGateway( ";

	__ENTER_CRITICAL_SECTION(m_Mutex)

	bool bPreviousPrint = false;
	for (int i=0; i<MAX_USER_GATEWAY_TYPE; i++)
	{
		if (m_UserInfos[i]>0)
		{
			if (bPreviousPrint)
			{
				msg << ", ";
			}

			msg << getUserGatewayTypeToString((UserGatewayType)i) << "="
				<< m_UserInfos[i];
			bPreviousPrint = true;
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	msg << " )";

	return msg.toString();

	__END_CATCH
}

