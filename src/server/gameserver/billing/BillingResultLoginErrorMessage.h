#ifndef __BILLING_RESULT_LOGIN_ERROR_MESSAGE_H__
#define __BILLING_RESULT_LOGIN_ERROR_MESSAGE_H__

#include "Types.h"
#include "BillingInfo.h"
#include "Utility.h"
#include <string>
#include <hash_map>

class BillingResultLoginErrorMessage
{
public:
	static BillingResultLoginErrorMessage* Instance();

	string getMessage( int index ) const;

protected:
	BillingResultLoginErrorMessage();

	void initMessage();

private:
	static BillingResultLoginErrorMessage* _instance;

	typedef hash_map<int, string>			HashMapMessage;
	typedef HashMapMessage::iterator		HashMapMessageItr;
	typedef HashMapMessage::const_iterator	HashMapMessageConstItr;

	HashMapMessage m_Messages;
};


BillingResultLoginErrorMessage* BillingResultLoginErrorMessage::_instance = 0;

BillingResultLoginErrorMessage* BillingResultLoginErrorMessage::Instance()
{
	if ( _instance == 0 )
	{
		_instance = new BillingResultLoginErrorMessage;
	}
	
	return _instance;
}

BillingResultLoginErrorMessage::BillingResultLoginErrorMessage()
{
	initMessage();
}

void BillingResultLoginErrorMessage::initMessage()
{
	m_Messages[BILLING_RESULT_LOGIN_DB_ERROR]		= "DB에 접근할 수 없습니다.";
	m_Messages[BILLING_RESULT_LOGIN_NETWORK_ERROR]	= "네트워크에 오류가 발생하였습니다.";
	m_Messages[BILLING_RESULT_LOGIN_NO_CASH]		= "잔액이 부족합니다.";
	m_Messages[BILLING_RESULT_LOGIN_NO_SESSION]		= "세션이 없습니다.";
	m_Messages[BILLING_RESULT_LOGIN_BAD_PACKET]		= "정의 되지 않는 패킷";
	m_Messages[BILLING_RESULT_LOGIN_COM_ERROR]		= "COM 에러";
	m_Messages[BILLING_RESULT_LOGIN_NO_RESPONSE]	= "지정된 시간동안 응답이 없습니다.";
	m_Messages[BILLING_RESULT_LOGIN_NO_MACHINE]		= "해당 장비에 접속할 수 없습니다.";
	m_Messages[BILLING_RESULT_LOGIN_BAD_GAME_NO]	= "빌링 서버에 등록된 게임번호와 다릅니다.";
	m_Messages[BILLING_RESULT_LOGIN_ACCOUNT_ERROR]	= "빌링 어카운트의 서비스 에러";
	m_Messages[BILLING_RESULT_LOGIN_DENY]			= "해당 게임에 사용 불가능 ( 결제 정보는 있음 )";
	m_Messages[BILLING_RESULT_LOGIN_TIME_OVER]		= "유효 기간이 지남";
	m_Messages[BILLING_RESULT_LOGIN_BUSY]			= "빌링 서버 사용자가 많습니다.";
	m_Messages[BILLING_RESULT_LOGIN_UNKNOWN_ERROR]	= "정의 되지 않은 오류 번호입니다.";
	m_Messages[BILLING_RESULT_LOGIN_IP_COM_ERROR]	= "IP를 확인하는중 COM에러가 발생하였습니다.";
	m_Messages[BILLING_RESULT_LOGIN_IP_ERROR]		= "해당 IP를 보유한 공급자의 정보가 부족합니다.";
	m_Messages[BILLING_RESULT_LOGIN_KEY_COM_ERROR]	= "인증키를 확인하는 중 COM에러가 발생하였습니다.";
	m_Messages[BILLING_RESULT_LOGIN_NO_KEY]			= "인증키를 찾지 못했습니다.";
}

string BillingResultLoginErrorMessage::getMessage( int index ) const
{
	HashMapMessageConstItr itr = m_Messages.find( index );

	if ( itr == m_Messages.end() )
	{
		filelog( "BillingResultLoginErrorMessage.txt", "No Message ID : %d", index );
		return "";
	}

	return itr->second;
}

#endif
