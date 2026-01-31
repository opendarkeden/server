//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillFormula.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "Monster.h"
#include "SkillHandler.h"
#include "Vampire.h"

// °Ë°è¿­
#include "CrossCounter.h"
#include "DancingSword.h"
#include "DoubleImpact.h"
#include "Expansion.h"
#include "FlashSliding.h"
#include "HitConvert.h"
#include "LightningHand.h"
#include "MentalSword.h"
#include "MiracleShield.h"
#include "RainbowSlasher.h"
#include "SharpShield.h"
#include "SnakeCombo.h"
#include "SwordRay.h"
#include "SwordWave.h"
#include "ThunderBolt.h"
#include "ThunderFlash.h"
#include "ThunderSpark.h"
#include "ThunderStorm.h"
#include "TripleSlasher.h"
#include "WideLightning.h"
#include "WindDivider.h"

// µµ°è¿­
#include "AirShield.h"
#include "Berserker.h"
#include "ChargingPower.h"
#include "Earthquake.h"
#include "GhostBlade.h"
#include "HurricaneCombo.h"
#include "MoonlightSever.h"
#include "MultiAmputate.h"
#include "PotentialExplosion.h"
#include "PowerOfLand.h"
#include "ShadowDancing.h"
#include "ShadowWalk.h"
#include "SingleBlow.h"
#include "SpiralSlay.h"
#include "TornadoSever.h"
#include "TripleBreak.h"
#include "Typhoon.h"
#include "WildSmash.h"
#include "WildTyphoon.h"

// ±ºÀÎ °è¿­
#include "DoubleShot.h"
#include "HeadShot.h"
#include "MindControl.h"
#include "MultiShot.h"
#include "Piercing.h"
#include "QuickFire.h"
#include "Sniping.h"
#include "TripleShot.h"
// #include "DetectMine.h"
#include "BulletOfLight.h"
#include "Concealment.h"
#include "CreateBomb.h"
#include "CreateMine.h"
#include "DisarmMine.h"
#include "GunShotGuidance.h"
#include "InstallMine.h"
#include "ObservingEye.h"
#include "Revealer.h"
#include "UltimateBlow.h"

// ÀÎÃ¦ °è¿­
#include "AuraBall.h"
#include "AuraRing.h"
#include "Bless.h"
#include "ContinualLight.h"
#include "CreateHolyWater.h"
#include "DetectHidden.h"
#include "DetectInvisibility.h"
#include "Flare.h"
#include "Light.h"
#include "Purify.h"
#include "Striking.h"
// #include "Identify.h"
#include "AuraShield.h"
// #include "Enchant.h"
#include "Hymn.h"
#include "LightBall.h"
#include "Lightness.h"
#include "Rebuke.h"
#include "Reflection.h"
#include "Requital.h"
#include "Sanctuary.h"
#include "SpiritGuard.h"
#include "VigorDrop.h"
#include "Visible.h"

// Èú¸µ °è¿­
#include "Activation.h"
#include "CauseCriticalWounds.h"
#include "CauseLightWounds.h"
#include "CauseSeriousWounds.h"
#include "CureAll.h"
#include "CureCriticalWounds.h"
#include "CureLightWounds.h"
#include "CurePoison.h"
#include "CureSeriousWounds.h"
#include "EnergyDrop.h"
#include "HolyBlast.h"
#include "ProtectionFromAcid.h"
#include "ProtectionFromCurse.h"
#include "ProtectionFromPoison.h"
#include "RegenerationSkill.h"
#include "RemoveCurse.h"
#include "Resurrect.h"
#include "Sacrifice.h"
// #include "MassCure.h"
// #include "MassHeal.h"
#include "DenialMagic.h"
#include "HolyArrow.h"
#include "Illendue.h"
#include "Regeneration.h"
#include "TurnUndead.h"


// ¹ìÇÁ °è¿­
#include "AcidBall.h"
#include "AcidBolt.h"
#include "AcidSwamp.h"
#include "AcidTouch.h"
#include "DarkBluePoison.h"
#include "Doom.h"
#include "GreenPoison.h"
#include "GreenStalker.h"
#include "Paralyze.h"
#include "PoisonousHands.h"
#include "Seduction.h"
#include "YellowPoison.h"
// #include "Blind.h"
#include "BloodyBall.h"
#include "BloodyBreaker.h"
#include "BloodyKnife.h"
#include "BloodyMasterWave.h"
#include "BloodyNail.h"
#include "BloodyWarp.h"
#include "BloodyWave.h"
#include "Death.h"
#include "Mephisto.h"
// #include "BloodyWall.h"
#include "BloodySnake.h"
#include "BloodySpear.h"
#include "BloodyWall.h"
#include "Darkness.h"
#include "Hide.h"
#include "Invisibility.h"
#include "RapidGliding.h"
#include "TransformToBat.h"
#include "TransformToWolf.h"

// #include "SummonWolf.h"
#include "OpenCasket.h"
#include "SummonCasket.h"
// #include "RaisingDead.h"
// #include "SummonServant.h"

#include "AcidStorm.h"
#include "AcidStrike.h"
#include "Armageddon.h"
#include "BloodyMarker.h"
#include "BloodyStorm.h"
#include "BloodyStrike.h"
#include "BloodyTunnel.h"
#include "Extreme.h"
#include "HandsOfWisdom.h"
#include "PoisonStorm.h"
#include "PoisonStrike.h"
#include "Transfusion.h"

// ±âÅ¸
#include "CriticalGround.h"
#include "DuplicateSelf.h"
#include "GroundAttack.h"
#include "Hallucination.h"
#include "MeteorStrike.h"
#include "Peace.h"
#include "Restore.h"
#include "SoulChain.h"
#include "SummonMonsters.h"

// ¼ºÁö½ºÅ³
#include "IllusionOfAvenge.h"
#include "MagicElusion.h"
#include "PoisonMesh.h"
#include "WillOfLife.h"

// ¾Æ¿ì½ºÅÍÁî ½ºÅ³
#include "AcidEruption.h"
#include "BackStab.h"
#include "BeatHead.h"
#include "BlazeBolt.h"
#include "BlazeWalk.h"
#include "BlitzSliding.h"
#include "BloodyZenith.h"
#include "Blunting.h"
#include "BombingStar.h"
#include "BurningSolCharging.h"
#include "BurningSolLaunch.h"
#include "Cannonade.h"
#include "ChainThrowingAxe.h"
#include "ChargingAttack.h"
#include "ChoppingFirewood.h"
#include "ClaymoreExplosion.h"
#include "CreateHolyPotion.h"
#include "CrossGuard.h"
#include "DeleoEfficio.h"
#include "DestructionSpear.h"
#include "DistanceBlitz.h"
#include "DivineGuidance.h"
#include "DivineSpirits.h"
#include "DuckingWallop.h"
#include "EarthsTeeth.h"
#include "EmissionWater.h"
#include "Eternity.h"
#include "Evade.h"
#include "ExplosionWater.h"
#include "FatalSnick.h"
#include "FirePiercing.h"
#include "Flourish.h"
#include "FrozenArmor.h"
#include "GammaChop.h"
#include "Glacier1.h"
#include "Glacier2.h"
#include "GnomesWhisper.h"
#include "GoreGlandFire.h"
#include "GrayDarkness.h"
#include "GreatHeal.h"
#include "GroundBless.h"
#include "HandsOfFire.h"
#include "HandsOfNizie.h"
#include "HeartCatalyst.h"
#include "HellFire.h"
#include "HolyArmor.h"
#include "Howl.h"
#include "IceAuger.h"
#include "IceField.h"
#include "IceHail.h"
#include "IceLance.h"
#include "IceWave.h"
#include "InfinityThunderbolt.h"
#include "InstallTrap.h"
#include "InstallTurret.h"
#include "IntimateGrail.h"
#include "JabbingVein.h"
#include "KasasArrow.h"
#include "LandMineExplosion.h"
#include "LarSlash.h"
#include "Liberty.h"
#include "MagnumSpear.h"
#include "MercyGround.h"
#include "MeteorStorm.h"
#include "MoleShot.h"
#include "MultiThrowingAxe.h"
#include "NooseOfWraith.h"
#include "NymphRecovery.h"
#include "PlasmaRocketLauncher.h"
#include "PlayingWithFire.h"
#include "PleasureExplosion.h"
#include "Prominence.h"
#include "ProtectionFromBlood.h"
#include "ReactiveArmor.h"
#include "Rediance.h"
#include "RefusalEther.h"
#include "ReputoFactum.h"
#include "RingOfFlare.h"
#include "SetAfire.h"
#include "SharpChakram.h"
#include "SharpRound.h"
#include "ShiftBreak.h"
#include "SoulRebirth.h"
#include "SpitStream.h"
#include "StoneAuger.h"
#include "StoneSkin.h"
#include "SummonFireElemental.h"
#include "SummonGoreGland.h"
#include "SummonGroundElemental.h"
#include "SummonWaterElemental.h"
#include "SweepVice.h"
#include "SwordOfThor.h"
#include "TalonOfCrow.h"
#include "Teleport.h"
#include "Tendril.h"
#include "ThrowingAxe.h"
#include "TransformToWerwolf.h"
#include "Trident.h"
#include "TurretFire.h"
#include "ViolentPhantom.h"
#include "WaterBarrier.h"
#include "Whitsuntide.h"
#include "WideIceField.h"
#include "WideIceHail.h"

// ¾Æ¿ì½ºÅÍÁî 140·¹º§ ½ºÅ³
#include "ARAttack.h"
#include "Aberration.h"
#include "BikeCrash.h"
#include "Destinies.h"
#include "DragonTornado.h"
#include "FierceFlame.h"
#include "FuryOfGnome.h"
#include "GrenadeAttack.h"
#include "Halo.h"
#include "HarpoonBomb.h"
#include "IceHorizon.h"
#include "PassingHeal.h"
#include "RottenApple.h"
#include "SMGAttack.h"
#include "SelfDestruction.h"
#include "ShadowOfStorm.h"
#include "SharpHail.h"
#include "SummonMiga.h"
#include "SummonMigaAttack.h"
#include "WildWolf.h"
// add by coffee 2007-2-17
#include "BloodCurse.h"        //ÑªÖ®?Öä
#include "BloodyScarify.h"     //ÑªÖ®ÀÓÓ¡
#include "BombCrashWalk.h"     //¾ÞÅÚºäÕ¨
#include "HeavenGround.h"      //ÌìÉñ½µÁÙ
#include "IllusionInversion.h" //¿Ö²À»Ã¾õ(ÈËÀà·¨Ê¦)
#include "SatelliteBomb.h"     //ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
#include "ShineSword.h"        //ÉÁÒ«Ö®½£
// Ä§Áé
#include "BigRockfall.h"      //395 ADD BY RALLSER
#include "BrambleHalo.h"      //390 ADD BY RALLSER
#include "CutStorm.h"         //387 ADD BY RALLSER
#include "DeadlyClaw.h"       //391ÖÂÉËÁÑ×¦ add by rallser
#include "DummyDrake.h"       // µÂÀ×¿Ë¿þÀÜ(»ð·¨)
#include "FireMeteor.h"       //394 ADD BY RALLSER
#include "HeterChakram.h"     // ÏÄ²¼Àû»ùÒò(ÃôÕ½)
#include "HydroConvergence.h" // ¸´ºÏË®ÁÆ(Ë®·¨)
#include "PenetrateWheel.h"   //393 ADD BY RALLSER
#include "RapidFreeze.h"      //396 ADD BY RALLSER
#include "SacredStamp.h"      //389 ADD BY RALLSER
#include "SkyFire.h"          //386 ÌìÀ×»ð»¨ ADD BY RALLSER
#include "SummonClay.h"       // ÍÁ·¨
#include "VoodooRing.h"       //392 ADD BY RALLSER
#include "XRLMissile.h"       //388 ADD BY RALLSER


// add by coffee 2007-3-1

const int PartyEffectBoost[7] = {
    100, // 0
    100, // 1
    120, // 2
    135, // 3
    140, // 4
    145, // 5
    150  // 6
};

const int PartyDurationBoost[7] = {
    100, // 0
    100, // 1
    130, // 2
    155, // 3
    175, // 4
    190, // 5
    200  // 6
};

//////////////////////////////////////////////////////////////////////////////
// °Ë °è¿­
//////////////////////////////////////////////////////////////////////////////

void DoubleImpact::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 1 + (input.STR / 20) + input.SkillLevel / 20;
    output.Delay = 8; // 1ÃÊ
                      // output.Damage = 2 + input.SkillLevel/33;
    // output.Delay  = 10; // 1ÃÊ
}

void TripleSlasher::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 2 + (input.STR/20) + (input.SkillLevel/15);
    output.Damage = 3 + (input.STR / 20) + (input.SkillLevel / 15);
    output.Delay = 8; // 0.7ÃÊ
                      // output.Damage = 3 + input.SkillLevel/33;
    // output.Delay  = 7; // 0.7ÃÊ
}

void RainbowSlasher::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 4 + input.STR / 15 + input.SkillLevel / 10;
    output.Delay = 8; // 0.8ÃÊ
                      // output.Damage = 7 + input.SkillLevel/33;
    // output.Delay  = 8; // 0.8ÃÊ
}

void ThunderSpark::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 3 + input.STR / 20 + input.SkillLevel / 10;
    output.Delay = 7; // 0.7ÃÊ
                      // output.Damage = 5 + input.SkillLevel/33;
    // output.Delay  = 7; // 0.7ÃÊ
}

void DancingSword::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 1 + (input.DEX / 10) + (input.SkillLevel / 10);
    //	output.Duration = (10 + input.STR/10 + input.SkillLevel/2) * 10;
    output.Duration = (30 + input.STR / 10 + input.SkillLevel / 2) * 10;
    // output.Delay    = (5 - input.SkillLevel/33) * 10; // 5->2ÃÊ
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5

    // output.Damage   = 5 + input.SkillLevel/10;
    // output.Duration = (30 + input.SkillLevel/4) * 10;
    // output.Delay    = (5 - input.SkillLevel/33) * 10; // 5->2ÃÊ
}

