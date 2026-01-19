//////////////////////////////////////////////////////////////////////////////
// Filename    : ModifyInfo.h
// Written By  : elca@ewestsoft.com
// Description :
// �÷��̾��� ���°� ���� ��, Ŭ���̾�Ʈ���� ���ư��� ��Ŷ�̴�.
// �ַ� �÷��̾ ���� ����� ���� ��� ��Ŷ�� �� ��Ŷ��
// ��ӹ޾Ƽ� ���� ��찡 ����.
//////////////////////////////////////////////////////////////////////////////

#ifndef __MODIFY_INFO_H__
#define __MODIFY_INFO_H__

#include <list>

#include "Exception.h"
#include "Packet.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// ���� ��ȭ Ÿ��
//////////////////////////////////////////////////////////////////////////////
enum ModifyType {
    MODIFY_BASIC_STR = 0,           // �⺻ STR�� ����
    MODIFY_CURRENT_STR,             // ���� STR�� ����
    MODIFY_MAX_STR,                 // �ƽ� STR�� ����
    MODIFY_STR_EXP,                 // STR ����ġ�� ����
    MODIFY_BASIC_DEX,               // �⺻ DEX�� ����
    MODIFY_CURRENT_DEX,             // ���� DEX�� ����
    MODIFY_MAX_DEX,                 // �ƽ� DEX�� ����
    MODIFY_DEX_EXP,                 // DEX ����ġ�� ����
    MODIFY_BASIC_INT,               // �⺻ INT�� ����
    MODIFY_CURRENT_INT,             // ���� INT�� ����
    MODIFY_MAX_INT,                 // �ƽ� INT�� ����
    MODIFY_INT_EXP,                 // INT ����ġ�� ����
    MODIFY_CURRENT_HP,              // ���� HP�� ����
    MODIFY_MAX_HP,                  // �ƽ� HP�� ����
    MODIFY_CURRENT_MP,              // ���� MP�� ����
    MODIFY_MAX_MP,                  // �ƽ� MP�� ����
    MODIFY_MIN_DAMAGE,              // �ּ� �������� ����
    MODIFY_MAX_DAMAGE,              // �ƽ� �������� ����
    MODIFY_DEFENSE,                 // ���潺�� ����
    MODIFY_PROTECTION,              // �����ؼ��� ����
    MODIFY_TOHIT,                   // ���߷��� ����
    MODIFY_VISION,                  // �þ߸� ����
    MODIFY_FAME,                    // ������ ����
    MODIFY_GOLD,                    // �������� ����
    MODIFY_SWORD_DOMAIN_LEVEL,      // �� �迭 ������ ����
    MODIFY_SWORD_DOMAIN_EXP,        // �� �迭 ������ ����
    MODIFY_SWORD_DOMAIN_GOAL_EXP,   // �� �迭 ������ ����
    MODIFY_BLADE_DOMAIN_LEVEL,      // �� �迭 ������ ����
    MODIFY_BLADE_DOMAIN_EXP,        // �� �迭 ������ ����
    MODIFY_BLADE_DOMAIN_GOAL_EXP,   // �� �迭 ������ ����
    MODIFY_HEAL_DOMAIN_LEVEL,       // �� �迭 ������ ����
    MODIFY_HEAL_DOMAIN_EXP,         // �� �迭 ������ ����
    MODIFY_HEAL_DOMAIN_GOAL_EXP,    // �� �迭 ������ ����
    MODIFY_ENCHANT_DOMAIN_LEVEL,    // ��æƮ �迭 ������ ����
    MODIFY_ENCHANT_DOMAIN_EXP,      // ��æƮ �迭 ������ ����
    MODIFY_ENCHANT_DOMAIN_GOAL_EXP, // ��æƮ �迭 ������ ����
    MODIFY_GUN_DOMAIN_LEVEL,        // �� �迭 ������ ����
    MODIFY_GUN_DOMAIN_EXP,          // �� �迭 ������ ����
    MODIFY_GUN_DOMAIN_GOAL_EXP,     // �� �迭 ������ ����
    MODIFY_ETC_DOMAIN_LEVEL,        // ��Ÿ �迭 ������ ����
    MODIFY_ETC_DOMAIN_EXP,          // ��Ÿ �迭 ������ ����
    MODIFY_ETC_DOMAIN_GOAL_EXP,     // ��Ÿ �迭 ������ ����
    MODIFY_SKILL_LEVEL,             // Ư�� ��ų ������ ����
    MODIFY_LEVEL,                   // �����̾� ������ ����
    MODIFY_EFFECT_STAT,             // ����Ʈ ���¸� ����
    MODIFY_DURATION,                // ����Ʈ ���� �ð��� ����
    MODIFY_BULLET,                  // ��� �ִ� �Ѿ��� �Ѿ� ���� ����
    MODIFY_BONUS_POINT,             // �����̾��� ���ʽ� ����Ʈ�� ����
    MODIFY_DURABILITY,              // ��� �ִ� ������ �� �ϳ��� �������� ����
    MODIFY_NOTORIETY,               // �Ǹ�ġ�� ����
    MODIFY_VAMP_GOAL_EXP,           // �����̾��� ����ġ�� ����
    MODIFY_SILVER_DAMAGE,           // �� �������� ����
    MODIFY_ATTACK_SPEED,            // ���� �ӵ��� ����
    MODIFY_ALIGNMENT,               // ����
    MODIFY_SILVER_DURABILITY,       // �� ���ݾ��� ����
    MODIFY_REGEN_RATE,              // ���� �ð��� �������� ����
    MODIFY_GUILDID,                 // ��� ���̵� ����
    MODIFY_RANK,                    // ��� �ܰ�
    MODIFY_RANK_EXP,                // ��� ����ġ
    MODIFY_OUSTERS_GOAL_EXP,        // �ƿ콺�ͽ��� ����ġ�� ����
    MODIFY_SKILL_BONUS_POINT,       // �ƿ콺�ͽ��� ��ų ���ʽ� ����Ʈ�� ����

