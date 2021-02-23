//////////////////////////////////////////////////////////////////////////////
// Filename    : NPCInfo.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "NPCInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class NPCInfo member methods
//////////////////////////////////////////////////////////////////////////////

NPCInfo::NPCInfo()
{
	m_Name  = "";
	m_NPCID = 0;
	m_X     = 0;
	m_Y     = 0;
}

NPCInfo::~NPCInfo()
{
}

void NPCInfo::read(SocketInputStream& iStream)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE m_NameLength = 0;
	iStream.read( m_NameLength );

	if (m_NameLength > 0)
	{
		iStream.read( m_Name, m_NameLength );
		iStream.read( m_NPCID );
		iStream.read( m_X );
		iStream.read( m_Y );
	}

	__END_CATCH
}

void NPCInfo::write(SocketOutputStream& oStream) const
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE m_NameLength = m_Name.size();
	oStream.write(m_NameLength);

	if (m_NameLength > 0)
	{
		oStream.write( m_Name );
		oStream.write( m_NPCID );
		oStream.write( m_X );
		oStream.write( m_Y );
	}

	__END_CATCH
}

string NPCInfo::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "NPCInfo("
		<< "Name:" << m_Name
		<< ",NPCID:" << (int)m_NPCID
		<< ",X:" << (int)m_X
		<< ",Y:" << (int)m_Y
		<< ")";
	return msg.toString();

	__END_CATCH
}

