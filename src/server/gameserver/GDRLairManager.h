#ifndef __GDR_LAIR_MANAGER_H__
#define __GDR_LAIR_MANAGER_H__

#include "Types.h"
#include "FiniteStateMachine.h"
#include "GDRLairAbstractStates.h"
#include "Thread.h"

class Monster;

enum GDRLairStatus
{
	GDR_LAIR_IDLE = 1,
	GDR_LAIR_ENTRANCE,
	GDR_LAIR_ILLUSIONS_WAY_ONLY,
	GDR_LAIR_ICEPOLE,
	GDR_LAIR_SCENE_1,
	GDR_LAIR_SUMMON_MONSTER,
	GDR_LAIR_SCENE_2,
	GDR_LAIR_SUMMON_GDR_DUP,
	GDR_LAIR_SCENE_3,
	GDR_LAIR_GDR_FIGHT,
	GDR_LAIR_SCENE_4,
	GDR_LAIR_AWAKENED_GDR_FIGHT,
	GDR_LAIR_SCENE_5,
	GDR_LAIR_MINION_FIGHT,
	GDR_LAIR_SCENE_6,
	GDR_LAIR_ENDING,
	GDR_LAIR_KILL_ALL,
};

// 평시. 레어는 쉬고 있고 시간이 되면 레어를 열어준다.
class GDRLairIdle : public SetTimeState
{
public:
	DWORD	getStateType() const { return GDR_LAIR_IDLE; }
	GDRLairIdle( const VSDateTime& date ) : SetTimeState( GDR_LAIR_ENTRANCE, date ) { }

	void start();

	State*	clone() { return new GDRLairIdle( getTimer() ); }
	string	toString() const { return "GDRLairIdle"; }
private:
};

// 20분간 레어가 열리면서 일루젼스 웨이 함정이 활성화된다.
class GDRLairEntrance : public TimerState
{
public:
	DWORD	getStateType() const { return GDR_LAIR_ENTRANCE; }
	GDRLairEntrance() : TimerState( GDR_LAIR_ICEPOLE, 1210 ) { }

	void start();
	DWORD heartbeat(Timeval currentTime);

	State*	clone() { return new GDRLairEntrance(); }
	string	toString() const { return "GDRLairEntrance"; }
};

// 레어 입구가 닫힌 뒤에도 5분간 일루젼스 웨이를 통과할 수 있는 시간이 있다.
// 그냥 5분 시간끄는거고 일루젼스 웨이를 한명이라도 통과하면 바로 Icepole
// State로 넘어간다.
/*class GDRLairIllusionsWayOnly : public TimerState
{
public:
	DWORD	getStateType() const { return GDR_LAIR_ILLUSIONS_WAY_ONLY; }
	GDRLairIllusionsWayOnly() : TimerState( GDR_LAIR_ICEPOLE, 600 ) { }
	DWORD	heartbeat(Timeval currentTime);

	void start();
	void end();

	State*	clone() { return new GDRLairIllusionsWayOnly(); }
	string	toString() const { return "GDRLairIllusionsWayOnly"; }
};*/

// 일루젼스 웨이를 통과한 플레이어가 있다면 얼음 기둥을 깰 수 있는 시간을
// 준다. 시작할 때 얼음 기둥을 소환하고 얼음 기둥 깨지면 그 자리에 1분뒤에
// 데미지를 주는 얼음기둥 이펙트가.. (--)
class GDRLairIcepole : public State
{
public:
	void start();
	DWORD	getStateType() const { return GDR_LAIR_ICEPOLE; }
	DWORD	heartbeat(Timeval currentTime);

	State*	clone() { return new GDRLairIcepole(); }
	string	toString() const { return "GDRLairIcepole"; }

private:
	Timeval	m_BroadcastTime;
};

// 얼음 기둥을 통과한 넘이 있다면 질드레가 등장한다.
// 질드레가 소환되고 이펙트가 발생하고 질드레 대사 1을 한다.
class GDRLairScene1 : public GDRScene
{
public:
	GDRLairScene1() : GDRScene( GDR_LAIR_SUMMON_MONSTER ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_1; }
	void	end();

	State*	clone() { return new GDRLairScene1(); }
	string	toString() const { return "GDRLairScene1"; }
};

// 질드레 레어에 일반 몬스터를 10회 소환한다.
// 살아남은 넘이 없어지면 Idle로
// 10회 소환한 뒤에도 살아남은 넘이 있으면 Scene2로
class GDRLairSummonMonster : public MonsterSummonState
{
public:
	GDRLairSummonMonster();
	DWORD	getStateType() const { return GDR_LAIR_SUMMON_MONSTER; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairSummonMonster(); }
	string	toString() const { return "GDRLairSummonMonster"; }
};

// 질드레가 대사 2를 하고 이펙트 시전 후 지정 위치로 이동한 뒤
// 대사 3을 한다.
class GDRLairScene2 : public GDRScene
{
public:
	GDRLairScene2() : GDRScene( GDR_LAIR_SUMMON_GDR_DUP ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_2; }
	void	end();

	State*	clone() { return new GDRLairScene2(); }
	string	toString() const { return "GDRLairScene2"; }
};

// 질드레가 분신을 소환한다.
class GDRLairSummonGDRDup : public MonsterSummonState
{
public:
	GDRLairSummonGDRDup();
	DWORD	getStateType() const { return GDR_LAIR_SUMMON_GDR_DUP; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairSummonGDRDup(); }
	string	toString() const { return "GDRLairSummonGDRDup"; }
};

