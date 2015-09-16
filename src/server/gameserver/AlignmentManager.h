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
	AlignmentManager() throw();
	~AlignmentManager() throw();

public:
	Alignment getAlignmentType(Alignment_t Alignment) throw();

	int getMultiplier(Alignment_t AttackerAlignment, Alignment_t DefenderAlignment) throw();

	BYTE getDropItemNum(Alignment_t Alignment, bool isPK) throw();

	BYTE getDropBonusPercentage(Alignment_t Alignment) throw();

	BYTE getMoneyDropPenalty(Alignment_t Alignment) throw();

	string toString() const throw();
};

// global variable definition
extern AlignmentManager* g_pAlignmentManager;

#endif	// __ALIGNMENT_MANAGER_H__
