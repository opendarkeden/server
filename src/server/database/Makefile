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
DBINCDIR  = /usr/local/include/mysql
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
LOGDIR  = $(VSHOME)/log
SRCDIR  = $(VSHOME)/src
COREDIR = $(SRCDIR)/Core
SERVDIR = $(SRCDIR)/server


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o .gs.o .ls.o .us.o .ss.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBINCDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o : 
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

.cpp.gs.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -o $*.gs.o $<

.cpp.ls.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__LOGIN_SERVER__ $(INCLUDES) -o $*.ls.o $<

.cpp.us.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_SERVER__ $(INCLUDES) -o $*.us.o $<

.cpp.ss.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__SHARED_SERVER__ $(INCLUDES) -o $*.ss.o $<

#----------------------------------------------------------------------
# Server Core Library
#----------------------------------------------------------------------
DB_OBJS = Connection.o Statement.o Result.o DatabaseManager.o
DB_SRC  = $(DB_OBJS:.o=.cpp)
DB_LIB  = $(LIBDIR)/libDatabase.a

#----------------------------------------------------------------------
# Packet Library for GameServer
#----------------------------------------------------------------------
GS_DB_OBJS = Connection.gs.o Statement.gs.o Result.gs.o DatabaseManager.gs.o
GS_DB_SRCS = $(GS_DB_OBJS:.gs.o=.cpp)
GS_DB_LIB  = $(LIBDIR)/libGameServerDatabase.a

#----------------------------------------------------------------------
# Packet Library for LoginServer
#----------------------------------------------------------------------
LS_DB_OBJS = Connection.ls.o Statement.ls.o Result.ls.o DatabaseManager.ls.o
LS_DB_SRCS = $(LS_DB_OBJS:.ls.o=.cpp)
LS_DB_LIB  = $(LIBDIR)/libLoginServerDatabase.a

#----------------------------------------------------------------------
# Packet Library for Updateserver 
#----------------------------------------------------------------------
US_DB_OBJS = Connection.us.o Statement.us.o Result.gs.o DatabaseManager.us.o
US_DB_SRCS = $(US_DB_OBJS:.us.o=.cpp)
US_DB_LIB  = $(LIBDIR)/libUpdateServerDatabase.a

#----------------------------------------------------------------------
# Database Library for Updateserver 
#----------------------------------------------------------------------
SS_DB_OBJS = Connection.ss.o Statement.ss.o Result.ss.o DatabaseManager.ss.o
SS_DB_SRCS = $(SS_DB_OBJS:.ss.o=.cpp)
SS_DB_LIB  = $(LIBDIR)/libSharedServerDatabase.a

#----------------------------------------------------------------------
# All Targets
#----------------------------------------------------------------------
#TARGETS = $(CORE_LIB) $(LS_DB_LIB) $(GS_DB_LIB)
SRCS = $(LS_DB_SRCS) $(GS_DB_SRCS) $(US_DB_SRCS) $(SS_DB_SRCS)
TARGETS = $(DB_LIB) $(LS_DB_LIB) $(GS_DB_LIB) $(US_DB_LIB) $(SS_DB_LIB)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGETS)

$(DB_LIB) : $(DB_OBJS)
	ar rc $@ $^

$(LS_DB_LIB) : $(LS_DB_OBJS)
	ar rc $@ $^

$(GS_DB_LIB) : $(GS_DB_OBJS)
	ar rc $@ $^

$(US_DB_LIB) : $(US_DB_OBJS)
	ar rc $@ $^

$(SS_DB_LIB) : $(SS_DB_OBJS)
	ar rc $@ $^

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGETS)

depall : 
	gccmakedep $(SRCS) $(INCLUDES)

dep : 
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
