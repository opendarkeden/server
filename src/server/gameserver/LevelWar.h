#ifndef __LEVEL_WAR_H__
#define __LEVEL_WAR_H__

#include "Types.h"
#include "Exception.h"

#include "war/Work.h"
#include "LevelWarManager.h"

class LevelWar : public Work
{
	enum State
	{
		READY,
		START
	};

	State m_State;

	void executeStart();
	void executeEnd();

	LevelWarManager* m_pManager;
public:
	LevelWar(LevelWarManager* pManager) : m_pManager(pManager) { m_State = READY; }
	virtual void	execute() throw(Error);
	virtual string toString() const throw(Error);
};

#endif// __LEVEL_WAR_H__

