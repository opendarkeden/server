//////////////////////////////////////////////////////////////////////////////
// Filename    : ContinualLight.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ContinualLight.h"
#include "EffectDarkness.h"
#include "EffectGrayDarkness.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCDeleteEffectFromTile.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void ContinualLight::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayertile)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

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
		
		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		bool bTileCheck = false;
		bool bSuccessCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& rTile = pZone->getTile(X, Y);
			Effect* pTestEffect = rTile.getEffect(Effect::EFFECT_CLASS_DARKNESS);
			if ( pTestEffect == NULL ) pTestEffect = rTile.getEffect( Effect::EFFECT_CLASS_GRAY_DARKNESS );

			if (pTestEffect != NULL) {
				bTileCheck = true;
				bSuccessCheck = true;
			}
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bTileCheck && bSuccessCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));

			int oX = 0, oY = 0;

			list<Creature*> cList; // 당하는 분들 list
			for(oY = -output.Range; oY <= output.Range; oY++)
			{
				for(oX = -output.Range; oX <= output.Range; oX++)
				{
					int tileX = X+oX;
					int tileY = Y+oY;

					if (rect.ptInRect(tileX, tileY))
					{
						Tile& tile = pZone->getTile(tileX, tileY);
						EffectDarkness* pEffect = (EffectDarkness*)(tile.getEffect(Effect::EFFECT_CLASS_DARKNESS));
						bool success=false;

						// 이 타일에 다크니스가 존재한다면...
						if (pEffect != NULL)
						{
							bool Remove = false;

							// 성공할 확률
							// min(0) - max(150) 에서
							// min(25) - max(75) 로 조정  2002.7.9 장홍창 
							int ratio =  min( max(25, SkillLevel - pEffect->getLevel()/3), 75);

							if (rand()%100 < ratio) Remove = true;

							if (Remove)
							{
								ObjectID_t effectObjectID = pEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_DARKNESS);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);

								success = true;
							}
						}

						EffectGrayDarkness* pGrayEffect = (EffectGrayDarkness*)(tile.getEffect(Effect::EFFECT_CLASS_GRAY_DARKNESS));

						// 이 타일에 다크니스가 존재한다면...
						if (pGrayEffect != NULL)
						{
							bool Remove = false;

							// 성공할 확률
							// min(0) - max(150) 에서
							// min(25) - max(75) 로 조정  2002.7.9 장홍창 
							int ratio =  min( max(20, SkillLevel - (int)(pGrayEffect->getLevel()/2.8)), 70);

							if (rand()%100 < ratio) Remove = true;

							if (Remove)
							{
								ObjectID_t effectObjectID = pGrayEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);

								// 타일에 걸어다니는 크리쳐가 존재한다면 포인터를 받아온다.
//								Creature* pTargetCreature = NULL;
//								if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
//									pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
//
//								if (pTargetCreature != NULL && ( pTargetCreature->isSlayer() || pTargetCreature->isOusters() ))
//									cList.push_back(pTargetCreature);

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_GRAY_DARKNESS);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);

								success = true;
							}
						}

						if ( success )
						{
							// 타일에 걸어다니는 크리쳐가 존재한다면 포인터를 받아온다.
							Creature* pTargetCreature = NULL;
							if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
								pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

							if (pTargetCreature != NULL && ( pTargetCreature->isSlayer() || pTargetCreature->isOusters() ))
								cList.push_back(pTargetCreature);
						}
					}
				}
			}
			
			// 경험치를 올려준다.
			Exp_t ExpUp = 10*(Grade+1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToTileOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);

			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(0);

			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(0);
			_GCSkillToTileOK2.setRange(output.Range);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(output.Range);
			_GCSkillToTileOK4.setDuration(0);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(output.Range);
			_GCSkillToTileOK5.setDuration(0);
			
			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				_GCSkillToTileOK4.addCListElement((*itr)->getObjectID());
				_GCSkillToTileOK5.addCListElement((*itr)->getObjectID());

				(*itr)->getPlayer()->sendPacket(&_GCSkillToTileOK2);
			}

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayertile)" << endl;

	__END_CATCH
}

ContinualLight g_ContinualLight;
