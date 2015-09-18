//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterAI.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MonsterAI.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterInfo.h"
#include "EffectManager.h"
#include "SkillInfo.h"
#include "skill/SkillHandlerManager.h"
#include "Directive.h"
#include "ZoneUtil.h"
#include "Tile.h"
#include "MonsterManager.h"
#include "MasterLairManager.h"
#include "VariableManager.h"
#include "Effect.h"
#include "StringPool.h"

#include "Profile.h"
#include "GCSay.h"

#include <list>

#define ABS(X) (((X)>=0)?X:-X)

//#define __PROFILE_MONSTER__

#ifdef __PROFILE_MONSTER__
	#define __BEGIN_PROFILE_MONSTER(name)	beginProfileEx(name);
	#define __END_PROFILE_MONSTER(name)		endProfileEx(name);
#else
	#define __BEGIN_PROFILE_MONSTER(name)	((void)0);
	#define __END_PROFILE_MONSTER(name)		((void)0);
#endif

TPOINT getSafeTile(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
{
	TPOINT ptAcid;
	ptAcid = findSuitablePositionForEffect(pZone, x, y, Effect::EFFECT_CLASS_ACID_SWAMP);

	/*
	TPOINT ptBloody;
	ptBloody = findSuitablePositionForEffect(pZone, x, y, Effect::EFFECT_CLASS_BLOODY_WALL);
	*/

	return ptAcid;
}

int getStrongValue(Creature* pCreature)
{
	HP_t currentHP = 0;
	HP_t maxHP = 0;
	int  strongValue = 0;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		currentHP = pSlayer->getHP(ATTR_CURRENT);
		maxHP = pSlayer->getHP(ATTR_MAX);

		strongValue = pSlayer->getSTR() + 
						pSlayer->getDEX() + 
						pSlayer->getINT() + 
						pSlayer->getProtection() + 
						pSlayer->getDefense();
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		currentHP = pVampire->getHP(ATTR_CURRENT);
		maxHP = pVampire->getHP(ATTR_MAX);

		strongValue = pVampire->getSTR() + 
						pVampire->getDEX() + 
						pVampire->getINT() +
						pVampire->getProtection() + 
						pVampire->getDefense();
	}
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		currentHP = pOusters->getHP(ATTR_CURRENT);
		maxHP = pOusters->getHP(ATTR_MAX);

		strongValue = pOusters->getSTR() + 
						pOusters->getDEX() + 
						pOusters->getINT() +
						pOusters->getProtection() + 
						pOusters->getDefense();
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		currentHP = pMonster->getHP(ATTR_CURRENT);
		maxHP = pMonster->getHP(ATTR_MAX);

		strongValue = pMonster->getSTR() + 
						pMonster->getDEX() + 
						pMonster->getINT() +
						pMonster->getProtection() + 
						pMonster->getDefense();
	}
	else return 0;

	// pCreature HP가 120이상 
	if (currentHP>=120)
	{
		strongValue += 200;
	}
	
	// HP percentage가 60% 이상이라면 
	if (currentHP*100 >= maxHP*60)
	{
		strongValue += 200;
	}

	return strongValue;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
TPOINT randPos(int ox, int oy, int threshold, Zone* pZone) 
	throw()
{
	int tx = ox + (rand()%(threshold*2)) - threshold;
	int ty = oy + (rand()%(threshold*2)) - threshold;

	if (tx < 0) tx = 0;
	else if (tx >= pZone->getWidth()) tx = pZone->getWidth() - 1;

	if (ty < 0) ty = 0;
	else if (ty >= pZone->getHeight()) ty = pZone->getHeight() - 1;

	TPOINT pt;
	pt.x = tx;
	pt.y = ty;

	return pt;
}


//////////////////////////////////////////////////////////////////////////////
// 생성자/소멸자
//////////////////////////////////////////////////////////////////////////////

MonsterAI::MonsterAI(Monster* pMonster, uint type)
	throw()
{
	__BEGIN_TRY

	Assert(pMonster != NULL);	// by sigi

	m_pBody         = pMonster;
	m_AIType        = type;
	m_Panic         = 5;
	m_PanicMax      = 5;
	m_Courage       = 20;
	m_CourageMax    = 20;
	m_bDamaged      = false;
	m_LastAction    = LAST_ACTION_NONE;

	m_MoveRule 		= MOVE_RULE_NORMAL;
	m_BlockedDir	= DIR_NONE;
	m_WallCount		= 0;

	m_pDirectiveSet = g_pDirectiveSetManager->getDirectiveSet(type);

	m_pCondChecker[DIRECTIVE_COND_ENEMY_RANGE_MELEE]           = checkEnemyRangeMelee;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_RANGE_MISSILE]         = checkEnemyRangeMissile;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_RANGE_CLOSE]           = checkEnemyRangeClose;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_RANGE_OUT_OF_SIGHT]    = checkEnemyRangeOutOfSight;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_DYING]                 = checkEnemyDying;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_BLOOD_DRAINED]     = checkEnemyNotBloodDrained;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_GREEN_POISONED]    = checkEnemyNotGreenPoisoned;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_YELLOW_POISONED]   = checkEnemyNotYellowPoisoned;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_DARKBLUE_POISONED] = checkEnemyNotDarkbluePoisoned;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_GREEN_STALKERED]   = checkEnemyNotGreenStalkered;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_PARALYZED]         = checkEnemyNotParalyzed;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_DOOMED]            = checkEnemyNotDoomed;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_BLINDED]           = checkEnemyNotBlinded;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_IN_DARKNESS]       = checkEnemyNotInDarkness;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_SEDUCTION]      = checkEnemyNotSeduction;
	m_pCondChecker[DIRECTIVE_COND_IM_OK]                       = checkImOK;
	m_pCondChecker[DIRECTIVE_COND_IM_DYING]                    = checkImDying;
	m_pCondChecker[DIRECTIVE_COND_IM_DAMAGED]                  = checkImDamaged;
	m_pCondChecker[DIRECTIVE_COND_IM_HIDING]                   = checkImHiding;
	m_pCondChecker[DIRECTIVE_COND_IM_WOLF]                     = checkImWolf;
	m_pCondChecker[DIRECTIVE_COND_IM_BAT]                      = checkImBat;
	m_pCondChecker[DIRECTIVE_COND_IM_INVISIBLE]                = checkImInvisible;
	m_pCondChecker[DIRECTIVE_COND_IM_WALKING_WALL]             = checkImWalkingWall;
	m_pCondChecker[DIRECTIVE_COND_TIMING_BLOOD_DRAIN]          = checkTimingBloodDrain;
	m_pCondChecker[DIRECTIVE_COND_MASTER_SUMMON_TIMING]        = checkMasterSummonTiming;
	m_pCondChecker[DIRECTIVE_COND_MASTER_NOT_READY]            = checkMasterNotReady;
	m_pCondChecker[DIRECTIVE_COND_IM_IN_BAD_POSITION]          = checkImInBadPosition;
	m_pCondChecker[DIRECTIVE_COND_FIND_WEAK_ENEMY]             = checkFindWeakEnemy;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_DEATH]            = checkEnemyNotDeath;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_NOT_HALLUCINATION]    = checkEnemyNotHallucination;
	m_pCondChecker[DIRECTIVE_COND_TIMING_MASTER_BLOOD_DRAIN]  = checkTimingMasterBloodDrain;
	m_pCondChecker[DIRECTIVE_COND_TIMING_DUPLICATE_SELF]  	   = checkTimingDuplicateSelf;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_RANGE_IN_MISSILE]         = checkEnemyRangeInMissile;
	m_pCondChecker[DIRECTIVE_COND_POSSIBLE_SUMMON_MONSTERS]   = checkPossibleSummonMonsters;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_TILE_NOT_ACID_SWAMP]	= checkEnemyTileNotAcidSwamp;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_ON_AIR]					= checkEnemyOnAir;
	m_pCondChecker[DIRECTIVE_COND_ENEMY_ON_SAFE_ZONE]			= checkEnemyOnSafeZone;
	m_pCondChecker[DIRECTIVE_COND_CAN_ATTACK_THROWING_AXE]			= checkCanAttackThrowingAxe;

	__END_CATCH
}

