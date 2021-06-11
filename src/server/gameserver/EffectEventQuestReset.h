//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEventQuestReset.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EVENT_QUEST_RESET__
#define __EFFECT_EVENT_QUEST_RESET__

#include "Effect.h"
#include "EffectLoader.h"

#define EVENT_QUEST_TIME_LIMIT (12*3600)
#define BROADCASTING_DELAY (600)

//////////////////////////////////////////////////////////////////////////////
// class EffectEffectEventQuestReset
//////////////////////////////////////////////////////////////////////////////

class EffectEventQuestReset : public Effect 
{
public:
	EffectEventQuestReset(Creature* pCreature, int type) ;
	~EffectEventQuestReset() ;

public:
	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

    EffectClass getEffectClass() const  { return EFFECT_CLASS_TRANSPORT_CREATURE; }

	string toString() const ;

public:
	int m_Type;
};

#endif // __EFFECT_EVENT_QUEST_RESET__
