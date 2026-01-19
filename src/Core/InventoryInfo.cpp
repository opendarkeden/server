//////////////////////////////////////////////////////////////////////////////
// Filename    : InventoryInfo.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "InventoryInfo.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
InventoryInfo::InventoryInfo() {
    __BEGIN_TRY

    m_ListNum = 0;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
InventoryInfo::~InventoryInfo() noexcept {
    while (!m_InventorySlotInfoList.empty()) {
        InventorySlotInfo* pInventorySlotInfo = m_InventorySlotInfoList.front();
        SAFE_DELETE(pInventorySlotInfo);
        m_InventorySlotInfoList.pop_front();
    }
}


//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void InventoryInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    iStream.read(m_ListNum);

    for (int i = 0; i < m_ListNum; i++) {
        InventorySlotInfo* pInventorySlotInfo = new InventorySlotInfo();
        pInventorySlotInfo->read(iStream);
        m_InventorySlotInfoList.push_back(pInventorySlotInfo);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void InventoryInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    oStream.write(m_ListNum);

    list<InventorySlotInfo*>::const_iterator itr = m_InventorySlotInfoList.begin();
    for (; itr != m_InventorySlotInfoList.end(); itr++) {
        (*itr)->write(oStream);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// getSize
//////////////////////////////////////////////////////////////////////////////
PacketSize_t InventoryInfo::getSize() {
    PacketSize_t PacketSize = szBYTE;

    for (list<InventorySlotInfo*>::const_iterator itr = m_InventorySlotInfoList.begin();
         itr != m_InventorySlotInfoList.end(); itr++) {
        PacketSize += (*itr)->getSize();
    }

    return PacketSize;
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string InventoryInfo::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "InventoryInfo( ListNum:" << (int)m_ListNum << " ListSet( ";

    for (list<InventorySlotInfo*>::const_iterator itr = m_InventorySlotInfoList.begin();
         itr != m_InventorySlotInfoList.end(); itr++) {
        msg << (*itr)->toString() << ",";
    }

    msg << ")";

    return msg.toString();

    __END_CATCH
}
