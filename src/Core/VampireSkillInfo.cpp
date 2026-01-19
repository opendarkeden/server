//////////////////////////////////////////////////////////////////////
//
// Filename    : VampireSkillInfo.cpp
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "VampireSkillInfo.h"

#include "Assert.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
VampireSkillInfo::VampireSkillInfo() {
    __BEGIN_TRY
    m_bLearnNewSkill = false;
    m_ListNum = 0;
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
VampireSkillInfo::~VampireSkillInfo() noexcept {
    // �Ҽӵ� ��� ��ü���� �����Ѵ�.
    while (!m_SubVampireSkillInfoList.empty()) {
        SubVampireSkillInfo* pSubVampireSkillInfo = m_SubVampireSkillInfoList.front();
        SAFE_DELETE(pSubVampireSkillInfo);
        m_SubVampireSkillInfoList.pop_front();
    }
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void VampireSkillInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    iStream.read(m_bLearnNewSkill);
    iStream.read(m_ListNum);

    for (int i = 0; i < m_ListNum; i++) {
        SubVampireSkillInfo* pSubVampireSkillInfo = new SubVampireSkillInfo();
        pSubVampireSkillInfo->read(iStream);
        m_SubVampireSkillInfoList.push_back(pSubVampireSkillInfo);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void VampireSkillInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    oStream.write(m_bLearnNewSkill);
    oStream.write(m_ListNum);

    for (list<SubVampireSkillInfo*>::const_iterator itr = m_SubVampireSkillInfoList.begin();
         itr != m_SubVampireSkillInfoList.end(); itr++) {
        Assert(*itr != NULL);
        (*itr)->write(oStream);
    }

    __END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t VampireSkillInfo::getSize() {
    PacketSize_t PacketSize = szBYTE + szBYTE;

    for (list<SubVampireSkillInfo*>::const_iterator itr = m_SubVampireSkillInfoList.begin();
         itr != m_SubVampireSkillInfoList.end(); itr++) {
        PacketSize += (*itr)->getSize();
    }

    return PacketSize;
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string VampireSkillInfo::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "VampireSkillInfo( ListNum:" << (int)m_ListNum << " ListSet( ";

    for (list<SubVampireSkillInfo*>::const_iterator itr = m_SubVampireSkillInfoList.begin();
         itr != m_SubVampireSkillInfoList.end(); itr++) {
        Assert(*itr != NULL);
        msg << (*itr)->toString() << ",";
    }

    msg << ")";

    return msg.toString();

    __END_CATCH
}