void CrossCounter::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.SkillLevel / 2) * 10;
    // output.Delay    = max(5 - input.SkillLevel/20, 2) * 10; // 5->2ÃÊ
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5

    // output.Duration = (30 + input.SkillLevel/4) * 10;
    // output.Delay    = max(5 - input.SkillLevel/20, 2) * 10; // 5->2ÃÊ
}

void FlashSliding::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = max(3 - input.SkillLevel / 50, 1) * 10; // 3->1ÃÊ
    output.Duration = 3 - input.SkillLevel / 50;
    // output.Delay = (3 - input.SkillLevel/50) * 10; // 3->1ÃÊ
}

void LightningHand::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 10 + input.SkillLevel / 10;
    // Å¬¶óÀÌ¾ðÆ®¿ÍÀÇ µ¿±âÈ­ ¹®Á¦·Î µô·¹ÀÌ°¡ ¾ø°Å³ª Á¶±Ý ´õ Âª¾Æ¾ß ÇÑ´Ù.
    output.Delay = 4; // 0.2ÃÊ
                      // output.Damage = 7 + input.SkillLevel/20;
    // output.Delay  = 2; // 0.2ÃÊ
}

void SwordWave::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 5 + input.SkillLevel/33;
    output.Damage = 15 + input.SkillLevel / 20;
    output.Delay = 4; // 1ÃÊ
                      // output.Damage = 5 + input.SkillLevel/33;
    // output.Delay  = 10; // 1ÃÊ
}

void SnakeCombo::computeOutput(const SkillInput& input, SkillOutput& output) {
    // by sigi. 2002.12.3
    output.Damage = 5 + input.STR / 12 + input.SkillLevel / 8;
    output.Delay = 10; // 1ÃÊ
                       // output.Damage = 7 + input.SkillLevel/10;
    // output.Delay  = 10; // 1ÃÊ
}

void WindDivider::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 14 + input.SkillLevel / 20;
    output.Delay = 13; // 1ÃÊ
}

void ThunderBolt::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 10 + input.SkillLevel / 10; // by bezz. 2002.12.10
    output.Delay = (3 - input.SkillLevel / 50) * 10;        // by sigi. 2002.12.3
}

void Expansion::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 10 + input.SkillLevel / 2; // ÀÚ½ÅÀÇ + °ª
    output.ToHit = 5 + input.SkillLevel / 3;   // ÆÄÆ¼ÀÇ + °ª
                                               //	output.Duration = (30 + input.STR/10 + input.SkillLevel*2/3) * 10;
    output.Duration = (45 + input.STR / 10 + input.SkillLevel) * 10;
    // output.Delay    = max(5 - input.SkillLevel/33,2) * 10;
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5

    // output.Damage   = 30 + input.SkillLevel/2; // ÀÚ½ÅÀÇ + °ª
    // output.ToHit    = 15 + input.SkillLevel/4; // ÆÄÆ¼ÀÇ + °ª
    // output.Duration = (30 + input.SkillLevel/3) * 10;
    // output.Delay    = (5 - input.SkillLevel/33) * 10;
}

void MiracleShield::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (5 + input.SkillLevel / 5);         // 5->25
    output.Duration = (30 + input.SkillLevel / 5) * 10; // 30~50ÃÊ
    output.Delay = (5 - input.SkillLevel / 33) * 10;    // 5->2ÃÊ
}

void ThunderFlash::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.SkillLevel / 10;
    output.Delay = 20; // 2ÃÊ
}

void ThunderStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 10 + input.SkillLevel / 10; // by bezz. 2002.12.10
    output.Delay = (3 - input.SkillLevel / 50) * 10;        // 1ÃÊ
                                                            // output.Damage = 10 + input.SkillLevel/5;
    // output.Delay  = (5 - input.SkillLevel/33)*10; // 1ÃÊ
}

void MentalSword::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 30 + (15 * input.SkillLevel / 50);
    output.Range = 2 + input.SkillLevel / 33;
    output.Delay = (8 - input.SkillLevel / 20) * 10; // 5~3ÃÊ
                                                     // output.Damage = 30 + ( 15 * input.SkillLev/50 );
    // output.Range = 2 + input.SkillLevel/20;
    // output.Delay  = (5 - input.SkillLevel / 50)*10; // 5~3ÃÊ
}

//////////////////////////////////////////////////////////////////////////////
// µµ °è¿­
//////////////////////////////////////////////////////////////////////////////

void SingleBlow::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 1 + input.STR / 20 + input.SkillLevel / 20; // by sigi. 2002.12.3
    output.Delay = 7;                                           // 1ÃÊ
}

void SpiralSlay::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 2 + input.STR/20 + input.SkillLevel/15;	// by sigi. 2002.12.3
    output.Damage = 4 + input.STR / 20 + input.SkillLevel / 15;
    output.Delay = 7; // 0.7ÃÊ
}

void TripleBreak::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 3 + input.STR / 20 + input.SkillLevel / 10; // by sigi. 2002.12.3
    output.Delay = 7;                                           // 0.7ÃÊ
}

void WildSmash::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 4 + input.STR / 15 + input.SkillLevel / 10; // by sigi. 2002.12.3
    output.Delay = 8;                                           // 0.8ÃÊ
}

void GhostBlade::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.SkillLevel / 10;
    // output.Duration = (30 + input.SkillLevel/4) * 10;
    // output.Duration = (10 + input.STR/10 + input.SkillLevel/2) * 10;
    output.Duration = (30 + input.STR / 10 + input.SkillLevel / 2) * 10;
    // output.Delay    = (5 - input.SkillLevel/33) * 10; // 5->2ÃÊ
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void PotentialExplosion::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 1 + input.SkillLevel / 15;
    //	output.Duration = (10 + input.SkillLevel/2) * 10;
    output.Duration = (30 + input.SkillLevel / 2) * 10;
    // output.Delay    = (7 - input.SkillLevel/20) * 10; // 7->2ÃÊ
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void ShadowWalk::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Range = max(2 + input.SkillLevel / 25, 2);
    output.Delay = (3 - input.SkillLevel / 50) * 10; // 3->1ÃÊ
}

void ChargingPower::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + (input.SkillLevel / 20) + (input.DomainLevel / 30);
    output.Duration = (60 + input.SkillLevel * 3 / 2) * 10;
    //	output.Duration = (30 + input.STR/10 + input.SkillLevel*10/12) * 10;
    // 	output.Damage   = 1 + (input.STR + input.SkillLevel)/20;
    //	output.Duration = (10 + input.SkillLevel/2) * 10;
    // output.Delay    = (5 - input.SkillLevel/33) * 10; // 5->2ÃÊ
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void HurricaneCombo::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.STR / 12 + input.SkillLevel / 8;
    output.Delay = 10; // 1ÃÊ
}

void TornadoSever::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 8 + input.STR/15 + input.SkillLevel/10;
    //	output.Damage = 3 + input.STR/20 + input.SkillLevel/10;
    output.Damage = 10 + input.STR / 20 + input.SkillLevel / 8;
    //	output.Delay  = 20 - (input.SkillLevel/100); // 2ÃÊ
    output.Delay = 4;
}

void Earthquake::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.STR / 20 + input.SkillLevel / 10; // by sigi. 2002.12.3
    output.Range = 7;                                           // by bezz. 2002.12.10
    output.Delay = 13;                                          // 1.3ÃÊ by bezz. 2002.12.10
}

void Berserker::computeOutput(const SkillInput& input, SkillOutput& output) {
    // penalty°ªÀº Berserker.cpp¿¡ ÀÖ´Ù.
    // output.Damage    = (input.STR/20) * (1 + input.SkillLevel/20); //  µ¥¹ÌÁö º¸³Ê½º
    // output.ToHit    = (input.DEX/10) * (1 + input.SkillLevel/10); //  ÅõÈý º¸³Ê½º

    // 2002.12.06 ÀåÈ«Ã¢
    output.Damage = (input.STR / 20) * (1 + input.SkillLevel / 25); //  µ¥¹ÌÁö º¸³Ê½º
    //	output.ToHit    = (input.DEX/10) * (1 + input.SkillLevel/12); //  ÅõÈý º¸³Ê½º
    output.ToHit = 10 + (1 + input.SkillLevel / 12); //  ÅõÈý º¸³Ê½º

    //	output.Duration = (30 + input.SkillLevel/5) * 10;
    output.Duration = (45 + input.SkillLevel / 1.5) * 10;
    // output.Delay    = max(5 - input.SkillLevel/33,2) * 10;
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void MoonlightSever::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage   = 8 + input.STR/10 + input.SkillLevel/10;
    output.Damage = 15 + input.STR / 10 + input.SkillLevel / 8;
    //	output.Delay    = 8; // 0.8ÃÊ
    output.Delay = 4; // 0.4ÃÊ
}

void ShadowDancing::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 30 + ( 15 * input.SkillLevel/50 );
    output.Damage = 30 + (15 * input.SkillLevel / 25);
    output.ToHit = 10 + input.SkillLevel / 20; // Å©¸®Æ¼ÄÃ È®·ü Áõ°¡Ä¡
    // output.Delay    = (5 - input.SkillLevel / 50)*10; // 2ÃÊ¸¦ ¼¼¹øÀ¸·Î ³ª´©¸é 0.66666 = 0.7ÃÊ
    output.Delay = (8 - input.SkillLevel / 20) * 10; // by sigi. 2002.12.3
}

void Typhoon::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 10 + input.SkillLevel / 5;
    // output.Duration = 10; // 1ÃÊ (Å¸°ÙÀÌ »æ»æ µ¹¾Æ°¡´Â ½Ã°£) - effect¾ø´Ù -_-;
    // output.Delay    = 15; // 1.5ÃÊ
    output.Duration = (1 + input.SkillLevel / 100) * 10; // 1ÃÊ (Å¸°ÙÀÌ »æ»æ µ¹¾Æ°¡´Â ½Ã°£) - effect¾ø´Ù -_-;
    output.Delay = (3 - input.SkillLevel / 50) * 10;     // by bezz. 2002.12.10
}

//////////////////////////////////////////////////////////////////////////////
// ÃÑ °è¿­
//////////////////////////////////////////////////////////////////////////////

void QuickFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.ToHit  = -20 + (input.DEX/10) + input.SkillLevel/5;
    // output.Damage = -50 + input.STR/10 + input.SkillLevel/3;
    output.ToHit = -30 + input.DEX / 20 + input.SkillLevel / 5;
    output.Damage = -30 + input.STR / 20 + input.SkillLevel / 5;
    output.Delay = 2;
}

void DoubleShot::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.ToHit = -20 + input.SkillLevel / 5;
    output.Damage = -50 + input.SkillLevel / 3;
    output.Delay = 2;
}

void TripleShot::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.ToHit = -20 + input.SkillLevel / 5;
    output.Damage = -50 + input.SkillLevel / 3;
    output.Delay = 2;
}

void MultiShot::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.IClass == Item::ITEM_CLASS_SG) {
        //		output.Damage = 3 + input.SkillLevel/10;
        output.Damage = 8 + input.SkillLevel / 10;
    }

    else if (input.IClass == Item::ITEM_CLASS_AR || input.IClass == Item::ITEM_CLASS_SMG) {
        //		output.Damage = 1 + input.SkillLevel/30;
        output.Damage = 5 + input.SkillLevel / 15;
    }

    else if (input.IClass == Item::ITEM_CLASS_SR) {
        //		output.Damage = input.SkillLevel/50;
        output.Damage = 3 + input.SkillLevel / 20;
    }

    output.ToHit = -20 + input.SkillLevel / 5;
    output.Delay = 8; // 0.8ÃÊ
}

void HeadShot::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 0;

    // SkillUtil.cppÀÇ computeArmsWeaponDamageBonus()¿¡¼­ °è»êµÇ¹Ç·Î.. Áßº¹ µ¥¹ÌÁö´Ù. - -; by sigi. 2002.12.3
    if (input.IClass == Item::ITEM_CLASS_SG) {
        switch (input.Range) {
        case 3:
            output.Damage = 5;
        case 2:
            output.Damage = 8;
        case 1:
            output.Damage = 10;
        default:
            break;
        }
    } else if (input.IClass == Item::ITEM_CLASS_AR || input.IClass == Item::ITEM_CLASS_SMG) {
        switch (input.Range) {
        case 3:
            output.Damage = 5;
        case 2:
            output.Damage = 6;
        case 1:
            output.Damage = 8;
        default:
            break;
        }
    } else if (input.IClass == Item::ITEM_CLASS_SR) {
        switch (input.Range) {
        case 3:
            output.Damage = 3;
        case 2:
            output.Damage = 6;
        case 1:
            output.Damage = 8;
        default:
            break;
        }
    } else {
        Assert(false);
    }

    output.Delay = 8; // 0.8ÃÊ
}

void Piercing::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.ToHit = 0;
    output.Damage = 2;
    output.Delay = 8; // 0.8ÃÊ
}

void Sniping::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (30 + input.SkillLevel / 5) * 10;
    output.Delay = (10 - input.SkillLevel / 20) * 10; // 10->5ÃÊ
}

void MindControl::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 15 + input.SkillLevel / 10;
    output.Duration = (30 + input.SkillLevel / 5) * 10;
    output.Delay = 30; // 3ÃÊ
}

void Revealer::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (30 + input.SkillLevel / 5) * 10; // 30~50ÃÊ
    output.Delay = output.Duration;
    //	output.Delay    = (5 - input.SkillLevel/33) * 10; // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void CreateBomb::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 15 + input.SkillLevel / 10;
    output.Duration = (30 + input.SkillLevel / 5) * 10;
    output.Delay = 30 - input.SkillLevel / 10; // 3ÃÊ ~ 2ÃÊ
}

