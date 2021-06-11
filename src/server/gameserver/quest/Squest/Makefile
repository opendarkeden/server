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
VSHOME   = ../../../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../../../..
COREDIR  = ../../../../Core
SERVDIR  = ../../..
DBDIR    = ../../../database
MYSQLDIR = /usr/local/lib/mysql
GSDIR    = ../..
SKILLDIR = ../../skill
ITEMDIR  = ../../item
QUESTDIR  = ..


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__ 
#-D__QUEST_TEST__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(QUESTDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

#LIBS     = -L$(LIBDIR) -lGameServerDatabase -lServerCore -lGameServerPackets -lCore
#SYSLIBS  = -L$(MYSQLDIR) -static -lpthread -lnsl -lmysqlclient -lz


DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

SIMPLE_QUEST_OBJS = MonsterKillQuest.o  \
					QuestFactoryManager.o \
					Quest.o \
					QuestManager.o \
					QuestBoard.o  \
					QuestPrice.o \
					QuestPriceReward.o \
					QuestPricePenalty.o \
					SimpleQuest.o \
					SimpleQuestLoader.o \
					QuestEvent.o \
					MonsterSelector.o

#							\
					main.o \
					FakeMonsterInfo.o
					              
OBJS = $(SIMPLE_QUEST_OBJS)
SRCS = $(OBJS:.o=.cpp)
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

TARGET   = $(LIBDIR)/libSimpleQuest.a
#TARGET = qt


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET)

$(TARGET) : $(OBJS)
	ar rc $@ $^

#$(TARGET) : $(OBJS) $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libCore.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libGameServerPackets.a
#	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)


clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
