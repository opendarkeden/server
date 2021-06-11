######################################################################
#
# Filename    : Makefile for Skill.lib
# Written By  : elca@ewestsoft.com
# Description :
#
######################################################################

VSHOME   = ../../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../../..
COREDIR  = ../../../Core
SERVDIR  = ../..
GAMEDIR  = ..
DBDIR    = ../../database
MYSQLDIR = /usr/local/lib/mysql


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I$(GAMEDIR) -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I.
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 


DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

HANDLER_OBJS = \
	HitRoll.o \
	SkillHandler.o \
	SkillHandlerManager.o \
	VampireSkillSlot.o \
	OustersSkillSlot.o \
	SkillSlot.o \
	SkillFormula.o \
	SkillUtil.o \
	CastleSkillSlot.o

SKILL_OBJS = \
	SimpleMeleeSkill.o \
	SimpleMissileSkill.o \
	SimpleTileMeleeSkill.o \
	SimpleLinearMeleeSkill.o \
	SimpleCureSkill.o \
	SimpleTileCureSkill.o \
	SimpleTileMissileSkill.o \
	AttackMelee.o \
	AttackArms.o \
	DoubleImpact.o \
	TripleSlasher.o \
	RainbowSlasher.o \
	ThunderSpark.o \
	DancingSword.o \
	CrossCounter.o \
	FlashSliding.o \
	LightningHand.o \
	SwordWave.o \
	SnakeCombo.o \
	SingleBlow.o \
	SpiralSlay.o \
	TripleBreak.o \
	WildSmash.o \
	GhostBlade.o \
	PotentialExplosion.o \
	ShadowWalk.o \
	ChargingPower.o \
	HurricaneCombo.o \
	TornadoSever.o \
	QuickFire.o \
	DoubleShot.o \
	TripleShot.o \
	MultiShot.o \
	HeadShot.o \
	Piercing.o \
	Sniping.o \
	CreateHolyWater.o \
	Light.o \
	DetectHidden.o \
	AuraBall.o \
	Bless.o \
	ContinualLight.o \
	Flare.o \
	Purify.o \
	AuraRing.o \
	Striking.o \
	DetectInvisibility.o \
	AuraShield.o \
	Visible.o \
	CureLightWounds.o \
	CurePoison.o \
	ProtectionFromPoison.o \
	CauseLightWounds.o \
	CureSeriousWounds.o \
	RemoveCurse.o \
	ProtectionFromCurse.o \
	CauseSeriousWounds.o \
	CureCriticalWounds.o \
	Sacrifice.o \
	CauseCriticalWounds.o \
	ProtectionFromAcid.o \
	CureAll.o \
	RegenerationSkill.o \
	BloodDrain.o \
	PoisonousHands.o \
	GreenPoison.o \
	YellowPoison.o \
	DarkBluePoison.o \
	GreenStalker.o \
	AcidTouch.o \
	AcidBolt.o \
	AcidBall.o \
	AcidSwamp.o \
	Paralyze.o \
	Doom.o \
	Hide.o \
	Darkness.o \
	Invisibility.o \
	TransformToWolf.o \
	TransformToBat.o \
	Unburrow.o \
	Untransform.o \
	Uninvisibility.o \
	EatCorpse.o \
	Howl.o \
	ThrowHolyWater.o \
	Restore.o \
	BloodyMarker.o \
	BloodyTunnel.o \
	Resurrect.o \
	Seduction.o \
	WindDivider.o \
	Earthquake.o \
	MindControl.o \
	BloodyNail.o \
	BloodyKnife.o \
	BloodyBall.o \
	BloodySpear.o \
	ThunderBolt.o \
	Expansion.o \
	MiracleShield.o \
	ThunderFlash.o \
	Berserker.o \
	MoonlightSever.o \
	ShadowDancing.o \
	Typhoon.o \
	PoisonStrike.o \
	AcidStrike.o \
	BloodyStrike.o \
	PoisonStorm.o \
	AcidStorm.o \
	BloodyStorm.o \
	InstallMine.o \
	DisarmMine.o \
	CreateBomb.o \
	CreateMine.o \
	Extreme.o \
	Revealer.o \
	VigorDrop.o \
	EnergyDrop.o \
	CriticalGround.o \
	ThunderStorm.o \
	Peace.o \
	Activation.o \
	HolyBlast.o \
	Sanctuary.o \
	Reflection.o \
	Hymn.o \
	Death.o \
	Mephisto.o \
	Transfusion.o \
	MentalSword.o \
	SummonCasket.o \
	OpenCasket.o \
	ObservingEye.o \
	SummonMonsters.o \
	BloodyWave.o \
	BloodyMasterWave.o \
	GroundAttack.o \
	MeteorStrike.o \
	Hallucination.o \
	DuplicateSelf.o \
	BloodyWall.o \
	BloodySnake.o \
	BloodyWarp.o \
	SoulChain.o \
	WideLightning.o \
	SharpShield.o \
	GunShotGuidance.o \
	AirShield.o \
	BulletOfLight.o \
	HandsOfWisdom.o \
	LightBall.o \
	HolyArrow.o \
	Rebuke.o \
	SpiritGuard.o \
	Regeneration.o \
	PowerOfLand.o \
	TurnUndead.o \
	Armageddon.o \
	BloodyBreaker.o \
	RapidGliding.o \
	MagicElusion.o \
	PoisonMesh.o \
	IllusionOfAvenge.o \
	WillOfLife.o \
	DenialMagic.o \
	Requital.o \
	Concealment.o \
	SwordRay.o \
	MultiAmputate.o \
	HitConvert.o \
	WildTyphoon.o \
	UltimateBlow.o \
	Illendue.o \
	Lightness.o \
	Flourish.o \
	Evade.o \
	SharpRound.o \
	BackStab.o \
	Blunting.o \
	GammaChop.o \
	CrossGuard.o \
	KasasArrow.o \
	HandsOfFire.o \
	Prominence.o \
	RingOfFlare.o \
	BlazeBolt.o \
	IceField.o \
	WaterBarrier.o \
	NymphRecovery.o \
	Liberty.o \
	Tendril.o \
	StoneAuger.o \
	EarthsTeeth.o \
	GnomesWhisper.o \
	AbsorbSoul.o \
	HandsOfNizie.o \
	RefusalEther.o \
	EmissionWater.o \
	BeatHead.o \
	DivineSpirits.o \
	BlitzSliding.o \
	JabbingVein.o \
	GreatHeal.o \
	DivineGuidance.o \
	BlazeWalk.o \
	BloodyZenith.o \
	Rediance.o \
	LarSlash.o \
	Trident.o \
	HeartCatalyst.o \
	ProtectionFromBlood.o \
	MoleShot.o \
	Eternity.o \
	InstallTrap.o \
	HolyArmor.o \
	MercyGround.o \
	CreateHolyPotion.o \
	TransformToWerwolf.o \
	GrayDarkness.o \
	StoneSkin.o \
	TalonOfCrow.o \
	BiteOfDeath.o \
	AcidEruption.o \
	Teleport.o \
	FirePiercing.o \
	SoulRebirth.o \
	IceLance.o \
	ExplosionWater.o \
	FrozenArmor.o \
	MagnumSpear.o \
	ReactiveArmor.o \
	GroundBless.o \
	HellFire.o \
	SharpChakram.o \
	DestructionSpear.o \
	ShiftBreak.o \
	FatalSnick.o \
	ChargingAttack.o \
	DuckingWallop.o \
	DistanceBlitz.o \
	SummonGroundElemental.o \
	SummonFireElemental.o \
	SummonWaterElemental.o \
	MeteorStorm.o \
	WideIceField.o \
	Glacier1.o \
	Glacier2.o \
	IceAuger.o \
	IceHail.o \
	WideIceHail.o \
	IceWave.o \
	LandMineExplosion.o \
	ClaymoreExplosion.o \
	PleasureExplosion.o \
	DeleoEfficio.o \
	ReputoFactum.o \
	SwordOfThor.o \
	BurningSolCharging.o \
	BurningSolLaunch.o \
	SweepVice.o \
	Whitsuntide.o \
	ViolentPhantom.o \
	InstallTurret.o \
	TurretFire.o \
	SummonGoreGland.o \
	GoreGlandFire.o \
	ThrowingAxe.o \
	ChoppingFirewood.o \
	ChainThrowingAxe.o \
	MultiThrowingAxe.o \
	PlayingWithFire.o \
	InfinityThunderbolt.o \
	SpitStream.o \
	PlasmaRocketLauncher.o \
	BombingStar.o \
	IntimateGrail.o \
	NooseOfWraith.o \
	SetAfire.o \
	SharpHail.o \
	IceHorizon.o \
	FuryOfGnome.o \
	SummonMiga.o \
	SummonMigaAttack.o \
	Cannonade.o \
	SelfDestruction.o \
	ARAttack.o \
	SMGAttack.o \
	GrenadeAttack.o \
	Halo.o \
	Destinies.o \
	FierceFlame.o \
	ShadowOfStorm.o \
	WildWolf.o \
	Aberration.o \
	DragonTornado.o \
	BikeCrash.o \
	HarpoonBomb.o \
	PassingHeal.o \
	RottenApple.o \
	MonsterRangeSkill.o \
	BloodyScarify.o \
	BloodCurse.o \
	ShineSword.o \
	BombCrashWalk.o \
	SatelliteBomb.o \
	IllusionInversion.o \
	HeavenGround.o \
	DummyDrake.o \
	HydroConvergence.o \
	SummonClay.o \
	HeterChakram.o