void CreateMine::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 15 + input.SkillLevel / 10;
    output.Duration = (30 + input.SkillLevel / 5) * 10;
    output.Delay = 30 - input.SkillLevel / 10; // 3ÃÊ ~ 2ÃÊ
}

void InstallMine::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 15 + input.SkillLevel / 10;
    output.Duration = (30 + input.SkillLevel / 5) * 10;
    //	output.Delay    = 30 - input.SkillLevel / 10; // 3ÃÊ ~ 2ÃÊ
    output.Delay = 90 - input.SkillLevel / 2.5; // 9ÃÊ ~ 5ÃÊ
}

void DisarmMine::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 15 + input.SkillLevel / 10;
    output.Duration = (30 + input.SkillLevel / 5) * 10;
    output.Delay = 30; // 3ÃÊ
}

void ObservingEye::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = (10 + input.SkillLevel/5)*10;
    output.Duration = (30 + input.SkillLevel / 3) * 10;
    // damage°ªÀº visionÀ¸·Î ³Ö°í
    // ´Ù¸¥ °ªÀ» Àû´çÈ÷ °è»êÇØ¼­ ¾´´Ù. -_-;
    output.Damage = 1 + input.SkillLevel / 50;
    // output.Delay  = (5 - input.DEX/50) * 10; // 20ÃÊ
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

//////////////////////////////////////////////////////////////////////////////
// ÀÎÃ¦Æ® °è¿­
//////////////////////////////////////////////////////////////////////////////

void CreateHolyWater::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (5 - input.SkillLevel / 33) * 10; // 5->2ÃÊ
}

void Light::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (60 + input.SkillLevel / 20 * 60) * 10; // 60~360ÃÊ
    output.Delay = (5 - input.SkillLevel / 33) * 10;          // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void DetectHidden::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.SkillLevel / 2) * 10; // 30~50ÃÊ
    output.Delay = (5 - input.INTE / 50) * 10;          // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void AuraBall::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 5 + (input.INTE/20) + input.SkillLevel/5;
    //	output.Damage = 10 + (input.INTE/10) + input.SkillLevel/5;
    output.Damage = 16 + (input.INTE / 10) + input.SkillLevel / 4;
    output.Delay = 10; // 1ÃÊ
    //	output.Range = 2 + (input.SkillLevel/25); // ¾²Áöµµ ¾Ê´Â °ª ¿Ö ³Ö¾î³ùÀ»±î.. 8/18

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

void Bless::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_SELF) {
        //		output.Damage   = input.INTE/20 + input.SkillLevel/20;
        output.Damage = 4 + input.INTE / 40 + input.SkillLevel / 20;
    } else {
        //		output.Damage   = input.INTE/20 + input.SkillLevel/20;
        output.Damage = 2 + input.INTE / 40 + input.SkillLevel / 20;
    }

    output.Duration = (30 + input.SkillLevel * 3 / 2) * 10; // 30~50ÃÊ
    output.Delay = (7 - input.SkillLevel / 20) * 10;        // 6->3ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void ContinualLight::computeOutput(const SkillInput& input, SkillOutput& output) {
    switch (g_pSkillInfoManager->getGradeByDomainLevel(input.DomainLevel)) {
    case SKILL_GRADE_APPRENTICE:
        output.Range = 1;
        break;
    case SKILL_GRADE_ADEPT:
        output.Range = 3;
        break;
    case SKILL_GRADE_EXPERT:
        output.Range = 4;
        break;
    case SKILL_GRADE_MASTER:
        output.Range = 5;
        break;
    case SKILL_GRADE_GRAND_MASTER:
        output.Range = 6;
        break;
    default:
        output.Range = 0;
        break;
    }

    output.Delay = (6 - input.SkillLevel / 25) * 10; // 5->2ÃÊ
    output.Duration = (10 + input.SkillLevel / 2) * 10;
}

void Flare::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (5 + input.SkillLevel / 5) * 10; // 10~20ÃÊ
    output.Delay = (6 - input.SkillLevel / 33) * 10;   // 6->3ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void Purify::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 10 + input.SkillLevel / 10;
    output.Delay = (5 - input.SkillLevel / 33) * 10; // 5->2ÃÊ

    switch (g_pSkillInfoManager->getGradeByDomainLevel(input.DomainLevel)) {
    case SKILL_GRADE_APPRENTICE:
        output.Range = 3;
        break;
    case SKILL_GRADE_ADEPT:
        output.Range = 3;
        break;
    case SKILL_GRADE_EXPERT:
        output.Range = 5;
        break;
    case SKILL_GRADE_MASTER:
        output.Range = 5;
        break;
    case SKILL_GRADE_GRAND_MASTER:
        output.Range = 7;
        break;
    default:
        output.Range = 0;
        break;
    }

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

void AuraRing::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 5 + input.INTE/10 + input.SkillLevel/3; // by bezz. 2002.12.10
    output.Damage = 15 + input.INTE / 10 + input.SkillLevel / 3; // by bezz. 2002.12.10
    output.Delay = max(1, 2 - (input.SkillLevel / 50)) * 10;     // by bezz. 2002.12.10

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

void Striking::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        //		output.Damage = input.INTE/33 + input.SkillLevel/20;
        output.Damage = input.INTE / 30 + input.SkillLevel / 20;
    } else {
        //		output.Damage = input.INTE/20 + input.SkillLevel/10;
        output.Damage = input.INTE / 30 + input.SkillLevel / 10;
    }

    output.Duration = (30 + input.SkillLevel * 3 / 2) * 10;
    //	output.Duration = (30 + input.SkillLevel * 2 / 3) * 10;
    output.Delay = (6 - input.SkillLevel / 33) * 10; // 6->3ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void DetectInvisibility::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.SkillLevel / 2) * 10; // 30~50ÃÊ
    output.Delay = (6 - input.SkillLevel / 33) * 10;    // 6->3ÃÊ

    switch (g_pSkillInfoManager->getGradeByDomainLevel(input.DomainLevel)) {
    case SKILL_GRADE_APPRENTICE:
        output.Range = 3;
        break;
    case SKILL_GRADE_ADEPT:
        output.Range = 3;
        break;
    case SKILL_GRADE_EXPERT:
        output.Range = 5;
        break;
    case SKILL_GRADE_MASTER:
        output.Range = 5;
        break;
    case SKILL_GRADE_GRAND_MASTER:
        output.Range = 7;
        break;
    default:
        output.Range = 0;
        break;
    }

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void AuraShield::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.SkillLevel / 3) * 10; // 15~35ÃÊ
    // output.Delay    = (5 - input.SkillLevel/33) * 10; // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void Visible::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (5 - input.SkillLevel / 50) * 10; // 5->3ÃÊ
    output.Range = 3 + (input.SkillLevel / 50);

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

//////////////////////////////////////////////////////////////////////////////
// Èú¸µ °è¿­
//////////////////////////////////////////////////////////////////////////////

void CureLightWounds::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        output.Damage = 10 + input.SkillLevel / 8;
    } else {
        output.Damage = 10 + input.SkillLevel / 4;
    }

    output.Delay = 10; // 1ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void CureAll::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        output.Damage = 50 + input.SkillLevel / 4;
    } else {
        output.Damage = 35 + input.SkillLevel / 2;
    }

    output.Delay = 40 - input.SkillLevel / 5; // 4ÃÊ~ 2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void CurePoison::computeOutput(const SkillInput& input, SkillOutput& output) {
    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);

    output.Delay = (4 - input.SkillLevel / 33) * 10; // 4->1ÃÊ
}

void ProtectionFromPoison::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        // output.Damage = 10 + input.SkillLevel/10;
        output.Damage = min(20, 10 + input.INTE / 20);
    } else {
        // output.Damage = 20 + input.SkillLevel/10;
        output.Damage = min(30, 20 + input.INTE / 20);
    }

    // output.Duration = (30 + input.SkillLevel/2) * 10; // 30~80ÃÊ
    //	output.Duration = (50 + input.INTE * 2 / 3) * 10; // 30~80ÃÊ// by sigi. 2002.12.3
    output.Duration = (60 + input.INTE / 2 + input.SkillLevel / 2) * 10; //
    output.Delay = (5 - input.SkillLevel / 33) * 10;                     // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void CauseLightWounds::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage = 10 + input.SkillLevel/10;
    // output.Damage = 5 + input.INTE/10 + input.SkillLevel/10;	// by sigi. 2002.12.3
    output.Damage = 10 + input.INTE / 10 + input.SkillLevel / 10; // by sigi. 2002.12.3
    output.Delay = 10;                                            // 1ÃÊ

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

void CureSeriousWounds::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        output.Damage = 30 + input.SkillLevel / 8;
    } else {
        output.Damage = 30 + input.SkillLevel / 4;
    }

    output.Delay = 10; // 1ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void RemoveCurse::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (5 - input.SkillLevel / 33) * 10; // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void ProtectionFromCurse::computeOutput(const SkillInput& input, SkillOutput& output) {
    // by sigi. 2002.12.3
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        // output.Damage = 10 + input.SkillLevel/10;
        output.Damage = min(20, 10 + input.INTE / 20);
    } else {
        // output.Damage = 20 + input.SkillLevel/10;
        output.Damage = max(30, 20 + input.INTE / 20);
    }

    // output.Duration = (25 + input.SkillLevel/2) * 10; // 25~75ÃÊ
    // output.Duration = (40 + input.INTE*2/3) * 10; // 25~75ÃÊ	// by sigi. 2002.12.3
    output.Duration = (60 + input.SkillLevel / 2 + input.INTE / 2) * 10; // 25~75ÃÊ	// by sigi. 2002.12.3
    output.Delay = (5 - input.SkillLevel / 33) * 10;                     // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void Resurrect::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 20; // 2ÃÊ
}

void CauseSeriousWounds::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage = 30 + input.SkillLevel/4;
    //  by sigi. 2002.12.3
    // output.Damage = 5 + input.INTE/8 + input.SkillLevel/5;
    output.Damage = 15 + input.INTE / 8 + input.SkillLevel / 5;
    output.Delay = 10; // 1ÃÊ

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

void CureCriticalWounds::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        output.Damage = 10 + input.SkillLevel / 10;
    } else {
        output.Damage = 10 + input.SkillLevel / 20;
    }

    output.Delay = (40 - input.SkillLevel / 5) * 10; // 40ÃÊ~20ÃÊ

    output.Duration = (20 + input.SkillLevel / 5) * 10; // 20ÃÊ~40ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void ProtectionFromAcid::computeOutput(const SkillInput& input, SkillOutput& output) {
    // by sigi. 2002.12.3
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        // output.Damage = 10 + input.SkillLevel/10;
        output.Damage = min(20, 10 + input.INTE / 20);
    } else {
        // output.Damage = 20 + input.SkillLevel/10;
        output.Damage = min(30, 20 + input.INTE / 20);
    }

    // output.Duration = (20 + input.SkillLevel/2) * 10; // 20~70ÃÊ
    // output.Duration = (40 + input.INTE*2/3) * 10; // 20~70ÃÊ
    output.Duration = (60 + input.SkillLevel / 2 + input.INTE / 2) * 10; // 20~70ÃÊ
    output.Delay = (5 - input.SkillLevel / 33) * 10;                     // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void Sacrifice::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (30 + input.SkillLevel / 5) * 10; // 30~50ÃÊ
    output.Delay = (5 - input.SkillLevel / 33) * 10;    // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Damage   = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void CauseCriticalWounds::computeOutput(const SkillInput& input, SkillOutput& output) {
    /*
    output.Damage = 20 + input.SkillLevel/6;
    output.Delay  = 10; // 1ÃÊ
    */

    // output.Damage = 3 + input.SkillLevel / 10; // 3-13
    //  by sigi. 2002.12.3
    output.Damage = 5 + input.INTE / 10 + input.SkillLevel / 5; // 3-13
    output.Delay = (10 - input.SkillLevel / 33) * 10;           // 10-7ÃÊ
    output.Duration = (3 + input.SkillLevel / 50) * 10;         // 3-5ÃÊ

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

/*
void CureAll::computeOutput(const SkillInput& input, SkillOutput& output)
{
    output.Delay = (4 - input.SkillLevel/33) * 10; // 4->1ÃÊ
}
*/

void RegenerationSkill::computeOutput(const SkillInput& input, SkillOutput& output) {}

void EnergyDrop::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage = 25 + input.SkillLevel/5; // 20 ~ 45
    // output.Delay = 30; // 3ÃÊ
    // output.Damage = 10 + input.INTE/10 + input.SkillLevel/5; // 20 ~ 45 12.06

    // 2002.12.06 ÀåÈ«Ã¢
    //	output.Damage = 10 + input.INTE/10 + input.SkillLevel/3;
    output.Damage = 18 + input.INTE / 10 + input.SkillLevel / 2.5;
    //	output.Delay = (8 - input.SkillLevel/20)*10;
    output.Delay = (5 - input.SkillLevel / 33) * 10;
}

void VigorDrop::computeOutput(const SkillInput& input, SkillOutput& output) {
    // by sigi. 2002.12.3
    // output.Damage = 25 + input.SkillLevel/5; // 20 ~ 45
    // output.Delay = 30; // 3ÃÊ
    // output.Damage = 10 + input.INTE/10 + input.SkillLevel/5; // 20 ~ 45 2002.12.06

    // 2002.12.06 ÀåÈ«Ã¢
    //	output.Damage = 10 + input.INTE/10 + input.SkillLevel/3;
    output.Damage = 18 + input.INTE / 10 + input.SkillLevel / 3;
    //	output.Delay = (8 - input.SkillLevel/20)*10;
    output.Delay = (5 - input.SkillLevel / 33) * 10;
}

void Activation::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 0;

    output.Duration = (40 + input.SkillLevel / 5) * 10;
    output.Delay = (6 - input.SkillLevel / 50) * 10;

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = 0;
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void HolyBlast::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 15 + input.SkillLevel / 8;
    output.Delay = (8 - input.SkillLevel / 33) * 10;
    output.Duration = 10;
}

