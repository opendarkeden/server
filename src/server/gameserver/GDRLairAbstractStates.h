#ifndef __GDR_LAIR_ABSTRACT_STATES_H__
#define __GDR_LAIR_ABSTRACT_STATES_H__

#include "FiniteStateMachine.h"
#include "Timeval.h"
#include <list>
#include "Effect.h"

class Monster;
class Zone;

class GDRScene : public State
{
public:
	enum ActionType
	{
		ACTION_WAIT,
		ACTION_SAY,
		ACTION_WALK,
		ACTION_EFFECT,
		ACTION_HOLLYWOOD,	// -_- 시뮬레이션 액션
		ACTION_WARP,		// 애들 다 데리고 지정 위치로 워프한다
	};

	class Action
	{
		Monster* m_pTarget;

	public:
		Monster*	getTarget() const { return m_pTarget; }

				Action(Monster* pTarget) : m_pTarget(pTarget) { }
		virtual ~Action() { }
		virtual ActionType	getActionType() const = 0;
		// 다 했으면 0을 리턴. 아니면 다음번 execute할때까지 시간을 리턴
		virtual Turn_t		execute() = 0;
	};

	class ActionWait : public Action
	{
		bool m_bWait;
		Turn_t m_Delay;
	public:
		ActionWait(Monster* pTarget, Turn_t delay) : Action(pTarget), m_bWait(false), m_Delay(delay) { }
		ActionType	getActionType() const { return ACTION_WAIT; }
		Turn_t		execute() { if ( !m_bWait ) { m_bWait = true; return m_Delay; } else return 0; }
	};

	class ActionSay : public Action
	{
		uint	m_strID;
	public:
		ActionSay(Monster* pTarget, uint strID) : Action(pTarget), m_strID(strID) { }
		ActionType	getActionType() const { return ACTION_SAY; }
		Turn_t		execute();
	};

	class ActionWalk : public Action
	{
		ZoneCoord_t	m_TargetX;
		ZoneCoord_t	m_TargetY;
		Turn_t		m_MoveDelay;
		int			m_DodgeCount;
	public:
		ActionWalk(Monster* pTarget, ZoneCoord_t X, ZoneCoord_t Y, Turn_t delay) : Action(pTarget), m_TargetX(X), m_TargetY(Y), m_MoveDelay(delay), m_DodgeCount(0) { }
		ActionType	getActionType() const { return ACTION_WALK; }
		Turn_t		execute();
	};

	class ActionEffect : public Action
	{
		Effect::EffectClass m_EffectClass;
		Turn_t				m_Duration;
	public:
		ActionEffect(Monster* pTarget, Effect::EffectClass eClass, Turn_t duration) : Action(pTarget), m_EffectClass(eClass), m_Duration(duration) { }
		ActionType	getActionType() const { return ACTION_EFFECT; }
		Turn_t		execute();
	};

	class ActionRemoveEffect : public Action
	{
		Effect::EffectClass m_EffectClass;
	public:
		ActionRemoveEffect(Monster* pTarget, Effect::EffectClass eClass) : Action(pTarget), m_EffectClass(eClass) { }
		ActionType	getActionType() const { return ACTION_EFFECT; }
		Turn_t		execute();
	};

	class ActionHollywood : public Action
	{
	public:
		ActionHollywood(Monster* pTarget) : Action(pTarget) { }
		ActionType	getActionType() const { return ACTION_HOLLYWOOD; }
		Turn_t		execute();
	};

	class ActionWarp: public Action
	{
		ZoneCoord_t	m_TargetX;
		ZoneCoord_t	m_TargetY;
	public:
		ActionWarp(Monster* pTarget, ZoneCoord_t X, ZoneCoord_t Y) : Action(pTarget), m_TargetX(X), m_TargetY(Y) { }
		ActionType	getActionType() const { return ACTION_WARP; }
		Turn_t		execute();
	};

protected:
	list<Action*>	m_ActionList;
	list<Action*>::iterator	m_NextAction;
	Timeval			m_NextActionTurn;
	DWORD			m_NextState;

	Monster*		getGDR() const;
	void			setGDR(Monster* pGDR) const;

public:
	GDRScene( DWORD nState ) : m_NextState(nState) { }
	// 하위 클래스에서는 반드시 세팅을 끝낸 뒤에 이 start 를 불러줘야 된다.
	void			start();
	DWORD			heartbeat(Timeval currentTime);
};

class MonsterSummonState : public TimerState
{
public:
	class GroupSummonInfo;

	class SummonInfo
	{
		MonsterType_t	m_MonsterType;
		int				m_MonsterNum;
		ZoneCoord_t		m_X;
		ZoneCoord_t		m_Y;
	public:
		SummonInfo(MonsterType_t mType, int num, ZoneCoord_t X, ZoneCoord_t Y) :
			m_MonsterType(mType), m_MonsterNum(num), m_X(X), m_Y(Y) { }
		friend class GroupSummonInfo;
	};

	class GroupSummonInfo
	{
		list<SummonInfo*>	m_SummonInfos;
	public:
		list<SummonInfo*>&			getSummonInfos() { return m_SummonInfos; }
		const list<SummonInfo*>&	getSummonInfos() const { return m_SummonInfos; }

		void						executeSummon( Zone* pZone );
	};

	MonsterSummonState( Zone* pZone, DWORD clearState, DWORD failState, DWORD timeoutState, Turn_t timeLimit ) :
		TimerState( timeoutState, timeLimit ), m_pZone( pZone ), m_ClearState( clearState ), m_FailState( failState ), m_TimeLimit( true ) { }
	MonsterSummonState( Zone* pZone, DWORD clearState, DWORD failState ) :
		TimerState( clearState, 999999999 ), m_pZone(pZone), m_ClearState( clearState ), m_FailState( failState ), m_TimeLimit(false) { }

	void	start();
	DWORD	heartbeat(Timeval currentTime);

private:
	Zone*	m_pZone;
	DWORD	m_ClearState;
	DWORD	m_FailState;
	bool	m_TimeLimit;

protected:
	list<GroupSummonInfo*>	m_GroupSummonInfos;
	list<GroupSummonInfo*>::iterator	m_CurrentSummonInfo;
};

#endif
