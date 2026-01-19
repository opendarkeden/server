//////////////////////////////////////////////////////////////////////////////
// Filename    : RideMotorcycleInfo.h
// Written By  : elca@ewestsoft.com
// Description :
// Ÿ�� �ִ� ���ͻ���Ŭ�� ���� ������ ������ �ִ� ��Ŷ�̴�.
// ���� ����Ŭ ��ü�� ���� ���� �ܿ���, ���� ����Ŭ ���ο� �ִ�
// �κ��丮�� ���� ������ ���� ������ �ִ�. �κ��丮 ������ ���� ����
// RideMotorcycleSlotInfo�� InventorySlotInfo�� �����϶�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __RIDE_MOTORCYCLE_INFO_H__
#define __RIDE_MOTORCYCLE_INFO_H__

#include <list>

#include "Exception.h"
#include "Packet.h"
#include "RideMotorcycleSlotInfo.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class RideMotorcycleInfo;
//////////////////////////////////////////////////////////////////////////////

class RideMotorcycleInfo {
public:
    RideMotorcycleInfo();
    ~RideMotorcycleInfo() noexcept;

public:
    void read(SocketInputStream& iStream);
    void write(SocketOutputStream& oStream) const;

    PacketSize_t getSize();

    static uint getMaxSize() {
        return szObjectID +   // motorcycle object id
               szItemType +   // motorcycle type
               szBYTE + 255 + // motorcycle option type
               szBYTE +       // number of item in motorcycle inventory
               RideMotorcycleSlotInfo::getMaxSize() * 60;
    }

    string toString() const;

public:
    void setObjectID(ObjectID_t ObjectID) {
        m_ObjectID = ObjectID;
    }
    ObjectID_t getObjectID() const {
        return m_ObjectID;
    }

    void setItemType(ItemType_t ItemType) {
        m_ItemType = ItemType;
    }
    ItemType_t getItemType() const {
        return m_ItemType;
    }

    void addOptionType(OptionType_t OptionType) {
        m_OptionType.push_back(OptionType);
    }
    void setOptionType(const list<OptionType_t>& OptionType) {
        m_OptionType = OptionType;
    }
    int getOptionTypeSize() const {
        return m_OptionType.size();
    }
    const list<OptionType_t>& getOptionType() const {
        return m_OptionType;
    }
    OptionType_t popOptionType() {
        if (m_OptionType.empty())
            return 0;
        OptionType_t optionType = m_OptionType.front();
        m_OptionType.pop_front();
        return optionType;
    }

public:
    BYTE getListNum() const {
        return m_ListNum;
    }
    void setListNum(BYTE ListNum) {
        m_ListNum = ListNum;
    }

    void addListElement(RideMotorcycleSlotInfo* pRideMotorcycleSlotInfo) {
        m_RideMotorcycleSlotInfoList.push_back(pRideMotorcycleSlotInfo);
    }

    void clearList() {
        m_RideMotorcycleSlotInfoList.clear();
        m_ListNum = 0;
    }

    RideMotorcycleSlotInfo* popFrontListElement() {
        RideMotorcycleSlotInfo* TempRideMotorcycleSlotInfo = m_RideMotorcycleSlotInfoList.front();
        m_RideMotorcycleSlotInfoList.pop_front();
        return TempRideMotorcycleSlotInfo;
    }

private:
    ObjectID_t m_ObjectID;           // motorcycle object id
    ItemType_t m_ItemType;           // motorcycle item type
    list<OptionType_t> m_OptionType; // motorcycle option type
    BYTE m_ListNum;                  // number of item in motorcycle inventory

    // actual item info in motorcycle inventory
    list<RideMotorcycleSlotInfo*> m_RideMotorcycleSlotInfoList;
};

#endif