void Sanctuary::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 0;
    output.Delay = 5 - input.SkillLevel / 50;
    output.Duration = (5 + input.SkillLevel / 20) * 10;
}

void Reflection::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 0;
    // output.Delay = 5 - input.SkillLevel/33;
    output.Duration = (20 + input.SkillLevel / 5) * 10;
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void Hymn::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 10 + input.SkillLevel / 10;
    output.Duration = (20 + input.SkillLevel / 2) * 10;
    output.Delay = 7 - input.SkillLevel / 20;
}

//////////////////////////////////////////////////////////////////////////////
// ¹ìÆÄÀÌ¾î °è¿­
//////////////////////////////////////////////////////////////////////////////

void PoisonousHands::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(20, 3 + (input.INTE - 20) / 3);
    output.Delay = 6; // 0.6ÃÊ
}

void AcidTouch::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 6 + input.INTE / 15;
    output.Delay = 6; // 0.6ÃÊ
}

void GreenPoison::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(15, 5 + (input.INTE - 20) / 10);
    output.Duration = min(20, 10 + (input.INTE - 20) / 10) * 10;
    output.Delay = max(2, 5 - (input.INTE - 20) / 50) * 10; // 5->2ÃÊ
}

void Darkness::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.INTE / 6) * 10;
    output.Delay = max(2, 10 - input.DEX / 30) * 10;
    output.Range = (3 + (input.SkillLevel - 15) / 25);
}

void YellowPoison::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = input.INTE / 4 * 10;
    output.Delay = max(2, 10 - input.DEX / 30) * 10;
}

void TransformToBat::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 30;
}

void SummonCasket::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 10;
}

void OpenCasket::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 30;
}

void AcidBolt::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(40, input.STR / 20 + input.INTE / 5);
    output.Delay = max(1, 3 - (input.DEX / 50) - (input.INTE / 50)) * 10; // by bezz. 2002.12.10
}

void GreenStalker::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 20 + input.INTE / 10;
    output.Tick = 40;
    output.Duration = (input.DEX / 5 + input.INTE / 5) * 10; // by sigi. 2002.12.3
    output.Delay = max(1, 5 - input.DEX / 40) * 10;
}

void BloodyTunnel::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 30;
}

void Paralyze::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(40, 25 + (input.INTE - 20) / 20);
    output.Duration = (3 + input.INTE / 15) * 10;
    output.Delay = max(3, (6 - input.DEX / 50)) * 10;
}

void BloodyMarker::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 30;
}

void DarkBluePoison::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(20, 5 + (input.INTE - 20) / 10);
    output.Duration = min(45, 21 + (input.INTE - 20) / 5) * 10;
    output.Tick = 30;
    output.Delay = max(3, 5 - (input.INTE - 20) / 10) * 10;
}

void TransformToWolf::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 30;
}

void Doom::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(30, 20 + (input.INTE - 20) / 20);
    //	output.Duration = min(80, 30 + (input.INTE-20)/3) * 10;
    output.Duration = min(30, 10 + (input.INTE - 20) / 10) * 10;
    output.Delay = max(3, 5 - (input.INTE - 20) / 10) * 10;
}

void AcidBall::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 15 + input.INTE / 5;                  // by bezz. 2002.12.10
    output.Delay = max(1, 3 - input.DEX / 50 - input.INTE / 50) * 10; // by bezz. 2002.12.10
}

void Invisibility::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 30;
}

void AcidSwamp::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 15 + input.INTE / 4;
    output.Duration = max(40, ((input.DEX - 40 + input.INTE - 40) / 6) * 10);
    output.Tick = 15;
    output.Delay = max(2, 6 - input.DEX / 40) * 10;
}

void Seduction::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(30, 10 + (input.INTE - 20) / 10);
    output.Duration = min(50, 20 + (input.INTE - 20) / 5) * 10;
    output.Delay = max(3, 5 - (input.INTE - 20) / 10) * 10;
}

void BloodyNail::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 8 + input.DEX / 10 + input.INTE / 30;
    output.Delay = 6; // 0.6ÃÊ
}

void BloodyKnife::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 10 + input.INTE / 5 + input.DEX / 10;
    output.Delay = max(2, 6 - (input.DEX / 50) - (input.INTE / 50)); // by bezz. 2002.12.10
}

void BloodyBall::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 8 + input.INTE / 4 + input.DEX / 8;
    output.Delay = 30;
}

void BloodyWave::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.INTE / 6 + input.STR / 7 + input.DEX / 7;
    output.Delay = max(1, 3 - input.DEX / 50) * 10;
    // ToHit´Â bKnockbackÀ¸·Î ¾²ÀÎ´Ù.
    output.ToHit = 50; // min(35, 10 + (int)(input.INTE/10));
}

void BloodyMasterWave::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(80, 40 + (input.INTE - 20) / 4);
    output.Delay = 30;
    // ToHit´Â bKnockbackÀ¸·Î ¾²ÀÎ´Ù.
    output.ToHit = min(55, 30 + (int)(input.INTE / 10));
}

void BloodyWarp::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(70, 30 + (input.INTE - 20) / 4);
    output.Delay = 30;
    // ToHit´Â bKnockbackÀ¸·Î ¾²ÀÎ´Ù.
    output.ToHit = min(35, 10 + (int)(input.INTE / 10));
}

void BloodyWall::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.INTE / 5 + input.STR / 10;
    output.Duration = (input.DEX / 15 + input.INTE / 10) * 10;
    output.Delay = max(2, 5 - input.DEX / 50) * 10;
    output.Tick = 10;
}

void BloodySnake::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(35, 10 + (input.INTE - 20) / 9);
    output.Duration = (1 + (input.INTE - 20) / 80) * 10;
    output.Delay = max(3, 6 - (input.INTE - 20) / 50) * 10;
    output.Tick = 3;
}


void BloodySpear::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(180, input.STR / 6 + input.INTE / 2 + input.DEX / 12);
    output.Delay = max(2, 6 - input.DEX / 50) * 10;
}

void PoisonStrike::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(65, input.STR / 10 + input.INTE * 2 / 9);
    output.Delay = max(1, 5 - input.DEX / 50) * 10;
}

void AcidStrike::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(75, input.STR / 8 + input.INTE / 4);
    output.Delay = max(1, 5 - input.DEX / 50) * 10;
}

void BloodyStrike::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(90, input.STR / 8 + input.INTE * 10 / 23);
    output.Delay = max(2, 6 - input.DEX / 50) * 10;
}

void PoisonStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage = input.STR/30 + input.INTE/9; 12.6

    // 2002.12.06 ÀåÈ«Ã¢
    output.Damage = input.STR / 30 + input.INTE / 4;

    // 2003.3.20 Sequoia µô·¹ÀÌ ¹Ì´Ï¸Ø ³Ö¾ú´Ù.
    output.Delay = max((8 - input.DEX / 50) * 10, 20);
    output.Range = min(6, 3 + (input.SkillLevel - 40) / 8);
}

void AcidStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage = input.STR/28 + input.INTE/8;  12.6

    // 2002.12.06 ÀåÈ«Ã¢
    output.Damage = input.STR / 25 + input.INTE * 2 / 7;

    // 2003.3.20 Sequoia µô·¹ÀÌ ¹Ì´Ï¸Ø ³Ö¾ú´Ù.
    output.Delay = max((9 - input.DEX / 50) * 10, 20);
}

void BloodyStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 25 + input.INTE / 6;
    output.Duration = (input.DEX / 100 + input.INTE / 100) * 10;

    // 2003.3.20 Sequoia µô·¹ÀÌ ¹Ì´Ï¸Ø ³Ö¾ú´Ù.
    output.Delay = max((9 - input.DEX / 50) * 10, 20);
}

void Extreme::computeOutput(const SkillInput& input, SkillOutput& output) {
    // µ¥¹ÌÁö º¸³Ê½º´Â ¿©±â¼­ °è»êÇÏÁö ¾Ê°í,
    // Vampire::initAllStat()¿¡¼­ °è»êÇÑ´Ù.
    output.Damage = 0;
    //	output.Duration = (30 + (input.INTE-20)/6) * 10;  // 30 -> 80
    output.Duration = (60 + input.STR / 15 + input.DEX / 6 + input.INTE / 20) * 10; // 30 -> 80
    output.Delay = (6 - input.STR / 70) * 10;                                       // 5 -> 2
}

void CriticalGround::computeOutput(const SkillInput& input, SkillOutput& output) {
    // acid bolt¶û ¶È°°´ç - -;
    // output.Damage = min(40, 20 + (input.INTE-20)/6);
    // output.Delay  = 10; // 1ÃÊ

    // 20
    // 145 --> 145~290 --> 22~46
    // 500 --> 500~1000 --> 125~250 (±âÈ¹140~280)

    int divider = 1;
    if (input.STR < 200) {
        divider = 6;
    } else {
        divider = 4;
    }

    output.Damage = max(20, (input.STR + rand() % input.STR) / divider);
    output.Delay = 10; // 0.6ÃÊ

    // °ø°Ý°è ±â¼ú¿¡´Â ÆÄÆ¼ º¸³Ê½º°¡ Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
}

void Peace::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = (15 + input.INTE / 10)*10;
    output.Duration = (10 + input.INTE / 40 + input.SkillLevel / 20) * 10;
    output.Delay = max(10 - input.INTE / 20, 5) * 10;
}

void Death::computeOutput(const SkillInput& input, SkillOutput& output) {
    // 2003.3.20 by Sequoia ÃÖ´ë°ªÀÌ Ãß°¡µÇ¾ú´Ù.
    //	output.Damage   = min( input.INTE*10/25 + input.STR/6, 150 );
    output.Damage = min(input.INTE / 5 + input.STR / 12, 80);
    output.Duration = (input.INTE / 5) * 10;
    output.Delay = max(2, 5 - input.DEX / 50) * 10;
}

void Mephisto::computeOutput(const SkillInput& input, SkillOutput& output) {
    // ÀÌ ±â¼ú¸¸ Æ¯º°È÷.. parameter¸¦ ´ÙÀ½°ú °°ÀÌ ³Ñ°ÜÁØ´Ù.
    // input.SkillLevel = pVampire->getSTR()+pVampire->getDEX()+pVampire->getINT();
    // input.DomainLevel = pVampire->getLevel();

    // output.Damage   = 10 + (input.SkillLevel-60)/15;
    // output.Duration = (25 + (input.DomainLevel/4))*10;

    // by sigi. 2002.12.3
    output.Damage = 10 + (input.STR + input.DEX + input.INTE) / 30;
    output.Duration = max(10, (input.DomainLevel - 95) * 10) * 10;
    output.Delay = max(2, 5 - (input.INTE - 20) / 10) * 10;
}

void Transfusion::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage   = min(60, 15 + (input.INTE-20)/5);
    // output.Duration = (10 + (input.INTE-20)/10) * 10;
    // output.Delay    = 5;//max(3, 6 - (input.INTE-20)/50) * 10;
    output.Delay = max(3, 6 - (input.INTE - 20) / 50) * 10;
}

void SummonMonsters::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 0;
    output.Delay = 20; // 2ÃÊ
}

void GroundAttack::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(100, 30 + (input.INTE - 20) / 5); // % damage
    output.Duration = 20;                                 // ¸î ÃÊÈÄ Æø¹ß
    output.Tick = 15;
    output.Delay = max(3, 6 - (input.INTE - 20) / 50) * 10;
}

void MeteorStrike::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage =
        (int)(input.SkillLevel * 0.8 + (rand() % (int)(input.SkillLevel * 0.4 + 1))) + (input.STR + input.DEX) / 6;
    output.Duration = 10; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 10;
}

void Hallucination::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage   = min(20, 10 + (input.INTE-20)/20);
    // output.Duration = min(80, 30 + (input.INTE-20)/3) * 10;
    output.Duration = (20 + (input.STR / 65) + (input.DEX / 85) + (input.INTE / 40)) * 10;
    // output.Delay    = max(3, 5 - (input.INTE-20)/10) * 10;
    // output.Delay	= ( 10 - (input.DEX/50) ) * 10;
    output.Delay = output.Duration;
}

void DuplicateSelf::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min((3 + rand() % 5), input.INTE / 100); // ºÐ½Å °³¼ö
    output.Duration = min(80, 30 + (input.INTE - 20) / 3) * 10;
    output.Delay = max(3, 5 - (input.INTE - 20) / 10) * 10;
}

void SoulChain::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 100;
    output.Delay = 1200;
}

void SharpShield::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + (input.SkillLevel / 2)) * 10;
    output.Damage = (input.STR / 20) + (input.SkillLevel / 20);
    // output.Delay    = ( 5 - ( input.SkillLevel / 25 ) ) * 10;
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void WideLightning::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 10;
    output.Damage = (input.STR / 8) + (input.SkillLevel / 3);
    output.Duration = 6; // 0.6ÃÊ
    output.Tick = 6;     // 0.6ÃÊ
}

void GunShotGuidance::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 50 + input.SkillLevel / 2;
    output.Duration = 10;
    output.Delay = 10;
    output.Range = 8;
}

void AirShield::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage	= 50 + ( input.SkillLevel >> 1 ); 			// 50 + SkillLevel / 2
    output.Damage = 50 + (input.SkillLevel / 5);           // 50 + SkillLevel / 2
    output.Duration = (10 + (input.SkillLevel >> 1)) * 10; // 10 + SkillLevel / 2 (ÃÊ)
    // output.Delay	= ( 5 - ( input.SkillLevel / 25 ) ) * 10;
    output.Delay = output.Duration; // Delay ¿Í Duration ÀÌ °°´Ù. by bezz 2003.3.5
}

