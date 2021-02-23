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

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

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

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)
# DO NOT DELETE
ItemIDRegistry.o: ItemIDRegistry.cpp ../../database/DB.h \
 ../../database/DatabaseManager.h ../../../Core/Types.h \
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
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h \
 /usr/include/sys/time.h ../ItemInfoManager.h ../Item.h ../Object.h \
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h ../EffectManager.h \
 ../../../Core/EffectInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h /usr/include/STL/bitset \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 Motorcycle.h ../ItemFactory.h ../ItemLoader.h Potion.h \
 ../ConcreteItem.h ../ItemPolicies.h Water.h HolyWater.h Magazine.h \
 BombMaterial.h ETC.h Key.h Ring.h Bracelet.h Necklace.h Coat.h \
 Trouser.h Shoes.h Sword.h Blade.h Shield.h Cross.h Mace.h Glove.h \
 Helm.h SG.h SMG.h AR.h SR.h Bomb.h Mine.h Belt.h LearningItem.h \
 Money.h VampireRing.h VampireBracelet.h VampireNecklace.h \
 VampireCoat.h Skull.h Serum.h VampireETC.h SlayerPortalItem.h \
 VampirePortalItem.h EventGiftBox.h EventStar.h VampireEarring.h \
 Relic.h VampireWeapon.h VampireAmulet.h QuestItem.h EventTree.h \
 EventETC.h BloodBible.h CastleSymbol.h CoupleRing.h CoupleRingBase.h \
 VampireCoupleRing.h EventItem.h DyePotion.h ResurrectItem.h \
 MixingItem.h OustersArmsband.h OustersBoots.h OustersChakram.h \
 OustersCirclet.h OustersCoat.h OustersPendent.h OustersRing.h \
 OustersStone.h OustersWristlet.h Larva.h Pupa.h ComposMei.h \
 OustersSummonItem.h EffectItem.h CodeSheet.h MoonCard.h Sweeper.h \
 PetItem.h ../../../Core/PetInfo.h ../../../Core/types/PetTypes.h \
 ../../../Core/VSDateTime.h PetFood.h PetEnchantItem.h LuckyBag.h \
 SMSItem.h CoreZap.h ../OptionInfo.h TrapItem.h WarItem.h \
 CarryingReceiver.h ShoulderArmor.h Dermis.h Persona.h Fascia.h \
 Mitten.h
AR.o: AR.cpp AR.h ../ConcreteItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../ItemInfoManager.h \
 ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Belt.o: Belt.cpp Belt.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Blade.o: Blade.cpp Blade.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Bomb.o: Bomb.cpp Bomb.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
BombMaterial.o: BombMaterial.cpp BombMaterial.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Bracelet.o: Bracelet.cpp Bracelet.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Coat.o: Coat.cpp Coat.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Cross.o: Cross.cpp Cross.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Mace.o: Mace.cpp Mace.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
ETC.o: ETC.cpp ETC.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Glove.o: Glove.cpp Glove.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Sword.o: Sword.cpp Sword.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Helm.o: Helm.cpp Helm.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
HolyWater.o: HolyWater.cpp HolyWater.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Key.o: Key.cpp Key.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemFactoryManager.h ../ItemUtil.h
LearningItem.o: LearningItem.cpp LearningItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Magazine.o: Magazine.cpp Magazine.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Mine.o: Mine.cpp Mine.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Money.o: Money.cpp Money.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Motorcycle.o: Motorcycle.cpp Motorcycle.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 ../Stash.h ../ItemUtil.h
Necklace.o: Necklace.cpp Necklace.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Potion.o: Potion.cpp Potion.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h ../ZoneGroupManager.h \
 /usr/include/STL/map /usr/include/STL/stl_tree.h \
 /usr/include/STL/stl_map.h /usr/include/STL/stl_multimap.h \
 ../ZoneGroup.h ../../../Core/GameTime.h \
 ../../../Core/Gpackets/GMServerInfo.h ../../../Core/DatagramPacket.h \
 ../../../Core/Datagram.h
Ring.o: Ring.cpp Ring.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
SG.o: SG.cpp SG.h ../ConcreteItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../ItemInfoManager.h \
 ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
SMG.o: SMG.cpp SMG.h ../ConcreteItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../ItemInfoManager.h \
 ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Shield.o: Shield.cpp Shield.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Shoes.o: Shoes.cpp Shoes.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
SR.o: SR.cpp SR.h ../ConcreteItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../ItemInfoManager.h \
 ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Trouser.o: Trouser.cpp Trouser.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
