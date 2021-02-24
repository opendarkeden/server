#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
VSHOME  = ../../../..
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = $(VSHOME)/src/Core
SERVDIR = $(VSHOME)/src/server
DBDIR   = $(SERVDIR)/database
GSDIR   = $(SERVDIR)/gameserver
LSDIR   = $(SERVDIR)/loginserver
SSDIR   = $(SERVDIR)/sharedserver
SKILLDIR= $(GSDIR)/skill
ITEMDIR = $(GSDIR)/item
BILLINGDIR = $(GSDIR)/billing


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__SHARED_SERVER__ 
INCLUDES = -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(LSDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

TARGET_GS  = $(LIBDIR)/libGameServerPackets.a
TARGET_LS  = $(LIBDIR)/libLoginServerPackets.a
TARGET_SS  = $(LIBDIR)/libSharedServerPackets.a

TARGET = $(TARGET_SS)

include ../OBJS

DEPDIR = .deps
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

all : $(TARGET)

$(TARGET) : $(OBJS)
	ar r $@ $(OBJS)

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
