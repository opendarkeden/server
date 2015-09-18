//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillHandlerManager.cpp 
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SkillHandlerManager.h"
#include "Assert1.h"

// 일반 공격
#include "AttackMelee.h"
#include "AttackArms.h"

// 검계열
#include "DoubleImpact.h"
#include "TripleSlasher.h"
#include "RainbowSlasher.h"
#include "ThunderSpark.h"
#include "DancingSword.h"
#include "CrossCounter.h"
#include "FlashSliding.h"
#include "LightningHand.h"
#include "SwordWave.h"
#include "SnakeCombo.h"
#include "WindDivider.h"
#include "ThunderBolt.h"
#include "Expansion.h"
#include "MiracleShield.h"
#include "ThunderFlash.h"
#include "ThunderStorm.h"
#include "MentalSword.h"
#include "SwordRay.h"
#include "HitConvert.h"

// 도계열
#include "SingleBlow.h"
#include "SpiralSlay.h"
#include "TripleBreak.h"
#include "WildSmash.h"
#include "GhostBlade.h"
#include "PotentialExplosion.h"
#include "ShadowWalk.h"
#include "ChargingPower.h"
#include "HurricaneCombo.h"
#include "TornadoSever.h"
#include "Earthquake.h"
#include "Berserker.h"
#include "MoonlightSever.h"
#include "ShadowDancing.h"
#include "Typhoon.h"
#include "AirShield.h"
#include "PowerOfLand.h"
#include "MultiAmputate.h"
#include "WildTyphoon.h"

// 군인 계열
#include "QuickFire.h"
#include "DoubleShot.h"
#include "TripleShot.h"
#include "MultiShot.h"
#include "HeadShot.h"
#include "Piercing.h"
#include "Sniping.h"
#include "MindControl.h"
#include "Revealer.h"
#include "CreateBomb.h"
#include "CreateMine.h"
#include "InstallMine.h"
#include "DisarmMine.h"
#include "ObservingEye.h"
#include "BulletOfLight.h"
#include "Concealment.h"
#include "UltimateBlow.h"

// 인챈 계열
#include "CreateHolyWater.h"
#include "Light.h"
#include "DetectHidden.h"
#include "AuraBall.h"
#include "Bless.h"
#include "ContinualLight.h"
#include "Flare.h"
#include "Purify.h"
#include "AuraRing.h"
#include "Striking.h"
#include "DetectInvisibility.h"
//#include "Identify.h"
#include "AuraShield.h"
//#include "Enchant.h"
#include "Visible.h"
#include "VigorDrop.h"
#include "Sanctuary.h"
#include "Reflection.h"
#include "Hymn.h"
#include "LightBall.h"
#include "Rebuke.h"
#include "SpiritGuard.h"
#include "Requital.h"
#include "Lightness.h"

// 힐링 계열
#include "CureLightWounds.h"
#include "CurePoison.h"
#include "ProtectionFromPoison.h"
#include "CauseLightWounds.h"
#include "CureSeriousWounds.h"
#include "RemoveCurse.h"
#include "ProtectionFromCurse.h"
#include "CauseSeriousWounds.h"
#include "CureCriticalWounds.h"
#include "ProtectionFromAcid.h"
#include "Sacrifice.h"
#include "CauseCriticalWounds.h"
#include "CureAll.h"
#include "Regeneration.h"
#include "Resurrect.h"
#include "EnergyDrop.h"
#include "Peace.h"
#include "Activation.h"
#include "HolyBlast.h"
//#include "MassCure.h"
//#include "MassHeal.h"
#include "HolyArrow.h"
#include "TurnUndead.h"
#include "DenialMagic.h"
#include "Illendue.h"


// 뱀프 계열
#include "BloodDrain.h"

#include "PoisonousHands.h"
#include "GreenPoison.h"
#include "YellowPoison.h"
#include "DarkBluePoison.h"
#include "GreenStalker.h"

#include "AcidTouch.h"
#include "AcidBolt.h"
#include "AcidBall.h"
#include "AcidSwamp.h"

#include "Paralyze.h"
#include "Doom.h"
#include "Seduction.h"
//#include "Blind.h"
//#include "Death.h"

