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
VSHOME  = ../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
LOGDIR  = $(VSHOME)/log
SRCDIR  = ..
COREDIR = ../Core
DBDIR    = ./database


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(DBDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<


#----------------------------------------------------------------------
# Server Core Library
#----------------------------------------------------------------------
SERVER_CORE_OBJS = CondVar.o LogData.o LogClient.o Mutex.o PlayerManager.o GameWorldInfoManager.o SystemAPI.o Thread.o ThreadAttr.o Timeval.o pthreadAPI.o Profile.o PacketProfile.o GameServerInfoManager.o PaySystem.o
SERVER_CORE_LIB  = $(LIBDIR)/libServerCore.a

SERVER_CORE_SRCS = $(SERVER_CORE_OBJS:.o=.cpp)

DEPS = $(SERVER_CORE_SRCS:%.cpp=$(DEPDIR)/%.d)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(BINDIR) $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C chinabilling
	$(MAKE) -C gameserver
	$(MAKE) -C loginserver
	$(MAKE) -C sharedserver
	# $(MAKE) -C updateserver

server : $(SERVER_CORE_LIB)

allgameserver : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C chinabilling
	$(MAKE) -C gameserver

allloginserver : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C chinabilling
	$(MAKE) -C loginserver

allsharedserver : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C sharedserver

alltheoneserver : $(SERVER_CORE_LIB)
	$(MAKE) -C theoneserver

$(SERVER_CORE_LIB) : $(SERVER_CORE_OBJS)
	ar rc $@ $^

clean :
	$(MAKE) -C database clean
	$(MAKE) -C chinabilling clean
	$(MAKE) -C loginserver clean
	$(MAKE) -C gameserver clean
	$(MAKE) -C updateserver clean
	$(MAKE) -C sharedserver clean
	rm -rf *.o

cleanloginserver :
	$(MAKE) -C database clean
	$(MAKE) -C chinabilling clean
	$(MAKE) -C loginserver clean
	rm -rf *.o

cleangameserver :
	$(MAKE) -C database clean
	$(MAKE) -C chinabilling clean
	$(MAKE) -C gameserver clean
	rm -rf *.o

cleansharedserver :
	$(MAKE) -C database clean
	$(MAKE) -C sharedserver clean
	rm -rf *.o

cleanall :
	$(MAKE) -C database cleanall
	$(MAKE) -C chinabilling cleanall
	$(MAKE) -C loginserver cleanall
	$(MAKE) -C gameserver cleanall
	$(MAKE) -C updateserver cleanall
	$(MAKE) -C sharedserver cleanall
	rm -rf *.o $(SERVER_CORE_LIB)

$(BINDIR) :
	mkdir -p $(BINDIR)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
