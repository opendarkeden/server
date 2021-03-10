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
VSHOME = ../..
BINDIR = $(VSHOME)/bin
LIBDIR = $(VSHOME)/lib
LOGDIR = $(VSHOME)/log

#----------------------------------------------------------------------
# Core Library
#----------------------------------------------------------------------
CORE_OBJS = WarInfo.o RaceWarInfo.o GuildWarInfo.o LevelWarInfo.o BloodBibleBonusInfo.o \
			Assert.o Datagram.o SerialDatagram.o DatagramSocket.o FileAPI.o GameTime.o \
			ScriptParameter.o \
			Player.o PCSlayerInfo.o PCVampireInfo.o PCSlayerInfo2.o \
			PCVampireInfo2.o PCSlayerInfo3.o PCVampireInfo3.o \
			Properties.o Resource.o ResourceManager.o \
			ServerSocket.o Socket.o SocketAPI.o SocketImpl.o \
			SocketInputStream.o SocketOutputStream.o StringStream.o \
			Update.o UpdateManager.o InventoryInfo.o InventorySlotInfo.o \
			RideMotorcycleInfo.o RideMotorcycleSlotInfo.o \
			GearSlotInfo.o GearInfo.o ExtraInfo.o \
			ExtraSlotInfo.o PCItemInfo.o SubItemInfo.o \
			ModifyInfo.o ModifyItemInfo.o \
			EffectInfo.o SlayerSkillInfo.o VampireSkillInfo.o \
			SubSlayerSkillInfo.o SubVampireSkillInfo.o Utility.o VSDateTime.o ServerGroupInfo.o TimeChecker.o\
			NPCInfo.o Shape.o Geometry.o WorldInfo.o GuildInfo.o GuildMemberInfo.o \
			GuildInfo2.o GuildMemberInfo2.o \
			Encrypter.o	SocketEncryptInputStream.o SocketEncryptOutputStream.o \
			OustersSkillInfo.o PCOustersInfo.o PCOustersInfo2.o PCOustersInfo3.o SubOustersSkillInfo.o \
			ItemNameInfo.o SweeperBonusInfo.o PetInfo.o NicknameInfo.o QuestStatusInfo.o \
			BloodBibleSignInfo.o StoreInfo.o SXml.o

CORE_SRCS = $(CORE_OBJS:.o=.cpp)
CORE_LIB = $(LIBDIR)/libCore.a

LC_PACKET_SRC = LCCreatePCError.cpp LCLoginOK.cpp LCRegisterPlayerError.cpp LCVersionCheckOK.cpp \
  LCDeletePCOK.cpp LCQueryResultPlayerID.cpp LCServerList.cpp \
  LCCreatePCOK.cpp LCPCList.cpp LCRegisterPlayerOK.cpp LCWorldList.cpp \
  LCLoginError.cpp LCReconnect.cpp LCVersionCheckError.cpp  \
  LCDeletePCError.cpp LCQueryResultCharacterName.cpp LCSelectPCError.cpp

LG_PACKET_SRC := LGIncomingConnection.cpp LGIncomingConnectionError.cpp LGIncomingConnectionOK.cpp LGKickCharacter.cpp

CL_PACKET_SRC := CLCreatePC.cpp CLGetPCList.cpp CLGetWorldList.cpp \
	CLLogout.cpp CLQueryPlayerID.cpp CLRegisterPlayer.cpp CLSelectServer.cpp \
	CLVersionCheck.cpp CLChangeServer.cpp CLDeletePC.cpp CLGetServerList.cpp \
	CLLogin.cpp CLQueryCharacterName.cpp CLReconnectLogin.cpp CLSelectPC.cpp CLSelectWorld.cpp

GL_PACKET_SRC := GLIncomingConnection.cpp  GLIncomingConnectionError.cpp GLIncomingConnectionOK.cpp GLKickVerify.cpp