MonsterAI::~MonsterAI()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void MonsterAI::addDirective(Directive* pDirective)
	throw()
{
	__BEGIN_TRY

	m_pDirectiveSet->addDirective(pDirective);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 조건 함수
//////////////////////////////////////////////////////////////////////////////

bool MonsterAI::checkCondition(int condition, Creature* pEnemy)
	throw()
{
	__BEGIN_TRY

	Assert(0 <= condition && condition < DIRECTIVE_COND_MAX);
//	cout << m_pBody->toString() << " check condition " << condition << " to" << pEnemy->toString() << endl;
	return m_pCondChecker[condition](m_pBody, pEnemy);

	__END_CATCH
}

bool MonsterAI::checkDirective(Directive* pDirective, Creature* pEnemy)
	throw()
{
	__BEGIN_TRY

	if (pDirective == NULL) return false;

	// 컨디션 리스트를 얻어내고...
	list<int>& conditionList = pDirective->getConditions();
	bool       rValue        = true;

	// 조건 중에 하나라도 만족하지 않는 것이 있다면,
	// false를 리턴한다.
	list<int>::iterator itr = conditionList.begin();
	for (; itr != conditionList.end(); itr++)
	{
		if (checkCondition(*itr, pEnemy) == false)
		{
			rValue = false;
			break;
		}
	}

	return rValue;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 보통의 움직임
//////////////////////////////////////////////////////////////////////////////

bool MonsterAI::moveNormal(ZoneCoord_t ex, ZoneCoord_t ey, ZoneCoord_t& nx, ZoneCoord_t& ny, Dir_t& ndir)
	throw()
{
	//Zone*       pZone   = m_pBody->getZone();
	Dir_t       bestDir = DIR_NONE;

	Dir_t curDir = m_pBody->getDir();

	////////////////////////////////////////////////////////////
	// 목적지점으로 향하는 최선의 방향을 찾는다.
	////////////////////////////////////////////////////////////
	if (m_pBody->getX() < ex) 
	{
		if (m_pBody->getY() < ey)      bestDir = RIGHTDOWN;
		else if (m_pBody->getY() > ey) bestDir = RIGHTUP;
		else                           bestDir = RIGHT;// m_pBody->getY() == ey
	} 
	else if (m_pBody->getX() > ex) 
	{
		if (m_pBody->getY() < ey)      bestDir = LEFTDOWN;
		else if (m_pBody->getY() > ey) bestDir = LEFTUP;
		else                           bestDir = LEFT;// m_pBody->getY() == ey
	} 
	else 
	{	
		if (m_pBody->getY() < ey)      bestDir = DOWN; // m_pBody->getX() == ex
		else if (m_pBody->getY() > ey) bestDir = UP;
		else                           bestDir = DIR_NONE; // m_pBody->getY() == ey
	}

	////////////////////////////////////////////////////////////
	// search surrounding tiles
	////////////////////////////////////////////////////////////

	int diffLevel = 0;

	// 방향과 방향 사이의 차이를 나타낸다. diffLevel == 1 에서, diff == 0 이기 위해서
	// 0 으로 초기화해야 한다. 그렇지 않으면, garbage 값으로 인해 오류가 나게 된다.
	int diff = 0;

	// 다음 방향이 발견되었는가?
	bool found = false;

	// 우선 bestDir 부터 체크해본다. unsigned type 이 되어서는 안된다.
	ndir = bestDir;

	// 다음 좌표
	nx = m_pBody->getX() + dirMoveMask[ndir].x;
	ny = m_pBody->getY() + dirMoveMask[ndir].y;

	bool bBlocked[DIR_MAX] = { false, };

	const Dir_t DIR_MAX_1 = DIR_MAX - 1;

	// bestDir 방향이 막혀 있다면, previous Dir 방향을 기준으로 +- 하면서 체크한다.
	// 이때 존의 경계를 넘어서는지 체크를 해야 한다.
	bool bCanMove = m_pBody->canMove(nx,ny);

	// 마스터인 경우에는 바닥에 안 좋은게 없어야 한다. - -; by sigi. 2002.9.12
	/*
	if (bCanMove && m_pBody->isMaster())
	{
		Tile& tile = m_pBody->getZone()->getTile(nx, ny);
		if (tile.hasEffect())
		{
			if (tile.getEffect(Effect::EFFECT_CLASS_ACID_SWAMP)!=NULL
				&& tile.getEffect(Effect::EFFECT_CLASS_GROUND_ATTACK)!=NULL)
			{
			}
			else bCanMove = false;
		}
	}
	*/

	if (!bCanMove)
	{
		bBlocked[ndir] = true;

		// best direction이 벽이라면 다음부터 벽타기를 한다.
		// 박쥐나 hide중이 아니어야 한다.
		if (!m_pBody->isBlockedByCreature(nx,ny)
			&& !m_pBody->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
			&& !m_pBody->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			setMoveRule(MOVE_RULE_RIGHTWALL); // 여기껀 별 의미없다.
			m_BlockedDir = bestDir;

			// 이번 턴에는 그냥 갈 방향을 결정하면 된다.
		}

		while (true) 
		{
			// 최초일 경우, diffLevel == 1 이 된다. 이는 m_pBody->getDir() 방향을 체크하라는 뜻이다.
			diffLevel ++;

			// 적절한 방향을 찾았거나, 더이상 찾을 수 없다면 끝낸다.
			if (found || diffLevel > 8) break;

			////////////////////////////////////////////////////////////
			// diffLevel 을 2 로 나눈 값이 같다는 뜻은, 서로 대칭되는
			// 방향이라는 뜻이다.  그 중 짝수를 만나면 최초로 diff 를 
			// 계산해서 한쪽 방향을 체크하며, 홀수를 만나면 이전 루프에서
			// 반대편 방향이 체크되었다는 뜻이므로, 계산된 diff 의
			// 음수를 사용해서 다른편 방향을 체크하면 되겠다.
			////////////////////////////////////////////////////////////
			if ((diffLevel & 0x00000001) == 0) 	// % 2 인데.. 바꿨당.. ㅋㅋ by sigi 
			{
				//diff = (int)(diffLevel >> 1) * (bSelectLeft ? 1 : -1);
				diff = diffLevel >> 1;

				Dir_t dir1 = (m_pBody->getDir() + diff) & DIR_MAX_1;
				Dir_t dir2 = (m_pBody->getDir() + DIR_MAX - diff) & DIR_MAX_1;

				// bestDir에 가까운 쪽을 먼저 선택해보자.
				if ((abs(ndir+DIR_MAX-dir1) & DIR_MAX_1) 
						< (abs(ndir+DIR_MAX-dir2) & DIR_MAX_1))
				{
					ndir = dir1;
				}
				else
				{
					diff = -diff;
					ndir = dir2;
				}
			} 
			else ndir = m_pBody->getDir() + DIR_MAX - diff;

			////////////////////////////////////////////////////////////
			// ndir 이 overflow, underflow 할 경우 값을 보정해줘야 한다.
			// overflow  : -1 -> 7 , -2 -> 6 , -3 -> 5 , ...
			// underflow :  8 -> 0 ,  9 -> 1 , 10 -> 2 , ...
			////////////////////////////////////////////////////////////
			//if (ndir >= DIR_MAX) // overflow
			//{	
			//	ndir = Directions(DIR_MAX - ndir);
			//} 
			//else if (ndir < 0) // underflow
			//{	
			//	ndir = Directions(DIR_MAX + ndir);
			//}
			ndir &= DIR_MAX_1;

			// 다음 좌표를 구한다.
			nx = m_pBody->getX() + dirMoveMask[ndir].x;
			ny = m_pBody->getY() + dirMoveMask[ndir].y;

			// 다음 방향이 비었으면, 루프를 빠져나갈 수 있다.
			// 이때 존의 경계를 넘어서는지 체크를 해야 한다.
			if (m_pBody->canMove(nx,ny))
			{
				// 마스터인 경우에는 바닥에 안 좋은게 없어야 한다. - -; by sigi. 2002.9.12
				/*
				if (m_pBody->isMaster())
				{
					Tile& tile = m_pBody->getZone()->getTile(nx, ny);
					if (tile.hasEffect())
					{
						if (tile.getEffect(Effect::EFFECT_CLASS_ACID_SWAMP)!=NULL
							&& tile.getEffect(Effect::EFFECT_CLASS_GROUND_ATTACK)!=NULL)
						{
							found = true;
						}
					}
				}
				else
				*/
				{
					found = true;
				}
			}

			bBlocked[ndir] = true;
		}//while
	} 
	else found = true;

	// 좌수/우수를 확실히 결정해준다.
	if (found 
		&& m_MoveRule!=MOVE_RULE_NORMAL)
	{
		bool leftWall = bBlocked[(ndir+2) & DIR_MAX_1];
		bool rightWall = bBlocked[(ndir+DIR_MAX-2) & DIR_MAX_1];

		// 둘 다 막혔으면 방향에 따라서.. 사바사바
		if (leftWall && rightWall)
		{
			if (ndir>curDir && ndir<curDir+4
				|| curDir>4 && (ndir>curDir || ndir<curDir-4))
			{
				setMoveRule(MOVE_RULE_RIGHTWALL);
				//cout << "set RightWall : " << (int)curDir << " to " << (int)ndir << " - " << (int)m_BlockedDir << " - " << m_pBody->getName() << endl;
			}
			else
			{
				setMoveRule(MOVE_RULE_LEFTWALL);
				//cout << "set LeftWall : " << (int)curDir << " to " << (int)ndir << " - " << (int)m_BlockedDir << " - " << m_pBody->getName() << endl;
			}
		}
		// 좌수법 적용
		else if (leftWall)
		{
			setMoveRule(MOVE_RULE_LEFTWALL);
			//cout << "set LeftWall : " << (int)curDir << " to " << (int)ndir << " - " << (int)m_BlockedDir << " - " << m_pBody->getName() << endl;
		}
		// 우수법 적용
		else if (rightWall)
		{
			setMoveRule(MOVE_RULE_RIGHTWALL);
			//cout << "set RightWall : " << (int)curDir << " to " << (int)ndir << " - " << (int)m_BlockedDir << " - " << m_pBody->getName() << endl;
		}
		// 벽이 없다면 벽타기 안한다.
		else
		{
			setMoveRule(MOVE_RULE_NORMAL);
		}
	}
	else
	{
		setMoveRule(MOVE_RULE_NORMAL);
	}

	return found;
}

//////////////////////////////////////////////////////////////////////////////
// 벽타고 이동하기
//////////////////////////////////////////////////////////////////////////////

bool MonsterAI::moveWall(ZoneCoord_t ex, ZoneCoord_t ey, ZoneCoord_t& nx, ZoneCoord_t& ny, Dir_t& ndir, bool bLeft)
	throw()
{
	//Zone*       pZone   = m_pBody->getZone();
	//cout << "MoveWall[" << (bLeft? "Left" : "Right") << "] : " << m_pBody->getName() << endl;

	////////////////////////////////////////////////////////////
	// search surrounding tiles
	////////////////////////////////////////////////////////////
	// 우선 목표 방향으로 가볼려고 한다.
	ndir = m_BlockedDir;

	// 다음 좌표
	nx = m_pBody->getX() + dirMoveMask[ndir].x;
	ny = m_pBody->getY() + dirMoveMask[ndir].y;

	m_WallCount++;

	// 목표한 방향으로 갈 수 있는 경우
	bool bCanMove = m_pBody->canMove(nx,ny); 

	// 마스터인 경우에는 바닥에 안 좋은게 없어야 한다. - -; by sigi. 2002.9.12
	/*
	if (bCanMove && m_pBody->isMaster())
	{
		Tile& tile = m_pBody->getZone()->getTile(nx, ny);
		if (tile.hasEffect())
		{
			if (tile.getEffect(Effect::EFFECT_CLASS_ACID_SWAMP)!=NULL
				&& tile.getEffect(Effect::EFFECT_CLASS_GROUND_ATTACK)!=NULL)
			{
			}
			else bCanMove = false;
		}
	}
	*/

	if (bCanMove)
	{
		/*
		Dir_t bestDir;

		////////////////////////////////////////////////////////////
		// (nx, ny)에서 목적지점으로 향하는 최선의 방향을 찾는다.
		////////////////////////////////////////////////////////////
		if (nx < ex) 
		{
			if (ny < ey)      bestDir = RIGHTDOWN;
			else if (ny > ey) bestDir = RIGHTUP;
			else              bestDir = RIGHT;// m_pBody->getY() == ey
		} 
		else if (nx > ex) 
		{
			if (ny < ey)      bestDir = LEFTDOWN;
			else if (ny > ey) bestDir = LEFTUP;
			else              bestDir = LEFT;// m_pBody->getY() == ey
		} 
		else 
		{	
			if (ny < ey)      bestDir = DOWN; // m_pBody->getX() == ex
			else if (ny > ey) bestDir = UP;
			else              bestDir = DIR_NONE; // m_pBody->getY() == ey
		}

		ZoneCoord_t bx = nx + dirMoveMask[bestDir].x;
		ZoneCoord_t by = ny + dirMoveMask[bestDir].y;
		*/

		// 한 칸 이동했을때의
		// best방향이 block이 되어있지 않은 경우에만 벽타기를 그만둔다.
		//if (m_pBody->canMove(bx,by)) 
		{
			// 벽타기를 그만둔다.
			//cout << "FindBest : " << (int)m_BlockedDir << " - " << m_pBody->getName() << endl;
			setMoveRule(MOVE_RULE_NORMAL);
		}

		return true;
	}


	const Dir_t DIR_MAX_1 = DIR_MAX-1;

	Dir_t dirInc, dirWallInc;

	if (bLeft)	
	{
		// 좌수법
		dirInc = 7;		//	+DIR_MAX-1;
		dirWallInc = 2;	// 벽이 있어야하는 방향
	}
	else		
	{
		// 우수법
		dirInc = 1;
		dirWallInc = 6;	// +DIR_MAX-3 벽이 있어야하는 방향
	}

	// 벽이 있어야하는 방향부터 체크
	ndir = (m_pBody->getDir() + dirWallInc) & DIR_MAX_1;
	
	//----------------------------------------------------------
	// 갈려는 방향으로 갈 수 있으면 가면 된다.
	// 
	// 갈 수 없는 이유가 맵에 의한 block이 아닌 경우이면 
	//        벽타기를 그만둔다.
	//----------------------------------------------------------
	for (int i=0; i<DIR_MAX; i++)
	{
		// 다음 좌표
		nx = m_pBody->getX() + dirMoveMask[ndir].x;
		ny = m_pBody->getY() + dirMoveMask[ndir].y;

		if (m_pBody->canMove(nx,ny))
		{
			// 무조건 가버리면 된다.
			// 벽이 있어야 되는 위치
			//Dir_t 		dirWall = (ndir + dirWallInc) & DIR_MAX_1;
			//ZoneCoord_t wallx 	= m_pBody->getX() + dirMoveMask[dirWall].x;
			//ZoneCoord_t wally 	= m_pBody->getY() + dirMoveMask[dirWall].y;

			// 갈 수 없고 creature에 의한 block이 아니면 벽이다.
			//if (!m_pBody->canMove(wallx,wally)
			//	&& !m_pBody->isBlockedByCreature(wallx,wally)) 
			{
				//cout << "FindWay : " << (int)dirWall << " - go : " << (int)ndir << " - " << m_pBody->getName() << endl;
				return true;
			}
		}
		// 다른 creature에 의해서 갈 수 없다면 벽타기를 그만둔다.
		else if (m_pBody->isBlockedByCreature(nx,ny))
		{
			break;
		}

		// 다음 방향
		ndir = (ndir+dirInc) & DIR_MAX_1;
	}

	// 벽타기로 아무곳도 갈 수 없다면 벽타기를 그만둔다. 
	setMoveRule(MOVE_RULE_NORMAL);

	//cout << "Can't go Wall : " << m_pBody->getName() << endl;

	return false;
}


//////////////////////////////////////////////////////////////////////////////
// 행동 함수 (공격 관련)
//////////////////////////////////////////////////////////////////////////////

bool MonsterAI::move(ZoneCoord_t ex, ZoneCoord_t ey)
	throw()
{
	Zone*       pZone   = m_pBody->getZone();

	// 하이드 상태에서는 움직이면 곤란하다...
	//if (m_pBody->isFlag(Effect::EFFECT_CLASS_HIDE))
	//{
	//	m_LastAction = LAST_ACTION_MOVE;
	//	return true;
	//}
	
	// 이동할 위치,방향
	ZoneCoord_t nx, ny; 
	Dir_t ndir;

	// 이동 방법에 따라서 이동할 곳을 결정한다.
	bool found = false;
	switch (m_MoveRule)
	{
		// 보통의 이동
		case MOVE_RULE_NORMAL :
			found = moveNormal(ex, ey, nx, ny, ndir);
		break;

		// 좌수법
		case MOVE_RULE_LEFTWALL :
			found = moveWall(ex, ey, nx, ny, ndir, true);		// true가 left방향이다.
		break;

		// 우수법
		case MOVE_RULE_RIGHTWALL :
			found = moveWall(ex, ey, nx, ny, ndir, false);	// false가 right방향이다.
		break;

		default :
		break;
	}

	// 1. 다음 방향이 발견되었고,
	// 2. 안전 지대가 아니라면... 
	if ((found) && !(pZone->getZoneLevel(nx, ny) & SAFE_ZONE))
	{
		// 내부에서 크리처의 좌표와 방향을 변경하며, 브로드캐스트를 알아서 해준다.
		// 이미 Q(nx,ny)가 계산되어 있으므로 굳이 재계산할 필요는 없다.
		pZone->moveCreature(m_pBody, nx, ny, ndir);
	}

	m_LastAction = LAST_ACTION_MOVE;

	return true;
}

bool MonsterAI::move(Creature* pEnemy, bool bRetreat)
	throw()
{
	__BEGIN_TRY

	Zone*       pZone   = m_pBody->getZone();
	ZoneCoord_t enemyX  = pEnemy->getX();
	ZoneCoord_t enemyY  = pEnemy->getY();
	ZoneCoord_t myX     = m_pBody->getX();
	ZoneCoord_t myY     = m_pBody->getY();
	int         xOffset = enemyX - myX;
	int         yOffset = enemyY - myY;
	ZoneCoord_t ex      = pEnemy->getX();
	ZoneCoord_t ey      = pEnemy->getY();

	// 도망을 칠 경우에는 적의 반대 좌표에 적이 있다고 
	// 생각하고, 움직이면 된다.
	if (bRetreat)
	{
		////////////////////////////////////////////////////////////
		// (enemyX, enemyY)          
		//
		//                  myX, myY
		//
		//                           (ex, ey)
		//                           
		// 적이 있는 포지션(enemyX, enemyY)에서 
		// 대각선 반대 방향으로 도망을 친다.
		////////////////////////////////////////////////////////////
		int xOffset2 = xOffset<<1;	// by sigi
		int yOffset2 = yOffset<<1;	// by sigi

		if (enemyX - xOffset2 < 0) ex = 0;
		else if (enemyX - xOffset2 > (int)pZone->getWidth()) ex = pZone->getWidth();
		else ex = enemyX - xOffset2;

		if (enemyY - yOffset2 < 0) ey = 0;
		else if (enemyY - yOffset2 > (int)pZone->getHeight()) ey = pZone->getHeight();
		else ey = enemyY - yOffset2;

		setMoveRule(MOVE_RULE_NORMAL);	// 정상적인 이동
	}

	return move(ex, ey);

	__END_CATCH
}

bool MonsterAI::flee(Creature* pEnemy)
	throw()
{
	__BEGIN_TRY

	if (m_Panic == 0)
	{
		if (m_Courage == 0)
		{
			m_Panic   = m_PanicMax;
			m_Courage = m_CourageMax;
		}
		else
		{
			m_Courage--;
		}
	}
	else m_Panic--;

	if (m_Panic > 0)
	{
		// 도망친다.
		move(pEnemy, true);
		return true;
	}

	return false;

	__END_CATCH
}

int MonsterAI::useSkill(Creature* pEnemy, SkillType_t SkillType, int ratio) 
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pEnemy != NULL);

	ZoneCoord_t ex = pEnemy->getX();
	ZoneCoord_t ey = pEnemy->getY();
	Distance_t  dist = m_pBody->getDistance(ex , ey);

	// 어떤 행동을 취할 때는 그 행동을 취할 확률이 돌아온다.
	if (rand()%100 >= ratio) return SKILL_FAILED_RATIO;
 
	// [ test code ]
	//	Zone* pZone = m_pBody->getZone();
	// Assert(pZone != NULL);

	//cout << "ZoneID=" << (int)pZone->getZoneID()
    //    << ", MonsterCount=" << (int)pZone->getMonsterCount() << endl;


	//----------------------------------------------------------
	// skill을 사용하기 불가능한 상태라면 
	// 일단 가능한 상태로 만들어야 한다.
	// Directive에 넣어도 되지만, 모든 몹이 동일하기 때문에...
	//
	// Slayer몹/Vampire몹으로 나뉘지 않을까.. 으흠 - -;
	//----------------------------------------------------------
	// Hide상태라면 튀어나와야 한다.
	if (m_pBody->isFlag(Effect::EFFECT_CLASS_HIDE ))
	{
		SkillType = SKILL_UN_BURROW;
	}
	// 박쥐상태라면 다시 변신
	else if (m_pBody->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT ))
	{
		SkillType = SKILL_UN_TRANSFORM;
	}
	// invisible상태라면 풀어야 한다.
	else if (m_pBody->isFlag(Effect::EFFECT_CLASS_INVISIBILITY ))
	{
		SkillType = SKILL_UN_INVISIBILITY;
	}
	// 늑대는 마법쓰면 안되는데.. - -;

	SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
	Assert(pSkillHandler != NULL);

	SkillInfo* pSkillInfo = NULL;

	Timeval delay;

	switch (SkillType)
	{
		////////////////////////////////////////////////////////////
		// 근거리 기술들
		////////////////////////////////////////////////////////////
		case SKILL_ATTACK_MELEE:
		case SKILL_ACID_TOUCH:
		case SKILL_SINGLE_BLOW:
		case SKILL_BLOODY_NAIL:
		case SKILL_TALON_OF_CROW:
			if (dist > m_pBody->getMeleeRange()) return SKILL_FAILED_RANGE;
			pSkillHandler->execute(m_pBody, pEnemy);
			break;
		case SKILL_BLOOD_DRAIN:
			if (!m_pBody->isMaster() && dist > m_pBody->getMeleeRange()) return SKILL_FAILED_RANGE;
			pSkillHandler->execute(m_pBody, pEnemy);
			break;
		////////////////////////////////////////////////////////////
		// 장거리 기술들
		////////////////////////////////////////////////////////////
		case SKILL_ATTACK_ARMS:
		case SKILL_UNTERFELDWEBEL_FIRE:
		case SKILL_FELDWEBEL_FIRE:
			if (dist > m_pBody->getMissileRange()) return SKILL_FAILED_RANGE;
			pSkillHandler->execute(m_pBody, pEnemy);
			break;
		////////////////////////////////////////////////////////////
		// 장거리 기술들 (with delay)
		////////////////////////////////////////////////////////////
		case SKILL_GREEN_POISON:
		case SKILL_YELLOW_POISON:
		case SKILL_DARKBLUE_POISON:
		case SKILL_GREEN_STALKER:
		case SKILL_ACID_BOLT:
		case SKILL_ACID_BALL:
		case SKILL_BLOODY_BALL:
		case SKILL_BLOODY_WAVE:
		case SKILL_BLOODY_MASTER_WAVE:
		case SKILL_BLOODY_WARP:
		case SKILL_PARALYZE:
		case SKILL_DOOM:
		case SKILL_SEDUCTION:
		case SKILL_DEATH:
		case SKILL_DARKNESS:
		case SKILL_BLOODY_KNIFE:
		case SKILL_BLOODY_SPEAR:
		case SKILL_BLOODY_STORM:
		case SKILL_ACID_STORM:
		case SKILL_POISON_STORM:
		case SKILL_HALLUCINATION:
		// 2003.04.13-14 몬스터가 사용할 수 있도록 추가.
		case SKILL_METEOR_STRIKE:
		case SKILL_BLOODY_WALL:
		case SKILL_BLOODY_SNAKE:
		case SKILL_BLOODY_BREAKER:
		case SKILL_ACID_SWAMP:
		case SKILL_POISON_STRIKE:
		case SKILL_ACID_STRIKE:
		case SKILL_HANDS_OF_WISDOM:
		case SKILL_POISONOUS_HANDS:
		case SKILL_BLOODY_ZENITH:
		case SKILL_ACID_ERUPTION:
		case SKILL_ICE_FIELD:

		// 질드레 스킬
		case SKILL_WIDE_ICE_FIELD:
		case SKILL_GLACIER_1:
		case SKILL_GLACIER_2:
		case SKILL_ICE_AUGER:
		case SKILL_ICE_HAIL:
		case SKILL_WIDE_ICE_HAIL:
		case SKILL_ICE_WAVE:
		case SKILL_ICE_LANCE:
		case SKILL_GUN_SHOT_GUIDANCE:
		case SKILL_THROWING_AXE:
		case SKILL_CHOPPING_FIREWOOD:
		case SKILL_CHAIN_THROWING_AXE:
		case SKILL_MULTI_THROWING_AXE:
		case SKILL_CANNONADE:
		case SKILL_AR_ATTACK:
		case SKILL_SMG_ATTACK:
		case SKILL_GRENADE_ATTACK:
		case SKILL_TRASLA_ATTACK:
		case SKILL_PUSCA_ATTACK:
		case SKILL_NOD_COPILA_ATTACK:
		case SKILL_NOD_COPILA_ATTACK_2:

			pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
			Assert(pSkillInfo != NULL);

			if (SkillType == SKILL_GUN_SHOT_GUIDANCE || SkillType == SKILL_ICE_LANCE || SkillType == SKILL_ICE_HAIL )
			{
				// 바보
			}
			else if (dist > pSkillInfo->getRange()) return SKILL_FAILED_RANGE;
			//cout << "useSkill: " << pSkillInfo->getName().c_str() << endl;
			pSkillHandler->execute(m_pBody, pEnemy);
			//cout << "useSkillOK: " << pSkillInfo->getName().c_str() << endl;

			// 미사일 쏘는 속도가 너무 빠르기 때문에 지연시간을 세팅해 준다.
			if (m_pBody->isMaster()
				|| m_pBody->getMonsterType() == 599
				|| m_pBody->getMonsterType() == 764
				|| m_pBody->getMonsterType() == 765
			)		// 마스터는 delay를 좀 줄인다. by sigi. 2002.9.13
			{
				delay.tv_sec  = 0;
				delay.tv_usec = 700000;
			}
			else
			{
				delay.tv_sec  = 1;
				delay.tv_usec = 500000;
			}

			if (SkillType == SKILL_ICE_WAVE || SkillType == SKILL_CHOPPING_FIREWOOD )
			{
				delay.tv_sec  = 2;
				delay.tv_usec = 500000;
			}
			m_pBody->addAccuDelay(delay);
			break;
		////////////////////////////////////////////////////////////
		// 셀프 기술들
		////////////////////////////////////////////////////////////
		case SKILL_HIDE:
		case SKILL_UN_BURROW:
		case SKILL_UN_TRANSFORM:
		case SKILL_TRANSFORM_TO_WOLF:
		case SKILL_TRANSFORM_TO_BAT:
		case SKILL_INVISIBILITY:
		case SKILL_UN_INVISIBILITY:
		case SKILL_DUPLICATE_SELF:
			pSkillHandler->execute(m_pBody);

			// delay설정
			delay.tv_sec  = 1;
			delay.tv_usec = 500000;
			m_pBody->addAccuDelay(delay);
			break;

		case SKILL_SUMMON_MONSTERS:
			if (!checkPossibleSummonMonsters(m_pBody, NULL) && !m_pBody->isMaster() ) return SKILL_FAILED_RANGE;
			
			pSkillHandler->execute(m_pBody);

			// delay설정
			delay.tv_sec  = 1;
			delay.tv_usec = 500000;
			m_pBody->addAccuDelay(delay);
			break;

		case SKILL_CRITICAL_GROUND:
			pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
			Assert(pSkillInfo != NULL);

			//cout << "useSkill: " << pSkillInfo->getName().c_str() << endl;
			pSkillHandler->execute(m_pBody);
			//cout << "useSkillOK: " << pSkillInfo->getName().c_str() << endl;

			// delay설정
			delay.tv_sec  = 1;
			delay.tv_usec = 0;
			m_pBody->addAccuDelay(delay);
			break;

		case SKILL_PLAYING_WITH_FIRE:
		case SKILL_SUMMON_MIGA_ATTACK:
		case SKILL_SELF_DESTRUCTION:
			pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
			Assert(pSkillInfo != NULL);

			//cout << "useSkill: " << pSkillInfo->getName().c_str() << endl;
			pSkillHandler->execute(m_pBody);
			//cout << "useSkillOK: " << pSkillInfo->getName().c_str() << endl;

			// delay설정
			delay.tv_sec  = 3;
			delay.tv_usec = 0;
			m_pBody->addAccuDelay(delay);
			break;

		case SKILL_GORE_GLAND_FIRE:
			pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
			Assert(pSkillInfo != NULL);

			if (dist > pSkillInfo->getRange()) return SKILL_FAILED_RANGE;
			pSkillHandler->execute(m_pBody, pEnemy);

			break;

		////////////////////////////////////////////////////////////
		// QuickFire - -;
		////////////////////////////////////////////////////////////
		case SKILL_QUICK_FIRE:
			pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
			Assert(pSkillInfo != NULL);

			if (dist > pSkillInfo->getRange()) return SKILL_FAILED_RANGE;
			pSkillHandler->execute(m_pBody, pEnemy);
			
			break;


		////////////////////////////////////////////////////////////
		// 지원되지 않는 기술
		////////////////////////////////////////////////////////////
		default:
			cerr << "MonsterAI::useSkill() : Try to use unavailable skill!" << endl;
			Assert(false);
			break;
	}

	m_LastAction = LAST_ACTION_SKILL;

	return 0;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 행동 패턴 선택 함수
