//--------------------------------------------------------------------------------
// QuestPriceReward.h
//--------------------------------------------------------------------------------

#include "QuestPriceReward.h"
#include "Creature.h"

//--------------------------------------------------------------------------------
// affect ( Creature* )
//--------------------------------------------------------------------------------
void	
QuestPriceReward::affect(Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	if (pCreature==NULL)
		return;

	// pCreature의 gold증가
	// pCreature의 rankExp증가
	// pCreature의 fame증가
	cout << "[Reward to " << pCreature->getName().c_str() << "] "
		<< "Gold=" << (int)getGold()
		<< ", RankExp=" << (int)getRankExp()
		<< ", Fame=" << (int)getFame() << endl;

	// 변화된 값들을 DB에 저장

	__END_CATCH
}

