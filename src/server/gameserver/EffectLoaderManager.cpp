//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoaderManager.cpp
// Written By  : elca, excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectLoaderManager.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Zone.h"

#include "EffectBloodDrain.h"
#include "EffectLight.h"
#include "EffectAftermath.h"
#include "EffectEnemyErase.h"
#include "EffectRestore.h"
#include "EffectKillAftermath.h"
#include "EffectMute.h"
#include "EffectOnBridge.h"

#include "EffectGreenPoison.h"
#include "EffectYellowPoison.h"
#include "EffectDarkness.h"
#include "EffectAcidSwamp.h"
#include "EffectContinualBloodyWall.h"
#include "EffectIceField.h"
#include "EffectProminence.h"

#include "EffectCanEnterGDRLair.h"
#include "EffectBehemothForceScroll.h"
#include "EffectSafeForceScroll.h"
#include "EffectCarnelianForceScroll.h"

EffectLoaderManager::EffectLoaderManager () 
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

EffectLoaderManager::~EffectLoaderManager () 
	throw()
{
	__BEGIN_TRY

	SAFE_DELETE(g_pEffectBloodDrainLoader);
	SAFE_DELETE(g_pEffectLightLoader);
	SAFE_DELETE(g_pEffectAftermathLoader);
	SAFE_DELETE(g_pEffectEnemyEraseLoader);
	SAFE_DELETE(g_pEffectRestoreLoader);
	SAFE_DELETE(g_pEffectKillAftermathLoader);
	SAFE_DELETE(g_pEffectMuteLoader);

	SAFE_DELETE(g_pEffectGreenPoisonLoader);
	SAFE_DELETE(g_pEffectYellowPoisonLoader);
	SAFE_DELETE(g_pEffectDarknessLoader);
	SAFE_DELETE(g_pEffectAcidSwampLoader);
	SAFE_DELETE(g_pEffectContinualBloodyWallLoader);
	SAFE_DELETE(g_pEffectIceFieldLoader);
	SAFE_DELETE(g_pEffectProminenceLoader);

	SAFE_DELETE(g_pEffectOnBridgeLoader);
	SAFE_DELETE(g_pEffectCanEnterGDRLairLoader);
	SAFE_DELETE(g_pEffectBehemothForceScrollLoader);
	SAFE_DELETE(g_pEffectSafeForceScrollLoader);
	SAFE_DELETE(g_pEffectCarnelianForceScrollLoader);

	__END_CATCH
}

void EffectLoaderManager::init () 
	throw(Error)
{
	__BEGIN_TRY

	m_pEffectLoaders[Effect::EFFECT_CLASS_BLOOD_DRAIN] = g_pEffectBloodDrainLoader = new EffectBloodDrainLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_LIGHT] = g_pEffectLightLoader = new EffectLightLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_AFTERMATH] = g_pEffectAftermathLoader = new EffectAftermathLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_ENEMY_ERASE] = g_pEffectEnemyEraseLoader = new EffectEnemyEraseLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_RESTORE] = g_pEffectRestoreLoader = new EffectRestoreLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_KILL_AFTERMATH] = g_pEffectKillAftermathLoader = new EffectKillAftermathLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_MUTE] = g_pEffectMuteLoader = new EffectMuteLoader();

	m_pEffectLoaders[Effect::EFFECT_CLASS_GREEN_POISON] = g_pEffectGreenPoisonLoader = new EffectGreenPoisonLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_YELLOW_POISON] = g_pEffectYellowPoisonLoader = new EffectYellowPoisonLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_DARKNESS] = g_pEffectDarknessLoader = new EffectDarknessLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_ACID_SWAMP] = g_pEffectAcidSwampLoader = new EffectAcidSwampLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_CONTINUAL_BLOODY_WALL] = g_pEffectContinualBloodyWallLoader = new EffectContinualBloodyWallLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_ICE_FIELD] = g_pEffectIceFieldLoader = new EffectIceFieldLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_PROMINENCE] = g_pEffectProminenceLoader = new EffectProminenceLoader();

	m_pEffectLoaders[Effect::EFFECT_CLASS_ON_BRIDGE] = g_pEffectOnBridgeLoader = new EffectOnBridgeLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR] = g_pEffectCanEnterGDRLairLoader = new EffectCanEnterGDRLairLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_BEHEMOTH_FORCE_SCROLL] = g_pEffectBehemothForceScrollLoader = new EffectBehemothForceScrollLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_SAFE_FORCE_SCROLL] = g_pEffectSafeForceScrollLoader = new EffectSafeForceScrollLoader();
	m_pEffectLoaders[Effect::EFFECT_CLASS_CARNELIAN_FORCE_SCROLL] = g_pEffectCarnelianForceScrollLoader = new EffectCarnelianForceScrollLoader();

	__END_CATCH
}

