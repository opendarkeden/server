#ifndef __SMS_ADDRESS_BOOK_H__
#define __SMS_ADDRESS_BOOK_H__

#include "Types.h"

#include "Gpackets/GCSMSAddressList.h"

#include <string>
#include <hash_map>

#define MAX_ADDRESS_NUM 30

class PlayerCreature;
class SMSAddressBook;

class SMSAddressElement
{
public:
	SMSAddressElement( DWORD eID, const string& name, const string& cName, const string& number ) :
		m_ElementID(eID), m_CharacterName(name), m_CustomName(cName), m_Number(number) { }

	AddressUnit*	getAddressUnit() const;
	DWORD			getID() const { return m_ElementID; }

	friend class SMSAddressBook;

private:
	DWORD	m_ElementID;
	string	m_CharacterName;
	string	m_CustomName;
	string	m_Number;
};

class SMSAddressBook
{
public:
	SMSAddressBook( PlayerCreature* pOwner ) : m_pOwner(pOwner) { m_Addresses.clear(); }
	~SMSAddressBook();

	void load() throw(Error);

	GCSMSAddressList*	getGCSMSAddressList() const;

	int addAddressElement( SMSAddressElement* pElement );
	int removeAddressElement( DWORD eID );

	DWORD	popNextEID() { return m_NextEID++; }

private:
	PlayerCreature*						m_pOwner;
	hash_map<DWORD, SMSAddressElement*>	m_Addresses;

	DWORD								m_NextEID;
};

#endif
