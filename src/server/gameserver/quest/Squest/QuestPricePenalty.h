//--------------------------------------------------------------------------------
// QuestPricePenalty.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_PRICE_PENALTY_H__
#define __QUEST_PRICE_PENALTY_H__

#include "QuestPrice.h"

//--------------------------------------------------------------------------------
// QuestPricePenalty
//--------------------------------------------------------------------------------
class QuestPricePenalty : public QuestPrice {
public :
	QuestPricePenalty(Gold_t gold=0, RankExp_t rankExp=0, Fame_t fame=0)
		                : QuestPrice(gold, rankExp, fame) {}

	QuestPriceType	getQuestPriceType() const { return QUEST_PRICE_REWARD; }

	virtual void	affect(Creature* pCreature) throw (Error);	
};

#endif

