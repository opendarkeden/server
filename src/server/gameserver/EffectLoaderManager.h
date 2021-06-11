//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoaderManager.h
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LOADER_MANAGER_H__
#define __EFFECT_LOADER_MANAGER_H__

#include "Types.h"
#include "Effect.h"
#include "EffectLoader.h"

class Slayer;
class Vampire;
class Ousters;

//////////////////////////////////////////////////////////////////////////////
// class EffectLoaderManager;
//////////////////////////////////////////////////////////////////////////////

class EffectLoaderManager 
{
public:
	EffectLoaderManager() ;
	~EffectLoaderManager() ;

public:
	void init() ;

	void load(Slayer* pSlayer) ;
	void load(Vampire* pVampire) ;
	void load(Ousters* pOusters) ;

	void load(Zone* pZone) ;

	string toString() const ;

private:
	EffectLoader* m_pEffectLoaders[Effect::EFFECT_CLASS_MAX];
};

extern EffectLoaderManager* g_pEffectLoaderManager;

#endif
