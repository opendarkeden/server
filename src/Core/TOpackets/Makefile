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
COREDIR = $(SRCDIR)/Core
SERVDIR = $(SRCDIR)/server
TOSDIR  = $(SERVDIR)/theoneserver
GSDIR   = $(SERVDIR)/gameserver
DBDIR	= $(SERVDIR)/database
LSDIR   = $(SERVDIR)/loginserver


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .tos.o .gs.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(GSDIR) -I$(TOSDIR) -I$(DBDIR) -I$(LSDIR) -I$(SERVDIR)
#INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(TOSDIR)
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 

TARGET1 = $(LIBDIR)/libTheOneServerPackets.a
TARGET2 = $(LIBDIR)/libGameServerPackets.a

OBJS1	= \
		GTOAcknowledgement.tos.o GTOAcknowledgementHandler.tos.o

OBJS2	= \
		GTOAcknowledgement.gs.o GTOAcknowledgementHandler.gs.o

SRCS	= $(OBJS1:.tos.o=.cpp)

.cpp.tos.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__THE_ONE_SERVER__ $(INCLUDES) -I$(TOSDIR) -I$(SERVDIR) -I$(DBDIR) -o $*.tos.o $<

.cpp.gs.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -I$(GSDIR) -I$(SERVDIR) -I$(DBDIR) -o $*.gs.o $<



#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

all : $(TARGET1) $(TARGET2)
#all : $(TARGET1)

alltheoneserver : $(TARGET1)

allgameserver : $(TARGET2)

$(TARGET1) : $(OBJS1)
	ar rc $@ $(OBJS1)

$(TARGET2) : $(OBJS2)
	ar r $@ $(OBJS2)

clean :
	rm -rf *.o

cleantheoneserver :
	rm -rf *.tos.o

cleangameserver :
	rm -rf *.gs.o

cleanall :
	rm -rf *.o $(TARGET1) $(TARGET2)

depall :
	gccmakedep  $(SRCS) $(INCLUDES) $(DEFS)

dep :
	gccmakedep  $(SRCS) $(INCLUDES) $(DEFS)

# DO NOT DELETE
GTOAcknowledgement.o: GTOAcknowledgement.cpp GTOAcknowledgement.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h /usr/include/arpa/inet.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
GTOAcknowledgementHandler.o: GTOAcknowledgementHandler.cpp \
 GTOAcknowledgement.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /usr/include/sys/socket.h /usr/include/sys/uio.h \
 /usr/include/bits/uio.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h /usr/include/arpa/inet.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h \
 /home/darkeden/vs/src/server/theoneserver/DB.h \
 /home/darkeden/vs/src/server/theoneserver/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 /home/darkeden/vs/src/server/theoneserver/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h \
 /home/darkeden/vs/src/server/theoneserver/Statement.h \
 /home/darkeden/vs/src/server/theoneserver/Result.h \
 /usr/include/sys/time.h \
 /home/darkeden/vs/src/Core/Gpackets/GGCommand.h \
 /home/darkeden/vs/src/server/theoneserver/GameServerManager.h \
 /home/darkeden/vs/src/server/Thread.h \
 /home/darkeden/vs/src/server/pthreadAPI.h \
 /home/darkeden/vs/src/Core/DatagramSocket.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h