EFFECT_OBJS = \
	EffectAcidSwamp.o \
	EffectAuraShield.o \
	EffectBless.o \
	EffectBloodDrain.o \
	EffectCrossCounter.o \
	EffectDoom.o \
	EffectDarkBluePoison.o \
	EffectDarkness.o \
	EffectRevealer.o \
	EffectDetectHidden.o \
	EffectDetectInvisibility.o \
	EffectDetectMine.o \
	EffectFadeOut.o \
	EffectGreenPoison.o \
	EffectGreenStalker.o \
	EffectInvisibility.o \
	EffectLight.o \
	EffectPoison.o \
	EffectPotentialExplosion.o \
	EffectProtectionFromCurse.o \
	EffectProtectionFromPoison.o \
	EffectParalyze.o \
	EffectRegeneration.o \
	EffectReloadTimer.o \
	EffectStriking.o \
	EffectTransformToWolf.o \
	EffectTransformToBat.o \
	EffectYellowPoison.o \
	EffectYellowPoisonToCreature.o \
	EffectFlare.o \
	EffectAuraShield.o \
	EffectDancingSword.o \
	EffectSnipingMode.o \
	EffectChargingPower.o \
	EffectGhostBlade.o \
	EffectProtectionFromAcid.o \
	EffectSacrifice.o \
	EffectVampirePortal.o \
	EffectSeduction.o \
	EffectMindControl.o \
	EffectExpansion.o \
	EffectMiracleShield.o \
	EffectBerserker.o \
	EffectTyphoon.o \
	EffectCureCriticalWounds.o \
	EffectRestore.o \
	EffectExtreme.o \
	EffectAcidStorm.o \
	EffectStormAcid.o \
	EffectBloodyStorm.o \
	EffectStormBloody.o \
	EffectPoisonStorm.o \
	EffectEnergyDrop.o \
	EffectEnergyDropToCreature.o \
	EffectVigorDrop.o \
	EffectVigorDropToCreature.o \
	EffectStormPoison.o \
	EffectCauseCriticalWounds.o \
	EffectPeace.o \
	EffectActivation.o \
	EffectSanctuary.o \
	EffectReflection.o \
	EffectHymn.o \
	EffectDeath.o \
	EffectSummonCasket.o \
	EffectMephisto.o \
	EffectObservingEye.o \
	EffectGroundAttack.o \
	EffectMeteorStrike.o \
	EffectHallucination.o \
	EffectDecreaseHP.o \
	EffectBloodyWall.o \
	EffectBloodySnake.o \
	EffectBloodyWallBlocked.o \
	EffectSoulChain.o \
	EffectSharpShield.o \
	EffectGunShotGuidanceAim.o \
	EffectGunShotGuidancePoint.o \
	EffectAirShield.o \
	EffectSleep.o \
	EffectSpiritGuard.o \
	EffectArmageddon.o \
	EffectTileStorm.o \
	EffectMagicElusion.o \
	EffectPoisonMesh.o \
	EffectWillOfLife.o \
	EffectDenialMagic.o \
	EffectRequital.o \
	EffectConcealment.o \
	EffectLightness.o \
	EffectEvade.o \
	EffectBlunting.o \
	EffectCrossGuard.o \
	EffectHandsOfFire.o \
	EffectProminence.o \
	EffectRingOfFlare.o \
	EffectIceField.o \
	EffectIceFieldToCreature.o \
	EffectWaterBarrier.o \
	EffectTendril.o \
	EffectGnomesWhisper.o \
	EffectSummonSylph.o \
	EffectIceOfSoulStone.o \
	EffectBlockHead.o \
	EffectDivineSpirits.o \
	EffectContinualBloodyWall.o \
	EffectJabbingVein.o \
	EffectDivineGuidance.o \
	EffectBlazeWalk.o \
	EffectRediance.o \
	EffectHeartCatalyst.o \
	EffectProtectionFromBlood.o \
	EffectEternity.o \
	EffectTrapInstalled.o \
	EffectTrapTriggered.o \
	EffectHolyArmor.o \
	EffectMercyGround.o \
	EffectTransformToWerwolf.o \
	EffectGrayDarkness.o \
	EffectStoneSkin.o \
	EffectHowl.o \
	EffectAcidEruption.o \
	EffectExplosionWater.o \
	EffectFrozenArmor.o \
	EffectMagnumSpear.o \
	EffectReactiveArmor.o \
	EffectGroundBless.o \
	EffectHellFire.o \
	EffectHellFireToEnemy.o \
	EffectSharpChakram.o \
	EffectDestructionSpear.o \
	EffectSummonGroundElemental.o \
	EffectGroundElemental.o \
	EffectSummonFireElemental.o \
	EffectSummonWaterElemental.o \
	EffectBlindness.o \
	EffectIceHail.o \
	EffectIceHailToTile.o \
	EffectReputoFactum.o \
	EffectSwordOfThor.o \
	EffectBurningSolCharging.o \
	EffectWhitsuntide.o \
	EffectInstallTurret.o \
	EffectPlasmaRocketLauncher.o \
	EffectIntimateGrail.o \
	EffectSetAfire.o \
	EffectIceHorizon.o \
	EffectFuryOfGnome.o \
	EffectFuryOfGnomeMark.o \
	EffectSharpHail.o \
	EffectCannonade.o \
	EffectHalo.o \
	EffectDestinies.o \
	EffectFierceFlame.o \
	EffectShadowOfStorm.o \
	EffectAberration.o \
	EffectDragonTornado.o \
	EffectHarpoonBomb.o \
	EffectPassingHeal.o \
	EffectBloodCurse.o \
	EffectBombCrashWalk.o \
	EffectBombCrashWalkToEnemy.o \
	EffectSatelliteBombAim.o \
	EffectSatelliteBombPoint.o \
	EffectHeavenGround.o \
	EffectDummyDrake.o \
	EffectHydroConvergence.o \
	EffectSummonClay.o \
	EffectHeterChakram.o  \
        BigRockfall.o \
        BrambleHalo.o \
        CutStorm.o \
        DeadlyClaw.o \
        FireMeteor.o \
        PenetrateWheel.o \
        RapidFreeze.o \
        SacredStamp.o \
        SkyFire.o \
        VoodooRing.o \
        XRLMissile.o \
        EffectBrambleHalo.o \
        EffectFireMeteor.o \
        EffectPenetrateWheel.o \
        EffectRapidFreeze.o \
        EffectXRLMissile.o 


OBJS = $(HANDLER_OBJS) $(SKILL_OBJS) $(EFFECT_OBJS)

SRCS = $(OBJS:.o=.cpp)

DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

TARGET = $(LIBDIR)/libSkill.a

$(TARGET) : $(OBJS)
	ar rc $(TARGET) $(OBJS)

clean :
	rm -rf *.o $(TARGET)

cleanall :
	rm -rf *.o $(TARGET)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
