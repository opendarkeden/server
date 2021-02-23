#ifndef __MONSTER_SELECTOR_H__
#define __MONSTER_SELECTOR_H__

#include "Types.h"
#include "Exception.h"

//--------------------------------------------------------------------------------
// MonsterSelector
//--------------------------------------------------------------------------------
class MonsterSelector {
public :
	MonsterSelector(const MonsterSelector& mtc)
	{
		m_MonsterType = mtc.m_MonsterType;
		m_SpriteType = mtc.m_SpriteType;
		m_Number = mtc.m_Number;
	}
	MonsterSelector(MonsterType_t monsterType, SpriteType_t spriteType, int number)
	{
		m_MonsterType = monsterType;
		m_SpriteType = spriteType;
		m_Number = number;			
	}
	~MonsterSelector() {}

	MonsterType_t		getMonsterType() const	{ return m_MonsterType; }
	SpriteType_t		getSpriteType() const	{ return m_SpriteType; }
	int					getNumber() const		{ return m_Number; }

	void				setMonsterType(MonsterType_t m) 	{ m_MonsterType = m; }
	void				setSpriteType(SpriteType_t s) 		{ m_SpriteType = s; }
	void				setNumber(int n)					{ m_Number = n; }

	bool				decreaseNumber()		{ if (m_Number>0) { m_Number--; return true; } return false; }

	bool				operator == (const MonsterSelector& mtc) const
	{
		if (m_MonsterType!=0)
			return m_MonsterType==mtc.m_MonsterType;

		if (m_SpriteType!=0)
			return m_SpriteType==mtc.m_SpriteType;

		return false;
	}

	void				setMonster(const string& text) throw (Error);
	string				toString() const throw(Error);

private :
	MonsterType_t		m_MonsterType;
	SpriteType_t		m_SpriteType;
	int					m_Number;
};

#endif
