//////////////////////////////////////////////////////////////////////////////
// Filename    : CLCreatePC.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLCreatePC.h"

void CLCreatePC::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szName;

	iStream.read(szName);

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 20)
		throw InvalidProtocolException("too long name length");
		
	iStream.read(m_Name , szName);

	BYTE slot;
	iStream.read(slot);
	m_Slot = Slot(slot);

	BYTE flags;
	iStream.read(flags);
	m_BitSet = flags;

	for (uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++)
		iStream.read(m_Colors[i]);	

	iStream.read(m_STR);
	iStream.read(m_DEX);
	iStream.read(m_INT);

	iStream.read(m_Race);

	__END_CATCH
}

void CLCreatePC::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 20)
		throw InvalidProtocolException("too long name length");

	oStream.write(szName);
	oStream.write(m_Name);

	oStream.write((BYTE)m_Slot);

	oStream.write((BYTE)m_BitSet.to_ulong());

	for (uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++)
		oStream.write(m_Colors[i]);	

	oStream.write(m_STR);
	oStream.write(m_DEX);
	oStream.write(m_INT);

	oStream.write(m_Race);

	__END_CATCH
}

void CLCreatePC::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CLCreatePCHandler::execute(this , pPlayer);
		
	__END_CATCH
}

string CLCreatePC::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CLCreatePC(Name: " << m_Name 
		<< ",Slot:" << Slot2String[m_Slot]
		<< ",Sex:" << Sex2String[getSex()]
		<< ",HairStyle:" << HairStyle2String[getHairStyle()] 
		<< ",HairColor:" << (int)getHairColor()
		<< ",SkinColor:" << (int)getSkinColor()
		<< ",STR:" << (int)m_STR
		<< ",DEX:" << (int)m_DEX
		<< ",INT:" << (int)m_INT
		<< ",Race:" << (int)m_Race
		<< ")";
	return msg.toString();

	__END_CATCH
}

