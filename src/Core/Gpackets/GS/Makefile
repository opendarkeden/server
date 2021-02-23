#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
VSHOME  = ../../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = $(VSHOME)/src/Core
SERVDIR = $(VSHOME)/src/server
DBDIR   = $(SERVDIR)/database
GSDIR   = $(SERVDIR)/gameserver
LSDIR   = $(SERVDIR)/loginserver
SSDIR   = $(SERVDIR)/sharedserver
SKILLDIR= $(GSDIR)/skill
ITEMDIR = $(GSDIR)/item
BILLINGDIR = $(GSDIR)/billing


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__ 
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR) -I.

CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

TARGET_GS = $(LIBDIR)/libGameServerPackets.a
TARGET_LS = $(LIBDIR)/libLoginServerPackets.a
TARGET_SS = $(LIBDIR)/libSharedServerPackets.a


TARGET = $(TARGET_GS)

include ../OBJS

.cpp.o : 
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

all : $(TARGET)

$(TARGET) : $(OBJS)
	ar r $@ $(OBJS)

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o

depall :
	gccmakedep	$(SRCS) $(INCLUDES) $(DEFS)

dep :
	gccmakedep	$(SRCS) $(INCLUDES) $(DEFS)


# DO NOT DELETE
GCWarList.o: GCWarList.cpp GCWarList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/WarInfo.h \
 ../../../../src/Core/ValueList.h \
 ../../../../src/Core/Assert.h
GCWarListHandler.o: GCWarListHandler.cpp GCWarList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/WarInfo.h \
 ../../../../src/Core/ValueList.h
GCAddBat.o: GCAddBat.cpp GCAddBat.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddBatHandler.o: GCAddBatHandler.cpp GCAddBat.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddBurrowingCreature.o: GCAddBurrowingCreature.cpp \
 GCAddBurrowingCreature.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddBurrowingCreatureHandler.o: GCAddBurrowingCreatureHandler.cpp \
 GCAddBurrowingCreature.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddEffect.o: GCAddEffect.cpp GCAddEffect.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddEffectHandler.o: GCAddEffectHandler.cpp GCAddEffect.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddEffectToTile.o: GCAddEffectToTile.cpp GCAddEffectToTile.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddEffectToTileHandler.o: GCAddEffectToTileHandler.cpp \
 GCAddEffectToTile.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddGearToInventory.o: GCAddGearToInventory.cpp \
 GCAddGearToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/server/gameserver/Vampire.h \
 ../../../../src/server/gameserver/PlayerCreature.h \
 ../../../../src/server/gameserver/Creature.h \
 ../../../../src/server/gameserver/Object.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/server/gameserver/EffectManager.h \
 ../../../../src/server/gameserver/Effect.h \
 ../../../../src/server/Timeval.h  \
   \
   \
 ../../../../src/Core/EffectInfo.h \
 ../../../../src/server/gameserver/VisionInfo.h \
  \
 ../../../../src/server/gameserver/ObjectRegistry.h \
 ../../../../src/server/Mutex.h  \
   \
   \
 ../../../../src/server/gameserver/InventorySlot.h \
 ../../../../src/server/gameserver/Item.h \
   \
   \
 ../../../../src/server/gameserver/Garbage.h \
 ../../../../src/server/gameserver/RankBonus.h \
 ../../../../src/server/gameserver/quest/Squest/QuestManager.h \
   \
  \
 ../../../../src/server/gameserver/Inventory.h \
 ../../../../src/server/gameserver/VolumeInfo.h \
 ../../../../src/server/gameserver/Zone.h \
 ../../../../src/server/gameserver/Tile.h  \
  \
 ../../../../src/server/gameserver/Obstacle.h \
 ../../../../src/server/gameserver/Portal.h \
 ../../../../src/server/gameserver/quest/TriggerManager.h \
 ../../../../src/server/gameserver/quest/Trigger.h \
 ../../../../src/server/gameserver/quest/Condition.h \
 ../../../../src/server/gameserver/quest/PropertyBuffer.h \
 ../../../../src/server/gameserver/Sector.h \
 ../../../../src/server/gameserver/Party.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/server/gameserver/PCManager.h \
 ../../../../src/server/gameserver/CreatureManager.h \
   \
  \
 ../../../../src/Core/PCVampireInfo.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h \
 ../../../../src/Core/VampireSkillInfo.h \
 ../../../../src/Core/PCSkillInfo.h \
 ../../../../src/Core/SubVampireSkillInfo.h \
 ../../../../src/server/gameserver/CreatureUtil.h \
 ../../../../src/server/gameserver/skill/VampireSkillSlot.h \
 ../../../../src/server/gameserver/skill/Skill.h \
 ../../../../src/Core/Gpackets/GCModifyInformation.h
GCAddGearToInventoryHandler.o: GCAddGearToInventoryHandler.cpp \
 GCAddGearToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddGearToZone.o: GCAddGearToZone.cpp GCAddGearToZone.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddGearToZoneHandler.o: GCAddGearToZoneHandler.cpp GCAddGearToZone.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddMonster.o: GCAddMonster.cpp GCAddMonster.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCAddMonsterHandler.o: GCAddMonsterHandler.cpp GCAddMonster.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCAddMonsterCorpse.o: GCAddMonsterCorpse.cpp GCAddMonsterCorpse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddMonsterCorpseHandler.o: GCAddMonsterCorpseHandler.cpp \
 GCAddMonsterCorpse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddMonsterFromBurrowing.o: GCAddMonsterFromBurrowing.cpp \
 GCAddMonsterFromBurrowing.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCAddMonsterFromBurrowingHandler.o: \
 GCAddMonsterFromBurrowingHandler.cpp GCAddMonsterFromBurrowing.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCAddMonsterFromTransformation.o: GCAddMonsterFromTransformation.cpp \
 GCAddMonsterFromTransformation.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCAddMonsterFromTransformationHandler.o: \
 GCAddMonsterFromTransformationHandler.cpp \
 GCAddMonsterFromTransformation.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCAddInstalledMineToZone.o: GCAddInstalledMineToZone.cpp \
 GCAddInstalledMineToZone.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h GCAddItemToZone.h \
 ../../../../src/Core/Assert.h
GCAddInstalledMineToZoneHandler.o: GCAddInstalledMineToZoneHandler.cpp \
 GCAddInstalledMineToZone.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h GCAddItemToZone.h
GCAddItemToInventory.o: GCAddItemToInventory.cpp \
 GCAddItemToInventory.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddItemToZone.o: GCAddItemToZone.cpp GCAddItemToZone.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
