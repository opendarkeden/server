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
DEFS     = -D__LINUX__ -D_REENTRANT -D__SHARED_SERVER__ 
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(SSDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR)

CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

TARGET_GS  = $(LIBDIR)/libGameServerPackets.a
TARGET_LS  = $(LIBDIR)/libLoginServerPackets.a
TARGET_SS  = $(LIBDIR)/libSharedServerPackets.a

TARGET = $(TARGET_SS)

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
CGAttack.o: CGAttack.cpp CGAttack.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGAttackHandler.o: CGAttackHandler.cpp CGAttack.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddGearToMouse.o: CGAddGearToMouse.cpp CGAddGearToMouse.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddGearToMouseHandler.o: CGAddGearToMouseHandler.cpp \
 CGAddGearToMouse.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddInventoryToMouse.o: CGAddInventoryToMouse.cpp \
 CGAddInventoryToMouse.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddInventoryToMouseHandler.o: CGAddInventoryToMouseHandler.cpp \
 CGAddInventoryToMouse.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToGear.o: CGAddMouseToGear.cpp CGAddMouseToGear.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToGearHandler.o: CGAddMouseToGearHandler.cpp \
 CGAddMouseToGear.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToInventory.o: CGAddMouseToInventory.cpp \
 CGAddMouseToInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToInventoryHandler.o: CGAddMouseToInventoryHandler.cpp \
 CGAddMouseToInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToQuickSlot.o: CGAddMouseToQuickSlot.cpp \
 CGAddMouseToQuickSlot.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToQuickSlotHandler.o: CGAddMouseToQuickSlotHandler.cpp \
 CGAddMouseToQuickSlot.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddMouseToZone.o: CGAddMouseToZone.cpp CGAddMouseToZone.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGAddMouseToZoneHandler.o: CGAddMouseToZoneHandler.cpp \
 CGAddMouseToZone.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddQuickSlotToMouse.o: CGAddQuickSlotToMouse.cpp \
 CGAddQuickSlotToMouse.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddQuickSlotToMouseHandler.o: CGAddQuickSlotToMouseHandler.cpp \
 CGAddQuickSlotToMouse.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddZoneToInventory.o: CGAddZoneToInventory.cpp \
 CGAddZoneToInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGAddZoneToInventoryHandler.o: CGAddZoneToInventoryHandler.cpp \
 CGAddZoneToInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddZoneToMouse.o: CGAddZoneToMouse.cpp CGAddZoneToMouse.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGAddZoneToMouseHandler.o: CGAddZoneToMouseHandler.cpp \
 CGAddZoneToMouse.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGBloodDrain.o: CGBloodDrain.cpp CGBloodDrain.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGBloodDrainHandler.o: CGBloodDrainHandler.cpp CGBloodDrain.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGCastingSkill.o: CGCastingSkill.cpp CGCastingSkill.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGCastingSkillHandler.o: CGCastingSkillHandler.cpp CGCastingSkill.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGConnect.o: CGConnect.cpp CGConnect.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGConnectHandler.o: CGConnectHandler.cpp CGConnect.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLReconnectLogin.o: CLReconnectLogin.cpp CLReconnectLogin.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLReconnectLoginHandler.o: CLReconnectLoginHandler.cpp \
 CLReconnectLogin.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGDissectionCorpse.o: CGDissectionCorpse.cpp CGDissectionCorpse.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGDissectionCorpseHandler.o: CGDissectionCorpseHandler.cpp \
 CGDissectionCorpse.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGGlobalChat.o: CGGlobalChat.cpp CGGlobalChat.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGGlobalChatHandler.o: CGGlobalChatHandler.cpp CGGlobalChat.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGLearnSkill.o: CGLearnSkill.cpp CGLearnSkill.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGLearnSkillHandler.o: CGLearnSkillHandler.cpp CGLearnSkill.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGLogout.o: CGLogout.cpp CGLogout.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGLogoutHandler.o: CGLogoutHandler.cpp CGLogout.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGMakeItem.o: CGMakeItem.cpp CGMakeItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGMakeItemHandler.o: CGMakeItemHandler.cpp CGMakeItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGMove.o: CGMove.cpp CGMove.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGMoveHandler.o: CGMoveHandler.cpp CGMove.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGReady.o: CGReady.cpp CGReady.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGReadyHandler.o: CGReadyHandler.cpp CGReady.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGReloadFromInventory.o: CGReloadFromInventory.cpp \
 CGReloadFromInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGReloadFromInventoryHandler.o: CGReloadFromInventoryHandler.cpp \
 CGReloadFromInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGReloadFromQuickSlot.o: CGReloadFromQuickSlot.cpp \
 CGReloadFromQuickSlot.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGReloadFromQuickSlotHandler.o: CGReloadFromQuickSlotHandler.cpp \
 CGReloadFromQuickSlot.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRideMotorCycle.o: CGRideMotorCycle.cpp CGRideMotorCycle.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRideMotorCycleHandler.o: CGRideMotorCycleHandler.cpp \
 CGRideMotorCycle.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGGetOffMotorCycle.o: CGGetOffMotorCycle.cpp CGGetOffMotorCycle.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGGetOffMotorCycleHandler.o: CGGetOffMotorCycleHandler.cpp \
 CGGetOffMotorCycle.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSay.o: CGSay.cpp CGSay.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSayHandler.o: CGSayHandler.cpp CGSay.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSkillToInventory.o: CGSkillToInventory.cpp CGSkillToInventory.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGSkillToInventoryHandler.o: CGSkillToInventoryHandler.cpp \
 CGSkillToInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectPortal.o: CGSelectPortal.cpp CGSelectPortal.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectPortalHandler.o: CGSelectPortalHandler.cpp CGSelectPortal.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGThrowItem.o: CGThrowItem.cpp CGThrowItem.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGThrowItemHandler.o: CGThrowItemHandler.cpp CGThrowItem.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGThrowBomb.o: CGThrowBomb.cpp CGThrowBomb.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGThrowBombHandler.o: CGThrowBombHandler.cpp CGThrowBomb.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUnburrow.o: CGUnburrow.cpp CGUnburrow.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUnburrowHandler.o: CGUnburrowHandler.cpp CGUnburrow.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUntransform.o: CGUntransform.cpp CGUntransform.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUntransformHandler.o: CGUntransformHandler.cpp CGUntransform.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUseBonusPoint.o: CGUseBonusPoint.cpp CGUseBonusPoint.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUseBonusPointHandler.o: CGUseBonusPointHandler.cpp CGUseBonusPoint.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUsePotionFromQuickSlot.o: CGUsePotionFromQuickSlot.cpp \
 CGUsePotionFromQuickSlot.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUsePotionFromQuickSlotHandler.o: CGUsePotionFromQuickSlotHandler.cpp \
 CGUsePotionFromQuickSlot.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUsePotionFromInventory.o: CGUsePotionFromInventory.cpp \
 CGUsePotionFromInventory.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGUsePotionFromInventoryHandler.o: CGUsePotionFromInventoryHandler.cpp \
 CGUsePotionFromInventory.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGVisible.o: CGVisible.cpp CGVisible.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGVisibleHandler.o: CGVisibleHandler.cpp CGVisible.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGVerifyTime.o: CGVerifyTime.cpp CGVerifyTime.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGVerifyTimeHandler.o: CGVerifyTimeHandler.cpp CGVerifyTime.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLCreatePC.o: CLCreatePC.cpp CLCreatePC.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /usr/include/STL/bitset
