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
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR)

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
LCCreatePCError.o: LCCreatePCError.cpp LCCreatePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCCreatePCErrorHandler.o: LCCreatePCErrorHandler.cpp LCCreatePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCCreatePCOK.o: LCCreatePCOK.cpp LCCreatePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCCreatePCOKHandler.o: LCCreatePCOKHandler.cpp LCCreatePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCError.o: LCDeletePCError.cpp LCDeletePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCErrorHandler.o: LCDeletePCErrorHandler.cpp LCDeletePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCOK.o: LCDeletePCOK.cpp LCDeletePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCOKHandler.o: LCDeletePCOKHandler.cpp LCDeletePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginError.o: LCLoginError.cpp LCLoginError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginErrorHandler.o: LCLoginErrorHandler.cpp LCLoginError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginOK.o: LCLoginOK.cpp LCLoginOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginOKHandler.o: LCLoginOKHandler.cpp LCLoginOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCPCList.o: LCPCList.cpp LCPCList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/PCInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCPCListHandler.o: LCPCListHandler.cpp LCPCList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/PCInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCQueryResultPlayerID.o: LCQueryResultPlayerID.cpp \
 LCQueryResultPlayerID.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCQueryResultPlayerIDHandler.o: LCQueryResultPlayerIDHandler.cpp \
 LCQueryResultPlayerID.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCQueryResultCharacterName.o: LCQueryResultCharacterName.cpp \
 LCQueryResultCharacterName.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCQueryResultCharacterNameHandler.o: \
 LCQueryResultCharacterNameHandler.cpp LCQueryResultCharacterName.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCReconnect.o: LCReconnect.cpp LCReconnect.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCReconnectHandler.o: LCReconnectHandler.cpp LCReconnect.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerError.o: LCRegisterPlayerError.cpp \
 LCRegisterPlayerError.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerErrorHandler.o: LCRegisterPlayerErrorHandler.cpp \
 LCRegisterPlayerError.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerOK.o: LCRegisterPlayerOK.cpp LCRegisterPlayerOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerOKHandler.o: LCRegisterPlayerOKHandler.cpp \
 LCRegisterPlayerOK.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCSelectPCError.o: LCSelectPCError.cpp LCSelectPCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCSelectPCErrorHandler.o: LCSelectPCErrorHandler.cpp LCSelectPCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCServerList.o: LCServerList.cpp LCServerList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/ServerGroupInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h \
 /home/darkeden/vs/src/Core/PCInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCServerListHandler.o: LCServerListHandler.cpp LCServerList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/ServerGroupInfo.h
LCWorldList.o: LCWorldList.cpp LCWorldList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/WorldInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h \
 /home/darkeden/vs/src/Core/PCInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCWorldListHandler.o: LCWorldListHandler.cpp LCWorldList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/WorldInfo.h
LCVersionCheckOK.o: LCVersionCheckOK.cpp LCVersionCheckOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCVersionCheckOKHandler.o: LCVersionCheckOKHandler.cpp \
 LCVersionCheckOK.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCVersionCheckError.o: LCVersionCheckError.cpp LCVersionCheckError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCVersionCheckErrorHandler.o: LCVersionCheckErrorHandler.cpp \
 LCVersionCheckError.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnection.o: LGIncomingConnection.cpp \
 LGIncomingConnection.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionHandler.o: LGIncomingConnectionHandler.cpp \
 LGIncomingConnection.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h
LGIncomingConnectionOK.o: LGIncomingConnectionOK.cpp \
 LGIncomingConnectionOK.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionOKHandler.o: LGIncomingConnectionOKHandler.cpp \
 LGIncomingConnectionOK.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionError.o: LGIncomingConnectionError.cpp \
 LGIncomingConnectionError.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionErrorHandler.o: \
 LGIncomingConnectionErrorHandler.cpp LGIncomingConnectionError.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGKickCharacter.o: LGKickCharacter.cpp LGKickCharacter.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGKickCharacterHandler.o: LGKickCharacterHandler.cpp LGKickCharacter.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
