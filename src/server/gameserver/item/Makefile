#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
# Description :
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Directories Setting
#----------------------------------------------------------------------
VSHOME   = ../../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../../..
COREDIR  = ../../../Core
SERVDIR  = ../..
DBDIR    = ../../database
GSDIR    = ..
MYSQLDIR = /usr/local/lib/mysql


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I.
#CCFLAGS  = -Wall -c -g  
CCFLAGS  = -Wall -c -g 

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

OBJS = \
	ItemIDRegistry.o \
	AR.o \
	Belt.o \
	Blade.o \
	Bomb.o \
	BombMaterial.o \
	Bracelet.o \
	Coat.o \
	Cross.o \
	Mace.o \
	ETC.o \
	Glove.o \
	Sword.o \
	Helm.o \
	HolyWater.o \
	Key.o \
	LearningItem.o \
	Magazine.o \
	Mine.o \
	Money.o \
	Motorcycle.o \
	Necklace.o \
	Potion.o \
	Ring.o \
	SG.o \
	SMG.o \
	Shield.o \
	Shoes.o \
	SR.o \
	Trouser.o \
	VampireBracelet.o \
	VampireRing.o \
	VampireNecklace.o \
	VampireCoat.o \
	Water.o \
	Skull.o \
	Serum.o \
	VampireETC.o \
	SlayerPortalItem.o \
	VampirePortalItem.o \
	EventGiftBox.o \
	EventStar.o	\
	VampireEarring.o \
	Relic.o \
	VampireWeapon.o \
	VampireAmulet.o \
	QuestItem.o \
	Gun.o \
	EventTree.o \
	EventETC.o \
	BloodBible.o \
	CastleSymbol.o \
	CoupleRing.o \
	VampireCoupleRing.o \
	CoupleRingBase.o \
	EventItem.o \
	DyePotion.o \
	ResurrectItem.o \
	MixingItem.o \
	OustersArmsband.o \
	OustersBoots.o \
	OustersChakram.o \
	OustersCirclet.o \
	OustersCoat.o \
	OustersPendent.o \
	OustersRing.o \
	OustersStone.o \
	OustersWristlet.o \
	Larva.o \
	Pupa.o \
	ComposMei.o \
	OustersSummonItem.o \
	EffectItem.o \
	CodeSheet.o \
	MoonCard.o \
	Sweeper.o \
	PetItem.o \
	PetFood.o \
	PetEnchantItem.o \
	LuckyBag.o \
	SMSItem.o \
	CoreZap.o \
	TrapItem.o \
	WarItem.o \
	CarryingReceiver.o \
	ShoulderArmor.o \
	Dermis.o \
	Persona.o \
	Fascia.o \
	Mitten.o

SRCS = $(OBJS:.o=.cpp)

DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

TARGET = $(LIBDIR)/libItems.a


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET)

$(TARGET) : $(OBJS)
	ar rc $@ $^

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
