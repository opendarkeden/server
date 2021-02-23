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
#VSHOME  = /home/darkeden/sigitest/pt
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
DEFS     = -D__LINUX__ -D_REENTRANT -D__LOGIN_SERVER__ 
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(LSDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR)

CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

TARGET_GS  = $(LIBDIR)/libGameServerPackets.a
TARGET_LS  = $(LIBDIR)/libLoginServerPackets.a
TARGET_SS  = $(LIBDIR)/libSharedServerPackets.a

TARGET = $(TARGET_LS)

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
CGAttack.o: CGAttack.cpp CGAttack.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
CGAttackHandler.o: CGAttackHandler.cpp CGAttack.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGAddGearToMouse.o: CGAddGearToMouse.cpp CGAddGearToMouse.h \
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
CGAddGearToMouseHandler.o: CGAddGearToMouseHandler.cpp \
 CGAddGearToMouse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddInventoryToMouse.o: CGAddInventoryToMouse.cpp \
 CGAddInventoryToMouse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddInventoryToMouseHandler.o: CGAddInventoryToMouseHandler.cpp \
 CGAddInventoryToMouse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddMouseToGear.o: CGAddMouseToGear.cpp CGAddMouseToGear.h \
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
CGAddMouseToGearHandler.o: CGAddMouseToGearHandler.cpp \
 CGAddMouseToGear.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddMouseToInventory.o: CGAddMouseToInventory.cpp \
 CGAddMouseToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddMouseToInventoryHandler.o: CGAddMouseToInventoryHandler.cpp \
 CGAddMouseToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddMouseToQuickSlot.o: CGAddMouseToQuickSlot.cpp \
 CGAddMouseToQuickSlot.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddMouseToQuickSlotHandler.o: CGAddMouseToQuickSlotHandler.cpp \
 CGAddMouseToQuickSlot.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddMouseToZone.o: CGAddMouseToZone.cpp CGAddMouseToZone.h \
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
CGAddMouseToZoneHandler.o: CGAddMouseToZoneHandler.cpp \
 CGAddMouseToZone.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddQuickSlotToMouse.o: CGAddQuickSlotToMouse.cpp \
 CGAddQuickSlotToMouse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddQuickSlotToMouseHandler.o: CGAddQuickSlotToMouseHandler.cpp \
 CGAddQuickSlotToMouse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddZoneToInventory.o: CGAddZoneToInventory.cpp \
 CGAddZoneToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddZoneToInventoryHandler.o: CGAddZoneToInventoryHandler.cpp \
 CGAddZoneToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGAddZoneToMouse.o: CGAddZoneToMouse.cpp CGAddZoneToMouse.h \
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
CGAddZoneToMouseHandler.o: CGAddZoneToMouseHandler.cpp \
 CGAddZoneToMouse.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGBloodDrain.o: CGBloodDrain.cpp CGBloodDrain.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGBloodDrainHandler.o: CGBloodDrainHandler.cpp CGBloodDrain.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGCastingSkill.o: CGCastingSkill.cpp CGCastingSkill.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGCastingSkillHandler.o: CGCastingSkillHandler.cpp CGCastingSkill.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGConnect.o: CGConnect.cpp CGConnect.h \
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
CGConnectHandler.o: CGConnectHandler.cpp CGConnect.h \
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
CLReconnectLogin.o: CLReconnectLogin.cpp CLReconnectLogin.h \
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
CLReconnectLoginHandler.o: CLReconnectLoginHandler.cpp \
 CLReconnectLogin.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGDissectionCorpse.o: CGDissectionCorpse.cpp CGDissectionCorpse.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