GCAddNewItemToZone.o: GCAddNewItemToZone.cpp GCAddNewItemToZone.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h GCAddItemToZone.h \
 ../../../../src/Core/Assert.h
GCAddNewItemToZoneHandler.o: GCAddNewItemToZoneHandler.cpp \
 GCAddNewItemToZone.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h GCAddItemToZone.h
GCAddNPC.o: GCAddNPC.cpp GCAddNPC.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddNPCHandler.o: GCAddNPCHandler.cpp GCAddNPC.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddSlayer.o: GCAddSlayer.cpp GCAddSlayer.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h  \
 ../../../../src/Core/EffectInfo.h
GCAddSlayerHandler.o: GCAddSlayerHandler.cpp GCAddSlayer.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h  \
 ../../../../src/Core/EffectInfo.h
GCAddSlayerCorpse.o: GCAddSlayerCorpse.cpp GCAddSlayerCorpse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h 
GCAddSlayerCorpseHandler.o: GCAddSlayerCorpseHandler.cpp \
 GCAddSlayerCorpse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h 
GCAddVampire.o: GCAddVampire.cpp GCAddVampire.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/EffectInfo.h
GCAddVampireHandler.o: GCAddVampireHandler.cpp GCAddVampire.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/EffectInfo.h
GCAddVampireCorpse.o: GCAddVampireCorpse.cpp GCAddVampireCorpse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h
GCAddVampireCorpseHandler.o: GCAddVampireCorpseHandler.cpp \
 GCAddVampireCorpse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h
GCAddVampireFromBurrowing.o: GCAddVampireFromBurrowing.cpp \
 GCAddVampireFromBurrowing.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/EffectInfo.h
GCAddVampireFromBurrowingHandler.o: \
 GCAddVampireFromBurrowingHandler.cpp GCAddVampireFromBurrowing.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/EffectInfo.h
GCAddVampireFromTransformation.o: GCAddVampireFromTransformation.cpp \
 GCAddVampireFromTransformation.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/EffectInfo.h
GCAddVampireFromTransformationHandler.o: \
 GCAddVampireFromTransformationHandler.cpp \
 GCAddVampireFromTransformation.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCVampireInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/EffectInfo.h
GCAddWolf.o: GCAddWolf.cpp GCAddWolf.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddWolfHandler.o: GCAddWolfHandler.cpp GCAddWolf.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddInjuriousCreature.o: GCAddInjuriousCreature.cpp \
 GCAddInjuriousCreature.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddInjuriousCreatureHandler.o: GCAddInjuriousCreatureHandler.cpp \
 GCAddInjuriousCreature.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK1.o: GCAttackArmsOK1.cpp GCAttackArmsOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK1Handler.o: GCAttackArmsOK1Handler.cpp GCAttackArmsOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK2.o: GCAttackArmsOK2.cpp GCAttackArmsOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK2Handler.o: GCAttackArmsOK2Handler.cpp GCAttackArmsOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK3.o: GCAttackArmsOK3.cpp GCAttackArmsOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK3Handler.o: GCAttackArmsOK3Handler.cpp GCAttackArmsOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK4.o: GCAttackArmsOK4.cpp GCAttackArmsOK4.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK4Handler.o: GCAttackArmsOK4Handler.cpp GCAttackArmsOK4.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK5.o: GCAttackArmsOK5.cpp GCAttackArmsOK5.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackArmsOK5Handler.o: GCAttackArmsOK5Handler.cpp GCAttackArmsOK5.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackMeleeOK1.o: GCAttackMeleeOK1.cpp GCAttackMeleeOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackMeleeOK1Handler.o: GCAttackMeleeOK1Handler.cpp \
 GCAttackMeleeOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackMeleeOK2.o: GCAttackMeleeOK2.cpp GCAttackMeleeOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackMeleeOK2Handler.o: GCAttackMeleeOK2Handler.cpp \
 GCAttackMeleeOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackMeleeOK3.o: GCAttackMeleeOK3.cpp GCAttackMeleeOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackMeleeOK3Handler.o: GCAttackMeleeOK3Handler.cpp \
 GCAttackMeleeOK3.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttack.o: GCAttack.cpp GCAttack.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAttackHandler.o: GCAttackHandler.cpp GCAttack.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCBloodDrainOK1.o: GCBloodDrainOK1.cpp GCBloodDrainOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCBloodDrainOK1Handler.o: GCBloodDrainOK1Handler.cpp GCBloodDrainOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCBloodDrainOK2.o: GCBloodDrainOK2.cpp GCBloodDrainOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCBloodDrainOK2Handler.o: GCBloodDrainOK2Handler.cpp GCBloodDrainOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCBloodDrainOK3.o: GCBloodDrainOK3.cpp GCBloodDrainOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCBloodDrainOK3Handler.o: GCBloodDrainOK3Handler.cpp GCBloodDrainOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCannotAdd.o: GCCannotAdd.cpp GCCannotAdd.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCannotAddHandler.o: GCCannotAddHandler.cpp GCCannotAdd.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCannotUse.o: GCCannotUse.cpp GCCannotUse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCannotUseHandler.o: GCCannotUseHandler.cpp GCCannotUse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeShape.o: GCChangeShape.cpp GCChangeShape.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeShapeHandler.o: GCChangeShapeHandler.cpp GCChangeShape.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeWeather.o: GCChangeWeather.cpp GCChangeWeather.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeWeatherHandler.o: GCChangeWeatherHandler.cpp GCChangeWeather.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCreateItem.o: GCCreateItem.cpp GCCreateItem.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCreateItemHandler.o: GCCreateItemHandler.cpp GCCreateItem.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCreatureDied.o: GCCreatureDied.cpp GCCreatureDied.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCreatureDiedHandler.o: GCCreatureDiedHandler.cpp GCCreatureDied.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCrossCounterOK1.o: GCCrossCounterOK1.cpp GCCrossCounterOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCrossCounterOK1Handler.o: GCCrossCounterOK1Handler.cpp \
 GCCrossCounterOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCrossCounterOK2.o: GCCrossCounterOK2.cpp GCCrossCounterOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCrossCounterOK2Handler.o: GCCrossCounterOK2Handler.cpp \
 GCCrossCounterOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCrossCounterOK3.o: GCCrossCounterOK3.cpp GCCrossCounterOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCrossCounterOK3Handler.o: GCCrossCounterOK3Handler.cpp \
 GCCrossCounterOK3.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteandPickUpOK.o: GCDeleteandPickUpOK.cpp GCDeleteandPickUpOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteandPickUpOKHandler.o: GCDeleteandPickUpOKHandler.cpp \
 GCDeleteandPickUpOK.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteEffectFromTile.o: GCDeleteEffectFromTile.cpp \
 GCDeleteEffectFromTile.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteEffectFromTileHandler.o: GCDeleteEffectFromTileHandler.cpp \
 GCDeleteEffectFromTile.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeDarkLight.o: GCChangeDarkLight.cpp GCChangeDarkLight.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeDarkLightHandler.o: GCChangeDarkLightHandler.cpp \
 GCChangeDarkLight.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCChangeInventoryItemNum.o: GCChangeInventoryItemNum.cpp \
 GCChangeInventoryItemNum.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCastingSkill.o: GCCastingSkill.cpp GCCastingSkill.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCCastingSkillHandler.o: GCCastingSkillHandler.cpp GCCastingSkill.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteInventoryItem.o: GCDeleteInventoryItem.cpp \
 GCDeleteInventoryItem.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteInventoryItemHandler.o: GCDeleteInventoryItemHandler.cpp \
 GCDeleteInventoryItem.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteObject.o: GCDeleteObject.cpp GCDeleteObject.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDeleteObjectHandler.o: GCDeleteObjectHandler.cpp GCDeleteObject.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveCorpseHead.o: GCRemoveCorpseHead.cpp GCRemoveCorpseHead.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveCorpseHeadHandler.o: GCRemoveCorpseHeadHandler.cpp \
 GCRemoveCorpseHead.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveInjuriousCreature.o: GCRemoveInjuriousCreature.cpp \
 GCRemoveInjuriousCreature.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveInjuriousCreatureHandler.o: \
 GCRemoveInjuriousCreatureHandler.cpp GCRemoveInjuriousCreature.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDisconnect.o: GCDisconnect.cpp GCDisconnect.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDisconnectHandler.o: GCDisconnectHandler.cpp GCDisconnect.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCDropItemToZone.o: GCDropItemToZone.cpp GCDropItemToZone.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h GCAddItemToZone.h \
 ../../../../src/Core/Assert.h