L_HANDLER_SRC := CLDeletePCHandler.cpp CLGetWorldListHandler.cpp  CLQueryCharacterNameHandler.cpp \
	CLRegisterPlayerHandler.cpp  CLSelectWorldHandler.cpp              GLIncomingConnectionHandler.cpp \
	CLChangeServerHandler.cpp  CLGetPCListHandler.cpp      CLLoginHandler.cpp         CLQueryPlayerIDHandler.cpp \
	CLSelectPCHandler.cpp        CLVersionCheckHandler.cpp             GLIncomingConnectionOKHandler.cpp \
	CLCreatePCHandler.cpp      CLGetServerListHandler.cpp  CLLogoutHandler.cpp        CLReconnectLoginHandler.cpp \
	CLSelectServerHandler.cpp    GLIncomingConnectionErrorHandler.cpp  GLKickVerifyHandler.cpp

#----------------------------------------------------------------------
# Packet Library for LoginServer
#----------------------------------------------------------------------
LS_PACKET_OBJS = PacketFactoryManager.ls.o PacketIDSet.ls.o PacketValidator.ls.o
LS_LIB_OBJS := $(LC_PACKET_SRC:.cpp=.o) $(LG_PACKET_SRC:.cpp=.o) $(CL_PACKET_SRC:.cpp=.o) $(GL_PACKET_SRC:.cpp=.o) $(L_HANDLER_SRC:.cpp=.ls.o) $(LS_PACKET_OBJS)
LS_PACKET_LIB  = $(LIBDIR)/libLoginServerPackets.a


SRCS = $(CORE_SRCS) $(LC_PACKET_SRC) $(LG_PACKET_SRC) $(CL_PACKET_SRC) $(GL_PACKET_SRC) $(L_HANDLER_SRC)

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o .gs.o .ls.o .us.o .ss.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I./loki -I.
CCFLAGS  = -Wall -c -g  

# .cpp.o : 
# 	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.cpp.gs.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -o $*.gs.o $<

.cpp.ls.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__LOGIN_SERVER__ $(INCLUDES) -o $*.ls.o $<

.cpp.us.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_SERVER__ $(INCLUDES) -o $*.us.o $<

.cpp.ss.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__SHARED_SERVER__ $(INCLUDES) -o $*.ss.o $<

#----------------------------------------------------------------------
# Packet Library for GameServer
#----------------------------------------------------------------------
GS_PACKET_OBJS = PacketFactoryManager.gs.o PacketIDSet.gs.o PacketValidator.gs.o
GS_PACKET_SRCS = $(GS_PACKET_OBJS:.gs.o=.cpp)
GS_PACKET_LIB  = $(LIBDIR)/libGameServerPackets.a

#----------------------------------------------------------------------
# Packet Library for Updateserver 
#----------------------------------------------------------------------
US_PACKET_OBJS = PacketFactoryManager.us.o PacketIDSet.us.o PacketValidator.us.o
US_PACKET_SRCS = $(US_PACKET_OBJS:.us.o=.cpp)
US_PACKET_LIB  = $(LIBDIR)/libUpdateServerPackets.a

#----------------------------------------------------------------------
# Packet Library for SharedServer
#----------------------------------------------------------------------
SS_PACKET_OBJS = PacketFactoryManager.ss.o PacketIDSet.ss.o PacketValidator.ss.o
SS_PACKET_SRCS = $(SS_PACKET_OBJS:.ss.o=.cpp)
SS_PACKET_LIB  = $(LIBDIR)/libSharedServerPackets.a

#----------------------------------------------------------------------
# All Targets
#----------------------------------------------------------------------
#TARGETS = $(CORE_LIB) $(LS_PACKET_LIB) $(GS_PACKET_LIB) $(LCC_PACKET_LIB) 
#SRCS = $(CORE_SRCS) $(LS_PACKET_SRCS) $(GS_PACKET_SRCS) $(LCC_PACKET_SRCS) $(US_PACKET_SRCS) $(SS_PACKET_SRCS)
TARGETS = $(CORE_LIB) $(LS_PACKET_LIB) $(GS_PACKET_LIB) $(US_PACKET_LIB) $(SS_PACKET_LIB)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------