void BulletOfLight::computeOutput(const SkillInput& input, SkillOutput& output) {
    /*	switch( input.IClass )
        {
            case Item::ITEM_CLASS_SMG:
                output.Damage = 2 + ( input.SkillLevel / 10 );
                break;
            case Item::ITEM_CLASS_SG:
                output.Damage = 3 + ( input.SkillLevel / 8 );
                break;
            case Item::ITEM_CLASS_AR:
                output.Damage = 4 + ( input.SkillLevel / 6 );
                break;
            case Item::ITEM_CLASS_SR:
                output.Damage = 5 + ( input.SkillLevel / 5 );
                break;
            default:
                output.Damage = 0;
                break;
        }*/
    output.Damage = -20 + (input.SkillLevel * 2 / 3); // / 1.5 );
    output.ToHit = -10 + (input.SkillLevel / 2);      // / 1.5 );
    output.Delay = 2;                                 // 0.2ÃÊ
}

void HandsOfWisdom::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 15 + input.INTE / 8;
    output.Delay = 6; // 0.6ÃÊ
}

void LightBall::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 2 + (input.INTE/20) + (input.SkillLevel/10);
    output.Damage = 9 + (input.INTE / 20) + (input.SkillLevel / 10);
    output.Delay = 10; // 1ÃÊ
    output.Range = 2 + (input.SkillLevel / 25);
}

void HolyArrow::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 2 + (input.INTE/20) + (input.SkillLevel/10);
    output.Damage = 8 + (input.INTE / 20) + (input.SkillLevel / 10);
    output.Delay = 10; // 1ÃÊ
    output.Range = 2 + (input.SkillLevel / 25);
}

void Rebuke::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = ( 2 + (input.SkillLevel/20) ) * 10;
    output.Duration = (8 + (input.SkillLevel / 20)) * 10;
    //	output.Damage	= ( input.INTE/10 ) + ( input.SkillLevel/5 );
    output.Damage = 10 + (input.INTE / 10) + (input.SkillLevel / 5);
    output.Delay = 80;
}

void SpiritGuard::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + (input.SkillLevel / 2)) * 10;
    output.Damage = (input.INTE / 10) + (input.SkillLevel / 4);
    output.Delay = 10;
    output.Tick = 10;
}

void Regeneration::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = ( 5 + (input.SkillLevel/10) ) * 10;
    output.Damage = 10 + (input.INTE / 40) + (input.SkillLevel / 10);
    output.Duration = (15 + (input.SkillLevel / 2)) * 10;
    //	output.Delay	= ( 6 + (input.SkillLevel/50) ) * 10;
    output.Delay = output.Duration;
    output.Tick = 10;
}

void PowerOfLand::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 10;
    output.Damage = (input.STR / 8) + (input.SkillLevel / 3);
    output.Duration = 10; // 1ÃÊ
    output.Tick = 10;     // 1ÃÊ
}

void TurnUndead::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage	= 10 + ( input.INTE / 20 ) + ( input.SkillLevel / 2 );
    output.Damage = 20 + (input.INTE / 20) + (input.SkillLevel / 3);
    output.Delay = 10;
}

void Armageddon::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (input.STR / 8) + (input.INTE / 6);
    output.Delay = 10;
    output.Duration = ((input.DEX / 10) + (input.INTE / 20)) * 10;
    output.Tick = 10;
}

void BloodyBreaker::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.INTE / 4 + input.STR / 5 + input.DEX / 5;
    output.Delay = max(1, 3 - input.DEX / 50) * 10;
    // ToHit Àº knockback È®·ü
    output.ToHit = 50;
}

void RapidGliding::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Range = min(6, 2 + (input.DEX / 50));
    output.Delay = max(1, 5 - (input.DEX / 60)) * 10; // min=1
}

void MagicElusion::computeOutput(const SkillInput& input, SkillOutput& output) {
    Attr_t SUM = (input.STR + input.DEX + input.INTE);
    output.Damage = SUM / 5;
    output.Duration = 50 + (SUM / 3);
    output.Delay = 50;
}

void PoisonMesh::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.SkillLevel / 4;
    output.Duration = 50;
    output.Delay = 50;
}

void IllusionOfAvenge::computeOutput(const SkillInput& input, SkillOutput& output) {
    Attr_t SUM = (input.STR + input.DEX + input.INTE);
    output.Damage = 15 + (SUM / 3);
    output.Delay = 50;
}

void WillOfLife::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.SkillLevel / 7;
    output.Duration = 30 + input.SkillLevel;
    output.Delay = output.Duration * 2;
}

void DenialMagic::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + (input.SkillLevel / 2)) * 10;
    output.Delay = (8 - (input.SkillLevel / 20)) * 10;
}

void Requital::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + (input.SkillLevel / 2)) * 10;
    output.Delay = (10 + (input.SkillLevel / 2)) * 10;
    output.Damage = (input.INTE / 8) + (input.SkillLevel / 4);
}

void Concealment::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = ( 5 + ( input.SkillLevel / 5 )) * 10;
    //	output.Duration = ( 15 + ( input.SkillLevel / 3 )) * 10;
    output.Duration = (30 + (input.SkillLevel / 2)) * 10;
    //	output.Delay = max( 1, 5 - ( input.DEX / 50 ) ) * 10;
    output.Delay = output.Duration;
}

void SwordRay::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 5 + input.STR/15 + input.SkillLevel/10;
    output.Damage = input.STR / 25 + input.SkillLevel / 20;
    output.Range = 2 + input.SkillLevel / 33;
    output.Delay = (5 - input.SkillLevel / 25) * 10;
    output.Tick = 5;
    output.Duration = 5;
}

void MultiAmputate::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = input.STR / 20 + input.SkillLevel / 10;
    output.Range = 2 + input.SkillLevel / 25;
    output.Delay = (5 - input.SkillLevel / 25) * 10;
}

void HitConvert::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (8 - input.SkillLevel / 33) * 10;
    output.Range = 2 + input.SkillLevel / 33;
}

void WildTyphoon::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (input.STR / 12) + (input.SkillLevel / 5);
    output.Delay = 50 - input.SkillLevel * 10 / 25;
    output.Range = 1;
}

void UltimateBlow::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 100 - input.SkillLevel * 10 / 25;
    output.Range = 1 + input.SkillLevel / 50;
}

void Illendue::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (input.INTE / 10) * (1 + (input.SkillLevel / 33));
    output.Delay = 50 - input.SkillLevel * 10 / 33;
    output.Range = 5;
}

void Lightness::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (15 + ((input.SkillLevel / 25) * 10)) * 10;
    output.Delay = min(300, output.Duration);
}

void Flourish::computeOutput(const SkillInput& input, SkillOutput& output) {
    // 1 <= SkillLevel <= 15
    if (input.SkillLevel < 16) {
        output.Damage = 3 + (int)((input.STR / 20.0) * (1.0 + (input.SkillLevel / 22.5)));
        output.Damage = min(30, output.Damage);
    }
    // 16 <= SkillLevel <= 30
    else {
        output.Damage = 3 + (int)((input.STR / 20.0) * (4.0 / 3.0 + (input.SkillLevel / 45.0)));
        output.Damage = min(30, output.Damage);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }
}

void Evade::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = (int)( ( input.DEX / 10.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 22.5 ) ) );
        output.Damage = 10 + (int)(input.SkillLevel * 16.0 / 9.0);
    } else {
        //		output.Damage = (int)( ( input.DEX / 10.0 ) * ( 4.0/3.0 + ( (float)(input.SkillLevel) / 45.0 ) ) );
        output.Damage = 10 + (int)(40.0 / 3.0 + input.SkillLevel * 8.0 / 9.0);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Damage = min(50, output.Damage);
    //	output.Duration = (int)(( 30.0 + ( (float)(input.SkillLevel) * 3.0 ) ) * 10);
    output.Duration = (60 + input.DEX / 10 * (input.SkillLevel * 2 / 3)) * 10;
    output.Duration = min(1200, output.Duration);
    //	output.Delay = max ( 50 , output.Duration * 2 - ( input.DEX * 2 ) );
    output.Delay = output.Duration - (input.SkillLevel / 5);
}

void SharpRound::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = (int)( ( input.STR / 9.0 ) * ( 1.0 + ( input.SkillLevel / 15.0 ) ) );
        output.Damage = (int)(14.0 + (input.STR / 15.0) * (1.0 + (input.SkillLevel / 15.0)));
        output.Damage = min(55, output.Damage);
    } else {
        //		output.Damage = (int)( ( input.STR / 9.0 ) * ( 1.5 + ( input.SkillLevel / 30.0 ) ) );
        output.Damage = (int)(14.0 + (input.STR / 15.0) * (1.5 + (input.SkillLevel / 30.0)));
        output.Damage = min(55, output.Damage);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = 0;
}

void BackStab::computeOutput(const SkillInput& input, SkillOutput& output) {}

void Blunting::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = min(60, (int)(((input.STR / 20.0) + (input.DEX / 10.0)) * (1.0 + (input.SkillLevel / 15.0))));
    } else {
        output.Damage = min(60, (int)(((input.STR / 20.0) + (input.DEX / 10.0)) * (1.5 + (input.SkillLevel / 30.0))));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Duration = min(300, (int)((((input.DEX + input.INTE) / 20.0) + ((input.SkillLevel / 2.0))) * 10));
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);

    output.Delay = max(40, (int)((8 - (input.DEX / 50.0)) * 10));
    output.Range = 1 + (input.SkillLevel / 10);
}

void GammaChop::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 10 + (int)((input.STR / 10.0) * (1.0 + (input.SkillLevel / 11.25)));
        output.Damage = min(120, output.Damage);
    } else {
        output.Damage = 10 + (int)((input.STR / 10.0) * (5.0 / 3.0 + (input.SkillLevel / 22.5)));
        output.Damage = min(120, output.Damage);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }
    output.Delay = 10; // max(10,(int)(( 4 - ( input.DEX / 60.0 ) ) * 10));
    output.Range = 1 + (input.SkillLevel / 15);
}

void CrossGuard::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = (int)( ( input.STR / 20.0 ) * ( 1.0 + ( input.SkillLevel / 11.25 ) ) );
        output.Damage = 15 + (input.SkillLevel * 14 / 9);
    } else {
        //		output.Damage = (int)( ( input.STR / 20.0 ) * ( 5.0/3.0 + ( input.SkillLevel / 22.5 ) ) );
        output.Damage = 15 + (35 / 3 + input.SkillLevel * 7 / 9);
    }

    output.Damage = min(50, output.Damage);
    output.Duration = (int)((60.0 + (input.DEX / 10.0) + (input.SkillLevel * 2.0)) * 10);
    output.Duration = min(1800, output.Duration);

    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);

    output.Delay = output.Duration;
}

void KasasArrow::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = 7 + (int)( ( input.INTE / 8.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 22.5 ) ) );
        output.Damage = 15 + (int)((input.INTE / 55.0) * (1.0 + ((float)(input.SkillLevel) / 30.0)));
    } else {
        //		output.Damage = 7 + (int)( ( input.INTE / 8.0 ) * ( 4.0/3.0 + ( (float)(input.SkillLevel) / 45.0 ) ) );
        output.Damage = 15 + (int)((input.INTE / 50.0) * (1.5 + ((float)(input.SkillLevel) / 25.0)));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.2);
    }

    output.Delay = 0;
    output.Range = 3 + (input.SkillLevel / 10);
}

void HandsOfFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (int)(5.0 + input.SkillLevel * 15.0 / 30.0);
    if (input.SkillLevel <= 15) {
        //		output.Damage = (int)( ( 1 + input.INTE / 50.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 22.5 ) ) );
        //		output.Damage = (int)( ( 7 + input.INTE / 12.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 11.25 ) ) );
    } else {
        //		output.Damage = (int)( ( 1 + input.INTE / 50.0 ) * ( 4.0/3.0 + ( (float)(input.SkillLevel) / 45.0 ) ) );
        //		output.Damage = (int)( ( 7 + input.INTE / 12.0 ) * ( 5.0/3.0 + ( (float)(input.SkillLevel) / 22.5 ) ) );
    }

    output.Duration = (int)((60.0 + (input.DEX / 10.0) + (input.SkillLevel * 1.5)) * 10);
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);
    output.Duration = min(1200, output.Duration);
    output.Delay = output.Duration;
}

void Prominence::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = (int)( ( input.INTE / 30.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 15.0 ) ) );
        //		output.Damage = 15 + (int)( ( input.INTE / 20.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 11.25 ) ) );
        output.Damage = 5 + (int)((input.INTE / 25.0) * (1.0 + ((float)(input.SkillLevel) / 10.0)));
    } else {
        //		output.Damage = (int)( ( input.INTE / 30.0 ) * ( 1.5 + ( (float)(input.SkillLevel) / 30.0 ) ) );
        //		output.Damage = 15 + (int)( ( input.INTE / 20.0 ) * ( 5.0/3.0 + ( (float)(input.SkillLevel) / 22.5 ) )
        //);
        output.Damage = 5 + (int)((input.INTE / 25.0) * (2.0 + ((float)(input.SkillLevel) / 25.0)));
    }

    output.Duration = (int)((5.0 + (input.INTE / 30.0) + (input.SkillLevel / 5.0)) * 10);
    output.Delay = output.Duration - (input.DEX / 20);
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);

    output.Range = 2 + (input.SkillLevel / 10);
    output.Tick = 10;
}

void RingOfFlare::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = (int)( ( input.INTE / 10.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 15.0 ) ) );
        output.Damage = (int)(5 + (input.INTE / 17.0) + (1.0 + ((float)(input.SkillLevel) / 3.0)));
    } else {
        //		output.Damage = (int)( ( input.INTE / 10.0 ) * ( 1.5 + ( (float)(input.SkillLevel) / 30.0 ) ) );
        output.Damage = (int)(2 + (input.INTE / 15.0) + (1.0 + ((float)(input.SkillLevel) / 2.0)));
    }

    output.Duration = (int)((35.0 + (input.INTE / 30.0) + (input.SkillLevel / 3.0)) * 10);
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);
    output.Delay = output.Duration;
}

