//////////////////////////////////////////////////////////////////////
//
// Filename    : SlayerSkillInfo.cpp
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "SlayerSkillInfo.h"

#include "Assert.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SlayerSkillInfo::SlayerSkillInfo() {
    __BEGIN_TRY
    m_bLearnNewSkill = false;
    m_DomainType = 0;
    m_ListNum = 0;
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SlayerSkillInfo::~SlayerSkillInfo() noexcept {
    // �Ҽӵ� ��� ��ü���� �����Ѵ�.
    while (!m_SubSlayerSkillInfoList.empty()) {
        SubSlayerSkillInfo* pSubSlayerSkillInfo = m_SubSlayerSkillInfoList.front();
        SAFE_DELETE(pSubSlayerSkillInfo);
        m_SubSlayerSkillInfoList.pop_front();
    }
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void SlayerSkillInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    iStream.read(m_bLearnNewSkill);
    iStream.read(m_DomainType);
    iStream.read(m_ListNum);

    for (int i = 0; i < m_ListNum; i++) {
        SubSlayerSkillInfo* pSubSlayerSkillInfo = new SubSlayerSkillInfo();
        pSubSlayerSkillInfo->read(iStream);
        m_SubSlayerSkillInfoList.push_back(pSubSlayerSkillInfo);
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void SlayerSkillInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    // ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
    oStream.write(m_bLearnNewSkill);
    oStream.write(m_DomainType);
    oStream.write(m_ListNum);

    for (list<SubSlayerSkillInfo*>::const_iterator itr = m_SubSlayerSkillInfoList.begin();
         itr != m_SubSlayerSkillInfoList.end(); itr++) {
        Assert(*itr != NULL);
        (*itr)->write(oStream);
    }

    __END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t SlayerSkillInfo::getSize() {
    PacketSize_t PacketSize = szBYTE + szSkillDomainType + szBYTE;

    for (list<SubSlayerSkillInfo*>::const_iterator itr = m_SubSlayerSkillInfoList.begin();
         itr != m_SubSlayerSkillInfoList.end(); itr++) {
        PacketSize += (*itr)->getSize();
    }

    return PacketSize;
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string SlayerSkillInfo::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "SlayerSkillInfo( ListNum:" << (int)m_ListNum << " ListSet( ";

    for (list<SubSlayerSkillInfo*>::const_iterator itr = m_SubSlayerSkillInfoList.begin();
         itr != m_SubSlayerSkillInfoList.end(); itr++) {
        Assert(*itr != NULL);
        msg << (*itr)->toString() << ",";
    }

    msg << ")";

    return msg.toString();

    __END_CATCH
}
