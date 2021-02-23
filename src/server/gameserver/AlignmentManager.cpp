//////////////////////////////////////////////////////////////////////////////
// Filename    : AlignmentManager.cpp
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "AlignmentManager.h"
#include "Assert.h"
#include "DB.h"
#include <algo.h>

AlignmentManager* g_pAlignmentManager = NULL;

//////////////////////////////////////////////////////////////////////////////
// class AlignmentManager member methods
//////////////////////////////////////////////////////////////////////////////

AlignmentManager::AlignmentManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

AlignmentManager::~AlignmentManager()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

Alignment AlignmentManager::getAlignmentType(Alignment_t Alignment)
	throw()
{
	__BEGIN_TRY

	if (Alignment <= -10000)
	{
		return LESS_EVIL;
	}
	if (Alignment >= -10000 && Alignment < -7500) 
	{
		return LESS_EVIL;
	} 
	else if (Alignment >= -7500 && Alignment < -2500) 
	{
		return EVIL;
	} 
	else if (Alignment >= -2500 && Alignment < 2500) 
	{
		return NEUTRAL;
	}
	else if (Alignment >= 2500 && Alignment < 7500) 
	{
		return GOOD;
	} 
	else if (Alignment >= 7500 && Alignment <= 10000) 
	{
		return MORE_GOOD;
	} 
	else 
	{
		return MORE_GOOD;
	}
	
	__END_CATCH
}

int AlignmentManager::getMultiplier(Alignment_t AttackerAlignment, Alignment_t DefenderAlignment)
	throw()
{
	__BEGIN_TRY
	
	Alignment AAlignmentType = getAlignmentType(AttackerAlignment);
	Alignment DAlignmentType = getAlignmentType(DefenderAlignment);

	// 공격자의 성향이 Good, More Good 이면
	if (AAlignmentType >= GOOD) 
	{
		// 방어자의 성향이 GOOD, More Good 이면
		if (DAlignmentType >= GOOD) 
		{
			// 공격자의 성향이 상대 선이면 -2
			if (AttackerAlignment > DefenderAlignment) 
			{
				return -200;
			} 
			// 공격자의 성향이 상대 악이면 -3
			else if (AttackerAlignment <= DefenderAlignment) 
			{
				return -300;
			}
		} 
		// 방어자의 성향이 NEUTRAL 이면,
		else if (DAlignmentType == NEUTRAL) 
		{
			return -100;
		} 
		// 방어자의 성향이 Evil, Less Evil 이면,
		else if (DAlignmentType <= EVIL) {
			return 200;
		}
	} 
	else if (getAlignmentType(AttackerAlignment) == NEUTRAL) 
	{
		// 방어자의 성향이 GOOD, More Good 이면
		if (DAlignmentType >= GOOD) 
		{
			return -300;
		} 
		// 방어자의 성향이 NEUTRAL 이면,
		else if (DAlignmentType == NEUTRAL) 
		{
			// 공격자의 성향이 상대 선이면 -1
			if (AttackerAlignment > DefenderAlignment) 
			{
				return -100;
			} 
			// 공격자의 성향이 상대 악이면 -2
			else if (AttackerAlignment <= DefenderAlignment) 
			{
				return -200;
			}
		} 
		// 방어자의 성향이 Evil, Less Evil 이면,
		else if (DAlignmentType <= EVIL) 
		{
			return 100;
		}
	} 
	else if (getAlignmentType(AttackerAlignment) <= EVIL) 
	{
		// 방어자의 성향이 GOOD, More Good 이면
		if (DAlignmentType >= GOOD) 
		{
			return -300;
		} 
		// 방어자의 성향이 NEUTRAL 이면,
		else if (DAlignmentType == NEUTRAL) 
		{
			return -200;
		} 
		// 방어자의 성향이 Evil, Less Evil 이면,
		else if (DAlignmentType <= EVIL) 
		{
			// 공격자의 성향이 상대 선이면 2
			if (AttackerAlignment > DefenderAlignment) 
			{
				return 200;
			} 
			// 공격자의 성향이 상대 악이면 1
			else if (AttackerAlignment <= DefenderAlignment) {
				return 100;
			}
		}
	} 
	else 
	{
		return -300;
	}

	return -300;

	__END_CATCH
}

BYTE AlignmentManager::getDropItemNum(Alignment_t Alignment, bool isPK)
	throw()
{
	__BEGIN_TRY

	int Count = 0;

	if (Alignment > -10000 && Alignment < -7500) 
	{
		Count = 2;
	}
	else if (Alignment >= -7500 && Alignment < -2500) 
	{
		Count = 1;
	}
	else if (Alignment == -10000) 
	{
		Count = 3;
	}

	/*
	언제 변경된 지는 알 수 없지만, 성향이 착한 사람이 아이템을 떨어뜨리는
	일이 발생하기 시작했다. PCManager.cpp의 killCreature() 부분의
	주석을 좀 지우다가 예전에 뭔가 있던 것을 날린 것 같은데,
	일단 성향이 착한 사람이 아이템을 떨어뜨리지 않게 하기 위해서 이 부분을
	주석처리한다. -- 2001.12.25 김성민
	int Percent = getDropBonusPercentage(Alignment);

	if (isPK) 
	{
		Count = max(0, Count - 1);
		Percent = Percent/2;
	}

	Count = max(0, Count);
	Count = min(5, Count);

	if (Random(1, 100) < Percent) 
	{
		Count++;
	}
	*/

	return (BYTE)Count;

	__END_CATCH
}

BYTE AlignmentManager::getDropBonusPercentage(Alignment_t Alignment)
	throw()
{
	__BEGIN_TRY
	return 0;

	int Percent = (10000 - Alignment) / 400;

	Percent = max(0, Percent);
	Percent = min(50, Percent);

	return (BYTE)Percent;

	__END_CATCH
}

BYTE AlignmentManager::getMoneyDropPenalty(Alignment_t Alignment)
	throw()
{
	__BEGIN_TRY

	BYTE Penalty = 0;

	if (Alignment == 10000) 
	{
		Penalty = 0;
	}
	else if (Alignment >=  7500  && Alignment < 10000) 
	{
		Penalty = 1;
	} 
	else if (Alignment >=  2500  && Alignment <  7500) 
	{
		Penalty = 2;
	}
	else if (Alignment >= -2500  && Alignment <  2500) 
	{
		Penalty = 4;
	} 
	else if (Alignment >= -7500  && Alignment < -2500) 
	{
		Penalty = 8;
	}
	else if (Alignment >= -10000 && Alignment < -7500) 
	{
		Penalty = 16;
	} 
	else 
	{
		Penalty = 32;
	}

	return Penalty;

	__END_CATCH
}

string AlignmentManager::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "AlignmentManager ("
			<< ")";
	return msg.toString();

	__END_CATCH
}


