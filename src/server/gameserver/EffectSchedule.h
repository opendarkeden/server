//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSchedule.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SCHEDULE_H__
#define __EFFECT_SCHEDULE_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

enum EffectScheduleWorkCode
{
	WORKCODE_ADD_VAMPIRE_PORTAL = 0,
	WORKCODE_DELETE,

	WORKCODE_MAX
};


//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Effect;


//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleWork
//////////////////////////////////////////////////////////////////////////////

class EffectScheduleWork
{
public:
	EffectScheduleWork() ;
	~EffectScheduleWork() ;

public:
	int getCode(void) const { return m_Code; }
	void setCode(int code) { m_Code = code; }

	void* getData(void) const { return m_pData; }
	void setData(void* pData) { m_pData = pData; }

private:
	int   m_Code;     // 이펙트에 대한 작업 코드
	void* m_pData;    // 이펙트 작업 코드에 필요한 데이터
};


//////////////////////////////////////////////////////////////////////////////
// class EffectSchedule
//////////////////////////////////////////////////////////////////////////////

class EffectSchedule
{
public:
	EffectSchedule() ;
	~EffectSchedule() ;

public:
	// 작업 대상인 이펙트를 더한다.
	Effect* getEffect(void) const { return m_pEffect; }
	void setEffect(Effect* pEffect) { m_pEffect = pEffect; }

	// 작업을 더한다.
	void addWork(int WorkCode, void* pData) ;

	// 작업 중에 제일 앞에 있는 작업의 포인터를 리턴한다.
	EffectScheduleWork* getFrontWork(void) ;

private:
	Effect* m_pEffect;
	list<EffectScheduleWork*> m_WorkList;
};


//////////////////////////////////////////////////////////////////////////////
// class EffectScheduleManager
//////////////////////////////////////////////////////////////////////////////

class EffectScheduleManager
{
public:
	EffectScheduleManager() ;
	~EffectScheduleManager() ;

public:
	// 이펙트 스케쥴을 더한다.
	void addEffectSchedule(EffectSchedule* pEffectSchedule) ;

	// 이펙트 스케쥴을 실행한다.
	void heartbeat(void) ;

protected:
	list<EffectSchedule*> m_EffectScheduleList;
	mutable Mutex        m_Mutex;
};


#endif
