////////////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : BombCrashWalk.cpp
////////////////////////////////////////////////////////////////////////////////

#include "BombCrashWalk.h"
#include "EffectBombCrashWalk.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// ½½·¹ÀÌ¾î ¿ÀºêÁ§Æ® ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void BombCrashWalk::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Slayer Object Assertion
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuchÁ¦°Å. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
		    
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ½½·¹ÀÌ¾î Å¸ÀÏ ÇÚµé·¯
//  ½½·¹ÀÌ¾î°¡ Wide Lightning SkillÀ» Tile¿¡ »ç¿ëÇßÀ»¶§ »ç¿ëÇÏ´Â Handler
//////////////////////////////////////////////////////////////////////////////
void BombCrashWalk::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());
		
		// ÀÏ´Ü ±â¼úÀº ¼º°øÇÏ´Â °ÍÀ¸·Î ÇÏ°í µ¥¹ÌÁö¸¦ °è»êÇÒ¶§(EffectBombCrashWalk::affect())
		// Å©¸®ÃÄ º°·Î ´Ù½Å °è»êÇÏ´Â °É·Î ÇÑ´Ù.
		// 2003.1.8 by bezz
		//bool bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		bool bTileCheck = false;
		Tile& tile = pZone->getTile(X, Y);
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if(rect.ptInRect(X, Y))
		{
			if (tile.canAddEffect()) bTileCheck = true;
		}
// 		bool bUseSkill	 = false;
// 		// È¡³öµ±Ç°Ê¹ÓÃ¼¼ÄÜ½ÇÉ«ËùÊ¹ÓÃµÄÎäÆ÷
// 		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
// 		//Ã»ÓÐÎäÆ÷²»ÄÜÊ¹ÓÃ¼¼ÄÜ
// 		if (pWeapon != NULL) 
// 		{
// 			Silver_t silverDamage= pWeapon->getSilver();
// 			if (silverDamage >50)
// 			{
// 				silverDamage-=50;
// 				pWeapon->setSilver(silverDamage);
// 				bUseSkill=true;
// 			}
// 		}
		if (bManaCheck && bTimeCheck && bRangeCheck && bTileCheck )//&& bUseSkill)
		{
			//pZone->moveFastPC(pSlayer, pSlayer->getX(), pSlayer->getY(), X,Y,getSkillType());//pTargetCreature->getX(), pTargetCreature->getY(), getSkillType());
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 5;

			EffectBombCrashWalk* pEffect = new EffectBombCrashWalk( pZone, X, Y );
			pEffect->setUserObjectID( pSlayer->getObjectID() );
			pEffect->setDamage( output.Damage );
			pEffect->setSkillType( SkillType );
			pEffect->setStormTime( 0 );
			pEffect->setTick( output.Tick );
			pEffect->setNextTime( output.Duration );

			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);

			// ±â¼úÀ» »ç¿ëÇÑ »ç¶÷µé¿¡°Ô
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);
		
			// ±â¼úÀ» ¾´ »ç¶÷¸¸ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			//_GCSkillToTileOK3.setRange(Range);

			// ±â¼úÀ» ´çÇÑ »ç¶÷¸¸ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//±â¼úÀ» ¾´ »ç¶÷°ú ´çÇÑ »ç¶÷À» ¸ðµÎ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
			// ±â¼úÀ» »ç¿ëÇÑ »ç¶÷¿¡°Ô packet Àü´Þ
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			// ±â¼úÀ» ¾µ »ç¶÷°ú ´çÇÑ »ç¶÷À» ¸ðµÎ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasing
			// broadcastingÈÄ 5¹øOK¸¦ ¹ÞÀº »ç¶÷À» ±â·ÏÇÑ´Ù.
			// ¿©±â¿¡ ±â·ÏµÈ »ç¶÷Àº Â÷ÈÄ broadcasting¿¡¼­ Á¦¿ÜµÈ´Ù.
			list<Creature*> cList;
			cList.push_back( pSlayer );
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// ±â¼úÀ» ¾´ »ç¶÷À» º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// ±â¼úÀ» ´çÇÑ »ç¶÷À» º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

			// ±â¼ú delay setting
			pSkillSlot->setRunTime(output.Delay);

		}
		else
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}


BombCrashWalk g_BombCrashWalk;
