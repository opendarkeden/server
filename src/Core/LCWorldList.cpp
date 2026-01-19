//----------------------------------------------------------------------
//
// Filename    : LCWorldList.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "LCWorldList.h"

#include "PCSlayerInfo.h"
#include "PCVampireInfo.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
LCWorldList::LCWorldList()

{
    m_CurrentWorldID = 1;
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
LCWorldList::~LCWorldList() noexcept

{
    // �Ҽӵ� ��� ��ü���� �����Ѵ�.
    while (!m_WorldInfoList.empty()) {
        WorldInfo* pWorldInfo = m_WorldInfoList.front();
        SAFE_DELETE(pWorldInfo);
        m_WorldInfoList.pop_front();
    }
}


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void LCWorldList::read(SocketInputStream& iStream)

{
    __BEGIN_TRY

    iStream.read(m_CurrentWorldID);

    BYTE ListNum;

    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    iStream.read(ListNum);
    for (int i = 0; i < ListNum; i++) {
        WorldInfo* pWorldInfo = new WorldInfo();
        pWorldInfo->read(iStream);
        m_WorldInfoList.push_back(pWorldInfo);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void LCWorldList::write(SocketOutputStream& oStream) const

{
    __BEGIN_TRY

    oStream.write(m_CurrentWorldID);

    BYTE ListNum = m_WorldInfoList.size();
    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    oStream.write(ListNum);

    for (list<WorldInfo*>::const_iterator itr = m_WorldInfoList.begin(); itr != m_WorldInfoList.end(); itr++) {
        (*itr)->write(oStream);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCWorldList::execute(Player* pPlayer)

{
    __BEGIN_TRY

    LCWorldListHandler::execute(this, pPlayer);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
PacketSize_t LCWorldList::getPacketSize() const

{
    __BEGIN_TRY

    // ����Ʈ ������ ����
    PacketSize_t PacketSize = szWorldID + szBYTE;

    for (list<WorldInfo*>::const_iterator itr = m_WorldInfoList.begin(); itr != m_WorldInfoList.end(); itr++) {
        PacketSize += (*itr)->getSize();
    }

    return PacketSize;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string LCWorldList::toString() const

{
    __BEGIN_TRY

    StringStream msg;

    msg << "LCWorldList(CurrentWorldID : " << (int)m_CurrentWorldID;
    for (list<WorldInfo*>::const_iterator itr = m_WorldInfoList.begin(); itr != m_WorldInfoList.end(); itr++) {
        msg << (*itr)->toString();
    }
    msg << ")";

    return msg.toString();

    __END_CATCH
}
