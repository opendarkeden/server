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
GSDIR    = $(SERVDIR)/gameserver
LSDIR    = $(SERVDIR)/loginserver
BILLDIR  = $(GSDIR)/billing
MYSQLDIR = /usr/local/lib/mysql


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o .gs.o .ls.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I.
#CCFLAGS  = -Wall -c -g  
CCFLAGS  = -Wall -c -g 
#LIBS     = -L$(LIBDIR) -lServerCore -lCore
#SYSLIBS  = -static -lpthread -ldl -lnsl -lz

# < for Library >
TARGET     = $(LIBDIR)/libMofus.a

#BINTARGET	= $(BINDIR)/mofus

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

#	main.o
OBJS = \
	Mofus.o \
	MPacketManager.o \
	MPlayer.o \
	MPlayerManager.o \
	PKTConnectAccept.o \
	PKTConnectAcceptHandler.o \
	PKTConnectAsk.o \
	PKTError.o \
	PKTErrorHandler.o \
	PKTLogout.o \
	PKTPowerPoint.o \
	PKTPowerPointHandler.o \
	PKTReceiveOK.o \
	PKTResult.o \
	PKTUserInfo.o \
	PKTSError.o

#BINOBJS = main.o StringParser.o

SRCS = $(OBJS:.o=.cpp)

DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET)

#bin : $(BINTARGET)

# < for Library >
$(TARGET) : $(OBJS)
	ar r $@ $(OBJS)

#$(BINTARGET) : $(BINOBJS) $(OBJS) $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a
#	$(CC) -o $@ $(BINOBJS) $(OBJS) $(LIBS) $(SYSLIBS) -rdynamic

# < for Test >
#$(TARGET) : $(OBJS) $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a 
#	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)


clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
