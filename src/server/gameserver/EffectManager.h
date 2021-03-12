//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectManager.h
// Written by  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Effect.h"
#include "EffectInfo.h"
#include "Timeval.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class EffectManager;
//////////////////////////////////////////////////////////////////////////////

class EffectManager 
{
public:
	EffectManager() ;
	virtual ~EffectManager() ;

public:
	void save(const string & ownerID) ;

	EffectInfo* getEffectInfo() ;

	bool isEffect(Effect::EffectClass EClass) ;

	void deleteEffect(Effect::EffectClass EClass) ;
	void deleteEffect(ObjectID_t ObjectID) ;
	void deleteEffect(Creature* pCreature, Effect::EffectClass EClass) ;
	Effect* findEffect(Effect::EffectClass EClass) const ;
	Effect* findEffect(ObjectID_t ObjectID) const ;

	// Enemy Erase 이펙트를 가려내기 위한 함수이다.
	Effect* findEffect(Effect::EffectClass EClass, string EnemyName) const ;

	// priority_queue에 등록하고, affect한다.
	void addEffect(Effect* pEffect) ;

	Effect* getEffect() const  { return m_Effects.front(); }

	// 현재 있는 모든 이펙트의 deadline 을 0으로 만든다.
	void setTimeOutAllEffect() ;

	// 일정 시간마다 실행되어야 하는 이펙트를 찾아서 affect 시키거나, 
	// expire 된 이펙트를 삭제한다.
//	int heartbeat() ;
	int heartbeat(const Timeval& currentTime) ;

	void	sendEffectInfo(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) ;

	// 현재 이펙트 개수 반환
	uint getSize() const { return m_Effects.size(); }

protected:
	list<Effect*> m_Effects;

	// by sigi. for debugging. 2002.12.23
	int m_LastEffectClass;

	EffectInfo	m_EffectInfo;
};

#endif
