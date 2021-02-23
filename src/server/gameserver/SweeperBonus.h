//////////////////////////////////////////////////////////////////////////////
// Filename    : SweeperBonus.h
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SWEEPER_BONUS_H__
#define __SWEEPER_BONUS_H__

#include "Types.h"
#include "ItemUtil.h"

typedef list<OptionType_t>				OptionTypeList;
typedef OptionTypeList::iterator		OptionTypeListItor;
typedef OptionTypeList::const_iterator	OptionTypeListConstItor;

class SweeperBonus
{

public:
	SweeperBonus() throw() {}
	~SweeperBonus() throw() { clearOptionTypeList(); }

public:
	SweeperBonusType_t getType() const { return m_Type; }
	void setType( DWORD type ) { m_Type = type; }

	string getName() const { return m_Name; }
	void setName( string name ) { m_Name = name; }

	int getLevel() const { return m_Level; }
	void setLevel( int level ) { m_Level = level; }

	Race_t getRace() const { return m_Race; }
	void setRace( Race_t race );

	void clearOptionTypeList() { m_OptionTypeList.clear(); }
	const OptionTypeList& getOptionTypeList() const { return m_OptionTypeList; }
	void setOptionTypeList( const string& optionList ) { makeOptionList( optionList, m_OptionTypeList ); } 
	string toString() const throw();

protected:
	SweeperBonusType_t		m_Type;
	string					m_Name;
	int						m_Level;
	Race_t					m_Race;
	OptionTypeList			m_OptionTypeList;

};

#endif
