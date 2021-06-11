//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSanctuary.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SANCTUARY__
#define __EFFECT_SANCTUARY__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSanctuary
//////////////////////////////////////////////////////////////////////////////

class EffectSanctuary : public Effect 
{
public:
	EffectSanctuary(Zone* pZone, ZoneCoord_t ZoneX, ZoneCoord_t ZoneY, ZoneCoord_t CenterX, ZoneCoord_t CenterY) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SANCTUARY; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) ;

	void unaffect() ;
	void unaffect(Creature* pCreature)  {};
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) ;
	void unaffect(Item* pItem)  {}

	string toString() const throw();

public:

	void setCenterX(ZoneCoord_t x)  { m_CenterX = x;}
	ZoneCoord_t getCenterX() const throw() { return m_CenterX;}

	void setCenterY(ZoneCoord_t y)  { m_CenterY = y;}
	ZoneCoord_t getCenterY() const throw() { return m_CenterY;}

	void setLevel(Attr_t l)  { m_Level = l;}
	Attr_t getLevel() const throw() { return m_Level;}
	
	void setDuration(Duration_t d)  { m_Duration = d; }
	Duration_t getDuration()  { return m_Duration;}
	
	void setStartTime() throw() { getCurrentTime(m_StartTime);}
	bool isHalfTimePassed() 
	{
		Timeval currentTime;
		getCurrentTime(currentTime);
		if((currentTime.tv_sec - m_StartTime.tv_sec) >= m_Duration/10)
			return true;

		return false;
	}
	void setHalfTimeDeadline()
	{
		m_Duration /= 2;
		m_Deadline.tv_sec = m_StartTime.tv_sec + m_Duration / 10;
		m_Deadline.tv_usec = m_StartTime.tv_usec +(m_Duration%10)* 100000;
	}
	
	bool affectObject(Object*, bool bAffectByMove) ;
	void unaffectObject(Object*, bool bUnaffectByMove) ;
	
private :
	// effect의 중심좌표
	ZoneCoord_t	 m_CenterX;
	ZoneCoord_t	 m_CenterY;

	Attr_t       m_Level;
	Duration_t   m_Duration;
	Timeval      m_StartTime ;// 기술이 시작된 시간.

};

#endif // __EFFECT_SANCTUARY__
