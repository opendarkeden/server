//////////////////////////////////////////////////////////////////////////////
// Filename    : Monster.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Monster.h"
#include "MonsterInfo.h"
#include "MonsterManager.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "MonsterAI.h"
#include "AbilityBalance.h"
#include "Zone.h"
#include "MonsterNameManager.h"
#include "Effect.h"
#include "PrecedenceTable.h"
#include "MonsterFunctionObject.h"
#include "CreatureUtil.h"
#include "VariableManager.h"
#include "StringPool.h"
#include "SkillUtil.h"

#include "SkillHandler.h"

#include "GCAddMonster.h"
#include "GCMove.h"
#include "GCStatusCurrentHP.h"
#include "GCSay.h"

#include "skill/SkillHandlerManager.h"
#include "skill/EffectParalyze.h"
#include "skill/EffectDoom.h"
#include "skill/EffectTransformToWolf.h"
#include "skill/EffectTransformToBat.h"
#include "skill/EffectPeace.h"

#include "skill/SummonGroundElemental.h"

#include "Profile.h"
#include "SiegeManager.h"
#include "GDRLairManager.h"

#include "EffectRegenerate.h"

//#define __PROFILE_MONSTER__

#ifdef __PROFILE_MONSTER__
	#define __BEGIN_PROFILE_MONSTER(name)	beginProfileEx(name);
	#define __END_PROFILE_MONSTER(name)		endProfileEx(name);
#else
	#define __BEGIN_PROFILE_MONSTER(name)	((void)0);
	#define __END_PROFILE_MONSTER(name)		((void)0);
#endif

//#ifdef __XMAS_EVENT_CODE__
	
const string SantaSpeech[] = 
{
	"이 녀석들, 상당한 지식을 가진 놈들이었군!!!",
	"도망가자!!!",
	"피의 성서의 최후의 주인은 나다!!!",
	"멀뚱멀뚱~ O.o o.O",
	"메리 크리스마스!!",
	"크리스마스에 교회는 안 가고 뭐하는 거야!!!",
	"내가 죽을 것 같으냐!!!",
	"이런 완벽한 작전이 어떻게 들킨 거지???",
	"루돌프!!! 뿔을 뽑아서 공격해랏!!!",
	"이 녀석들 상당한 실력을 가진 놈들이었군!!!",
	"으~~~ 반드시 복수하겠다!!!",
	"아야~ 아파. 그만 때려.",
	"야 어디가..."
};

const string RudolfSpeech[] = 
{
	"워우~ 워우~", 
	"꺄훌~", 
	"끄에~", 
	"크르르~", 
	"징글벨~",
	"멍멍",
	"카오~",
	"깨갱~ 깨갱~",
	"깡총~ 깡총~",
	"멀뚱~ 멀뚱~ O.O",
};

const int SantaSpeechMax = 13;
const int RudolfSpeechMax = 10;

//#endif


