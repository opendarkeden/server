//////////////////////////////////////////////////////////////////////////////
// Filename    : CLRegisterPlayer.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLRegisterPlayer.h"

void CLRegisterPlayer::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// 플레이어 기본 정보 (ID - Password)
	BYTE szID;
	iStream.read(szID);
	if (szID == 0)
		throw InvalidProtocolException("szID == 0");
	if (szID < minIDLength)
		throw InvalidProtocolException("too short ID length");
	if (szID > maxIDLength)
		throw InvalidProtocolException("too long ID length");
	iStream.read(m_ID , szID);

	BYTE szPassword;
	iStream.read(szPassword);
	if (szPassword == 0)
		throw InvalidProtocolException("szPassword == 0");
	if (szPassword < minPasswordLength)
		throw InvalidProtocolException("too short Password length");
	if (szPassword > maxPasswordLength)
		throw InvalidProtocolException("too long Password length");
	iStream.read(m_Password , szPassword);

	// 플레이어 개인 정보 (Name - Sex - SSN)
	BYTE szName;
	iStream.read(szName);
	if (szName == 0)
		throw InvalidProtocolException("szName == 0");
	if (szName > maxNameLength)
		throw InvalidProtocolException("too long Name length");
	iStream.read(m_Name , szName);

	BYTE sex;
	iStream.read(sex);
	m_Sex = (Sex)sex;

	BYTE szSSN;
	iStream.read(szSSN);
	if (szSSN == 0)
		throw InvalidProtocolException("szSSN == 0");
	if (szSSN > maxSSNLength)
		throw InvalidProtocolException("too long SSN length");
	iStream.read(m_SSN , szSSN);

	// 플레이어 연락처 (Telephone - Cellular - ZipCode - Address - Nation)
	BYTE szTelephone;
	iStream.read(szTelephone);
	if (szTelephone == 0)
		throw InvalidProtocolException("szTelephone == 0");
	if (szTelephone > maxTelephoneLength)
		throw InvalidProtocolException("too long Telephone length");
	iStream.read(m_Telephone , szTelephone);

	BYTE szCellular;
	iStream.read(szCellular);
	if (szCellular == 0)
		throw InvalidProtocolException("szCellular == 0");
	if (szCellular > maxCellularLength)
		throw InvalidProtocolException("too long Cellular length");
	iStream.read(m_Cellular , szCellular);

	BYTE szZipCode;
	iStream.read(szZipCode);
	if (szZipCode == 0)
		throw InvalidProtocolException("szZipCode == 0");
	if (szZipCode > maxZipCodeLength)
		throw InvalidProtocolException("too long ZipCode length");
	iStream.read(m_ZipCode , szZipCode);

	BYTE szAddress;
	iStream.read(szAddress);
	if (szAddress == 0)
		throw InvalidProtocolException("szAddress == 0");
	if (szAddress > maxAddressLength)
		throw InvalidProtocolException("too long Address length");
	iStream.read(m_Address , szAddress);

	BYTE nation;
	iStream.read(nation);
	m_Nation = (Nation)nation;

	// 플레이어 전자 정보 (Email - Homepage)
	BYTE szEmail;
	iStream.read(szEmail);
	if (szEmail == 0)
		throw InvalidProtocolException("szEmail == 0");
	if (szEmail > maxEmailLength)
		throw InvalidProtocolException("too long Email length");
	iStream.read(m_Email , szEmail);

	BYTE szHomepage;
	iStream.read(szHomepage);
	if (szHomepage == 0)
		throw InvalidProtocolException("szHomepage == 0");
	if (szHomepage > maxHomepageLength)
		throw InvalidProtocolException("too long Homepage length");
	iStream.read(m_Homepage , szHomepage);

	// 기타 (Profile - Public)
	BYTE szProfile;
	iStream.read(szProfile);
	if (szProfile == 0)
		throw InvalidProtocolException("szProfile == 0");
	if (szProfile > maxProfileLength)
		throw InvalidProtocolException("too long Profile length");
	iStream.read(m_Profile , szProfile);

	iStream.read(m_bPublic);

	__END_CATCH
}