//////////////////////////////////////////////////////////////////////////////

void MonsterAI::deal(Creature* pEnemy, const Timeval& currentTime)
	throw()
{
	__BEGIN_TRY

	Assert(pEnemy != NULL);	// by sigi

	// 다이렉티브 리스트를 얻어낸다.
	const list<Directive*>& directiveList = m_pDirectiveSet->getDirectives();
	int rValue = 0;
	int parameter = 0;
	int ratio = 0;

	// 다이랙티브 리스트를 하나씩 검색하면서,
	// 조건이 만족되는 것이 있는지 체크한다.
	list<Directive*>::const_iterator itr = directiveList.begin();
	for (; itr != directiveList.end(); itr++)
	{
		Directive* pDirective = *itr;

		// 조건이 만족하는 다이렉티브가 있다면,
		// 그에 해당하는 액션을 수행한다.
		if (checkDirective(pDirective, pEnemy))
		{
			switch (pDirective->getAction())
			{
				// 적에게 다가간다.
				case DIRECTIVE_ACTION_APPROACH:
					__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_APPROACH");
					approach(pEnemy);
					__END_PROFILE_MONSTER("DIRECTIVE_ACTION_APPROACH");
					//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] approach" << endl;
					break;

				// 적으로부터 도망친다.
				case DIRECTIVE_ACTION_FLEE:
					__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_FLEE");
					if (!flee(pEnemy))
					{
						setMoveRule(MOVE_RULE_NORMAL);	// 정상적인 이동
						rValue = useSkill(pEnemy, SKILL_ATTACK_MELEE, 100);
						if (rValue != 0) approach(pEnemy);
						//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] !free" << endl;
					}
					else
					{
						//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] free" << endl;
					}
					__END_PROFILE_MONSTER("DIRECTIVE_ACTION_FLEE");
					break;

				// 스킬을 사용한다. 적을 공격하거나, 셀프 기술...
				case DIRECTIVE_ACTION_USE_SKILL:
					__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_USE_SKILL");
					// Block Head 걸려있을때는 스킬을 사용할 수 없다.
					if (m_pBody->isFlag(Effect::EFFECT_CLASS_BLOCK_HEAD ) || m_pBody->isFlag(Effect::EFFECT_CLASS_TENDRIL ) ) continue;
					parameter = pDirective->getParameter();
					ratio     = pDirective->getRatio();
					rValue    = useSkill(pEnemy, (SkillType_t)parameter, ratio);
					__END_PROFILE_MONSTER("DIRECTIVE_ACTION_USE_SKILL");

					if (rValue != 0) 
					{
						//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] !" << SkillTypes2String[parameter] << endl;
						continue;
					}

					//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] " << SkillTypes2String[parameter] << endl;


					setMoveRule(MOVE_RULE_NORMAL);	// 정상적인 이동

					break;
				
				// 적을 포기한다.
				case DIRECTIVE_ACTION_FORGET:
					__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_FORGET");
					// by sigi. 2002.10.7
					if (!m_pBody->getEnemies().empty())
						m_pBody->getEnemies().pop_front();

					setMoveRule(MOVE_RULE_NORMAL);	// 정상적인 이동
					//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] forget" << endl;
					__END_PROFILE_MONSTER("DIRECTIVE_ACTION_FORGET");

					break;

				// 새로운 PrimaryEnemy를 찾아서 체크한다.
				case DIRECTIVE_ACTION_CHANGE_ENEMY :
					{
						ratio = pDirective->getParameter();

						// 적을 안 바꾼다.
						if (rand()%100 >= ratio)
						{
							//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] !changeEnemy" << endl;
							continue;
						}

						__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_CHANGE_ENEMY");
						
						Creature* pNewEnemy = m_pBody->getPrimaryEnemy();
						if (pNewEnemy!=NULL)
						{
							pEnemy = pNewEnemy;
						}
						else
						{
							// 없다면.. checkFindWeakEnemy에서 delete하고 
							// 새로운 적이 추가가 되지 않았다는 의미이다.
							// 기존의 적을 다시 추가한다.
							// by sigi. 2002.10.7
							if (m_pBody->getEnemies().empty())
							{
								m_pBody->addEnemy(pEnemy);
							}
						}

						__END_PROFILE_MONSTER("DIRECTIVE_ACTION_CHANGE_ENEMY");

						// 다음 AI를 게속 진행한다.
						//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] changeEnemy" << endl;
						continue;
					}
					break;

				// 근처의 어딘가로 이동한다.
				case DIRECTIVE_ACTION_MOVE_RANDOM :
					{
						ratio = pDirective->getParameter();

						// 어딘가로 이동하지 않는다.
						if (rand()%100 >= ratio)
						{
							//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] !moveRandom" << endl;
							continue;
						}

						ZoneCoord_t x;
						ZoneCoord_t y;
						TPOINT p;

						__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_MOVE_RANDOM_GET_SAFE_TILE");

						x = m_pBody->getX();
						y = m_pBody->getY();

						p = getSafeTile(m_pBody->getZone(), x, y);

						__END_PROFILE_MONSTER("DIRECTIVE_ACTION_MOVE_RANDOM_GET_SAFE_TILE");

						// 자리가 없다면.. 걍 포기 - -;
						if (p.x==-1)
						{
							///cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] moveRandom : no position" << endl;
							continue;
						}

						__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_MOVE_RANDOM_MOVE");

						ZoneCoord_t x1 = p.x;//x + rand()%7 - 3;
						ZoneCoord_t y1 = p.y;//y + rand()%7 - 3;
						
						if (x!=x1 || y!=y1)
							move(x1, y1);

						__END_PROFILE_MONSTER("DIRECTIVE_ACTION_MOVE_RANDOM_MOVE");
						//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] moveRandom" << endl;
					}
					break;

				// 잠시 대기한다.
				case DIRECTIVE_ACTION_WAIT :
					{
						__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_WAIT");
						Timeval delay;
						delay.tv_sec  = 2;
						delay.tv_usec = 0;
						m_pBody->addAccuDelay(delay);
						__END_PROFILE_MONSTER("DIRECTIVE_ACTION_WAIT");
						//cout << "[" << (int)currentTime.tv_sec << "." << (int)currentTime.tv_usec << "] wait" << endl;
					}
					break;

				case DIRECTIVE_ACTION_FAST_FLEE :
					{
						bool result = false;

						__BEGIN_PROFILE_MONSTER("DIRECTIVE_ACTION_FAST_FLEE");
						int myX = m_pBody->getX();
						int myY = m_pBody->getY();

						int nmX = pEnemy->getX();
						int nmY = pEnemy->getY();

						int diffX = myX - nmX;
						int diffY = myY - nmY;

						float ratio = 5.0 / (ABS(diffX) + ABS(diffY));

						int newX = (int)(myX + diffX * ratio);
						int newY = (int)(myY + diffY * ratio);

						if (isValidZoneCoord(m_pBody->getZone(), newX, newY ) )
							result = m_pBody->getZone()->moveFastMonster(m_pBody, myX, myY, newX, newY, SKILL_RAPID_GLIDING);

/*						if (newX > 0 ) continue;
						if (newY < 0 ) continue;
						if (newX >= m_pBody->getZone()->getWidth() ) continue;
						if (newY >= m_pBody->getZone()->getHeight() ) continue;

						if (!m_pBody->getZone()->moveFastMonster(m_pBody, myX, myY, newX, newY, SKILL_RAPID_GLIDING ) ) continue;*/
						__END_PROFILE_MONSTER("DIRECTIVE_ACTION_FAST_FLEE");

						if (!result ) continue;
					}
					break;
				case DIRECTIVE_ACTION_SAY:
				{
					parameter = pDirective->getParameter();
					GCSay gcSay;
					gcSay.setObjectID(m_pBody->getObjectID());
					gcSay.setMessage(g_pStringPool->getString(parameter ));
					gcSay.setColor(0x00ffffff);
					m_pBody->getZone()->broadcastPacket(m_pBody->getX(), m_pBody->getY(), &gcSay);
				}
			}
			break;
		}
	}

	__BEGIN_PROFILE_MONSTER("MAI_POST_DEAL");

	// 이번 턴에 어떤 행동을 했느냐에 따라 행동 지연 시간을 세팅해준다.
	switch (m_LastAction)
	{
		case LAST_ACTION_NONE:
		case LAST_ACTION_MOVE:
			setDelay(currentTime);
			break;
		case LAST_ACTION_SKILL:
			setAttackDelay(currentTime);
			break;
	}

	// 행동 변수를 새로 세팅해 준다.
	m_LastAction = LAST_ACTION_NONE;
	
	// 도망에 관한 변수를 확률적으로 새로 세팅해준다.
	if ((rand() & 0x0000007F) > 64)	//%100 > 50)
	{
		if (m_bDamaged)
		{
			m_bDamaged = false;
			m_Panic    = m_PanicMax;
			m_Courage  = m_CourageMax;
		}
	}

	__END_PROFILE_MONSTER("MAI_POST_DEAL");

	__END_CATCH
}