#include "BloodyNail.h"
#include "BloodyKnife.h"
#include "BloodyBall.h"
#include "BloodyWave.h"
#include "BloodyMasterWave.h"
#include "BloodyWarp.h"
#include "BloodySpear.h"
#include "BloodyWall.h"
#include "BloodySnake.h"
#include "BloodyBreaker.h"
#include "RapidGliding.h"

#include "Hide.h"
#include "Darkness.h"
#include "Invisibility.h"
#include "TransformToWolf.h"
#include "TransformToBat.h"

//#include "SummonWolf.h"
#include "SummonCasket.h"
#include "OpenCasket.h"
//#include "RaisingDead.h"
//#include "SummonServant.h"

#include "BloodyMarker.h"
#include "BloodyTunnel.h"

#include "PoisonStrike.h"
#include "AcidStrike.h"
#include "BloodyStrike.h"
#include "PoisonStorm.h"
#include "AcidStorm.h"
#include "BloodyStorm.h"
#include "Extreme.h"

#include "Unburrow.h"
#include "Untransform.h"

#include "EatCorpse.h"
#include "Howl.h"
#include "ThrowHolyWater.h"

#include "Restore.h"

#include "Uninvisibility.h"
#include "Death.h"
#include "Transfusion.h"
#include "Mephisto.h"


// 기타 계열
#include "CriticalGround.h"
#include "SummonMonsters.h"
#include "GroundAttack.h"
#include "MeteorStrike.h"

#include "Hallucination.h"
#include "DuplicateSelf.h"

// 2002.10.23
#include "SoulChain.h"

// 2002.12.26
#include "SharpShield.h"
#include "WideLightning.h"
#include "GunShotGuidance.h"

#include "HandsOfWisdom.h"
#include "Armageddon.h"

// 성지스킬
#include "MagicElusion.h"
#include "PoisonMesh.h"
#include "IllusionOfAvenge.h"
#include "WillOfLife.h"

// 아우스터즈 스킬
#include "Flourish.h"
#include "Evade.h"
#include "SharpRound.h"
#include "BackStab.h"
#include "Blunting.h"
#include "GammaChop.h"
#include "CrossGuard.h"
#include "KasasArrow.h"
#include "HandsOfFire.h"
#include "Prominence.h"
#include "RingOfFlare.h"
#include "BlazeBolt.h"
#include "IceField.h"
#include "WaterBarrier.h"
#include "NymphRecovery.h"
#include "Liberty.h"
#include "Tendril.h"

#include "StoneAuger.h"
#include "EarthsTeeth.h"
#include "AbsorbSoul.h"
#include "GnomesWhisper.h"
#include "HandsOfNizie.h"
#include "RefusalEther.h"

#include "EmissionWater.h"
#include "BeatHead.h"
#include "DivineSpirits.h"

#include "BlitzSliding.h"
#include "JabbingVein.h"
#include "GreatHeal.h"
#include "DivineGuidance.h"
#include "BlazeWalk.h"
#include "BloodyZenith.h"

#include "Rediance.h"
#include "LarSlash.h"
#include "Trident.h"
#include "HeartCatalyst.h"
#include "ProtectionFromBlood.h"

#include "MoleShot.h"
#include "Eternity.h"
#include "InstallTrap.h"
#include "HolyArmor.h"
#include "MercyGround.h"
#include "CreateHolyPotion.h"

#include "TransformToWerwolf.h"
#include "GrayDarkness.h"
#include "StoneSkin.h"
#include "TalonOfCrow.h"
#include "BiteOfDeath.h"
#include "AcidEruption.h"
#include "Teleport.h"
#include "FirePiercing.h"
#include "SoulRebirth.h"
#include "IceLance.h"
#include "ExplosionWater.h"
#include "FrozenArmor.h"
#include "ReactiveArmor.h"
#include "MagnumSpear.h"
#include "HellFire.h"
#include "GroundBless.h"

#include "SharpChakram.h"
#include "DestructionSpear.h"
#include "ShiftBreak.h"
#include "FatalSnick.h"
#include "ChargingAttack.h"
#include "DuckingWallop.h"
#include "DistanceBlitz.h"
#include "SummonGroundElemental.h"
#include "SummonFireElemental.h"
#include "SummonWaterElemental.h"
#include "MeteorStorm.h"
#include "WideIceField.h"

#include "Glacier1.h"
#include "Glacier2.h"
#include "IceAuger.h"
#include "IceHail.h"
#include "WideIceHail.h"
#include "IceWave.h"

