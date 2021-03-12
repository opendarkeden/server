//////////////////////////////////////////////////////////////////////////////
// Filename    : Unburrow.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Unburrow.h"
#include "ZoneUtil.h"

#include "Gpackets/GCUnburrowFail.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Unburrow::execute(Vampire * pVampire)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);

	try 
	{
		if (pVampire->isDead())
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);
		
		int x = pVampire->getX();
		int y = pVampire->getY();
								
		if (!pVampire->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			Player * pPlayer = pVampire->getPlayer();
			GCUnburrowFail gcUnburrowFail;
			pPlayer->sendPacket(&gcUnburrowFail);

			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		addUnburrowCreature(pZone, pVampire, x, y, pVampire->getDir());
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Unburrow::execute(Monster* pMonster)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		if (pMonster->isDead())
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);
		
		int x = pMonster->getX();
		int y = pMonster->getY();
								
		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			addUnburrowCreature(pZone, pMonster , x, y, pMonster->getDir());
		}
	} 
	catch(Throwable & t) 
	{
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

Unburrow g_Unburrow;
