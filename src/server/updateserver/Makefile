#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
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
SRCDIR   = ../..
COREDIR  = ../../Core
SERVDIR  = ..
DBDIR    = ../database


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__UPDATE_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS     = -L$(LIBDIR) -lUpdateServerPackets -lServerCore -lCore
SYSLIBS  = -lpthread -lnsl

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS   = main.o UpdateServer.o UpdateServerPlayer.o
SRCS   = $(OBJS:.o=.cpp)
TARGET = $(BINDIR)/updateserver
UPDATE = $(BINDIR)/update

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET) $(UPDATE)

$(TARGET) : $(OBJS) $(LIBDIR)/libUpdateServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)

$(UPDATE) : update.o $(LIBDIR)/libCore.a
	$(CC) -o $@ update.o -L$(LIBDIR) -lCore

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET) $(UPDATE)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
