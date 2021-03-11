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
#LIBS     = -L$(LIBDIR) -lDatabase -lSharedServerPackets -lGameServerPackets -lServerCore -lCore
LIBS     = -L$(LIBDIR) -lDatabase -lSharedServerPackets -lServerCore -lCore
# SYSLIBS  = -L$(MYSQLDIR) -static -lmysqlclient -lpthread -lnsl -lz
#SYSLIBS  = -L$(MYSQLDIR) -lmysqlclient -lpthread -lnsl -lz -ldl -lutil -lpython2.2 -rdynamic
SYSLIBS  = -L$(MYSQLDIR) -lmysqlclient -lpthread -lnsl -lz -ldl

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<


#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS = \
	Guild.o GuildManager.o ResurrectLocationManager.o GameServerPlayer.o \
	HeartbeatManager.o GameServerInfoManager.o \
	GameServerGroupInfoManager.o GameServerManager.o \
	SharedServer.o main.o StringPool.o \

SRCS = $(OBJS:.o=.cpp)
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

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

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