// 죽을 때의 행동을 취한다.
void MonsterAI::actDeadAction(Creature* pEnemy) 
	throw()
{
	__BEGIN_TRY

	// MonsterAI의 한계로 인해,
	// 적이 없을 경우에 행할 수 있는 액션에는 한계가 있다.
	if (pEnemy != NULL)
	{
		// 다이렉티브 리스트를 얻어낸다.
		const list<Directive*>& directiveList = m_pDirectiveSet->getDeadDirectives();
		bool bContinue = true;

		// 다이랙티브 리스트를 하나씩 검색하면서,
		// 조건이 만족되는 것이 있는지 체크한다.
		list<Directive*>::const_iterator itr = directiveList.begin();
		for (; itr != directiveList.end() && bContinue; itr++)
		{
			Directive* pDirective = *itr;

			if (pDirective->getAction() == DIRECTIVE_ACTION_USE_SKILL)
			{
				SkillType_t SkillType = pDirective->getParameter();
				int         ratio     = pDirective->getRatio();

				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);

				if ((rand()%ratio) < 100)
				{
					switch (SkillType)
					{
						case SKILL_GREEN_POISON:
						case SKILL_LAND_MINE_EXPLOSION:
						case SKILL_PLEASURE_EXPLOSION:
						case SKILL_CLAYMORE_EXPLOSION:
						case SKILL_SUMMON_MONSTERS:
							pSkillHandler->execute(m_pBody);
							bContinue = false;
							break;
						default:
							Assert(false);
							break;
					}
				}
				else
				{
					// 기술 사용이 확률 체크로 인해 실패했다면 다음 액션으로 넘어간다.
					continue;
				}
			}
			else if (pDirective->getAction() == DIRECTIVE_ACTION_SAY)
			{
				int parameter = pDirective->getParameter();
				GCSay gcSay;
				gcSay.setObjectID(m_pBody->getObjectID());
				gcSay.setMessage(g_pStringPool->getString(parameter ));
				gcSay.setColor(0x00ffffff);
				m_pBody->getZone()->broadcastPacket(m_pBody->getX(), m_pBody->getY(), &gcSay);
			}
		}
	}

	__END_CATCH
}

