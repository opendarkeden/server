#ifndef __PC_LIMITER_H__
#define __PC_LIMITER_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include <vector>

class PlayerCreature;

//--------------------------------------------------------------------------------
//
// 								LimitInfo
//
//--------------------------------------------------------------------------------
// 숫자 제한 : 0 <= Current <= Limit
//--------------------------------------------------------------------------------
class LimitInfo {
public :
	LimitInfo( int limit ) : m_nCurrent( 0 ), m_nLimit(limit) {}

	int		getCurrent() const			{ return m_nCurrent; }
	void	setCurrent(int current) 	{ m_nCurrent = current; }

	int		getLimit() const	{ return m_nLimit; }
	void	setLimit(int limit) { m_nLimit = limit; }

	bool	isLimit() const 	{ return m_nCurrent >= m_nLimit; }

	void	increase() { if (m_nCurrent < m_nLimit) m_nCurrent++; }
	void	decrease() { if (m_nCurrent > 0) m_nCurrent--; }

	void	operator = (const LimitInfo& li) { m_nCurrent = li.m_nCurrent; m_nLimit = li.m_nLimit; }

protected :
	int			m_nCurrent;
	int			m_nLimit;
};

//--------------------------------------------------------------------------------
//
// 								LevelLimitInfo
//
//--------------------------------------------------------------------------------
// 숫자 제한 : 특정 레벨(MinLevel ~ MaxLevel)의 사용자 제한
// 0 <= Current <= Limit
//--------------------------------------------------------------------------------
class LevelLimitInfo : public LimitInfo {
public :
	LevelLimitInfo( int ID, int minLevel, int maxLevel, int limit ) : LimitInfo(limit)
	{
		m_ID = ID;
		m_MinLevel = minLevel;
		m_MaxLevel = maxLevel;
	}

	int 	getID() const			{ return m_ID; }
	int 	getMaxLevel() const		{ return m_MaxLevel; }
	int		getMinLevel() const		{ return m_MinLevel; }

	bool	isLevelInRange(int level) const	{ return level>=m_MinLevel && level<=m_MaxLevel; }

	void	operator = (const LevelLimitInfo& li) 
	{ 
		m_nCurrent 	= li.m_nCurrent; 
		m_nLimit 	= li.m_nLimit; 
		m_ID	 	= li.m_ID; 
		m_MinLevel 	= li.m_MinLevel; 
		m_MaxLevel 	= li.m_MaxLevel; 
	}

private :
	int		m_ID;		// 구분용 ID
	int 	m_MinLevel;
	int 	m_MaxLevel;
};


//--------------------------------------------------------------------------------
//
// 								PCLimiter
//
//--------------------------------------------------------------------------------
// PlayerCreature에 대한 출입 체크
//--------------------------------------------------------------------------------
template <class T>
class PCLimiter {
public :
	typedef T 						LimitInfo_t;
	typedef vector<LimitInfo_t> 	LimitInfos;

public :
	PCLimiter();
	virtual ~PCLimiter();

	virtual void		clear();

	virtual void		load() throw (Error) = 0;

	virtual bool 		join(PlayerCreature* pPC) throw (Error) = 0;
	virtual bool		leave(PlayerCreature* pPC) throw (Error) = 0;

	int					getSize() const						{ return m_LimitInfos.size(); }
	LimitInfo_t* 		getLimitInfoByIndex(int index) throw (Error);

protected :
	void 				lock() throw(Error) 	{ m_Mutex.lock(); }
	void 				unlock() throw(Error) 	{ m_Mutex.unlock(); }

	void				addLimitInfo(const LimitInfo_t& limitInfo)	{ m_LimitInfos.push_back( limitInfo ); }

	virtual LimitInfo_t* getLimitInfo(PlayerCreature* pPC) throw (Error) = 0;

protected:
	LimitInfos			m_LimitInfos;

	mutable Mutex 		m_Mutex;
};


//--------------------------------------------------------------------------------
//
// 							PCLimiter
//
//--------------------------------------------------------------------------------
template <class T>
PCLimiter<T>::PCLimiter()
{
	m_Mutex.setName("PCLimiter");
}

template <class T>
PCLimiter<T>::~PCLimiter()
{
}

//--------------------------------------------------------------------------------
// clear
//--------------------------------------------------------------------------------
template <class T>
void        
PCLimiter<T>::clear() 
{
	m_LimitInfos.clear();
}

template <class T>
PCLimiter<T>::LimitInfo_t* 
PCLimiter<T>::getLimitInfoByIndex(int index) 
	throw (Error)
{
	__BEGIN_TRY

	if (index < 0 || index >= (int)m_LimitInfos.size())
	{
		return NULL;
	}

	return &(m_LimitInfos[index]);

	__END_CATCH
}

#endif