GCDropItemToZoneHandler.o: GCDropItemToZoneHandler.cpp \
 GCDropItemToZone.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h GCAddItemToZone.h
GCFastMove.o: GCFastMove.cpp GCFastMove.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCFastMoveHandler.o: GCFastMoveHandler.cpp GCFastMove.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Player.h
GCFakeMove.o: GCFakeMove.cpp GCFakeMove.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCFakeMoveHandler.o: GCFakeMoveHandler.cpp GCFakeMove.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Player.h
GCGetDamage.o: GCGetDamage.cpp GCGetDamage.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetDamageHandler.o: GCGetDamageHandler.cpp GCGetDamage.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetOffMotorCycle.o: GCGetOffMotorCycle.cpp GCGetOffMotorCycle.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetOffMotorCycleHandler.o: GCGetOffMotorCycleHandler.cpp \
 GCGetOffMotorCycle.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetOffMotorCycleOK.o: GCGetOffMotorCycleOK.cpp \
 GCGetOffMotorCycleOK.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetOffMotorCycleOKHandler.o: GCGetOffMotorCycleOKHandler.cpp \
 GCGetOffMotorCycleOK.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetOffMotorCycleFailed.o: GCGetOffMotorCycleFailed.cpp \
 GCGetOffMotorCycleFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGetOffMotorCycleFailedHandler.o: GCGetOffMotorCycleFailedHandler.cpp \
 GCGetOffMotorCycleFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGlobalChat.o: GCGlobalChat.cpp GCGlobalChat.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGlobalChatHandler.o: GCGlobalChatHandler.cpp GCGlobalChat.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCHPRecoveryStartToSelf.o: GCHPRecoveryStartToSelf.cpp \
 GCHPRecoveryStartToSelf.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCHPRecoveryStartToSelfHandler.o: GCHPRecoveryStartToSelfHandler.cpp \
 GCHPRecoveryStartToSelf.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCHPRecoveryStartToOthers.o: GCHPRecoveryStartToOthers.cpp \
 GCHPRecoveryStartToOthers.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCHPRecoveryStartToOthersHandler.o: \
 GCHPRecoveryStartToOthersHandler.cpp GCHPRecoveryStartToOthers.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCHPRecoveryEndToSelf.o: GCHPRecoveryEndToSelf.cpp \
 GCHPRecoveryEndToSelf.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCHPRecoveryEndToSelfHandler.o: GCHPRecoveryEndToSelfHandler.cpp \
 GCHPRecoveryEndToSelf.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCHPRecoveryEndToOthers.o: GCHPRecoveryEndToOthers.cpp \
 GCHPRecoveryEndToOthers.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCHPRecoveryEndToOthersHandler.o: GCHPRecoveryEndToOthersHandler.cpp \
 GCHPRecoveryEndToOthers.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCKnockBack.o: GCKnockBack.cpp GCKnockBack.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnockBackHandler.o: GCKnockBackHandler.cpp GCKnockBack.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnocksTargetBackOK1.o: GCKnocksTargetBackOK1.cpp \
 GCKnocksTargetBackOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/ModifyItemInfo.h
GCKnocksTargetBackOK1Handler.o: GCKnocksTargetBackOK1Handler.cpp \
 GCKnocksTargetBackOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/ModifyItemInfo.h
GCKnocksTargetBackOK2.o: GCKnocksTargetBackOK2.cpp \
 GCKnocksTargetBackOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnocksTargetBackOK2Handler.o: GCKnocksTargetBackOK2Handler.cpp \
 GCKnocksTargetBackOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnocksTargetBackOK4.o: GCKnocksTargetBackOK4.cpp \
 GCKnocksTargetBackOK4.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnocksTargetBackOK4Handler.o: GCKnocksTargetBackOK4Handler.cpp \
 GCKnocksTargetBackOK4.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnocksTargetBackOK5.o: GCKnocksTargetBackOK5.cpp \
 GCKnocksTargetBackOK5.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCKnocksTargetBackOK5Handler.o: GCKnocksTargetBackOK5Handler.cpp \
 GCKnocksTargetBackOK5.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLearnSkillFailed.o: GCLearnSkillFailed.cpp GCLearnSkillFailed.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLearnSkillFailedHandler.o: GCLearnSkillFailedHandler.cpp \
 GCLearnSkillFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLearnSkillOK.o: GCLearnSkillOK.cpp GCLearnSkillOK.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLearnSkillOKHandler.o: GCLearnSkillOKHandler.cpp GCLearnSkillOK.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLearnSkillReady.o: GCLearnSkillReady.cpp GCLearnSkillReady.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLearnSkillReadyHandler.o: GCLearnSkillReadyHandler.cpp \
 GCLearnSkillReady.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLightning.o: GCLightning.cpp GCLightning.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCLightningHandler.o: GCLightningHandler.cpp GCLightning.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMakeItemOK.o: GCMakeItemOK.cpp GCMakeItemOK.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h GCChangeInventoryItemNum.h \
 GCAddItemToInventory.h ../../../../src/Core/ModifyInfo.h
