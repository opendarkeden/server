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
VSHOME   = ../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = $(VSHOME)/src
COREDIR  = $(SRCDIR)/Core
SERVDIR  = $(SRCDIR)/server
DBDIR    = $(SERVDIR)/database
GSDIR    = $(SERVDIR)/gameserver
LSDIR    = $(SERVDIR)/loginserver
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
TARGET     = $(LIBDIR)/libCBilling.a
TARGET_GS  = $(LIBDIR)/libGameServerCBilling.a
TARGET_LS  = $(LIBDIR)/libLoginServerCBilling.a

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

# < for Test >
#TARGET = test/billingTest


#	main.o
OBJS = \
	CBillingPacketErrorBody.o \
	CBillingPacketResponseLoginBody.o \
	CBillingPacketHeader.o \
	CBillingPacketResponseLogoutBody.o \
	CBillingPacketRequestIntervalValidationBody.o \
	CBillingPacketResponseMinusMinuteBody.o \
	CBillingPacketRequestLoginBody.o \
	CBillingPacketResponseMinusPointBody.o \
	CBillingPacketRequestLogoutBody.o \
	CBillingPlayer.o \
	CBillingPacketRequestMinusMinuteBody.o \
	CBillingPlayerInfo.o \
	CBillingPacketRequestMinusPointBody.o \
	CBillingPlayerManager.o \
	CBillingPacketResponseIntervalValidationBody.o \

GS_OBJS = \
	CBillingPacketErrorBody.gs.o \
	CBillingPacketResponseLoginBody.gs.o \
	CBillingPacketHeader.gs.o \
	CBillingPacketResponseLogoutBody.gs.o \
	CBillingPacketRequestIntervalValidationBody.gs.o \
	CBillingPacketResponseMinusMinuteBody.gs.o \
	CBillingPacketRequestLoginBody.gs.o \
	CBillingPacketResponseMinusPointBody.gs.o \
	CBillingPacketRequestLogoutBody.gs.o \
	CBillingPlayer.gs.o \
	CBillingPacketRequestMinusMinuteBody.gs.o \
	CBillingPlayerInfo.gs.o \
	CBillingPacketRequestMinusPointBody.gs.o \
	CBillingPlayerManager.gs.o \
	CBillingPacketResponseIntervalValidationBody.gs.o \

LS_OBJS = \
	CBillingPacketErrorBody.ls.o \
	CBillingPacketResponseLoginBody.ls.o \
	CBillingPacketHeader.ls.o \
	CBillingPacketResponseLogoutBody.ls.o \
	CBillingPacketRequestIntervalValidationBody.ls.o \
	CBillingPacketResponseMinusMinuteBody.ls.o \
	CBillingPacketRequestLoginBody.ls.o \
	CBillingPacketResponseMinusPointBody.ls.o \
	CBillingPacketRequestLogoutBody.ls.o \
	CBillingPlayer.ls.o \
	CBillingPacketRequestMinusMinuteBody.ls.o \
	CBillingPlayerInfo.ls.o \
	CBillingPacketRequestMinusPointBody.ls.o \
	CBillingPlayerManager.ls.o \
	CBillingPacketResponseIntervalValidationBody.ls.o \

SRCS = $(GS_OBJS:.gs.o=.cpp)



#.cpp.o :
#	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS)  $(INCLUDES) -o $*.o $<

.cpp.gs.o :
	$(CC) $(CCFLAGS) $(DEFS)  -D__GAME_SERVER__ $(INCLUDES_GS) -o $*.gs.o $<

.cpp.ls.o :
	$(CC) $(CCFLAGS) $(DEFS)  -D__LOGIN_SERVER__ $(INCLUDES_LS) -o $*.ls.o $<

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
#all : $(TARGET)
all : $(TARGET_GS) $(TARGET_LS) $(TARGET)

allgameserver : $(TARGET_GS)

allloginserver : $(TARGET_LS)

# < for Library >
$(TARGET_GS) : $(GS_OBJS)
	ar r $@ $(GS_OBJS)

