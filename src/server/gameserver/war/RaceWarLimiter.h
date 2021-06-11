#ifndef __RACE_WAR_LIMITER_H__
#define __RACE_WAR_LIMITER_H__

#include "PCLimiter.h"

//--------------------------------------------------------------------------------
//
// 					PCWarLimiter
//
//--------------------------------------------------------------------------------
// 에 대한 출입 체크
//--------------------------------------------------------------------------------
class PCWarLimiter : public PCLimiter<LevelLimitInfo> {
public :
	PCWarLimiter();
	virtual ~PCWarLimiter();

	virtual Race_t 	getRace() const = 0;
	virtual string 	getTableName() const = 0;

	void	clearCurrent() ;

	void	load() ;

	virtual LevelLimitInfo* getLimitInfo(PlayerCreature* pPC)  = 0;

	bool 	join(PlayerCreature* pPC) ;
	bool	leave(PlayerCreature* pPC) ;

	void    saveCurrent(const LevelLimitInfo* pLI) const ;
};


//--------------------------------------------------------------------------------
//
// 							SlayerWarLimiter
//
//--------------------------------------------------------------------------------
class SlayerWarLimiter : public PCWarLimiter {
public :
	SlayerWarLimiter();
	~SlayerWarLimiter();

	Race_t 			getRace() const			{ return RACE_SLAYER; }
	string 			getTableName() const 	{ return "RaceWarPCLimit"; }

	LevelLimitInfo*	getLimitInfo(PlayerCreature* pPC) ;
};

//--------------------------------------------------------------------------------
//
// 							VampireWarLimiter
//
//--------------------------------------------------------------------------------
class VampireWarLimiter : public PCWarLimiter {
public :
	VampireWarLimiter();
	~VampireWarLimiter();

	Race_t 			getRace() const			{ return RACE_VAMPIRE; }
	string 			getTableName() const 	{ return "RaceWarPCLimit"; }

	LevelLimitInfo*	getLimitInfo(PlayerCreature* pPC) ;
};
//--------------------------------------------------------------------------------
//
// 							VampireWarLimiter
//
//--------------------------------------------------------------------------------
class OustersWarLimiter : public PCWarLimiter {
public :
	OustersWarLimiter();
	~OustersWarLimiter();

	Race_t 			getRace() const			{ return RACE_OUSTERS; }
	string 			getTableName() const 	{ return "RaceWarPCLimit"; }

	LevelLimitInfo*	getLimitInfo(PlayerCreature* pPC) ;
};

//--------------------------------------------------------------------------------
//
//							PCWarLimiter
//
//--------------------------------------------------------------------------------
class RaceWarLimiter
{
public :
	static RaceWarLimiter* getInstance()
	{
		static RaceWarLimiter RWL;
		return &RWL;
	}

	void			clearCurrent() ;

	void			load() ;

	bool			join(PlayerCreature* pPC) ;
	bool			leave(PlayerCreature* pPC) ;

	LevelLimitInfo*	getLimitInfo(Race_t race, int index) ;

	// 전쟁 참가자 리스트
	static void		clearPCList() ;
	static void		addPCList(PlayerCreature* pPC) ;
	static bool     isInPCList(PlayerCreature* pPC) ;
	static void		removePCList(PlayerCreature* pPC) ;

private :
	SlayerWarLimiter	m_SlayerWarLimiter;
	VampireWarLimiter	m_VampireWarLimiter;
	OustersWarLimiter	m_OustersWarLimiter;

private :
	RaceWarLimiter() {}
	~RaceWarLimiter() {}
};

#endif