void BlazeBolt::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Damage = 10 + (int)( ( input.INTE / 13.0 ) * ( 1.0 + ( (float)(input.SkillLevel) / 11.25 ) ) );
        output.Damage = 20 + (int)((input.INTE / 20.0) + (1.0 + ((float)(input.SkillLevel) / 3.0)));
    } else {
        //		output.Damage = 10 + (int)( ( input.INTE / 13.0 ) * ( 5.0 / 3.0 + ( (float)(input.SkillLevel) / 22.5 ) )
        //);
        output.Damage = 20 + (int)((input.INTE / 20.0) + (((float)(input.SkillLevel) / 2.5)));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.2);
    }

    output.Delay = 10;
    output.Range = 4 + (input.SkillLevel / 10);
}

void IceField::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Duration = (int)max(
            10, (int)min(300.0, ((input.INTE / 30.0) * (1.0 + ((float)(input.SkillLevel) / 22.5)) + 5.0) * 10));
        output.Range = max(20, min(150, output.Duration));
    } else {
        output.Duration = (int)max(
            10, (int)min(300.0, ((input.INTE / 30.0) * (4.0 / 3.0 + ((float)(input.SkillLevel) / 45.0)) + 5.0) * 10));
        output.Range = max(20, min(150, output.Duration));
    }

    output.Delay = (int)(output.Duration * 1.2 - (input.SkillLevel));
    output.Tick = 10;
}

void WaterBarrier::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)min(40, (int)(10.0 + (input.INTE / 20.0) * (1.0 + ((float)(input.SkillLevel) / 15.0))));
    } else {
        output.Damage = (int)min(40, (int)(10.0 + (input.INTE / 20.0) * (1.5 + ((float)(input.SkillLevel) / 30.0))));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Duration = (int)((30.0 + (input.INTE / 10.0) * (1.0 + (float)(input.SkillLevel) / 20.0)) * 10);
    output.Duration = min(1800, output.Duration);
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);
    output.Delay = output.Duration;
}

void NymphRecovery::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        if (input.TargetType == SkillInput::TARGET_OTHER) {
            output.Damage = 15 + (int)((input.INTE / 13.0) * (1.0 + ((float)(input.SkillLevel) / 15.0)));
        } else {
            output.Damage = 15 + (int)((input.INTE / 10.0) * (1.0 + ((float)(input.SkillLevel) / 15.0)));
        }
    } else {
        if (input.TargetType == SkillInput::TARGET_OTHER) {
            output.Damage = 15 + (int)((input.INTE / 13.0) * (1.5 + ((float)(input.SkillLevel) / 30.0)));
        } else {
            output.Damage = 15 + (int)((input.INTE / 10.0) * (1.5 + ((float)(input.SkillLevel) / 30.0)));
        }
    }
    if (input.SkillLevel == 30)
        output.Damage = (int)(output.Damage * 1.1);

    output.Delay = (int)((4 - (input.SkillLevel / 15.0)) * 10);
}

void Liberty::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (8 - (input.SkillLevel / 10)) * 10;
}

void Tendril::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        //		output.Duration = (int)(( 3 + ( input.INTE / 30.0 ) * ( 1.0 + (input.SkillLevel / 22.5) ) ) * 10);
        output.Duration = (3 + input.SkillLevel / 7) * 10;
    } else {
        //		output.Duration = (int)(( 3 + ( input.INTE / 30.0 ) * ( 4.0/3.0 + (input.SkillLevel / 45.0) ) ) * 10);
        output.Duration = (5 + input.SkillLevel / 15) * 10;
    }

    output.Delay = (9 - (input.SkillLevel / 6)) * 10;
    output.Range = 1 + (input.SkillLevel / 10);
}

void StoneAuger::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 20 + (int)(((input.INTE / 30.0) * (1.0 + (input.SkillLevel / 15.0))));
        output.Damage = min(50, output.Damage);
    } else {
        output.Damage = 20 + (int)(((input.INTE / 30.0) * (1.5 + (input.SkillLevel / 30.0))));
        output.Damage = min(50, output.Damage);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = (4 - (input.SkillLevel / 10)) * 10;
}

void EarthsTeeth::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 18 + (int)((input.INTE / 13.0) * (1.0 + ((float)(input.SkillLevel) / 11.25)));
        output.Damage = min(90, output.Damage);
    } else {
        output.Damage = 18 + (int)((input.INTE / 13.0) * (5.0 / 3.0 + ((float)(input.SkillLevel) / 22.5)));
        output.Damage = min(90, output.Damage);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = (2 - (input.SkillLevel / 10)) * 10;
    output.Delay = max(output.Delay, 6);
    output.Range = 3 + (input.SkillLevel / 15);
}

void HandsOfNizie::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 10 + (int)((input.INTE / 18.0) * (1.0 + ((float)(input.SkillLevel) / 15.0)));
    } else {
        output.Damage = 10 + (int)((input.INTE / 18.0) * (1.5 + ((float)(input.SkillLevel) / 30.0)));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = 6;
}

void GnomesWhisper::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Duration = (int)((input.INTE / 5.0) * (1.0 + ((float)(input.SkillLevel) / 11.25)));
    } else {
        output.Duration = (int)((input.INTE / 5.0) * (5.0 / 3.0 + ((float)(input.SkillLevel) / 22.5)));
        if (input.SkillLevel == 30)
            output.Duration = (int)(output.Duration * 1.1);
    }

    output.Duration *= 10;
    output.Delay = output.Duration;
}

void RefusalEther::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (5 - (input.SkillLevel / 15)) * 10;

    if (input.SkillLevel <= 8) {
        output.Range = 1;
    } else if (input.SkillLevel <= 16) {
        output.Range = 3;
    } else if (input.SkillLevel <= 23) {
        output.Range = 4;
    } else if (input.SkillLevel <= 29) {
        output.Range = 5;
    } else {
        output.Range = 7;
    }
}

void EmissionWater::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 10 + (int)((input.INTE / 50.0) * (1.0 + ((float)(input.SkillLevel) / 20.0)));
    } else {
        output.Damage = 10 + (int)((input.INTE / 55.0) * (2.0 + ((float)(input.SkillLevel) / 15.0)));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = 10;
}

void BeatHead::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 10 + (int)((input.INTE / 8.0) * (1.0 + ((float)(input.SkillLevel) / 22.5)));
    } else {
        output.Damage = 10 + (int)((input.INTE / 8.0) * (4.0 / 3.0 + ((float)(input.SkillLevel) / 45.0)));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = 0;
}

void DivineSpirits::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 10 + (int)((float)input.SkillLevel * 4.0 / 3.0);
    } else {
        output.Damage = 20 + (int)((float)input.SkillLevel * 2.0 / 3.0);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Duration = 30 + input.SkillLevel * 2;
    output.Duration *= 10;
    output.Delay = output.Duration;
}

void BlitzSliding::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 4 * (1 + input.SkillLevel / 25);
    output.Delay = (4 - (input.SkillLevel / 50)) * 10;
}

void JabbingVein::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = -30 + (input.STR / 20 + input.SkillLevel / 3);
    output.Delay = 2;

    if (input.TargetType == SkillInput::TARGET_PC) {
        output.Range = 2 + (input.SkillLevel / 33);
        output.Duration = (1 + (input.SkillLevel / 50)) * 10;
    } else {
        output.Range = 5 + (input.SkillLevel / 20);
        output.Duration = (2 + (input.SkillLevel / 25)) * 10;
    }
}

void GreatHeal::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        output.Damage = 100 + input.SkillLevel / 3;
    } else {
        output.Damage = 110 + input.SkillLevel / 3;
    }

    output.Delay = (5 - input.SkillLevel / 33) * 10;

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    // output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void DivineGuidance::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_PC) {
        output.Damage = 15 + (2 * input.SkillLevel / 25);
        output.Tick = 15;
        output.Range = (input.INTE / 5) + (input.SkillLevel / 10);
        output.Range = min(output.Range, 70);
    } else {
        output.Damage = 20 + (3 * input.SkillLevel / 20);
        output.Tick = 10;
        output.Range = (input.INTE / 3) + (input.SkillLevel / 10);
        output.Range = min(output.Range, 90);
    }

    output.Delay = (10 + input.SkillLevel / 20) * 10;
    output.Duration = (10 + input.SkillLevel / 20) * 10;
}

void BlazeWalk::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (5 - input.SkillLevel / 50) * 10;
    output.Damage = 2 * (1 + input.SkillLevel / 25);
}

void BloodyZenith::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (7 - (input.STR / 100 + input.DEX / 220 + input.INTE / 330)) * 10;
    output.Delay = max(30, output.Delay);
    //	output.Damage = 20 + input.STR/8 + input.DEX/20;
    output.Damage = min(150, 30 + input.STR / 3 + input.DEX / 10 + input.INTE / 20);
}

void Rediance::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (60 + input.SkillLevel * 3 / 2) * 10;
    //	output.Duration = ( 30 + input.STR/10 + input.SkillLevel*10/12 ) * 10;
    output.Delay = output.Duration;
    output.Damage = 7 + input.SkillLevel / 20 + input.DomainLevel / 10;
}

void LarSlash::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 4;
    output.Damage = 5 + input.STR / 10 + input.SkillLevel / 8;
}

void Trident::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.ToHit = -30 + input.DEX / 20 + input.SkillLevel / 4;
    output.Damage = -30 + input.STR / 20 + input.SkillLevel / 4;
    output.Delay = 2;
}

void HeartCatalyst::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 2 + input.SkillLevel / 20;
    output.Tick = 20;
    output.Duration = (10 + input.SkillLevel / 2) * 10;
    output.Delay = output.Duration;
}

void ProtectionFromBlood::computeOutput(const SkillInput& input, SkillOutput& output) {
    // by sigi. 2002.12.3
    if (input.TargetType == SkillInput::TARGET_OTHER) {
        // output.Damage = 10 + input.SkillLevel/10;
        output.Damage = min(20, 10 + input.INTE / 20);
    } else {
        // output.Damage = 20 + input.SkillLevel/10;
        output.Damage = min(30, 20 + input.INTE / 20);
    }

    // output.Duration = (20 + input.SkillLevel/2) * 10; // 20~70ÃÊ
    output.Duration = (60 + input.INTE / 2 + input.SkillLevel / 2) * 10; // 20~70ÃÊ
    output.Delay = (5 - input.SkillLevel / 33) * 10;                     // 5->2ÃÊ

    // ÆÄÆ¼ º¸³Ê½º¸¦ °è»êÇÑ´Ù.
    output.Damage = getPercentValue(output.Damage, PartyEffectBoost[input.PartySize]);
    output.Duration = getPercentValue(output.Duration, PartyDurationBoost[input.PartySize]);
}

void MoleShot::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.IClass == Item::ITEM_CLASS_SG) {
        output.Damage = 3 + input.SkillLevel / 10;
    }

    else if (input.IClass == Item::ITEM_CLASS_AR || input.IClass == Item::ITEM_CLASS_SMG) {
        output.Damage = 1 + input.SkillLevel / 30;
    }

    else if (input.IClass == Item::ITEM_CLASS_SR) {
        output.Damage = input.SkillLevel / 50;
    }

    output.ToHit = -20 + input.SkillLevel / 5;
    output.Delay = 2;
}

void Eternity::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = -50 + (input.SkillLevel / 2);
    //	output.Range = 50 + (input.SkillLevel/3);
    output.Duration = 50;
}

void InstallTrap::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 600;
    output.Tick = (5 + (input.SkillLevel / 25)) * 10;
    output.Delay = (60 - (int)(input.SkillLevel / 2.5)) * 10;
}

void HolyArmor::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (30 + (input.SkillLevel / 2)) * 10;
    output.Damage = 10 + (input.INTE / 20) + (input.SkillLevel / 10);
    output.Delay = output.Duration;
}

void MercyGround::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = (10 + input.INTE/20 + input.SkillLevel/10)*10;
    output.Duration = (15 + input.INTE / 15 + input.SkillLevel / 6) * 10;
    output.Delay = (10 - input.SkillLevel / 33) * 10;
}

void CreateHolyPotion::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (5 - input.SkillLevel / 33) * 10;
}

void TransformToWerwolf::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 50;
}

void GrayDarkness::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.INTE / 8) * 10;
    output.Delay = max(3, 10 - input.DEX / 50) * 10;
    //	output.Range    = (  3 + (input.SkillLevel-15) / 25);
}

void StoneSkin::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = min(60, 10 + input.STR / 10 + input.INTE / 6) * 10;
    output.Delay = min(60, 10 + input.STR / 10 + input.INTE / 6) * 10;
    output.Damage = min(30, 20 + input.INTE / 20);
}

void TalonOfCrow::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 6;
    output.Damage = input.STR / 6 + input.INTE / 30;
}

void Howl::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = min(120, 30 + input.STR / 4 + input.DEX / 3 + input.INTE / 6) * 10;
    output.Range = min(100, 60 + input.DEX / 20);
}

void AcidEruption::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(180, (input.STR / 6) + (input.INTE / 2) + (input.DEX / 10));
    output.Delay = max(3, 6 - (input.DEX / 50)) * 10;
}

void Teleport::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Range = min(6, 3 + input.SkillLevel / 10);
    output.Delay = max(1, 5 - (input.DEX / 60) - (input.INTE / 60)) * 10;
}

void FirePiercing::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 30 + (input.INTE / 20 + (3 + input.SkillLevel / 4));
    } else {
        output.Damage = 30 + (input.INTE / 20 + (2 + input.SkillLevel / 3));
    }

    if (input.SkillLevel == 30)
        output.Damage = (int)(output.Damage * 1.2);

    output.Delay = 0;
}

void SoulRebirth::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (8 - input.SkillLevel / 10) * 10;
    output.Range = 2 + input.SkillLevel / 10;

    if (input.SkillLevel <= 15) {
        output.Tick = 20 + input.SkillLevel * 2;
    } else {
        output.Tick = 50 + input.SkillLevel / 2;
    }
}