//////////////////////////////////////////////////////////////////////////////
// 몬스터 적 인식 관련 함수
//////////////////////////////////////////////////////////////////////////////
bool Monster::isRealEnemy(Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pEnemy != NULL);

	if (m_pBrain == NULL ) return false;
	Zone* pZone = pEnemy->getZone();
	if (pEnemy->getObjectID() == m_OwnerObjectID ) return false;

	if (m_OwnerObjectID != 0 )
	{
		Creature* pOwner = m_pZone->getCreature(m_OwnerObjectID);
		if (pOwner != NULL && pOwner->getCreatureClass() == pEnemy->getCreatureClass() && canAttack(pOwner, pEnemy ) )
		{
//			cout << __PRETTY_FUNCTION__ << pEnemy->getName() << "is same class as owner" << pOwner->getName() << endl;
			return false;
		}

		if (GDRLairManager::Instance().isGDRLairZone(getZoneID()) && pEnemy->isPC() ) return false;
	}

	// 유령은 무시
	if (pEnemy->isFlag(Effect::EFFECT_CLASS_GHOST)
		// 죽은 놈은 적으로 인식하지 않는다.
		|| pEnemy->isFlag(Effect::EFFECT_CLASS_COMA)
		// 공중 공격을 못하면 박쥐 상태의 적은 적으로 인식하지 않는다.
		|| (!m_pBrain->canAttackAir() && pEnemy->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT) )
		// 스나이핑 모드의 적도 적으로 인식하지 않는다.
		|| !pEnemy->isFlag(Effect::EFFECT_CLASS_PARALYZE)	// 석화 걸리면 보인다고 하자
			&& !pZone->isMasterLair()						// 마스터 레어에서는 다 보인다. 2002.10.16.by sigi
			&& (!isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE) 
					&& pEnemy->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
			// 내가 디덱트 인비가 없는 경우에 인비저블 상태의 적도 적으로 인식하지 않는다.
				|| !isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) 
					&& pEnemy->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		// 아마게돈 걸린 놈음 때리면 안 된다. 어차피 안 맞는다. 2003. 1. 2. by Sequoia
		|| pEnemy->isFlag(Effect::EFFECT_CLASS_ARMAGEDDON)
		// 안전지대 내부를 못 보면 안전지대 내부에 있는 적도 적으로 인삭하지 않는다.
		|| (!m_pBrain->canSeeSafeZone() && (pZone->getZoneLevel(pEnemy->getX(), pEnemy->getY()) & SAFE_ZONE) )
		)
	{
		return false;
	}

	if (SiegeManager::Instance().isSiegeZone(pZone->getZoneID()) )
	{
		if (pEnemy->isFlag(Effect::EFFECT_CLASS_SIEGE_DEFENDER ) || pEnemy->isFlag(Effect::EFFECT_CLASS_SIEGE_REINFORCE ) )
			return false;
	}

	return true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Monster::Monster (MonsterType_t monsterType)
	throw() : m_MonsterType(monsterType)
{
	__BEGIN_TRY

	try {
	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(m_MonsterType);

	// 이동 모드에 대한 설정
	m_MoveMode = pMonsterInfo->getMoveMode();

	// STR, DEX, INT는 DB에서 로딩하여 초기화 시킨다.
	m_STR           = pMonsterInfo->getSTR();
	m_DEX           = pMonsterInfo->getDEX();
	m_INT           = pMonsterInfo->getINT();
	m_Exp           = pMonsterInfo->getExp();
	m_Moral         = pMonsterInfo->getMoral();
	m_Delay         = pMonsterInfo->getDelay();
	m_AttackDelay   = pMonsterInfo->getAttackDelay();
	m_Sight         = pMonsterInfo->getSight();
	m_MeleeRange    = pMonsterInfo->getMeleeRange();
	m_MissileRange  = pMonsterInfo->getMissileRange();
	m_AttackOrder	= pMonsterInfo->getAttackOrder();

	// by sigi. 2002.9.2
	m_bMaster       = pMonsterInfo->isMaster();
	m_bTreasure     = pMonsterInfo->hasTreasure();
	m_MonsterSummonStep	= 0;

	Creature::CreatureClass CClass = getCreatureClass();
	BASIC_ATTR              attr;

	attr.nSTR   = m_STR;
	attr.nDEX   = m_DEX;
	attr.nINT   = m_INT;
	attr.nLevel = pMonsterInfo->getLevel();

	m_HP[ATTR_MAX]         = computeHP(CClass, &attr, pMonsterInfo->getEnhanceHP());
	m_ToHit                = computeToHit(CClass, &attr, pMonsterInfo->getEnhanceToHit());
	m_Defense              = computeDefense(CClass, &attr, pMonsterInfo->getEnhanceDefense());
	m_Protection           = computeProtection(CClass, &attr, pMonsterInfo->getEnhanceProtection());
	m_Damage[ATTR_CURRENT] = computeMinDamage(CClass, &attr, pMonsterInfo->getEnhanceMinDamage());
	m_Damage[ATTR_MAX]     = computeMaxDamage(CClass, &attr, pMonsterInfo->getEnhanceMaxDamage());

	if (monsterType == 717 ) m_HP[ATTR_MAX] = 40000;
	if (monsterType == 723 ) m_HP[ATTR_MAX] = 60000;
	if (monsterType == 724 ) m_HP[ATTR_MAX] = 30000;
	if (monsterType == 725 ) m_HP[ATTR_MAX] = 30000;
	if (monsterType == 764 ) m_HP[ATTR_MAX] = 55000;
	if (monsterType == 765 ) m_HP[ATTR_MAX] = 60000;

	if (m_HP[ATTR_MAX] > 20000 )
	{
		if (monsterType >= 717 ){}
			//cout << pMonsterInfo->getHName() << "의 HP : " << m_HP[ATTR_MAX] << endl;
		else
			m_HP[ATTR_MAX] = 20000;
	}

	// InitAllStat이랑 여기꺼랑 어느게 참일까? - 2002.5.14 홍창
	if (monsterType == 358 || monsterType == 359 || monsterType == 360 || monsterType == 361)
		m_HP[ATTR_MAX] = m_HP[ATTR_MAX] * 10;

	if(monsterType>=371 && monsterType <= 375)
	{
		m_HP[ATTR_MAX] = 500;   // 5000으로 잡혀 있다. 테스트를 위해서 줄인 것
		m_Defense = 50;
		m_Protection = 20;
	}

	m_HP[ATTR_CURRENT]     = m_HP[ATTR_MAX];
	m_SilverDamage         = 0;

	// 다음 처리받을 턴을 지정한다.
	getCurrentTime(m_NextTurn);
	m_NextTurn.tv_sec += rand() % 3;
	m_NextTurn.tv_usec += rand() % 1000000;
	if (m_NextTurn.tv_usec >= 1000000) m_NextTurn.tv_sec ++;

	clearAccuDelay();

	if (monsterType != 722 )
	{
		// AI 클래스를 생성한다.
		uint aitype = pMonsterInfo->getAIType();
		if (aitype != 65535 )
			m_pBrain = new MonsterAI(this, aitype);
		else
		{
			//cout << pMonsterInfo->getHName() << "은 뇌가 없다." << endl;
			m_pBrain = NULL;
		}
	}
	else
	{
		m_pBrain = NULL;
	}

	// Monster가 존에 나타나는 방법
	switch (pMonsterInfo->selectRegenType())
	{
		case REGENTYPE_HIDE :
			setFlag(Effect::EFFECT_CLASS_HIDE);
			m_MoveMode = MOVE_MODE_BURROWING;
		break;

		case REGENTYPE_PORTAL :
			// by sigi. 2002.9.6
			setFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);
		break;

		case REGENTYPE_INVISIBLE :
			setFlag(Effect::EFFECT_CLASS_INVISIBILITY);
		break;

		case REGENTYPE_BAT :
			setFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);
			m_MoveMode = MOVE_MODE_FLYING;
		break;

		default :
		break;
	}

	// 이름을 설정한다.
	if (m_bMaster)
		m_Name = pMonsterInfo->getHName();
	else
		m_Name = g_pMonsterNameManager->getRandomName(this);

	if (monsterType == 722 ) m_Name = "하이메스 맹인석상";

	getCurrentTime(m_LastSpeechTime);

	switch (monsterType)
	{
		case 358:
		case 359:
			m_Name = g_pStringPool->getString(STRID_EVENT_SANTA_NAME);
			break;
		case 360:
		case 361:
			m_Name = g_pStringPool->getString(STRID_EVENT_WOLF_NAME);
			break;
		case 371:
		case 372:
			m_Name = g_pStringPool->getString(STRID_SLAYER_RELIC_SHRINE);
			break;
		case 374:
	    case 375:
			m_Name = g_pStringPool->getString(STRID_VAMPIRE_RELIC_SHRINE);
			break;
		default:
			break;
	}

	if (monsterType >= 660 && monsterType <= 669 ) m_Name = g_pStringPool->getString(STRID_ORE);

	// 클랜 타입을 세팅한다.
	// by sigi. 2002.10.8
	m_ClanType = pMonsterInfo->getClanType();//CLAN_VAMPIRE_MONSTER;
	m_OwnerObjectID = 0;

	m_HostName = "";
	m_HostPartyID = 0;

	// InitAllStat 함수에 있는 부분이지만,
	// InitAllStat 함수는 무거운 함수여서
	// 간단히 여기서 바로 저항력을 세팅해 준다.
	if(monsterType>=371 && monsterType<=375)
	{
		m_Resist[MAGIC_DOMAIN_NO_DOMAIN] = 0;
		m_Resist[MAGIC_DOMAIN_POISON]    = 70;
		m_Resist[MAGIC_DOMAIN_ACID]      = 60;
		m_Resist[MAGIC_DOMAIN_CURSE]     = 100;
		m_Resist[MAGIC_DOMAIN_BLOOD]     = 50;
	}
	else
	{
		m_Resist[MAGIC_DOMAIN_NO_DOMAIN] = 0;
		m_Resist[MAGIC_DOMAIN_POISON]    = 50;
		m_Resist[MAGIC_DOMAIN_ACID]      = 0;
		m_Resist[MAGIC_DOMAIN_CURSE]     = 0;
		m_Resist[MAGIC_DOMAIN_BLOOD]     = 0;
	}

	// 기본 effect들을 설정한다. by sigi. 2002.9.13
	pMonsterInfo->addDefaultEffects(this);
		
	m_LastHitCreatureClass = CREATURE_CLASS_MAX;
	m_isEventMonster = false;

	// 없는게 -1이다.
	m_RelicIndex = -1;

	// 대충 못 움직이는 몹은 걍 RelicIndex를 넣어가지고 못 움직이게 한다.
	if (monsterType >= 660 && monsterType <= 669 )
	{
		m_RelicIndex = monsterType;
	}

	m_bScanEnemy = false;
	m_NextScanTurn.tv_sec = 0;
	m_NextScanTurn.tv_usec = 0;

	m_pOldEnemy = NULL;
	m_bEnemyLimit = false;

	// 2002.10.14
	if (pMonsterInfo->isNormalRegen())
	{
		m_EventMonsterIndex = 0xFFFF;
	}
	else
	{
		// 실제 index는 외부에서 설정해야되지만,
		// 소환된 몬스터인 경우는 여기서 사바사바~ 일단 설정해둔다.
		m_EventMonsterIndex = 0xF000 + rand()%0x0FFF;
	}

	setChief(pMonsterInfo->isChief());

	} catch (Throwable& t)
	{
		filelog("monsterCreateBug.txt", "%s", t.toString().c_str());
		throw;
	}

	m_pQuestItem = NULL;

