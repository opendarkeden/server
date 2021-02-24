#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
VSHOME  = ../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = ..
SERVDIR = ../../server
USDIR   = $(SERVDIR)/updateserver
CLIDIR  = ../../client
UCDIR   = $(CLIDIR)/updateclient


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .us.o .uc.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__UPDATE_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(USDIR) -I$(SERVDIR)
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 

TARGET1 = $(LIBDIR)/libUpdateServerPackets.a
# TARGET2 = $(LIBDIR)/libUpdateClientPackets.a

SRCS	= \
		CUBeginUpdate.cpp CUBeginUpdateHandler.cpp \
		CURequest.cpp \
		CUEndUpdate.cpp CUEndUpdateHandler.cpp \
		CURequestLoginMode.cpp CURequestLoginModeHandler.cpp \
		UCUpdate.cpp UCUpdateHandler.cpp \
		UCUpdateList.cpp UCUpdateListHandler.cpp \
		UCRequestLoginMode.cpp UCRequestLoginModeHandler.cpp \
	  CURequestHandler.cpp

# OBJS2	= \
# 		CUBeginUpdate.uc.o CUBeginUpdateHandler.uc.o \
# 		CURequest.uc.o \
# 		CUEndUpdate.uc.o CUEndUpdateHandler.uc.o \
# 		CURequestLoginMode.uc.o CURequestLoginModeHandler.uc.o \
# 		UCUpdate.uc.o UCUpdateHandler.uc.o \
# 		UCUpdateList.uc.o UCUpdateListHandler.uc.o \
# 		UCRequestLoginMode.uc.o UCRequestLoginModeHandler.uc.o \
# 	  CURequestHandler.uc.o 

# SRCS	= $(OBJS1:.us.o=.cpp)

# .cpp.uc.o : 
# 	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_CLIENT__ $(INCLUDES) -I$(UCDIR) -o $*.uc.o $<


OBJS = $(SRCS:.cpp=.o)

DEPDIR = .deps
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

# .cpp.us.o : 
# 	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_SERVER__ $(INCLUDES) -I$(USDIR) -I$(SERVDIR) -o $*.us.o $<



#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

# all : $(TARGET1) $(TARGET2)
all : $(TARGET1)

allloginserver : $(TARGET1) $(TARGET2)

allgameserver : $(TARGET1) $(TARGET2)

$(TARGET1) : $(OBJS)
	ar rc $@ $(OBJS)

# $(TARGET2) : $(OBJS2)
# 	ar rc $@ $(OBJS2)

clean :
	rm -rf *.o

cleanloginserver :
	rm -rf *.o

cleangameserver :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET1) $(TARGET2)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
