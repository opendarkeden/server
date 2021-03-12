//////////////////////////////////////////////////////////////////////////////
// Filename    : SatelliteBomb.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SatelliteBomb.h"
#include "EffectSatelliteBombAim.h"
#include "EffectSatelliteBombPoint.h"

#include "ItemUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 人类 卫星轰击技能 180级
//////////////////////////////////////////////////////////////////////////////
void SatelliteBomb::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	// 数据安全验证
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		// 获取当前地图,并进行安全验证.根据目标ID取得对象
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		

		// 检测目标攻击可能性
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC()
			)
		{
			// 通知客户端使用技能失败
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}
		// 使用技能
		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	//错误处理
	catch (Throwable & t)  
	{
		// 通知客户端使用技能失败
		executeSkillFailException(pSlayer, getSkillType());			
    }
    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 技能运行函数 pSlayer->使用技能对象  X,Y->坐标 pSkillSlot->技能信息  CEffectID->效果ID
//////////////////////////////////////////////////////////////////////////////
void SatelliteBomb::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	try 
	{
		// 根据Slayer 取得Player对象指针
		Player* pPlayer = pSlayer->getPlayer();
		// 根据Slayer 取得当前地图指针
		Zone* pZone = pSlayer->getZone();
		// 错误处理
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 检测是否有装备武器
		Item* pItem = pSlayer->getWearItem( Slayer::WEAR_RIGHTHAND );
		if ( pItem == NULL || isArmsWeapon( pItem ) == false )
		{
			// 通知客户端使用技能失败
			executeSkillFailException( pSlayer, getSkillType() );
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;
		// 获取当前使用技能类型
		SkillType_t SkillType  = pSkillSlot->getSkillType();
		// 获取数据库当前使用技能信息
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		
		// RequiredMP  获取技能需要消耗的MP值.
		// bManaCheck  检测当前使用对象是否有足够的MP值消耗.
		// bTimeCheck  检测当前技能使用时间间隔是否超出.
		// bRangeCheck 检测技能使用距离.
		// bEffected   检测当前技能是否在使用中.
		// bTileCheck  检测当前地图使用可能性
		int  RequiredMP  = pSkillInfo->getConsumeMP();										
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);								
		bool bTimeCheck  = verifyRunTime(pSkillSlot);										
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());           
		bool bEffected	 = pSlayer->isFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM ); 

		bool bTileCheck = false;
		VSRect rect( 0, 0, pZone->getWidth()-1, pZone->getHeight()-1 );
		if ( rect.ptInRect( X, Y ) )
		{
			Tile& tile = pZone->getTile(X,Y);
			if ( tile.canAddEffect() ) bTileCheck = true;
		}
		bool bUseSkill	 = false;
		/*
		// 取出当前使用技能角色所使用的武器
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		//没有武器不能使用技能
		if (pWeapon != NULL) 
		{
			Silver_t silverDamage= pWeapon->getSilver();
			if (silverDamage >50)
			{
				silverDamage-=50;
				pWeapon->setSilver(silverDamage);
				bUseSkill=true;
			}
		}
		*/
		bUseSkill =true;
		// 如果全部检测通过,则执行技能函数.
		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected && bTileCheck && bUseSkill )
		{
			// 设置使用角色MP减少
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// 创建技能输入输出变量,并计算技能伤害等信息.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Tile& tile = pZone->getTile( X, Y );

			// 如果EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT技能效果在使用中,移除效果.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 创建使用角色效果
			EffectSatelliteBombAim* pEffect = new EffectSatelliteBombAim(pSlayer, pZone, X, Y);
			// 设置效果伤害
			pEffect->setDamage(output.Damage);
			// 设置效果使用时间
			pEffect->setDeadline(output.Duration);
			
			pSlayer->addEffect( pEffect );
			pSlayer->setFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );

			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(output.Range);
		
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(output.Range);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(output.Range);

			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// SatelliteBombAim 捞棋飘甫 宏肺靛某胶泼 茄促.
			GCAddEffect gcAddAimEffect;
			gcAddAimEffect.setObjectID( pSlayer->getObjectID() );
			gcAddAimEffect.setEffectID( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );
			gcAddAimEffect.setDuration( output.Duration );
			pZone->broadcastPacket( myX, myY, &gcAddAimEffect );

			///////////////////////////////////////////////////////////////////
			// SatelliteBombPoint 捞棋飘甫 父甸绢辑 嘿捞绊 宏肺靛某胶泼 茄促.
			///////////////////////////////////////////////////////////////////
			EffectSatelliteBombPoint* pPointEffect = new EffectSatelliteBombPoint( pZone, X, Y );
			pPointEffect->setDeadline( output.Duration );

			ObjectRegistry & objectRegister = pZone->getObjectRegistry();
			objectRegister.registerObject( pPointEffect );

			pZone->addEffect( pPointEffect );
			tile.addEffect( pPointEffect );

			GCAddEffectToTile gcAddEffectToTile;
			gcAddEffectToTile.setObjectID( pPointEffect->getObjectID() );
			gcAddEffectToTile.setEffectID( pPointEffect->getEffectClass() );
			gcAddEffectToTile.setXY( X, Y );
			gcAddEffectToTile.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffectToTile );

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	__END_CATCH
}

void SatelliteBomb::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) 
{
	__BEGIN_TRY

	try 
	{
		cout << pMonster->getName() << " use gunshotguiadance" << endl;
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = getSkillType();
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bTileCheck)
		{
			Tile& tile = pZone->getTile(X, Y);
		
			ZoneCoord_t myX = pMonster->getX();
			ZoneCoord_t myY = pMonster->getY();

			// 鞍篮 捞棋飘啊 捞固 粮犁茄促搁 昏力茄促.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 单固瘤客 瘤加 矫埃阑 拌魂茄促.
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);
		
			// 捞棋飘 坷宏璃飘甫 积己茄促.
			EffectSatelliteBombAim* pEffect = new EffectSatelliteBombAim(pMonster, pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamage(output.Damage);

			pMonster->setFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );
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

			// SatelliteBombAim 捞棋飘甫 宏肺靛某胶泼 茄促.
			GCAddEffect gcAddAimEffect;
			gcAddAimEffect.setObjectID( pMonster->getObjectID() );
			gcAddAimEffect.setEffectID( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );
			gcAddAimEffect.setDuration( output.Duration );
			pZone->broadcastPacket( myX, myY, &gcAddAimEffect );

			EffectSatelliteBombPoint* pPointEffect = new EffectSatelliteBombPoint( pZone, X, Y );
			pPointEffect->setDeadline( output.Duration );

			ObjectRegistry & objectRegister = pZone->getObjectRegistry();
			objectRegister.registerObject( pPointEffect );

			pZone->addEffect( pPointEffect );
			tile.addEffect( pPointEffect );

			GCAddEffectToTile gcAddEffectToTile;
			gcAddEffectToTile.setObjectID( pPointEffect->getObjectID() );
			gcAddEffectToTile.setEffectID( pPointEffect->getEffectClass() );
			gcAddEffectToTile.setXY( X, Y );
			gcAddEffectToTile.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffectToTile );
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

	__END_CATCH
}

SatelliteBomb g_SatelliteBomb;
