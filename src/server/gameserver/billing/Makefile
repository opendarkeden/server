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
SRCS = \
	CommonBillingPacket.cpp \
	CommonBillingPacketHandler.cpp \
	BillingPlayer.cpp	\
	BillingPlayerManager.cpp \
	BillingPlayerInfo.cpp

GS_OBJS = $(SRCS:%.cpp=%.gs.o)
LS_OBJS = $(SRCS:%.cpp=%.ls.o)
GS_DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.gs.d)
LS_DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.ls.d)

DEPFLAGS = -MT $@ -MMD -MP -MF 
DEPDIR = .deps
%.o : %.cpp

%.gs.o : %.cpp $(DEPDIR)/%.gs.d | $(DEPDIR)
	$(CC) $(DEPFLAGS) $(DEPDIR)/$*.gs.d $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -c $(OUTPUT_OPTION) $<

%.ls.o : %.cpp $(DEPDIR)/%.ls.d | $(DEPDIR)
	$(CC) $(DEPFLAGS) $(DEPDIR)/$*.ls.d $(CCFLAGS) $(DEFS)-D__LOGIN_SERVER__ $(INCLUDES) -c $(OUTPUT_OPTION) $<

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

$(DEPDIR):
	@mkdir -p $@

$(GS_DEPS):
$(LS_DEPS):

include $(wildcard $(GS_DEPS))
include $(wildcard $(LS_DEPS))
