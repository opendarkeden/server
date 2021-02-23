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
		CURequest.us.o \
		CUEndUpdate.us.o CUEndUpdateHandler.us.o \
		CURequestLoginMode.us.o CURequestLoginModeHandler.us.o \
		UCUpdate.us.o UCUpdateHandler.us.o \
		UCUpdateList.us.o UCUpdateListHandler.us.o \
		UCRequestLoginMode.us.o UCRequestLoginModeHandler.us.o \
	# CURequestHandler.us.o

OBJS2	= \
		CUBeginUpdate.uc.o CUBeginUpdateHandler.uc.o \
		CURequest.uc.o \
		CUEndUpdate.uc.o CUEndUpdateHandler.uc.o \
		CURequestLoginMode.uc.o CURequestLoginModeHandler.uc.o \
		UCUpdate.uc.o UCUpdateHandler.uc.o \
		UCUpdateList.uc.o UCUpdateListHandler.uc.o \
		UCRequestLoginMode.uc.o UCRequestLoginModeHandler.uc.o \
	# CURequestHandler.uc.o 

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
CUBeginUpdate.o: CUBeginUpdate.cpp /usr/include/stdc-predef.h \
 CUBeginUpdate.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../UpdateManager.h ../Update.h \
 ../UpdateDef.h ../Assert.h ../Resource.h /usr/include/c++/7/stdlib.h \
 ../ResourceManager.h ../Properties.h /usr/include/c++/7/map \
 /usr/include/c++/7/bits/stl_tree.h /usr/include/c++/7/bits/stl_map.h \
 /usr/include/c++/7/tuple /usr/include/c++/7/utility \
 /usr/include/c++/7/bits/stl_relops.h /usr/include/c++/7/array \
 /usr/include/c++/7/bits/uses_allocator.h \
 /usr/include/c++/7/bits/invoke.h /usr/include/c++/7/bits/stl_multimap.h
CUBeginUpdateHandler.o: CUBeginUpdateHandler.cpp \
 /usr/include/stdc-predef.h CUBeginUpdate.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../UpdateManager.h ../Update.h \
 ../UpdateDef.h ../Assert.h ../Resource.h /usr/include/c++/7/stdlib.h \
 ../ResourceManager.h
CURequest.o: CURequest.cpp /usr/include/stdc-predef.h CURequest.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../Resource.h ../UpdateDef.h \
 /usr/include/c++/7/stdlib.h
CURequestHandler.o: CURequestHandler.cpp /usr/include/stdc-predef.h \
 CURequest.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../Resource.h ../UpdateDef.h \
 /usr/include/c++/7/stdlib.h
CUEndUpdate.o: CUEndUpdate.cpp /usr/include/stdc-predef.h CUEndUpdate.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h
CUEndUpdateHandler.o: CUEndUpdateHandler.cpp /usr/include/stdc-predef.h \
 CUEndUpdate.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h
CURequestLoginMode.o: CURequestLoginMode.cpp /usr/include/stdc-predef.h \
 CURequestLoginMode.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h
CURequestLoginModeHandler.o: CURequestLoginModeHandler.cpp \
 /usr/include/stdc-predef.h CURequestLoginMode.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h
UCUpdate.o: UCUpdate.cpp /usr/include/stdc-predef.h UCUpdate.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../Resource.h ../UpdateDef.h \
 /usr/include/c++/7/stdlib.h
UCUpdateHandler.o: UCUpdateHandler.cpp /usr/include/stdc-predef.h \
 UCUpdate.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../Resource.h ../UpdateDef.h \
 /usr/include/c++/7/stdlib.h
UCUpdateList.o: UCUpdateList.cpp /usr/include/stdc-predef.h \
 UCUpdateList.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../UpdateManager.h ../Update.h \
 ../UpdateDef.h ../Assert.h ../Resource.h /usr/include/c++/7/stdlib.h \
 ../ResourceManager.h