void MonsterAI::setDelay(const Timeval& currentTime)
	throw()
{
	__BEGIN_TRY

	// 기존에 구한 시간을 이용한다. 계산 줄일려고. - -; by sigi. 2002.5.6
	//Timeval currentTime;
	//getCurrentTime(currentTime);

	int delay    = m_pBody->getDelay();

	if (m_pBody->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
	{
		delay = 200; // 250
	}
	else if (m_pBody->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF))
	{
		delay = 300; // 375
	}

	int modifier = (rand()%41)-20;

	delay = delay*1000;
	delay = delay + delay*modifier/100;

	Timeval nexttime;
	nexttime.tv_sec  = delay/1000000;
	nexttime.tv_usec = delay%1000000;

	nexttime = nexttime + m_pBody->getAccuDelay();

	m_pBody->clearAccuDelay();

	if (m_pBody->isFlag(Effect::EFFECT_CLASS_ICE_FIELD_TO_CREATURE ) 
	||	m_pBody->isFlag(Effect::EFFECT_CLASS_JABBING_VEIN ) )
	{
		m_pBody->setNextTurn(currentTime + nexttime + nexttime);
	}
	else
	{
		m_pBody->setNextTurn(currentTime + nexttime);
	}

	/*
	Timeval currentTime;
	Timeval delay;

	getCurrentTime(currentTime);

	delay.tv_sec  = m_pBody->getDelay()/1000;
	delay.tv_usec = (m_pBody->getDelay()%1000)*1000 + rand()%200000;

	delay = delay + m_pBody->getAccuDelay();

	m_pBody->clearAccuDelay();
	m_pBody->setNextTurn(currentTime + delay);
	*/
	
	/*
	Timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = m_pBody->getDelay()* 1000 + rand() % 200000;
	m_pBody->setNextTurn(m_pBody->getNextTurn() + delay);
	*/

	__END_CATCH
}

