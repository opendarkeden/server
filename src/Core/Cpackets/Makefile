#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
#VSHOME  = 
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = $(SRCDIR)/Core
SERVDIR = $(SRCDIR)/server
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
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__ 
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR)

CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o : 
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) -I$(SERVDIR) -I$(GSDIR) -I$(DBDIR) -o $*.o $<

#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

all : 
	$(MAKE) -C GS
	$(MAKE) -C LS
	$(MAKE) -C SS

allloginserver : 
	$(MAKE) -C LS

allgameserver :
	$(MAKE) -C GS

allsharedserver :
	$(MAKE) -C SS

clean :
	$(MAKE) -C GS clean
	$(MAKE) -C LS clean
	$(MAKE) -C SS clean

cleanall :
	$(MAKE) -C GS cleanll
	$(MAKE) -C LS cleanll
	$(MAKE) -C SS cleanll

depall :
	refreshSrc
	$(MAKE) -C GS depall
	$(MAKE) -C LS depall
	$(MAKE) -C SS depall

dep :

# DO NOT DELETE