void EffectLoaderManager::load (Slayer* pSlayer) 
	throw(Error)
{
	__BEGIN_TRY

	g_pEffectBloodDrainLoader->load(pSlayer);
	g_pEffectLightLoader->load(pSlayer);
	g_pEffectAftermathLoader->load(pSlayer);
	g_pEffectEnemyEraseLoader->load(pSlayer);
	g_pEffectRestoreLoader->load(pSlayer);
	g_pEffectKillAftermathLoader->load(pSlayer);
	g_pEffectMuteLoader->load(pSlayer);
	g_pEffectCanEnterGDRLairLoader->load(pSlayer);
	g_pEffectBehemothForceScrollLoader->load(pSlayer);
	g_pEffectSafeForceScrollLoader->load(pSlayer);
	g_pEffectCarnelianForceScrollLoader->load(pSlayer);

	__END_CATCH
}

void EffectLoaderManager::load (Vampire* pVampire) 
	throw(Error)
{
	__BEGIN_TRY

	g_pEffectBloodDrainLoader->load(pVampire);
	g_pEffectLightLoader->load(pVampire);
	g_pEffectAftermathLoader->load(pVampire);
	g_pEffectEnemyEraseLoader->load(pVampire);
	g_pEffectRestoreLoader->load(pVampire);
	g_pEffectKillAftermathLoader->load(pVampire);
	g_pEffectMuteLoader->load(pVampire);
	g_pEffectCanEnterGDRLairLoader->load(pVampire);
	g_pEffectBehemothForceScrollLoader->load(pVampire);
	g_pEffectSafeForceScrollLoader->load(pVampire);
	g_pEffectCarnelianForceScrollLoader->load(pVampire);

	__END_CATCH
}

void EffectLoaderManager::load (Ousters* pOusters) 
	throw(Error)
{
	__BEGIN_TRY

	g_pEffectBloodDrainLoader->load(pOusters);
	g_pEffectAftermathLoader->load(pOusters);
	g_pEffectKillAftermathLoader->load(pOusters);
	g_pEffectMuteLoader->load(pOusters);
	g_pEffectCanEnterGDRLairLoader->load(pOusters);
	g_pEffectBehemothForceScrollLoader->load(pOusters);
	g_pEffectSafeForceScrollLoader->load(pOusters);
	g_pEffectCarnelianForceScrollLoader->load(pOusters);

	__END_CATCH
}

void EffectLoaderManager::load (Zone* pZone)
	throw(Error)
{
	__BEGIN_TRY

	g_pEffectGreenPoisonLoader->load(pZone);
	g_pEffectYellowPoisonLoader->load(pZone);
	g_pEffectDarknessLoader->load(pZone);
	g_pEffectAcidSwampLoader->load(pZone);
	g_pEffectContinualBloodyWallLoader->load(pZone);
	g_pEffectIceFieldLoader->load(pZone);
	g_pEffectProminenceLoader->load(pZone);
	g_pEffectOnBridgeLoader->load(pZone);

	__END_CATCH
}

string EffectLoaderManager::toString () const
	throw()
{
	__BEGIN_TRY

	return "";

	__END_CATCH
}

// global variable definition
EffectLoaderManager* g_pEffectLoaderManager = NULL;
