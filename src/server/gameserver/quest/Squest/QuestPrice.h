//--------------------------------------------------------------------------------
// QuestPrice.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_PRICE_H__
#define __QUEST_PRICE_H__

#include "Types.h"
#include "Exception.h"

class Item;
class Creature;

enum QuestPriceType
{
	QUEST_PRICE_REWARD,
	QUEST_PRICE_PENALTY,
	
	QUEST_PRICE_MAX
};

//--------------------------------------------------------------------------------
// QuestPrice
//--------------------------------------------------------------------------------
class QuestPrice {

public :
	QuestPrice(Gold_t gold=0, RankExp_t rankExp=0, Fame_t fame=0) 
		: m_Gold(gold), m_RankExp(rankExp), m_Fame(fame) {}
	virtual ~QuestPrice() {}

	virtual QuestPriceType	getQuestPriceType() const = 0;

	virtual void	affect(Creature* pCreature) throw (Error) {}
	virtual void	affect(Item* pItem) throw (Error) {}

	Gold_t			getGold() const				{ return m_Gold; }
	void			setGold(Gold_t gold)		{ m_Gold = gold; }

	RankExp_t		getRankExp() const			{ return m_RankExp; }
	void			setRankExp(RankExp_t RankExp)	{ m_RankExp = RankExp; }

	Fame_t			getFame() const				{ return m_Fame; }
	void			setFame(Fame_t fame)		{ m_Fame = fame; }

	virtual void	setPrice(const string& text) throw (Error);

	string			toString() const throw (Error);

private :
	Gold_t			m_Gold;
	RankExp_t		m_RankExp;
	Fame_t			m_Fame;
};


#endif