VampireBracelet.o: VampireBracelet.cpp VampireBracelet.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
VampireRing.o: VampireRing.cpp VampireRing.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
VampireNecklace.o: VampireNecklace.cpp VampireNecklace.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
VampireCoat.o: VampireCoat.cpp VampireCoat.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Water.o: Water.cpp Water.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
Skull.o: Skull.cpp Skull.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
Serum.o: Serum.cpp Serum.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
VampireETC.o: VampireETC.cpp VampireETC.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
SlayerPortalItem.o: SlayerPortalItem.cpp SlayerPortalItem.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
VampirePortalItem.o: VampirePortalItem.cpp VampirePortalItem.h \
 ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h ../skill/EffectVampirePortal.h \
 ../EffectLoader.h
EventGiftBox.o: EventGiftBox.cpp EventGiftBox.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
EventStar.o: EventStar.cpp EventStar.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
VampireEarring.o: VampireEarring.cpp VampireEarring.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Relic.o: Relic.cpp Relic.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
VampireWeapon.o: VampireWeapon.cpp VampireWeapon.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
VampireAmulet.o: VampireAmulet.cpp VampireAmulet.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
QuestItem.o: QuestItem.cpp QuestItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
Gun.o: Gun.cpp Gun.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemUtil.h \
 ../../../Core/PCItemInfo.h ../../../Core/SubItemInfo.h
EventTree.o: EventTree.cpp EventTree.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
EventETC.o: EventETC.cpp EventETC.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h OustersArmsband.h Motorcycle.h \
 ../Stash.h ../ItemUtil.h
BloodBible.o: BloodBible.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h BloodBible.h ../Item.h ../Object.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/STL/fstream \
 /usr/include/STL/fstream.h /usr/include/STL/string \
 /usr/include/STL/stl_config.h /usr/include/STL/stl_string_fwd.h \
 /usr/include/STL/stl_alloc.h \
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
 /usr/include/STL/char_traits.h /usr/include/STL/stl_hash_fun.h \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../../../Core/Assert.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
CastleSymbol.o: CastleSymbol.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h CastleSymbol.h ../Item.h ../Object.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/STL/fstream \
 /usr/include/STL/fstream.h /usr/include/STL/string \
 /usr/include/STL/stl_config.h /usr/include/STL/stl_string_fwd.h \
 /usr/include/STL/stl_alloc.h \
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
 /usr/include/STL/char_traits.h /usr/include/STL/stl_hash_fun.h \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../../../Core/Assert.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
CoupleRing.o: CoupleRing.cpp CoupleRing.h CoupleRingBase.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h ../FlagSet.h \
 ../couple/CoupleManager.h
VampireCoupleRing.o: VampireCoupleRing.cpp VampireCoupleRing.h \
 CoupleRingBase.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h ../FlagSet.h \
 ../couple/CoupleManager.h
CoupleRingBase.o: CoupleRingBase.cpp CoupleRingBase.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h CoupleRing.h ../ItemInfo.h \
 ../InfoClassManager.h ../ItemFactory.h ../ItemLoader.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 VampireCoupleRing.h ../ItemUtil.h
EventItem.o: EventItem.cpp EventItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
DyePotion.o: DyePotion.cpp DyePotion.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
ResurrectItem.o: ResurrectItem.cpp ResurrectItem.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
MixingItem.o: MixingItem.cpp MixingItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersArmsband.o: OustersArmsband.cpp OustersArmsband.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersBoots.o: OustersBoots.cpp OustersBoots.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersChakram.o: OustersChakram.cpp OustersChakram.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersCirclet.o: OustersCirclet.cpp OustersCirclet.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersCoat.o: OustersCoat.cpp OustersCoat.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersPendent.o: OustersPendent.cpp OustersPendent.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersRing.o: OustersRing.cpp OustersRing.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersStone.o: OustersStone.cpp OustersStone.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
OustersWristlet.o: OustersWristlet.cpp OustersWristlet.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
Larva.o: Larva.cpp Larva.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h ../ZoneGroupManager.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../ZoneGroup.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h
Pupa.o: Pupa.cpp Pupa.h ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h OustersArmsband.h Motorcycle.h \
 ../Stash.h ../ItemUtil.h ../ZoneGroupManager.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../ZoneGroup.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h
ComposMei.o: ComposMei.cpp ComposMei.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h OustersArmsband.h Motorcycle.h \
 ../Stash.h ../ItemUtil.h ../ZoneGroupManager.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../ZoneGroup.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h
OustersSummonItem.o: OustersSummonItem.cpp OustersSummonItem.h \
 ../Item.h ../Object.h ../../../Core/Types.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
