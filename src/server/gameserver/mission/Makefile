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
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

OBJS = \
	QuestInfo.o \
	MonsterKillQuestInfo.o \
	GatherItemQuestInfo.o \
	MeetNPCQuestInfo.o \
	RewardClass.o \
	RandomRewardClass.o \
	SlayerWeaponRewardClass.o \
	AnotherQuestRewardClass.o \
	RewardInfo.o \
	ItemRewardInfo.o \
	QuestAdvanceRewardInfo.o \
	AnotherQuestRewardInfo.o \
	MiniGameQuestInfo.o \
	QuestInfoManager.o \
	SimpleQuestInfoManager.o \
	EventQuestInfoManager.o \
	RewardClassInfoManager.o \
	SimpleQuestRewardManager.o \
	QuestManager.o \
	QuestStatus.o \
	MonsterKillQuestStatus.o \
	GatherItemQuestStatus.o \
	DummyQuestStatus.o \
	MeetNPCQuestStatus.o \
	MiniGameQuestStatus.o \
	EventQuestAdvance.o \
	EventQuestLootingManager.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(LIBDIR)/libMission.a

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

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)
# DO NOT DELETE
QuestInfo.o: QuestInfo.cpp QuestInfo.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Assert.h RewardClass.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 QuestManager.h QuestStatus.h ../../../Core/VSDateTime.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h EventQuestAdvance.h \
 ../PlayerCreature.h ../Creature.h ../Object.h ../EffectManager.h \
 ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h /usr/include/STL/bitset \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Slayer.h \
 ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /usr/include/STL/stl_deque.h \
 /usr/include/STL/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../../../Core/PCSlayerInfo.h ../../../Core/PCInfo.h \
 ../../../Core/PCSlayerInfo2.h ../../../Core/PCSlayerInfo3.h \
 ../../../Core/InventoryInfo.h ../../../Core/InventorySlotInfo.h \
 ../../../Core/PCItemInfo.h ../../../Core/SubItemInfo.h \
 ../ItemLoaderManager.h ../ItemLoader.h ../../../Core/GearInfo.h \
 ../../../Core/GearSlotInfo.h ../../../Core/ExtraInfo.h \
 ../../../Core/ExtraSlotInfo.h ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h
MonsterKillQuestInfo.o: MonsterKillQuestInfo.cpp \
 MonsterKillQuestInfo.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h QuestInfo.h \
 ../../../Core/Assert.h RewardClass.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 MonsterKillQuestStatus.h QuestStatus.h ../../../Core/VSDateTime.h \
 ../../../Core/Gpackets/GCQuestStatus.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h \
 /usr/include/sys/time.h
GatherItemQuestInfo.o: GatherItemQuestInfo.cpp GatherItemQuestStatus.h \
 QuestStatus.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../Item.h ../Object.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset ../../../Core/Gpackets/GCQuestStatus.h \
 GatherItemQuestInfo.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h /usr/include/STL/slist \
 /usr/include/STL/stl_slist.h
MeetNPCQuestInfo.o: MeetNPCQuestInfo.cpp MeetNPCQuestInfo.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h QuestInfo.h \
 ../../../Core/Assert.h RewardClass.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 MeetNPCQuestStatus.h QuestStatus.h ../../../Core/VSDateTime.h \
 ../../../Core/Gpackets/GCQuestStatus.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h \
 /usr/include/sys/time.h
RewardClass.o: RewardClass.cpp RewardClass.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 RewardInfo.h ../../../Core/Assert.h
RandomRewardClass.o: RandomRewardClass.cpp RandomRewardClass.h \
 RewardClass.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 RewardInfo.h ../../../Core/Assert.h
SlayerWeaponRewardClass.o: SlayerWeaponRewardClass.cpp \
 SlayerWeaponRewardClass.h RewardClass.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 ../PlayerCreature.h ../Creature.h ../Object.h ../../../Core/Assert.h \
 ../EffectManager.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h /usr/include/STL/slist \
 /usr/include/STL/stl_slist.h ../Slayer.h ../Zone.h ../Tile.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h ../ItemLoader.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Ousters.h \
 ../../../Core/PCOustersInfo.h ../../../Core/PCOustersInfo2.h \
 ../../../Core/PCOustersInfo3.h ../../../Core/OustersSkillInfo.h \
 ../../../Core/SubOustersSkillInfo.h ../skill/OustersSkillSlot.h \
 ItemRewardInfo.h RewardInfo.h ../ItemUtil.h
AnotherQuestRewardClass.o: AnotherQuestRewardClass.cpp \
 AnotherQuestRewardClass.h RewardClass.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 RewardInfo.h ../../../Core/Assert.h
