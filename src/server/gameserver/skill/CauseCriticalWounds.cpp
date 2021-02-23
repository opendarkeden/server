//////////////////////////////////////////////////////////////////////////////
// Filename    : CauseCriticalWounds.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CauseCriticalWounds.h"
#include "EffectCauseCriticalWounds.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "SimpleMissileSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void CauseCriticalWounds::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert( pSlayer != NULL );
	Assert( pSkillSlot != NULL );

	try {
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert( pPlayer != NULL );
		Assert( pZone != NULL );

		Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

		// NPC 를 공격할 수 없다
		// 면역이거나.. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.5
		if ( pTargetCreature==NULL
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_PARALYZE)
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC() )
		{
			executeSkillFailException( pSlayer, getSkillType() );

			return;
		}

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SkillType );
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		Tile& rTile = pZone->getTile( pTargetCreature->getX(), pTargetCreature->getY() );

		// 스킬 사용이 가능한지 체크한다
		int	RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana( pSlayer, RequiredMP );
		bool bTimeCheck = verifyRunTime( pSkillSlot );
		bool bRangeCheck = verifyDistance( pSlayer, pTargetCreature, pSkillInfo->getRange() );
		bool bHitRoll = HitRoll::isSuccessMagic( pSlayer, pSkillInfo, pSkillSlot );
		bool bCanHit = canHit( pSlayer, pTargetCreature, SkillType );
		bool bEffected = pTargetCreature->isFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS ) || rTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION)!=NULL;
		bool bPK = verifyPK( pSlayer, pTargetCreature );

		if ( bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && !bEffected && bPK )
		{
			// packet
			GCSkillToObjectOK1 _GCSkillToObjectOK1;
			GCSkillToObjectOK2 _GCSkillToObjectOK2;
			GCSkillToObjectOK3 _GCSkillToObjectOK3;
			GCSkillToObjectOK4 _GCSkillToObjectOK4;
			GCSkillToObjectOK5 _GCSkillToObjectOK5;
			GCSkillToObjectOK6 _GCSkillToObjectOK6;

			ZoneCoord_t prayerX = pSlayer->getX();
			ZoneCoord_t prayerY = pSlayer->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			// 스킬의 damage, delay, duration을 계산
			SkillInput input( pSlayer, pSkillSlot );
			SkillOutput output;
			computeOutput( input, output );

			// Soul Smashing 이 있다면 데미지 10% 증가
			if ( pSlayer->hasRankBonus( RankBonus::RANK_BONUS_SOUL_SMASHING ) )
			{
				RankBonus* pRankBonus = pSlayer->getRankBonus( RankBonus::RANK_BONUS_SOUL_SMASHING );
				Assert( pRankBonus != NULL );

				output.Damage += pRankBonus->getPoint();
			}

			// 마나를 줄인다
			decreaseMana( pSlayer, RequiredMP, _GCSkillToObjectOK1 );

			// 데미지를 가하고, 내구도를 떨어뜨린다. 공격대상이 슬레이어가 아니므로 alignment, PK 체크할 필요가 없다
			setDamage( pTargetCreature, output.Damage, pSlayer, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1 );
			computeAlignmentChange( pTargetCreature, output.Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1 );
			decreaseDurability( pSlayer, pTargetCreature, NULL, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2 );

			// 타겟이 슬레이어가 아닌 경우에만
			// 경험치를 올린다
			// Effect를 붙인다
			// Effect를 브로드 캐스팅 한다
			if ( !pTargetCreature->isSlayer() )
			{
				SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel( pSlayer->getSkillDomainLevel( DomainType ) );
				Exp_t ExpUp = 10 * ( Grade + 1 );
				shareAttrExp( pSlayer, ExpUp, 1, 1, 8, _GCSkillToObjectOK1 );
				increaseDomainExp( pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel() );
				increaseSkillExp( pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1 );
				increaseAlignment( pSlayer, pTargetCreature, _GCSkillToObjectOK1 );

				// Effect를 생성해서 붙인다
				EffectCauseCriticalWounds* pEffectCauseCriticalWounds = new EffectCauseCriticalWounds( pTargetCreature );
				pEffectCauseCriticalWounds->setDeadline( output.Duration );
				pTargetCreature->addEffect( pEffectCauseCriticalWounds );
				pTargetCreature->setFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );

				// Effect 를 브로드 캐스팅 한다
				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
				gcAddEffect.setEffectID( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );
				gcAddEffect.setDuration( output.Duration );
				pZone->broadcastPacket( targetX, targetY, &gcAddEffect );
			}
			else // 슬레이어 일 경우
			{
				// 슬레이어 일 경우 Duration을 0으로 세팅한다. 마비는 하지 않고 데미지만 적용한다.
				output.Duration = 0;
			}

			bool bCanSeePrayer = canSee( pTargetCreature, pSlayer );

			// 스킬을 사용한 사람에게
			_GCSkillToObjectOK1.setSkillType( SkillType );
			_GCSkillToObjectOK1.setCEffectID( CEffectID );
			_GCSkillToObjectOK1.setTargetObjectID( TargetObjectID );
			_GCSkillToObjectOK1.setDuration( output.Duration );

			// 스킬의 대상자에게
			_GCSkillToObjectOK2.setObjectID( pSlayer->getObjectID() );
			_GCSkillToObjectOK2.setSkillType( SkillType );
			_GCSkillToObjectOK2.setDuration( output.Duration );

			// 스킬을 사용한 사람만 볼 수 있는 사람에게
			_GCSkillToObjectOK3.setObjectID( pSlayer->getObjectID() );
			_GCSkillToObjectOK3.setSkillType( SkillType );
			_GCSkillToObjectOK3.setTargetXY( targetX, targetY );

			// 스킬의 대상자만 불 수 있는 사람에게
			_GCSkillToObjectOK4.setSkillType( SkillType );
			_GCSkillToObjectOK4.setTargetObjectID( TargetObjectID );

			// 스킬 사용자와 대상자 모두 볼 수 있는 사람에게
			_GCSkillToObjectOK5.setObjectID( pSlayer->getObjectID() );
			_GCSkillToObjectOK5.setTargetObjectID( TargetObjectID );
			_GCSkillToObjectOK5.setSkillType( SkillType );
			_GCSkillToObjectOK5.setDuration( output.Duration );

			// 스킬 대상자가 스킬 사용자를 볼 수 없을 때
			_GCSkillToObjectOK6.setXY( prayerX, prayerY );
			_GCSkillToObjectOK6.setSkillType( SkillType );
			_GCSkillToObjectOK6.setDuration( output.Duration );

			pPlayer->sendPacket( &_GCSkillToObjectOK1 );

			if ( pTargetCreature->isPC() )
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert( pTargetPlayer != NULL );

				if ( bCanSeePrayer )
					pTargetPlayer->sendPacket( &_GCSkillToObjectOK2 );
				else
					pTargetPlayer->sendPacket( &_GCSkillToObjectOK6 );
			}
			else
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				Assert( pTargetMonster != NULL );

				pTargetMonster->addEnemy( pSlayer );
			}

			list<Creature*> cList;
			cList.push_back( pSlayer );
			cList.push_back( pTargetCreature );

			cList = pZone->broadcastSkillPacket( prayerX, prayerY, targetX, targetY, &_GCSkillToObjectOK5, cList );

			pZone->broadcastPacket( prayerX, prayerY, &_GCSkillToObjectOK3, cList );
			pZone->broadcastPacket( targetX, targetY, &_GCSkillToObjectOK4, cList );

			pSkillSlot->setRunTime( output.Delay );
		}
		else
		{
			executeSkillFailNormal( pSlayer, getSkillType(), pTargetCreature );
		}
	}
	catch ( Throwable& t )
	{
		executeSkillFailException( pSlayer, getSkillType() );
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

CauseCriticalWounds g_CauseCriticalWounds;

