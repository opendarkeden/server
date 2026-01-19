//////////////////////////////////////////////////////////////////////
//
// Filename    : VampireSkillInfo.h
// Written By  : elca@ewestsoft.com
// Description :  ��ų�� ������
//
//////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_SKILL_INFO_H__
#define __VAMPIRE_SKILL_INFO_H__

// include files
#include "Exception.h"
#include "PCSkillInfo.h"
#include "Packet.h"
#include "SubVampireSkillInfo.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////
//
// class VampireSkillInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class VampireSkillInfo : public PCSkillInfo {
public:
    // constructor
    VampireSkillInfo();

    // destructor
    ~VampireSkillInfo() noexcept;

public:
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ��
    // �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream);

    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const;

    // get packet's body size
    // ����ȭ��, �̸� ���� ������ ����Ѵ�.
    PacketSize_t getSize();

    static uint getMaxSize() {
        return szBYTE + szBYTE + (SubVampireSkillInfo::getMaxSize() * 120);
    }

    // get packet's debug string
    string toString() const;

    // get / set New Skill
    bool isLearnNewSkill() const {
        return m_bLearnNewSkill;
    }
    void setLearnNewSkill(bool NewSkill) {
        m_bLearnNewSkill = NewSkill;
    }

    // get / set ListNumber
    BYTE getListNum() const {
        return m_ListNum;
    }
    void setListNum(BYTE ListNum) {
        m_ListNum = ListNum;
    }

    // add / delete / clear S List
    void addListElement(SubVampireSkillInfo* pSubVampireSkillInfo) {
        m_SubVampireSkillInfoList.push_back(pSubVampireSkillInfo);
    }

    // ClearList
    void clearList() {
        m_SubVampireSkillInfoList.clear();
        m_ListNum = 0;
    }

    // pop front Element in Status List
    SubVampireSkillInfo* popFrontListElement() {
        SubVampireSkillInfo* TempSubVampireSkillInfo = m_SubVampireSkillInfoList.front();
        m_SubVampireSkillInfoList.pop_front();
        return TempSubVampireSkillInfo;
    }

private:
    // New ��ų�� ��� �� �ִ��� ������ ����
    bool m_bLearnNewSkill;

    // SubVampireSkillInfo List Total Number
    BYTE m_ListNum;

    // SubVampireSkillInfo List
    list<SubVampireSkillInfo*> m_SubVampireSkillInfoList;
};

#endif
