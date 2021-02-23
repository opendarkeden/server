//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEnemyErase.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ENEMY_ERASE__
#define __EFFECT_ENEMY_ERASE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEffectEnemyErase
//////////////////////////////////////////////////////////////////////////////

class EffectEnemyErase : public Effect 
{
public:
	EffectEnemyErase(Creature* pCreature) throw(Error);
	~EffectEnemyErase() throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ENEMY_ERASE; }

	string getEnemyName() const throw() { return m_EnemyName ;}
	void setEnemyName(const string & EnemyName) throw(Error) { m_EnemyName = EnemyName;}

    virtual void create(const string & ownerID) throw(Error);
    virtual void save(const string & ownerID) throw(Error);
    virtual void destroy(const string & ownerID) throw(Error);

	string toString() const throw();

private:
	string m_EnemyName;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectEnemyEraseLoader
//////////////////////////////////////////////////////////////////////////////

class EffectEnemyEraseLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_ENEMY_ERASE; }
	virtual string getEffectClassName() const throw() { return "EffectEnemyErase"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectEnemyEraseLoader* g_pEffectEnemyEraseLoader;

#endif // __EFFECT_ENEMY_ERASE__
