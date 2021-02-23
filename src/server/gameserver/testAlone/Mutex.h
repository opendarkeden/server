#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "Types.h"

class Mutex {
public :
	Mutex() { m_bLock = false; }
	~Mutex();

	void setName(const string& name) {}

	void lock()		{ m_bLock = true; }
	void unlock()	{ m_bLock = false; }

public :
	bool m_bLock;
};

#endif