#ifdef __UNDERWORLD__
	m_bUnderWorld = false;
#endif

	m_LastKiller = 0;
	getCurrentTime(m_NextRegenTime);
	
	switch (m_MonsterType )
	{
		case 724:
		case 725:
			m_HP[ATTR_CURRENT] = m_HP[ATTR_MAX] = 30000;
			break;
		default:
			break;
	}

	switch (m_MonsterType )
	{
		case 717:
		case 723:
		case 724:
		case 725:
			{
				m_RegenAmount = 100;
			}
			break;
	
		case 721:
			{
				m_RegenAmount = 50;
			}
			break;

		default:
			{
				m_RegenAmount = 0;
			}
	}

	if (m_MonsterType == 764 )
	{
		EffectRegenerate* pEffect = new EffectRegenerate(this);
		pEffect->setTick(30);
		pEffect->setPoint(200);
		pEffect->setNextTime(0);
		addEffect(pEffect);
	}
	else if (m_MonsterType == 765 )
	{
		EffectRegenerate* pEffect = new EffectRegenerate(this);
		pEffect->setTick(30);
		pEffect->setPoint(300);
		pEffect->setNextTime(0);
		addEffect(pEffect);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
Monster::~Monster() 
    throw()
{
	__BEGIN_TRY

	SAFE_DELETE(m_pBrain);
	
	__END_CATCH
}

SpriteType_t Monster::getSpriteType () const 
	throw() 
{ 
	__BEGIN_TRY

	return g_pMonsterInfoManager->getMonsterInfo(m_MonsterType)->getSpriteType(); 
	
	__END_CATCH
}

Level_t Monster::getLevel () const 
	throw() 
{ 
	__BEGIN_TRY

	return g_pMonsterInfoManager->getMonsterInfo(m_MonsterType)->getLevel(); 
	
	__END_CATCH
}

uint Monster::getBodySize () const 
	throw() 
{ 
	__BEGIN_TRY

	return g_pMonsterInfoManager->getMonsterInfo(m_MonsterType)->getBodySize(); 
	
	__END_CATCH
}

Color_t Monster::getMainColor () const 
	throw() 
{ 
	__BEGIN_TRY

	return g_pMonsterInfoManager->getMonsterInfo(m_MonsterType)->getMainColor(); 
	
	__END_CATCH
}

Color_t Monster::getSubColor () const 
	throw() 
{ 
	__BEGIN_TRY

	return g_pMonsterInfoManager->getMonsterInfo(m_MonsterType)->getSubColor(); 
	
	__END_CATCH
}

MAlignment Monster::getAlignment () const 
	throw() 
{ 
	__BEGIN_TRY

	return g_pMonsterInfoManager->getMonsterInfo(m_MonsterType)->getAlignment(); 
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// registerObject 
//////////////////////////////////////////////////////////////////////////////
void Monster::registerObject ()
	throw(Error)
{
	__BEGIN_TRY

	Assert(getZone() != NULL);

	ObjectRegistry & OR = getZone()->getObjectRegistry();

	__ENTER_CRITICAL_SECTION(OR)

	OR.registerObject_NOLOCKED(this);

	__LEAVE_CRITICAL_SECTION(OR)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 몬스터 AI 가 실행되는 메쏘드이다. Zone::processZone () 에서 존에 존재
// 하는 모든 몬스터를 iterating 해가면서 Monster::act() 메쏘드를 호출한다.
//////////////////////////////////////////////////////////////////////////////
void Monster::act(const Timeval& currentTime)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	if (m_RegenAmount != 0 && currentTime > m_NextRegenTime )
	{
		if ((HP_t)(m_HP[ATTR_MAX] * 0.3) > m_HP[ATTR_CURRENT] )
		{
			switch (m_MonsterType )
			{
				case 724:
				case 725:
					{
						m_NextRegenTime.tv_sec += 1;
						m_RegenAmount = 100;
					}
					break;
				case 717:
					{
						m_NextRegenTime.tv_sec += 1;
						m_RegenAmount = 200;
					}
					break;
				case 723:
					{
						m_NextRegenTime.tv_sec += 1;
						m_RegenAmount = 300;
					}
					break;
				default:
					m_NextRegenTime.tv_sec += 3;
			}
		}
		else
		{
			switch (m_MonsterType )
			{
				case 724:
				case 725:
				case 717:
				case 723:
					{
						m_NextRegenTime.tv_sec += 2;
					}
					break;
			
				case 721:
				default:
					{
						m_NextRegenTime.tv_sec += 7;
					}
					break;
			}
		}

		m_HP[ATTR_CURRENT] += min((int)m_RegenAmount, m_HP[ATTR_MAX] - m_HP[ATTR_CURRENT]);

		GCStatusCurrentHP gcHP;
		gcHP.setObjectID(getObjectID());
		gcHP.setCurrentHP(m_HP[ATTR_CURRENT]);

		if (getZone() != NULL )
			getZone()->broadcastPacket(getX(), getY(), &gcHP);
	}

	// 현재 시간이 다음 턴보다 작다면, 아직 좀 더 기다려야 한다.
	// 그렇지 않으면, 액션을 취한다.
	if (currentTime < m_NextTurn) return;	

	// 쌓여있는 딜레이가 있다면 제거해야 한다.
	if (m_AccuDelay.tv_sec != 0 || m_AccuDelay.tv_usec != 0)
	{
		m_NextTurn.tv_sec  += m_AccuDelay.tv_sec;
		m_NextTurn.tv_usec += m_AccuDelay.tv_usec;

		clearAccuDelay();
		return;
	}

	__BEGIN_PROFILE_MONSTER("M_VERIFY_ENEMIES");

	// 그동안 로그아웃하거나 안전지대 안으로
	// 들어간 PC가 있으면 적 리스트에서 삭제를 한다.
	verifyEnemies(); 

	__END_PROFILE_MONSTER("M_VERIFY_ENEMIES");

	// AI가 없다면...
	if (m_pBrain==NULL)
	{
		// delay설정
		Timeval delay;
		delay.tv_sec  = 1;
		delay.tv_usec = 500000;
		addAccuDelay(delay);

		return;
	}

	// Paralyze에 걸려있다면 움직일 수가 없다.
	if (isFlag(Effect::EFFECT_CLASS_PARALYZE) 
		|| isFlag(Effect::EFFECT_CLASS_COMA) 
		|| isFlag(Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS)
		|| isFlag(Effect::EFFECT_CLASS_SLEEP)
		|| isFlag(Effect::EFFECT_CLASS_ARMAGEDDON)
		|| isFlag(Effect::EFFECT_CLASS_TRAPPED)
		|| isFlag(Effect::EFFECT_CLASS_EXPLOSION_WATER)
	)
	{
		m_pBrain->setDelay(currentTime);
		return;
	}
/*
//#ifdef __XMAS_EVENT_CODE__
	
	if (m_LastSpeechTime < currentTime && isEventMonster(this))
	{
		GCSay gcSay;
		gcSay.setObjectID(getObjectID());

		if (m_MonsterType == 358 || m_MonsterType == 359)
		{
			gcSay.setMessage(SantaSpeech[rand()%SantaSpeechMax]);
		}
		else if (m_MonsterType == 360 || m_MonsterType == 361)
		{
			gcSay.setMessage(RudolfSpeech[rand()%RudolfSpeechMax]);
		}
		else
		{
			Assert(false);
		}

		m_pZone->broadcastPacket(m_X, m_Y, &gcSay);

		m_LastSpeechTime.tv_sec = currentTime.tv_sec + 30;
		m_LastSpeechTime.tv_usec = currentTime.tv_usec;
	}

//#endif
*/
	// 적이 있다면 적에 따라, 일련의 행동을 취한다.
	if (hasEnemy())
	{
		Creature* pEnemy = getPrimaryEnemy();

		if (pEnemy!=NULL) 
		{
			__BEGIN_PROFILE_MONSTER("M_AI_DEAL");
			m_pBrain->deal(pEnemy, currentTime);
			__END_PROFILE_MONSTER("M_AI_DEAL");
		}
	}
	else
	{
		// 숨어있는 경우 체크
		if (isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			__BEGIN_PROFILE_MONSTER("M_UNBURROW");
			const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(m_MonsterType);
		
			if ((rand() & 0x0000007F) < pMonsterInfo->getUnburrowChance())
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_UN_BURROW);
				Assert(pSkillHandler != NULL);

				pSkillHandler->execute(this);

				// delay설정
				Timeval delay;
				delay.tv_sec  = 1;
				delay.tv_usec = 500000;
				addAccuDelay(delay);
			}
			else
			{
				// 숨어있는 동안도 체크 delay를 둔다.
				m_pBrain->setDelay(currentTime);
			}
			__END_PROFILE_MONSTER("M_UNBURROW");
		}
		// 적이 없을 때에는 맵의 중간을 향해 움직인다.
		// 마스터가 아닌 경우에..
		// 아담의 성지 중앙 맵이 이상하게 생겨서 아담의 성지 중앙 맵도 안한다.
		else if (!isMaster() && m_pZone->getZoneID() != 72 )
		{
			// 몬스터의 타입이 Relic인 경우는 움직이지 않는다.
			if (m_RelicIndex==-1)
			{
				__BEGIN_PROFILE_MONSTER("M_MOVE_CENTER");
				POINT pt(getX(), getY());

				VSRect* pOuterRect = m_pZone->getOuterRect();
				VSRect* pInnerRect = m_pZone->getInnerRect();
				VSRect* pCoreRect  = m_pZone->getCoreRect();

				// 안쪽부터 검사해 나간다.
				if (pCoreRect->ptInRect(pt) || pInnerRect->ptInRect(pt))
				{
					// 바깥쪽에 있다면 랜덤으로 움직인다.
					uint diceResult = rand() & 0x0000007F;	//%100;
					if (diceResult < 6)						// 5
					{
						uint        direction = rand() & 0x00000007; //% 8;
						ZoneCoord_t nx        = pt.x + dirMoveMask[direction].x;
						ZoneCoord_t ny        = pt.y + dirMoveMask[direction].y;

						// 1. 다음 좌표가 블럭킹이 되어있지 않아야 하고,
						// 2. 안전 지대가 아니라면,
						if (canMove(nx, ny) && !(m_pZone->getZoneLevel(nx, ny) & SAFE_ZONE))
						{
							m_pZone->moveCreature(this, nx, ny, direction);
						}
					}
				}
				else if (pOuterRect->ptInRect(pt))
				{
					// 제일 바깥쪽에 있다면, 맵의 중앙을 향해 움직인다.
					m_pBrain->move(m_pZone->getWidth()>>1, m_pZone->getHeight()>>1);
				}

				if ((m_bScanEnemy || isFlag(Effect::EFFECT_CLASS_HALLUCINATION) ) && currentTime > m_NextScanTurn )
				{
					m_pZone->monsterScan(this, m_X, m_Y, m_Dir);

					// 5초 후 다시 검색
					m_NextScanTurn.tv_sec = currentTime.tv_sec + 2;
					m_NextScanTurn.tv_usec = currentTime.tv_usec;
				}
				__END_PROFILE_MONSTER("M_MOVE_CENTER");
			}

			// 다음 턴을 지정한다.
			// 현재 몬스터들은 1초에 1타일만 움직이기 땜시로.. =_=;
			m_pBrain->setDelay(currentTime);
		}
	}

	//----------------------------------------------------------------------
	// HP를 리젠한다.
	// fucking
	//----------------------------------------------------------------------
	__BEGIN_PROFILE_MONSTER("M_REGEN_HP");
	int statSum = m_STR + m_DEX + m_INT;
	if (rand()%600 < statSum && isAlive())
		m_HP[ATTR_CURRENT] =(HP_t)min((int)m_HP[ATTR_CURRENT]+1, (int)m_HP[ATTR_MAX]);

	if (m_HP[ATTR_CURRENT] == m_HP[ATTR_MAX] && isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN ) )
	{
		removeFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
	}
	__END_PROFILE_MONSTER("M_REGEN_HP");

	__END_DEBUG
	__END_CATCH
}