CLCreatePCHandler.o: CLCreatePCHandler.cpp CLCreatePC.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /usr/include/STL/bitset
CLDeletePC.o: CLDeletePC.cpp CLDeletePC.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLDeletePCHandler.o: CLDeletePCHandler.cpp CLDeletePC.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLGetPCList.o: CLGetPCList.cpp CLGetPCList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLGetPCListHandler.o: CLGetPCListHandler.cpp CLGetPCList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLLogin.o: CLLogin.cpp CLLogin.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLLoginHandler.o: CLLoginHandler.cpp CLLogin.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLLogout.o: CLLogout.cpp CLLogout.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLLogoutHandler.o: CLLogoutHandler.cpp CLLogout.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CLQueryPlayerID.o: CLQueryPlayerID.cpp CLQueryPlayerID.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLQueryPlayerIDHandler.o: CLQueryPlayerIDHandler.cpp CLQueryPlayerID.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLQueryCharacterName.o: CLQueryCharacterName.cpp \
 CLQueryCharacterName.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLQueryCharacterNameHandler.o: CLQueryCharacterNameHandler.cpp \
 CLQueryCharacterName.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLRegisterPlayer.o: CLRegisterPlayer.cpp CLRegisterPlayer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLRegisterPlayerHandler.o: CLRegisterPlayerHandler.cpp \
 CLRegisterPlayer.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLSelectPC.o: CLSelectPC.cpp CLSelectPC.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/Player.h
