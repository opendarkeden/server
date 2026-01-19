//////////////////////////////////////////////////////////////////////
//
// Filename    : GuildWarInfo.cpp
// Written By  :
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GuildWarInfo.h"

//////////////////////////////////////////////////////////////////////
// Read war info from the incoming stream.
//////////////////////////////////////////////////////////////////////
void GuildWarInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    WarInfo::read(iStream);
    iStream.read(m_CastleID);


    BYTE szName;
    iStream.read(szName);
    if (szName > 0)
        iStream.read(m_AttackGuildName, szName);

    iStream.read(szName);
    if (szName > 0)
        iStream.read(m_DefenseGuildName, szName);


    m_GuildIDs.read(iStream);

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// Write war info into the outgoing stream.
//////////////////////////////////////////////////////////////////////
void GuildWarInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    WarInfo::write(oStream);
    oStream.write(m_CastleID);

    BYTE szName = m_AttackGuildName.size();
    oStream.write(szName);
    if (szName > 0)
        oStream.write(m_AttackGuildName);

    szName = m_DefenseGuildName.size();
    oStream.write(szName);
    if (szName > 0)
        oStream.write(m_DefenseGuildName);

    m_GuildIDs.write(oStream);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string GuildWarInfo::toString() const {
    StringStream msg;

    msg << "GuildWarInfo("
        << "CastleID:" << (int)m_CastleID << ",AttackGuildName:" << m_AttackGuildName
        << ",DefenseGuildName:" << m_DefenseGuildName << ",RemainTime:" << (int)m_RemainTime
        << ",Guilds:" << m_GuildIDs.toString() << ")";

    return msg.toString();
}
