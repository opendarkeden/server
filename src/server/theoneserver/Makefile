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
MYSQLDIR = /usr/local/lib/mysql

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__THE_ONE_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBINCDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS     = -L$(LIBDIR) -lCore -lTheOneServerPackets -lServerCore 
#LIBS     = -L$(LIBDIR) -lTheOneServerPackets -lItems -lQuest -lGameServerDatabase -lServerCore -lGameServerPackets -lSkill -lCore -lGameServerBilling -lLuaScript -lGameServerTest -lWar -lCouple -lMission -lCTF -lGameServerCBilling
SYSLIBS  = -L$(MYSQLDIR) -static -lmysqlclient -lpthread -lnsl -lz

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS = \
	TheOneServer.o \
	GameServerManager.o \
	main.o \
	PacketFactoryManager.o \
	DatabaseManager.o \
	Connection.o \
	Result.o \
	Statement.o \

SRCS = $(OBJS:.o=.cpp)

TARGET = $(BINDIR)/theoneserver


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
$(TARGET) : $(OBJS) $(LIBDIR)/libTheOneServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a 

#$(TARGET) : $(OBJS) $(LIBDIR)/libTheOneServerPackets.a $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libSkill.a $(LIBDIR)/libGameServerPackets.a $(LIBDIR)/libItems.a $(LIBDIR)/libQuest.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a $(LIBDIR)/libSharedServerPackets.a $(LIBDIR)/libGameServerBilling.a $(LIBDIR)/libLuaScript.a $(LIBDIR)/libGameServerTest.a $(LIBDIR)/libWar.a $(LIBDIR)/libCouple.a $(LIBDIR)/libMission.a $(LIBDIR)/libCTF.a $(LIBDIR)/libGameServerCBilling.a
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