CLSelectPCHandler.o: CLSelectPCHandler.cpp CLSelectPC.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/Player.h
CLGetServerList.o: CLGetServerList.cpp CLGetServerList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLGetServerListHandler.o: CLGetServerListHandler.cpp CLGetServerList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLGetWorldList.o: CLGetWorldList.cpp CLGetWorldList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLGetWorldListHandler.o: CLGetWorldListHandler.cpp CLGetWorldList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLChangeServer.o: CLChangeServer.cpp CLChangeServer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLChangeServerHandler.o: CLChangeServerHandler.cpp CLChangeServer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLSelectServer.o: CLSelectServer.cpp CLSelectServer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLSelectServerHandler.o: CLSelectServerHandler.cpp CLSelectServer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLSelectWorld.o: CLSelectWorld.cpp CLSelectWorld.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLSelectWorldHandler.o: CLSelectWorldHandler.cpp CLSelectWorld.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLVersionCheck.o: CLVersionCheck.cpp CLVersionCheck.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CLVersionCheckHandler.o: CLVersionCheckHandler.cpp CLVersionCheck.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGNPCTalk.o: CGNPCTalk.cpp CGNPCTalk.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGNPCTalkHandler.o: CGNPCTalkHandler.cpp CGNPCTalk.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGNPCAskAnswer.o: CGNPCAskAnswer.cpp CGNPCAskAnswer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGNPCAskAnswerHandler.o: CGNPCAskAnswerHandler.cpp CGNPCAskAnswer.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGShopRequestList.o: CGShopRequestList.cpp CGShopRequestList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGShopRequestListHandler.o: CGShopRequestListHandler.cpp \
 CGShopRequestList.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGShopRequestBuy.o: CGShopRequestBuy.cpp CGShopRequestBuy.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGShopRequestBuyHandler.o: CGShopRequestBuyHandler.cpp \
 CGShopRequestBuy.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGShopRequestSell.o: CGShopRequestSell.cpp CGShopRequestSell.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGShopRequestSellHandler.o: CGShopRequestSellHandler.cpp \
 CGShopRequestSell.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGDialUp.o: CGDialUp.cpp CGDialUp.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGDialUpHandler.o: CGDialUpHandler.cpp CGDialUp.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPhoneDisconnect.o: CGPhoneDisconnect.cpp CGPhoneDisconnect.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPhoneDisconnectHandler.o: CGPhoneDisconnectHandler.cpp \
 CGPhoneDisconnect.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPhoneSay.o: CGPhoneSay.cpp CGPhoneSay.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPhoneSayHandler.o: CGPhoneSayHandler.cpp CGPhoneSay.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGWhisper.o: CGWhisper.cpp CGWhisper.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGWhisperHandler.o: CGWhisperHandler.cpp CGWhisper.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPickupMoney.o: CGPickupMoney.cpp CGPickupMoney.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGPickupMoneyHandler.o: CGPickupMoneyHandler.cpp CGPickupMoney.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGDropMoney.o: CGDropMoney.cpp CGDropMoney.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGDropMoneyHandler.o: CGDropMoneyHandler.cpp CGDropMoney.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSetSlayerHotKey.o: CGSetSlayerHotKey.cpp CGSetSlayerHotKey.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSetSlayerHotKeyHandler.o: CGSetSlayerHotKeyHandler.cpp \
 CGSetSlayerHotKey.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSetVampireHotKey.o: CGSetVampireHotKey.cpp CGSetVampireHotKey.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSetVampireHotKeyHandler.o: CGSetVampireHotKeyHandler.cpp \
 CGSetVampireHotKey.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestRepair.o: CGRequestRepair.cpp CGRequestRepair.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestRepairHandler.o: CGRequestRepairHandler.cpp CGRequestRepair.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGMouseToStash.o: CGMouseToStash.cpp CGMouseToStash.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGMouseToStashHandler.o: CGMouseToStashHandler.cpp CGMouseToStash.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashList.o: CGStashList.cpp CGStashList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashListHandler.o: CGStashListHandler.cpp CGStashList.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashToMouse.o: CGStashToMouse.cpp CGStashToMouse.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashToMouseHandler.o: CGStashToMouseHandler.cpp CGStashToMouse.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashDeposit.o: CGStashDeposit.cpp CGStashDeposit.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashDepositHandler.o: CGStashDepositHandler.cpp CGStashDeposit.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashRequestBuy.o: CGStashRequestBuy.cpp CGStashRequestBuy.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashRequestBuyHandler.o: CGStashRequestBuyHandler.cpp \
 CGStashRequestBuy.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashWithdraw.o: CGStashWithdraw.cpp CGStashWithdraw.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGStashWithdrawHandler.o: CGStashWithdrawHandler.cpp CGStashWithdraw.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradePrepare.o: CGTradePrepare.cpp CGTradePrepare.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradePrepareHandler.o: CGTradePrepareHandler.cpp CGTradePrepare.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeAddItem.o: CGTradeAddItem.cpp CGTradeAddItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeAddItemHandler.o: CGTradeAddItemHandler.cpp CGTradeAddItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeRemoveItem.o: CGTradeRemoveItem.cpp CGTradeRemoveItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeRemoveItemHandler.o: CGTradeRemoveItemHandler.cpp \
 CGTradeRemoveItem.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeMoney.o: CGTradeMoney.cpp CGTradeMoney.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeMoneyHandler.o: CGTradeMoneyHandler.cpp CGTradeMoney.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeFinish.o: CGTradeFinish.cpp CGTradeFinish.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTradeFinishHandler.o: CGTradeFinishHandler.cpp CGTradeFinish.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSkillToObject.o: CGSkillToObject.cpp CGSkillToObject.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGSkillToObjectHandler.o: CGSkillToObjectHandler.cpp CGSkillToObject.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSkillToSelf.o: CGSkillToSelf.cpp CGSkillToSelf.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGSkillToSelfHandler.o: CGSkillToSelfHandler.cpp CGSkillToSelf.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSkillToTile.o: CGSkillToTile.cpp CGSkillToTile.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGSkillToTileHandler.o: CGSkillToTileHandler.cpp CGSkillToTile.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSilverCoating.o: CGSilverCoating.cpp CGSilverCoating.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSilverCoatingHandler.o: CGSilverCoatingHandler.cpp CGSilverCoating.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestNewbieItem.o: CGRequestNewbieItem.cpp CGRequestNewbieItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestNewbieItemHandler.o: CGRequestNewbieItemHandler.cpp \
 CGRequestNewbieItem.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUseItemFromInventory.o: CGUseItemFromInventory.cpp \
 CGUseItemFromInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Encrypter.h \
 /home/darkeden/sigitest/pt/src/Core/EncryptUtility.h \
 /home/darkeden/sigitest/pt/src/Core/SocketEncryptOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Assert.h
