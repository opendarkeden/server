// by sigi. 2002.12.30

#ifndef __USER_GATEWAY_H__
#define __USER_GATEWAY_H__

#include "Types.h"
#include "Exception.h"
#include <vector>
#include "Mutex.h"

class UserGateway {
public :
	typedef vector<int> USER_INFO;	

	enum UserGatewayType
	{
		USER_IN_NORMAL ,

		USER_OUT_NORMAL ,
		USER_OUT_KICKED ,
		USER_OUT_INCOMING_INPUT_ERROR ,
		USER_OUT_INCOMING_INPUT_DISCONNECT ,
		USER_OUT_INCOMING_COMMAND_ERROR ,
		USER_OUT_INCOMING_COMMAND_DISCONNECT ,
		USER_OUT_INCOMING_OUTPUT_ERROR ,
		USER_OUT_INCOMING_OUTPUT_DISCONNECT ,
		USER_OUT_INCOMING_OUTPUT_DISCONNECT2 ,
		USER_OUT_INCOMING_EXCEPTION ,
		USER_OUT_ZPM_INPUT_ERROR ,
		USER_OUT_ZPM_INPUT_DISCONNECT ,
		USER_OUT_ZPM_INPUT_DISCONNECT2 ,
		USER_OUT_ZPM_COMMAND_PAYPLAY_END ,
		USER_OUT_ZPM_COMMAND_ERROR ,
		USER_OUT_ZPM_OUTPUT_ERROR ,
		USER_OUT_ZPM_OUTPUT_DISCONNECT ,
		USER_OUT_ZPM_OUTPUT_DISCONNECT2 ,
		USER_OUT_ZPM_EXCEPTION ,

		MAX_USER_GATEWAY_TYPE
	};


public :
	UserGateway() ;
	~UserGateway()  ;

	static UserGateway* getInstance()
	{
		static UserGateway userGateway;
		return &userGateway;
	}

	static const string& getUserGatewayTypeToString(UserGatewayType ugt)
	{
		return s_UserGatewayTypeToString[ugt];
	}

	void 	clear() ;

	void	passUser(UserGatewayType ugt) ;
	int		getInfo(UserGatewayType ugt) const ;

	int		getTotalInfo() const ;

	string	toString() ;

protected :
	USER_INFO		m_UserInfos;
	static string	s_UserGatewayTypeToString[MAX_USER_GATEWAY_TYPE];

	mutable Mutex	m_Mutex;
};

#endif
