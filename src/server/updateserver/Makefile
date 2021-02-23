#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Directories Setting
#----------------------------------------------------------------------
VSHOME   = ../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../..
COREDIR  = ../../Core
SERVDIR  = ..
DBDIR    = ../database


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__UPDATE_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS     = -L$(LIBDIR) -lUpdateServerPackets -lServerCore -lCore
SYSLIBS  = -lpthread -lnsl

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS   = main.o UpdateServer.o UpdateServerPlayer.o
SRCS   = $(OBJS:.o=.cpp)
TARGET = $(BINDIR)/updateserver
UPDATE = $(BINDIR)/update

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET) $(UPDATE)

$(TARGET) : $(OBJS) $(LIBDIR)/libUpdateServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)

$(UPDATE) : update.o $(LIBDIR)/libCore.a
	$(CC) -o $@ update.o -L$(LIBDIR) -lCore

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET) $(UPDATE)

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
main.o: main.cpp ../../Core/Types.h ../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h UpdateServer.h \
 ../../Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../../Core/ServerSocket.h \
 ../../Core/SocketImpl.h ../../Core/SocketAPI.h ../../Core/Socket.h \
 /usr/include/bits/stdio_lim.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/dirent.h \
 /usr/include/bits/dirent.h /usr/include/sys/stat.h \
 /usr/include/bits/stat.h /usr/include/sys/resource.h \
 /usr/include/bits/resource.h ../../Core/UpdateManager.h \
 ../../Core/Update.h ../../Core/UpdateDef.h ../../Core/Assert.h \
 ../../Core/SocketInputStream.h ../../Core/SocketOutputStream.h \
 ../../Core/Resource.h ../../Core/ResourceManager.h
UpdateServer.o: UpdateServer.cpp /usr/include/STL/fstream \
 /usr/include/STL/fstream.h /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/time.h /usr/include/bits/time.h /usr/include/signal.h \
 /usr/include/bits/sigset.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/wordsize.h \
 /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h \
 /usr/include/asm/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/include/bits/sigthread.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/stdio.h \
 /usr/include/bits/stdio_lim.h /usr/include/fcntl.h \
 /usr/include/bits/fcntl.h /usr/include/sys/types.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_config.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/include/string.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
 /usr/include/alloca.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/stl_iterator.h \
 /usr/include/STL/stl_alloc.h /usr/include/assert.h \
 /usr/include/STL/stl_construct.h /usr/include/STL/stl_tempbuf.h \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/stl_uninitialized.h /usr/include/STL/stl_function.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_fun.h \
 /usr/include/STL/stl_hash_map.h UpdateServer.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/string /usr/include/STL/stl_string_fwd.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/memory /usr/include/STL/stl_raw_storage_iter.h \
 /usr/include/STL/algorithm /usr/include/STL/char_traits.h \
 ../../Core/types/PlayerTypes.h ../../Core/types/ObjectTypes.h \
 ../../Core/types/CreatureTypes.h ../../Core/types/ItemTypes.h \
 ../../Core/types/ZoneTypes.h ../../Core/types/QuestTypes.h \
 ../../Core/types/ShopTypes.h ../../Core/types/GuildTypes.h \
 ../../Core/types/WarTypes.h ../../Core/types/ServerType.h \
 ../../Core/Utility.h ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../../Core/ServerSocket.h \
 ../../Core/SocketImpl.h ../../Core/SocketAPI.h ../../Core/Socket.h \
 ../../Core/Assert.h ../SystemAPI.h UpdateServerPlayer.h \
 ../../Core/Player.h ../../Core/PlayerStatus.h /usr/include/STL/deque \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_deque.h \
 ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/SocketOutputStream.h ../Timeval.h /usr/include/sys/time.h \
 /usr/include/STL/bitset
UpdateServerPlayer.o: UpdateServerPlayer.cpp UpdateServerPlayer.h \
 ../../Core/Player.h ../../Core/Types.h ../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../../Core/PlayerStatus.h /usr/include/STL/deque \
 /usr/include/STL/stl_range_errors.h /usr/include/STL/stl_deque.h \
 ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/Socket.h ../../Core/SocketImpl.h ../../Core/SocketAPI.h \
 ../../Core/SocketOutputStream.h ../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 /usr/include/STL/bitset ../../Core/Assert.h \
 ../../Core/Upackets/CUBeginUpdate.h ../../Core/PacketFactory.h \
 ../../Core/UpdateManager.h ../../Core/Update.h ../../Core/UpdateDef.h \
 ../../Core/Resource.h ../../Core/ResourceManager.h \
 ../../Core/Upackets/CURequest.h ../../Core/Upackets/CUEndUpdate.h \
 ../../Core/Upackets/CURequestLoginMode.h
