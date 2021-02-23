//////////////////////////////////////////////////////////////////////
// 
// Filename    : BillingPlayerInfo.h 
// Written by  : sigi
// Description : 빌링시스템 접속 정보
// 
//////////////////////////////////////////////////////////////////////

#ifndef __BILLING_PLAYER_INFO_H__
#define __BILLING_PLAYER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Timeval.h"

class Player;

//////////////////////////////////////////////////////////////////////
//
// class BillingPlayerInfo
//
//////////////////////////////////////////////////////////////////////

class BillingPlayerInfo {

public :

	// constructor
	BillingPlayerInfo () throw (Error);
	
	// destructor
	virtual ~BillingPlayerInfo () throw (Error);

	// get debug string
	virtual string toString () const throw (Error);

public :
	void            setBillingUserKey(int buid) { m_BillingUserKey = buid; }
	int				getBillingUserKey() const  { return m_BillingUserKey; }

	void            setBillingSession(Player* pPlayer) throw (Error);
	const string&   getBillingSession() const  { return m_BillingSession; }
	
	void            setBillingUserStatus(const string& us)	{ m_BillingUserStatus = us; }
	const string&   getBillingUserStatus() const  { return m_BillingUserStatus; }

	bool			isBillingPlayAvaiable() const	{ return !m_BillingUserStatus.empty(); }

	virtual bool	sendBillingLogin() throw (Error) = 0;
	int				getBillingLoginRequestCount() const	{ return m_BillingLoginRequestCount; }

	void			setBillingLoginVerified(bool bVerified=true)	{ m_BillingLoginVerified = bVerified; }
	bool			isBillingLoginVerified() const	{ return m_BillingLoginVerified; }
	
protected :

	// for BillingServer. by sigi. 2002.11.18
	int 	m_BillingLoginRequestCount;
	Timeval	m_BillingNextLoginRequestTime;
	bool	m_BillingLoginVerified;
	int		m_BillingUserKey;
	string	m_BillingSession;
	string	m_BillingUserStatus;
};

#endif
