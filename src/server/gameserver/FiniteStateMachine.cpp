#include "FiniteStateMachine.h"

void FiniteStateMachine::heartbeat(Timeval currentTime)
{
	DWORD nextState;
	if ( m_bReset )
	{
		nextState = m_ResetState;
		m_bReset = false;
	}
	else
		nextState = m_pCurrentState->heartbeat(currentTime);

	// 상태가 바뀌는 경우
	if ( nextState != 0 )
	{
		// 현재 상태를 끝내고
		cout << "End state " << m_pCurrentState->toString() << endl;
		m_pCurrentState->end();
		m_pStateFactory->wasteState( m_pCurrentState );

		// 다음 상태로 간다.
		State* pNextState = m_pStateFactory->makeState( nextState );
		m_pCurrentState = pNextState;
		cout << "Start state " << m_pCurrentState->toString() << endl;
		m_pCurrentState->start();
	}
}

void TimerState::start()
{
	getCurrentTime( m_Deadline );
	cout << "lifespan : " << m_LifeSpan << endl;

	m_Deadline.tv_sec += m_LifeSpan;
}

DWORD TimerState::heartbeat(Timeval currentTime)
{
	if ( currentTime > m_Deadline )
	{
		return m_TimeOutState;
	}

	return 0;
}

void TimerState::expire()
{
	getCurrentTime(m_Deadline);
}

void SetTimeState::start()
{
	getCurrentTime( m_Deadline );
	VSDateTime currentTime = VSDateTime::currentDateTime();

	int getSecs = currentTime.secsTo( m_SetTime );
	m_Deadline.tv_sec += getSecs;
}

DWORD SetTimeState::heartbeat(Timeval currentTime)
{
	if ( currentTime > m_Deadline )
	{
		return m_TimeOutState;
	}

	return 0;
}

void SetTimeState::expire()
{
	setTimer( VSDateTime::currentDateTime() );
	getCurrentTime( m_Deadline );
}
