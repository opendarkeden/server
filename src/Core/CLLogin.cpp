//////////////////////////////////////////////////////////////////////////////
// Filename    : CLLogin.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLLogin.h"

#include "Properties.h"

void CLLogin::read (SocketInputStream & iStream) 
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY

    setNetmarble(false);

    BYTE szID;

    iStream.read(szID);

    if (szID == 0)
        throw InvalidProtocolException("szID == 0");

    if (szID > 30)
        throw InvalidProtocolException("too large ID length");

    iStream.read(m_ID , szID);

    BYTE szPassword;

    iStream.read(szPassword);

    if (szPassword == 0)
        throw InvalidProtocolException("szPassword == 0");

    if (szPassword > 30)
        throw InvalidProtocolException("too large password length");

    iStream.read(m_Password , szPassword);

    iStream.read((char*)m_cMacAddress, 6 * szBYTE);

    iStream.read(m_LoginMode);

    /* convert hex -> str */
    
    char	tmpStr[20];
    sprintf(tmpStr, "%02x%02x%02x%02x%02x%02x", m_cMacAddress[0],m_cMacAddress[1],m_cMacAddress[2],m_cMacAddress[3],m_cMacAddress[4],m_cMacAddress[5]);

    m_strMacAddress	= tmpStr;

	__END_CATCH
}

void CLLogin::write (SocketOutputStream & oStream) const 
     throw(ProtocolException , Error)
{
	__BEGIN_TRY

	// 넷마블의 Cpsso 관련된 코드는 서버의 Write 에서는 고치지 않는다  (쓰이지 않으므로 ;;)
	// Client 에서만 알아서 처리해서 보내주도록 한다.
	BYTE szID = m_ID.size();

	if (szID == 0)
		throw InvalidProtocolException("empty ID");
	if (szID > 30)
		throw InvalidProtocolException("too large ID length");

	oStream.write(szID);

	oStream.write(m_ID);

	BYTE szPassword = m_Password.size();

	if (szPassword == 0)
		throw InvalidProtocolException("szPassword == 0");
	if (szPassword > 30)
		throw InvalidProtocolException("too large password length");

	oStream.write(szPassword);

	oStream.write(m_Password);
	oStream.write((char*)m_cMacAddress, 6 * sizeof(BYTE));

	oStream.write(m_LoginMode);

	__END_CATCH
}

void CLLogin::execute (Player* pPlayer) 
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY
		
	CLLoginHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CLLogin::toString () const
	throw()
{
	StringStream msg;
	msg << "CLLogin("
		<< "ID:" << m_ID 
		<< ",Password:" << m_Password 
		<< ")";
	return msg.toString();
}

PacketSize_t CLLogin::getPacketSize() const 
	throw()
{ 
    return szBYTE + m_ID.size() + szBYTE + m_Password.size() + 6 + szBYTE; 
}

bool CLLogin::checkMacAddress(string lastMac) const 
	throw() 
{
	bool retValue = false;

	if(m_strMacAddress	== lastMac)	retValue = true;
	
	return retValue;     
}