void MonsterAI::setAttackDelay(const Timeval& currentTime)
	throw()
{
	__BEGIN_TRY

	// 기존에 구한 시간을 이용한다. 계산 줄일려고. - -; by sigi. 2002.5.6
	//Timeval currentTime;
	//getCurrentTime(currentTime);

	int delay    = m_pBody->getAttackDelay();
	int modifier = (rand()%21);

	delay = delay*1000;
	delay = delay + delay*modifier/100;

	Timeval nexttime;
	nexttime.tv_sec  = delay/1000000;
	nexttime.tv_usec = delay%1000000;

	nexttime = nexttime + m_pBody->getAccuDelay();

	m_pBody->clearAccuDelay();

	if (m_pBody->isFlag(Effect::EFFECT_CLASS_ICE_OF_SOUL_STONE ) 
		||	m_pBody->getZone()->getTile(m_pBody->getX(),m_pBody->getY()).getEffect(Effect::EFFECT_CLASS_FURY_OF_GNOME) != NULL )
	{
		m_pBody->setNextTurn(currentTime + nexttime + nexttime);
	}
	else
	{
		m_pBody->setNextTurn(currentTime + nexttime);
	}

	
	/*
	Timeval currentTime;
	Timeval delay;

	getCurrentTime(currentTime);

	delay.tv_sec  = m_pBody->getAttackDelay()/1000;
	delay.tv_usec = (m_pBody->getAttackDelay()%1000)*1000 + rand()%200000;

	delay = delay + m_pBody->getAccuDelay();

	m_pBody->clearAccuDelay();
	m_pBody->setNextTurn(currentTime + delay);
	*/

	/*
	Timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = m_pBody->getAttackDelay()* 1000 + rand() % 200000;
	m_pBody->setNextTurn(m_pBody->getNextTurn() + delay);
	*/

	__END_CATCH
}




bool checkEnemyRangeMelee(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	Distance_t dist = pMonster->getDistance(pEnemy->getX(), pEnemy->getY());
	if (dist <= pMonster->getMeleeRange()) return true;
	return false;
}

bool checkEnemyRangeMissile(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	Distance_t dist = pMonster->getDistance(pEnemy->getX(), pEnemy->getY());
	if (dist > pMonster->getMeleeRange() && dist <= pMonster->getSight()) return true;
	return false;
}

bool checkEnemyRangeInMissile(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	Distance_t dist = pMonster->getDistance(pEnemy->getX(), pEnemy->getY());
	if (dist <= pMonster->getSight()) return true;
	return false;
}

bool checkEnemyRangeClose(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	Distance_t dist = pMonster->getDistance(pEnemy->getX(), pEnemy->getY());
	if (dist <= 1) return true;
	return false;
}


bool checkEnemyRangeOutOfSight(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	Distance_t dist = pMonster->getDistance(pEnemy->getX(), pEnemy->getY());
	if (dist > pMonster->getSight()) return true;
	return false;
}

bool checkEnemyDying(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;

	HP_t EnemyCurHP = 0;
	HP_t EnemyMaxHP = 0;

	if (pEnemy->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pEnemy);
		EnemyCurHP = pSlayer->getHP(ATTR_CURRENT);
		EnemyMaxHP = pSlayer->getHP(ATTR_MAX);
	}
	else if (pEnemy->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pEnemy);
		EnemyCurHP = pVampire->getHP(ATTR_CURRENT);
		EnemyMaxHP = pVampire->getHP(ATTR_MAX);
	}
	else if (pEnemy->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pEnemy);
		EnemyCurHP = pOusters->getHP(ATTR_CURRENT);
		EnemyMaxHP = pOusters->getHP(ATTR_MAX);
	}
	else if (pEnemy->isMonster())
	{
		Monster* pEnemyMonster = dynamic_cast<Monster*>(pEnemy);
		EnemyCurHP = pEnemyMonster->getHP(ATTR_CURRENT);
		EnemyMaxHP = pEnemyMonster->getHP(ATTR_MAX);
	}

	if (EnemyCurHP*5 < EnemyMaxHP) return true;

	return false;
}