$(TARGET_LS) : $(LS_OBJS)
	ar r $@ $(LS_OBJS)

$(TARGET) : $(OBJS)
	ar r $@ $(OBJS)

# < for Test >
#$(TARGET) : $(OBJS) $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a 
#	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)


clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET_GS) $(TARGET_LS) $(TARGET)

cleanloginserver :
	rm -rf *.ls.o

cleangameserver :
	rm -rf *.gs.o

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
CBillingPacketErrorBody.o: CBillingPacketErrorBody.cpp \
 /usr/include/stdc-predef.h CBillingPacketErrorBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPacketResponseLoginBody.o: CBillingPacketResponseLoginBody.cpp \
 /usr/include/stdc-predef.h CBillingPacketResponseLoginBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPacketHeader.o: CBillingPacketHeader.cpp \
 /usr/include/stdc-predef.h CBillingPacketHeader.h CBillingInfo.h \
 /usr/include/c++/7/string \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/bits/stringfwd.h /usr/include/c++/7/bits/memoryfwd.h \
 /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h /usr/include/c++/7/bits/move.h \
 /usr/include/c++/7/bits/concept_check.h /usr/include/c++/7/type_traits \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h \
 /usr/include/c++/7/bits/postypes.h /usr/include/c++/7/cwchar \
 /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h /usr/include/c++/7/new \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/iosfwd \
 /usr/include/c++/7/cctype /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc ../../../src/Core/Exception.h \
 ../../../src/Core/Types.h ../../../src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream /usr/include/c++/7/ostream \
 /usr/include/c++/7/ios /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/bits/locale_classes.h \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../../../src/Core/SocketInputStream.h ../../../src/Core/Exception.h \
 ../../../src/Core/Socket.h ../../../src/Core/SocketImpl.h \
 ../../../src/Core/SocketAPI.h ../../../src/Core/SocketOutputStream.h \
 ../../../src/Core/Properties.h /usr/include/c++/7/map \
 /usr/include/c++/7/bits/stl_tree.h /usr/include/c++/7/bits/stl_map.h \
 /usr/include/c++/7/tuple /usr/include/c++/7/utility \
 /usr/include/c++/7/bits/stl_relops.h /usr/include/c++/7/array \
 /usr/include/c++/7/bits/uses_allocator.h \
 /usr/include/c++/7/bits/invoke.h /usr/include/c++/7/bits/stl_multimap.h
CBillingPacketResponseLogoutBody.o: CBillingPacketResponseLogoutBody.cpp \
 /usr/include/stdc-predef.h CBillingPacketResponseLogoutBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPacketRequestIntervalValidationBody.o: \
 CBillingPacketRequestIntervalValidationBody.cpp \
 /usr/include/stdc-predef.h CBillingPacketRequestIntervalValidationBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h CBillingPlayerManager.h \
 ../../../src/Core/Types.h ../../../src/server/Thread.h \
 ../../../src/server/pthreadAPI.h ../../../src/Core/Socket.h \
 ../../../src/server/Mutex.h