GCMakeItemOKHandler.o: GCMakeItemOKHandler.cpp GCMakeItemOK.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h GCChangeInventoryItemNum.h \
 GCAddItemToInventory.h ../../../../src/Core/ModifyInfo.h
GCMakeItemFail.o: GCMakeItemFail.cpp GCMakeItemFail.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h GCChangeInventoryItemNum.h \
 ../../../../src/Core/ModifyInfo.h
GCMakeItemFailHandler.o: GCMakeItemFailHandler.cpp GCMakeItemFail.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h GCChangeInventoryItemNum.h \
 ../../../../src/Core/ModifyInfo.h
GCMineExplosionOK1.o: GCMineExplosionOK1.cpp GCMineExplosionOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMineExplosionOK1Handler.o: GCMineExplosionOK1Handler.cpp \
 GCMineExplosionOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMineExplosionOK2.o: GCMineExplosionOK2.cpp GCMineExplosionOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMineExplosionOK2Handler.o: GCMineExplosionOK2Handler.cpp \
 GCMineExplosionOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCModifyInformation.o: GCModifyInformation.cpp GCModifyInformation.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/ModifyInfo.h
GCModifyInformationHandler.o: GCModifyInformationHandler.cpp \
 GCModifyInformation.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/ModifyInfo.h
GCMorph1.o: GCMorph1.cpp GCMorph1.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GameTime.h \
 ../../../../src/Core/PCSlayerInfo2.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h
GCMorph1Handler.o: GCMorph1Handler.cpp GCMorph1.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GameTime.h \
 ../../../../src/Core/PCSlayerInfo2.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h
GCMorphVampire2.o: GCMorphVampire2.cpp GCMorphVampire2.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h  \
 ../../../../src/Core/PCVampireInfo3.h
GCMorphVampire2Handler.o: GCMorphVampire2Handler.cpp GCMorphVampire2.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h  \
 ../../../../src/Core/PCVampireInfo3.h
GCMorphSlayer2.o: GCMorphSlayer2.cpp GCMorphSlayer2.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h  \
 ../../../../src/Core/PCVampireInfo3.h
GCMorphSlayer2Handler.o: GCMorphSlayer2Handler.cpp GCMorphSlayer2.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSlayerInfo3.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/Assert.h  \
 ../../../../src/Core/PCVampireInfo3.h
