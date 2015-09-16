//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromCurse.h
// Written by  : excel96
// Description : 
// ProtectionFromCurse에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROTECTION_FROM_CURSE__
#define __EFFECT_PROTECTION_FROM_CURSE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromCurse
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromCurse : public Effect 
{
public:
	EffectProtectionFromCurse(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PROTECTION_FROM_CURSE; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
	Resist_t getResist(void) const throw() { return m_Resist; }
	void setResist(Resist_t resist) { m_Resist = resist; }

private :
	Resist_t m_Resist;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromCurseLoader
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromCurseLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_PROTECTION_FROM_CURSE; }
	virtual string getEffectClassName() const throw() { return "EffectProtectionFromCurse"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectProtectionFromCurseLoader* g_pEffectProtectionFromCurseLoader;

#endif // __EFFECT_PROTECTION_FROM_CURSE__