RewardInfo.o: RewardInfo.cpp RewardInfo.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h
ItemRewardInfo.o: ItemRewardInfo.cpp ItemRewardInfo.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../Item.h \
 ../Object.h ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h RewardInfo.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/PacketFactory.h \
 RewardClass.h ../PlayerCreature.h ../Creature.h ../ObjectRegistry.h \
 ../../Mutex.h /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/signal.h /usr/include/bits/initspin.h \
 /usr/include/bits/sigthread.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h /usr/include/STL/slist \
 /usr/include/STL/stl_slist.h ../Inventory.h ../VolumeInfo.h \
 ../ItemInfoManager.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactoryManager.h ../ItemFactory.h ../../../Core/Player.h \
 ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /usr/include/STL/stl_deque.h \
 /usr/include/STL/stl_queue.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../ItemUtil.h ../PacketUtil.h \
 ../../../Core/PetInfo.h ../../../Core/types/PetTypes.h \
 ../../../Core/VSDateTime.h ../item/PetItem.h ../ItemLoader.h \
 ../PetTypeInfo.h ../../../Core/Gpackets/GCCreateItem.h
QuestAdvanceRewardInfo.o: QuestAdvanceRewardInfo.cpp \
 QuestAdvanceRewardInfo.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../Item.h \
 ../Object.h ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h RewardInfo.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/PacketFactory.h \
 QuestManager.h QuestInfo.h RewardClass.h QuestStatus.h \
 ../../../Core/VSDateTime.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 EventQuestAdvance.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h
AnotherQuestRewardInfo.o: AnotherQuestRewardInfo.cpp \
 AnotherQuestRewardInfo.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../Item.h \
 ../Object.h ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h RewardInfo.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/PacketFactory.h \
 QuestManager.h QuestInfo.h RewardClass.h QuestStatus.h \
 ../../../Core/VSDateTime.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../PlayerCreature.h ../Creature.h ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h
MiniGameQuestInfo.o: MiniGameQuestInfo.cpp MiniGameQuestInfo.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h QuestInfo.h \
 ../../../Core/Assert.h RewardClass.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 MiniGameQuestStatus.h QuestStatus.h ../../../Core/VSDateTime.h \
 ../../../Core/Gpackets/GCQuestStatus.h
QuestInfoManager.o: QuestInfoManager.cpp QuestInfoManager.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 QuestInfo.h ../../../Core/Assert.h RewardClass.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_bvector.h ItemRewardInfo.h ../Item.h ../Object.h \
 ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h ../EffectManager.h \
 ../../../Core/EffectInfo.h /usr/include/STL/bitset RewardInfo.h \
 MonsterKillQuestInfo.h MonsterKillQuestStatus.h QuestStatus.h \
 ../../../Core/VSDateTime.h ../../../Core/Gpackets/GCQuestStatus.h \
 GatherItemQuestInfo.h GatherItemQuestStatus.h QuestManager.h \
 EventQuestAdvance.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../NPC.h \
 ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /usr/include/STL/stl_deque.h \
 /usr/include/STL/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../couple/PartnerWaitingManager.h ../VariableManager.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h
SimpleQuestInfoManager.o: SimpleQuestInfoManager.cpp \
 SimpleQuestInfoManager.h QuestInfoManager.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 RewardClass.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_bvector.h \
 RewardClassInfoManager.h MonsterKillQuestInfo.h QuestInfo.h \
 ../../../Core/Assert.h MonsterKillQuestStatus.h QuestStatus.h \
 ../../../Core/VSDateTime.h ../../../Core/Gpackets/GCQuestStatus.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h \
 /usr/include/sys/time.h
EventQuestInfoManager.o: EventQuestInfoManager.cpp \
 EventQuestInfoManager.h QuestInfoManager.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 RewardClass.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_bvector.h \
 RewardClassInfoManager.h MonsterKillQuestInfo.h QuestInfo.h \
 ../../../Core/Assert.h MonsterKillQuestStatus.h QuestStatus.h \
 ../../../Core/VSDateTime.h ../../../Core/Gpackets/GCQuestStatus.h \
 GatherItemQuestInfo.h ../Item.h ../Object.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset GatherItemQuestStatus.h MeetNPCQuestInfo.h \
 MeetNPCQuestStatus.h MiniGameQuestInfo.h MiniGameQuestStatus.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h
RewardClassInfoManager.o: RewardClassInfoManager.cpp \
 RewardClassInfoManager.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 RandomRewardClass.h RewardClass.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_bvector.h \
 SlayerWeaponRewardClass.h ItemRewardInfo.h ../Item.h ../Object.h \
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset RewardInfo.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h
SimpleQuestRewardManager.o: SimpleQuestRewardManager.cpp \
 SimpleQuestRewardManager.h RewardClassInfoManager.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h \
 /usr/include/sys/time.h ../Item.h ../Object.h ../../../Core/Assert.h \
 ../Effect.h ../../Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_bvector.h \
 RandomRewardClass.h RewardClass.h SlayerWeaponRewardClass.h \
 ItemRewardInfo.h RewardInfo.h
