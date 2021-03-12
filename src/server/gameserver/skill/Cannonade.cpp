//////////////////////////////////////////////////////////////////////////////
// Filename    : Cannonade.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Cannonade.h"
#include "EffectCannonade.h"

#include "ItemUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"

void Cannonade::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) 
{
	__BEGIN_TRY

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = getSkillType();
		ZoneCoord_t myX = pMonster->getX();
		ZoneCoord_t myY = pMonster->getY();

		// 데미지와 지속 시간을 계산한다.
		SkillInput input(pMonster);
		SkillOutput output;
		computeOutput(input, output);
	
		// 이펙트 오브젝트를 생성한다.
		EffectCannonade* pEffect = new EffectCannonade(pMonster, pZone, X, Y);
		pEffect->setDeadline(output.Duration);
		pEffect->setDamage(output.Damage);
		pMonster->addEffect( pEffect );

		_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
		_GCSkillToTileOK3.setSkillType(SkillType);
		_GCSkillToTileOK3.setX(X);
		_GCSkillToTileOK3.setY(Y);
		
		_GCSkillToTileOK4.setSkillType(SkillType);
		_GCSkillToTileOK4.setX(X);
		_GCSkillToTileOK4.setY(Y);
		_GCSkillToTileOK4.setDuration(output.Duration);
		_GCSkillToTileOK4.setRange(1);
	
		_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
		_GCSkillToTileOK5.setSkillType(SkillType);
		_GCSkillToTileOK5.setX(X);
		_GCSkillToTileOK5.setY(Y);
		_GCSkillToTileOK5.setDuration(output.Duration);
		_GCSkillToTileOK5.setRange(1);

		list<Creature*> cList;
		cList.push_back(pMonster);

		cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

		pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
		pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	__END_CATCH
}

Cannonade g_Cannonade;
