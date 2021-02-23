#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
VSHOME  = ../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = ..
SERVDIR = ../../server
USDIR   = $(SERVDIR)/updateserver
CLIDIR  = ../../client
UCDIR   = $(CLIDIR)/updateclient


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .us.o .uc.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR)
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 

TARGET1 = $(LIBDIR)/libUpdateServerPackets.a
TARGET2 = $(LIBDIR)/libUpdateClientPackets.a

OBJS1	= \
		CUBeginUpdate.us.o CUBeginUpdateHandler.us.o \
		CURequest.us.o CURequestHandler.us.o \
		CUEndUpdate.us.o CUEndUpdateHandler.us.o \
		CURequestLoginMode.us.o CURequestLoginModeHandler.us.o \
		UCUpdate.us.o UCUpdateHandler.us.o \
		UCUpdateList.us.o UCUpdateListHandler.us.o \
		UCRequestLoginMode.us.o UCRequestLoginModeHandler.us.o

OBJS2	= \
		CUBeginUpdate.uc.o CUBeginUpdateHandler.uc.o \
		CURequest.uc.o CURequestHandler.uc.o \
		CUEndUpdate.uc.o CUEndUpdateHandler.uc.o \
		CURequestLoginMode.uc.o CURequestLoginModeHandler.uc.o \
		UCUpdate.uc.o UCUpdateHandler.uc.o \
		UCUpdateList.uc.o UCUpdateListHandler.uc.o \
		UCRequestLoginMode.uc.o UCRequestLoginModeHandler.uc.o

SRCS	= $(OBJS1:.us.o=.cpp)

.cpp.us.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_SERVER__ $(INCLUDES) -I$(USDIR) -I$(SERVDIR) -o $*.us.o $<

.cpp.uc.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_CLIENT__ $(INCLUDES) -I$(UCDIR) -o $*.uc.o $<



#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

all : $(TARGET1) $(TARGET2)
#all : $(TARGET1)

allloginserver : $(TARGET1) $(TARGET2)

allgameserver : $(TARGET1) $(TARGET2)

$(TARGET1) : $(OBJS1)
	ar rc $@ $(OBJS1)

$(TARGET2) : $(OBJS2)
	ar rc $@ $(OBJS2)

clean :
	rm -rf *.o

cleanloginserver :
	rm -rf *.o

cleangameserver :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET1) $(TARGET2)

depall :
	gccmakedep  $(SRCS) $(INCLUDES) $(DEFS)

dep :
	gccmakedep  $(SRCS) $(INCLUDES) $(DEFS)

# DO NOT DELETE
CUBeginUpdate.o: CUBeginUpdate.cpp CUBeginUpdate.h ../Packet.h \
 ../Types.h ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../UpdateManager.h ../Update.h ../UpdateDef.h ../Assert.h \
 ../Resource.h ../ResourceManager.h ../Properties.h \
 /usr/include/STL/map /usr/include/STL/stl_tree.h \
 /usr/include/STL/stl_map.h /usr/include/STL/stl_multimap.h
CUBeginUpdateHandler.o: CUBeginUpdateHandler.cpp CUBeginUpdate.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/sys/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../UpdateManager.h ../Update.h ../UpdateDef.h ../Assert.h \
 ../Resource.h ../ResourceManager.h
CURequest.o: CURequest.cpp CURequest.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../Resource.h ../UpdateDef.h
CURequestHandler.o: CURequestHandler.cpp CURequest.h ../Packet.h \
 ../Types.h ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../Resource.h ../UpdateDef.h
CUEndUpdate.o: CUEndUpdate.cpp CUEndUpdate.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h
CUEndUpdateHandler.o: CUEndUpdateHandler.cpp CUEndUpdate.h ../Packet.h \
 ../Types.h ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h
CURequestLoginMode.o: CURequestLoginMode.cpp CURequestLoginMode.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/sys/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h
CURequestLoginModeHandler.o: CURequestLoginModeHandler.cpp \
 CURequestLoginMode.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/sys/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h
UCUpdate.o: UCUpdate.cpp UCUpdate.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../Resource.h ../UpdateDef.h
UCUpdateHandler.o: UCUpdateHandler.cpp UCUpdate.h ../Packet.h \
 ../Types.h ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../Resource.h ../UpdateDef.h
UCUpdateList.o: UCUpdateList.cpp UCUpdateList.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/sys/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../UpdateManager.h ../Update.h ../UpdateDef.h ../Assert.h \
 ../Resource.h ../ResourceManager.h
UCUpdateListHandler.o: UCUpdateListHandler.cpp UCUpdateList.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/sys/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h \
 ../UpdateManager.h ../Update.h ../UpdateDef.h ../Assert.h \
 ../Resource.h ../ResourceManager.h
UCRequestLoginMode.o: UCRequestLoginMode.cpp UCRequestLoginMode.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/sys/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h
UCRequestLoginModeHandler.o: UCRequestLoginModeHandler.cpp \
 UCRequestLoginMode.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/sys/types.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/include/bits/types.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/STL/iostream \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h \
 /usr/include/assert.h /usr/include/STL/stl_threads.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/stl_iterator_base.h \
 /usr/include/STL/memory /usr/include/STL/stl_algobase.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/include/STL/stl_iterator.h /usr/include/STL/stl_construct.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_raw_storage_iter.h /usr/include/STL/algorithm \
 /usr/include/STL/stl_algo.h /usr/include/STL/stl_heap.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../types/WarTypes.h ../types/ServerType.h \
 ../Utility.h ../Exception.h ../StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h ../SocketInputStream.h ../Socket.h \
 ../SocketImpl.h ../SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h ../SocketOutputStream.h ../PacketFactory.h