EffectItem.o: EffectItem.cpp EffectItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
CodeSheet.o: CodeSheet.cpp CodeSheet.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
MoonCard.o: MoonCard.cpp MoonCard.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
Sweeper.o: Sweeper.cpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h Sweeper.h ../Item.h ../Object.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/STL/fstream \
 /usr/include/STL/fstream.h /usr/include/STL/string \
 /usr/include/STL/stl_config.h /usr/include/STL/stl_string_fwd.h \
 /usr/include/STL/stl_alloc.h \
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
 /usr/include/STL/char_traits.h /usr/include/STL/stl_hash_fun.h \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../../../Core/Assert.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h ../ConcreteItem.h ../ItemInfoManager.h ../ItemPolicies.h \
 Motorcycle.h ../Stash.h ../ItemUtil.h
PetItem.o: PetItem.cpp PetItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../../Core/PetInfo.h ../../../Core/types/PetTypes.h \
 ../../../Core/VSDateTime.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h ../PetUtil.h ../EffectHasPet.h ../GamePlayer.h \
 ../../../Core/Player.h ../../../Core/SocketEncryptOutputStream.h \
 ../../../Core/SocketEncryptInputStream.h /usr/include/STL/deque \
 ../../../Core/PlayerStatus.h ../EventManager.h ../Event.h \
 ../../PaySystem.h ../billing/BillingPlayerInfo.h \
 ../../chinabilling/CBillingPlayerInfo.h \
 ../../chinabilling/CBillingInfo.h \
 ../../../Core/Gpackets/GCReconnectLogin.h ../gameguard/CSAuth.h \
 ../PetTypeInfo.h
PetFood.o: PetFood.cpp PetFood.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../../Core/types/PetTypes.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
PetEnchantItem.o: PetEnchantItem.cpp PetEnchantItem.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../../Core/types/PetTypes.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
LuckyBag.o: LuckyBag.cpp LuckyBag.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
SMSItem.o: SMSItem.cpp SMSItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
CoreZap.o: CoreZap.cpp CoreZap.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../OptionInfo.h ../Slayer.h \
 ../PlayerCreature.h ../Creature.h ../ObjectRegistry.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h /usr/include/STL/slist \
 /usr/include/STL/stl_slist.h ../Zone.h ../Tile.h ../Obstacle.h \
 ../Portal.h ../quest/TriggerManager.h ../quest/Trigger.h \
 ../quest/Condition.h ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /usr/include/STL/stl_deque.h \
 /usr/include/STL/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../../../Core/PCSlayerInfo.h ../../../Core/PCInfo.h \
 ../../../Core/PCSlayerInfo2.h ../../../Core/PCSlayerInfo3.h \
 ../../../Core/InventoryInfo.h ../../../Core/InventorySlotInfo.h \
 ../../../Core/PCItemInfo.h ../../../Core/SubItemInfo.h \
 ../ItemLoaderManager.h ../../../Core/GearInfo.h \
 ../../../Core/GearSlotInfo.h ../../../Core/ExtraInfo.h \
 ../../../Core/ExtraSlotInfo.h ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
TrapItem.o: TrapItem.cpp TrapItem.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h ../ConcreteItem.h \
 ../ItemInfoManager.h ../ItemPolicies.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
WarItem.o: WarItem.cpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h WarItem.h ../Item.h ../Object.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/STL/fstream \
 /usr/include/STL/fstream.h /usr/include/STL/string \
 /usr/include/STL/stl_config.h /usr/include/STL/stl_string_fwd.h \
 /usr/include/STL/stl_alloc.h \
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
 /usr/include/STL/char_traits.h /usr/include/STL/stl_hash_fun.h \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../../../Core/Assert.h ../Effect.h \
 ../../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ItemInfo.h ../InfoClassManager.h \
 ../ItemFactory.h ../ItemLoader.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../ItemInfoManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h
CarryingReceiver.o: CarryingReceiver.cpp CarryingReceiver.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
ShoulderArmor.o: ShoulderArmor.cpp ShoulderArmor.h ../Item.h \
 ../Object.h ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Dermis.o: Dermis.cpp Dermis.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Persona.o: Persona.cpp Persona.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 Belt.h Motorcycle.h ../Stash.h ../ItemUtil.h
Fascia.o: Fascia.cpp Fascia.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
Mitten.o: Mitten.cpp Mitten.h ../Item.h ../Object.h \
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
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset /usr/include/STL/vector \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_bvector.h ../ConcreteItem.h ../ItemInfo.h \
 ../ItemInfoManager.h ../InfoClassManager.h ../../database/DB.h \
 ../../database/DatabaseManager.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../database/Statement.h ../../database/Result.h ../ItemPolicies.h \
 ../ItemFactory.h ../ItemLoader.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../ObjectRegistry.h ../InventorySlot.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /usr/include/STL/stl_deque.h /usr/include/STL/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h Belt.h Motorcycle.h ../Stash.h \
 ../ItemUtil.h
