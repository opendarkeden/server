//////////////////////////////////////////////////////////////////////////////
// Filename    : Event.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_H__
#define __EVENT_H__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class Event;
// 플레이어 클래스에 연관되어 있으며,
// 일정 시간 후에 특정 액션을 취하도록 해준다.
//////////////////////////////////////////////////////////////////////////////

class GamePlayer;

class Event 
{
public:
	enum EventClass 
	{
		EVENT_CLASS_RESURRECT,    // 크리처가 죽었을 경우, 부활시키기..
		EVENT_CLASS_MORPH,        // 슬레이어 -> 뱀파이어변신
		EVENT_CLASS_RESTORE,      // 뱀파이어 -> 슬레이어 변신
		EVENT_SAVE,               // 주기적으로 크리처 정보를 저장하기
		EVENT_CLASS_REGENERATION, // 뱀파이어를 주기적으로 회복해주기
		EVENT_CLASS_RELOAD_INFO,  // DB에서 info를 reload한다.
		EVENT_CLASS_TRANSPORT,    // Zone이동 한다.
		EVENT_CLASS_KICK,    	  // 얼마 후에 kick한다.
		EVENT_CLASS_SYSTEM_MESSAGE,  // Incoming에서 받은 System메세지를 갖고 있다가 뿌려준다.
		EVENT_CLASS_REFRESH_HOLY_LAND_PLAYER,	// Holy Land Race Bonus 변화에 따라 Holy Land Player Stat 을 갱신
		EVENT_CLASS_SHUTDOWN,	// 사용자들을 몽땅 정리하고 셧다운
		EVENT_CLASS_HEAD_COUNT,	// 30분에 한번씩 머리 딴 갯수 세장
		EVENT_CLASS_CBILLING,	// 중국 빌링. 주기적으로 minus point/minute 패킷을 보낸다.
		EVENT_CLASS_AUTH,		// Nprotect 인증
		EVENT_CLASS_MAX
	};

public:
	Event(GamePlayer* pGamePlayer) throw(Error);
	virtual ~Event() throw();
			
public:
	virtual EventClass getEventClass() const throw() = 0;

	// get event life-cycle
	// 기본적으로 모든 이벤트들은 1회용이다.
	virtual bool isTemporary() const throw() { return true; }
	virtual bool isPermanent() const throw() { return false; }

	virtual void activate() throw(Error) = 0;
	
	Timeval getDeadline() const throw() { return m_Deadline; }
	void setDeadline(Turn_t delay) throw();

	virtual string toString() const throw() = 0;

protected:
	GamePlayer* m_pGamePlayer; // 게임 플레이어 객체
	Timeval     m_Deadline;    // 실행 시간
	
};

#endif
