//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPoisonMesh.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_POISON_MESH__
#define __EFFECT_POISON_MESH__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPoisonMesh
//////////////////////////////////////////////////////////////////////////////

class EffectPoisonMesh : public Effect 
{
public:
	EffectPoisonMesh(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_POISON_MESH; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

public:
	void		setCasterID( ObjectID_t objectID ) { m_CasterID = objectID; }
	ObjectID_t	getCasterID() const { return m_CasterID; }

	void		setDamage( Damage_t damage ) { m_Damage = damage; }
	Damage_t	getDamage() const { return m_Damage; }

private:
	ObjectID_t	m_CasterID;
	Damage_t	m_Damage;
};

#endif // __EFFECT_POISON_MESH__
