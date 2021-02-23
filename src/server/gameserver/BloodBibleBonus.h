//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBibleBonus.h
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __BLOOD_BIBLE_BONUS_H__
#define __BLOOD_BIBLE_BONUS_H__

#include "Types.h"
#include "ItemUtil.h"

typedef list<OptionType_t>				OptionTypeList;
typedef OptionTypeList::iterator		OptionTypeListItor;
typedef OptionTypeList::const_iterator	OptionTypeListConstItor;

class BloodBibleBonus
{
public:
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	enum BloodBibleBonusType
	{
		BLOOD_BIBLE_BONUS_ARMEGA,
		BLOOD_BIBLE_BONUS_MIHOLE,
		BLOOD_BIBLE_BONUS_KIRO,
		BLOOD_BIBLE_BONUS_INI,
		BLOOD_BIBLE_BONUS_GREGORI,
		BLOOD_BIBLE_BONUS_CONCILIA,
		BLOOD_BIBLE_BONUS_LEGIOS,
		BLOOD_BIBLE_BONUS_HILLEL,
		BLOOD_BIBLE_BONUS_JAVE,
		BLOOD_BIBLE_BONUS_NEMA,
		BLOOD_BIBLE_BONUS_AROSA,
		BLOOD_BIBLE_BONUS_CHASPA,

		BLOOD_BIBLE_BONUS_MAX
	};

public:
	BloodBibleBonus() throw() {}
	~BloodBibleBonus() throw() { clearOptionTypeList(); }

public:
	BloodBibleBonusType_t getType() const { return m_Type; }
	void setType( DWORD type ) { m_Type = type; }

	string getName() const { return m_Name; }
	void setName( string name ) { m_Name = name; }

	Race_t getRace() const { return m_Race; }
	void setRace( Race_t race ) { m_Race = race; }

	void clearOptionTypeList() { m_OptionTypeList.clear(); }
	const OptionTypeList& getOptionTypeList() const { return m_OptionTypeList; }
	void setOptionTypeList( const string& optionList ) { makeOptionList( optionList, m_OptionTypeList ); } 
	string toString() const throw();

protected:
	BloodBibleBonusType_t	m_Type;
	string					m_Name;
	Race_t					m_Race;
	OptionTypeList			m_OptionTypeList;

};

#endif
