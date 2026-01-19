//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlayer.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_SLAYER_H__
#define __GC_ADD_SLAYER_H__

#include "EffectInfo.h"
#include "NicknameInfo.h"
#include "PCSlayerInfo3.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "PetInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayer;
// Packet sent when a Slayer enters view. If a player already knows about the
// Slayer (including itself) and it only moves, GCMove is used. When a Slayer
// is seen for the first time or appears after a move to another map, send
// GCAddSlayer so the client can build the full Slayer state.
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayer : public Packet {
public:
    GCAddSlayer();
    GCAddSlayer(const PCSlayerInfo3& slayerInfo);
    virtual ~GCAddSlayer() noexcept;

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    void execute(Player* pPlayer);
    PacketID_t getPacketID() const {
        return PACKET_GC_ADD_SLAYER;
    }
    PacketSize_t getPacketSize() const;
    string getPacketName() const {
        return "GCAddSlayer";
    }
    string toString() const;

public:
    PCSlayerInfo3& getSlayerInfo() {
        return m_SlayerInfo;
    }
    const PCSlayerInfo3& getSlayerInfo() const {
        return m_SlayerInfo;
    }
    void setSlayerInfo(const PCSlayerInfo3& slayerInfo) {
        m_SlayerInfo = slayerInfo;
    }

    EffectInfo* getEffectInfo() const {
        return m_pEffectInfo;
    }
    void setEffectInfo(EffectInfo* pEffectInfo) {
        m_pEffectInfo = pEffectInfo;
    }

    PetInfo* getPetInfo() const {
        return m_pPetInfo;
    }
    void setPetInfo(PetInfo* pPetInfo) {
        m_pPetInfo = pPetInfo;
    }

    NicknameInfo* getNicknameInfo() const {
        return m_pNicknameInfo;
    }
    void setNicknameInfo(NicknameInfo* pNicknameInfo) {
        m_pNicknameInfo = pNicknameInfo;
    }

    StoreOutlook getStoreOutlook() const {
        return m_StoreOutlook;
    }
    void setStoreInfo(StoreInfo* pInfo) {
        pInfo->makeStoreOutlook(m_StoreOutlook);
    }

private:
    PCSlayerInfo3 m_SlayerInfo;    // Core Slayer info
    EffectInfo* m_pEffectInfo;     // Active effect info
    PetInfo* m_pPetInfo;           // Pet information
    NicknameInfo* m_pNicknameInfo; // Nickname information
    StoreOutlook m_StoreOutlook;   // Store visual state
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayerFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayerFactory : public PacketFactory {
public:
    Packet* createPacket() {
        return new GCAddSlayer();
    }
    string getPacketName() const {
        return "GCAddSlayer";
    }
    PacketID_t getPacketID() const {
        return Packet::PACKET_GC_ADD_SLAYER;
    }
    PacketSize_t getPacketMaxSize() const {
        return PCSlayerInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() +
               NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize();
    }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayerHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayerHandler {
public:
    static void execute(GCAddSlayer* pPacket, Player* pPlayer);
};

#endif
