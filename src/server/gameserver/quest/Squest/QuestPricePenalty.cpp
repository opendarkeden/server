//--------------------------------------------------------------------------------
// QuestPricePenalty.h
//--------------------------------------------------------------------------------

#include "QuestPricePenalty.h"
#include "Creature.h"

//--------------------------------------------------------------------------------
// affect ( Creature* )
//--------------------------------------------------------------------------------
void	
QuestPricePenalty::affect(Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	if (pCreature==NULL)
		return;

	// pCreature의 gold감소
	// pCreature의 rankExp감소
	// pCreature의 fame감소
	cout << "[Penalty to " << pCreature->getName().c_str() << "] "
		 << "Gold=" << (int)getGold()
		 << ", RankExp=" << (int)getRankExp()
		 << ", Fame=" << (int)getFame() << endl;

	// 변화된 값들을 DB에 저장

	__END_CATCH
}