// 질드레가 대사 4를 하고 이펙트를 시전한다.
class GDRLairScene3 : public GDRScene
{
public:
	GDRLairScene3() : GDRScene( GDR_LAIR_GDR_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_3; }
	void	end();

	State*	clone() { return new GDRLairScene3(); }
	string	toString() const { return "GDRLairScene3"; }
};

// 질드레가 활성화되어 플레이어들과 싸운다.
class GDRLairGDRFight : public State
{
public:
	DWORD	getStateType() const { return GDR_LAIR_GDR_FIGHT; }
	void	start();
	DWORD	heartbeat(Timeval currentTime);
	void	end();

	State*	clone() { return new GDRLairGDRFight(); }
	string	toString() const { return "GDRLairGDRFight"; }
};

// 질드레가 대사 5를 하고 엔딩 연출이 나온다.
// 이후 질드레 코어로 플레이어를 몽땅 옮겨버린뒤
// 질드레 각성체가 대사 6을 한다.
class GDRLairScene4 : public GDRScene
{
public:
	GDRLairScene4() : GDRScene( GDR_LAIR_AWAKENED_GDR_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_4; }

	State*	clone() { return new GDRLairScene4(); }
	string	toString() const { return "GDRLairScene4"; }
};

// 질드레 각성체가 활성화되어 플레이어들과 싸운다.
// HP가 50% 아래로 떨어지면 Scene5로, 죽으면 Scene6으로.
class GDRLairAwakenedGDRFight : public State
{
	bool	m_bGDRDamaged;
public:
	GDRLairAwakenedGDRFight(bool damaged = false) : m_bGDRDamaged(damaged) { }
	DWORD	getStateType() const { return GDR_LAIR_AWAKENED_GDR_FIGHT; }
	void	start();
	DWORD	heartbeat(Timeval currentTime);

	State*	clone() { return new GDRLairAwakenedGDRFight(m_bGDRDamaged); }
	string	toString() const { return "GDRLairAwakenedGDRFight"; }
};

// 대사 7을 하고 지정 위치로 이동한 뒤 대사 8을 한다.
class GDRLairScene5 : public GDRScene
{
public:
	GDRLairScene5() : GDRScene( GDR_LAIR_MINION_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_5; }

	State*	clone() { return new GDRLairScene5(); }
	string	toString() const { return "GDRLairScene5"; }
};

// 중간보스를 제한된 시간 안에 잡아야 한다.
class GDRLairMinionFight : public MonsterSummonState
{
public:
	GDRLairMinionFight();
	DWORD	getStateType() const { return GDR_LAIR_MINION_FIGHT; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairMinionFight(); }
	string	toString() const { return "GDRLairMinionFight"; }
};

// 대사 9를 하고 지정 위치로 이동한 뒤 대사 10을 한다.
class GDRLairScene6 : public GDRScene
{
public:
	GDRLairScene6() : GDRScene( GDR_LAIR_AWAKENED_GDR_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_6; }

	State*	clone() { return new GDRLairScene6(); }
	string	toString() const { return "GDRLairScene6"; }
};

// 죽으면서 대사를 하고 보상 아이템을 지급한다.
// 사실 별로 할 거 없다 -_-
class GDRLairEnding : public TimerState
{
public:
	GDRLairEnding() : TimerState( GDR_LAIR_IDLE, 10 ) { }
	DWORD	getStateType() const { return GDR_LAIR_ENDING; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairEnding(); }
	string	toString() const { return "GDRLairEnding"; }
};

// 끝장났다. 다 죽어라
class GDRLairKillAll : public TimerState
{
public:
	GDRLairKillAll() : TimerState( GDR_LAIR_IDLE, 10 ) { }
	DWORD	getStateType() const { return GDR_LAIR_KILL_ALL; }

	void	start();
//	DWORD	heartbeat(Timeval currentTime) { return GDR_LAIR_IDLE; }
	void	end();

	State*	clone() { return new GDRLairKillAll(); }
	string	toString() const { return "GDRLairKillAll"; }
};

// 질드레 레어를 총괄하는 매니저. ClientManager의 스레드에서 돈다.
class GDRLairManager : public FiniteStateMachine, public Thread
{
public:
	enum GDRLairZones
	{
		ILLUSIONS_WAY_1,
		ILLUSIONS_WAY_2,
		GDR_LAIR,
		GDR_LAIR_CORE,

		GDR_LAIR_MAX
	};

	void init();
	void run() throw();
	string getName() const throw() { return "GDRLairManager"; }

	static GDRLairManager& Instance() { static GDRLairManager theInstance; return theInstance; }
	Zone* getZone(int index) const { return m_pZones[index]; }

	Monster*	getGDR() const { return m_pGDR; }
	void		setGDR(Monster* pGDR) { m_pGDR = pGDR; }

	VSDateTime getNextOpenTime() const;

	BYTE		getCorrectPortal() const { return m_CorrectPortal; }
	void		setCorrectPortal(BYTE pid) { m_CorrectPortal = pid; }

	int			getTotalPCs() const;
	bool		isGDRLairZone(ZoneID_t ZoneID) const;

	void		open() { m_bCanEnter = true; }
	void		close() { m_bCanEnter = false; }
	bool		canEnter() const { return m_bCanEnter; }

	friend class GDRScene;
private:
	Monster*	m_pGDR;
	Zone*		m_pZones[GDR_LAIR_MAX];
	BYTE		m_CorrectPortal;
	bool		m_bCanEnter;
};

#endif
