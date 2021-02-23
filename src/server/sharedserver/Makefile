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
VSHOME  = ../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
LOGDIR  = $(VSHOME)/log
DBINCDIR  = /usr/local/include/mysql
SRCDIR  = ../..
COREDIR = ../../Core
SERVDIR = ..
DBDIR   = ../database
MYSQLDIR = /usr/local/lib/mysql
PYTHONDIR = /usr/local/include/python2.2

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__SHARED_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(DBINCDIR) -I$(PYTHONDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS     = -L$(LIBDIR) -lDatabase -lSharedServerPackets -lGameServerPackets -lServerCore -lCore
SYSLIBS  = -L$(MYSQLDIR) -static -lmysqlclient -lpthread -lnsl -lz
#SYSLIBS  = -L$(MYSQLDIR) -lmysqlclient -lpthread -lnsl -lz -ldl -lutil -lpython2.2 -rdynamic

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS = \
	Guild.o GuildManager.o ResurrectLocationManager.o GameServerPlayer.o \
	HeartbeatManager.o GameServerInfoManager.o \
	GameServerGroupInfoManager.o GameServerManager.o \
	SharedServer.o main.o StringPool.o \

SRCS = $(OBJS:.o=.cpp)

TARGET = $(BINDIR)/sharedserver


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
$(TARGET) : $(OBJS) $(LIBDIR)/libDatabase.a $(LIBDIR)/libGameServerPackets.a $(LIBDIR)/libSharedServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
Guild.o: Guild.cpp /usr/include/STL/algorithm \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_relops.h /usr/include/STL/stl_pair.h \
 /usr/include/STL/type_traits.h /usr/include/string.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
 /usr/include/limits.h /usr/include/bits/posix1_lim.h \
 /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/STL/iostream.h /usr/include/STL/streambuf.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/stl_iterator.h \
 /usr/include/STL/stl_construct.h /usr/include/STL/stl_uninitialized.h \
 /usr/include/STL/stl_tempbuf.h /usr/include/STL/stl_algo.h \
 /usr/include/STL/stl_heap.h Guild.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_string_fwd.h \
 /usr/include/STL/stl_alloc.h /usr/include/assert.h \
 /usr/include/ctype.h /usr/include/STL/functional \
 /usr/include/STL/stl_function.h /usr/include/STL/stdexcept \
 /usr/include/STL/stl_exception.h /usr/include/STL/memory \
 /usr/include/STL/stl_raw_storage_iter.h \
 /usr/include/STL/char_traits.h /usr/include/stdio.h \
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Assert.h ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 ../../Core/VSDateTime.h ../database/DB.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../database/Statement.h \
 ../database/Result.h /usr/include/sys/time.h ../../Core/GuildInfo.h \
 ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/Socket.h ../../Core/SocketImpl.h ../../Core/SocketAPI.h \
 ../../Core/SocketOutputStream.h \
 ../../Core/Gpackets/GCGuildMemberList.h /usr/include/STL/slist \
 /usr/include/STL/stl_slist.h ../../Core/PacketFactory.h \
 ../../Core/GuildMemberInfo.h ../../Core/Properties.h \
 /usr/include/STL/map /usr/include/STL/stl_tree.h \
 /usr/include/STL/stl_map.h /usr/include/STL/stl_multimap.h \
 /usr/include/bits/stdio_lim.h
GuildManager.o: GuildManager.cpp Guild.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
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
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Assert.h ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 ../../Core/VSDateTime.h GuildManager.h ../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../database/DB.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../database/Statement.h \
 ../database/Result.h ../../Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h ../../Core/Gpackets/GCWaitGuildList.h \
 /usr/include/STL/slist /usr/include/STL/stl_slist.h \
 ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/Socket.h ../../Core/SocketImpl.h ../../Core/SocketAPI.h \
 ../../Core/SocketOutputStream.h ../../Core/PacketFactory.h \
 ../../Core/GuildInfo.h ../../Core/Gpackets/GCActiveGuildList.h
ResurrectLocationManager.o: ResurrectLocationManager.cpp \
 ResurrectLocationManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
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
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 ../database/DB.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h
GameServerPlayer.o: GameServerPlayer.cpp GameServerPlayer.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /usr/include/STL/list /usr/include/STL/stl_list.h ../../Core/Player.h \
 ../../Core/Socket.h ../../Core/SocketImpl.h ../../Core/SocketAPI.h \
 ../../Core/SocketInputStream.h ../../Core/SocketOutputStream.h \
 ../../Core/Assert.h ../../Core/Packet.h \
 ../../Core/PacketFactoryManager.h ../../Core/PacketFactory.h
HeartbeatManager.o: HeartbeatManager.cpp HeartbeatManager.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 /usr/include/STL/list /usr/include/STL/stl_list.h ../../Core/Assert.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h
GameServerInfoManager.o: GameServerInfoManager.cpp \
 GameServerInfoManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
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
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h GameServerInfo.h \
 /usr/include/STL/hash_map /usr/include/STL/stl_hashtable.h \
 /usr/include/STL/stl_vector.h /usr/include/STL/stl_hash_map.h \
 ../database/DB.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h \
 ../../Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h
GameServerGroupInfoManager.o: GameServerGroupInfoManager.cpp \
 GameServerGroupInfoManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
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
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h \
 GameServerGroupInfo.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_hash_map.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h \
 ../database/DB.h
GameServerManager.o: GameServerManager.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/bits/stdio_lim.h GameServerManager.h ../Thread.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 ../../Core/types/PlayerTypes.h ../../Core/types/ObjectTypes.h \
 ../../Core/types/CreatureTypes.h ../../Core/types/ItemTypes.h \
 ../../Core/types/ZoneTypes.h ../../Core/types/QuestTypes.h \
 ../../Core/types/ShopTypes.h ../../Core/types/GuildTypes.h \
 ../../Core/types/WarTypes.h ../../Core/types/ServerType.h \
 ../../Core/Utility.h ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../pthreadAPI.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h GameServerPlayer.h ../../Core/Player.h \
 ../../Core/ServerSocket.h ../../Core/SocketImpl.h \
 ../../Core/SocketAPI.h ../../Core/Socket.h ../Mutex.h \
 ../../Core/Assert.h ../../Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h Guild.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_hash_map.h ../../Core/VSDateTime.h \
 GuildManager.h ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/SocketOutputStream.h ../database/DB.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../database/Statement.h \
 ../database/Result.h
SharedServer.o: SharedServer.cpp SharedServer.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/STL/iostream \
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
 /usr/include/STL/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/STL/list /usr/include/STL/stl_list.h ../../Core/Assert.h \
 GameServerInfoManager.h GameServerInfo.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_hash_map.h GameServerGroupInfoManager.h \
 GameServerGroupInfo.h GameServerManager.h ../Thread.h ../pthreadAPI.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h GameServerPlayer.h ../../Core/Player.h \
 ../../Core/ServerSocket.h ../../Core/SocketImpl.h \
 ../../Core/SocketAPI.h ../../Core/Socket.h ../Mutex.h \
 HeartbeatManager.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 ../../Core/PacketFactoryManager.h ../../Core/Packet.h \
 ../../Core/SocketInputStream.h ../../Core/SocketOutputStream.h \
 ../../Core/PacketFactory.h ../../Core/PacketValidator.h \
 ../../Core/PacketIDSet.h ../../Core/PlayerStatus.h \
 /usr/include/STL/vector /usr/include/STL/stl_range_errors.h \
 /usr/include/STL/stl_bvector.h ../GameWorldInfoManager.h \
 ../GameWorldInfo.h GuildManager.h ResurrectLocationManager.h \
 StringPool.h ../LogClient.h
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
 /usr/include/STL/list /usr/include/STL/stl_list.h SharedServer.h \
 ../LogClient.h ../../Core/Properties.h /usr/include/STL/map \
 /usr/include/STL/stl_tree.h /usr/include/STL/stl_map.h \
 /usr/include/STL/stl_multimap.h /usr/include/sys/resource.h \
 /usr/include/bits/resource.h
StringPool.o: StringPool.cpp StringPool.h ../../Core/Exception.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
 /usr/include/STL/iostream /usr/include/STL/iostream.h \
 /usr/include/STL/streambuf.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/bits/types.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/gnu/stubs.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stddef.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
 /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/stdarg.h \
 /usr/include/STL/fstream /usr/include/STL/fstream.h \
 /usr/include/STL/string /usr/include/STL/stl_config.h \
 /usr/include/STL/stl_string_fwd.h /usr/include/STL/stl_alloc.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/new \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/exception \
 /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/STL/functional /usr/include/STL/stl_function.h \
 /usr/include/STL/stdexcept /usr/include/STL/stl_exception.h \
 /usr/include/STL/stl_iterator_base.h /usr/include/STL/memory \
 /usr/include/STL/stl_algobase.h /usr/include/STL/stl_relops.h \
 /usr/include/STL/stl_pair.h /usr/include/STL/type_traits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/limits.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/syslimits.h \
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
 ../../Core/StringStream.h /usr/include/STL/list \
 /usr/include/STL/stl_list.h /usr/include/STL/hash_map \
 /usr/include/STL/stl_hashtable.h /usr/include/STL/stl_vector.h \
 /usr/include/STL/stl_hash_map.h ../database/DB.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h