bool checkEnemyNotBloodDrained(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (pEnemy->isVampire()) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN)) return true;
	return false;
}

bool checkEnemyNotGreenPoisoned(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (pEnemy->isVampire()) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_POISON)) return true;
	return false;
}

bool checkEnemyNotYellowPoisoned(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (pEnemy->isVampire()) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) return true;
	return false;
}

bool checkEnemyNotDarkbluePoisoned(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (pEnemy->isVampire()) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_DARKBLUE_POISON)) return true;
	return false;
}

bool checkEnemyNotGreenStalkered(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (pEnemy->isVampire()) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_GREEN_STALKER)) return true;
	return false;
}

bool checkEnemyNotParalyzed(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_PARALYZE)) return true;
	return false;
}

bool checkEnemyNotDoomed(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_DOOM)) return true;
	return false;
}

bool checkEnemyNotBlinded(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	return false;
}

bool checkEnemyNotInDarkness(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (pEnemy->isVampire()) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_DARKNESS)) return true;
	return false;
}

bool checkEnemyNotSeduction(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_SEDUCTION)) return true;
	return false;
}

bool checkEnemyNotDeath(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_DEATH)) return true;
	return false;
}

bool checkImOK(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	HP_t CurHP = pMonster->getHP(ATTR_CURRENT);
	HP_t MaxHP = pMonster->getHP(ATTR_MAX);
	if (CurHP > MaxHP/3) return true;
	return false;
}

bool checkImDying(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	HP_t CurHP = pMonster->getHP(ATTR_CURRENT);
	HP_t MaxHP = pMonster->getHP(ATTR_MAX);
	if (CurHP*4 < MaxHP) return true;
	return false;
}

bool checkImDamaged(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	return pMonster->getBrain()->getDamaged();
}

bool checkImHiding(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	return pMonster->isFlag(Effect::EFFECT_CLASS_HIDE);
}

bool checkImWolf(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	return pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);
}

bool checkImBat(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	return pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);
}

bool checkImInvisible(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	return pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY);
}


bool checkImWalkingWall(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	MonsterAI* pAI = pMonster->getBrain();

	Assert(pAI != NULL);

	if (pAI->getWallCount() > 3 
		&& (pAI->getMoveRule()==MOVE_RULE_LEFTWALL 
			|| pAI->getMoveRule()==MOVE_RULE_RIGHTWALL))
	{
		return true;
	}

	return false;
}

bool checkTimingBloodDrain(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	// 몬스터가 slayer가 아니라도 흡혈하게 수정. by sigi. 2002.9.14
	if (pEnemy == NULL
		// Slayer가 아니면 흡혈하지 않는다.
		|| pEnemy->isNPC()
		// 이미 흡혈당했으면 흡혈하지 않는다.
		|| pEnemy->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN)
		// 무적. 흡혈 면역. by sigi. 2002.9.14
		|| pEnemy->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE)
		|| pEnemy->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN)) 
	{
		return false;
	}

	// 흡혈거리가 되는지 확인한다.
	Distance_t dist = pMonster->getDistance(pEnemy->getX(), pEnemy->getY());
	if (dist > pMonster->getMeleeRange()) return false;

	HP_t EnemyCurHP = 0;
	HP_t EnemyMaxHP = 0;

	if (pEnemy->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pEnemy);
		EnemyCurHP = pSlayer->getHP(ATTR_CURRENT);
		EnemyMaxHP = pSlayer->getHP(ATTR_MAX);
	}
	else if (pEnemy->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pEnemy);
		EnemyCurHP = pVampire->getHP(ATTR_CURRENT);
		EnemyMaxHP = pVampire->getHP(ATTR_MAX);
	}
	else if (pEnemy->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pEnemy);
		EnemyCurHP = pOusters->getHP(ATTR_CURRENT);
		EnemyMaxHP = pOusters->getHP(ATTR_MAX);
	}
	else if (pEnemy->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pEnemy);
		EnemyCurHP = pMonster->getHP(ATTR_CURRENT);
		EnemyMaxHP = pMonster->getHP(ATTR_MAX);
	}

	// HP가 1/5이상 남았으면 흡혈하지 않는다.
	if (EnemyCurHP*5 >= EnemyMaxHP) return false;

	// 마침내... 흡혈한다~
	return true;

}

bool checkTimingMasterBloodDrain(Monster* pMonster, Creature* pEnemy)
{
	// 20% 체크
	// 계산 자체가 빡시므로..
	//if (rand()%100 > 10)
	//	return false;

	Assert(pMonster != NULL);

/*	if ((!pMonster->isMaster()
#ifdef __UNDERWORLD__
		&& pMonster->getMonsterType() != 599
#endif
		)
		|| pEnemy == NULL)*/
	if (pEnemy == NULL )
	{
		return false;
	}

	int masterHPPercent = pMonster->getHP(ATTR_CURRENT)*100/pMonster->getHP(ATTR_MAX);

	// 흡혈 확률
	//int startHPPercent 	= 70,	startBDPercent 	= 10;
	//int endHPPercent 	= 30, 	endBDPercent 	= 30;
	int startHPPercent 	= g_pVariableManager->getMasterBloodDrainStartHP();
	int startBDPercent 	= g_pVariableManager->getMasterBloodDrainStartBD();
	int endHPPercent 	= g_pVariableManager->getMasterBloodDrainEndHP();	
	int endBDPercent 	= g_pVariableManager->getMasterBloodDrainEndBD();

	// HP가 70% 이상이면 흡혈하지 않는다.
	if (masterHPPercent >= startHPPercent)
		return false;

	int ratio = rand()%100;

	// HP가 30% 이하이면.. 30%의 확률로 흡혈한다.
	if (masterHPPercent <= endHPPercent)
	{
		return ratio < endBDPercent;
	}

	// HP가 30~70%이면 10~30%의 확률로 흡혈한다.
	int maxBDPercent = max(startBDPercent, endBDPercent);
	int gapHPPercent = startHPPercent - endHPPercent;
	int gapBDPercent = abs(endBDPercent - startBDPercent);

	//int permitRatio = maxBDPercent - (masterHPPercent-endHPPercent)/2;
	int permitRatio = maxBDPercent - gapBDPercent * (masterHPPercent-endHPPercent) / gapHPPercent;

	return ratio < permitRatio;

	/*
	if (masterHPPercent < 3 || masterHPPercent > 70)
	{
		return false;
	}
	*/

	// 아무나 흡혈할 수 있으므로.. - -;
	//return true;

	/*
	int x = pEnemy->getX();
	int y = pEnemy->getY();
	int Splash = 30; // 그냥 30마리만 체크한다.
	int range = 3; // 7x7   //5;	// 11x11
	list<Creature*> creatureList;
	getSplashVictims(pMonster->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

	list<Creature*>::iterator itr = creatureList.begin();
	for (; itr != creatureList.end(); itr++)
	{
		Creature* pTargetCreature = (*itr);
		Assert(pTargetCreature != NULL);
	
		if (pMonster!=pTargetCreature
			&& pTargetCreature->isNPC()
			// 이미 흡혈당했으면 흡혈하지 않는다. 마스터가 이런거 따지겠나 싶어서 뺏다.
			//&& pTargetCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN)
			// 무적. 흡혈 면역. by sigi. 2002.9.14
			&& pTargetCreature->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE)
			&& pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN)) 
		{
			HP_t EnemyCurHP = 0;
			HP_t EnemyMaxHP = 0;

			if (pTargetCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
				EnemyCurHP = pSlayer->getHP(ATTR_CURRENT);
				EnemyMaxHP = pSlayer->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pTargetCreature);
				EnemyCurHP = pVampire->getHP(ATTR_CURRENT);
				EnemyMaxHP = pVampire->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				EnemyCurHP = pMonster->getHP(ATTR_CURRENT);
				EnemyMaxHP = pMonster->getHP(ATTR_MAX);
			}
	
			// 체력 50% 미만은 흡혈당한다
			if (EnemyCurHP*2 < EnemyMaxHP) 
				return true;
		}
	}
	*/

	return true;

}