QuestManager.o: QuestManager.cpp QuestManager.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h QuestInfo.h \
 ../../../Core/Assert.h RewardClass.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_bvector.h \
 QuestStatus.h ../../../Core/VSDateTime.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 MonsterKillQuestStatus.h ../../../Core/Gpackets/GCQuestStatus.h \
 GatherItemQuestStatus.h ../Item.h ../Object.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset MeetNPCQuestStatus.h MiniGameQuestStatus.h \
 QuestInfoManager.h EventQuestAdvance.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h \
 ../../../Core/Player.h ../Monster.h ../MonsterInfo.h \
 ../MonsterSummonInfo.h ../MonsterInfoTypes.h ../Treasure.h \
 ../PrecedenceTable.h ../NPC.h ../Zone.h ../Tile.h ../Obstacle.h \
 ../Portal.h ../quest/TriggerManager.h ../quest/Trigger.h \
 ../quest/Condition.h ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /usr/include/STL/stl_deque.h \
 /usr/include/STL/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../couple/PartnerWaitingManager.h ../VariableManager.h
QuestStatus.o: QuestStatus.cpp QuestStatus.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h QuestManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h
MonsterKillQuestStatus.o: MonsterKillQuestStatus.cpp \
 MonsterKillQuestStatus.h QuestStatus.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../../../Core/Gpackets/GCQuestStatus.h
GatherItemQuestStatus.o: GatherItemQuestStatus.cpp \
 GatherItemQuestStatus.h QuestStatus.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../Item.h ../Object.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 /usr/include/STL/bitset ../../../Core/Gpackets/GCQuestStatus.h \
 QuestInfoManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../PlayerCreature.h ../Creature.h ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Inventory.h \
 ../VolumeInfo.h /usr/include/STL/map /usr/include/STL/stl_tree.h \
 /usr/include/STL/stl_map.h /usr/include/STL/stl_multimap.h
DummyQuestStatus.o: DummyQuestStatus.cpp DummyQuestStatus.h \
 QuestStatus.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../../../Core/Gpackets/GCQuestStatus.h
MeetNPCQuestStatus.o: MeetNPCQuestStatus.cpp MeetNPCQuestStatus.h \
 QuestStatus.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../../../Core/Gpackets/GCQuestStatus.h
MiniGameQuestStatus.o: MiniGameQuestStatus.cpp MiniGameQuestStatus.h \
 QuestStatus.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h QuestInfo.h \
 RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../../../Core/Gpackets/GCQuestStatus.h \
 ../PlayerCreature.h ../Creature.h ../Object.h ../EffectManager.h \
 ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h /usr/include/STL/bitset \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h /usr/include/STL/slist \
 /usr/include/STL/stl_slist.h ../Slayer.h ../Zone.h ../Tile.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h ../ItemLoader.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h ../../../Core/Player.h ../PacketUtil.h \
 ../../../Core/Gpackets/GCMiniGameScores.h
EventQuestAdvance.o: EventQuestAdvance.cpp EventQuestAdvance.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../../Core/Assert.h /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h \
 /usr/include/sys/time.h ../PlayerCreature.h ../Creature.h ../Object.h \
 ../EffectManager.h ../Effect.h ../../Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset ../ObjectRegistry.h ../InventorySlot.h \
 ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h
EventQuestLootingManager.o: EventQuestLootingManager.cpp \
 EventQuestLootingManager.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/bits/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../Item.h \
 ../Object.h ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../Monster.h ../Creature.h \
 ../MonsterInfo.h ../MonsterSummonInfo.h ../MonsterInfoTypes.h \
 ../Treasure.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../PrecedenceTable.h ../ItemFactoryManager.h ../ItemFactory.h \
 ../PlayerCreature.h ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Slayer.h \
 ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /usr/include/STL/stl_deque.h \
 /usr/include/STL/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../../../Core/PCSlayerInfo.h ../../../Core/PCInfo.h \
 ../../../Core/PCSlayerInfo2.h ../../../Core/PCSlayerInfo3.h \
 ../../../Core/InventoryInfo.h ../../../Core/InventorySlotInfo.h \
 ../../../Core/PCItemInfo.h ../../../Core/SubItemInfo.h \
 ../ItemLoaderManager.h ../ItemLoader.h ../../../Core/GearInfo.h \
 ../../../Core/GearSlotInfo.h ../../../Core/ExtraInfo.h \
 ../../../Core/ExtraSlotInfo.h ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h EventQuestAdvance.h QuestManager.h \
 QuestInfo.h RewardClass.h ../../../Core/Gpackets/GCNPCResponse.h \
 QuestStatus.h ../../../Core/VSDateTime.h /usr/include/STL/iosfwd