    MODIFY_ELEMENTAL_FIRE,
    MODIFY_ELEMENTAL_WATER,
    MODIFY_ELEMENTAL_EARTH,
    MODIFY_ELEMENTAL_WIND,

    MODIFY_SKILL_EXP, // �����̾� ��ų ����ġ ����

    MODIFY_PET_HP,
    MODIFY_PET_EXP, // �� ����

    MODIFY_LAST_TARGET, // ���� ������ ��� ����
    MODIFY_UNIONID,     // ��忬�� ���̵�
    MODIFY_UNIONGRADE,  // ��忬�տ����� ��ġ

    MODIFY_ADVANCEMENT_CLASS_LEVEL,    // ���� ����
    MODIFY_ADVANCEMENT_CLASS_GOAL_EXP, // ���� ����ġ

    MODIFY_MAX
};

const string ModifyType2String[] = {"BASIC_STR",
                                    "CURRENT_STR",
                                    "MAX_STR",
                                    "STR_EXP",
                                    "BASIC_DEX",
                                    "CURRENT_DEX",
                                    "MAX_DEX",
                                    "DEX_EXP",
                                    "BASIC_INT",
                                    "CURRENT_INT",
                                    "MAX_INT",
                                    "INT_EXP",
                                    "CURRENT_HP",
                                    "MAX_HP",
                                    "CURRENT_MP",
                                    "MAX_MP",
                                    "MIN_DAMAGE",
                                    "MAX_DAMAGE",
                                    "DEFENSE",
                                    "PROTECTION",
                                    "TOHIT",
                                    "VISION",
                                    "FAME",
                                    "GOLD",
                                    "SWORD_DOMAIN_LEVEL",
                                    "SWORD_DOMAIN_EXP",
                                    "SWORD_DOMAIN_GOAL_EXP",
                                    "BLADE_DOMAIN_LEVEL",
                                    "BLADE_DOMAIN_EXP",
                                    "BLADE_DOMAIN_GOAL_EXP",
                                    "HEAL_DOMAIN_LEVEL",
                                    "HEAL_DOMAIN_EXP",
                                    "HEAL_DOMAIN_GOAL_EXP",
                                    "ENCHANT_DOMAIN_LEVEL",
                                    "ENCHANT_DOMAIN_EXP",
                                    "ENCHANT_DOMAIN_GOAL_EXP",
                                    "GUN_DOMAIN_LEVEL",
                                    "GUN_DOMAIN_EXP",
                                    "GUN_DOMAIN_GOAL_EXP",
                                    "ETC_DOMAIN_LEVEL",
                                    "ETC_DOMAIN_EXP",
                                    "ETC_DOMAIN_GOAL_EXP",
                                    "SKILL_LEVEL",
                                    "LEVEL",
                                    "EFFECT_STAT",
                                    "DURATION",
                                    "BULLET",
                                    "BONUS_POINT",
                                    "DURABILITY",
                                    "NOTORIETY",
                                    "VAMP_EXP",
                                    "SILVER_DAMAGE",
                                    "ATTACK_SPEED",
                                    "ALIGNMENT",
                                    "SILVER_DURABILITY",
                                    "REGEN_RATE",
                                    "GUILDID",
                                    "RANK",
                                    "RANK_EXP",
                                    "MODIFY_OUSTERS_EXP",
                                    "MODIFY_SKILL_BONUS_POINT",

                                    "MODIFY_ELEMENTAL_FIRE",
                                    "MODIFY_ELEMENTAL_WATER",
                                    "MODIFY_ELEMENTAL_EARTH",
                                    "MODIFY_ELEMENTAL_WIND",

                                    "MODIFY_SKILL_EXP", // �����̾� ��ų ����ġ ����

                                    "MODIFY_PET_HP",
                                    "MODIFY_PET_EXP", // �� ����

                                    "MODIFY_LAST_TARGET", // ���� ������ ��� ����
                                    "MODIFY_UNIONID",
                                    "MODIFY_UNIONGRADE",

                                    "MODIFY_ADVANCEMENT_CLASS_LEVEL",    // ���� ����
                                    "MODIFY_ADVANCEMENT_CLASS_GOAL_EXP", // ���� ����ġ

                                    "MAX"};

