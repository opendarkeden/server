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
	EffectEnemyErase(Creature* pCreature) ;
	~EffectEnemyErase() ;

public:
	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

    EffectClass getEffectClass() const  { return EFFECT_CLASS_ENEMY_ERASE; }

	string getEnemyName() const  { return m_EnemyName ;}
	void setEnemyName(const string & EnemyName)  { m_EnemyName = EnemyName;}

    virtual void create(const string & ownerID) ;
    virtual void save(const string & ownerID) ;
    virtual void destroy(const string & ownerID) ;

	string toString() const ;

private:
	string m_EnemyName;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectEnemyEraseLoader
//////////////////////////////////////////////////////////////////////////////

class EffectEnemyEraseLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const  { return Effect::EFFECT_CLASS_ENEMY_ERASE; }
	virtual string getEffectClassName() const  { return "EffectEnemyErase"; }

public:
	virtual void load(Creature* pCreature) ;
};

extern EffectEnemyEraseLoader* g_pEffectEnemyEraseLoader;

#endif // __EFFECT_ENEMY_ERASE__
