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
	EffectLoaderManager() throw();
	~EffectLoaderManager() throw();

public:
	void init() throw(Error);

	void load(Slayer* pSlayer) throw(Error);
	void load(Vampire* pVampire) throw(Error);
	void load(Ousters* pOusters) throw(Error);

	void load(Zone* pZone) throw(Error);

	string toString() const throw();

private:
	EffectLoader* m_pEffectLoaders[Effect::EFFECT_CLASS_MAX];
};

extern EffectLoaderManager* g_pEffectLoaderManager;

#endif