void CLRegisterPlayer::write (SocketOutputStream & oStream) const
	throw (ProtocolException , Error)
{
	__BEGIN_TRY

	// 플레이어 기본 정보 (ID - Password)
	BYTE szID = m_ID.size();
	if (szID == 0)
		throw InvalidProtocolException("szID == 0");
	if (szID < minIDLength)
		throw InvalidProtocolException("too short ID length");
	if (szID > maxIDLength)
		throw InvalidProtocolException("too long ID length");
	oStream.write(szID);
	oStream.write(m_ID);

	BYTE szPassword = m_Password.size();
	if (szPassword == 0)
		throw InvalidProtocolException("szPassword == 0");
	if (szPassword < minPasswordLength)
		throw InvalidProtocolException("too short Password length");
	if (szPassword > maxPasswordLength)
		throw InvalidProtocolException("too long Password length");
	oStream.write(szPassword);
	oStream.write(m_Password);

	// 플레이어 개인 정보 (Name - Sex - SSN)
	BYTE szName = m_Name.size();
	if (szName == 0)
		throw InvalidProtocolException("szName == 0");
	if (szName > maxNameLength)
		throw InvalidProtocolException("too long Name length");
	oStream.write(szName);
	oStream.write(m_Name);

	oStream.write((BYTE)m_Sex);

	BYTE szSSN = m_SSN.size();
	if (szSSN == 0)
		throw InvalidProtocolException("szSSN == 0");
	if (szSSN > maxSSNLength)
		throw InvalidProtocolException("too long SSN length");
	oStream.write(szSSN);
	oStream.write(m_SSN);

	// 플레이어 연락처 (Telephone - Cellular - ZipCode - Address - Nation)
	BYTE szTelephone = m_Telephone.size();
	if (szTelephone == 0)
		throw InvalidProtocolException("szTelephone == 0");
	if (szTelephone > maxTelephoneLength)
		throw InvalidProtocolException("too long Telephone length");
	oStream.write(szTelephone);
	oStream.write(m_Telephone);

	BYTE szCellular = m_Cellular.size();
	if (szCellular == 0)
		throw InvalidProtocolException("szCellular == 0");
	if (szCellular > maxCellularLength)
		throw InvalidProtocolException("too long Cellular length");
	oStream.write(szCellular);
	oStream.write(m_Cellular);

	BYTE szZipCode = m_ZipCode.size();
	if (szZipCode == 0)
		throw InvalidProtocolException("szZipCode == 0");
	if (szZipCode > maxZipCodeLength)
		throw InvalidProtocolException("too long ZipCode length");
	oStream.write(szZipCode);
	oStream.write(m_ZipCode);

	BYTE szAddress = m_Address.size();
	if (szAddress == 0)
		throw InvalidProtocolException("szAddress == 0");
	if (szAddress > maxAddressLength)
		throw InvalidProtocolException("too long Address length");
	oStream.write(szAddress);
	oStream.write(m_Address);

	oStream.write((BYTE)m_Nation);

	// 플레이어 전자 정보 (Email - Homepage)
	BYTE szEmail = m_Email.size();
	if (szEmail == 0)
		throw InvalidProtocolException("szEmail == 0");
	if (szEmail > maxEmailLength)
		throw InvalidProtocolException("too long Email length");
	oStream.write(szEmail);
	oStream.write(m_Email);

	BYTE szHomepage = m_Homepage.size();
	if (szHomepage == 0)
		throw InvalidProtocolException("szHomepage == 0");
	if (szHomepage > maxHomepageLength)
		throw InvalidProtocolException("too long Homepage length");
	oStream.write(szHomepage);
	oStream.write(m_Homepage);

	// 기타 (Profile - Public)
	BYTE szProfile = m_Profile.size();
	if (szProfile == 0)
		throw InvalidProtocolException("szProfile == 0");
	if (szProfile > maxProfileLength)
		throw InvalidProtocolException("too long Profile length");
	oStream.write(szProfile);
	oStream.write(m_Profile);

	oStream.write(m_bPublic);

	__END_CATCH
}

void CLRegisterPlayer::execute (Player* pPlayer)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CLRegisterPlayerHandler::execute(this , pPlayer);

	__END_CATCH
}

string CLRegisterPlayer::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CLRegisterPlayer("
		<< "ID:" << m_ID
		<< ",Password:" << m_Password 
		<< ",Name:" << m_Name
		<< ",Sex:" << Sex2String[m_Sex]
		<< ",SSN:" << m_SSN
		<< ",Telephone:" << m_Telephone
		<< ",Cellular:" << m_Cellular
		<< ",ZipCode:" << m_ZipCode
		<< ",Address:" << m_Address
		<< ",Nation:" << Nation2String[m_Nation]
		<< ",e-mail:" << m_Email
		<< ",Homepage:" << m_Homepage
		<< ",Profile:" << m_Profile
		<< ",Public:" << ((m_bPublic==true)?"PUBLIC":"PRIVATE")
		<< ")";
	return msg.toString();

	__END_CATCH
}
		    
