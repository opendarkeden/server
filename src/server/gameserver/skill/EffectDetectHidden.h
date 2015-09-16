//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDetectHidden.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DETECT_HIDDEN__
#define __EFFECT_DETECT_HIDDEN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDetectHidden
//////////////////////////////////////////////////////////////////////////////

class EffectDetectHidden : public Effect 
{
public:
	EffectDetectHidden(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DETECT_HIDDEN; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

private:

};

#endif // __EFFECT_DETECT_HIDDEN__
