//////////////////////////////////////////////////////////////////////////////
// Filename    : AlignmentManager.h
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ALIGNMENT_MANAGER_H__
#define __ALIGNMENT_MANAGER_H__

#include "Exception.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// Class AlignmentManager
//////////////////////////////////////////////////////////////////////////////

class AlignmentManager 
{
public:
	AlignmentManager() ;
	~AlignmentManager() ;

public:
	Alignment getAlignmentType(Alignment_t Alignment) ;

	int getMultiplier(Alignment_t AttackerAlignment, Alignment_t DefenderAlignment) ;

	BYTE getDropItemNum(Alignment_t Alignment, bool isPK) ;

	BYTE getDropBonusPercentage(Alignment_t Alignment) ;

	BYTE getMoneyDropPenalty(Alignment_t Alignment) ;

	string toString() const ;
};

// global variable definition
extern AlignmentManager* g_pAlignmentManager;

#endif	// __ALIGNMENT_MANAGER_H__