CGUseItemFromInventoryHandler.o: CGUseItemFromInventoryHandler.cpp \
 CGUseItemFromInventory.h /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectWayPoint.o: CGSelectWayPoint.cpp CGSelectWayPoint.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectWayPointHandler.o: CGSelectWayPointHandler.cpp \
 CGSelectWayPoint.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectTileEffect.o: CGSelectTileEffect.cpp CGSelectTileEffect.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectTileEffectHandler.o: CGSelectTileEffectHandler.cpp \
 CGSelectTileEffect.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPartyInvite.o: CGPartyInvite.cpp CGPartyInvite.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPartyInviteHandler.o: CGPartyInviteHandler.cpp CGPartyInvite.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPartyLeave.o: CGPartyLeave.cpp CGPartyLeave.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPartyLeaveHandler.o: CGPartyLeaveHandler.cpp CGPartyLeave.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGResurrect.o: CGResurrect.cpp CGResurrect.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGResurrectHandler.o: CGResurrectHandler.cpp CGResurrect.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestIP.o: CGRequestIP.cpp CGRequestIP.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestIPHandler.o: CGRequestIPHandler.cpp CGRequestIP.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRegistGuild.o: CGRegistGuild.cpp CGRegistGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRegistGuildHandler.o: CGRegistGuildHandler.cpp CGRegistGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectGuild.o: CGSelectGuild.cpp CGSelectGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectGuildHandler.o: CGSelectGuildHandler.cpp CGSelectGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTryJoinGuild.o: CGTryJoinGuild.cpp CGTryJoinGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGTryJoinGuildHandler.o: CGTryJoinGuildHandler.cpp CGTryJoinGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGJoinGuild.o: CGJoinGuild.cpp CGJoinGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGJoinGuildHandler.o: CGJoinGuildHandler.cpp CGJoinGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGQuitGuild.o: CGQuitGuild.cpp CGQuitGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGQuitGuildHandler.o: CGQuitGuildHandler.cpp CGQuitGuild.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestGuildMemberList.o: CGRequestGuildMemberList.cpp \
 CGRequestGuildMemberList.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestGuildMemberListHandler.o: CGRequestGuildMemberListHandler.cpp \
 CGRequestGuildMemberList.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectGuildMember.o: CGSelectGuildMember.cpp CGSelectGuildMember.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectGuildMemberHandler.o: CGSelectGuildMemberHandler.cpp \
 CGSelectGuildMember.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGExpelGuildMember.o: CGExpelGuildMember.cpp CGExpelGuildMember.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGExpelGuildMemberHandler.o: CGExpelGuildMemberHandler.cpp \
 CGExpelGuildMember.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGModifyGuildMember.o: CGModifyGuildMember.cpp CGModifyGuildMember.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGModifyGuildMemberHandler.o: CGModifyGuildMemberHandler.cpp \
 CGModifyGuildMember.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRelicToObject.o: CGRelicToObject.cpp CGRelicToObject.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRelicToObjectHandler.o: CGRelicToObjectHandler.cpp CGRelicToObject.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPortCheck.o: CGPortCheck.cpp CGPortCheck.h \
 /home/darkeden/sigitest/pt/src/Core/DatagramPacket.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Datagram.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGPortCheckHandler.o: CGPortCheckHandler.cpp CGPortCheck.h \
 /home/darkeden/sigitest/pt/src/Core/DatagramPacket.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Datagram.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 /home/darkeden/sigitest/pt/src/Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h /usr/include/bits/stdio_lim.h