CBillingPacketResponseMinusMinuteBody.o: \
 CBillingPacketResponseMinusMinuteBody.cpp /usr/include/stdc-predef.h \
 CBillingPacketResponseMinusMinuteBody.h ../../../src/Core/Exception.h \
 ../../../src/Core/Types.h ../../../src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPacketRequestLoginBody.o: CBillingPacketRequestLoginBody.cpp \
 /usr/include/stdc-predef.h CBillingPacketRequestLoginBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPacketResponseMinusPointBody.o: \
 CBillingPacketResponseMinusPointBody.cpp /usr/include/stdc-predef.h \
 CBillingPacketResponseMinusPointBody.h ../../../src/Core/Exception.h \
 ../../../src/Core/Types.h ../../../src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPacketRequestLogoutBody.o: CBillingPacketRequestLogoutBody.cpp \
 /usr/include/stdc-predef.h CBillingPacketRequestLogoutBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPlayer.o: CBillingPlayer.cpp /usr/include/stdc-predef.h \
 CBillingPlayer.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h ../../../src/Core/Types.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/Exception.h ../../../src/Core/StringStream.h \
 /usr/include/c++/7/list /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../../../src/Core/Player.h ../../../src/Core/Exception.h \
 ../../../src/Core/Socket.h ../../../src/Core/SocketImpl.h \
 ../../../src/Core/SocketAPI.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Socket.h ../../../src/Core/SocketOutputStream.h \
 ../../../src/Core/Assert.h ../../../src/Core/Packet.h \
 ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/SocketOutputStream.h CBillingPlayerManager.h \
 ../../../src/server/Thread.h ../../../src/server/pthreadAPI.h \
 ../../../src/server/Mutex.h CBillingInfo.h CBillingPacketHeader.h \
 CBillingPacketErrorBody.h /usr/include/signal.h \
 /usr/include/x86_64-linux-gnu/bits/signum.h \
 /usr/include/x86_64-linux-gnu/bits/signum-generic.h \
 /usr/include/x86_64-linux-gnu/bits/types/sig_atomic_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/siginfo_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigval_t.h \
 /usr/include/x86_64-linux-gnu/bits/siginfo-arch.h \
 /usr/include/x86_64-linux-gnu/bits/siginfo-consts.h \
 /usr/include/x86_64-linux-gnu/bits/siginfo-consts-arch.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigval_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigevent_t.h \
 /usr/include/x86_64-linux-gnu/bits/sigevent-consts.h \
 /usr/include/x86_64-linux-gnu/bits/sigaction.h \
 /usr/include/x86_64-linux-gnu/bits/sigcontext.h \
 /usr/include/x86_64-linux-gnu/bits/types/stack_t.h \
 /usr/include/x86_64-linux-gnu/sys/ucontext.h \
 /usr/include/x86_64-linux-gnu/bits/sigstack.h \
 /usr/include/x86_64-linux-gnu/bits/ss_flags.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_sigstack.h \
 /usr/include/x86_64-linux-gnu/bits/sigthread.h
CBillingPacketRequestMinusMinuteBody.o: \
 CBillingPacketRequestMinusMinuteBody.cpp /usr/include/stdc-predef.h \
 CBillingPacketRequestMinusMinuteBody.h ../../../src/Core/Exception.h \
 ../../../src/Core/Types.h ../../../src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPlayerInfo.o: CBillingPlayerInfo.cpp /usr/include/stdc-predef.h \
 CBillingPlayerInfo.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h ../../../src/Core/Types.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/Exception.h ../../../src/Core/StringStream.h \
 /usr/include/c++/7/list /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../../../src/server/Timeval.h /usr/include/x86_64-linux-gnu/sys/time.h \
 /usr/include/unistd.h /usr/include/x86_64-linux-gnu/bits/posix_opt.h \
 /usr/include/x86_64-linux-gnu/bits/environments.h \
 /usr/include/x86_64-linux-gnu/bits/confname.h \
 /usr/include/x86_64-linux-gnu/bits/getopt_posix.h \
 /usr/include/x86_64-linux-gnu/bits/getopt_core.h CBillingInfo.h \
 ../../../src/Core/VSDateTime.h ../../../src/Core/StringStream.h
CBillingPacketRequestMinusPointBody.o: \
 CBillingPacketRequestMinusPointBody.cpp /usr/include/stdc-predef.h \
 CBillingPacketRequestMinusPointBody.h ../../../src/Core/Exception.h \
 ../../../src/Core/Types.h ../../../src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