#include "LandMineExplosion.h"
#include "ClaymoreExplosion.h"
#include "PleasureExplosion.h"
#include "DeleoEfficio.h"
#include "ReputoFactum.h"

#include "SwordOfThor.h"
#include "BurningSolCharging.h"
#include "BurningSolLaunch.h"
#include "SweepVice.h"
#include "Whitsuntide.h"
#include "ViolentPhantom.h"
#include "InstallTurret.h"
#include "TurretFire.h"
#include "SummonGoreGland.h"
#include "GoreGlandFire.h"
#include "ThrowingAxe.h"
#include "ChoppingFirewood.h"
#include "ChainThrowingAxe.h"
#include "MultiThrowingAxe.h"
#include "PlayingWithFire.h"

#include "InfinityThunderbolt.h"
#include "SpitStream.h"
#include "PlasmaRocketLauncher.h"
#include "BombingStar.h"
#include "IntimateGrail.h"
#include "NooseOfWraith.h"
#include "SetAfire.h"

// 아우스터즈 140레벨 스킬
#include "SharpHail.h"
#include "IceHorizon.h"
#include "FuryOfGnome.h"
#include "SummonMiga.h"
#include "SummonMigaAttack.h"
#include "Cannonade.h"
#include "SelfDestruction.h"
#include "ARAttack.h"
#include "SMGAttack.h"
#include "GrenadeAttack.h"

#include "UnterfeldwebelFire.h"
#include "FeldwebelFire.h"

// 승직 스킬
#include "Halo.h"
#include "Destinies.h"
#include "FierceFlame.h"
#include "ShadowOfStorm.h"
#include "WildWolf.h"
#include "Aberration.h"
#include "DragonTornado.h"
#include "BikeCrash.h"
#include "HarpoonBomb.h"
#include "PassingHeal.h"
#include "RottenApple.h"
#include "MonsterRangeSkill.h"

// global variable declaration
SkillHandlerManager * g_pSkillHandlerManager = NULL;

// 몬스터 레인지 스킬들
MonsterRangeSkill
	g_TraslaAttack(SKILL_TRASLA_ATTACK, false),
	g_PuscaAttack(SKILL_PUSCA_ATTACK, false),
	g_NodCopilaAttack(SKILL_NOD_COPILA_ATTACK, false),
	g_NodCopilaAttack2(SKILL_NOD_COPILA_ATTACK_2, false);

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SkillHandlerManager::SkillHandlerManager () 
	throw()
