//////////////////////////////////////////////////////////////////////
//
// Filename    : ServerGroupInfo.cpp
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ServerGroupInfo.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ServerGroupInfo::ServerGroupInfo() {
    __BEGIN_TRY
    m_Stat = 0;
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ServerGroupInfo::~ServerGroupInfo() noexcept = default;


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void ServerGroupInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    BYTE szGroupName;
    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    iStream.read(m_GroupID);
    iStream.read(szGroupName);
    iStream.read(m_GroupName, szGroupName);
    iStream.read(m_Stat);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void ServerGroupInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    BYTE szGroupName = m_GroupName.size();
    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    oStream.write(m_GroupID);
    oStream.write(szGroupName);
    oStream.write(m_GroupName);
    oStream.write(m_Stat);

    __END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t ServerGroupInfo::getSize() {
    __BEGIN_TRY

    BYTE szGroupName = m_GroupName.size();

    PacketSize_t PacketSize = szServerGroupID + szBYTE + szGroupName + szBYTE;

    return PacketSize;

    __END_CATCH
}

/////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ServerGroupInfo::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "ServerGroupInfo( "
        << "GroupID : " << m_GroupID << "GroupName : " << m_GroupName << "Stat : " << m_Stat << ")";

    return msg.toString();

    __END_CATCH
}
