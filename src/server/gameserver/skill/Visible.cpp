//////////////////////////////////////////////////////////////////////
//
// Filename    : Visible.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#include "Visible.h"
#include "EffectInvisibility.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCRemoveEffect.h"
#include "ZoneUtil.h"

//////////////////////////////////////////////////////////////////////
//
// Visible::execute()
//
//////////////////////////////////////////////////////////////////////
void Visible::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		// Player를 받아온다.
		Player * pPlayer = pSlayer->getPlayer();

		// Zone을 받아온다.
		Zone * pZone = pSlayer->getZone();

		SkillType_t SkillType = pSkillSlot->getSkillType();

		SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// 기술의 레벨을 받아온다.
		//SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

		//SkillDomainType_t DomainType = pSkillInfo->getDomainType();

        VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());
		bool bHit       = false;

		// 기술성공률 검증.
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			GCSkillToTileOK1 _GCSkillToTileOK1;
			GCSkillToTileOK2 _GCSkillToTileOK2;
			GCSkillToTileOK3 _GCSkillToTileOK3;
			GCSkillToTileOK4 _GCSkillToTileOK4;
			GCSkillToTileOK5 _GCSkillToTileOK5;

			Coord_t myX = pSlayer->getX(), myY = pSlayer->getY();
	        Dir_t       dir           = calcDirection(myX, myY, X, Y);

			list<Creature*> cList;
			int oX, oY;
			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);
				Creature * pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING)) pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL)
				{
					if(pTargetCreature->isPC())
					{
						bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
						bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY);

						if( bHitRoll && bEffected ) {
							// 주위에 GCAddXXX를 보내고, effect manager에서 effect를 삭제하고, GCRemoveEffect를 보낸다.
							addVisibleCreature(pZone, pTargetCreature, true);

							_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
							_GCSkillToTileOK2.setSkillType(SkillType);
							_GCSkillToTileOK2.setX(X);
							_GCSkillToTileOK2.setY(Y);
							_GCSkillToTileOK2.setRange(dir);
							_GCSkillToTileOK2.setDuration(0);

							Player * pTargetPlayer = pTargetCreature->getPlayer();
							Assert(pTargetPlayer != NULL);
							pTargetPlayer->sendPacket(&_GCSkillToTileOK2);

							cList.push_back( pTargetCreature );

							bHit = true;
						}

					}
				} // if(pTargetCreature!= NULL)
			}

			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			// EXP UP!
			Exp_t Point = pSkillInfo->getPoint();

			if( bHit ) {
				shareAttrExp(pSlayer, Point, 1, 1, 8, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				
			}
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
	
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X , Y ,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// Visible::execute()
//
//////////////////////////////////////////////////////////////////////
void Visible::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		// Player를 받아온다.
		Player * pPlayer = pSlayer->getPlayer();

		// Zone을 받아온다.
		Zone * pZone = pSlayer->getZone();

		Creature * pTargetCreature = NULL;
		if (pSlayer->getObjectID() == TargetObjectID) pTargetCreature = pSlayer;
		else pTargetCreature = pZone->getCreature(TargetObjectID);

		SkillType_t SkillType = pSkillSlot->getSkillType();

		//Assert (pTargetCreature != NULL);
		if (pTargetCreature == NULL || pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, SkillType);
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// 기술의 레벨을 받아온다.
		//SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

		//SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHit       = false;


		// 기술성공률 검증.
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{

			Coord_t myX = pSlayer->getX(), myY = pSlayer->getY();
			Coord_t X = pTargetCreature->getX(), Y = pTargetCreature->getY();
	        Dir_t       dir           = calcDirection(myX, myY, X, Y);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			GCSkillToTileOK1 _GCSkillToTileOK1;
			GCSkillToTileOK2 _GCSkillToTileOK2;
			GCSkillToTileOK3 _GCSkillToTileOK3;
			GCSkillToTileOK4 _GCSkillToTileOK4;
			GCSkillToTileOK5 _GCSkillToTileOK5;

			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// by sigi. 2002.11.12
	        VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;
			int oX, oY;
			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				// by sigi. 2002.11.12
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING)) pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL)
				{
					if(pTargetCreature->isPC())
					{
						bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
						bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY);

						if( bHitRoll && bEffected ) {
							// 주위에 GCAddXXX를 보내고, effect manager에서 effect를 삭제하고, GCRemoveEffect를 보낸다.
							addVisibleCreature(pZone, pTargetCreature, true);

							_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
							_GCSkillToTileOK2.setSkillType(SkillType);
							_GCSkillToTileOK2.setX(X);
							_GCSkillToTileOK2.setY(Y);
							_GCSkillToTileOK2.setRange(dir);
							_GCSkillToTileOK2.setDuration(0);

							Player * pTargetPlayer = pTargetCreature->getPlayer();
							Assert(pTargetPlayer != NULL);
							pTargetPlayer->sendPacket(&_GCSkillToTileOK2);

							cList.push_back( pTargetCreature );

							bHit = true;
						}
					}
				} // if(pTargetCreature!= NULL)
			}

			SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			// EXP UP!
			Exp_t Point = pSkillInfo->getPoint();

			if( bHit ) {
				shareAttrExp(pSlayer, Point, 1, 1, 8, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				
			}


			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
	
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X , Y,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Visible g_Visible;