CBillingPlayerManager.o: CBillingPlayerManager.cpp \
 /usr/include/stdc-predef.h CBillingPlayerManager.h \
 ../../../src/Core/Types.h ../../../src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h ../../../src/Core/Types.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/Exception.h ../../../src/Core/StringStream.h \
 /usr/include/c++/7/list /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../../../src/server/Thread.h ../../../src/server/pthreadAPI.h \
 ../../../src/Core/Socket.h ../../../src/Core/Exception.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/server/Mutex.h CBillingInfo.h CBillingPlayer.h \
 ../../../src/Core/Player.h ../../../src/Core/Assert.h \
 ../../../src/Core/Properties.h /usr/include/c++/7/map \
 /usr/include/c++/7/bits/stl_tree.h /usr/include/c++/7/bits/stl_map.h \
 /usr/include/c++/7/tuple /usr/include/c++/7/utility \
 /usr/include/c++/7/bits/stl_relops.h /usr/include/c++/7/array \
 /usr/include/c++/7/bits/uses_allocator.h \
 /usr/include/c++/7/bits/invoke.h /usr/include/c++/7/bits/stl_multimap.h \
 /usr/include/unistd.h /usr/include/x86_64-linux-gnu/bits/posix_opt.h \
 /usr/include/x86_64-linux-gnu/bits/environments.h \
 /usr/include/x86_64-linux-gnu/bits/confname.h \
 /usr/include/x86_64-linux-gnu/bits/getopt_posix.h \
 /usr/include/x86_64-linux-gnu/bits/getopt_core.h \
 ../../../src/server/database/DB.h \
 ../../../src/server/database/DatabaseManager.h \
 /usr/include/c++/7/unordered_map /usr/include/c++/7/bits/hashtable.h \
 /usr/include/c++/7/bits/hashtable_policy.h \
 /usr/include/c++/7/bits/unordered_map.h \
 ../../../src/server/database/Connection.h /usr/include/mysql/mysql.h \
 /usr/include/mysql/mysql_version.h /usr/include/mysql/mysql_com.h \
 /usr/include/mysql/binary_log_types.h /usr/include/mysql/my_command.h \
 /usr/include/mysql/mysql_time.h /usr/include/mysql/my_list.h \
 /usr/include/mysql/mysql/client_plugin.h /usr/include/c++/7/stdlib.h \
 /usr/include/mysql/mysql/plugin_auth_common.h \
 /usr/include/mysql/typelib.h /usr/include/mysql/my_alloc.h \
 /usr/include/mysql/mysql/psi/psi_memory.h \
 /usr/include/mysql/mysql/psi/psi_base.h \
 ../../../src/server/database/Statement.h \
 ../../../src/server/database/Result.h \
 /usr/include/x86_64-linux-gnu/sys/time.h ../../../src/server/Timeval.h
