//////////////////////////////////////////////////////////////////////////////
// Filename   : SkillHandler.cpp
// Written by : elca@ewestsoft.com
// Description:
//////////////////////////////////////////////////////////////////////////////

#include "SkillHandler.h"
#include "SkillInfo.h"
#include "Player.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Party.h"
#include "ZoneUtil.h"
#include <math.h>

#include "GCSkillFailed1.h"

//#include "LogClient.h"

//////////////////////////////////////////////////////////////////////////////
// class SkillInput & SkillOutput member methods
//////////////////////////////////////////////////////////////////////////////

SkillInput::SkillInput(Slayer* pSlayer, SkillSlot* pSkillSlot)
{
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	SkillLevel  = pSkillSlot->getExpLevel();
	STR 		= pSlayer->getSTR(ATTR_CURRENT);
	DEX 		= pSlayer->getDEX(ATTR_CURRENT);
	INTE        = pSlayer->getINT(ATTR_CURRENT);
	TargetType  = TARGET_MAX;
	Range       = pSlayer->getAdvancementClassLevel();
	
	Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pWeapon != NULL) IClass = pWeapon->getItemClass();
	else IClass = Item::ITEM_CLASS_MAX;

	PartySize = 1;

	SkillType_t SkillType = pSkillSlot->getSkillType();
	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
	SkillDomainType_t domainType = pSkillInfo->getDomainType();
	DomainLevel = pSlayer->getSkillDomainLevel(domainType);
}

SkillInput::SkillInput(Vampire* pVampire)
{
	Assert(pVampire != NULL);

	SkillLevel  = pVampire->getLevel();
	STR         = pVampire->getSTR(ATTR_CURRENT);
	DEX         = pVampire->getDEX(ATTR_CURRENT);
	INTE        = pVampire->getINT(ATTR_CURRENT);
	TargetType  = TARGET_MAX;
	Range       = pVampire->getAdvancementClassLevel();
	IClass      = Item::ITEM_CLASS_MAX;
	PartySize   = 0;
	DomainLevel = 0;
}

SkillInput::SkillInput(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot)
{
	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	SkillLevel  = pOustersSkillSlot->getExpLevel();
	STR 		= pOusters->getSTR(ATTR_CURRENT);
	DEX 		= pOusters->getDEX(ATTR_CURRENT);
	INTE        = pOusters->getINT(ATTR_CURRENT);
	TargetType  = TARGET_MAX;
	Range       = pOusters->getAdvancementClassLevel();
	
	Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
	if (pWeapon != NULL) IClass = pWeapon->getItemClass();
	else IClass = Item::ITEM_CLASS_MAX;

	PartySize = 1;
	DomainLevel = 0;
}

SkillInput::SkillInput(Monster* pMonster)
{
	Assert(pMonster != NULL);

	SkillLevel  = 0;
	STR         = pMonster->getSTR();
	DEX         = pMonster->getDEX();
	INTE        = pMonster->getINT();
	TargetType  = TARGET_MAX;
	Range       = 0;
	IClass      = Item::ITEM_CLASS_MAX;
	PartySize   = 0;
	DomainLevel = 0;
}

//////////////////////////////////////////////////////////////////////////////
// method header for overriding
//////////////////////////////////////////////////////////////////////////////

void SkillHandler::execute(Slayer* pSlayer, ObjectID_t ObjectID) 
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1; 
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, ObjectID_t ObjectID) 
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire) 
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters, ObjectID_t ObjectID) 
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters) 
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Creature* pCreature, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID, SkillType_t SkillType) 
	throw(Error)
{
	if (pCreature != NULL && pCreature->isPC())
	{
		GCSkillFailed1 gcSkillFailed1;
		pCreature->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) 
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) 
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) 
	throw(Error)
{
	execute(pSlayer, TargetObjectID, X, Y, TargetX, TargetY, pSkillSlot);
}

// Create Holy Water 용 execute
void SkillHandler::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, ObjectID_t ItemObjectID, CoordInven_t X, CoordInven_t Y) 
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot)
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1; 
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, ObjectID_t TargetObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pSkillSlot) 
	throw(Error)
{
	execute(pVampire, TargetObjectID, X, Y, TargetX, TargetY, pSkillSlot);
}

