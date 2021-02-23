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
DBDIR   = $(SERVDIR)/database
GSDIR   = $(SERVDIR)/gameserver
LSDIR   = $(SERVDIR)/loginserver
SSDIR	= $(SERVDIR)/sharedserver
CLIDIR  = ../../client
LCCDIR  = $(CLIDIR)/linux/console


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .gs.o .ls.o .ss.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR)
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 

TARGET1 = $(LIBDIR)/libGameServerPackets.a
TARGET2 = $(LIBDIR)/libLoginServerPackets.a
TARGET3 = $(LIBDIR)/libLinuxConsoleClientPackets.a
TARGET4 = $(LIBDIR)/libSharedServerPackets.a

OBJS1	= \
		RCSay.gs.o RCSayHandler.gs.o

OBJS2	= \
		RCSay.ls.o RCSayHandler.ls.o

OBJS4	= \
		RCSay.ss.o RCSayHandler.ss.o

SRCS	= $(OBJS1:.gs.o=.cpp)

.cpp.gs.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -I$(SERVDIR) -I$(GSDIR) -I$(DBDIR) -o $*.gs.o $<

.cpp.ls.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__LOGIN_SERVER__ $(INCLUDES) -I$(SERVDIR) -I$(LSDIR) -I$(DBDIR) -o $*.ls.o $<

.cpp.ss.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__SHARED_SERVER__ $(INCLUDES) -I$(SERVDIR) -I$(SSDIR) -I$(DBDIR) -o $*.ss.o $<

#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

#all : $(TARGET1) $(TARGET2) $(TARGET3)
all : $(TARGET1) $(TARGET2) $(TARGET4)

allloginserver : $(TARGET2)

allgameserver : $(TARGET1)

allsharedserver : $(TARGET4)

$(TARGET1) : $(OBJS1)
	ar r $@ $(OBJS1)

$(TARGET2) : $(OBJS2)
	ar r $@ $(OBJS2)

$(TARGET3) : $(OBJS3)
	ar r $@ $(OBJS3)

$(TARGET4) : $(OBJS4)
	ar r $@ $(OBJS4)

clean :
	rm -rf *.o

cleanloginserver :
	rm -rf *.ls.o

cleangameserver :
	rm -rf *.gs.o

cleansharedserver :
	rm -rf *.ss.o

cleanall :
	rm -rf *.o

depall :
	gccmakedep $(SRCS) $(INCLUDES) $(DEFS)

dep :
	gccmakedep $(SRCS) $(INCLUDES) $(DEFS)

# DO NOT DELETE
RCSay.o: RCSay.cpp RCSay.h ../DatagramPacket.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/STL/iostream \
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
 /usr/include/STL/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../Utility.h ../Exception.h ../StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 ../SocketOutputStream.h ../Datagram.h ../PacketFactory.h
RCSayHandler.o: RCSayHandler.cpp RCSay.h ../DatagramPacket.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 ../types/GuildTypes.h ../Utility.h ../Exception.h ../StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 ../SocketOutputStream.h ../Datagram.h ../PacketFactory.h