CGDissectionCorpseHandler.o: CGDissectionCorpseHandler.cpp \
 CGDissectionCorpse.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGGlobalChat.o: CGGlobalChat.cpp CGGlobalChat.h \
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
CGGlobalChatHandler.o: CGGlobalChatHandler.cpp CGGlobalChat.h \
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
CGLearnSkill.o: CGLearnSkill.cpp CGLearnSkill.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGLearnSkillHandler.o: CGLearnSkillHandler.cpp CGLearnSkill.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGLogout.o: CGLogout.cpp CGLogout.h \
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
CGLogoutHandler.o: CGLogoutHandler.cpp CGLogout.h \
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
CGMakeItem.o: CGMakeItem.cpp CGMakeItem.h \
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
CGMakeItemHandler.o: CGMakeItemHandler.cpp CGMakeItem.h \
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
CGMove.o: CGMove.cpp CGMove.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGMoveHandler.o: CGMoveHandler.cpp CGMove.h \
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
CGReady.o: CGReady.cpp CGReady.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGReadyHandler.o: CGReadyHandler.cpp CGReady.h \
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
CGReloadFromInventory.o: CGReloadFromInventory.cpp \
 CGReloadFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGReloadFromInventoryHandler.o: CGReloadFromInventoryHandler.cpp \
 CGReloadFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGReloadFromQuickSlot.o: CGReloadFromQuickSlot.cpp \
 CGReloadFromQuickSlot.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGReloadFromQuickSlotHandler.o: CGReloadFromQuickSlotHandler.cpp \
 CGReloadFromQuickSlot.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGRideMotorCycle.o: CGRideMotorCycle.cpp CGRideMotorCycle.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGRideMotorCycleHandler.o: CGRideMotorCycleHandler.cpp \
 CGRideMotorCycle.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGGetOffMotorCycle.o: CGGetOffMotorCycle.cpp CGGetOffMotorCycle.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGGetOffMotorCycleHandler.o: CGGetOffMotorCycleHandler.cpp \
 CGGetOffMotorCycle.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSay.o: CGSay.cpp CGSay.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGSayHandler.o: CGSayHandler.cpp CGSay.h \
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
CGSkillToInventory.o: CGSkillToInventory.cpp CGSkillToInventory.h \
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
CGSkillToInventoryHandler.o: CGSkillToInventoryHandler.cpp \
 CGSkillToInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGSelectPortal.o: CGSelectPortal.cpp CGSelectPortal.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectPortalHandler.o: CGSelectPortalHandler.cpp CGSelectPortal.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGThrowItem.o: CGThrowItem.cpp CGThrowItem.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGThrowItemHandler.o: CGThrowItemHandler.cpp CGThrowItem.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGThrowBomb.o: CGThrowBomb.cpp CGThrowBomb.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGThrowBombHandler.o: CGThrowBombHandler.cpp CGThrowBomb.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGUnburrow.o: CGUnburrow.cpp CGUnburrow.h \
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
CGUnburrowHandler.o: CGUnburrowHandler.cpp CGUnburrow.h \
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
CGUntransform.o: CGUntransform.cpp CGUntransform.h \
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
CGUntransformHandler.o: CGUntransformHandler.cpp CGUntransform.h \
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
CGUseBonusPoint.o: CGUseBonusPoint.cpp CGUseBonusPoint.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGUseBonusPointHandler.o: CGUseBonusPointHandler.cpp CGUseBonusPoint.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGUsePotionFromQuickSlot.o: CGUsePotionFromQuickSlot.cpp \
 CGUsePotionFromQuickSlot.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGUsePotionFromQuickSlotHandler.o: CGUsePotionFromQuickSlotHandler.cpp \
 CGUsePotionFromQuickSlot.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGUsePotionFromInventory.o: CGUsePotionFromInventory.cpp \
 CGUsePotionFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGUsePotionFromInventoryHandler.o: CGUsePotionFromInventoryHandler.cpp \
 CGUsePotionFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGVisible.o: CGVisible.cpp CGVisible.h \
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
CGVisibleHandler.o: CGVisibleHandler.cpp CGVisible.h \
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
CGVerifyTime.o: CGVerifyTime.cpp CGVerifyTime.h \
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
CGVerifyTimeHandler.o: CGVerifyTimeHandler.cpp CGVerifyTime.h \
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
CLCreatePC.o: CLCreatePC.cpp CLCreatePC.h \
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
CLCreatePCHandler.o: CLCreatePCHandler.cpp CLCreatePC.h \
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
CLDeletePC.o: CLDeletePC.cpp CLDeletePC.h \
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
CLDeletePCHandler.o: CLDeletePCHandler.cpp CLDeletePC.h \
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
CLGetPCList.o: CLGetPCList.cpp CLGetPCList.h \
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
CLGetPCListHandler.o: CLGetPCListHandler.cpp CLGetPCList.h \
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
CLLogin.o: CLLogin.cpp CLLogin.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CLLoginHandler.o: CLLoginHandler.cpp CLLogin.h \
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
CLLogout.o: CLLogout.cpp CLLogout.h \
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
CLLogoutHandler.o: CLLogoutHandler.cpp CLLogout.h \
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
CLQueryPlayerID.o: CLQueryPlayerID.cpp CLQueryPlayerID.h \
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
CLQueryPlayerIDHandler.o: CLQueryPlayerIDHandler.cpp CLQueryPlayerID.h \
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
CLQueryCharacterName.o: CLQueryCharacterName.cpp \
 CLQueryCharacterName.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CLQueryCharacterNameHandler.o: CLQueryCharacterNameHandler.cpp \
 CLQueryCharacterName.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CLRegisterPlayer.o: CLRegisterPlayer.cpp CLRegisterPlayer.h \
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
CLRegisterPlayerHandler.o: CLRegisterPlayerHandler.cpp \
 CLRegisterPlayer.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CLSelectPC.o: CLSelectPC.cpp CLSelectPC.h \
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
CLSelectPCHandler.o: CLSelectPCHandler.cpp CLSelectPC.h \
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
CLGetServerList.o: CLGetServerList.cpp CLGetServerList.h \
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
CLGetServerListHandler.o: CLGetServerListHandler.cpp CLGetServerList.h \
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
CLGetWorldList.o: CLGetWorldList.cpp CLGetWorldList.h \
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
CLGetWorldListHandler.o: CLGetWorldListHandler.cpp CLGetWorldList.h \
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
CLChangeServer.o: CLChangeServer.cpp CLChangeServer.h \
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
CLChangeServerHandler.o: CLChangeServerHandler.cpp CLChangeServer.h \
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
CLSelectServer.o: CLSelectServer.cpp CLSelectServer.h \
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
CLSelectServerHandler.o: CLSelectServerHandler.cpp CLSelectServer.h \
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
CLSelectWorld.o: CLSelectWorld.cpp CLSelectWorld.h \
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
CLSelectWorldHandler.o: CLSelectWorldHandler.cpp CLSelectWorld.h \
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
CLVersionCheck.o: CLVersionCheck.cpp CLVersionCheck.h \
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
CLVersionCheckHandler.o: CLVersionCheckHandler.cpp CLVersionCheck.h \
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
CGNPCTalk.o: CGNPCTalk.cpp CGNPCTalk.h \
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
CGNPCTalkHandler.o: CGNPCTalkHandler.cpp CGNPCTalk.h \
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
CGNPCAskAnswer.o: CGNPCAskAnswer.cpp CGNPCAskAnswer.h \
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
CGNPCAskAnswerHandler.o: CGNPCAskAnswerHandler.cpp CGNPCAskAnswer.h \
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
CGShopRequestList.o: CGShopRequestList.cpp CGShopRequestList.h \
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
CGShopRequestListHandler.o: CGShopRequestListHandler.cpp \
 CGShopRequestList.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGShopRequestBuy.o: CGShopRequestBuy.cpp CGShopRequestBuy.h \
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
CGShopRequestBuyHandler.o: CGShopRequestBuyHandler.cpp \
 CGShopRequestBuy.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGShopRequestSell.o: CGShopRequestSell.cpp CGShopRequestSell.h \
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
CGShopRequestSellHandler.o: CGShopRequestSellHandler.cpp \
 CGShopRequestSell.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGDialUp.o: CGDialUp.cpp CGDialUp.h \
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
CGDialUpHandler.o: CGDialUpHandler.cpp CGDialUp.h \
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
CGPhoneDisconnect.o: CGPhoneDisconnect.cpp CGPhoneDisconnect.h \
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
CGPhoneDisconnectHandler.o: CGPhoneDisconnectHandler.cpp \
 CGPhoneDisconnect.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGPhoneSay.o: CGPhoneSay.cpp CGPhoneSay.h \
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
CGPhoneSayHandler.o: CGPhoneSayHandler.cpp CGPhoneSay.h \
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
CGWhisper.o: CGWhisper.cpp CGWhisper.h \
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
CGWhisperHandler.o: CGWhisperHandler.cpp CGWhisper.h \
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
CGPickupMoney.o: CGPickupMoney.cpp CGPickupMoney.h \
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
CGPickupMoneyHandler.o: CGPickupMoneyHandler.cpp CGPickupMoney.h \
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
CGDropMoney.o: CGDropMoney.cpp CGDropMoney.h \
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
CGDropMoneyHandler.o: CGDropMoneyHandler.cpp CGDropMoney.h \
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
CGSetSlayerHotKey.o: CGSetSlayerHotKey.cpp CGSetSlayerHotKey.h \
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
CGSetSlayerHotKeyHandler.o: CGSetSlayerHotKeyHandler.cpp \
 CGSetSlayerHotKey.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGSetVampireHotKey.o: CGSetVampireHotKey.cpp CGSetVampireHotKey.h \
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
CGSetVampireHotKeyHandler.o: CGSetVampireHotKeyHandler.cpp \
 CGSetVampireHotKey.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGRequestRepair.o: CGRequestRepair.cpp CGRequestRepair.h \
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
CGRequestRepairHandler.o: CGRequestRepairHandler.cpp CGRequestRepair.h \
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
CGMouseToStash.o: CGMouseToStash.cpp CGMouseToStash.h \
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
CGMouseToStashHandler.o: CGMouseToStashHandler.cpp CGMouseToStash.h \
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
CGStashList.o: CGStashList.cpp CGStashList.h \
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
CGStashListHandler.o: CGStashListHandler.cpp CGStashList.h \
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
CGStashToMouse.o: CGStashToMouse.cpp CGStashToMouse.h \
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
CGStashToMouseHandler.o: CGStashToMouseHandler.cpp CGStashToMouse.h \
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
CGStashDeposit.o: CGStashDeposit.cpp CGStashDeposit.h \
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
CGStashDepositHandler.o: CGStashDepositHandler.cpp CGStashDeposit.h \
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
CGStashRequestBuy.o: CGStashRequestBuy.cpp CGStashRequestBuy.h \
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
CGStashRequestBuyHandler.o: CGStashRequestBuyHandler.cpp \
 CGStashRequestBuy.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGStashWithdraw.o: CGStashWithdraw.cpp CGStashWithdraw.h \
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
CGStashWithdrawHandler.o: CGStashWithdrawHandler.cpp CGStashWithdraw.h \
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
CGTradePrepare.o: CGTradePrepare.cpp CGTradePrepare.h \
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
CGTradePrepareHandler.o: CGTradePrepareHandler.cpp CGTradePrepare.h \
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
CGTradeAddItem.o: CGTradeAddItem.cpp CGTradeAddItem.h \
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
CGTradeAddItemHandler.o: CGTradeAddItemHandler.cpp CGTradeAddItem.h \
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
CGTradeRemoveItem.o: CGTradeRemoveItem.cpp CGTradeRemoveItem.h \
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
CGTradeRemoveItemHandler.o: CGTradeRemoveItemHandler.cpp \
 CGTradeRemoveItem.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGTradeMoney.o: CGTradeMoney.cpp CGTradeMoney.h \
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
CGTradeMoneyHandler.o: CGTradeMoneyHandler.cpp CGTradeMoney.h \
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
CGTradeFinish.o: CGTradeFinish.cpp CGTradeFinish.h \
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
CGTradeFinishHandler.o: CGTradeFinishHandler.cpp CGTradeFinish.h \
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
CGSkillToObject.o: CGSkillToObject.cpp CGSkillToObject.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
CGSkillToObjectHandler.o: CGSkillToObjectHandler.cpp CGSkillToObject.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSkillToSelf.o: CGSkillToSelf.cpp CGSkillToSelf.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
CGSkillToSelfHandler.o: CGSkillToSelfHandler.cpp CGSkillToSelf.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSkillToTile.o: CGSkillToTile.cpp CGSkillToTile.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
 ../../../../src/Core/SocketEncryptInputStream.h \
 ../../../../src/Core/Encrypter.h \
 ../../../../src/Core/EncryptUtility.h \
 ../../../../src/Core/SocketEncryptOutputStream.h \
 ../../../../src/Core/Assert.h
