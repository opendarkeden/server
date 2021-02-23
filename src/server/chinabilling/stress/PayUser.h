
#ifndef __PAY_USER__
#define __PAY_USER__

#include <string>
using namespace std;

#include "Timeval.h"


class PayUser
{
public:
	enum PHASE
	{
		PHASE_SET_LOGIN_TIME,
		PHASE_LOGIN,
		PHASE_MINUS_POINT,
		PHASE_LOGOUT,

		PHASE_MAX
	};

public:
	PayUser();
	~PayUser();

public:
	void execute();
	void executeSetLoginTime();
	void executeLogin();
	void executeMinusPoint();
	void executeLogout();

public:
	// get / set name
	const string& getName() const { return m_Name; }
	void setName( const string& name ) { m_Name = name; }

	// get / set Connection ID
	int getConID() const { return m_ConID; }
	void setConID( int id ) { m_ConID = id; }

	bool isPayEnd() const { return m_LeftTime <= 0; }
	Timeval getActionTime() const { return m_ActionTime; }
	
	// get / set Left time
	int getLeftTime() const { return m_LeftTime; }
	void setLeftTime( int leftTime ) { m_LeftTime = leftTime; }

	void setSendTime();
	void setRecvTime();

private:
	string		m_Name;
	int			m_ConID;
	Timeval		m_SendTime;
	PHASE		m_Phase;
	Timeval		m_ActionTime;
	int			m_LeftTime;
	int			m_LogoutRatio;
};

#endif
