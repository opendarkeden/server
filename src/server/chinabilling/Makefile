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

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
