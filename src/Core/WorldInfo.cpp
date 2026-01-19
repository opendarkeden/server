//////////////////////////////////////////////////////////////////////
//
// Filename    : WorldInfo.cpp
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "WorldInfo.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
WorldInfo::WorldInfo() {
    __BEGIN_TRY
    m_Stat = 0;
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
WorldInfo::~WorldInfo() noexcept = default;


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void WorldInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    BYTE szName;
    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    iStream.read(m_ID);
    iStream.read(szName);
    iStream.read(m_Name, szName);
    iStream.read(m_Stat);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void WorldInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    BYTE szName = m_Name.size();
    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    oStream.write(m_ID);
    oStream.write(szName);
    oStream.write(m_Name);
    oStream.write(m_Stat);

    __END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t WorldInfo::getSize() {
    __BEGIN_TRY

    BYTE szName = m_Name.size();

    PacketSize_t PacketSize = szWorldID + szBYTE + szName + szBYTE;

    return PacketSize;

    __END_CATCH
}

/////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string WorldInfo::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "WorldInfo( "
        << "ID : " << m_ID << "Name : " << m_Name << "Stat : " << m_Stat << ")";

    return msg.toString();

    __END_CATCH
}