GCMove.o: GCMove.cpp GCMove.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMoveHandler.o: GCMoveHandler.cpp GCMove.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Player.h
GCMoveError.o: GCMoveError.cpp GCMoveError.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
GCMoveErrorHandler.o: GCMoveErrorHandler.cpp GCMoveError.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMoveOK.o: GCMoveOK.cpp GCMoveOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
GCMoveOKHandler.o: GCMoveOKHandler.cpp GCMoveOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMPRecoveryStart.o: GCMPRecoveryStart.cpp GCMPRecoveryStart.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMPRecoveryStartHandler.o: GCMPRecoveryStartHandler.cpp \
 GCMPRecoveryStart.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCMPRecoveryEnd.o: GCMPRecoveryEnd.cpp GCMPRecoveryEnd.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCMPRecoveryEndHandler.o: GCMPRecoveryEndHandler.cpp GCMPRecoveryEnd.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCReconnect.o: GCReconnect.cpp GCReconnect.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCReconnectHandler.o: GCReconnectHandler.cpp GCReconnect.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCReconnectLogin.o: GCReconnectLogin.cpp GCReconnectLogin.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCReconnectLoginHandler.o: GCReconnectLoginHandler.cpp \
 GCReconnectLogin.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveEffect.o: GCRemoveEffect.cpp GCRemoveEffect.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveEffectHandler.o: GCRemoveEffectHandler.cpp GCRemoveEffect.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveFromGear.o: GCRemoveFromGear.cpp GCRemoveFromGear.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRemoveFromGearHandler.o: GCRemoveFromGearHandler.cpp \
 GCRemoveFromGear.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRideMotorCycle.o: GCRideMotorCycle.cpp GCRideMotorCycle.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRideMotorCycleHandler.o: GCRideMotorCycleHandler.cpp \
 GCRideMotorCycle.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRideMotorCycleOK.o: GCRideMotorCycleOK.cpp GCRideMotorCycleOK.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRideMotorCycleOKHandler.o: GCRideMotorCycleOKHandler.cpp \
 GCRideMotorCycleOK.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRideMotorCycleFailed.o: GCRideMotorCycleFailed.cpp \
 GCRideMotorCycleFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRideMotorCycleFailedHandler.o: GCRideMotorCycleFailedHandler.cpp \
 GCRideMotorCycleFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSay.o: GCSay.cpp GCSay.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSayHandler.o: GCSayHandler.cpp GCSay.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSetPosition.o: GCSetPosition.cpp GCSetPosition.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSetPositionHandler.o: GCSetPositionHandler.cpp GCSetPosition.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillFailed1.o: GCSkillFailed1.cpp GCSkillFailed1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillFailed1Handler.o: GCSkillFailed1Handler.cpp GCSkillFailed1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillFailed2.o: GCSkillFailed2.cpp GCSkillFailed2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillFailed2Handler.o: GCSkillFailed2Handler.cpp GCSkillFailed2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToInventoryOK1.o: GCSkillToInventoryOK1.cpp \
 GCSkillToInventoryOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToInventoryOK1Handler.o: GCSkillToInventoryOK1Handler.cpp \
 GCSkillToInventoryOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToInventoryOK2.o: GCSkillToInventoryOK2.cpp \
 GCSkillToInventoryOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToInventoryOK2Handler.o: GCSkillToInventoryOK2Handler.cpp \
 GCSkillToInventoryOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK1.o: GCSkillToObjectOK1.cpp GCSkillToObjectOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK1Handler.o: GCSkillToObjectOK1Handler.cpp \
 GCSkillToObjectOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK2.o: GCSkillToObjectOK2.cpp GCSkillToObjectOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK2Handler.o: GCSkillToObjectOK2Handler.cpp \
 GCSkillToObjectOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK3.o: GCSkillToObjectOK3.cpp GCSkillToObjectOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK3Handler.o: GCSkillToObjectOK3Handler.cpp \
 GCSkillToObjectOK3.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK4.o: GCSkillToObjectOK4.cpp GCSkillToObjectOK4.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK4Handler.o: GCSkillToObjectOK4Handler.cpp \
 GCSkillToObjectOK4.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK5.o: GCSkillToObjectOK5.cpp GCSkillToObjectOK5.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK5Handler.o: GCSkillToObjectOK5Handler.cpp \
 GCSkillToObjectOK5.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK6.o: GCSkillToObjectOK6.cpp GCSkillToObjectOK6.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToObjectOK6Handler.o: GCSkillToObjectOK6Handler.cpp \
 GCSkillToObjectOK6.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToSelfOK1.o: GCSkillToSelfOK1.cpp GCSkillToSelfOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToSelfOK1Handler.o: GCSkillToSelfOK1Handler.cpp \
 GCSkillToSelfOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToSelfOK2.o: GCSkillToSelfOK2.cpp GCSkillToSelfOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToSelfOK2Handler.o: GCSkillToSelfOK2Handler.cpp \
 GCSkillToSelfOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToSelfOK3.o: GCSkillToSelfOK3.cpp GCSkillToSelfOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToSelfOK3Handler.o: GCSkillToSelfOK3Handler.cpp \
 GCSkillToSelfOK3.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK1.o: GCSkillToTileOK1.cpp GCSkillToTileOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK1Handler.o: GCSkillToTileOK1Handler.cpp \
 GCSkillToTileOK1.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK2.o: GCSkillToTileOK2.cpp GCSkillToTileOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK2Handler.o: GCSkillToTileOK2Handler.cpp \
 GCSkillToTileOK2.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK3.o: GCSkillToTileOK3.cpp GCSkillToTileOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK3Handler.o: GCSkillToTileOK3Handler.cpp \
 GCSkillToTileOK3.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK4.o: GCSkillToTileOK4.cpp GCSkillToTileOK4.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK4Handler.o: GCSkillToTileOK4Handler.cpp \
 GCSkillToTileOK4.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK5.o: GCSkillToTileOK5.cpp GCSkillToTileOK5.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK5Handler.o: GCSkillToTileOK5Handler.cpp \
 GCSkillToTileOK5.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK6.o: GCSkillToTileOK6.cpp GCSkillToTileOK6.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillToTileOK6Handler.o: GCSkillToTileOK6Handler.cpp \
 GCSkillToTileOK6.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSystemMessage.o: GCSystemMessage.cpp GCSystemMessage.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSystemMessageHandler.o: GCSystemMessageHandler.cpp GCSystemMessage.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTakeOff.o: GCTakeOff.cpp GCTakeOff.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTakeOffHandler.o: GCTakeOffHandler.cpp GCTakeOff.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowItemOK1.o: GCThrowItemOK1.cpp GCThrowItemOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowItemOK1Handler.o: GCThrowItemOK1Handler.cpp GCThrowItemOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowItemOK2.o: GCThrowItemOK2.cpp GCThrowItemOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowItemOK2Handler.o: GCThrowItemOK2Handler.cpp GCThrowItemOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowItemOK3.o: GCThrowItemOK3.cpp GCThrowItemOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowItemOK3Handler.o: GCThrowItemOK3Handler.cpp GCThrowItemOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowBombOK1.o: GCThrowBombOK1.cpp GCThrowBombOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowBombOK1Handler.o: GCThrowBombOK1Handler.cpp GCThrowBombOK1.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowBombOK2.o: GCThrowBombOK2.cpp GCThrowBombOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowBombOK2Handler.o: GCThrowBombOK2Handler.cpp GCThrowBombOK2.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowBombOK3.o: GCThrowBombOK3.cpp GCThrowBombOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCThrowBombOK3Handler.o: GCThrowBombOK3Handler.cpp GCThrowBombOK3.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUpdateInfo.o: GCUpdateInfo.cpp GCUpdateInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GameTime.h \
 ../../../../src/Core/PCSlayerInfo2.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h \
 ../../../../src/Core/EffectInfo.h \
 ../../../../src/Core/RideMotorcycleInfo.h \
 ../../../../src/Core/RideMotorcycleSlotInfo.h \
 ../../../../src/Core/NPCInfo.h
GCUpdateInfoHandler.o: GCUpdateInfoHandler.cpp GCUpdateInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GameTime.h \
 ../../../../src/Core/PCSlayerInfo2.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h \
 ../../../../src/Core/EffectInfo.h \
 ../../../../src/Core/RideMotorcycleInfo.h \
 ../../../../src/Core/RideMotorcycleSlotInfo.h \
 ../../../../src/Core/NPCInfo.h
GCUnburrowOK.o: GCUnburrowOK.cpp GCUnburrowOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUnburrowOKHandler.o: GCUnburrowOKHandler.cpp GCUnburrowOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUnburrowFail.o: GCUnburrowFail.cpp GCUnburrowFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUnburrowFailHandler.o: GCUnburrowFailHandler.cpp GCUnburrowFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUntransformOK.o: GCUntransformOK.cpp GCUntransformOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUntransformOKHandler.o: GCUntransformOKHandler.cpp GCUntransformOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUntransformFail.o: GCUntransformFail.cpp GCUntransformFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUntransformFailHandler.o: GCUntransformFailHandler.cpp \
 GCUntransformFail.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUseBonusPointFail.o: GCUseBonusPointFail.cpp GCUseBonusPointFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUseBonusPointFailHandler.o: GCUseBonusPointFailHandler.cpp \
 GCUseBonusPointFail.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCUseBonusPointOK.o: GCUseBonusPointOK.cpp GCUseBonusPointOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/PacketFactory.h
GCUseBonusPointOKHandler.o: GCUseBonusPointOKHandler.cpp \
 GCUseBonusPointOK.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/PacketFactory.h
GCUseOK.o: GCUseOK.cpp GCUseOK.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/PacketFactory.h
GCUseOKHandler.o: GCUseOKHandler.cpp GCUseOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/PacketFactory.h
GCReloadOK.o: GCReloadOK.cpp GCReloadOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/PacketFactory.h
GCReloadOKHandler.o: GCReloadOKHandler.cpp GCReloadOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/PacketFactory.h
GLIncomingConnection.o: GLIncomingConnection.cpp \
 GLIncomingConnection.h ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GLIncomingConnectionHandler.o: GLIncomingConnectionHandler.cpp \
 GLIncomingConnection.h ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Properties.h  \
   \
 