CGSkillToTileHandler.o: CGSkillToTileHandler.cpp CGSkillToTile.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSilverCoating.o: CGSilverCoating.cpp CGSilverCoating.h \
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
CGSilverCoatingHandler.o: CGSilverCoatingHandler.cpp CGSilverCoating.h \
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
CGRequestNewbieItem.o: CGRequestNewbieItem.cpp CGRequestNewbieItem.h \
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
CGRequestNewbieItemHandler.o: CGRequestNewbieItemHandler.cpp \
 CGRequestNewbieItem.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGUseItemFromInventory.o: CGUseItemFromInventory.cpp \
 CGUseItemFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGUseItemFromInventoryHandler.o: CGUseItemFromInventoryHandler.cpp \
 CGUseItemFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
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
CGSelectWayPoint.o: CGSelectWayPoint.cpp CGSelectWayPoint.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectWayPointHandler.o: CGSelectWayPointHandler.cpp \
 CGSelectWayPoint.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectTileEffect.o: CGSelectTileEffect.cpp CGSelectTileEffect.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectTileEffectHandler.o: CGSelectTileEffectHandler.cpp \
 CGSelectTileEffect.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGPartyInvite.o: CGPartyInvite.cpp CGPartyInvite.h \
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
CGPartyInviteHandler.o: CGPartyInviteHandler.cpp CGPartyInvite.h \
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
CGPartyLeave.o: CGPartyLeave.cpp CGPartyLeave.h \
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
CGPartyLeaveHandler.o: CGPartyLeaveHandler.cpp CGPartyLeave.h \
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
CGResurrect.o: CGResurrect.cpp CGResurrect.h \
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
CGResurrectHandler.o: CGResurrectHandler.cpp CGResurrect.h \
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
CGRequestIP.o: CGRequestIP.cpp CGRequestIP.h \
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
CGRequestIPHandler.o: CGRequestIPHandler.cpp CGRequestIP.h \
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
CGRegistGuild.o: CGRegistGuild.cpp CGRegistGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGRegistGuildHandler.o: CGRegistGuildHandler.cpp CGRegistGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectGuild.o: CGSelectGuild.cpp CGSelectGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectGuildHandler.o: CGSelectGuildHandler.cpp CGSelectGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGTryJoinGuild.o: CGTryJoinGuild.cpp CGTryJoinGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGTryJoinGuildHandler.o: CGTryJoinGuildHandler.cpp CGTryJoinGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGJoinGuild.o: CGJoinGuild.cpp CGJoinGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGJoinGuildHandler.o: CGJoinGuildHandler.cpp CGJoinGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGQuitGuild.o: CGQuitGuild.cpp CGQuitGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGQuitGuildHandler.o: CGQuitGuildHandler.cpp CGQuitGuild.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGRequestGuildMemberList.o: CGRequestGuildMemberList.cpp \
 CGRequestGuildMemberList.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGRequestGuildMemberListHandler.o: CGRequestGuildMemberListHandler.cpp \
 CGRequestGuildMemberList.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectGuildMember.o: CGSelectGuildMember.cpp CGSelectGuildMember.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectGuildMemberHandler.o: CGSelectGuildMemberHandler.cpp \
 CGSelectGuildMember.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGExpelGuildMember.o: CGExpelGuildMember.cpp CGExpelGuildMember.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGExpelGuildMemberHandler.o: CGExpelGuildMemberHandler.cpp \
 CGExpelGuildMember.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGModifyGuildMember.o: CGModifyGuildMember.cpp CGModifyGuildMember.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGModifyGuildMemberHandler.o: CGModifyGuildMemberHandler.cpp \
 CGModifyGuildMember.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGRelicToObject.o: CGRelicToObject.cpp CGRelicToObject.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGRelicToObjectHandler.o: CGRelicToObjectHandler.cpp CGRelicToObject.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGPortCheck.o: CGPortCheck.cpp CGPortCheck.h \
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
CGPortCheckHandler.o: CGPortCheckHandler.cpp CGPortCheck.h \
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
  
