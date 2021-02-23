#ifndef __SMS_SERVICE_THREAD_H__
#define __SMS_SERVICE_THREAD_H__

#include "Types.h"
#include "Exception.h"
#include "Thread.h"

#include "DB.h"
#include "Mutex.h"

#include <string>
#include <list>

class SMSServiceThread;

class SMSMessage
{
public:
	SMSMessage( const string& senderName, const string& recvNum, const string& callerNum, const string& msg ) : m_SenderName(senderName), m_ReceiverNumber(recvNum), m_CallerNumber(callerNum), m_Message(msg) { }
	string	toString() const;

	friend class SMSServiceThread;
private:
	string	m_SenderName;
	string	m_ReceiverNumber;
	string	m_CallerNumber;
	string	m_Message;
};

class SMSServiceThread : public Thread
{
public:
	static SMSServiceThread& Instance() { static SMSServiceThread theInstance; return theInstance; }

	void run() throw();
	string	getName() const throw() { return "SMSServiceThread"; }

	void pushMessage( SMSMessage* pMsg );
	string getDBString( const string& msg ) const;
	bool isValidNumber( const string& num ) const;

private:
	SMSServiceThread() : m_QueueMutex(), m_pConnection(NULL) { m_QueueMutex.setName("SMS Queue Lock"); }

	Mutex				m_QueueMutex;
	list<SMSMessage*>	m_MessageQueue;
	Connection*			m_pConnection;
};

#endif
