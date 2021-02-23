#ifndef __FINITE_STATE_MACHINE_H__
#define __FINITE_STATE_MACHINE_H__

#include "Types.h"
#include "Timeval.h"
#include <hash_map>
#include "Assert.h"
#include "VSDateTime.h"

/**
 * 기본 abstract class들
 **/
class State
{
public:
	State() { }
	virtual ~State() { }

	virtual DWORD		getStateType() const = 0;

	// 다음 상태를 return 한다. StateType 0 은 상태가 변하지 않는다는 의미.
	virtual DWORD		heartbeat(Timeval currentTime) = 0;

	virtual void		start() { }
	virtual void		end() { }

	virtual State*		clone() = 0;
	virtual string		toString() const = 0;

private:
};

class StateFactory
{
public:
	virtual ~StateFactory() { }
	virtual State*	makeState(DWORD sType) = 0;
	virtual void	wasteState(State* pState) { }
};

class FiniteStateMachine
{
public:
	FiniteStateMachine() : m_pCurrentState(NULL), m_pStateFactory(NULL), m_bReset(false), m_ResetState(0) { }
	virtual ~FiniteStateMachine() { }

	virtual void init() = 0;
	virtual void heartbeat(Timeval currentTime);

	DWORD	getCurrentState() const { return m_pCurrentState->getStateType(); }
	State*	getCurrentState_Object() const { return m_pCurrentState; }

	void	reset() { m_bReset = true; }

protected:
	State*			m_pCurrentState;
	StateFactory*	m_pStateFactory;

	bool			m_bReset;
	DWORD			m_ResetState;
};

/**
 * 자주 사용될만한 기본 class들
 **/
class TimerState : public State
{
public:
	// 수명은 초단위이다.
	TimerState( DWORD nState, Turn_t life ) : m_TimeOutState(nState), m_LifeSpan(life) { }
	void		start();
	DWORD		heartbeat(Timeval currentTime);
	void		expire();

private:
	DWORD		m_TimeOutState;
	Turn_t		m_LifeSpan;
	Timeval		m_Deadline;
};

class SetTimeState : public State
{
public:
	SetTimeState( DWORD nState, const VSDateTime& date ) : m_TimeOutState(nState), m_SetTime(date) { }

	void	start();
	DWORD	heartbeat(Timeval currentTime);
	void	expire();

protected:
	void				setTimer( const VSDateTime& date ) { m_SetTime = date; }
	const VSDateTime&	getTimer() const { return m_SetTime; }
private:
	DWORD		m_TimeOutState;
	VSDateTime	m_SetTime;
	Timeval		m_Deadline;
};

// 그냥 모든 state를 갖고 있고 갖고 있는 객체를 넘겨준다.
// 객체 안에 상태가 들어있을 경우 서로 다른 FSM에서 공유가 안되므로 주의
class FlyweightStateFactory : public StateFactory
{
public:
	void	registerState( State* pState ) { Assert(m_StateMap[pState->getStateType()] == NULL); m_StateMap[pState->getStateType()] = pState; }
	State*	makeState(DWORD sType) { return m_StateMap[sType]; }

private:
	hash_map<DWORD, State*>	m_StateMap;
};

#endif