void IceLance::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)(28 + (input.INTE / 25) * (1.2 + (input.SkillLevel / 12.0)));
    } else {
        output.Damage = (int)(28 + (input.INTE / 22) * (1.0 + (input.SkillLevel / 13.0)));
    }

    output.Range = 4 + input.SkillLevel / 10;
}

void ExplosionWater::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)(20 + (input.INTE / 30.0) + (3.0 + (input.SkillLevel / 4.0)));
    } else {
        output.Damage = (int)(20 + (input.INTE / 23.0) + (3.0 + (input.SkillLevel / 3.0)));
    }

    output.Range = 4 + input.SkillLevel / 10;
    output.Duration = (2 + (input.SkillLevel / 10)) * 10;
    output.Delay = (15 - (input.SkillLevel / 6)) * 10;
    output.Tick = 40 - (input.SkillLevel / 3);
}

void FrozenArmor::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)min(20, (int)(10.0 + (input.INTE / 40.0) * (1.0 + ((float)(input.SkillLevel) / 15.0))));
        output.Tick =
            max(20, (int)min(15, (int)(5.0 + (input.INTE / 30.0) * (1.0 + ((float)(input.SkillLevel) / 22.5)))) * 10);
    } else {
        output.Damage = (int)min(20, (int)(10.0 + (input.INTE / 40.0) * (1.5 + ((float)(input.SkillLevel) / 30.0))));
        //		if ( input.SkillLevel == 30 ) output.Damage = (int)(output.Damage * 1.1);
        output.Tick = max(
            20, (int)min(15, (int)(5.0 + (input.INTE / 30.0) * (4.0 / 3.0 + ((float)(input.SkillLevel) / 45.0)))) * 10);
    }

    output.Duration = (int)((20.0 + (input.INTE / 20.0) * (1.0 + (float)(input.SkillLevel) / 20.0)) * 10);
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);
    output.Duration = min(600, output.Duration);
    output.Delay = output.Duration;
    output.Range = 1;
}

void ReactiveArmor::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)min(30, (int)(5.0 + (input.INTE / 30.0) * (1.1 + ((float)(input.SkillLevel) / 20.0))));
    } else {
        output.Damage = (int)min(45, (int)(5.0 + (input.INTE / 30.0) * (1.0 + ((float)(input.SkillLevel) / 15.0))));
        //		if ( input.SkillLevel == 30 ) output.Damage = (int)(output.Damage * 1.1);
    }

    output.Duration = (int)((20.0 + (input.INTE / 20.0) * (1.0 + (float)(input.SkillLevel) / 4.0)) * 10);
    //	if ( input.SkillLevel == 30 ) output.Duration = (int)(output.Duration * 1.1);
    output.Duration = min(1800, output.Duration);
    output.Delay = max(2, 5 - (input.INTE - 20) / 10) * 10;
}


void MagnumSpear::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)(40.0 + (input.INTE / 10.0) + (3.0 + (float)(input.SkillLevel) / 4.0));
    } else {
        output.Damage = (int)(40.0 + (input.INTE / 6.0) + (3.0 + (float)(input.SkillLevel) / 3.0));
    }

    output.Range = (int)(4.0 + (float)(input.SkillLevel) / 10);
}

void HellFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)(30.0 + (input.INTE / 8.0) + (1.0 + (float)(input.SkillLevel) / 2.0));
        //		output.Duration = (int)max(10, (int)min(100.0, ( ( input.INTE / 30.0 ) * ( 1.0 + (
        //(float)(input.SkillLevel) / 22.5 ) ) + 5.0 ) * 10));
        output.Duration = (int)((6.0 + (input.INTE / 60.0) + (input.SkillLevel / 15.0)) * 10);
        output.Range =
            max(20, min(150, (int)(((input.INTE / 30.0) * (1.0 + ((float)(input.SkillLevel) / 22.5)) + 5.0) * 10)));
    } else {
        output.Damage = (int)(30.0 + (input.INTE / 6.0) + (1.0 + (float)(input.SkillLevel)));
        //		output.Duration = (int)max(10, (int)min(100.0, ( ( input.INTE / 30.0 ) * ( 4.0/3.0 + (
        //(float)(input.SkillLevel) / 45.0 ) ) + 5.0 ) * 10));
        output.Duration = (int)((6.0 + (input.INTE / 60.0) + (input.SkillLevel / 10.0)) * 10);
        output.Range =
            max(20, min(150, (int)(((input.INTE / 30.0) * (1.0 + ((float)(input.SkillLevel) / 45.0)) + 5.0) * 10)));
    }

    // ToHit À» Speed Damage ·Î »ç¿ë
    output.ToHit = (int)(5.0 + (input.INTE / 50.0) * (1.0 + (input.SkillLevel / 15.0)));
    output.Delay = (int)max(40.0, (output.Duration * 1.2 - (input.SkillLevel * 10)));
    output.Tick = 5;
}

void GroundBless::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = (int)(1.0 + (input.STR + input.DEX + input.INTE) / 100.0 + 0.5 + input.SkillLevel / 10.0);
    } else {
        output.Damage = (int)(1.0 + (input.STR + input.DEX + input.INTE) / 100.0 + 1.0 + input.SkillLevel / 12.0);
    }

    output.Duration = (int)((20.0 + (input.INTE / 20.0) * (1.0 + (float)(input.SkillLevel) / 4.0)) * 10);
    output.Duration = min(1800, output.Duration);
    output.Delay = max(2, 5 - (input.INTE - 20) / 10) * 10;
}

void SharpChakram::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 11 + input.SkillLevel / 6;
    } else {
        output.Damage = 11 + input.SkillLevel / 4;
        //		if ( input.SkillLevel == 30 ) output.Damage = (int)(output.Damage * 1.1);
    }

    output.Duration = 450 + input.DEX / 2 + input.SkillLevel * 15;
    output.Duration = min(900, output.Duration);
    if (input.SkillLevel == 30)
        output.Duration = (int)(output.Duration * 1.1);
    output.Delay = output.Duration;
}

void DestructionSpear::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = min(60, 15 + (input.DEX / 20) + (input.SkillLevel / 3));
        output.Duration = max(20, min(150, (int)((5.0 + (input.DEX / 30.0) * (1.0 + (input.SkillLevel / 22.5))) * 10)));
    } else {
        output.Damage = min(60, 15 + (input.DEX / 20) + (input.SkillLevel / 2));
        output.Duration =
            max(20, min(150, (int)((5.0 + (input.DEX / 30.0) * (4.0 / 3.0 + (input.SkillLevel / 45.0))) * 10)));
    }

    output.Delay = 30 - input.DEX / 6 - input.SkillLevel;
    output.Delay = max(output.Delay, 6);
}

void ShiftBreak::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 5 + input.STR / 20 + input.DEX / 20 + input.SkillLevel / 3;
    } else {
        output.Damage = 5 + input.STR / 20 + input.DEX / 20 + input.SkillLevel / 2;
    }

    if (input.SkillLevel == 30)
        output.Damage = (int)(output.Damage * 1.1);

    output.Delay = max(6, (int)(30 - (input.DEX / 12) - (input.SkillLevel / 1.5)));
    output.Range = 1;
}

void FatalSnick::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = min(160, 20 + (int)((input.STR / 10.0) * (1.0 + (input.SkillLevel / 11.25))));
    } else {
        output.Damage = min(160, 20 + (int)((input.STR / 10.0) * (5.0 / 3.0 + (input.SkillLevel / 22.5))));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }
    //	output.Delay = max(20, (4 - (input.DEX/60)) * 10 );
    output.Delay = 10;
    output.Range = 1 + (input.SkillLevel / 15);
}

void ChargingAttack::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 20 + (int)((input.STR / 10.0) * (1.0 + (input.SkillLevel / 11.25)));
    } else {
        output.Damage = 20 + (int)((input.STR / 10.0) * (5.0 / 3.0 + (input.SkillLevel / 22.5)));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = max(50, (10 - (input.DEX / 60) - (input.SkillLevel / 10)) * 10);
    output.Range = 3 + (input.SkillLevel / 10);
}

void DuckingWallop::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 20 + (input.DEX / 10) * (1 + (input.SkillLevel / 11.25));
    } else {
        output.Damage = 20 + (input.DEX / 10) * (5.0 / 3.0 + (input.SkillLevel / 22.5));
    }

    output.Delay = max(20, 100 - (input.DEX / 6) - input.SkillLevel);
}

void DistanceBlitz::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 20 + (input.STR + input.DEX) / 30 * (1.0 + (input.SkillLevel / 15.0));
    } else {
        output.Damage = 20 + (input.STR + input.DEX) / 30 * (5.0 / 3.0 + (input.SkillLevel / 10.0));
    }

    output.Delay = (3 - (input.SkillLevel / 15.0)) * 10;
    output.Delay = max(10, output.Delay);
}

void SummonGroundElemental::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.INTE / 8 + input.SkillLevel) * 10;
    output.Delay = output.Duration;
}

void SummonFireElemental::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.INTE / 8 + input.SkillLevel * 2) * 10;
    output.Duration = min(output.Duration, 1200);
    output.Delay = output.Duration;

    if (input.SkillLevel <= 15) {
        output.Damage = 12 + (input.INTE / 20) + (input.SkillLevel / 4);
    } else {
        output.Damage = 12 + (input.INTE / 15) + (input.SkillLevel / 3);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.2);
    }

    output.Range = 4 + input.SkillLevel / 10;
}

void SummonWaterElemental::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (5 + input.INTE / 8 + input.SkillLevel * 2) * 10;
    output.Duration = min(output.Duration, 1200);
    output.Delay = output.Duration;

    if (input.SkillLevel <= 15) {
        output.Damage = 8 + (input.INTE / 30.0) * (1 + input.SkillLevel / 45.0);
        output.Damage = min(output.Damage, 20);
    } else {
        output.Damage = 8 + (input.INTE / 40.0) * (1.5 + input.SkillLevel / 30.0);
        output.Damage = min(output.Damage, 30);
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }
}

void MeteorStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Damage = 50 + (int)(((input.INTE / 10.0) + (1.0 + (input.SkillLevel / 6.0))));
    } else {
        output.Damage = 50 + (int)(((input.INTE / 5.0) + (1 + (input.SkillLevel / 3.0))));
        if (input.SkillLevel == 30)
            output.Damage = (int)(output.Damage * 1.1);
    }

    output.Delay = (8 - (input.SkillLevel / 5)) * 10;
}

void WideIceField::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 200;
    output.Range = 200;
    output.Tick = 5;
}

void Glacier1::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 50;
}

void Glacier2::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 100;
}

void IceAuger::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 300;
    output.Delay = 10;
}

void IceHail::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 30;
    output.Damage = 50;
    output.Tick = 5;
}

void WideIceHail::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 50;
    output.Damage = 50;
    output.Tick = 5;
}

void IceWave::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 320;
    output.Delay = 10;
}

void LandMineExplosion::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 320;
    output.Delay = 10;
}

void ClaymoreExplosion::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 320;
    output.Delay = 10;
}

void PleasureExplosion::computeOutput(const SkillInput& input, SkillOutput& output) {}

void DeleoEfficio::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 150;
}
void ReputoFactum::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 300;
    output.Delay = 200;
}

void SwordOfThor::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 80 + input.STR / 2 + input.SkillLevel / 2;
    output.Delay = 150;
    output.Duration = 150 + input.SkillLevel;
}

void BurningSolCharging::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 0;
}

void BurningSolLaunch::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 0;

    switch (input.Range) {
    case 0:
        output.Damage = 35 + (input.STR / 6) + (input.SkillLevel / 3);
        break;
    case 1:
        output.Damage = 70 + (input.STR / 6) + (input.SkillLevel / 3);
        break;
    case 2:
        output.Damage = 120 + (input.STR / 5) + (input.SkillLevel / 2);
        break;
    default:
        output.Damage = 200 + (input.STR / 5) + (input.SkillLevel / 2);
        break;
    }
}

void SweepVice::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 20;

    switch (input.Range) {
    case 0:
        output.Damage = 40 + (input.INTE / 5) + (input.SkillLevel / 3);
        break;
    case 1:
        output.Damage = 30 + (input.INTE / 5) + (input.SkillLevel / 3);
        break;
    case 2:
    default:
        output.Damage = 20 + (input.INTE / 5) + (input.SkillLevel / 3);
        break;
    }
}

void Whitsuntide::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 50 + (input.SkillLevel / 2);
    output.Range = 20 + (input.SkillLevel / 10);
    //	output.Delay = 80 - input.SkillLevel/3;
    output.Delay = 100 - input.SkillLevel / 5;
    output.Duration = 300;
}

void ViolentPhantom::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 5 + input.STR / 30 + input.DEX / 60;
    output.Delay = 0;
}

void InstallTurret::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 8 + (input.SkillLevel / 7);
    output.ToHit = 40 + (input.SkillLevel / 10);
    //	output.Delay = 330 + input.SkillLevel*2;
    output.Delay = 100 - input.SkillLevel / 33 * 10;
    output.Duration = 900 + input.SkillLevel * 20;
}

void TurretFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.ToHit = 0;
    output.Damage = -10 + (input.SkillLevel / 5);
}

void SummonGoreGland::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = input.INTE * 10 / 25 + 50;
    output.Delay = output.Duration;
}

void GoreGlandFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 20 + input.INTE / 10;
    output.Damage = min(80, output.Damage);
}

void ThrowingAxe::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = Random(870, 1000);
    output.Duration = 20; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 10;
}

void ChoppingFirewood::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = Random(870, 1000);
    output.Duration = 10; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 10;
}

void ChainThrowingAxe::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = Random(500, 650);
    output.Duration = 20; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 10;
}

void MultiThrowingAxe::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = Random(870, 1000);
    output.Duration = 20; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 10;
}
void PlayingWithFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 400;
    output.Duration = 20; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 0;
}

