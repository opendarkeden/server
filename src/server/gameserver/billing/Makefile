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
SRCDIR   = $(VSHOME)/src
COREDIR  = $(SRCDIR)/Core
SERVDIR  = $(SRCDIR)/server
DBDIR    = $(SERVDIR)/database
GSDIR    = ..
LSDIR    = ../../loginserver
BILLDIR  = $(GSDIR)/billing
MYSQLDIR = /usr/local/lib/mysql


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o .gs.o .ls.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(LSDIR) -I$(BILLDIR) -I.
INCLUDES_GS = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(BILLDIR) -I.
INCLUDES_LS = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(LSDIR) -I$(BILLDIR) -I.
#CCFLAGS  = -Wall -c -g  
CCFLAGS  = -Wall -c -g 
#LIBS     = -L$(LIBDIR) -lGameServerDatabase -lServerCore -lCore
#SYSLIBS  = -L$(MYSQLDIR) -static -lpthread -lnsl -lmysqlclient -lz

# < for Library >
TARGET_GS  = $(LIBDIR)/libGameServerBilling.a
TARGET_LS  = $(LIBDIR)/libLoginServerBilling.a

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

# < for Test >
#TARGET = test/billingTest


#	main.o
GS_OBJS = \
	CommonBillingPacket.gs.o \
	CommonBillingPacketHandler.gs.o \
	BillingPlayer.gs.o	\
	BillingPlayerManager.gs.o \
	BillingPlayerInfo.gs.o

LS_OBJS = \
	CommonBillingPacket.ls.o \
	CommonBillingPacketHandler.ls.o \
	BillingPlayer.ls.o	\
	BillingPlayerManager.ls.o \
	BillingPlayerInfo.ls.o


SRCS = $(GS_OBJS:.gs.o=.cpp)



#.cpp.o :
#	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

.cpp.gs.o :
	$(CC) $(CCFLAGS) $(DEFS)  -D__GAME_SERVER__ $(INCLUDES_GS) -o $*.gs.o $<

.cpp.ls.o :
	$(CC) $(CCFLAGS) $(DEFS)  -D__LOGIN_SERVER__ $(INCLUDES_LS) -o $*.ls.o $<

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
#all : $(TARGET)
all : $(TARGET_GS) $(TARGET_LS)

allgameserver : $(TARGET_GS)

allloginserver : $(TARGET_LS)

# < for Library >
$(TARGET_GS) : $(GS_OBJS)
	ar r $@ $(GS_OBJS)

$(TARGET_LS) : $(LS_OBJS)
	ar r $@ $(LS_OBJS)

# < for Test >
#$(TARGET) : $(OBJS) $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a 
#	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)


clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET_GS) $(TARGET_LS)

cleanloginserver :
	rm -rf *.ls.o

cleangameserver :
	rm -rf *.gs.o

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
CommonBillingPacket.o: CommonBillingPacket.cpp CommonBillingPacket.h \
 /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
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
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h BillingInfo.h \
 /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/bits/wordsize.h \
 /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/bits/in.h /usr/include/bits/byteswap.h \
 /home/darkeden/vs/src/server/database/DB.h \
 /home/darkeden/vs/src/server/database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 /home/darkeden/vs/src/server/database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /home/darkeden/vs/src/server/database/Statement.h \
 /home/darkeden/vs/src/server/database/Result.h \
 /usr/include/sys/time.h /home/darkeden/vs/src/Core/VSDateTime.h
CommonBillingPacketHandler.o: CommonBillingPacketHandler.cpp \
 CommonBillingPacket.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
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
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h BillingInfo.h \
 BillingPlayer.h /home/darkeden/vs/src/Core/Player.h \
 /home/darkeden/vs/src/Core/Gpackets/GCSystemMessage.h
BillingPlayer.o: BillingPlayer.cpp BillingPlayer.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h /home/darkeden/vs/src/Core/Player.h \
 BillingInfo.h /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h \
 /home/darkeden/vs/src/Core/PacketFactoryManager.h \
 /home/darkeden/vs/src/Core/PacketFactory.h CommonBillingPacket.h \
 /usr/include/bits/stdio_lim.h
BillingPlayerManager.o: BillingPlayerManager.cpp \
 BillingPlayerManager.h /home/darkeden/vs/src/Core/Types.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h /home/darkeden/vs/src/server/Thread.h \
 /home/darkeden/vs/src/server/pthreadAPI.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/server/Mutex.h BillingInfo.h BillingPlayer.h \
 /home/darkeden/vs/src/Core/Player.h CommonBillingPacket.h \
 /usr/include/bits/stdio_lim.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h \
 /home/darkeden/vs/src/server/LogClient.h \
 /home/darkeden/vs/src/Core/Assert.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /home/darkeden/vs/src/server/database/DB.h \
 /home/darkeden/vs/src/server/database/DatabaseManager.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 /home/darkeden/vs/src/server/database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/database/Statement.h \
 /home/darkeden/vs/src/server/database/Result.h \
 /usr/include/sys/time.h /home/darkeden/vs/src/server/Timeval.h
BillingPlayerInfo.o: BillingPlayerInfo.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
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
 /usr/include/STL/stl_list.h /home/darkeden/vs/src/Core/Player.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h BillingPlayerInfo.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h
