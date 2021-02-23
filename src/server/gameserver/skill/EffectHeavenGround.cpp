//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectHeavenGround.h"
#include "Zone.h"
#include "Tile.h"

#include "EffectTrapTriggered.h"
#include "Monster.h"

#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCAddEffect.h"


#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHeavenGround::EffectHeavenGround( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y )
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;
	m_UserObjectID = 0;
	m_bSlayer = false;
	m_Damage = 0;
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHeavenGround::affect()
	throw(Error)
{
	__BEGIN_TRY

		Assert(m_pZone != NULL);
	//cout << "UserObejctID:" << (int)m_UserObjectID << endl;
	// 获取使用技能的人物
	Creature * pCastCreature = m_pZone->getCreature( m_UserObjectID );

	if ( pCastCreature == NULL  )
	{
		setNextTime(m_Tick);

		return;
	}
	//Slayer* pSlayer = dynamic_cast<Slayer*>(pSlayer);

	// 取出地图
	Tile& tile = m_pZone->getTile(m_X, m_Y);

	// 获取地图物品链表
	const slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::const_iterator itr = oList.begin();
	for (; itr != oList.end(); itr++) 
	{
		Assert(*itr != NULL);

		Object* pObject = *itr;
		Assert(pObject != NULL);

		if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature != NULL);

			// 检测当前对象是否可攻击
			if ( !canAttack( pCastCreature, pCreature )
				|| pCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_ACID)
				|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
				)
			{
				continue;
			}

			// 检测地图等级
			if( !checkZoneLevelToHitTarget( pCreature ) ) continue;
			// 创建伤害
			int AcidDamage = computeMagicDamage(pCreature, m_Damage, SKILL_HEAVEN_GROUND, m_bSlayer, pCastCreature);
			// 空中的不攻击
			if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
			{
				GCModifyInformation gcAttackerMI;
				GCModifyInformation gcDefenderMI;
				// 如果是人类,则不会造成伤害
				if (pCreature->isSlayer()) 
				{
					continue;
					//setNextTime(m_Tick);
					//return;
				} 
				else if (pCreature->isVampire())
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

					::setDamage( pVampire, AcidDamage, pCastCreature, SKILL_HEAVEN_GROUND, &gcDefenderMI, &gcAttackerMI, false );

					Player* pPlayer = pVampire->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcDefenderMI);
				}
				else if (pCreature->isOusters())
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

					::setDamage( pOusters, AcidDamage, pCastCreature, SKILL_HEAVEN_GROUND, &gcDefenderMI, &gcAttackerMI, false );

					Player* pPlayer = pOusters->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcDefenderMI);
				}
				else if (pCreature->isMonster())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, AcidDamage, pCastCreature, SKILL_HEAVEN_GROUND, NULL, &gcAttackerMI, false );
				}

				bool modifiedAttacker = false;

				// 磷菌栏搁 版氰摹霖促. 澜.....
// 				if ( pCastCreature != NULL )
// 				{
// 					if (pCreature->isDead() && pCastCreature->isVampire())
// 					{
// 						//computeAlignmentChange(pCreature, AcidDamage, pSlayer, &gcDefenderMI, &gcAttackerMI);
// 						//decreaseDurability(pSlayer, pCreature, NULL, &gcAttackerMI, &gcDefenderMI);
// 
// 						// 鸥百捞 浇饭捞绢啊 酒囱 版快俊父 版氰摹甫 棵妨霖促.
// 						if (!pCreature->isSlayer())
// 						{
// // 							//shareAttrExp(pSlayer, AcidDamage , 1, 1, 8, _GCSkillToObjectOK1);
// // 							increaseDomainExp(pSlayer, SKILL_HEAVEN_GROUND, pSkillInfo->getPoint(), gcAttackerMI, pTargetCreature->getLevel());
// // 							increaseSkillExp(pSlayer, SKILL_HEAVEN_GROUND,  pSkillSlot, pSkillInfo, gcAttackerMI);
// // 							increaseAlignment(pSlayer, pCreature, gcAttackerMI);
// 						}
// 						modifiedAttacker = true;
// 					}
// 				}

				// 己氢 拌魂窍扁
				if ( pCastCreature != NULL
					&& pCastCreature->isPC()
					&& pCreature->isPC()
						)
					{
						computeAlignmentChange( pCreature, AcidDamage, pCastCreature, &gcDefenderMI, &gcAttackerMI );
						modifiedAttacker = true;
					}

					if (modifiedAttacker) pCastCreature->getPlayer()->sendPacket( &gcAttackerMI );
			}
		}
	}

	setNextTime(m_Tick);

	//cout << "EffectAcidSwamp" << "affect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHeavenGround::affect(Zone* pZone, ZoneCoord_t Cx, ZoneCoord_t Cy)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHeavenGround::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile( m_X, m_Y );
	tile.deleteEffect( m_ObjectID );

	GCDeleteEffectFromTile gcDeleteEffect;
	gcDeleteEffect.setXY( m_X, m_Y );
	gcDeleteEffect.setObjectID( getObjectID() );
	gcDeleteEffect.setEffectID( getSendEffectClass() );

	m_pZone->broadcastPacket( m_X, m_Y, &gcDeleteEffect );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHeavenGround::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHeavenGround("
		<< ")";
	return msg.toString();

	__END_CATCH
}

