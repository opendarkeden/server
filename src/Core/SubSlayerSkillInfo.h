//----------------------------------------------------------------------
//
// Filename    : SubSlayerSkillInfo.h
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_SLAYER_SKILL_INFO_H__
#define __SUB_SLAYER_SKILL_INFO_H__

// include files
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Types.h"

//----------------------------------------------------------------------
//
// Holds inventory-related skill info.
//
// Sent to clients via GCUpdateInfo during character load.
// Does not include guild or other ability details not needed here.
//
//----------------------------------------------------------------------

class SubSlayerSkillInfo {
public:
    // read data from socket input stream
    void read(SocketInputStream& iStream);

    // write data to socket output stream
    void write(SocketOutputStream& oStream) const;

    // get size of object
    uint getSize() const {
        return szSkillType + szExp + szExpLevel + szTurn + szTurn + szBYTE;
    }
    // get max size of object
    static uint getMaxSize() {
        return szSkillType + szExp + szExpLevel + szTurn + szTurn + szBYTE;
    }

    // get debug string
    string toString() const;

public:
    // get / set SkillType
    SkillType_t getSkillType() const {
        return m_SkillType;
    }
    void setSkillType(SkillType_t SkillType) {
        m_SkillType = SkillType;
    }

    // get / set Exp
    Exp_t getSkillExp() const {
        return m_Exp;
    }
    void setSkillExp(Exp_t Exp) {
        m_Exp = Exp;
    }

    // get / set ExpLevel
    ExpLevel_t getSkillExpLevel() const {
        return m_ExpLevel;
    }
    void setSkillExpLevel(ExpLevel_t ExpLevel) {
        m_ExpLevel = ExpLevel;
    }

    // get / set Turn
    Turn_t getSkillTurn() const {
        return m_Interval;
    }
    void setSkillTurn(Turn_t SkillTurn) {
        m_Interval = SkillTurn;
    }

    // get / set CastingTime
    Turn_t getCastingTime() const {
        return m_CastingTime;
    }
    void setCastingTime(Turn_t CastingTime) {
        m_CastingTime = CastingTime;
    }

    // get / set Enable
    // true means the skill can be used; false means it is disabled.
    bool getEnable() const {
        return m_Enable;
    }
    void setEnable(bool Enable) {
        m_Enable = Enable;
    }

private:
    // Skill type
    SkillType_t m_SkillType;

    // Skill experience
    Exp_t m_Exp;

    // Skill level
    ExpLevel_t m_ExpLevel;

    // Cooldown interval
    Turn_t m_Interval;

    // Casting time
    Turn_t m_CastingTime;

    // Whether the skill is available for use
    bool m_Enable;
};

#endif