GLIncomingConnectionError.o: GLIncomingConnectionError.cpp \
 GLIncomingConnectionError.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GLIncomingConnectionErrorHandler.o: \
 GLIncomingConnectionErrorHandler.cpp GLIncomingConnectionError.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GLIncomingConnectionOK.o: GLIncomingConnectionOK.cpp \
 GLIncomingConnectionOK.h ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GLIncomingConnectionOKHandler.o: GLIncomingConnectionOKHandler.cpp \
 GLIncomingConnectionOK.h ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GCNPCSay.o: GCNPCSay.cpp GCNPCSay.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCSayHandler.o: GCNPCSayHandler.cpp GCNPCSay.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCAsk.o: GCNPCAsk.cpp GCNPCAsk.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCAskHandler.o: GCNPCAskHandler.cpp GCNPCAsk.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopVersion.o: GCShopVersion.cpp GCShopVersion.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopVersionHandler.o: GCShopVersionHandler.cpp GCShopVersion.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopList.o: GCShopList.cpp GCShopList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/server/gameserver/Item.h \
 ../../../../src/server/gameserver/Object.h \
 ../../../../src/server/gameserver/Effect.h \
 ../../../../src/server/Timeval.h  \
   \
   \
 ../../../../src/server/gameserver/EffectManager.h \
 ../../../../src/Core/EffectInfo.h  \
   \
  
GCShopListHandler.o: GCShopListHandler.cpp GCShopList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopListMysterious.o: GCShopListMysterious.cpp \
 GCShopListMysterious.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/server/gameserver/Item.h \
 ../../../../src/server/gameserver/Object.h \
 ../../../../src/server/gameserver/Effect.h \
 ../../../../src/server/Timeval.h  \
   \
   \
 ../../../../src/server/gameserver/EffectManager.h \
 ../../../../src/Core/EffectInfo.h  \
   \
  
GCShopListMysteriousHandler.o: GCShopListMysteriousHandler.cpp \
 GCShopListMysterious.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopBuyOK.o: GCShopBuyOK.cpp GCShopBuyOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopBuyOKHandler.o: GCShopBuyOKHandler.cpp GCShopBuyOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopBuyFail.o: GCShopBuyFail.cpp GCShopBuyFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopBuyFailHandler.o: GCShopBuyFailHandler.cpp GCShopBuyFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopSold.o: GCShopSold.cpp GCShopSold.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopSoldHandler.o: GCShopSoldHandler.cpp GCShopSold.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopBought.o: GCShopBought.cpp GCShopBought.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopBoughtHandler.o: GCShopBoughtHandler.cpp GCShopBought.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopSellFail.o: GCShopSellFail.cpp GCShopSellFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopSellFailHandler.o: GCShopSellFailHandler.cpp GCShopSellFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopSellOK.o: GCShopSellOK.cpp GCShopSellOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopSellOKHandler.o: GCShopSellOKHandler.cpp GCShopSellOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShopMarketCondition.o: GCShopMarketCondition.cpp \
 GCShopMarketCondition.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShopMarketConditionHandler.o: GCShopMarketConditionHandler.cpp \
 GCShopMarketCondition.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneConnected.o: GCPhoneConnected.cpp GCPhoneConnected.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneConnectedHandler.o: GCPhoneConnectedHandler.cpp \
 GCPhoneConnected.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRing.o: GCRing.cpp GCRing.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRingHandler.o: GCRingHandler.cpp GCRing.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneDisconnected.o: GCPhoneDisconnected.cpp GCPhoneDisconnected.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneDisconnectedHandler.o: GCPhoneDisconnectedHandler.cpp \
 GCPhoneDisconnected.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneConnectionFailed.o: GCPhoneConnectionFailed.cpp \
 GCPhoneConnectionFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneConnectionFailedHandler.o: GCPhoneConnectionFailedHandler.cpp \
 GCPhoneConnectionFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneSay.o: GCPhoneSay.cpp GCPhoneSay.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPhoneSayHandler.o: GCPhoneSayHandler.cpp GCPhoneSay.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCWhisper.o: GCWhisper.cpp GCWhisper.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCWhisperHandler.o: GCWhisperHandler.cpp GCWhisper.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCWhisperFailed.o: GCWhisperFailed.cpp GCWhisperFailed.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCWhisperFailedHandler.o: GCWhisperFailedHandler.cpp GCWhisperFailed.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTeachSkillInfo.o: GCTeachSkillInfo.cpp GCTeachSkillInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTeachSkillInfoHandler.o: GCTeachSkillInfoHandler.cpp \
 GCTeachSkillInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSkillInfo.o: GCSkillInfo.cpp GCSkillInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSkillInfo.h \
 ../../../../src/Core/SlayerSkillInfo.h \
 ../../../../src/Core/SubSlayerSkillInfo.h \
 ../../../../src/Core/VampireSkillInfo.h \
 ../../../../src/Core/SubVampireSkillInfo.h \
 ../../../../src/Core/Assert.h
GCSkillInfoHandler.o: GCSkillInfoHandler.cpp GCSkillInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/PCSkillInfo.h \
 ../../../../src/Core/SlayerSkillInfo.h \
 ../../../../src/Core/SubSlayerSkillInfo.h \
 ../../../../src/Core/VampireSkillInfo.h \
 ../../../../src/Core/SubVampireSkillInfo.h \
 ../../../../src/Core/Assert.h
GCStatusCurrentHP.o: GCStatusCurrentHP.cpp GCStatusCurrentHP.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCStatusCurrentHPHandler.o: GCStatusCurrentHPHandler.cpp \
 GCStatusCurrentHP.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/EffectInfo.h
GCSearchMotorcycleOK.o: GCSearchMotorcycleOK.cpp \
 GCSearchMotorcycleOK.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCSearchMotorcycleOKHandler.o: GCSearchMotorcycleOKHandler.cpp \
 GCSearchMotorcycleOK.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSearchMotorcycleFail.o: GCSearchMotorcycleFail.cpp \
 GCSearchMotorcycleFail.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCSearchMotorcycleFailHandler.o: GCSearchMotorcycleFailHandler.cpp \
 GCSearchMotorcycleFail.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRealWearingInfo.o: GCRealWearingInfo.cpp GCRealWearingInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRealWearingInfoHandler.o: GCRealWearingInfoHandler.cpp \
 GCRealWearingInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCStashList.o: GCStashList.cpp GCStashList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h