CGGuildChat.o: CGGuildChat.cpp CGGuildChat.h \
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
CGGuildChatHandler.o: CGGuildChatHandler.cpp CGGuildChat.h \
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
CGAddItemToItem.o: CGAddItemToItem.cpp CGAddItemToItem.h \
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
CGAddItemToItemHandler.o: CGAddItemToItemHandler.cpp CGAddItemToItem.h \
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
CGRequestInfo.o: CGRequestInfo.cpp CGRequestInfo.h \
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
CGRequestInfoHandler.o: CGRequestInfoHandler.cpp CGRequestInfo.h \
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
CGModifyGuildIntro.o: CGModifyGuildIntro.cpp CGModifyGuildIntro.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGModifyGuildIntroHandler.o: CGModifyGuildIntroHandler.cpp \
 CGModifyGuildIntro.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGModifyGuildMemberIntro.o: CGModifyGuildMemberIntro.cpp \
 CGModifyGuildMemberIntro.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGModifyGuildMemberIntroHandler.o: CGModifyGuildMemberIntroHandler.cpp \
 CGModifyGuildMemberIntro.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSkillToNamed.o: CGSkillToNamed.cpp CGSkillToNamed.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSkillToNamedHandler.o: CGSkillToNamedHandler.cpp CGSkillToNamed.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectRankBonus.o: CGSelectRankBonus.cpp CGSelectRankBonus.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGSelectRankBonusHandler.o: CGSelectRankBonusHandler.cpp \
 CGSelectRankBonus.h ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGUseMessageItemFromInventory.o: CGUseMessageItemFromInventory.cpp \
 CGUseMessageItemFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h CGUseItemFromInventory.h \
 ../../../../src/Core/Assert.h
