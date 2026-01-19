//----------------------------------------------------------------------
//
// Filename    : LCServerList.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "LCServerList.h"

#include "PCSlayerInfo.h"
#include "PCVampireInfo.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
LCServerList::LCServerList()

{
    m_CurrentServerGroupID = 0;
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
LCServerList::~LCServerList() noexcept

{
    // �Ҽӵ� ��� ��ü���� �����Ѵ�.
    while (!m_ServerGroupInfoList.empty()) {
        ServerGroupInfo* pServerGroupInfo = m_ServerGroupInfoList.front();
        SAFE_DELETE(pServerGroupInfo);
        m_ServerGroupInfoList.pop_front();
    }
}


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void LCServerList::read(SocketInputStream& iStream)

{
    __BEGIN_TRY

    iStream.read(m_CurrentServerGroupID);

    BYTE ListNum;

    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    iStream.read(ListNum);
    for (int i = 0; i < ListNum; i++) {
        ServerGroupInfo* pServerGroupInfo = new ServerGroupInfo();
        pServerGroupInfo->read(iStream);
        m_ServerGroupInfoList.push_back(pServerGroupInfo);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void LCServerList::write(SocketOutputStream& oStream) const

{
    __BEGIN_TRY

    oStream.write(m_CurrentServerGroupID);

    BYTE ListNum = m_ServerGroupInfoList.size();
    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    oStream.write(ListNum);

    for (list<ServerGroupInfo*>::const_iterator itr = m_ServerGroupInfoList.begin(); itr != m_ServerGroupInfoList.end();
         itr++) {
        (*itr)->write(oStream);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCServerList::execute(Player* pPlayer)

{
    __BEGIN_TRY

    LCServerListHandler::execute(this, pPlayer);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
PacketSize_t LCServerList::getPacketSize() const

{
    __BEGIN_TRY

    // ����Ʈ ������ ����
    PacketSize_t PacketSize = szServerGroupID + szBYTE;

    for (list<ServerGroupInfo*>::const_iterator itr = m_ServerGroupInfoList.begin(); itr != m_ServerGroupInfoList.end();
         itr++) {
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
string LCServerList::toString() const

{
    __BEGIN_TRY

    StringStream msg;

    msg << "LCServerList(CurrentServerGroupID : " << (int)m_CurrentServerGroupID;
    for (list<ServerGroupInfo*>::const_iterator itr = m_ServerGroupInfoList.begin(); itr != m_ServerGroupInfoList.end();
         itr++) {
        msg << (*itr)->toString();
    }
    msg << ")";

    return msg.toString();

    __END_CATCH
}
