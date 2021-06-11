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
SRCS = \
	CBillingPacketErrorBody.cpp \
	CBillingPacketResponseLoginBody.cpp \
	CBillingPacketHeader.cpp \
	CBillingPacketResponseLogoutBody.cpp \
	CBillingPacketRequestIntervalValidationBody.cpp \
	CBillingPacketResponseMinusMinuteBody.cpp \
	CBillingPacketRequestLoginBody.cpp \
	CBillingPacketResponseMinusPointBody.cpp \
	CBillingPacketRequestLogoutBody.cpp \
	CBillingPlayer.cpp \
	CBillingPacketRequestMinusMinuteBody.cpp \
	CBillingPlayerInfo.cpp \
	CBillingPacketRequestMinusPointBody.cpp \
	CBillingPlayerManager.cpp \
	CBillingPacketResponseIntervalValidationBody.cpp \

GS_OBJS = $(SRCS:%.cpp=%.gs.o)
LS_OBJS = $(SRCS:%.cpp=%.ls.o)
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)
GSDEPS = $(SRCS:%.cpp=$(DEPDIR)/%.gs.d)
LSDEPS = $(SRCS:%.cpp=$(DEPDIR)/%.ls.d)

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF
GSDEPFLAGS = $(DEPFLAGS) $(DEPDIR)/$*.gs.d
LSDEPFLAGS = $(DEPFLAGS) $(DEPDIR)/$*.ls.d

COMPILE.gs.c = $(CC) $(GSDEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
COMPILE.ls.c = $(CC) $(LSDEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c

%.o : %.cpp

%.gs.o : %.cpp $(DEPDIR)/%.gs.d | $(DEPDIR)
	$(COMPILE.gs.c) -D__GAME_SERVER__ $(INCLUDES_GS) $(OUTPUT_OPTION) $<

%.ls.o : %.cpp $(DEPDIR)/%.gs.d | $(DEPDIR)
	$(COMPILE.ls.c) -D__LOGIN_SERVER__ $(INCLUDES_LS) $(OUTPUT_OPTION) $<

#.cpp.o :
#	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

# .cpp.o :
# 	$(CC) $(CCFLAGS) $(DEFS)  $(INCLUDES) -o $*.o $<

# .cpp.gs.o :
# 	$(CC) $(CCFLAGS) $(DEFS)  -D__GAME_SERVER__ $(INCLUDES_GS) -o $*.gs.o $<

# .cpp.ls.o :
# 	$(CC) $(CCFLAGS) $(DEFS)  -D__LOGIN_SERVER__ $(INCLUDES_LS) -o $*.ls.o $<

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------

# test:
# 	echo $(GSDEPS)

#all : $(TARGET)
# all : $(TARGET_GS) $(TARGET_LS) $(TARGET)
all : $(TARGET_GS) $(TARGET_LS)

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

# $(DEPS):

$(GSDEPS):
$(LSDEPS):

include $(wildcard $(DEPS))
include $(wildcard $(GSDEPS))
include $(wildcard $(LSDEPS))