//////////////////////////////////////////////////////////////////////////////
// 2����Ʈ�� ����� �������� ���, �� ����ü�� ����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
typedef struct _SHORTDATA {
    BYTE type;
    ushort value;

} SHORTDATA;

//////////////////////////////////////////////////////////////////////////////
// 4����Ʈ�� ����� �������� ���, �� ����ü�� ����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
typedef struct _LONGDATA {
    BYTE type;
    DWORD value;

} LONGDATA;


//////////////////////////////////////////////////////////////////////////////
// class ModifyInfo;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸�
// �˷��ֱ� ���� ��ä ModifyInformation, SkillToObjectOK � �Ƿ��� ���ư���.
//////////////////////////////////////////////////////////////////////////////

class ModifyInfo : public Packet {
public:
    ModifyInfo();
    virtual ~ModifyInfo() noexcept;

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;
    PacketSize_t getPacketSize() const {
        return szBYTE * 2 + m_ShortCount * (szBYTE + szshort) + m_LongCount * (szBYTE + szDWORD);
    }
    static PacketSize_t getPacketMaxSize() {
        return szBYTE * 2 + 255 * (szBYTE + szshort + szBYTE + szDWORD);
    }
    string toString() const;

public:
    BYTE getShortCount(void) const {
        return m_ShortCount;
    }
    BYTE getLongCount(void) const {
        return m_LongCount;
    }

    void addShortData(ModifyType type, ushort value);
    void addLongData(ModifyType type, ulong value);

    void popShortData(SHORTDATA& rData);
    void popLongData(LONGDATA& rData);

    void clearList(void) {
        m_ShortCount = 0;
        m_LongCount = 0;
        m_ShortList.clear();
        m_LongList.clear();
    }

protected:
    BYTE m_ShortCount;
    list<SHORTDATA> m_ShortList;

    BYTE m_LongCount;
    list<LONGDATA> m_LongList;
};

#endif