void Monster::actDeadAction(void) 
	throw(Error)
{
	__BEGIN_TRY

	// 그동안 로그아웃하거나 안전지대 안으로
	// 들어간 PC가 있으면 적 리스트에서 삭제를 한다.
	verifyEnemies(); 

	// AI가 있다면..
	if (m_pBrain!=NULL)
	{
		if (hasEnemy())
		{
			Creature* pEnemy = getPrimaryEnemy();
			//Assert(pEnemy != NULL);
			if (pEnemy!=NULL) m_pBrain->actDeadAction(pEnemy);
		}
	}
	else if (getMonsterType() == GROUND_ELEMENTAL_TYPE )
	{
		int oX, oY;
		int X = getX();
		int Y = getY();

		for (oX = X - 2 ; oX <= X + 2 ; ++oX )
		for (oY = Y - 2 ; oY <= Y + 2 ; ++oY )
		{
			if (!isValidZoneCoord(getZone(), oX, oY ) ) continue;
			Effect* pEffect = getZone()->getTile(oX,oY).getEffect(Effect::EFFECT_CLASS_GROUND_ELEMENTAL_AURA);
			if (pEffect != NULL )
			{
				getZone()->deleteEffect(pEffect->getObjectID());
			}
		}
	}
	else if (getMonsterType() >= 726 && getMonsterType() <= 729 )
	{
		SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_SUMMON_MONSTERS);
		pSkillHandler->execute(this);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 특정 크리처를 적 리스트에 추가한다.
//
// 추가할 때, 몬스터의 AttackOrder 가 순서에 영향을 미친다.
//
// PC 가 이동할 때, 주변에 AGGRESSIVE 몬스터가 있을 경우, 그 몬스터에 
// 대해서 addEnemy() 를 호출해준다. 또는 PC가 몬스터를 공격할 때, 그
// 몬스터에 대해서 addEnemy()를 호출해준다. (이때 성향과는 무관하다.)
// PC가 몬스터를 공격할 때, 주변의 몬스터들에게도 addEnemy()를 호출해준다.
//////////////////////////////////////////////////////////////////////////////
void Monster::addEnemy (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	// 자신이 아니면.. by sigi. 2002.9.7
	if (this==pCreature
		|| !isRealEnemy(pCreature)) return;

	// peace에 걸려있다면..
	// addEnemy()는 때렸을때 불리는 함수이므로.. pece를 제거한다.
	if (isFlag(Effect::EFFECT_CLASS_PEACE))
	{
		Effect* pEffect = m_pEffectManager->findEffect(Effect::EFFECT_CLASS_PEACE);

		EffectPeace* pEffectPeace = dynamic_cast<EffectPeace*>(pEffect);

		// peace인 애라면 peace 제거
		if (pCreature->getObjectID()==pEffectPeace->getPeaceCreatureID())
		{
			pEffect->unaffect(this);
			m_pEffectManager->deleteEffect(Effect::EFFECT_CLASS_PEACE);
		}
	}

	try 
	{
		switch (getAttackOrder()) 
		{
			// 제일 먼저 때린 놈부터 공격하므로, 
			// 가장 마지막에 추가되어야 한다.
			case ATTACK_FIRST :          
				{
					// 기억하고 있는 적의 숫자가 자신의 최대기억개수보다 작고,
					// 자신이 이미 기억되고 있지 않는다면, enemy list의 맨 마지막에 추가한다.
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());
					if (itr == m_Enemies.end()) {
						m_Enemies.push_back(pCreature->getObjectID());
						if (m_Enemies.size() > getMaxEnemies()) {
							m_Enemies.pop_back();
						}
					}
				}
				break;

			// 제일 나중에 때린 놈부터 공격하므로,
			// 가장 앞에 추가되어야 한다.
			case ATTACK_LAST :           
				{
					// 기억하고 있는 적의 숫자가 자신의 최대기억개수보다 작고,
					// 자신이 이미 기억되고 있지 않는다면, enemy list의 맨 앞에 추가한다.
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());
					if (itr == m_Enemies.end())
					{
						m_Enemies.push_front(pCreature->getObjectID());
						
						// < 를 > 로 바꿨다. by sigi. 2002.10.7
						if (m_Enemies.size() > getMaxEnemies()) 
						{
							m_Enemies.pop_back();
						}
					}
				}
				break;

			// 제일 약한 놈부터 공격
			case ATTACK_WEAKEST :        
				{
					// 자신이 이미 기억되고 있지 않다면...
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());
					if (itr == m_Enemies.end()) {

						if (pCreature->isSlayer()) {

							Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

							itr = find_if (m_Enemies.begin() , m_Enemies.end() , StrongerSlayer(m_pZone , pSlayer->getSkillDomainLevelSum()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_front(pSlayer->getObjectID());
							else
								m_Enemies.insert(itr , pSlayer->getObjectID());
		
						}
						else if (pCreature->isVampire()) {
		
							Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		
							itr = find_if (m_Enemies.begin() , m_Enemies.end() , StrongerVampire(m_pZone , pVampire->getLevel()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_back(pVampire->getObjectID());
							else
								m_Enemies.insert(itr , pVampire->getObjectID());
		
						} 
						else if (pCreature->isOusters()) {
		
							Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		
							itr = find_if (m_Enemies.begin() , m_Enemies.end() , StrongerOusters(m_pZone , pOusters->getLevel()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_back(pOusters->getObjectID());
							else
								m_Enemies.insert(itr , pOusters->getObjectID());
		
						} 
						// 재미삼아 -_-; 2002.7.22 by sigi
						else if (pCreature->isMonster()) 
						{
							Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		
							itr = find_if (m_Enemies.begin() , m_Enemies.end() , StrongerMonster(m_pZone , pMonster->getLevel()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_back(pMonster->getObjectID());
							else
								m_Enemies.insert(itr , pMonster->getObjectID());

							// 전체의 적으로 인식시켜버린다.
							// 부하가 심해서 일단 뺀다.
							//m_pZone->getMonsterManager()->addPotentialEnemy(this, pCreature);
						}
		
						// 새로 추가된 결과, 정원을 초과한 경우 맨 마지막 놈을 삭제한다.
						if (!m_Enemies.empty() && m_Enemies.size() > getMaxEnemies())
							m_Enemies.pop_back();
					}

				}
				break;

			// 제일 강한 놈부터 공격
			case ATTACK_STRONGEST :      
				{
					// 자신이 이미 기억되고 있지 않다면...
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());

					if (itr == m_Enemies.end()) 
					{
						if (pCreature->isSlayer()) 
						{
							Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

							itr = find_if (m_Enemies.begin() , m_Enemies.end() , WeakerSlayer(m_pZone , pSlayer->getSkillDomainLevelSum()));

							if (itr == m_Enemies.end())
								m_Enemies.push_front(pSlayer->getObjectID());
							else
								m_Enemies.insert(itr , pSlayer->getObjectID());
						} 
						else if (pCreature->isVampire()) 
						{
							Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		
							itr = find_if (m_Enemies.begin() , m_Enemies.end() , WeakerVampire(m_pZone , pVampire->getLevel()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_back(pVampire->getObjectID());
							else
								m_Enemies.insert(itr , pVampire->getObjectID());
						}
						else if (pCreature->isOusters()) 
						{
							Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		
							itr = find_if (m_Enemies.begin() , m_Enemies.end() , WeakerOusters(m_pZone , pOusters->getLevel()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_back(pOusters->getObjectID());
							else
								m_Enemies.insert(itr , pOusters->getObjectID());
						}
						// 재미삼아 -_-; 2002.7.22 by sigi
						else if (pCreature->isMonster()) 
						{
							Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		
							itr = find_if (m_Enemies.begin() , m_Enemies.end() , WeakerMonster(m_pZone , pMonster->getLevel()));
		
							if (itr == m_Enemies.end())
								m_Enemies.push_back(pMonster->getObjectID());
							else
								m_Enemies.insert(itr , pMonster->getObjectID());
		
							// 전체의 적으로 인식시켜버린다.
							// 부하가 심해서 일단 뺀다.
							//m_pZone->getMonsterManager()->addPotentialEnemy(this, pCreature);
						}
		
						// 새로 추가된 결과, 정원을 초과한 경우 맨 마지막 놈을 삭제한다.
						if (!m_Enemies.empty() && m_Enemies.size() > getMaxEnemies())
							m_Enemies.pop_back();
					}
				}
				break;

			// 제일 가까운 놈 부터 공격
			// 적과의 거리는 계속 변하기 때문에, 내부 리스트를 계속 
			// 변경하는 대신 적을 고를 때, 가장 가깝거나 먼 적을 
			// 리턴하도록 해야 한다.
			case ATTACK_CLOSEST :        
				{
					// 자신이 이미 기억되고 있지 않다면...
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());
					if (itr == m_Enemies.end()) 
					{
						// 일단 추가한다.
						m_Enemies.push_back(pCreature->getObjectID());
		
						// 정원 초과일 경우
						if (m_Enemies.size() > getMaxEnemies()) 
						{
							// 누가 가장 거리가 먼지 알아낸다.
							list<ObjectID_t>::iterator farest = m_Enemies.end();
							Distance_t dist = 0;

							for (itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 	
							{
								Creature* pEnemy = NULL;
								
								/*
								try
								{
									pEnemy = m_pZone->getCreature(*itr);
								}
								catch (NoSuchElementException& nsee)
								{
									//cerr << nsee.toString() << endl;
									pEnemy = NULL;
								}
								*/

								// NoSuch..제거. by sigi. 2002.5.2
								pEnemy = m_pZone->getCreature(*itr);

								// zone에 없는 경우.. 제거하면 된다. by sigi. 2002.5.3
								if (pEnemy == NULL)
								{
									dist = 255;
									farest = itr;
									
									// 더 이상 검사해볼 필요가 없다.
									break;
								}
								else
								{
									Distance_t curDist = getDistance(pEnemy->getX() , pEnemy->getY());
									if (dist < curDist) 
									{
										dist = curDist;
										farest = itr;
									}
								}
							}
		
							// 정원 초과이므로, 가장 먼놈이 하나는 나와야 한당.
							//Assert(farest != m_Enemies.end());

							// 가장 거리가 먼 놈을 삭제한다.
							if (farest!=m_Enemies.end()) m_Enemies.erase(farest);
						}
					}
				}
				break;

			// 제일 먼 놈 부터 공격
			case ATTACK_FAREST :         
				{
					// 자신이 이미 기억되고 있지 않다면...
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());
					if (itr == m_Enemies.end()) 
					{
						// 일단 추가한다.
						m_Enemies.push_back(pCreature->getObjectID());
		
						// 정원 초과일 경우
						if (m_Enemies.size() > getMaxEnemies()) 
						{
							// 누가 가장 거리가 가까운지 알아낸다.
							list<ObjectID_t>::iterator closest = m_Enemies.end();
							Distance_t dist = 255;
		
							for (itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 
							{
								Creature* pEnemy = NULL;

								/*
								try
								{
									pEnemy = m_pZone->getCreature(*itr);
								}
								catch (NoSuchElementException& nsee)
								{
									//cerr << nsee.toString() << endl;
									pEnemy = NULL;
								}
								*/

								// NoSuch..제거. by sigi. 2002.5.2
								pEnemy = m_pZone->getCreature(*itr);

								// zone에 없는 경우.. 제거하면 된다. by sigi. 2002.5.3
								if (pEnemy == NULL)
								{
									dist = 0;
									closest = itr;

									// 더 이상 검사해볼 필요가 없다.
									break;
								}
								else
								{
									Distance_t curDist = getDistance(pEnemy->getX() , pEnemy->getY());
									if (dist > curDist) 
									{
										dist = curDist;
										closest = itr;
									}
								}
							}
			
							// 가장 거리가 가까운 놈을 삭제한다.
							if (closest!=m_Enemies.end()) m_Enemies.erase(closest);
						}
					}
				}
				break;

			// 전사 먼저 공격
			case ATTACK_FIGHTER :        
				{
					throw UnsupportedError(__PRETTY_FUNCTION__);

					// 일단 추가한다.
					m_Enemies.push_back(pCreature->getObjectID());

					// 정원 초과일 경우
					if (m_Enemies.size() > getMaxEnemies()) 
					{
						// 무사 스킬이 특히 높은 슬레이어가 아니라면 없엔다.
						for (list<ObjectID_t>::iterator itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 
						{
							//Creature* pCreature = m_pZone->getCreature(*itr);
						}
					}
				}
				break;

			// 성직자 먼저 공격
			case ATTACK_PRIEST :         
				{
					throw UnsupportedError(__PRETTY_FUNCTION__);

					// 일단 추가한다.
					m_Enemies.push_back(pCreature->getObjectID());

					// 정원 초과일 경우
					if (m_Enemies.size() > getMaxEnemies()) 
					{
						// 성직자 마법이 특히 높은 슬레이어가 아니라면 없엔다.
						for (list<ObjectID_t>::iterator itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 
						{
							//Creature* pCreature = m_pZone->getCreature(*itr);
						}
					}
				}
				break;

			// 건너 먼저 공격
			case ATTACK_GUNNER :         
				{
					throw UnsupportedError(__PRETTY_FUNCTION__);

					// 일단 추가한다.
					m_Enemies.push_back(pCreature->getObjectID());

					// 정원 초과일 경우
					if (m_Enemies.size() > getMaxEnemies()) 
					{
						// 건너 스킬이 특히 높은 슬레이어가 아니라면 없엔다.
						for (list<ObjectID_t>::iterator itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 
						{
							//Creature* pCreature = m_pZone->getCreature(*itr);
						}
					}
				}
				break;

			// 현재 원인을 알 수가 없어서 일단 제일 위의 타입으로 막아놓는다.
			default :
				
				{
					// 기억하고 있는 적의 숫자가 자신의 최대기억개수보다 작고,
					// 자신이 이미 기억되고 있지 않는다면, enemy list의 맨 마지막에 추가한다.
					list<ObjectID_t>::iterator itr = find(m_Enemies.begin() , m_Enemies.end() , pCreature->getObjectID());
					if (itr == m_Enemies.end()) {
						m_Enemies.push_back(pCreature->getObjectID());
						if (m_Enemies.size() > getMaxEnemies()) {
							m_Enemies.pop_back();
						}
					}
				}
				break;
				//throw Error("illegal attack order");
		}
	} 
	catch (Throwable & t) 
	{
		//cerr << t.toString() << endl;
	}

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 잠재적인 적을 리스트의 맨 뒤에 추가한다.
// addEnemy()가 직접적인 공격시에 설정되는 반면, addPotentialEnemy()는
// PC의 이동, 로그인시 설정된다.
//////////////////////////////////////////////////////////////////////////////
void Monster::addPotentialEnemy (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	// 자신이 아니면.. by sigi. 2002.9.7
	if (this==pCreature
		|| !isRealEnemy(pCreature)) return;
	// 할루 걸려있으면 클랜타입 구분 못 한다.
	if (!isFlag(Effect::EFFECT_CLASS_HALLUCINATION ) &&
		pCreature->getClanType() == m_ClanType) return;

	// peace에 걸려있다면..
	if (isFlag(Effect::EFFECT_CLASS_PEACE))
	{
//		Effect* pEffect = pMonster->getEffectManager()->findEffect(EFFECT_CLASS_PEACE);
		Effect* pEffect = m_pEffectManager->findEffect(Effect::EFFECT_CLASS_PEACE);

		EffectPeace* pEffectPeace = dynamic_cast<EffectPeace*>(pEffect);

		// peace인 애는 안 넣는다.
		if (pCreature->getObjectID()==pEffectPeace->getPeaceCreatureID())
		{
			return;
		}
	}

	// 현재 적 리스트에 존재하지 않는다면, 적으로서 인식하고 더한다.
	list<ObjectID_t>::iterator itr = find(m_Enemies.begin(), m_Enemies.end(), pCreature->getObjectID());
	if (itr == m_Enemies.end() && m_Enemies.size() < getMaxEnemies()) 
	{
		m_Enemies.push_back(pCreature->getObjectID());

		// 재미삼아 -_-; 2002.7.22 by sigi
		// 전체의 적으로 인식시켜버린다.
		// 부하가 심해서 일단 뺀다.
		// m_pZone->getMonsterManager()->addPotentialEnemy(this, pCreature);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 특정 크리처를 적 리스트에서 삭제한다.
//////////////////////////////////////////////////////////////////////////////
void Monster::deleteEnemy (ObjectID_t enemyID)
	throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	list<ObjectID_t>::iterator itr = find(m_Enemies.begin(), m_Enemies.end() , enemyID);

	if (itr == m_Enemies.end())
	{
		//cerr << "Monster::deleteEnemy() : NoSuchElementException" << endl;
		//throw NoSuchElementException();

		// exception 무시. by sigi. 2002.10.7
		return;
	}

	m_Enemies.erase(itr);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// Enemy 중에서 로그아웃한 PC 를 삭제한다.
//////////////////////////////////////////////////////////////////////////////
void Monster::verifyEnemies ()
	throw(Error)
{
	__BEGIN_TRY

	list<ObjectID_t>::iterator before  = m_Enemies.end();
	list<ObjectID_t>::iterator current = m_Enemies.begin();
	Creature*                  pEnemy  = NULL;

	while (current != m_Enemies.end())
	{
		// 크리처가 존재하는지 체크한다.
		pEnemy = m_pZone->getCreature(*current);

		if (pEnemy!=NULL)
		{
			if (!isRealEnemy(pEnemy))
			{
				m_Enemies.erase(current);

				if (before == m_Enemies.end()) // first enemy
				{
					current = m_Enemies.begin();
				}
				else // !first enemy
				{
					current = before;
					current ++;
				}
			}
			else
			{
				// 존재하면 다음 노드로 넘어간다.
				before = current ++;
			}
		} 
		else
		{
			// 존재하지 않으므로 삭제해야 한다.
			m_Enemies.erase(current);

			if (before == m_Enemies.end()) // first enemy
			{
				current = m_Enemies.begin();
			}
			else // !first enemy
			{
				current = before;
				current ++;
			}
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// PRIMARY ENEMY 를 리턴한다.
//////////////////////////////////////////////////////////////////////////////
Creature* Monster::getPrimaryEnemy () const
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// by sigi. 2002.10.7
	if (m_Enemies.empty())
		return NULL;

	Creature*  pEnemy    = NULL;
	Distance_t dist      = 255;
	Creature*  pCreature = NULL;
	Distance_t newDist   = 255;

	list<ObjectID_t>::const_iterator itr;

	switch (getAttackOrder()) 
	{
		// 다음 4 가지 공격 순서는 이미 적 리스트가
		// 순서대로 정렬되어 있으므로
		// 리스트의 front 에 위치하는 ENEMY 를 리턴하면 된다.
		case ATTACK_FIRST:
		case ATTACK_LAST:
		case ATTACK_STRONGEST:
		case ATTACK_WEAKEST:
			/*
			try
			{
				pEnemy = m_pZone->getCreature(m_Enemies.front());
			}
			catch (NoSuchElementException& nsee)
			{
				//cerr << nsee.toString() << endl;
				pEnemy = NULL;
			}
			*/

			// NoSuch.. 제거. by sigi. 2002.5.2
			pEnemy = m_pZone->getCreature(m_Enemies.front());

			break;

		// 다음 2 가지 공격 순서는, 거리가 계속 바뀌기 때문에 
		// 항상 계산을 해줘야 한다.
		case ATTACK_CLOSEST :
			dist = 255;
			for (itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 
			{
				/*
				try
				{
					pCreature = m_pZone->getCreature(*itr);
				}
				catch (NoSuchElementException& nsee)
				{
					//cerr << nsee.toString() << endl;
					pCreature = NULL;
				}
				*/
				
				// NoSuch.. 제거. by sigi. 2002.5.2
				pCreature = m_pZone->getCreature(*itr);

				if (pCreature != NULL)
				{
					newDist = pCreature->getDistance(m_X , m_Y);

					if (newDist < dist) // 거리가 더 가까울 경우
					{	
						dist = newDist;
						pEnemy = pCreature;
					}
				}
			}
			break;

		case ATTACK_FAREST :
			dist = 0;
			for (itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++) 
			{
				/*
				try
				{
					pCreature = m_pZone->getCreature(*itr);
				}
				catch (NoSuchElementException& nsee)
				{
					//cerr << nsee.toString() << endl;
					pCreature = NULL;
				}
				*/

				// NoSuch.. 제거. by sigi. 2002.5.2
				pCreature = m_pZone->getCreature(*itr);

				if (pCreature != NULL)
				{
					newDist = pCreature->getDistance(m_X , m_Y);

					if (newDist > dist) // 거리가 더 멀 경우
					{	
						dist = newDist;
						pEnemy = pCreature;
					}
				}
			}
			break;
		case ATTACK_FIGHTER :
		case ATTACK_PRIEST :
		case ATTACK_GUNNER :
		default :
			throw Error("invalid attack order");
	}

	if (pEnemy == NULL)
	{
		//cerr << "<ENEMY NULL ERROR>" << endl;
		//cerr << "Monster's AttackOrder : " << AttackOrder2String[getAttackOrder()] << endl;
		//cerr << "Enemy's ObjectID : " << m_Enemies.front();
	}

	return pEnemy;

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 적 리스트의 특정 위치의 크리처의 아이디를 리턴한다.
//////////////////////////////////////////////////////////////////////////////
ObjectID_t Monster::getEnemy (EnemyPriority enemyPriority) const
	throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	EnemyPriority ep = ENEMY_PRIMARY;
	list<ObjectID_t>::const_iterator itr = m_Enemies.begin();

	for (; itr != m_Enemies.end(); itr++) 
	{
		if (enemyPriority == ep) return *itr;
		ep = EnemyPriority(ep+1);
	}

	cerr << "Monster::getEnemy() : NoSuchElementException" << endl;
	throw NoSuchElementException();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 한 몬스터가 기억할 수 있는 최대 몬스터의 개수
//
// *CAUTION*
//
// 뱀파이어의 능력치의 최대값은 255 이다. 이 최대값을 바탕으로 기억량을
// 산정해보면...
//
//   0 -  30     : ENEMY_PRIORITY
//  30 -  60     : ENEMY_SECONDARY
//  60 -  90     : ENEMY_THIRD
//  90 - 120     : ENEMY_FOURTH
// 120 - 150     : ENEMY_FIFTH
// 150 - 180     : ENEMY_SIXTH
// 180 - 210     : ENEMY_SEVENTH
// 210 - maxAttr : ENEMY_EIGHTH
//////////////////////////////////////////////////////////////////////////////
uint Monster::getMaxEnemies () const
	throw()
{
	return (m_INT < 210) ? (m_INT / 30 + 1) : 8 ;
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string Monster::toString () const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	__BEGIN_DEBUG

	msg << "Monster("
		<< "ObjectID:"     << (int)getObjectID()
		<< ",MonsterType:" << (int)m_MonsterType
		<< ",SpriteType:"  << (int)getSpriteType()
		<< ",Name:"        << getName()
		<< ",Level:"       << (int)getLevel()
		<< ",STR:"         << (int)m_STR
		<< ",DEX:"         << (int)m_DEX
		<< ",INT:"         << (int)m_INT
		<< ",HP:"          << (int)m_HP[ATTR_CURRENT] << "/" << (int)m_HP[ATTR_MAX]
		<< ",MainColor:"   << (int)getMainColor()
		<< ",SubColor:"    << (int)getSubColor()
		<< ",Alignment:"   << MAlignment2String[getAlignment()]
		<< ",AttackOrder:" << AttackOrder2String[getAttackOrder()]
		<< ",Moral:"       << (int)m_Moral
		<< ",Delay:"       << (int)m_Delay
		<< ",Enemies(";

	for (list<ObjectID_t>::const_iterator itr = m_Enemies.begin() ; itr != m_Enemies.end() ; itr ++)
		msg << (int)(*itr) << " ";

	msg << ")"
		<< ",X:"      << (int)m_X
		<< ",Y:"      << (int)m_Y
		<< ",Sight :" << (int)m_Sight
		<< ")";

	__END_DEBUG

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Monster::setDamaged(bool value)
	throw()
{
	__BEGIN_TRY

	// AI가 있다면..
	if (m_pBrain!=NULL)
	{
		m_pBrain->setDamaged(value);
	}

	__END_CATCH
}

void Monster::addPrecedence(const string & Name, int PartyID, int damage)
{
	m_PrecedenceTable.addPrecedence(Name, PartyID, damage);
}

int Monster::getOustersExp(Ousters* pOusters )
{
	int total = computeCreatureExp(this, 100);
	double percent = m_PrecedenceTable.getDamagePercent(pOusters->getName(), pOusters->getPartyID());

//	return (int)((double)total * percent) * 1.4;
	return (int)((double)total * percent);
}

/*
void Monster::addPrecedence(Creature* pCreature, int damage)
{
	Assert(pCreature != NULL);
	m_PrecedenceTable.addPrecedence(pCreature, damage);
}
*/
void Monster::clearEnemyLimitTime() throw() 
{ 
	getCurrentTime(m_EnemyLimitTime); 
	
	m_EnemyLimitTime.tv_sec += g_pVariableManager->getEnemyLimitTime();
	m_EnemyLimitTime.tv_usec=0; 
}

bool Monster::hasNextMonsterSummonInfo()
	throw(Error)
{
	__BEGIN_TRY

	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(m_MonsterType);
	Assert(pMonsterInfo!=NULL);

	if (pMonsterInfo->hasNextMonsterSummonInfo(m_MonsterSummonStep ))
	{
		return true;
	}

	__END_CATCH

	return false;
}

bool Monster::getMonsterSummonInfo(SUMMON_INFO2& summonInfo) 
	throw(Error)
{
	__BEGIN_TRY

	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(m_MonsterType);
	Assert(pMonsterInfo!=NULL);

	if (pMonsterInfo->getMonsterSummonInfo(m_MonsterSummonStep, summonInfo ))
	{
		// 다음 단계의 소환을 준비한다.
		m_MonsterSummonStep ++;

		return true;
	}

	__END_CATCH

	return false;
}

////////////////////////////////////////////////////////////////////////////////
// isEnemyToAttack
////////////////////////////////////////////////////////////////////////////////
// 이 몬스터에게 있어서 적인가 아닌가를 판단하는 함수
//
// 파티/길드/동종족인 경우는 공격하지 않는다.
////////////////////////////////////////////////////////////////////////////////
bool Monster::isEnemyToAttack(Creature* pCreature) const
{
	if (pCreature->isFlag(Effect::EFFECT_CLASS_GHOST))
		return false;

	if (pCreature->getObjectID() == m_OwnerObjectID ) return false;

	if (m_OwnerObjectID != 0 )
	{
		Creature* pOwner = m_pZone->getCreature(m_OwnerObjectID);
		if (pOwner != NULL && pOwner->getCreatureClass() == pCreature->getCreatureClass() && canAttack(pOwner, pCreature ) )
		{
//			cout << __PRETTY_FUNCTION__ << pCreature->getName() << "is same race as owner " << pOwner->getName() << endl;
			return false;
		}

		if (GDRLairManager::Instance().isGDRLairZone(getZoneID()) && pCreature->isPC() ) return false;
	}

	if (m_Flag.test(Effect::EFFECT_CLASS_HALLUCINATION))
		return true;

	if (pCreature->isDead()
		|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
		return false;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		return isEnemyToAttack(pSlayer);
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		return isEnemyToAttack(pVampire);
	}
	else if (pCreature->isOusters())
	{
		// 일단은 새로 함수 추가 안하고 그냥 간다.
		return true;
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		return isEnemyToAttack(pMonster);
	}

	return false;
}

// 이 몬스터가 pSlayer를 공격해도 되는가?
bool Monster::isEnemyToAttack(Slayer* pSlayer) const
{
	if (pSlayer->isFlag(Effect::EFFECT_CLASS_GHOST))
		return false;

	if (m_Flag.test(Effect::EFFECT_CLASS_HALLUCINATION))
		return true;

	if (pSlayer->isDead()
		|| pSlayer->isFlag(Effect::EFFECT_CLASS_COMA))
		return false;

	// 지금은 무조건 슬레이어는 공격해도 된다.
	return true;	
}

// 이 몬스터가 pVampire를 공격해도 되는가?
bool Monster::isEnemyToAttack(Vampire* pVampire) const
{
	if (pVampire->isFlag(Effect::EFFECT_CLASS_GHOST))
		return false;

	if (m_Flag.test(Effect::EFFECT_CLASS_HALLUCINATION))
		return true;

	if (pVampire->isDead()
		|| pVampire->isFlag(Effect::EFFECT_CLASS_COMA))
		return false;

	// 지금은 무조건 뱀파이어는 공격해도 된다.
	return true;	
}

// 이 몬스터가 pMonster를 공격해도 되는가?
bool Monster::isEnemyToAttack(Monster* pMonster) const
{
	if (m_Flag.test(Effect::EFFECT_CLASS_HALLUCINATION))
		return true;

	// 같은 clan 소속 몬스터면 공격하지 않는다.
	// 나중에는.. 누군가의 명령?에 의해서 공격받을 수도 있으므로
	// m_Ememies를 검색해서 체크해야될 듯. -_-;
	// 걍 할루 걸린놈은 맞아도 싸다~ 원래는 m_Enemies 검색해야 되는 것 같은데 느려서 원 -_-
	if (pMonster->isDead() 
		|| pMonster->isFlag(Effect::EFFECT_CLASS_COMA)
		|| (!pMonster->isFlag(Effect::EFFECT_CLASS_HALLUCINATION) && pMonster->m_ClanType==m_ClanType)
	)
		return false;

	return true;
}

bool Monster::canMove(ZoneCoord_t nx, ZoneCoord_t ny) const throw(Error)
{
	return (Creature::canMove(nx, ny) && !(m_pZone->getZoneLevel(nx, ny) & SAFE_ZONE));
}


void Monster::setBrain(MonsterAI* pBrain)
{ 
	removeBrain(); 
	m_pBrain = pBrain; 
}

void Monster::removeBrain()
{ 
	SAFE_DELETE(m_pBrain); 
}

void Monster::deleteAllEnemy() 
	throw(Error)
{
	m_Enemies.clear();
}

Race_t Monster::getRace() const
{
	// 나중에.. 몬스터 종류에 따라서 다르게 해야겠지
	return RACE_VAMPIRE;
}