CGGuildChat.o: CGGuildChat.cpp CGGuildChat.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGGuildChatHandler.o: CGGuildChatHandler.cpp CGGuildChat.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddItemToItem.o: CGAddItemToItem.cpp CGAddItemToItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGAddItemToItemHandler.o: CGAddItemToItemHandler.cpp CGAddItemToItem.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestInfo.o: CGRequestInfo.cpp CGRequestInfo.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGRequestInfoHandler.o: CGRequestInfoHandler.cpp CGRequestInfo.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGModifyGuildIntro.o: CGModifyGuildIntro.cpp CGModifyGuildIntro.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGModifyGuildIntroHandler.o: CGModifyGuildIntroHandler.cpp \
 CGModifyGuildIntro.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGModifyGuildMemberIntro.o: CGModifyGuildMemberIntro.cpp \
 CGModifyGuildMemberIntro.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGModifyGuildMemberIntroHandler.o: CGModifyGuildMemberIntroHandler.cpp \
 CGModifyGuildMemberIntro.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSkillToNamed.o: CGSkillToNamed.cpp CGSkillToNamed.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSkillToNamedHandler.o: CGSkillToNamedHandler.cpp CGSkillToNamed.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectRankBonus.o: CGSelectRankBonus.cpp CGSelectRankBonus.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGSelectRankBonusHandler.o: CGSelectRankBonusHandler.cpp \
 CGSelectRankBonus.h /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGUseMessageItemFromInventory.o: CGUseMessageItemFromInventory.cpp \
 CGUseMessageItemFromInventory.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 CGUseItemFromInventory.h /home/darkeden/sigitest/pt/src/Core/Assert.h
CGUseMessageItemFromInventoryHandler.o: \
 CGUseMessageItemFromInventoryHandler.cpp \
 CGUseMessageItemFromInventory.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h \
 CGUseItemFromInventory.h
CGWithdrawTax.o: CGWithdrawTax.cpp CGWithdrawTax.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
CGWithdrawTaxHandler.o: CGWithdrawTaxHandler.cpp CGWithdrawTax.h \
 /home/darkeden/sigitest/pt/src/Core/Types.h \
 /home/darkeden/sigitest/pt/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_hash_fun.h \
 /home/darkeden/sigitest/pt/src/Core/types/PlayerTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ObjectTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/CreatureTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ItemTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ZoneTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/QuestTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/ShopTypes.h \
 /home/darkeden/sigitest/pt/src/Core/types/GuildTypes.h \
 /home/darkeden/sigitest/pt/src/Core/Utility.h \
 /home/darkeden/sigitest/pt/src/Core/Exception.h \
 /home/darkeden/sigitest/pt/src/Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /home/darkeden/sigitest/pt/src/Core/Packet.h \
 /home/darkeden/sigitest/pt/src/Core/SocketInputStream.h \
 /home/darkeden/sigitest/pt/src/Core/Socket.h \
 /home/darkeden/sigitest/pt/src/Core/SocketImpl.h \
 /home/darkeden/sigitest/pt/src/Core/SocketAPI.h \
 /home/darkeden/sigitest/pt/src/Core/SocketOutputStream.h \
 /home/darkeden/sigitest/pt/src/Core/PacketFactory.h