CGUseMessageItemFromInventoryHandler.o: \
 CGUseMessageItemFromInventoryHandler.cpp \
 CGUseMessageItemFromInventory.h ../../../../src/Core/Packet.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
 ../../../../src/Core/types/ItemTypes.h \
 ../../../../src/Core/types/ZoneTypes.h \
 ../../../../src/Core/types/QuestTypes.h \
 ../../../../src/Core/types/ShopTypes.h \
 ../../../../src/Core/types/GuildTypes.h \
 ../../../../src/Core/types/WarTypes.h \
 ../../../../src/Core/Utility.h \
 ../../../../src/Core/Exception.h \
 ../../../../src/Core/StringStream.h  \
  \
 ../../../../src/Core/SocketInputStream.h \
 ../../../../src/Core/Socket.h \
 ../../../../src/Core/SocketImpl.h \
 ../../../../src/Core/SocketAPI.h \
 ../../../../src/Core/SocketOutputStream.h \
 ../../../../src/Core/PacketFactory.h CGUseItemFromInventory.h
CGWithdrawTax.o: CGWithdrawTax.cpp CGWithdrawTax.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGWithdrawTaxHandler.o: CGWithdrawTaxHandler.cpp CGWithdrawTax.h \
 ../../../../src/Core/Types.h \
 ../../../../src/Core/types/SystemTypes.h \
   \
   \
   \
   \
  \
  \
   \
    \
  \
   \
   \
   \
  \
  \
    \
   \
   \
   \
   \
    \
   \
   \
   \
   \
   \
  \
  \
   \
   \
  \
  \
   \
   \
   \
   \
   \
  \
 ../../../../src/Core/types/PlayerTypes.h \
 ../../../../src/Core/types/ObjectTypes.h \
 ../../../../src/Core/types/CreatureTypes.h \
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
CGConnectSetKey.o: CGConnectSetKey.cpp CGConnectSetKey.h \
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
CGConnectSetKeyHandler.o: CGConnectSetKeyHandler.cpp CGConnectSetKey.h \
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