UCUpdateListHandler.o: UCUpdateListHandler.cpp /usr/include/stdc-predef.h \
 UCUpdateList.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h ../UpdateManager.h ../Update.h \
 ../UpdateDef.h ../Assert.h ../Resource.h /usr/include/c++/7/stdlib.h \
 ../ResourceManager.h
UCRequestLoginMode.o: UCRequestLoginMode.cpp /usr/include/stdc-predef.h \
 UCRequestLoginMode.h ../Packet.h ../Types.h ../types/SystemTypes.h \
 /usr/include/x86_64-linux-gnu/sys/types.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h
UCRequestLoginModeHandler.o: UCRequestLoginModeHandler.cpp \
 /usr/include/stdc-predef.h UCRequestLoginMode.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/x86_64-linux-gnu/sys/types.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h \
 /usr/include/x86_64-linux-gnu/bits/types/clock_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/time_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/timer_t.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/x86_64-linux-gnu/bits/endian.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap.h \
 /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
 /usr/include/x86_64-linux-gnu/bits/uintn-identity.h \
 /usr/include/x86_64-linux-gnu/sys/select.h \
 /usr/include/x86_64-linux-gnu/bits/select.h \
 /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h \
 /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/sysmacros.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
 /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h \
 /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h \
 /usr/include/c++/7/iostream \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++config.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/os_defines.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/cpu_defines.h \
 /usr/include/c++/7/ostream /usr/include/c++/7/ios \
 /usr/include/c++/7/iosfwd /usr/include/c++/7/bits/stringfwd.h \
 /usr/include/c++/7/bits/memoryfwd.h /usr/include/c++/7/bits/postypes.h \
 /usr/include/c++/7/cwchar /usr/include/wchar.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/x86_64-linux-gnu/bits/floatn.h \
 /usr/include/x86_64-linux-gnu/bits/floatn-common.h \
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
 /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h \
 /usr/include/c++/7/bits/localefwd.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/c++locale.h \
 /usr/include/c++/7/clocale /usr/include/locale.h \
 /usr/include/x86_64-linux-gnu/bits/locale.h /usr/include/c++/7/cctype \
 /usr/include/ctype.h /usr/include/c++/7/bits/ios_base.h \
 /usr/include/c++/7/ext/atomicity.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr.h \
 /usr/include/x86_64-linux-gnu/c++/7/bits/gthr-default.h \
 /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/x86_64-linux-gnu/bits/sched.h \
 /usr/include/x86_64-linux-gnu/bits/cpu-set.h /usr/include/time.h \
 /usr/include/x86_64-linux-gnu/bits/time.h \
 /usr/include/x86_64-linux-gnu/bits/timex.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h \
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
 /usr/include/x86_64-linux-gnu/bits/waitstatus.h /usr/include/alloca.h \
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
 /usr/include/c++/7/bits/fstream.tcc ../types/PlayerTypes.h \
 ../types/SystemTypes.h ../types/ObjectTypes.h ../types/CreatureTypes.h \
 ../types/ItemTypes.h ../types/ZoneTypes.h ../types/QuestTypes.h \
 ../types/ShopTypes.h ../types/ItemTypes.h ../types/GuildTypes.h \
 ../types/WarTypes.h ../types/ServerType.h ../Utility.h \
 /usr/include/c++/7/cstring /usr/include/string.h /usr/include/strings.h \
 ../Exception.h ../StringStream.h /usr/include/c++/7/list \
 /usr/include/c++/7/bits/stl_list.h \
 /usr/include/c++/7/bits/allocated_ptr.h \
 /usr/include/c++/7/ext/aligned_buffer.h /usr/include/c++/7/bits/list.tcc \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 /usr/include/netinet/in.h /usr/include/x86_64-linux-gnu/sys/socket.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_iovec.h \
 /usr/include/x86_64-linux-gnu/bits/socket.h \
 /usr/include/x86_64-linux-gnu/bits/socket_type.h \
 /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
 /usr/include/x86_64-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/x86_64-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/x86_64-linux-gnu/bits/types/struct_osockaddr.h \
 /usr/include/x86_64-linux-gnu/bits/in.h ../SocketOutputStream.h \
 ../PacketFactory.h ../Packet.h
