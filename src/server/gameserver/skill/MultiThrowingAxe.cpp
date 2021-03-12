//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiThrowingAxe.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MultiThrowingAxe.h"
#include "RankBonus.h"
#include "EffectMeteorStrike.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void MultiThrowingAxe::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

	cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin(monster) " << endl;

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = SKILL_MULTI_THROWING_AXE;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pMonster, pSkillInfo);

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		Dir_t dir = getDirection( pMonster->getX(), pMonster->getY(), X, Y );
		Dir_t dir2 = (dir+7)%8;		// left
		Dir_t dir3 = (dir+1)%8;		// right

		ZoneCoord_t tX[3],tY[3];
		
		// 원래 목표(3개중 가운데)
		X = tX[0] = pMonster->getX() + dirMoveMask[dir].x * 7;
		Y = tY[0] = pMonster->getY() + dirMoveMask[dir].y * 7;
		
		// 원래 목표의 왼쪽
		tX[1] = pMonster->getX() + dirMoveMask[dir2].x * 7;
		tY[1] = pMonster->getY() + dirMoveMask[dir2].y * 7;
	
		// 원래 목표의 오른쪽
		tX[2] = pMonster->getX() + dirMoveMask[dir3].x * 7;
		tY[2] = pMonster->getY() + dirMoveMask[dir3].y * 7;
			
		
		if (bRangeCheck && bHitRoll && bTileCheck)
		{
			Range_t Range = 1;	// 항상 1이다.
		
			// 데미지와 지속 시간을 계산한다.
			SkillInput input(pMonster);
			input.SkillLevel = pMonster->getLevel();
			SkillOutput output;
			computeOutput(input, output);
			
			for(int i=0; i < 3; i++)
			{
				if ( !isValidZoneCoord(pZone, tX[i], tY[i]) ) continue;
				Tile&   tile  = pZone->getTile(tX[i], tY[i]);
				
				// 이펙트 오브젝트를 생성한다.
				EffectMeteorStrike* pEffect = new EffectMeteorStrike(pZone, tX[i], tY[i]);
				pEffect->setNextTime(output.Duration);
				pEffect->setUserObjectID( pMonster->getObjectID() );
				pEffect->setBroadcastingEffect( false );
				//pEffect->setNextTime(0);
				//pEffect->setTick(output.Tick);
				pEffect->setDamage(output.Damage);
				pEffect->setSplashRatio(1, 75);
				pEffect->setSplashRatio(2, 50);
				//pEffect->setLevel(pSkillInfo->getLevel()/2);

				// 타일에 붙은 이펙트는 OID를 받아야 한다.
				ObjectRegistry & objectregister = pZone->getObjectRegistry();
				objectregister.registerObject(pEffect);
			
				// 존 및 타일에다가 이펙트를 추가한다.
				pZone->addEffect(pEffect);	
				tile.addEffect(pEffect);
			}
			ZoneCoord_t myX = pMonster->getX();
			ZoneCoord_t myY = pMonster->getY();

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);
		
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);

			list<Creature*> cList;
			cList.push_back(pMonster);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(monster) " << endl;

	__END_CATCH
}

MultiThrowingAxe g_MultiThrowingAxe;