GCStashListHandler.o: GCStashListHandler.cpp GCStashList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h
GCStashSell.o: GCStashSell.cpp GCStashSell.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCStashSellHandler.o: GCStashSellHandler.cpp GCStashSell.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradePrepare.o: GCTradePrepare.cpp GCTradePrepare.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradePrepareHandler.o: GCTradePrepareHandler.cpp GCTradePrepare.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeAddItem.o: GCTradeAddItem.cpp GCTradeAddItem.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h
GCTradeAddItemHandler.o: GCTradeAddItemHandler.cpp GCTradeAddItem.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/SubItemInfo.h
GCTradeRemoveItem.o: GCTradeRemoveItem.cpp GCTradeRemoveItem.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeRemoveItemHandler.o: GCTradeRemoveItemHandler.cpp \
 GCTradeRemoveItem.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeMoney.o: GCTradeMoney.cpp GCTradeMoney.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeMoneyHandler.o: GCTradeMoneyHandler.cpp GCTradeMoney.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeFinish.o: GCTradeFinish.cpp GCTradeFinish.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeFinishHandler.o: GCTradeFinishHandler.cpp GCTradeFinish.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeError.o: GCTradeError.cpp GCTradeError.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeErrorHandler.o: GCTradeErrorHandler.cpp GCTradeError.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeVerify.o: GCTradeVerify.cpp GCTradeVerify.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCTradeVerifyHandler.o: GCTradeVerifyHandler.cpp GCTradeVerify.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCVisibleOK.o: GCVisibleOK.cpp GCVisibleOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCVisibleOKHandler.o: GCVisibleOKHandler.cpp GCVisibleOK.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCVisibleFail.o: GCVisibleFail.cpp GCVisibleFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCVisibleFailHandler.o: GCVisibleFailHandler.cpp GCVisibleFail.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCResponse.o: GCNPCResponse.cpp GCNPCResponse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCResponseHandler.o: GCNPCResponseHandler.cpp GCNPCResponse.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCSayDynamic.o: GCNPCSayDynamic.cpp GCNPCSayDynamic.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCSayDynamicHandler.o: GCNPCSayDynamicHandler.cpp GCNPCSayDynamic.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCAskDynamic.o: GCNPCAskDynamic.cpp GCNPCAskDynamic.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNPCAskDynamicHandler.o: GCNPCAskDynamicHandler.cpp GCNPCAskDynamic.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddHelicopter.o: GCAddHelicopter.cpp GCAddHelicopter.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddHelicopterHandler.o: GCAddHelicopterHandler.cpp GCAddHelicopter.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddVampirePortal.o: GCAddVampirePortal.cpp GCAddVampirePortal.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddVampirePortalHandler.o: GCAddVampirePortalHandler.cpp \
 GCAddVampirePortal.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCEnterVampirePortal.o: GCEnterVampirePortal.cpp \
 GCEnterVampirePortal.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCEnterVampirePortalHandler.o: GCEnterVampirePortalHandler.cpp \
 GCEnterVampirePortal.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyInvite.o: GCPartyInvite.cpp GCPartyInvite.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyInviteHandler.o: GCPartyInviteHandler.cpp GCPartyInvite.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyJoined.o: GCPartyJoined.cpp GCPartyJoined.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCPartyJoinedHandler.o: GCPartyJoinedHandler.cpp GCPartyJoined.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyLeave.o: GCPartyLeave.cpp GCPartyLeave.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyLeaveHandler.o: GCPartyLeaveHandler.cpp GCPartyLeave.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyError.o: GCPartyError.cpp GCPartyError.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCPartyErrorHandler.o: GCPartyErrorHandler.cpp GCPartyError.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRequestedIP.o: GCRequestedIP.cpp GCRequestedIP.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRequestedIPHandler.o: GCRequestedIPHandler.cpp GCRequestedIP.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRequestFailed.o: GCRequestFailed.cpp GCRequestFailed.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRequestFailedHandler.o: GCRequestFailedHandler.cpp GCRequestFailed.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GMServerInfo.o: GMServerInfo.cpp GMServerInfo.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GMServerInfoHandler.o: GMServerInfoHandler.cpp GMServerInfo.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Properties.h  \
   \
 
GCOtherModifyInfo.o: GCOtherModifyInfo.cpp GCOtherModifyInfo.h \
 ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCOtherModifyInfoHandler.o: GCOtherModifyInfoHandler.cpp \
 GCOtherModifyInfo.h ../../../../src/Core/ModifyInfo.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GLKickVerify.o: GLKickVerify.cpp GLKickVerify.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GLKickVerifyHandler.o: GLKickVerifyHandler.cpp GLKickVerify.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GSAddGuild.o: GSAddGuild.cpp GSAddGuild.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSAddGuildHandler.o: GSAddGuildHandler.cpp GSAddGuild.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShowGuildRegist.o: GCShowGuildRegist.cpp GCShowGuildRegist.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShowGuildRegistHandler.o: GCShowGuildRegistHandler.cpp \
 GCShowGuildRegist.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCWaitGuildList.o: GCWaitGuildList.cpp GCWaitGuildList.h \
   \
   \
   \
   \
   \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GuildInfo.h
GCWaitGuildListHandler.o: GCWaitGuildListHandler.cpp GCWaitGuildList.h \
   \
   \
   \
   \
   \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GuildInfo.h
GCShowGuildInfo.o: GCShowGuildInfo.cpp GCShowGuildInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShowGuildInfoHandler.o: GCShowGuildInfoHandler.cpp GCShowGuildInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShowWaitGuildInfo.o: GCShowWaitGuildInfo.cpp GCShowWaitGuildInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h  \
 
GCShowWaitGuildInfoHandler.o: GCShowWaitGuildInfoHandler.cpp \
 GCShowWaitGuildInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h  \
 
GGCommand.o: GGCommand.cpp GGCommand.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GGCommandHandler.o: GGCommandHandler.cpp GGCommand.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GSAddGuildMember.o: GSAddGuildMember.cpp GSAddGuildMember.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSAddGuildMemberHandler.o: GSAddGuildMemberHandler.cpp \
 GSAddGuildMember.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GSAddGuildMember.o: GSAddGuildMember.cpp GSAddGuildMember.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSAddGuildMemberHandler.o: GSAddGuildMemberHandler.cpp \
 GSAddGuildMember.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCShowMessageBox.o: GCShowMessageBox.cpp GCShowMessageBox.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShowMessageBoxHandler.o: GCShowMessageBoxHandler.cpp \
 GCShowMessageBox.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCModifyMoney.o: GCModifyMoney.cpp GCModifyMoney.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCModifyMoneyHandler.o: GCModifyMoneyHandler.cpp GCModifyMoney.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCActiveGuildList.o: GCActiveGuildList.cpp GCActiveGuildList.h \
   \
   \
   \
   \
   \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GuildInfo.h
