#ifndef __SOMETHING_GROWING_UP_H__
#define __SOMETHING_GROWING_UP_H__

#include "DB.h"
#include "Assert.h"

#include <vector>
#include <string>
#include <cstdio>

template <typename _GoalExpType, typename _LevelType, _LevelType _MinLevel, _LevelType _MaxLevel, typename _TotalExpType = _GoalExpType>
class ExpTable
{
public:
	typedef _GoalExpType GoalExpType;
	typedef _LevelType LevelType;
	typedef _TotalExpType TotalExpType;

	static const LevelType MaxLevel = _MaxLevel;
	static const LevelType MinLevel = _MinLevel;

	ExpTable() : m_Records(MaxLevel) { }
	virtual ~ExpTable() { }

	// DB 관련 함수들
	virtual void load();
	virtual const string getDBTableName() const = 0;
	virtual const string getDBGoalExpFieldName() const { return "GoalExp"; }
	virtual const string getDBAccumExpFieldName() const { return "AccumExp"; }
	virtual const string getDBLevelFieldName() const { return "Level"; }
	virtual const string getDBQueryCondition() const { return ""; }

	// 쿼리하기
	GoalExpType getGoalExp( LevelType level ) const { Assert( level <= MaxLevel && level >= MinLevel ); return m_Records[level].m_GoalExp; }
	TotalExpType getAccumExp( LevelType level ) const { Assert( level <= MaxLevel && level >= MinLevel ); return m_Records[level].m_AccumExp; }

private:
	class TableRecord
	{
	public:
		GoalExpType		m_GoalExp;
		TotalExpType	m_AccumExp;
	};

	vector<TableRecord>	m_Records;
};


template <typename GoalExpType, typename LevelType, LevelType MinLevel, LevelType MaxLevel, typename TotalExpType>
void ExpTable<GoalExpType, LevelType, MinLevel, MaxLevel, TotalExpType>::load()
{
	__BEGIN_TRY

	const string QueryTemplate = "SELECT %s, %s, %s FROM %s %s";

	// 10바이트 정도 오바는 봐주자
	int size = QueryTemplate.size() + getDBTableName().size() + getDBGoalExpFieldName().size() + getDBAccumExpFieldName().size() + getDBLevelFieldName().size() + getDBQueryCondition().size();
	char* query = new char[size];

	snprintf( query, size, QueryTemplate.c_str(), getDBLevelFieldName().c_str(), getDBGoalExpFieldName().c_str(), getDBAccumExpFieldName().c_str(), getDBTableName().c_str(), getDBQueryCondition().c_str() );

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( query );

		while ( pResult->next() )
		{
			LevelType level = pResult->getInt(1);
			Assert( level >= MinLevel );
			Assert( level <= MaxLevel );
			m_Records[level].m_GoalExp = pResult->getInt(2);
			m_Records[level].m_AccumExp = pResult->getInt(3);
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt );

	SAFE_DELETE( query );

	__END_CATCH
}

template <class ExpTableClass>
class SomethingGrowingUp
{
public:
	typedef	typename ExpTableClass::GoalExpType GoalExpType;
	typedef typename ExpTableClass::LevelType LevelType;
	typedef typename ExpTableClass::TotalExpType TotalExpType;

	static const LevelType MaxLevel = ExpTableClass::MaxLevel;
	static const LevelType MinLevel = ExpTableClass::MinLevel;

	SomethingGrowingUp(LevelType level, GoalExpType goalExp, const ExpTableClass& ExpTable)
		: m_Level(level), m_GoalExp(goalExp), m_ExpTable(ExpTable) { }

	LevelType	getLevel() const { return m_Level; }
	GoalExpType	getGoalExp() const { return m_GoalExp; }
	TotalExpType	getTotalExp() const { return m_ExpTable.getAccumExp( m_Level ) - m_GoalExp; }

	bool increaseExp( GoalExpType exp, bool canLevelUp = true, bool giveRemainExp = false );
	bool levelUp();
	bool levelDown();

	// 꼭 필요할때만 씁시다.
	bool SET_LEVEL( LevelType level );

private:
	void setLevel( LevelType level );

	LevelType		m_Level;
	GoalExpType		m_GoalExp;
	const ExpTableClass&	m_ExpTable;
};

template <class ExpTableClass>
bool SomethingGrowingUp<ExpTableClass>::increaseExp( GoalExpType exp, bool canLevelUp, bool giveRemainExp )
{
	if ( m_GoalExp <= exp )
	{
		if ( canLevelUp )
		{
			GoalExpType remainExp = exp - m_GoalExp;
			if ( levelUp() )
			{
				if ( giveRemainExp ) increaseExp( remainExp, true, true );
				return true;
			}
		}
		else exp = m_GoalExp;
	}

	m_GoalExp -= exp;
	return false;
}

template <class ExpTableClass>
bool SomethingGrowingUp<ExpTableClass>::SET_LEVEL( LevelType level )
{
	if ( level < MinLevel || level > MaxLevel ) return false;
	setLevel( level );
	return true;
}

template <class ExpTableClass>
void SomethingGrowingUp<ExpTableClass>::setLevel( LevelType level )
{
	m_Level = level;
	m_GoalExp = m_ExpTable.getGoalExp( level );
}

template <class ExpTableClass>
bool SomethingGrowingUp<ExpTableClass>::levelUp()
{
	if ( m_Level == MaxLevel ) return false;
	setLevel( m_Level + 1 );
	return true;
}

template <class ExpTableClass>
bool SomethingGrowingUp<ExpTableClass>::levelDown()
{
	if ( m_Level == MinLevel ) return false;
	setLevel( m_Level - 1 );
	return true;
}

#endif