void InfinityThunderbolt::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Damage = 40 + (input.SkillLevel/2);
    output.Damage = 10 + (input.SkillLevel / 5);
    output.Duration = 0;
    output.Delay = 4;
}

void SpitStream::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 30 + (input.STR / 10) + (input.SkillLevel / 5);
    output.Duration = 4; // ¸î ÃÊÈÄ Æø¹ß
    output.Delay = 0;
}


void PlasmaRocketLauncher::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 30 + (input.SkillLevel / 1.5);
    output.ToHit = 10 + (input.STR / 10) + (input.SkillLevel / 5);
    output.Duration = (input.Range - 1) * 3;
    output.Delay = 0;
}

void BombingStar::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 40 + (input.INTE / 5) + (input.SkillLevel / 2);
    output.Delay = 20;
}

void IntimateGrail::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.TargetType == SkillInput::TARGET_SELF)
        output.Duration = 90 + (input.INTE / 5) + (input.SkillLevel / 2);
    else
        output.Duration = 10 + (input.INTE / 100.0) + (input.SkillLevel / 15.0);

    output.Duration *= 10;

    output.Delay = 15 - (input.SkillLevel / 30);
    output.Delay *= 10;
    output.Range = 4 + (input.SkillLevel / 50);
}

void NooseOfWraith::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(30 + (input.INTE / 3), 200);
    output.Delay = 18;
    output.Range = 7;
}

void SetAfire::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 0;
    // output.Damage = 10 + (input.STR/8) + (input.DEX/12);
    output.Damage = 20 + (input.STR / 6) + (input.DEX / 10);
}

void SharpHail::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 20;

    if (input.SkillLevel <= 15) {
        output.Damage = 30 + ((input.DEX + input.STR) / 20.0) * (1 + (input.SkillLevel / 15.0));
    } else {
        output.Damage = 30 + ((input.DEX + input.STR) / 20.0) * (5.0 / 3.0 + (input.SkillLevel / 10.0));
    }
    output.Tick = 3;
    output.Duration = 10;
}
void IceHorizon::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (5 + (input.INTE / 25) + (input.SkillLevel / 3)) * 10;
    output.Delay = output.Duration;
    output.Tick = 50;

    if (input.SkillLevel <= 15) {
        output.Damage = min(150, (int)(20 + (input.INTE / 3.0) + (3 + (input.SkillLevel / 4.0))));
        ;
    } else {
        output.Damage = min(200, (int)(20 + (input.INTE / 2.0) + (3 + (input.SkillLevel / 3.0))));
    }
}

void FuryOfGnome::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.SkillLevel <= 15) {
        output.Duration = min(10, (int)(5 * (1 + (input.SkillLevel / 22.5))));
        output.Damage = 70 + (input.INTE / 10.0) + (1 + (input.SkillLevel / 6.0));
    } else {
        output.Duration = min(10, (int)(5 * (4.0 / 3.0 + (input.SkillLevel / 45.0))));
        output.Damage = 70 + (input.INTE / 5.0) + (1 + (input.SkillLevel / 3.0));
    }
    output.Duration *= 10;
    output.Delay = (output.Duration) - (input.SkillLevel);
}

void SummonMiga::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 15 + (input.SkillLevel / 2);
    output.Duration *= 10;

    output.Delay = 80 - input.SkillLevel;
}

void SummonMigaAttack::computeOutput(const SkillInput& input, SkillOutput& output) {
    if (input.DEX <= 15) {
        output.Damage = 40 + (int)((input.INTE / 8.0) + (1 + (((float)input.DEX) / 6.0)));
    } else {
        output.Damage = 40 + (int)((input.INTE / 6.0) + (1 + (((float)input.DEX) / 3.0)));
    }
}

void Cannonade::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 52 + (rand() % 30);
    output.Duration = 20;
}

void SelfDestruction::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 0;
    output.Damage = 110 + (rand() % 40);
}

void ARAttack::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 0;
    output.Damage = 0;
}

void SMGAttack::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 0;
    output.Damage = 0;
}

void GrenadeAttack::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = 10;
    output.Damage = 80;
}

void Halo::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(200, 80 + (input.STR / 7) + (min(input.Range, 10) * 5));
    output.Range = 60 + (min(input.Range, 10) * 3);
    output.Duration = (5 + (input.DEX / 100.0) * 3) * 10;
    output.Delay = output.Duration;
}

void Destinies::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 70 + (input.INTE / 10) + (min(input.Range, 10) * 4);
    output.Delay = 100;
}

void FierceFlame::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 50 + (input.INTE / 30) + min(input.Range, 10);
    output.Duration = (5 + (min(input.Range, 10) / 2)) * 10;
    output.Delay = output.Duration;
}

void ShadowOfStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(80, 40 + (input.INTE / 30) + min(input.Range, 10));
    output.Duration = 50 + (min(input.Range, 10) * 5);
    output.Delay = 50;
}
// Ò°ÀÇ
void WildWolf::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (input.DEX / 8) + (input.STR / 30) + min(input.Range, 10) * 2;
    output.Delay = max(5, (10 - (input.DEX / 200))) * 10;
}

void Aberration::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.INTE / 40 + min(input.Range, 10) * 2) * 10;
    output.Delay = output.Duration;
    output.Range = min(40, 30 + input.INTE / 40);
}

void DragonTornado::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 30 + (input.STR / 15) + (min(input.Range, 10) * 2);
    output.Range = min(200, 80 + (input.STR / 10) + (min(input.Range, 10) * 4));
    output.Tick = min(200, 50 + (input.STR / 10) + (min(input.Range, 10) * 4));
    output.Duration = (20 + min(input.Range, 10)) * 10;
    output.Delay = 300;
}

void BikeCrash::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (20 + (input.STR / 15) + (min(input.Range, 10) * 2)) * 3;
    output.Delay = (10 - min(input.Range, 10) / 5) * 10;
}

void HarpoonBomb::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = -25 + (input.STR / 15) + (min(input.Range, 10) * 4);
    output.Delay = 0;
    output.Range = 30 + min(input.Range, 10) * 2;
    output.Tick = 100 + (min(input.Range, 10) * 5);
    output.Duration = (4 - (min(input.Range, 10) / 10.0)) * 10;
}

void PassingHeal::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 80 + (min(input.Range, 10) * 4);
    output.Delay = (3 - (min(input.Range, 10) / 10)) * 10;
    output.Range = 5 + (min(input.Range, 10) / 5);
    output.Duration = 0;
}

void RottenApple::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = (8 - (min(input.Range, 10) / 3)) * 10;
}

// add by coffee 2007-2-17
// ÑªÖ®ÀÓÓ¡
void BloodyScarify::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (input.DEX / 5) + (input.STR / 25) + min(input.Range, 10) * 2;
    output.Delay = max(5, (10 - (input.DEX / 200))) * 10;
}
// ÑªÖ®?Öä

void BloodCurse::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage =
        (int)(input.SkillLevel * 0.8 + (rand() % (int)(input.SkillLevel * 0.4 + 1))) + (input.INTE + input.DEX) / 4;
    output.Duration = 28; // ÑÓÊ±ÏÔÊ¾Ð§¹û
    output.Delay = max(5, (10 - (input.DEX / 200))) * 10;
    ;
}

// ÉÁÒ«Ö®½£
void ShineSword::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (20 + (input.STR / 15) + (min(input.Range, 10) * 2)) * 3;
    output.Delay = (4 - min(input.Range, 10) / 5) * 10;
    output.Duration = 20; // ÑÓÊ±ÏÔÊ¾Ð§¹û
}

// ¾ÞÅÚºäÕ¨
void BombCrashWalk::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Delay = 10;
    output.Damage = (input.STR / 8) + (input.SkillLevel / 3);
    output.Duration = 7; // 1ÃÊ
    output.Tick = 1;     // 1ÃÊ
                         /*
                         output.Damage = (20 + (input.STR/15) + (min(input.Range,10)*2))*3;
                         output.Delay = (4 - min(input.Range,10)/5)*10;
                         output.Duration = 20;//ÑÓÊ±ÏÔÊ¾Ð§¹û
                         */
}
// ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
void SatelliteBomb::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 150 + input.SkillLevel / 2;
    output.Duration = 6; // 0.6 Ãë
    output.Delay = 35 - input.SkillLevel * 10 / 33;
    output.Range = 8;
}

// ¿Ö²À»Ã¾õ (ÈËÀàÒ½ÉúÐÂ¼¼ÄÜ)
void IllusionInversion::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = max(200, ((input.INTE / 8) * (1 + (input.SkillLevel / 33))));
    // output.Damage = (( input.INTE / 5 )* 0.7) * ( 1 + ( input.SkillLevel / 33 ) );
    output.Delay = 170 - input.SkillLevel * 10 / 33;
    output.Range = 5;
    /*
    output.Damage	=  + input.SkillLevel / 2;
    output.Duration	= 6; //0.6 Ãë
    output.Delay	= 10;
    output.Range	= 8;
    */
}
// ÌìÉñ½µÁÙ (ÈËÀà×£¸£ÐÂ¼¼ÄÜ)
void HeavenGround::computeOutput(const SkillInput& input, SkillOutput& output) {
    //	output.Duration = (10 + input.INTE/20 + input.SkillLevel/10)*10;
    output.Duration = (10 + input.INTE / 20 + input.SkillLevel / 6) * 9;
    // cout << "ÌìÉñ½µÁÙÑÓÊ±:" << (int)output.Duration << endl;

    output.Delay = output.Duration; //(10 - input.SkillLevel/33) * 10;
    // edit by Coffee 2007-5-8
    output.Damage = min(80, (input.INTE / 18) * (1 + (input.SkillLevel / 33)));
    output.Tick = 20;
}
// µÂÀ×¿Ë¿þÀÜ(Ä§Áé »ð·¨)
void DummyDrake::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 250 + (input.INTE / 50) + min(input.Range, 10);
    output.Duration = (10 + (min(input.Range, 10) / 2)) * 5;
    output.Delay = output.Duration;
}
// ¸´ºÏË®ÁÆ (Ë®·¨)
void HydroConvergence::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 20 + (input.INTE / 50) + min(input.Range, 10);
    output.Duration = (10 + (min(input.Range, 10) / 2)) * 5;
    output.Delay = output.Duration;
}
// Õ³ÍÁÕÙ»½ (ÍÁ·¨)
void SummonClay::computeOutput(const SkillInput& input, SkillOutput& output) {
    // output.Damage = 20 + (input.INTE/50) + min(input.Range,10);
    output.Duration = ((input.INTE / 30) + (min(input.Range, 10) / 2)) * 13;
    // cout << "Õ³ÍÁÕÙ»½:" << (int)output.Duration << endl;
    output.Delay = output.Duration;
}
// ÏÄ²¼Àû»ùÒò (Ä§Õ½)
void HeterChakram::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = min(200, 140 + (input.STR / 5) + (min(input.Range, 10) * 5));
    output.Range = 60 + (min(input.Range, 10) * 3);
    output.Duration = 18;
    output.Delay = 70;
}

void SkyFire::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 60 + (int)((input.Range - 1) / 10) * 10;
    output.Duration = 0;
    output.Delay = 4;
}

void CutStorm::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (20 + (input.STR / 15) + (min(input.Range, 10) * 2)) * 3;
    output.Delay = (4 - min(input.Range, 10) / 5) * 10;
    output.Duration = 20; // ÑÓÊ±ÏÔÊ¾Ð§¹û
}
void XRLMissile::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 150 + input.SkillLevel / 2;
    output.Duration = 6; // 0.6 Ãë
    output.Delay = 35 - input.SkillLevel * 10 / 33;
    output.Range = 8;
}
void SacredStamp::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = max(200, ((input.INTE / 8) * (1 + (input.SkillLevel / 33))));
    // output.Damage = (( input.INTE / 5 )* 0.7) * ( 1 + ( input.SkillLevel / 33 ) );
    output.Delay = 170 - input.SkillLevel * 10 / 33;
    output.Range = 5;
    /*
    output.Damage	=  + input.SkillLevel / 2;
    output.Duration	= 6; //0.6 Ãë
    output.Delay	= 10;
    output.Range	= 8;
    */
}
void BrambleHalo::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = (10 + input.INTE / 20 + input.SkillLevel / 6) * 9;
    output.Delay = output.Duration; //(10 - input.SkillLevel/33) * 10;
    output.Damage = min(80, (input.INTE / 18) * (1 + (input.SkillLevel / 33)));
    output.Tick = 20;
}
void DeadlyClaw::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (input.DEX / 40) + (input.STR / 20) + min(input.Range, 10);
    output.Delay = 0;
}
void VoodooRing::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage =
        (int)(input.SkillLevel * 0.8 + (rand() % (int)(input.SkillLevel * 0.4 + 1))) + (input.INTE + input.DEX) / 4;
    output.Duration = 28; // ÑÓÊ±ÏÔÊ¾Ð§¹û
    output.Delay = max(5, (10 - (input.DEX / 200))) * 10;
    ;
}
void PenetrateWheel::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = (30 + (input.DEX / 10.0)) * (11 + (int)((input.Range - 1) / 10)) / 10;
    output.Duration = max(20, min(150, (int)((5.0 + (input.DEX / 30.0) * 2.0) * 10.0)));
    output.Delay = 6;
}

void FireMeteor::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 250 + (input.INTE / 50) + min(input.Range, 10);
    output.Duration = (10 + (min(input.Range, 10) / 2)) * 5;
    output.Delay = output.Duration;
}
void BigRockfall::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Duration = ((input.INTE / 30) + (min(input.Range, 10) / 2)) * 13;
    output.Delay = output.Duration;
}
void RapidFreeze::computeOutput(const SkillInput& input, SkillOutput& output) {
    output.Damage = 20 + (input.INTE / 50) + min(input.Range, 10);
    output.Duration = (10 + (min(input.Range, 10) / 2)) * 5;
    output.Delay = output.Duration;
}
