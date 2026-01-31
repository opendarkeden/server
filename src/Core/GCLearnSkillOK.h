//////////////////////////////////////////////////////////////////////
//
// Filename    :  GCLearnSkillOK.h
// Written By  :  elca@ewestsoft.com
// Description :  ÃÂ
//
//
//////////////////////////////////////////////////////////////////////

#ifndef __GC_LEARN_SKILL_OK_H__
#define __GC_LEARN_SKILL_OK_H__

// include files
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillOK;
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillOK : public Packet {
public:
    // constructor
    GCLearnSkillOK();

    // destructor
    ~GCLearnSkillOK();


public:
    // ÃÂÃÂÃÂ·ÃÂÃÂ½ÃÂºÃÂÃÂ®ÃÂ¸ÃÂ²(ÃÂ¹ÃÂ¶ÃÂÃÂ)ÃÂÃÂ¸ÃÂ·ÃÂÃÂºÃÂÃÂÃÂ ÃÂµÃÂ¥ÃÂÃÂÃÂÃÂ¸ÃÂ¸ÃÂ¦ ÃÂÃÂÃÂ¾ÃÂ®ÃÂ¼ÃÂ­ ÃÂÃÂÃÂÃÂ¶ÃÂÃÂ» ÃÂÃÂÃÂ±ÃÂ¢ÃÂÃÂ­ÃÂÃÂÃÂ´ÃÂ.
    void read(SocketInputStream& iStream);

    // ÃÂÃÂ¢ÃÂ·ÃÂÃÂ½ÃÂºÃÂÃÂ®ÃÂ¸ÃÂ²(ÃÂ¹ÃÂ¶ÃÂÃÂ)ÃÂÃÂ¸ÃÂ·ÃÂ ÃÂÃÂÃÂÃÂ¶ÃÂÃÂ ÃÂ¹ÃÂÃÂÃÂÃÂ³ÃÂÃÂ¸ÃÂ® ÃÂÃÂÃÂ¹ÃÂÃÂÃÂ¶ÃÂ¸ÃÂ¦ ÃÂºÃÂ¸ÃÂ³ÃÂ½ÃÂ´ÃÂ.
    void write(SocketOutputStream& oStream) const;

    // execute packet's handler
    void execute(Player* pPlayer);

    // get packet id
    PacketID_t getPacketID() const {
        return PACKET_GC_LEARN_SKILL_OK;
    }

    // get packet size
    PacketSize_t getPacketSize() const {
        return szSkillType + szSkillDomainType;
    }

    // get packet's name
    string getPacketName() const {
        return "GCLearnSkillOK";
    }

    // get packet's debug string
    string toString() const;

    // get/set m_SkillType
    SkillType_t getSkillType() const {
        return m_SkillType;
    }
    void setSkillType(SkillType_t SkillType) {
        m_SkillType = SkillType;
    }

    // get/set m_SkillDomainType
    SkillDomainType_t getSkillDomainType() const {
        return m_DomainType;
    }
    void setSkillDomainType(SkillDomainType_t DomainType) {
        m_DomainType = DomainType;
    }

private:
    // SkillType
    SkillType_t m_SkillType;

    // DomainType
    SkillDomainType_t m_DomainType;
};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillOKFactory;
//
// Factory for  GCLearnSkillOK
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillOKFactory : public PacketFactory {
public:
    // constructor
    GCLearnSkillOKFactory() {}

    // destructor
    virtual ~GCLearnSkillOKFactory() {}


public:
    // create packet
    Packet* createPacket() {
        return new GCLearnSkillOK();
    }

    // get packet name
    string getPacketName() const {
        return "GCLearnSkillOK";
    }

    // get packet id
    PacketID_t getPacketID() const {
        return Packet::PACKET_GC_LEARN_SKILL_OK;
    }

    // get Packet Max Size
    PacketSize_t getPacketMaxSize() const {
        return szSkillType + szSkillDomainType;
    }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillOKHandler {
public:
    // execute packet's handler
    static void execute(GCLearnSkillOK* pGCLearnSkillOK, Player* pPlayer);
};

#endif // __GC_LEARN_SKILL_OK_H__