//----------------------------------------------------------------------
//
// bool checkMasterSummonTiming(Monster* pMonster, Creature* pEnemy)
//
//----------------------------------------------------------------------
// 소환 기술을 쓰게 할려고 하는데..
// 현재 존이 마스터 레어이고.. 
// 다른 몹이 없어야 한다.
//----------------------------------------------------------------------
bool checkMasterSummonTiming(Monster* pMonster, Creature* pEnemy)
{
	//cout << "checkMasterSummonTiming: ";

	Assert(pMonster != NULL);

	// 마스터가 아니면 소용없다.
	if (!pMonster->isMaster())
		//|| !pMonster->hasNextMonsterSummonInfo())
	{
		//cout << "not Master" << endl;
		return false;
	}

	// 마스터가 있는 존이 마스터레어인지 확인한다.
	Zone* pZone = pMonster->getZone();
	Assert(pZone!=NULL);

	// 마스터 레어가 아니면 의미없다.
	if (!pZone->isMasterLair())
	{
		//cout << "not MasterLair" << endl;
		return false;
	}

	MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
	Assert(pMasterLairManager!=NULL);

	// 아직 마스터가 싸우는 상태가 아니고
	// 존에 마스터 이외의 몬스터가 없는 경우 소환할 수 있다.
	bool bSummonTiming = !pMasterLairManager->isMasterReady() && 
						pZone->getMonsterManager()->getSize() <= 1;

	/*
	if (bSummonTiming)
		cout << "Master Not Ready" << endl;
	else
		cout << "Master Ready" << endl;
		*/

	return bSummonTiming;
}

//----------------------------------------------------------------------
//
// bool checkMasterNotReady(Monster* pMonster, Creature* pEnemy)
//
//----------------------------------------------------------------------
bool checkMasterNotReady(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	// 마스터가 아니면 소용없다.
	if (!pMonster->isMaster())
	{
		return false;
	}

	// 마스터가 있는 존이 마스터레어인지 확인한다.
	Zone* pZone = pMonster->getZone();
	Assert(pZone!=NULL);

	// 마스터 레어가 아니면 의미없다.
	if (!pZone->isMasterLair())
	{
		return false;
	}

	MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
	Assert(pMasterLairManager!=NULL);

	// 아직 마스터가 싸우는 상태가 아니고
	// 존에 마스터 이외의 몬스터가 없는 경우 소환할 수 있다.
	return !pMasterLairManager->isMasterReady();
}

//----------------------------------------------------------------------
//
// bool checkImInBadPosition(Monster* pMonster, Creature* pEnemy)
//
//----------------------------------------------------------------------
// 현재 위치가 안 좋은 곳인가?
//
// pMonster가 있는 타일에 AcidSwamp이 뿌려져 있는 경우
//----------------------------------------------------------------------
bool checkImInBadPosition(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster!=NULL);

	Zone* pZone = pMonster->getZone();
	Assert(pZone!=NULL);

	Tile& rTile = pZone->getTile(pMonster->getX(), pMonster->getY());

	// 무적 상태가 아니고
	if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE)

			// Acid 면역이 아니고 바닥에 AcidSwap이 깔려있다면 안 좋지. - -;
		&& (!pMonster->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_ACID)
				&& rTile.getEffect(Effect::EFFECT_CLASS_ACID_SWAMP)!=NULL

			|| rTile.getEffect(Effect::EFFECT_CLASS_BLOODY_WALL)!=NULL
			|| rTile.getEffect(Effect::EFFECT_CLASS_GROUND_ATTACK)!=NULL)
		)
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
//
// bool checkFindWeakEnemy(Monster* pMonster, Creature* pEnemy)
//
//----------------------------------------------------------------------
// 더 약한 적을 찾을 수 있나?
//
// pEnemy의 HP가 100이상이고 HP percentage가 60% 이상이라면 
// 다른 약한 적을 함 찾아본다.
//----------------------------------------------------------------------
bool checkFindWeakEnemy(Monster* pMonster, Creature* pEnemy)
{
	// 일단
	//return false;

	try
	{
		if (pEnemy==NULL) return false;

		Assert(pMonster!=NULL);

		Zone* pZone = pMonster->getZone();
		Assert(pZone!=NULL);

		int strongValue = getStrongValue(pEnemy);

		if (strongValue==0) return false;

		// 현재 적은 좀 쎄다..라고 판단을 하고. --;
		// 새로운 약한 적을 찾는다.
		Creature* pWeakestCreature = NULL;

		// 주위 검색
		ZoneCoord_t cx = pMonster->getX();
		ZoneCoord_t cy = pMonster->getY();;
		ZoneCoord_t ix = 0;
		ZoneCoord_t iy = 0;
		ZoneCoord_t endx = 0;
		ZoneCoord_t endy = 0;

		// 몬스터 시야 범위에서 찾는다.
		Sight_t sight = pMonster->getSight();	

		endx = min(pZone->getWidth() - 1, cx + sight + 1);
		endy = min(pZone->getHeight() - 1, cy + sight  + 1);

		for (ix =  max(0, cx - sight - 1); ix <= endx ; ix++) 
		{
			for (iy = max(0, cy - sight - 1); iy <= endy ; iy++) 
			{
				Tile& rTile = pZone->getTile(ix, iy);

				// 타일에 크리처가 있는 경우에만
				if (rTile.hasCreature()) 
				{
					const list<Object*> & objectList = rTile.getObjectList();

					for (list<Object*>::const_iterator itr = objectList.begin() ; 
						itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; 
						itr++) 
					{
						Creature* pCreature = dynamic_cast<Creature*>(*itr);		
						Assert(pCreature != NULL);

						// pMonster, pEnemy가 아니라면..
						// Player라면 공격하게 된다.
						if (pCreature != pMonster 
							&& pCreature != pEnemy
							&& pCreature->isPC()
							&& pMonster->isRealEnemy(pCreature))
						{
							int checkStrongValue = getStrongValue(pCreature);

							// 더 약한넘을 pWeakestCreature로 임명~한다
							if (checkStrongValue < strongValue)
							{
								pWeakestCreature = pCreature;
								strongValue = checkStrongValue;
							}
						} 
					}
				}
			}
		}

		// 젤 약한넘을 찾은 경우..
		if (pWeakestCreature!=NULL)
		{
			pMonster->deleteAllEnemy();
			pMonster->addEnemy(pWeakestCreature);

			return true;
		}
		else
		{
		}

	} catch (Throwable& t) {
		// 모든 exception을 무시한다.
		filelog("monsterAIBug.txt", "%s", t.toString().c_str());
	}

	return false;
}

bool checkEnemyNotHallucination(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	if (pEnemy == NULL) return false;
	if (!pEnemy->isFlag(Effect::EFFECT_CLASS_HALLUCINATION)) return true;
	return false;
}

bool checkTimingDuplicateSelf(Monster* pMonster, Creature* pEnemy)
{
	Assert(pMonster != NULL);

	// 마스터가 아니면 소용없다.
	if (!pMonster->isMaster())
	{
		return false;
	}

	// 마스터가 있는 존이 마스터레어인지 확인한다.
	Zone* pZone = pMonster->getZone();
	Assert(pZone!=NULL);

	/*
	// 마스터 레어가 아니면 의미없다.
	if (!pZone->isMasterLair())
	{
		return false;
	}
	*/

	HP_t currentHP = pMonster->getHP(ATTR_CURRENT);
	HP_t maxHP = pMonster->getHP(ATTR_MAX);

	// HP가 70%가 넘으면 사용안한다.
	if (currentHP*100/maxHP > 70)
	{
		return false;
	}

	// 12마리 이상이면 더 소환 안한다.
	if (pZone->getMonsterManager()->getSize() > 12)
	{
		return false;
	}

	return true;
}

//----------------------------------------------------------------------
//
// bool checkPossibleSummonMonsters(Monster* pMonster, Creature* pEnemy)
//
//----------------------------------------------------------------------
// 소환 기술을 쓰게 할려고 하는데..
//----------------------------------------------------------------------
bool checkPossibleSummonMonsters(Monster* pMonster, Creature* pEnemy)
{
	//cout << "checkMasterSummonTiming: ";

	Assert(pMonster != NULL);

	return pMonster->hasNextMonsterSummonInfo();
}

bool checkEnemyTileNotAcidSwamp(Monster* pMonster, Creature* pEnemy)
{
	Zone* pZone = pEnemy->getZone();
	Assert(pZone != NULL);

	Tile& rTile = pZone->getTile(pEnemy->getX(), pEnemy->getY());
	if (rTile.getEffect(Effect::EFFECT_CLASS_ACID_SWAMP ) == NULL ) return true;

	return false;
}

bool checkEnemyOnAir(Monster* pMonster, Creature* pEnemy)
{
	if (pEnemy == NULL ) return false;
	if (pEnemy->getMoveMode() == Creature::MOVE_MODE_FLYING ) return true;
	return false;
}

bool checkEnemyOnSafeZone(Monster* pMonster, Creature* pEnemy)
{
	if (pEnemy==NULL ) return false;
	return ((pEnemy->getZone()->getZoneLevel(pEnemy->getX(), pEnemy->getY() ) & SAFE_ZONE ) != 0);
}

bool checkCanAttackThrowingAxe(Monster* pMonster, Creature* pEnemy)
{
	if (pEnemy==NULL ) return false;
	Dir_t dir = getDirection(pMonster->getX(), pMonster->getY(), pEnemy->getX(), pEnemy->getY());
	ZoneCoord_t X = pMonster->getX() + dirMoveMask[dir].x * 7;
	ZoneCoord_t Y = pMonster->getY() + dirMoveMask[dir].y * 7;
	Distance_t distance = pMonster->getDistance(X, Y, pEnemy->getX(), pEnemy->getY());

//	cout << "dir : " << (int)dir << ", distance : " << (int)distance << endl;

	if (distance > 2 ) return false;
	return true;
}