all : $(TARGETS)
	# $(MAKE) -C Lpackets
	$(MAKE) -C Gpackets
	$(MAKE) -C Cpackets
	$(MAKE) -C Upackets
	$(MAKE) -C Spackets

core : $(CORE_LIB)

allloginserver : $(TARGETS)
	$(MAKE) -C Lpackets allloginserver
	$(MAKE) -C Gpackets allloginserver
	$(MAKE) -C Cpackets allloginserver
	$(MAKE) -C Upackets allloginserver
	$(MAKE) -C Spackets allloginserver

allgameserver : $(TARGETS)
	$(MAKE) -C Lpackets allgameserver
	$(MAKE) -C Gpackets allgameserver
	$(MAKE) -C Cpackets allgameserver
	$(MAKE) -C Upackets allgameserver
	$(MAKE) -C Spackets allgameserver
	$(MAKE) -C TOpackets allgameserver

allsharedserver : $(TARGETS)
	$(MAKE) -C Lpackets allsharedserver
	$(MAKE) -C Gpackets allsharedserver
	$(MAKE) -C Cpackets allsharedserver
	$(MAKE) -C Spackets allsharedserver
#	$(MAKE) -C Upackets allsharedserver

alltheoneserver : $(CORE_LIB)
	$(MAKE) -C TOpackets alltheoneserver

$(CORE_LIB) : $(CORE_OBJS)
	ar rc $@ $^

$(LS_PACKET_LIB) : $(LS_LIB_OBJS)
	ar rc $@ $^

$(GS_PACKET_LIB) : $(GS_PACKET_OBJS)
	ar rc $@ $^

$(LCC_PACKET_LIB) : $(LCC_PACKET_OBJS)
	ar rc $@ $^

$(US_PACKET_LIB) : $(US_PACKET_OBJS)
	ar rc $@ $^

$(SS_PACKET_LIB) : $(SS_PACKET_OBJS)
	ar rc $@ $^

clean :
	$(MAKE) -C Lpackets clean
	$(MAKE) -C Gpackets clean
	$(MAKE) -C Cpackets clean
	$(MAKE) -C Upackets clean
	$(MAKE) -C Spackets clean
	$(MAKE) -C TOpackets clean
	rm -rf *.o

cleanall :
	$(MAKE) -C Lpackets cleanall
	$(MAKE) -C Gpackets cleanall
	$(MAKE) -C Cpackets cleanall
	$(MAKE) -C Upackets cleanall
	$(MAKE) -C Spackets cleanall
	$(MAKE) -C TOpackets cleanall
	rm -rf *.o $(TARGETS)

cleangameserver :
	$(MAKE) -C Lpackets cleangameserver
	$(MAKE) -C Gpackets cleangameserver
	$(MAKE) -C Cpackets cleangameserver
	$(MAKE) -C Upackets cleangameserver
	$(MAKE) -C Spackets cleangameserver
	$(MAKE) -C TOpackets cleangameserver
	rm -rf *.o $(TARGETS)

cleanloginserver :
	$(MAKE) -C Lpackets cleanloginserver
	$(MAKE) -C Gpackets cleanloginserver
	$(MAKE) -C Cpackets cleanloginserver
	$(MAKE) -C Upackets cleanloginserver
	$(MAKE) -C Spackets cleanloginserver
	rm -rf *.o $(TARGETS)

cleansharedserver :
	$(MAKE) -C Lpackets cleansharedserver
	$(MAKE) -C Gpackets cleansharedserver
	$(MAKE) -C Cpackets cleansharedserver
	$(MAKE) -C Upackets cleansharedserver
	$(MAKE) -C Spackets cleansharedserver
	rm -rf *.o $(TARGETS)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