CBillingPacketResponseIntervalValidationBody.o: \
 CBillingPacketResponseIntervalValidationBody.cpp \
 /usr/include/stdc-predef.h \
 CBillingPacketResponseIntervalValidationBody.h \
 ../../../src/Core/Exception.h ../../../src/Core/Types.h \
 ../../../src/Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h \
 /usr/include/x86_64-linux-gnu/bits/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/types/wint_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/FILE.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/c++/7/exception /usr/include/c++/7/bits/exception.h \
 /usr/include/c++/7/bits/exception_ptr.h \
 /usr/include/c++/7/bits/exception_defines.h \
 /usr/include/c++/7/bits/cxxabi_init_exception.h \
 /usr/include/c++/7/typeinfo /usr/include/c++/7/bits/hash_bytes.h \
 /usr/include/c++/7/new /usr/include/c++/7/bits/nested_exception.h \
 /usr/include/c++/7/bits/move.h /usr/include/c++/7/bits/concept_check.h \
 /usr/include/c++/7/type_traits /usr/include/c++/7/bits/char_traits.h \
 /usr/include/c++/7/bits/stl_algobase.h \
 /usr/include/c++/7/bits/functexcept.h \
 /usr/include/c++/7/bits/cpp_type_traits.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/include/c++/7/ext/numeric_traits.h \
 /usr/include/c++/7/bits/stl_pair.h \
 /usr/include/c++/7/bits/stl_iterator_base_types.h \
 /usr/include/c++/7/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/7/debug/assertions.h \
 /usr/include/c++/7/bits/stl_iterator.h \
 /usr/include/c++/7/bits/ptr_traits.h /usr/include/c++/7/debug/debug.h \
 /usr/include/c++/7/bits/predefined_ops.h /usr/include/c++/7/cstdint \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h /usr/include/stdint.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/c++/7/bits/ios_base.h /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/x86_64-linux-gnu/bits/setjmp.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/atomic_word.h \
 /usr/include/c++/7/bits/locale_classes.h /usr/include/c++/7/string \
 /usr/include/c++/7/bits/allocator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h \
 /usr/include/c++/7/ext/new_allocator.h \
 /usr/include/c++/7/bits/ostream_insert.h \
 /usr/include/c++/7/bits/cxxabi_forced.h \
 /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/backward/binders.h \
 /usr/include/c++/7/bits/range_access.h \
 /usr/include/c++/7/initializer_list \
 /usr/include/c++/7/bits/basic_string.h \
 /usr/include/c++/7/ext/alloc_traits.h \
 /usr/include/c++/7/bits/alloc_traits.h \
 /usr/include/c++/7/ext/string_conversions.h /usr/include/c++/7/cstdlib \
 /usr/include/stdlib.h /usr/include/x86_64-linux-gnu/bits/waitflags.h \
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
 /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h /usr/include/alloca.h \
 /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
 /usr/include/c++/7/bits/std_abs.h /usr/include/c++/7/cstdio \
 /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/libio.h \
 /usr/include/x86_64-linux-gnu/bits/_G_config.h \
 /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
 /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
 /usr/include/c++/7/cerrno /usr/include/errno.h \
 /usr/include/x86_64-linux-gnu/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/x86_64-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 /usr/include/c++/7/bits/functional_hash.h \
 /usr/include/c++/7/bits/basic_string.tcc \
 /usr/include/c++/7/bits/locale_classes.tcc \
 /usr/include/c++/7/system_error \
 /usr/include/x86_64-linux-gnu/c++/7/bits/error_constants.h \
 /usr/include/c++/7/stdexcept /usr/include/c++/7/streambuf \
 /usr/include/c++/7/bits/streambuf.tcc \
 /usr/include/c++/7/bits/basic_ios.h \
 /usr/include/c++/7/bits/locale_facets.h /usr/include/c++/7/cwctype \
 /usr/include/wctype.h /usr/include/x86_64-linux-gnu/bits/wctype-wchar.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_base.h \
 /usr/include/c++/7/bits/streambuf_iterator.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/ctype_inline.h \
 /usr/include/c++/7/bits/locale_facets.tcc \
 /usr/include/c++/7/bits/basic_ios.tcc \
 /usr/include/c++/7/bits/ostream.tcc /usr/include/c++/7/istream \
 /usr/include/c++/7/bits/istream.tcc /usr/include/c++/7/fstream \
 /usr/include/c++/7/bits/codecvt.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/basic_file.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++io.h \
 /usr/include/c++/7/bits/fstream.tcc \
 ../../../src/Core/types/PlayerTypes.h \
 ../../../src/Core/types/SystemTypes.h \
 ../../../src/Core/types/ObjectTypes.h \
 ../../../src/Core/types/CreatureTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/ZoneTypes.h \
 ../../../src/Core/types/QuestTypes.h ../../../src/Core/types/ShopTypes.h \
 ../../../src/Core/types/ItemTypes.h ../../../src/Core/types/GuildTypes.h \
 ../../../src/Core/types/WarTypes.h ../../../src/Core/types/ServerType.h \
 ../../../src/Core/Utility.h /usr/include/c++/7/cstring \
 /usr/include/string.h /usr/include/strings.h \
 ../../../src/Core/StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 CBillingInfo.h ../../../src/Core/SocketInputStream.h \
 ../../../src/Core/Exception.h ../../../src/Core/Socket.h \
 ../../../src/Core/SocketImpl.h ../../../src/Core/SocketAPI.h \
 ../../../src/Core/SocketOutputStream.h