GCActiveGuildListHandler.o: GCActiveGuildListHandler.cpp \
 GCActiveGuildList.h  \
   \
   \
   \
   \
  \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GuildInfo.h
GCShowGuildJoin.o: GCShowGuildJoin.cpp GCShowGuildJoin.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShowGuildJoinHandler.o: GCShowGuildJoinHandler.cpp GCShowGuildJoin.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSQuitGuild.o: GSQuitGuild.cpp GSQuitGuild.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSQuitGuildHandler.o: GSQuitGuildHandler.cpp GSQuitGuild.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCGuildMemberList.o: GCGuildMemberList.cpp GCGuildMemberList.h \
   \
   \
   \
   \
   \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GuildMemberInfo.h
GCGuildMemberListHandler.o: GCGuildMemberListHandler.cpp \
 GCGuildMemberList.h  \
   \
   \
   \
   \
  \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GuildMemberInfo.h
GCShowGuildMemberInfo.o: GCShowGuildMemberInfo.cpp \
 GCShowGuildMemberInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCShowGuildMemberInfoHandler.o: GCShowGuildMemberInfoHandler.cpp \
 GCShowGuildMemberInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSExpelGuildMember.o: GSExpelGuildMember.cpp GSExpelGuildMember.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSExpelGuildMemberHandler.o: GSExpelGuildMemberHandler.cpp \
 GSExpelGuildMember.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GSModifyGuildMember.o: GSModifyGuildMember.cpp GSModifyGuildMember.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSModifyGuildMemberHandler.o: GSModifyGuildMemberHandler.cpp \
 GSModifyGuildMember.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCGuildChat.o: GCGuildChat.cpp GCGuildChat.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCGuildChatHandler.o: GCGuildChatHandler.cpp GCGuildChat.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GGGuildChat.o: GGGuildChat.cpp GGGuildChat.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GGGuildChatHandler.o: GGGuildChatHandler.cpp GGGuildChat.h \
 ../../../../src/Core/DatagramPacket.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/Datagram.h \
 ../../../../src/Core/PacketFactory.h
GCAddItemToItemVerify.o: GCAddItemToItemVerify.cpp \
 GCAddItemToItemVerify.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCAddItemToItemVerifyHandler.o: GCAddItemToItemVerifyHandler.cpp \
 GCAddItemToItemVerify.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSRequestGuildInfo.o: GSRequestGuildInfo.cpp GSRequestGuildInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSRequestGuildInfoHandler.o: GSRequestGuildInfoHandler.cpp \
 GSRequestGuildInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCModifyGuildMemberInfo.o: GCModifyGuildMemberInfo.cpp \
 GCModifyGuildMemberInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCModifyGuildMemberInfoHandler.o: GCModifyGuildMemberInfoHandler.cpp \
 GCModifyGuildMemberInfo.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNoticeEvent.o: GCNoticeEvent.cpp GCNoticeEvent.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCNoticeEventHandler.o: GCNoticeEventHandler.cpp GCNoticeEvent.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSModifyGuildIntro.o: GSModifyGuildIntro.cpp GSModifyGuildIntro.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSModifyGuildIntroHandler.o: GSModifyGuildIntroHandler.cpp \
 GSModifyGuildIntro.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GSGuildMemberLogOn.o: GSGuildMemberLogOn.cpp GSGuildMemberLogOn.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GSGuildMemberLogOnHandler.o: GSGuildMemberLogOnHandler.cpp \
 GSGuildMemberLogOn.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCSelectRankBonusOK.o: GCSelectRankBonusOK.cpp GCSelectRankBonusOK.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSelectRankBonusOKHandler.o: GCSelectRankBonusOKHandler.cpp \
 GCSelectRankBonusOK.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSelectRankBonusFailed.o: GCSelectRankBonusFailed.cpp \
 GCSelectRankBonusFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCSelectRankBonusFailedHandler.o: GCSelectRankBonusFailedHandler.cpp \
 GCSelectRankBonusFailed.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCRankBonusInfo.o: GCRankBonusInfo.cpp GCRankBonusInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCRankBonusInfoHandler.o: GCRankBonusInfoHandler.cpp GCRankBonusInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCNPCInfo.o: GCNPCInfo.cpp GCNPCInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GameTime.h \
 ../../../../src/Core/PCSlayerInfo2.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h \
 ../../../../src/Core/EffectInfo.h \
 ../../../../src/Core/RideMotorcycleInfo.h \
 ../../../../src/Core/RideMotorcycleSlotInfo.h \
 ../../../../src/Core/NPCInfo.h
GCNPCInfoHandler.o: GCNPCInfoHandler.cpp GCNPCInfo.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/GameTime.h \
 ../../../../src/Core/PCSlayerInfo2.h \
 ../../../../src/Core/PCInfo.h \
 ../../../../src/Core/PCVampireInfo2.h \
 ../../../../src/Core/InventoryInfo.h \
 ../../../../src/Core/InventorySlotInfo.h \
 ../../../../src/Core/PCItemInfo.h \
 ../../../../src/Core/SubItemInfo.h \
 ../../../../src/Core/Assert.h \
 ../../../../src/Core/GearInfo.h \
 ../../../../src/Core/GearSlotInfo.h \
 ../../../../src/Core/ExtraInfo.h \
 ../../../../src/Core/ExtraSlotInfo.h \
 ../../../../src/Core/EffectInfo.h \
 ../../../../src/Core/RideMotorcycleInfo.h \
 ../../../../src/Core/RideMotorcycleSlotInfo.h \
 ../../../../src/Core/NPCInfo.h
GCNPCAskVariable.o: GCNPCAskVariable.cpp GCNPCAskVariable.h \
   \
   \
   \
   \
   \
  \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/ScriptParameter.h
GCNPCAskVariableHandler.o: GCNPCAskVariableHandler.cpp \
 GCNPCAskVariable.h  \
   \
   \
   \
   \
   \
  \
  \
  \
   \
   \
   \
   \
   \
    \
   \
   \
   \
  \
  \
  \
   \
    \
   \
  \
   \
   \
   \
   \
   \
   \
  ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
   \
   \
   \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/ScriptParameter.h
GCWarScheduleList.o: GCWarScheduleList.cpp GCWarScheduleList.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Assert.h
GCWarScheduleListHandler.o: GCWarScheduleListHandler.cpp \
 GCWarScheduleList.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h
GCFriendChatting.o: GCFriendChatting.cpp GCFriendChatting.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Gpackets/GCFriendChatting.h
GCFriendChattingHandler.o: GCFriendChattingHandler.cpp GCFriendChatting.h \
 ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h \
 ../../../../src/Core/Gpackets/GCFriendChatting.h