void SkillHandler::execute(Ousters* pOusters, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, OustersSkillSlot* pOustersSkillSlot)
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1; 
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters, ObjectID_t TargetObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, OustersSkillSlot* pSkillSlot) 
	throw(Error)
{
	execute(pOusters, TargetObjectID, X, Y, TargetX, TargetY, pSkillSlot);
}

void SkillHandler::execute(Ousters* pOusters, ObjectID_t TargetObjectID, ZoneCoord_t TargetZoneX, ZoneCoord_t TargetZoneY, ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY)
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1; 
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(PlayerCreature* pPC, const string& TargetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	if (pPC != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pPC->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Slayer* pSlayer, const string& TargetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	if (pSlayer != NULL)
	{
		GCSkillFailed1 gcSkillFailed1;
		pSlayer->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Vampire* pVampire, const string& TargetName, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	if (pVampire != NULL)
	{
		GCSkillFailed1 gcSkillFailed1; 
		pVampire->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Ousters* pOusters, const string& TargetName, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	if (pOusters != NULL)
	{
		GCSkillFailed1 gcSkillFailed1; 
		pOusters->getPlayer()->sendPacket(&gcSkillFailed1);
	}
}

void SkillHandler::execute(Monster* pMonster) 
	throw(Error)
{
}

void SkillHandler::execute(Monster* pMonster, Creature* pEnemy) 
	throw(Error)
{
	__BEGIN_TRY

	if (pEnemy==NULL) return;

	execute(pMonster, pEnemy->getX(), pEnemy->getY());

	__END_CATCH
}

void SkillHandler::execute(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y) throw(Error)
{
}

// Mine & Bomb 관련 
const int ETypeCount = 5;	// 폭발의 종류
const int tilesByEType[ ETypeCount] = { 3, 3, 5, 5, 9 };	// 폭발 타입에 따른 피해 타일의 수.

// 방향 왼쪽 부터 밑으로 돈다.
const int xOffsetByEType0[DIR_MAX][ 3 ] = {
	{-1, 0, 1 },
	{-1, 0, 1 },
	{ 0, 0, 0 },
	{-1, 0, 1 },
	{-1, 0, 1 },
	{-1, 0, 1 },
	{ 0, 0, 0 },
	{-1, 0, 1 }
};

const int yOffsetByEType0[DIR_MAX][ 3 ] = {
	{ 0, 0, 0 },
	{ 1, 0,-1 },
	{-1, 0, 1 },
	{-1, 0, 1 },
	{ 0, 0, 0 },
	{ 1, 0,-1 },
	{ 0, 0, 0 },
	{-1, 0, 1 }
};

const int xOffsetByEType1[DIR_MAX][ 3 ] = {
	{ 0, 0, 0 },
	{-1, 0, 1 },
	{-1, 0, 1 },
	{-1, 0, 1 },
	{ 0, 0, 0 },
	{-1, 0, 1 },
	{-1, 0, 1 },
	{-1, 0, 1 }
};

const int yOffsetByEType1[DIR_MAX][ 3 ] = {
	{-1, 0, 1 },
	{-1, 0, 1 },
	{ 0, 0, 0 },
	{ 1, 0,-1 },
	{ 0, 0, 0 },
	{-1, 0, 1 },
	{ 0, 0, 0 },
	{ 1, 0,-1 }
};

const int xOffsetByEType2[DIR_MAX][ 5 ] = {
	{-1, -1, -1, 0, 1 },
	{-3, -2, -1,-1, 0 },
	{-1,  0,  1, 0, 0 },
	{ 3,  2,  1, 1, 0 },
	{ 2,  2,  2, 1, 0 },
	{ 3,  2,  1, 1, 0 },
	{-1,  0,  1, 0, 0 },
	{-3, -2, -1,-1, 0 }
};

const int yOffsetByEType2[DIR_MAX][ 5 ] = {
	{-1,  0,  1, 0, 0 },
	{ 1,  2,  3, 1, 0 },
	{ 2,  2,  2, 1, 0 },
	{ 1,  2,  3, 1, 0 },
	{-1,  0,  1, 0, 0 },
	{-1, -2, -3,-1, 0 },
	{ 2,  2,  2, 1, 0 },
	{-1, -2, -3,-1, 0 }
};

const int xOffsetByEType3[ 5 ] = { -1,  0, 0, 1, 0};
const int yOffsetByEType3[ 5 ] = {  0, -1, 1, 0, 0};

const int xOffsetByEType4[ 9 ] = { -1, 0, 1, -1, 0, 1, -1, 0, 1};
const int yOffsetByEType4[ 9 ] = { -1, -1, -1, 0, 0, 0, 1, 1, 1};

/*
// 폭발 종류에 따른 피해 타일의 위치
const int xOffsetByEType0[ 1 ] = { 0};
const int yOffsetByEType0[ 1 ] = { 0};

const int xOffsetByEType1[ 5 ] = { 0, -1, 0, 1, 0};
const int yOffsetByEType1[ 5 ] = { -1, 0, 0, 0, 1};

const int xOffsetByEType2[ 5 ] = { -1, 1, 0, -1, 1};
const int yOffsetByEType2[ 5 ] = { -1, -1, 0, 1, 1};

const int xOffsetByEType3[ 9 ] = { -1, 0, 1, -1, 0, 1, -1, 0, 1};
const int yOffsetByEType3[ 9 ] = { -1, -1, -1, 0, 0, 0, 1, 1, 1};

const int xOffsetByEType4[DIR_MAX][ 9 ] = { 
	{  0, -1,  0, -2, -1,  0, -1,  0,  0},
	{ -2, -1, -1,  0, -1,  0,  1, -2,  2},
	{ -2, -1,  0,  1,  2, -1,  0,  1,  0},
	{  2,  1,  0,  1, -1,  0,  1, -2,  2},
	{  0,  0,  1,  0,  1,  2,  0,  1,  0},
	{ -2,  2, -1,  0,  1,  0,  1,  1,  2},
	{  0, -1,  0,  1, -2, -1,  0,  1,  2},
	{ -2,  2, -1,  0,  1, -1,  0, -1, -2}
};
		
const int yOffsetByEType4[DIR_MAX][ 9 ] = { 
	{ -2, -1, -1,  0, 0, 0, 1, 1, 2},
	{ -2, -1,  0,  0, 1, 1, 1, 2, 2},
	{  0,  0,  0,  0, 0, 1, 1, 1, 2},
	{ -2, -1,  0,  0, 1, 1, 1, 2, 2},
	{ -2, -1, -1,  0, 0, 0, 1, 1, 2},
	{ -2, -2, -1, -1, -1, 0, 0, 1, 2},
	{ -2, -1, -1, -1, 0, 0, 0, 0, 0},
	{ -2, -2, -1, -1, -1, 0, 0, 1, 2}
};

const int xOffsetByEType5[DIR_MAX][ 5 ] = {
	{ 0, 0, 0, 0, 0},
	{ -2, -1, 0, 1, 2},
	{ -2, -1, 0, 1, 2},
	{ 2, 1, 0, -1, -2},
	{ 0, 0, 0, 0, 0},
	{ -2, -1, 0, 1, 2},
	{ -2, -1, 0, 1, 2},
	{ 2, 1, 0, -1, -2}
};
const int yOffsetByEType5[DIR_MAX][ 5 ] = {
	{ -2, -1, 0, 1, 2},
	{ -2, -1, 0, 1, 2},
	{ 0, 0, 0, 0, 0},
	{ -2, -1, 0, 1, 2},
	{ -2, -1, 0, 1, 2},
	{ -2, -1, 0, 1, 2},
	{ 0, 0, 0, 0, 0},
	{ -2, -1, 0, 1, 2}
};
*/

void getExplosionTypeXYOffset(int explodeType, int dir, const int*& xOffset, const int*& yOffset, int& tiles)
{
	switch(explodeType)
	{
		case 0:
			xOffset = xOffsetByEType0[dir];
			yOffset = yOffsetByEType0[dir];
			break;
			
		case 1:
			xOffset = xOffsetByEType1[dir];
			yOffset = yOffsetByEType1[dir];
			break;
			
		case 2:
			xOffset = xOffsetByEType2[dir];
			yOffset = yOffsetByEType2[dir];
			break;
			
		case 3:
			xOffset = xOffsetByEType3;
			yOffset = yOffsetByEType3;
			break;
			
		case 4:
			xOffset = xOffsetByEType4;
			yOffset = yOffsetByEType4;
			break;
		default:
			Assert(false);
	}
	
	tiles = tilesByEType[ explodeType];
}