: m_SkillHandlers(NULL) , m_Size(SKILL_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// 스킬 핸들러 배열을 생성한다.
	m_SkillHandlers = new SkillHandler*[ m_Size ];
	
	// 스킬 핸들러의 배열을 초기화한다.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_SkillHandlers[i] = NULL;
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SkillHandlerManager::~SkillHandlerManager () 
	throw()
{
	__BEGIN_TRY
		
	Assert(m_SkillHandlers != NULL);

	// 스킬 핸들러를 각각 삭제한다.
	for (int i = 0 ; i < m_Size ; i ++) 
	{
		SAFE_DELETE(m_SkillHandlers[i]);
	}
	
	// 스킬핸들러 배열을 삭제한다.
	SAFE_DELETE_ARRAY(m_SkillHandlers);
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SkillHandlerManager::init ()
	 throw(Error)
{
	__BEGIN_TRY
		
	// 기본 공격
	addSkillHandler(&g_AttackMelee);
	addSkillHandler(&g_AttackArms);

	// 검 계열
	addSkillHandler(&g_DoubleImpact);
	addSkillHandler(&g_TripleSlasher);
	addSkillHandler(&g_RainbowSlasher);
	addSkillHandler(&g_ThunderSpark);
	addSkillHandler(&g_DancingSword);
	addSkillHandler(&g_CrossCounter);
	addSkillHandler(&g_FlashSliding);
	addSkillHandler(&g_LightningHand);
	addSkillHandler(&g_SwordWave);
	addSkillHandler(&g_SnakeCombo);
	addSkillHandler(&g_WindDivider);
	addSkillHandler(&g_ThunderBolt);
	addSkillHandler(&g_Expansion);
	addSkillHandler(&g_MiracleShield);
	addSkillHandler(&g_ThunderFlash);
	addSkillHandler(&g_ThunderStorm);
	addSkillHandler(&g_MentalSword);

	//addSkillHandler(&g_DragonRising);
	//addSkillHandler(&g_FiveStormCrash);
	//addSkillHandler(&g_HeavensSword);

	// 도계열
	addSkillHandler(&g_SingleBlow);
	addSkillHandler(&g_SpiralSlay);
	addSkillHandler(&g_TripleBreak);
	addSkillHandler(&g_WildSmash);
	addSkillHandler(&g_GhostBlade);
	addSkillHandler(&g_PotentialExplosion);
	addSkillHandler(&g_ShadowWalk);
	addSkillHandler(&g_ChargingPower);
	addSkillHandler(&g_HurricaneCombo);
	addSkillHandler(&g_TornadoSever);
	addSkillHandler(&g_Earthquake);
	addSkillHandler(&g_Berserker);
	addSkillHandler(&g_MoonlightSever);
	addSkillHandler(&g_ShadowDancing);
	addSkillHandler(&g_Typhoon);

	// 군인 계열
	addSkillHandler(&g_QuickFire);
	addSkillHandler(&g_DoubleShot);
	addSkillHandler(&g_TripleShot);
	addSkillHandler(&g_MultiShot);
	addSkillHandler(&g_HeadShot);
	addSkillHandler(&g_Piercing);
	addSkillHandler(&g_Sniping);
	addSkillHandler(&g_MindControl);
	addSkillHandler(&g_Revealer);
	//addSkillHandler(&g_DetectMine);
	addSkillHandler(&g_InstallMine);
	addSkillHandler(&g_CreateBomb);
	addSkillHandler(&g_CreateMine);
	addSkillHandler(&g_ObservingEye);

	// 인챈 계열
	addSkillHandler(&g_CreateHolyWater);
	addSkillHandler(&g_Light);
	addSkillHandler(&g_DetectHidden);
	addSkillHandler(&g_AuraBall);
	addSkillHandler(&g_Bless);
	addSkillHandler(&g_ContinualLight);
	addSkillHandler(&g_Flare);
	addSkillHandler(&g_Purify);
	addSkillHandler(&g_AuraRing);
	addSkillHandler(&g_Striking);
	addSkillHandler(&g_DetectInvisibility);
	//addSkillHandler(&g_Identify);
	addSkillHandler(&g_AuraShield);
	addSkillHandler(&g_VigorDrop);
	//addSkillHandler(&g_Enchant);
	addSkillHandler(&g_Visible);
	addSkillHandler(&g_Sanctuary);
	addSkillHandler(&g_Reflection);
	addSkillHandler(&g_Hymn);

	// 힐링 계열
	addSkillHandler(&g_CureLightWounds);
	addSkillHandler(&g_CurePoison);
	addSkillHandler(&g_ProtectionFromPoison);
	addSkillHandler(&g_CauseLightWounds);
	addSkillHandler(&g_CureSeriousWounds);
	addSkillHandler(&g_RemoveCurse);
	addSkillHandler(&g_ProtectionFromCurse);
	addSkillHandler(&g_CauseSeriousWounds);
	addSkillHandler(&g_CureCriticalWounds);
	addSkillHandler(&g_ProtectionFromAcid);
	addSkillHandler(&g_Sacrifice);
	addSkillHandler(&g_CauseCriticalWounds);
	addSkillHandler(&g_Resurrect);
	addSkillHandler(&g_EnergyDrop);
	addSkillHandler(&g_CureAll);
	addSkillHandler(&g_Peace);
	addSkillHandler(&g_Activation);
	addSkillHandler(&g_HolyBlast);
	//addSkillHandler(&g_RegenerationSkill);
	//addSkillHandler(&g_MassCure);
	//addSkillHandler(&g_MassHeal);

	// 뱀프 계열
	addSkillHandler(&g_BloodDrain);

	addSkillHandler(&g_PoisonousHands);
	addSkillHandler(&g_GreenPoison);
	addSkillHandler(&g_YellowPoison);
	addSkillHandler(&g_DarkBluePoison);
	addSkillHandler(&g_GreenStalker);

	addSkillHandler(&g_AcidTouch);
	addSkillHandler(&g_AcidBolt);
	addSkillHandler(&g_AcidBall);
	addSkillHandler(&g_AcidSwamp);

	addSkillHandler(&g_Paralyze);
	addSkillHandler(&g_Doom);
	addSkillHandler(&g_Seduction);
	//addSkillHandler(&g_Blind);
	addSkillHandler(&g_Death);

	addSkillHandler(&g_BloodyNail);
	addSkillHandler(&g_BloodyKnife);
	addSkillHandler(&g_BloodyBall);
	addSkillHandler(&g_BloodyWave);
	addSkillHandler(&g_BloodyMasterWave);
	addSkillHandler(&g_BloodyWarp);
	addSkillHandler(&g_BloodySpear);
	addSkillHandler(&g_BloodyWall);
	addSkillHandler(&g_BloodySnake);
	addSkillHandler(&g_BloodyBreaker);
	addSkillHandler(&g_RapidGliding);

	addSkillHandler(&g_Transfusion);
	addSkillHandler(&g_Mephisto);

	addSkillHandler(&g_Hide);
	addSkillHandler(&g_Darkness);
	addSkillHandler(&g_Invisibility);
	addSkillHandler(&g_TransformToWolf);
	addSkillHandler(&g_TransformToBat);

	//addSkillHandler(&g_SummonWolf);
	addSkillHandler(&g_SummonCasket);
	addSkillHandler(&g_OpenCasket);
	//addSkillHandler(&g_RaisingDead);
	//addSkillHandler(&g_SummonServant);
	
	addSkillHandler(&g_BloodyMarker);
	addSkillHandler(&g_BloodyTunnel);

	addSkillHandler(&g_PoisonStrike);
	addSkillHandler(&g_AcidStrike);
	addSkillHandler(&g_BloodyStrike);
	addSkillHandler(&g_PoisonStorm);
	addSkillHandler(&g_AcidStorm);
	addSkillHandler(&g_BloodyStorm);
	addSkillHandler(&g_Extreme);

	addSkillHandler(&g_Unburrow);
	addSkillHandler(&g_Untransform);
	addSkillHandler(&g_Uninvisibility);

	addSkillHandler(&g_EatCorpse);
	addSkillHandler(&g_Howl);
	addSkillHandler(&g_ThrowHolyWater);

	addSkillHandler(&g_Restore);
	
	addSkillHandler(&g_CriticalGround);
	addSkillHandler(&g_SummonMonsters);
	addSkillHandler(&g_GroundAttack);
	addSkillHandler(&g_MeteorStrike);
	addSkillHandler(&g_Hallucination);
	addSkillHandler(&g_DuplicateSelf);

	addSkillHandler(&g_SoulChain);

	addSkillHandler(&g_SharpShield);
	addSkillHandler(&g_WideLightning);
	addSkillHandler(&g_GunShotGuidance);

	addSkillHandler(&g_AirShield);
	addSkillHandler(&g_BulletOfLight);
	addSkillHandler(&g_HandsOfWisdom);
	addSkillHandler(&g_LightBall);
	addSkillHandler(&g_HolyArrow);
	addSkillHandler(&g_Rebuke);
	addSkillHandler(&g_SpiritGuard);
	addSkillHandler(&g_Regeneration);
	addSkillHandler(&g_PowerOfLand);
	addSkillHandler(&g_TurnUndead);
	addSkillHandler(&g_Armageddon);

	addSkillHandler(&g_MagicElusion);
	addSkillHandler(&g_PoisonMesh);
	addSkillHandler(&g_IllusionOfAvenge);
	addSkillHandler(&g_WillOfLife);

	addSkillHandler(&g_DenialMagic);
	addSkillHandler(&g_SwordRay);
	addSkillHandler(&g_Concealment);
	addSkillHandler(&g_Requital);
	addSkillHandler(&g_MultiAmputate);

	addSkillHandler(&g_HitConvert);
	addSkillHandler(&g_WildTyphoon);
	addSkillHandler(&g_UltimateBlow);
	addSkillHandler(&g_Illendue);
	addSkillHandler(&g_Lightness);

	addSkillHandler(&g_Flourish);
	addSkillHandler(&g_Evade);
	addSkillHandler(&g_SharpRound);
	addSkillHandler(&g_BackStab);
	addSkillHandler(&g_Blunting);
	addSkillHandler(&g_GammaChop);
	addSkillHandler(&g_CrossGuard);
	addSkillHandler(&g_KasasArrow);
	addSkillHandler(&g_HandsOfFire);
	addSkillHandler(&g_Prominence);
	addSkillHandler(&g_RingOfFlare);
	addSkillHandler(&g_BlazeBolt);
	addSkillHandler(&g_IceField);
	addSkillHandler(&g_WaterBarrier);
	addSkillHandler(&g_NymphRecovery);
	addSkillHandler(&g_Liberty);
	addSkillHandler(&g_Tendril);
	addSkillHandler(&g_StoneAuger);

	addSkillHandler(&g_EarthsTeeth);
	addSkillHandler(&g_AbsorbSoul);
	addSkillHandler(&g_GnomesWhisper);
	addSkillHandler(&g_HandsOfNizie);
	addSkillHandler(&g_RefusalEther);

	addSkillHandler(&g_EmissionWater);
	addSkillHandler(&g_BeatHead);

	addSkillHandler(&g_DivineSpirits);
	addSkillHandler(&g_BlitzSliding);
	addSkillHandler(&g_JabbingVein);
	addSkillHandler(&g_GreatHeal);
	addSkillHandler(&g_DivineGuidance);
	addSkillHandler(&g_BlazeWalk);
	addSkillHandler(&g_BloodyZenith);

	addSkillHandler(&g_Rediance);
	addSkillHandler(&g_LarSlash);
	addSkillHandler(&g_Trident);

	addSkillHandler(&g_HeartCatalyst);
	addSkillHandler(&g_ProtectionFromBlood);
	addSkillHandler(&g_MoleShot);
	addSkillHandler(&g_Eternity);

	addSkillHandler(&g_InstallTrap);
	addSkillHandler(&g_HolyArmor);
	addSkillHandler(&g_MercyGround);
	addSkillHandler(&g_CreateHolyPotion);

	addSkillHandler(&g_TransformToWerwolf);
	addSkillHandler(&g_GrayDarkness);
	addSkillHandler(&g_StoneSkin);
	addSkillHandler(&g_TalonOfCrow);
	addSkillHandler(&g_BiteOfDeath);
	addSkillHandler(&g_AcidEruption);

	addSkillHandler(&g_Teleport);
	addSkillHandler(&g_FirePiercing);
	addSkillHandler(&g_SoulRebirth);
	addSkillHandler(&g_IceLance);
	addSkillHandler(&g_ExplosionWater);
	addSkillHandler(&g_FrozenArmor);
	addSkillHandler(&g_ReactiveArmor);
	addSkillHandler(&g_MagnumSpear);
	addSkillHandler(&g_HellFire);
	addSkillHandler(&g_GroundBless);

	addSkillHandler(&g_SharpChakram);
	addSkillHandler(&g_DestructionSpear);
	addSkillHandler(&g_ShiftBreak);
	addSkillHandler(&g_FatalSnick);
	addSkillHandler(&g_ChargingAttack);
	addSkillHandler(&g_DuckingWallop);
	addSkillHandler(&g_DistanceBlitz);
	addSkillHandler(&g_SummonGroundElemental);
	addSkillHandler(&g_SummonFireElemental);
	addSkillHandler(&g_SummonWaterElemental);
	addSkillHandler(&g_MeteorStorm);
	addSkillHandler(&g_WideIceField);

	addSkillHandler(&g_Glacier1);
	addSkillHandler(&g_Glacier2);
	addSkillHandler(&g_IceAuger);
	addSkillHandler(&g_IceHail);
	addSkillHandler(&g_WideIceHail);
	addSkillHandler(&g_IceWave);

	addSkillHandler(&g_LandMineExplosion);
	addSkillHandler(&g_ClaymoreExplosion);
	addSkillHandler(&g_PleasureExplosion);

	addSkillHandler(&g_DeleoEfficio);
	addSkillHandler(&g_ReputoFactum);
	addSkillHandler(&g_SwordOfThor);
	addSkillHandler(&g_BurningSolCharging);
	addSkillHandler(&g_BurningSolLaunch);
	addSkillHandler(&g_SweepVice1);
	addSkillHandler(&g_SweepVice3);
	addSkillHandler(&g_SweepVice5);
	addSkillHandler(&g_Whitsuntide);
	addSkillHandler(&g_ViolentPhantom);
	addSkillHandler(&g_InstallTurret);
	addSkillHandler(&g_TurretFire);
	addSkillHandler(&g_SummonGoreGland);
	addSkillHandler(&g_GoreGlandFire);
	addSkillHandler(&g_ThrowingAxe);
	addSkillHandler(&g_ChoppingFirewood);
	addSkillHandler(&g_ChainThrowingAxe);
	addSkillHandler(&g_MultiThrowingAxe);
	addSkillHandler(&g_PlayingWithFire);

	addSkillHandler(&g_InfinityThunderbolt);
	addSkillHandler(&g_SpitStream);
	addSkillHandler(&g_PlasmaRocketLauncher);
	addSkillHandler(&g_IntimateGrail);
	addSkillHandler(&g_BombingStar);
	addSkillHandler(&g_SetAfire);
	addSkillHandler(&g_NooseOfWraith);

	addSkillHandler(&g_SharpHail);
	addSkillHandler(&g_IceHorizon);
	addSkillHandler(&g_FuryOfGnome);
	addSkillHandler(&g_SummonMiga);
	addSkillHandler(&g_SummonMigaAttack);
	addSkillHandler(&g_Cannonade);
	addSkillHandler(&g_SelfDestruction);
	addSkillHandler(&g_ARAttack);
	addSkillHandler(&g_SMGAttack);
	addSkillHandler(&g_GrenadeAttack);
	addSkillHandler(&g_Halo);
	addSkillHandler(&g_Destinies);
	addSkillHandler(&g_FierceFlame);
	addSkillHandler(&g_ShadowOfStorm);
	addSkillHandler(&g_WildWolf);
	addSkillHandler(&g_Aberration);
	addSkillHandler(&g_DragonTornado);
	addSkillHandler(&g_BikeCrash);
	addSkillHandler(&g_HarpoonBomb);
	addSkillHandler(&g_PassingHeal);
	addSkillHandler(&g_RottenApple);
	addSkillHandler(&g_TraslaAttack);
	addSkillHandler(&g_PuscaAttack);
	addSkillHandler(&g_NodCopilaAttack);
	addSkillHandler(&g_NodCopilaAttack2);
	addSkillHandler(&g_UnterfeldwebelFire);
	addSkillHandler(&g_FeldwebelFire);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SkillHandlerManager::addSkillHandler (SkillHandler * pSkillHandler) 
	 throw(Error)
{
	__BEGIN_TRY
		
	if (m_SkillHandlers[ pSkillHandler->getSkillType() ] != NULL) {
		StringStream msg;
		msg << "duplicate Skill Handler, " << pSkillHandler->getSkillHandlerName () ;
		throw Error(msg.toString());
	}
	
	// 스킬핸들러를 등록한다.
	m_SkillHandlers[ pSkillHandler->getSkillType() ] = pSkillHandler;
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SkillHandler * SkillHandlerManager::getSkillHandler (SkillType_t SkillType)
	throw(Error)
{
	__BEGIN_TRY

	// Wide Storm 을 가지고 있을 경우, Wide 처리는 원래 기술 안에서 처리한다.
/*	if (SkillType == SKILL_DARKNESS_WIDE )
	{
		SkillType = SKILL_DARKNESS;
	}
	else if (SkillType == SKILL_POISON_STORM_WIDE )
	{
		SkillType = SKILL_POISON_STORM;
	}
	else if (SkillType == SKILL_ACID_STORM_WIDE )
	{
		SkillType = SKILL_ACID_STORM;
	}
*/
	if (m_SkillHandlers[SkillType]  == NULL) 
	{
		StringStream msg;
		msg << "None Skill Handler (Type : " << (int)SkillType << ")";
		throw Error(msg.toString());
	}
	else if (SkillType > SKILL_MAX) 
	{
		StringStream msg;
		msg << "Skill Handler Upper Bound";
		throw Error(msg.toString());
	}

	return m_SkillHandlers[SkillType];
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string SkillHandlerManager::toString () const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "SkillHandlerManager(\n";
	for (int i = 0 ; i < m_Size ; i ++)
	{
		msg << "SkillHandlers[" << i << "] == ";
		msg	<< (m_SkillHandlers[i] == NULL ? "NULL" : m_SkillHandlers[i]->getSkillHandlerName());
		msg << "\n";
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}
	
