//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGrayDarkness.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GRAY_DARKNESS__
#define __EFFECT_GRAY_DARKNESS__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGrayDarkness
//////////////////////////////////////////////////////////////////////////////

class EffectGrayDarkness : public Effect 
{
public:
	EffectGrayDarkness(Zone* pZone, ZoneCoord_t ZoneX, ZoneCoord_t ZoneY) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GRAY_DARKNESS; }

	void affect() {}
//	void affect(Creature* pCreature) ;
//	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) ;

	void unaffect() ;
//	void unaffect(Creature* pCreature)  {};
//	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) ;
//	void unaffect(Item* pItem)  {}

	string toString() const throw();

public:
	void setLevel(Attr_t l)  { m_Level = l;}
	Attr_t getLevel() const throw() { return m_Level;}
	
	void setDuration(Duration_t d)  { m_Duration = d; }
	Duration_t getDuration()  { return m_Duration;}
	
//	void setStartTime() throw() { getCurrentTime(m_StartTime);}
//	bool isHalfTimePassed() 
//	{
//		Timeval currentTime;
//		getCurrentTime(currentTime);
//		if((currentTime.tv_sec - m_StartTime.tv_sec) >= m_Duration/10)
//			return true;
//
//		return false;
//	}
//	void setHalfTimeDeadline()
//	{
//		m_Duration /= 2;
//		m_Deadline.tv_sec = m_StartTime.tv_sec + m_Duration / 10;
//		m_Deadline.tv_usec = m_StartTime.tv_usec +(m_Duration%10)* 100000;
//	}
	
//	bool affectObject(Object*, bool bAffectByMove) ;
//	void unaffectObject(Object*, bool bUnaffectByMove) ;
	
private :
	Attr_t       m_Level;
	Duration_t   m_Duration;
	Timeval      m_StartTime ;// 기술이 시작된 시간.

};

/*class EffectGrayDarknessLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_GRAY_DARKNESS; }
	virtual string getEffectClassName() const throw() { return "EffectGrayDarkness"; }

public:
	virtual void load(Creature* pCreature)  {}
	virtual void load(Zone* pZone) ;
};

extern EffectGrayDarknessLoader* g_pEffectGrayDarknessLoader;*/

#endif // __EFFECT_GRAY_DARKNESS__
