#ifndef __SWEEPER_SET_H__
#define __SWEEPER_SET_H__

#include "Types.h"
#include "Exception.h"
#include "MonsterCorpse.h"
#include <vector>
#include <map>
#include <algorithm>
#include "item/Sweeper.h"

class SweeperSet
{
public:
	enum SweeperIndex
	{
		SWEEPER_SLAYER,
		SWEEPER_VAMPIRE,
		SWEEPER_OUSTERS,
		SWEEPER_DEFAULT
	};

	SweeperSet( SweeperIndex idx ) : m_Index(idx)
	{
	//	m_SweeperSafes.reserve(12);
	}

	void	addSafe( uint itemType, MonsterCorpse* pSafe ) { m_SweeperSafes[itemType] = pSafe; }
	MonsterCorpse* getSweeperSafes( uint itemType );
	bool	isSafe( MonsterCorpse* pCorpse ) const; 
	int		getType( MonsterCorpse* pCorpse ) const; 
//	bool	isSafe( MonsterCorpse* pCorpse ) const { return find( m_SweeperSafes.begin(), m_SweeperSafes.end(), pCorpse ) != m_SweeperSafes.end(); }

//	MonsterCorpse*	getLastSafe() const { return m_SweeperSafes.back(); }

	uint	getIndex() const { return m_Index; }

private:
//	vector<MonsterCorpse*>	m_SweeperSafes;
	map<uint, MonsterCorpse*>	m_SweeperSafes;
	SweeperIndex				m_Index;
};

class SweeperSetManager
{
public:
	SweeperSetManager() {}
	virtual ~SweeperSetManager();

	void	load(int level, Zone* pZone);

	int		getSafeIndex( MonsterCorpse* pSafe ) const;
//	bool	isFit( Item* pSweeper, MonsterCorpse* pSafe );
	bool	putSweeper( Item* pSweeper, MonsterCorpse* pSafe );

	SweeperSet* getSweeperSet( uint index ) { return m_SweeperSets[index]; }

	bool	returnAllSweeper();
	bool	returnSweeper( ItemType_t sweeperID , bool bLock = true );
//	bool	returnSweeper( Zone* pZone, Sweeper* pSweeper ) const;

	void	saveSweeperOwner( uint itemType, int safeType, int ownerRace );

private:
	map<uint, SweeperSet*> m_SweeperSets;
	map<ItemType_t, Item*> m_Sweepers;
};

#endif// __SWEEPER_SET_H__
