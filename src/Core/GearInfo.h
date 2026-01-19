//////////////////////////////////////////////////////////////////////////////
// Filename    : GearInfo.h
// Written By  : elca@ewestsoft.com
// Description :
// �԰� �ִ� ��� �����۵��� ���� ����Ʈ�̴�.
// ������ ��� �����ۿ� ���� ������ GearSlotInfo�� �����ϸ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GEAR_INFO_H__
#define __GEAR_INFO_H__

#include "Exception.h"
#include "GearSlotInfo.h"
#include "Packet.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class GearInfo;
//////////////////////////////////////////////////////////////////////////////

class GearInfo {
public:
    GearInfo();
    ~GearInfo() noexcept;

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;

    PacketSize_t getSize();

    static uint getMaxSize() {
        return szBYTE + (GearSlotInfo::getMaxSize() * 13);
    }

    string toString() const;

public:
    BYTE getListNum() const {
        return m_ListNum;
    }
    void setListNum(BYTE ListNum) {
        m_ListNum = ListNum;
    }

    void addListElement(GearSlotInfo* pGearSlotInfo) {
        m_GearSlotInfoList.push_back(pGearSlotInfo);
    }

    void clearList() {
        m_GearSlotInfoList.clear();
        m_ListNum = 0;
    }

    GearSlotInfo* popFrontListElement() {
        GearSlotInfo* TempGearSlotInfo = m_GearSlotInfoList.front();
        m_GearSlotInfoList.pop_front();
        return TempGearSlotInfo;
    }

private:
    BYTE m_ListNum;                         // number of gear
    list<GearSlotInfo*> m_GearSlotInfoList; // actual gear info
};

#endif
