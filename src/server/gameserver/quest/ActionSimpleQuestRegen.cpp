////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestRegen.cpp
// Written By  : 
// Description : 
// 상점 NPC를 제일 처음 로딩할 때, 상점 NPC가 팔게 될 아이템을
// 준비하는 액션이다. ShopTemplate 클래스와 매니저를 참고할 것.
////////////////////////////////////////////////////////////////////////////////

#include "ActionSimpleQuestRegen.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionSimpleQuestRegen::ActionSimpleQuestRegen()
	
{
	__BEGIN_TRY

	m_Period.tv_sec     = 0;
	m_Period.tv_usec    = 0;
	m_NextRegen.tv_sec  = 0;
	m_NextRegen.tv_usec = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionSimpleQuestRegen::~ActionSimpleQuestRegen()
	
{
	__BEGIN_TRY

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestRegen::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		//int m_Num   = propertyBuffer.getPropertyInt("Num");

		// 상점 업데이트 주기를 읽어들인다. (초 단위)
		int nSecond = propertyBuffer.getPropertyInt("Period");

		m_Period.tv_sec = nSecond;

		// 다음 상점 업데이트를 언제 할 것인가를 세팅해 준다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		m_NextRegen = currentTime;
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
// NOTE : ShopTemplate은 이 액션이 실행되기 전에 모두 로드되어 있어야 한다.
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestRegen::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

/*	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert(pNPC != NULL);

	Zone* pZone = pNPC->getZone();
	Assert(pZone != NULL);

	// 현재 시간을 얻어낸다.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// 업데이트할 시간이 아직 되직 않았다면 걍 리턴한다.
	if (currentTime < m_NextRegen) return;

	// 주위에 NPC랑 이야기하고 있는 플레이어가 없는지 먼저 검사한다.
	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
	int centerX = pNPC->getX();
	int centerY = pNPC->getY();
	try
	{
		for (int zx = centerX - 5; zx <= centerX+5; zx++)
		{
			for (int zy = centerY - 5; zy <= centerY+5; zy++)
			{
				// 좌표가 한계를 넘어가지 않았는지 체크...
				if (!rect.ptInRect(zx, zy))
				{
					continue;
				}

				Tile& tile = pZone->getTile(zx, zy);

				// 걸어다니는 크리쳐를 검색
				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					Assert(pNearCreature != NULL);
					// NPC랑 이야기하고 있는 놈이 있으면 걍 리턴
					if (pNearCreature->isPC())
					{
						return;
					}
				}
				// 날아다니는 크리쳐를 검색
				if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					Assert(pNearCreature != NULL);
					// NPC랑 이야기하고 있는 놈이 있으면 걍 리턴
					if (pNearCreature->isPC())
					{
						return;
					}
				}
			}
		}
	}
	catch (Throwable & t)
	{
		filelog("questBUG.txt", "%s", t.toString().c_str());
		return;
	}

	try {

		pNPC->regenSimpleQuest();


	} catch (Error& t) {
		// 에러는 다시 던진다.
		filelog("regenQuestBug.txt", "%s", t.toString().c_str());
		throw;
	} catch (Throwable& t) {
		filelog("regenQuestBug.txt", "%s", t.toString().c_str());
	}

	// 다음 업데이트할 시간을 정해준다.
	m_NextRegen = m_NextRegen + m_Period;*/

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSimpleQuestRegen::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionSimpleQuestRegen()";

	return msg.toString();

	__END_CATCH
}
