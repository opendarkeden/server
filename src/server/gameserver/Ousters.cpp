//////////////////////////////////////////////////////////////////////////////
// Filename    : Ousters.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Ousters.h"
#include "Player.h"
#include "OptionInfo.h"
#include "SkillInfo.h"
#include "ItemLoaderManager.h"
#include "EffectLoaderManager.h"
#include "SkillParentInfo.h"
#include "DB.h"
#include "ItemInfoManager.h"
#include "AbilityBalance.h"
#include "Stash.h"
#include "TradeManager.h"
#include "CreatureUtil.h"
#include "FlagSet.h"
#include "OustersEXPInfo.h"
#include "Party.h"
#include "ItemUtil.h"
#include "PacketUtil.h"
#include "SkillUtil.h"
#include "Shape.h"
#include "GamePlayer.h"
//#include "RankEXPInfo.h"
#include "RankExpTable.h"
#include "VariableManager.h"
#include "WarSystem.h"
#include "ResurrectLocationManager.h"
#include "PKZoneInfoManager.h"
#include "TimeLimitItemManager.h"
#include <stdio.h>

#include "item/AR.h"
#include "item/SR.h"
#include "item/SG.h"
#include "item/SMG.h"
#include "item/Belt.h"
#include "item/Skull.h"
#include "item/OustersWristlet.h"
#include "item/OustersStone.h"
#include "item/OustersArmsband.h"

#include "skill/EffectBless.h"
#include "skill/EffectParalyze.h"
#include "skill/EffectDoom.h"
#include "skill/EffectTransformToWolf.h"
#include "skill/EffectTransformToBat.h"
#include "EffectGrandMasterOusters.h"
#include "RaceWarLimiter.h"

#include "GCModifyInformation.h"
#include "GCChangeShape.h"
#include "GCSkillInfo.h"
#include "GCRealWearingInfo.h"
#include "GCStatusCurrentHP.h"
#include "GCTakeOff.h"
#include "GCOtherModifyInfo.h"
#include "GCPetStashList.h"

#include "MonsterInfo.h"
#include "CastleSkillInfo.h"
#include "skill/OustersCastleSkillSlot.h"
#include "GuildUnion.h"
#include "Store.h"
#include "AdvancementClassExpTable.h"
#include "DynamicZone.h"

#include "SystemAvailabilitiesManager.h"

const Color_t UNIQUE_COLOR = 0xFFFF;
const Color_t QUEST_COLOR = 0xFFFE;

const Level_t MAX_OUSTERS_LEVEL = 150;

Ousters::Ousters () 
	 
: PlayerCreature(0, NULL)
{
	__BEGIN_TRY

	m_CClass = CREATURE_CLASS_OUSTERS;

	m_Mutex.setName("Ousters");

	// AttackMelee 같은 기본 공격을 집어넣어준다.
	for (int i=0; i<SKILL_DOUBLE_IMPACT; i++)
	{
		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;
		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(i);
		pOustersSkillSlot->setInterval(5);
		pOustersSkillSlot->setRunTime();

		addSkill(pOustersSkillSlot);
	}

	//////////////////////////////////////
	// 기본 스킬
	//////////////////////////////////////
	{
		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;
		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(SKILL_ABSORB_SOUL);
		pOustersSkillSlot->setExpLevel(1);
		pOustersSkillSlot->setInterval(5);
		pOustersSkillSlot->setRunTime();

		addSkill(pOustersSkillSlot);
	}
	{
		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;
		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(SKILL_SUMMON_SYLPH);
		pOustersSkillSlot->setExpLevel(1);
		pOustersSkillSlot->setInterval(5);
		pOustersSkillSlot->setRunTime();

		addSkill(pOustersSkillSlot);
	}

    for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
        m_pWearItem[i] = NULL;

	getCurrentTime(m_MPRegenTime);

	// 경험치 세이브 카운트 초기화
//	m_RankExpSaveCount		= 0;
	m_ExpSaveCount			= 0;
	m_FameSaveCount			= 0;
	m_AlignmentSaveCount	= 0;

	__END_CATCH
}

Ousters::~Ousters() 
    
{
	__BEGIN_TRY

	// 복장 정보를 생성해둔다. by sigi. 2002.6.18
	char pField[128];
	sprintf(pField, "CoatType=%d,ArmType=%d,CoatColor=%d,ArmColor=%d,BootsColor=%d",
					m_OustersInfo.getCoatType(),
					m_OustersInfo.getArmType(),
					m_OustersInfo.getCoatColor(),
					m_OustersInfo.getArmColor(),
					m_OustersInfo.getBootsColor() );

	tinysave(pField);

	// 떨어진 아이템의 내구성과 경험치, 성향 등을 저장한다.
	saveGears();
	saveExps();
	saveSkills();

	// 입고 있는 아이템을 메모리에서 삭제한다.
	destroyGears();

	// 클래스가 삭제될 경우, 해당하는 교환 정보를 삭제해야 함은 물론,
	// 교환 상대에게도 이 사실을 알려줘야 한다.
	TradeManager* pTradeManager = m_pZone->getTradeManager();
	TradeInfo* pInfo = pTradeManager->getTradeInfo(getName());
	if (pInfo != NULL)
	{
		// 교환 정보를 삭제
		pTradeManager->cancelTrade(this);
	}

	// 글로벌 파티 정보를 삭제한다. 
	// 일반적인 로그아웃의 경우에는
	// CGLogoutHandler에서 Zone::deleteCreature() 함수를 부르게 되고,
	// 비정상적인 경우라고 해도, 
	// GamePlayer::disconnect()에서 Zone::deleteCreature() 함수를 부르게 되므로,
	// 로컬 파티 및 파티 초대, 트레이드 정보를 걱정할 필요는 없다.
	deleteAllPartyInfo(this);

	// 기술들을 삭제
	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		OustersSkillSlot* pOustersSkillSlot = itr->second;
		SAFE_DELETE(pOustersSkillSlot);
	}

	__END_CATCH
}

// registerObject
// Zone에 종속된 ObjectRegistry를 사용해서, Ousters 와 소유아이템들의
// ObjectID를 할당받는다.
void Ousters::registerObject ()
    
{
    __BEGIN_TRY

    Assert(getZone() != NULL);

    // zone 의 object registery 에 접근한다.
    ObjectRegistry & OR = getZone()->getObjectRegistry();

    __ENTER_CRITICAL_SECTION(OR)

	// 모든 아이템에 OID 가 바뀌므로 시간제한 아이템 매니저에서 OID 맵을 지워줘야 한다.
	if (m_pTimeLimitItemManager != NULL)
		m_pTimeLimitItemManager->clear();

	// 우선 아우스터스의 OID를 등록받는다.
	OR.registerObject_NOLOCKED(this);

	// 인벤토리의 아이템들의 OID를 등록받는다.
	registerInventory(OR);

	// Goods Inventory의 아이템들의 OID를 등록받는다.
	registerGoodsInventory(OR);

	// 장착하고 있는 아이템들의 OID를 등록받는다.
	for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			bool bCheck = true;

			// 양손 무기일 경우, WEAR_LEFTHAND 에서 등록했으므로,
			// 또 등록할 필요는 없다.
			if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				bCheck = false;

			if (bCheck) registerItem(pItem, OR);
		}
	}

	// 마우스에 들고 있는 아이템의 OID를 등록 받는다.
	Item* pSlotItem = m_pExtraInventorySlot->getItem();
	if (pSlotItem != NULL) registerItem(pSlotItem, OR);

	m_Garbage.registerObject(OR);

	for ( int i=0; i<MAX_PET_STASH; ++i )
	{
		Item* pItem = getPetStashItem(i);
		if ( pItem != NULL ) registerItem( pItem, OR );
	}

    __LEAVE_CRITICAL_SECTION(OR)

	m_OustersInfo.setObjectID(m_ObjectID);
	m_pStore->updateStoreInfo();

    __END_CATCH
}

// Zone에 종속된 ObjectRegistry를 사용해서, Ousters 와 소유아이템들의
// ObjectID를 할당받는다. ItemTrace 를 남길지 여부 결정을 위해 따로 뺐다
void Ousters::registerInitObject ()
    
{
    __BEGIN_TRY

    Assert(getZone() != NULL);

    // zone 의 object registery 에 접근한다.
    ObjectRegistry & OR = getZone()->getObjectRegistry();

    __ENTER_CRITICAL_SECTION(OR)

	// 모든 아이템에 OID 가 바뀌므로 시간제한 아이템 매니저에서 OID 맵을 지워줘야 한다.
	if (m_pTimeLimitItemManager != NULL)
		m_pTimeLimitItemManager->clear();

	// 우선 아우스터스의 OID를 등록받는다.
	OR.registerObject_NOLOCKED(this);

	// 인벤토리의 아이템들의 OID를 등록받는다.
	registerInitInventory(OR);

	// Goods Inventory의 아이템들의 OID를 등록받는다.
	registerGoodsInventory(OR);

	// 장착하고 있는 아이템들의 OID를 등록받는다.
	for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			// ItemTrace 를 남길 것인지 결정
			pItem->setTraceItem( bTraceLog( pItem ) );

			bool bCheck = true;

			// 양손 무기일 경우, WEAR_LEFTHAND 에서 등록했으므로,
			// 또 등록할 필요는 없다.
			if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				bCheck = false;

			if (bCheck) registerItem(pItem, OR);
		}
	}

	// 마우스에 들고 있는 아이템의 OID를 등록 받는다.
	Item* pSlotItem = m_pExtraInventorySlot->getItem();
	if (pSlotItem != NULL)
	{
		// ItemTrace 를 남길 것인지 결정
		pSlotItem->setTraceItem( bTraceLog( pSlotItem ) );
		registerItem(pSlotItem, OR);
	}

	m_Garbage.registerObject(OR);

    __LEAVE_CRITICAL_SECTION(OR)

	m_OustersInfo.setObjectID(m_ObjectID);

    __END_CATCH
}

// 시간제한 아이템을 체크한다.
// 모든 아이템이 이미 register 되어있어야 한다.
void Ousters::checkItemTimeLimit() 
{
	__BEGIN_TRY

	// 인벤토리에서 찾는다.
	{
		list<Item*> ItemList;
		int height = m_pInventory->getHeight();
		int width  = m_pInventory->getWidth();

		for (int j=0; j<height; j++)
		{
			for (int i=0; i<width; i++)
			{
				Item* pItem = m_pInventory->getItem(i, j);
				if (pItem != NULL)
				{
					// 체크된 아이템의 리스트에서 현재 아이템을 찾는다.
					list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

					if (itr == ItemList.end())
					{
						i += pItem->getVolumeWidth() - 1;

						if ( wasteIfTimeLimitExpired( pItem ) )
						{
							m_pInventory->deleteItem( pItem->getObjectID() );
							SAFE_DELETE( pItem );
						}
						else
						{
							// 리스트에 아이템이 없으면
							// 같은 아이템을 두번 체크하지 않기 위해서
							// 리스트에다가 아이템을 집어넣는다.
							ItemList.push_back(pItem);
						}
					}
				}
			}
		}
	}

	// 장착하고 있는 것 중에 찾는다.
	{
		for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
		{
			Item* pItem = m_pWearItem[i];

			if (pItem != NULL) 
			{
				bool bCheck = true;

				// 양손 무기일 경우, WEAR_LEFTHAND 에서 등록했으므로,
				// 또 등록할 필요는 없다.
				if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
					bCheck = false;

				if (bCheck) 
				{
					if ( wasteIfTimeLimitExpired( pItem ) )
					{
						deleteWearItem( (WearPart)i );
						if ( i == WEAR_LEFTHAND && isTwohandWeapon(pItem) )
							deleteWearItem( WEAR_RIGHTHAND );
						SAFE_DELETE( pItem );
					}
				}
			}
		}
	}

	// 마우스에 들고 있는 아이템을 체크한다.
	{
		Item* pSlotItem = m_pExtraInventorySlot->getItem();
		if (pSlotItem != NULL && wasteIfTimeLimitExpired( pSlotItem ))
		{
			deleteItemFromExtraInventorySlot();
			SAFE_DELETE( pSlotItem );
		}
	}

	__END_CATCH
}

void Ousters::updateEventItemTime( DWORD time ) 
{
	__BEGIN_TRY

	// 인벤토리에서 찾는다.
	{
		list<Item*> ItemList;
		int height = m_pInventory->getHeight();
		int width  = m_pInventory->getWidth();

		for (int j=0; j<height; j++)
		{
			for (int i=0; i<width; i++)
			{
				Item* pItem = m_pInventory->getItem(i, j);
				if (pItem != NULL)
				{
					// 체크된 아이템의 리스트에서 현재 아이템을 찾는다.
					list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

					if (itr == ItemList.end())
					{
						i += pItem->getVolumeWidth() - 1;
						updateItemTimeLimit( pItem, time );
						// 리스트에 아이템이 없으면
						// 같은 아이템을 두번 체크하지 않기 위해서
						// 리스트에다가 아이템을 집어넣는다.
						ItemList.push_back(pItem);
					}
				}
			}
		}
	}

	// 장착하고 있는 것 중에 찾는다.
	{
		for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
		{
			Item* pItem = m_pWearItem[i];

			if (pItem != NULL) 
			{
				bool bCheck = true;

				// 양손 무기일 경우, WEAR_LEFTHAND 에서 등록했으므로,
				// 또 등록할 필요는 없다.
				if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
					bCheck = false;

				if (bCheck) 
				{
					updateItemTimeLimit( pItem, time );
				}
			}
		}
	}

	// 마우스에 들고 있는 아이템을 체크한다.
	{
		Item* pSlotItem = m_pExtraInventorySlot->getItem();
		if (pSlotItem != NULL)
		{
			updateItemTimeLimit( pSlotItem, time );
		}
	}

	__END_CATCH
}

///////////////////////////////////////////
//	Ousters와 Slayer사이의 변신을 위해서
//	아템 로딩은 따로 처리한다.
//
void Ousters::loadItem( bool checkTimeLimit )
	
{
	__BEGIN_TRY

	PlayerCreature::loadItem();

    // 인벤토리를 생성한다.
	SAFE_DELETE(m_pInventory);
	m_pInventory = new Inventory(10, 6);
	m_pInventory->setOwner(getName());

	// 아이템을 로드한다.
	g_pItemLoaderManager->load(this);

	PlayerCreature::loadGoods();

	// 로드한 아이템들을 등록시키고
    registerInitObject();

	// 처음 접속한 사람일 경우 초보자용 아이템세트를 일단 준 다음..
	if( !m_pFlagSet->isOn( FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO ) )
	{
		addNewbieItemToInventory( this );
		addNewbieGoldToInventory( this );
		addNewbieItemToGear( this );
		// 주었을 경우 줬다는 플래그를 꺼준다.
		m_pFlagSet->turnOn( FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO );
		m_pFlagSet->save( getName() );
	}

	if ( checkTimeLimit )
	{
		checkItemTimeLimit();
	}

	// 입고 있는 옷에 따라 능력치를 계산해준다.
	initAllStat();

	__END_CATCH
}


//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::load ()
	
{
	__BEGIN_TRY

	if ( !PlayerCreature::load() ) return false;

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
			"SELECT Name, AdvancementClass, AdvancementGoalExp, Sex,MasterEffectColor,\
			STR, DEX, INTE, HP, CurrentHP, MP, CurrentMP, Fame, \
			GoalExp, Level, Bonus, SkillBonus, Gold, GuildID, \
			ZoneID, XCoord, YCoord, Sight, Alignment,\
			StashGold, StashNum, Competence, CompetenceShape, ResurrectZone, SilverDamage, SMSCharge,\
			`Rank`, RankGoalExp, HairColor FROM Ousters WHERE Name = '%s' AND Active = 'ACTIVE'",
			m_Name.c_str()
		);

		if (pResult->getRowCount() == 0) 
		{
			//throw Error("Critical Error : data intergrity broken. (로그인 서버에서 게임 서버로 넘어오는 동안에 캐릭터가 삭제되었습니다.)");
			SAFE_DELETE(pStmt);
			return false;
		}

		pResult->next();

		uint i = 0;

		setName(pResult->getString(++i));

		Level_t advLevel = pResult->getInt(++i);
		Exp_t	advGoalExp = pResult->getInt(++i);

		m_pAdvancementClass = new AdvancementClass( advLevel, advGoalExp, AdvancementClassExpTable::s_AdvancementClassExpTable );
		if ( getAdvancementClassLevel() > 0 ) m_bAdvanced = true;

		setSex(pResult->getString(++i));
		setMasterEffectColor(pResult->getInt(++i));

		m_STR[ATTR_BASIC]   = pResult->getInt(++i);
		m_STR[ATTR_CURRENT] = m_STR[ATTR_BASIC];
	   	m_STR[ATTR_MAX]     = m_STR[ATTR_BASIC];

		m_DEX[ATTR_BASIC]   = pResult->getInt(++i);
		m_DEX[ATTR_CURRENT] = m_DEX[ATTR_BASIC];
	   	m_DEX[ATTR_MAX]     = m_DEX[ATTR_BASIC];

		m_INT[ATTR_BASIC]   = pResult->getInt(++i);
		m_INT[ATTR_CURRENT] = m_INT[ATTR_BASIC];
	   	m_INT[ATTR_MAX]     = m_INT[ATTR_BASIC];

		setHP(pResult->getInt(++i) , ATTR_MAX);
		setHP(getHP(ATTR_MAX) , ATTR_BASIC);
		setHP(pResult->getInt(++i) , ATTR_CURRENT);

		setMP(pResult->getInt(++i) , ATTR_MAX);
		setMP(getMP(ATTR_MAX) , ATTR_BASIC);
		setMP(pResult->getInt(++i) , ATTR_CURRENT);
		
		setFame(pResult->getInt(++i));

//		setExp(pResult->getInt(++i));
		setGoalExp(pResult->getInt(++i));
//		setExpOffset(pResult->getInt(++i));
		setLevel(pResult->getInt(++i));
		setBonus(pResult->getInt(++i));
		setSkillBonus(pResult->getInt(++i));

		setGold(pResult->getInt(++i));
		setGuildID(pResult->getInt(++i));

		ZoneID_t zoneID = pResult->getInt(++i);
		setX(pResult->getInt(++i));
		setY(pResult->getInt(++i));

		setSight (pResult->getInt(++i));

		setAlignment(pResult->getInt(++i));

		setStashGold(pResult->getInt(++i));
		setStashNum(pResult->getBYTE(++i));
		
		m_Competence = pResult->getBYTE(++i);

		if ( m_Competence >= 4 )
			m_Competence = 3;

		m_CompetenceShape = pResult->getBYTE(++i);

		setResurrectZoneID(pResult->getInt(++i));
		setSilverDamage(pResult->getInt(++i));

		setSMSCharge( pResult->getInt(++i) );

		Rank_t CurRank               = pResult->getInt(++i);
		RankExp_t RankGoalExp        = pResult->getInt(++i);

		m_pRank = new Rank( CurRank, RankGoalExp, RankExpTable::s_RankExpTables[RANK_TYPE_OUSTERS] );

//		setRank( pResult->getInt(++i) );
//		setRankExp( pResult->getInt(++i) );
//		setRankGoalExp( pResult->getInt(++i) );

		setHairColor(pResult->getInt(++i));

		// maxHP를 다시 계산해서 설정해준다.
		// 2002.7.15 by sigi
		// 공식 바뀌면 AbilityBalance.cpp의 computeHP도 수정해야한다.
		int maxHP = m_STR[ATTR_CURRENT]*2 + m_INT[ATTR_CURRENT] + m_DEX[ATTR_CURRENT] + m_Level;
		maxHP = min((int)maxHP, OUSTERS_MAX_HP);
		setHP( maxHP, ATTR_MAX );

		try
		{
			setZoneID( zoneID );
		}
		catch ( Error& e )
		{
			ZONE_COORD ResurrectCoord;
			g_pResurrectLocationManager->getOustersPosition( 1311, ResurrectCoord );
			setZoneID( ResurrectCoord.id );
			setX( ResurrectCoord.x );
			setY( ResurrectCoord.y );
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	//----------------------------------------------------------------------
	// Ousters Outlook Information 을 구성한다.
	//----------------------------------------------------------------------
	// 아우스터스는 로딩할때 ObjectID를 세팅 하도록 한다.
	m_OustersInfo.setObjectID(m_ObjectID);
	m_OustersInfo.setName(m_Name);
	m_OustersInfo.setSex(m_Sex);
	m_OustersInfo.setHairColor(m_HairColor);
	m_OustersInfo.setMasterEffectColor(m_MasterEffectColor);

	m_OustersInfo.setCompetence(m_CompetenceShape);

    //----------------------------------------------------------------------
	// 스킬을 로딩한다.
	//----------------------------------------------------------------------
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT SkillType, SkillLevel, Delay, CastingTime, NextTime FROM OustersSkillSave WHERE OwnerID = '%s'", m_Name.c_str());
	
		while(pResult->next()) 
		{
			int         i          = 0;
			SkillType_t SkillType = pResult->getInt(++i);

			if (hasSkill(SkillType) == NULL) 
			{
				OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot();
		
				pOustersSkillSlot->setName(m_Name);
				pOustersSkillSlot->setSkillType(SkillType);
				pOustersSkillSlot->setExpLevel(pResult->getInt(++i));
				pOustersSkillSlot->setInterval (pResult->getInt(++i));
				pOustersSkillSlot->setCastingTime (pResult->getInt(++i));
				pOustersSkillSlot->setRunTime();
		
				addSkill(pOustersSkillSlot);
			}
		}
	
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

    //----------------------------------------------------------------------
	// Rank Bonus 를  로딩한다.
	//----------------------------------------------------------------------
	loadRankBonus();

    //----------------------------------------------------------------------
	// 이펙트를 로딩한다.
	//----------------------------------------------------------------------
	g_pEffectLoaderManager->load(this);

	//----------------------------------------------------------------------
	// GrandMaster인 경우는 Effect를 붙여준다.
	//----------------------------------------------------------------------
	// by sigi. 2002.11.8
	if (m_Level>=100
		&& SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_GRAND_MASTER_EFFECT ) )
	{
		if (!isFlag(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS))
		{
			EffectGrandMasterOusters* pEffect = new EffectGrandMasterOusters(this);
			pEffect->setDeadline(999999);
			getEffectManager()->addEffect( pEffect );
			setFlag(Effect::EFFECT_CLASS_GRAND_MASTER_OUSTERS);
		}
	}

	//----------------------------------------------------------------------
	// 플래그 셋을 로드한다.
	//----------------------------------------------------------------------
	m_pFlagSet->load(getName());

	//----------------------------------------------------------------------
	// Ousters Outlook Information 을 초기화한다.
	//----------------------------------------------------------------------
	m_OustersInfo.setCoatType(OUSTERS_COAT_BASIC);
	m_OustersInfo.setArmType(OUSTERS_ARM_GAUNTLET);
	m_OustersInfo.setSylphType(OUSTERS_SYLPH_NONE);
	m_OustersInfo.setHairColor(m_HairColor);

	m_OustersInfo.setCoatColor( 377 );
	m_OustersInfo.setAdvancementLevel( getAdvancementClassLevel() );

	// 잘못된 경험치를 재조정 해준다.
/*	OustersEXPInfo* pOustersEXPInfo = g_pOustersEXPInfoManager->getOustersEXPInfo(m_Level);

	if ( (pOustersEXPInfo->getAccumExp() != m_Exp + m_GoalExp) 
		&& m_Level > 1 && m_Level < OUSTERS_MAX_LEVEL ) 
	{
		// 현재 누적 경험치 = 현재 레벨의 총 경험치 - 목표 경험치
		m_Exp = pOustersEXPInfo->getAccumExp() - m_GoalExp;

		char pField[80];
		sprintf(pField, "Exp=%lu", m_Exp);
		tinysave(pField);
	}
*/
	// rank가 0이면 초기값이 설정되지 않았다는 의미이다. by sigi. 2002.9.13
	if (getRank()==0)
	{
		saveInitialRank();
	}


	// 잘못된 계급을 재조정 해준다.
/*	RankEXPInfo* pRankEXPInfo = g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->getRankEXPInfo(m_Rank);

	if ((pRankEXPInfo->getAccumExp() != m_RankExp + m_RankGoalExp) 
		&& m_Rank > 1 && m_Rank < OUSTERS_MAX_RANK) 
	{
		m_RankExp = pRankEXPInfo->getAccumExp() - m_RankGoalExp;

		char pField[80];
		sprintf(pField, "RankExp=%lu", m_RankExp);
		tinysave(pField);
	}
*/

	initAllStat();

	// 전쟁 참가 Flag 체크
	if ( RaceWarLimiter::isInPCList( this ) )
	{
		setFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET );
	}

	if (m_pZone->isHolyLand()
        && g_pWarSystem->hasActiveRaceWar()
        && !isFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET ))
	{
        ZONE_COORD ResurrectCoord;
        g_pResurrectLocationManager->getPosition( this, ResurrectCoord );
        setZoneID( ResurrectCoord.id );
        setX( ResurrectCoord.x );
        setY( ResurrectCoord.y );
    }

	return true;

	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
void Ousters::save () const
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Statement* pStmt;

	//--------------------------------------------------------------------------------
	// 아우스터스 정보를 저장한다.
	//--------------------------------------------------------------------------------
	BEGIN_DB
	{
		StringStream sql;
		sql << "UPDATE Ousters SET"
			<< " CurrentHP = " << (int)m_HP[ATTR_CURRENT]
			<< ", HP = " << (int)m_HP[ATTR_MAX]
			<< ", CurrentMP = " << (int)m_MP[ATTR_CURRENT]
			<< ", MP = " << (int)m_MP[ATTR_MAX]
			<< ", ZoneID = " << (int)getZoneID()
			<< ", XCoord = " << (int)m_X
			<< ", YCoord = " << (int)m_Y
			<< " WHERE Name = '" << m_Name << "'";
		
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQueryString(sql.toString());

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	//--------------------------------------------------
	// 이펙트를 세이브 한다.
	//--------------------------------------------------
	m_pEffectManager->save(m_Name);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//----------------------------------------------------------------------
// tinysave
//----------------------------------------------------------------------
void Ousters::tinysave(const string & field)	// by sigi. 2002.5.15
	    const 
{
    __BEGIN_TRY

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Ousters SET %s WHERE Name='%s'", field.c_str(), m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 사용한 skill bonus 포인트를 리턴한다.
////////////////////////////////////////////////////////////////////////////////
SkillBonus_t Ousters::getSumOfUsedSkillBonus() const
	
{
	__BEGIN_TRY

	return 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
//
// 스킬 관련 함수
//
//
////////////////////////////////////////////////////////////////////////////////

// 특정 Skill을 리턴한다.
OustersSkillSlot* Ousters::getSkill (SkillType_t SkillType) const 
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::const_iterator itr = m_SkillSlot.find(SkillType);
	if (itr != m_SkillSlot.end())
	{
		return itr->second;
	}

	return NULL;

	__END_CATCH
}

// 특정 Skill을 add 한다
void Ousters::addSkill(SkillType_t SkillType)
	
{
	__BEGIN_TRY

	switch (SkillType)
	{
		case SKILL_UN_BURROW:
		case SKILL_UN_TRANSFORM:
		case SKILL_UN_INVISIBILITY:
		case SKILL_THROW_HOLY_WATER:
		case SKILL_EAT_CORPSE:
		case SKILL_HOWL:
			filelog("OustersError.log", "SkillType[%d], %s", SkillType, toString().c_str());
			Assert(false);
			break;
		default:
			break;
	}

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);

	if (itr == m_SkillSlot.end())
	{
		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Turn_t Delay = pSkillInfo->getMaxDelay();

		OustersSkillSlot* pOustersSkillSlot = new OustersSkillSlot;

		pOustersSkillSlot->setName(m_Name);
		pOustersSkillSlot->setSkillType(SkillType);
		pOustersSkillSlot->setInterval(Delay);
		pOustersSkillSlot->setRunTime();
		pOustersSkillSlot->setExpLevel(1);
		pOustersSkillSlot->create(m_Name);

		m_SkillSlot[SkillType] = pOustersSkillSlot;
	}

	__END_CATCH
}

// 특정 SkillSlot을 자동으로 빈 슬랏을 찾아 넣는다.
void Ousters::addSkill(OustersSkillSlot* pOustersSkillSlot)
	
{
	__BEGIN_TRY

	SkillType_t SkillType = pOustersSkillSlot->getSkillType();
	switch (SkillType)
	{
		case SKILL_UN_BURROW:
		case SKILL_UN_TRANSFORM:
		case SKILL_UN_INVISIBILITY:
		case SKILL_THROW_HOLY_WATER:
		case SKILL_EAT_CORPSE:
		case SKILL_HOWL:
			filelog("OustersError.log", "SkillType[%d], %s", SkillType, toString().c_str());
			Assert(false);
			break;
		default:
			break;
	}

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(pOustersSkillSlot->getSkillType());
	
	if (itr == m_SkillSlot.end())
	{
		m_SkillSlot[pOustersSkillSlot->getSkillType()] = pOustersSkillSlot;
	}
	// 2002.1.16 by sigi
	else
	{
		delete pOustersSkillSlot;
	}

	__END_CATCH
}

void Ousters::removeSkill(SkillType_t SkillType)
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);
	
	if (itr != m_SkillSlot.end())
	{
		OustersSkillSlot* pSkillSlot = itr->second;

		SAFE_DELETE( pSkillSlot );

		m_SkillSlot.erase( itr );
	}

	__END_CATCH
}

// 성지스킬을 지워주는 함수다.
void Ousters::removeCastleSkill(SkillType_t SkillType)
	
{
	__BEGIN_TRY

	// 성지 스킬만 지울 수 있다.
	if ( g_pCastleSkillInfoManager->getZoneID( SkillType ) == 0 ) return;

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);
	
	if (itr != m_SkillSlot.end())
	{
		OustersCastleSkillSlot* pCastleSkillSlot = dynamic_cast<OustersCastleSkillSlot*>(itr->second);

		SAFE_DELETE( pCastleSkillSlot );

		m_SkillSlot.erase( itr );
	}

	__END_CATCH
}

// 갖고 있는 모든 성지스킬을 지워주는 함수이다.
void Ousters::removeAllCastleSkill()
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();

	while ( itr != m_SkillSlot.end() )
	{
		if ( itr->second != NULL )
		{
			OustersSkillSlot* pSkillSlot = itr->second;
			if ( g_pCastleSkillInfoManager->getZoneID( pSkillSlot->getSkillType() ) == 0 )
			{
				// 성지스킬이 아니면 다음껄로 넘어간다.
				++itr;
				continue;
			}

			// 성지스킬이면 지워준다. 반복자 사용에 주의
			SAFE_DELETE( pSkillSlot );
			unordered_map<SkillType_t, OustersSkillSlot*>::iterator prevItr = itr;
			
			++itr;
			m_SkillSlot.erase( prevItr );
		}
		else
		{
			// 이건 멀까.... Assert 해야 되지 않나 -_-;
			Assert(false);
		}
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
//
// 아이템 착/탈 관련 함수
//
//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
//
// Ousters::WearItem()
//
// Item을 장착창에 장착시키고 능력치를 계산한다.
//
//----------------------------------------------------------------------
void Ousters::wearItem(WearPart Part, Item* pItem)
	
{
	__BEGIN_TRY

	Assert(pItem != NULL);

	Item* pPrevItem = NULL;
	Item* pLeft = NULL;
	Item* pRight = NULL;

	// 양손 무기일 경우에는 양손 장착창에다 하나의 아이템 포인터를 할당...
	if (isTwohandWeapon(pItem))
	{
		// 양손에 아이템을 들고 있을 경우
		if (isWear(WEAR_RIGHTHAND) && isWear(WEAR_LEFTHAND))
		{
			pLeft  = getWearItem(WEAR_RIGHTHAND);
			pRight = getWearItem(WEAR_LEFTHAND);
			
			// 양손 무기를 들고 있을 경우
			if (pLeft == pRight)
			{
				// 요구한 아이템을 장착 포인트에 넣고,
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				char pField[80];
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);
			}
			// 냥냥
			else
			{
				// 양손에 검과 방패를 들고 있었는데...양손 무기를 들려고 하면,
				// 검은 마우스 포인터에 달아줄 수 있지만, 방패는 어떻게 할 수가 없다.
				// 인벤토리에 넣어줘야 할 텐데, 지금 당장은 어떻게 할 지를 모르겠네...
				// 걍 입을 수 없다는 패킷을 보내주자...
				//cerr << "양손에 칼과 방패를 들고 있어서, 양손 무기를 장착할 수 없습니다." << endl;
				return;
			}
		}
		// 양손에 아이템을 들고 있지 않을 경우
		else 
		{
			char pField[80];

			// 오른쪽에 아이템을 들고 있을 경우
			if (isWear(WEAR_RIGHTHAND))
			{
				pRight = getWearItem(WEAR_RIGHTHAND);
				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pRight);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pRight->tinysave(pField);
			}
			// 왼쪽에 아이템을 들고 있을 경우
			else if (isWear(WEAR_LEFTHAND))
			{
				pLeft = getWearItem(WEAR_LEFTHAND);
				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);
			}
			// 아무쪽도 아이템을 들고 있지 않을 경우
			else
			{
				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);
			}
		}
	}
	else 
	{
		if (isWear(Part))
		{
			pPrevItem = getWearItem(Part);
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			char pField[80];
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);

			addItemToExtraInventorySlot(pPrevItem);
			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pPrevItem->tinysave(pField);
		}
		else
		{
			// 요구한 아이템을 장착 포인트에 넣는다.
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			char pField[80];
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);
		}
	}

	// 옷이라면 옷에 따른 색깔을 정해준다.
	// 나중에라도 옷 타입이 여러 가지가 될 수 있으리라 생각하는데,
	// 현재로서는 옷 타입이 하나이므로, 색깔만 세팅해준다.
	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_OUSTERS_COAT:
			// item type을 설정해준다. 
			m_OustersInfo.setCoatType( getOustersCoatType( pItem->getItemType() ) );
			m_OustersInfo.setCoatColor( getItemShapeColor( pItem ) );
			break;
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
			m_OustersInfo.setArmType( OUSTERS_ARM_CHAKRAM );
			m_OustersInfo.setArmColor( getItemShapeColor( pItem ) );
			break;
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
			m_OustersInfo.setArmColor( getItemShapeColor( pItem ) );
			break;
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
			m_OustersInfo.setBootsColor( getItemShapeColor( pItem ) );
			break;
		default:
			break;
	}

	__END_CATCH
}


//----------------------------------------------------------------------
// Ousters::WearItem()
// Item을 장착창에 장착시키고 능력치를 계산한다.
//----------------------------------------------------------------------
void Ousters::wearItem(WearPart Part)
	
{
	__BEGIN_TRY

	// 장착 준비중인 아이템을 받아온다.
	Item* pItem = getExtraInventorySlotItem();
	Assert(pItem != NULL);

	Item* pPrevItem = NULL;
	Item* pLeft = NULL;
	Item* pRight = NULL;

	// 먼저 옷을 입히거나, 벗기기 전에 현재의 능력치를 버퍼에다 저장해 둔다.
	// 이는 나중에 변한 능력치만을 전송하기 위한 것이다.
	OUSTERS_RECORD prev;
	getOustersRecord(prev);

	char pField[80];

	// 양손 무기일 경우에는 양손 장착창에다 하나의 아이템 포인터를 할당...
	if (isTwohandWeapon(pItem))
	{
		// 양손에 아이템을 들고 있을 경우
		if (isWear(WEAR_RIGHTHAND) && isWear(WEAR_LEFTHAND))
		{
			pLeft  = getWearItem(WEAR_RIGHTHAND);
			pRight = getWearItem(WEAR_LEFTHAND);
			
			// 양손 무기를 들고 있을 경우
			if (pLeft == pRight)
			{
				takeOffItem(WEAR_LEFTHAND, false, false);

				// 요구한 아이템을 장착 포인트에 넣고,
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;
				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);

			}
			// 검과 방패를 들고 있을 경우
			else
			{
				// 양손에 검과 방패를 들고 있었는데...양손 무기를 들려고 하면,
				// 검은 마우스 포인터에 달아줄 수 있지만, 방패는 어떻게 할 수가 없다.
				// 인벤토리에 넣어줘야 할 텐데, 지금 당장은 어떻게 할 지를 모르겠네...
				// 걍 입을 수 없다는 패킷을 보내주자...
				return;
			}
		}
		// 양손에 아이템을 들고 있지 않을 경우
		else 
		{
			// by sigi. 2002.5.15
			// 오른쪽에 아이템을 들고 있을 경우
			if (isWear(WEAR_RIGHTHAND))
			{
				pRight = getWearItem(WEAR_RIGHTHAND);

				takeOffItem(WEAR_RIGHTHAND, false, false);

				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pRight);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pRight->tinysave(pField);
				
			}
			// 왼쪽에 아이템을 들고 있을 경우
			else if (isWear(WEAR_LEFTHAND))
			{
				pLeft = getWearItem(WEAR_LEFTHAND);
				
				takeOffItem(WEAR_LEFTHAND, false, false);

				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;
				
				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pLeft->tinysave(pField);
			}
			// 아무쪽도 아이템을 들고 있지 않을 경우
			else
			{
				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;

				pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
			}
		}
	}
	else
	{
		if (isWear(Part))
		{
			pPrevItem = getWearItem(Part);
			takeOffItem(Part, false, false);
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);

			deleteItemFromExtraInventorySlot();
			addItemToExtraInventorySlot(pPrevItem);

			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pPrevItem->tinysave(pField);
		}
		else
		{
			m_pWearItem[Part] = pItem;
			deleteItemFromExtraInventorySlot();

			// by sigi. 2002.5.15
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);
		}
	}

	initAllStat();
	sendRealWearingInfo();
	sendModifyInfo(prev);

	// 실제 적용되는 아이템만 복장을 바꾼다. by sigi. 2002.10.30
	if (m_pRealWearingCheck[Part])
	{
		if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_COAT
			|| pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_WRISTLET
			|| pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_CHAKRAM
			|| pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_BOOTS ) 
		{
			Color_t color = getItemShapeColor( pItem );

			// 옷을 갈아입었으니, 주위에다가 옷 갈아입었다고 정보를 날린다.
			GCChangeShape pkt;
			pkt.setObjectID(getObjectID());
			pkt.setItemClass(pItem->getItemClass());
			pkt.setItemType(pItem->getItemType());
			pkt.setOptionType(pItem->getFirstOptionType());
			pkt.setAttackSpeed(m_AttackSpeed[ATTR_CURRENT]);

			if ( color == QUEST_COLOR )
				pkt.setFlag( SHAPE_FLAG_QUEST );

			Zone* pZone = getZone();
			pZone->broadcastPacket(m_X, m_Y , &pkt, this);

			// PCOustersInfo3 정보를 바꿔준다.
			switch ( pItem->getItemClass() )
			{
				case Item::ITEM_CLASS_OUSTERS_COAT:
					// item type을 설정해준다. 
					m_OustersInfo.setCoatType( getOustersCoatType( pItem->getItemType() ) );
					m_OustersInfo.setCoatColor( color );
					break;
				case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
					m_OustersInfo.setArmType( OUSTERS_ARM_CHAKRAM );
					m_OustersInfo.setArmColor( color );
					break;
				case Item::ITEM_CLASS_OUSTERS_WRISTLET:
					m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
					m_OustersInfo.setArmColor( color );
					break;
				case Item::ITEM_CLASS_OUSTERS_BOOTS:
					m_OustersInfo.setBootsColor( color );
					break;
				default:
					break;
			}
		}
	}

	if (m_pZone != NULL)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, this, &prev);

		if (gcOtherModifyInfo.getShortCount() != 0 || gcOtherModifyInfo.getLongCount() != 0)
		{
			m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
		}
	}
	
	__END_CATCH
}


//----------------------------------------------------------------------
//
// Ousters::takeOffItem()
//
//----------------------------------------------------------------------
void Ousters::takeOffItem(WearPart Part, bool bAddOnMouse, bool bSendModifyInfo)
	
{
	__BEGIN_TRY

	OUSTERS_RECORD prev;

	// 장착창에 있는 아이템을 받아온다.
	Item* pItem = m_pWearItem[Part];
	Assert(pItem != NULL);

	// 장착창에 있는 아이템을 받아온다.
	//Item::ItemClass IClass = pItem->getItemClass();

	if (Part == WEAR_LEFTHAND || Part == WEAR_RIGHTHAND)
	{
		if (m_pWearItem[WEAR_RIGHTHAND] && m_pWearItem[WEAR_LEFTHAND])
		{
			if (m_pWearItem[WEAR_RIGHTHAND] == m_pWearItem[WEAR_LEFTHAND])
			{
				m_pWearItem[WEAR_RIGHTHAND] = NULL;
				m_pWearItem[WEAR_LEFTHAND] = NULL;
			}
		}
	}

	// 아이템을 장착포인트에서 제거한다.
	if (isTwohandWeapon(pItem))
	{
		m_pWearItem[WEAR_RIGHTHAND] = NULL;
		m_pWearItem[WEAR_LEFTHAND] = NULL;
	}
	else m_pWearItem[Part] = NULL;

	// wearItem에서 지정된 슬랏에 옷을 이미 입고 있는 경우에, 그것을 벗기고
	// 다시 옷을 입히는데, 그러면 벗길 때 패킷을 한번, 입었을 때 다시 패킷을
	// 한번, 총 두 번의 패킷을 보내게 된다. 그것을 방지하기 위해서
	// bool 변수를 하나 집어넣었다. -- 2002.01.24 김성민
	if (bSendModifyInfo)
	{
		getOustersRecord(prev);
		initAllStat();
		sendRealWearingInfo();
		sendModifyInfo(prev);
	}
	else
	{
		initAllStat();
	}

	//---------------------------------------------
	// 있어선 안될 체크 -_-; 임시 땜빵
	// 아이템을 마우스 커서에다 달아준당.
	//---------------------------------------------
	if (bAddOnMouse) 
	{
		addItemToExtraInventorySlot(pItem);
		// item저장 최적화. by sigi. 2002.5.13
		char pField[80];
        sprintf(pField, "Storage=%d, Durability=%d", STORAGE_EXTRASLOT, pItem->getDurability());
        pItem->tinysave(pField);
	}

	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_OUSTERS_COAT:
			{
				m_OustersInfo.setCoatType( OUSTERS_COAT_BASIC );
				m_OustersInfo.setCoatColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_COAT);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
			{
				m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
				m_OustersInfo.setArmColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_LEFTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			{
				m_OustersInfo.setArmType( OUSTERS_ARM_GAUNTLET );
				m_OustersInfo.setArmColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_LEFTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
			{
				m_OustersInfo.setBootsColor( 377 );
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_TROUSER);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
			break;
		default:
			break;
	}

	if (m_pZone != NULL)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, this, &prev);

		if (gcOtherModifyInfo.getShortCount() != 0 || gcOtherModifyInfo.getLongCount() != 0)
		{
			m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
		}
	}

	__END_CATCH
}




//----------------------------------------------------------------------
// destroyGears
// 장착 아이템을 Delete 한다.
//----------------------------------------------------------------------
void Ousters::destroyGears() 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	for (int j = 0; j < OUSTERS_WEAR_MAX; j++) 
	{
		Item* pItem = m_pWearItem[j];
		if (pItem != NULL)
		{
			Item::ItemClass IClass = pItem->getItemClass();

			//-------------------------------------------------------------
			// 슬레이어용 아이템을 입고 있는 이상한 자식이 있으면 다 어서트
			//-------------------------------------------------------------
			Assert(IClass != Item::ITEM_CLASS_AR);
			Assert(IClass != Item::ITEM_CLASS_SR);
			Assert(IClass != Item::ITEM_CLASS_SG);
			Assert(IClass != Item::ITEM_CLASS_SMG);
			Assert(IClass != Item::ITEM_CLASS_SWORD);
			Assert(IClass != Item::ITEM_CLASS_BLADE);
			Assert(IClass != Item::ITEM_CLASS_SHIELD);
			Assert(IClass != Item::ITEM_CLASS_CROSS);
			Assert(IClass != Item::ITEM_CLASS_MACE);
			Assert(IClass != Item::ITEM_CLASS_HELM);
			Assert(IClass != Item::ITEM_CLASS_GLOVE);
			Assert(IClass != Item::ITEM_CLASS_TROUSER);
			Assert(IClass != Item::ITEM_CLASS_COAT);

			// 양손 무기인지를 검사해서 아이템 하나를 지우면서
			// 양손을 비워준다.
			if (isTwohandWeapon(pItem))
			{
				m_pWearItem[WEAR_RIGHTHAND] = NULL;
				m_pWearItem[WEAR_LEFTHAND]  = NULL;
			}
			else m_pWearItem[j] = NULL;

			SAFE_DELETE(pItem);
		}
	}

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::isRealWearing(WearPart part) const
	
{
	__BEGIN_TRY

	if (part >= OUSTERS_WEAR_MAX) throw("Ousters::isRealWearing() : invalid wear point!");

	if (m_pWearItem[part] == NULL) return false;
	if (part >= WEAR_ZAP1 && part <= WEAR_ZAP4)
	{
		// 해당 위치에 정령석도 있어야 된다.
		if ( m_pWearItem[part-WEAR_ZAP1+WEAR_STONE1]==NULL ) return false;
	}

	return isRealWearing(m_pWearItem[part]);

	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::isRealWearing(Item* pItem) const
	
{
	__BEGIN_TRY

	if (pItem == NULL) return false;

/*	if ( m_pZone != NULL && m_pZone->isDynamicZone() && m_pZone->getDynamicZone()->getTemplateZoneID() == 4005 )
	{
		if ( !isOustersWeapon( pItem->getItemClass() ) ) return false;
	}*/

	// 시간제한아이템은 레어나 유니크나 무료사용자도 쓸 수 있다....... 2003.5.4
	if ( pItem->isTimeLimitItem() )
	{
		return true;
	}

	// 프리미엄 존에서는 유료사용자만 유니크/레어 아이템이 적용된다.
	// 커플링도 유료사용자만 쓸 수 있다. by Sequoia 2003. 3. 5.
	if (getZone()->isPremiumZone()
		&& (pItem->isUnique() || pItem->getOptionTypeSize()>1  ) )
			//pItem->getItemClass() == Item::ITEM_CLASS_COUPLE_RING || pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_COUPLE_RING))
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(getPlayer());
		if (!pGamePlayer->isPayPlaying() 
			&& !pGamePlayer->isPremiumPlay())
		{
			return false;
		}
	}

	Item::ItemClass IClass    = pItem->getItemClass();
	ItemInfo*       pItemInfo = g_pItemInfoManager->getItemInfo(IClass, pItem->getItemType());

	Level_t			ReqAdvancedLevel = pItemInfo->getReqAdvancedLevel();
	if ( ReqAdvancedLevel > 0 && ( !isAdvanced() || getAdvancementClassLevel() < ReqAdvancedLevel ) ) return false;

	if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_COAT || pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_BOOTS ||
		isOustersWeapon(pItem->getItemClass()) )
	{
		if ( ReqAdvancedLevel <= 0 && isAdvanced() ) return false;
	}
	
	Level_t         ReqLevel  = pItemInfo->getReqLevel();
	Attr_t			ReqSTR    = pItemInfo->getReqSTR();
	Attr_t			ReqDEX    = pItemInfo->getReqDEX();
	Attr_t			ReqINT    = pItemInfo->getReqINT();
	Attr_t			ReqSum    = pItemInfo->getReqSum();

	// 아이템이 옵션을 가지고 있다면,
	// 옵션의 종류에 따라서 능력치 제한을 올려준다.
	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	list<OptionType_t>::const_iterator itr;

	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
		if (ReqLevel != 0) ReqLevel += pOptionInfo->getReqLevel();
		if (ReqSTR != 0) ReqSTR += (pOptionInfo->getReqSum() * 2);
		if (ReqDEX != 0) ReqDEX += (pOptionInfo->getReqSum() * 2);
		if (ReqINT != 0) ReqINT += (pOptionInfo->getReqSum() * 2);
		if (ReqSum != 0) ReqSum += pOptionInfo->getReqSum();
	}

	ReqLevel = min(ReqLevel, MAX_OUSTERS_LEVEL );
//	ReqSum = min((int)ReqSum, OUSTERS_MAX_SUM);
//	ReqSTR = min((int)ReqSTR, OUSTERS_MAX_ATTR);
//	ReqDEX = min((int)ReqDEX, OUSTERS_MAX_ATTR);
//	ReqINT = min((int)ReqINT, OUSTERS_MAX_ATTR);

	// 능력치 제한이 하나라도 있다면,
	// 그 능력을 만족시키는지 검사해야 한다.
	Attr_t CSTR = m_STR[ATTR_CURRENT];
	Attr_t CDEX = m_DEX[ATTR_CURRENT];
	Attr_t CINT = m_INT[ATTR_CURRENT];
	Attr_t CSUM = CSTR + CDEX + CINT;

	if ( CSTR < ReqSTR || CDEX < ReqDEX || CINT < ReqINT || CSUM < ReqSum || m_Level < ReqLevel )
	{
		return false;
	}

	return true;

	__END_CATCH
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool Ousters::isRealWearingEx(WearPart part) const
{
	if (part >= OUSTERS_WEAR_MAX) return false;
	return m_pRealWearingCheck[part];
}

DWORD Ousters::sendRealWearingInfo(void) const
	
{
	__BEGIN_TRY

	DWORD info = 0;
	DWORD flag = 1;

	for (int i=0; i<OUSTERS_WEAR_MAX; i++)
	{
		if (isRealWearing((Ousters::WearPart)i)) info |= flag;
		flag <<= 1;
	}

	GCRealWearingInfo pkt;
	pkt.setInfo(info);
	m_pPlayer->sendPacket(&pkt);

	return info;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
//
// 인포 관련 함수
//
//
////////////////////////////////////////////////////////////////////////////////

PCOustersInfo2* Ousters::getOustersInfo2 ()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	PCOustersInfo2* pInfo = new PCOustersInfo2();

	pInfo->setObjectID(m_ObjectID);
	pInfo->setName(m_Name);
	pInfo->setLevel(m_Level);
	pInfo->setSex(m_Sex);
	pInfo->setHairColor(m_HairColor);
	pInfo->setMasterEffectColor(m_MasterEffectColor);

    // 성향
	pInfo->setAlignment(m_Alignment);

	// 능력치
	pInfo->setSTR(m_STR[ATTR_CURRENT], ATTR_CURRENT);
	pInfo->setSTR(m_STR[ATTR_MAX], ATTR_MAX);
	pInfo->setSTR(m_STR[ATTR_BASIC], ATTR_BASIC);
	pInfo->setDEX(m_DEX[ATTR_CURRENT], ATTR_CURRENT);
	pInfo->setDEX(m_DEX[ATTR_MAX], ATTR_MAX);
	pInfo->setDEX(m_DEX[ATTR_BASIC], ATTR_BASIC);
	pInfo->setINT(m_INT[ATTR_CURRENT], ATTR_CURRENT);
	pInfo->setINT(m_INT[ATTR_MAX], ATTR_MAX);
	pInfo->setINT(m_INT[ATTR_BASIC], ATTR_BASIC);
	
	pInfo->setHP(m_HP[ATTR_CURRENT] , m_HP[ATTR_MAX]);
	pInfo->setMP(m_MP[ATTR_CURRENT] , m_MP[ATTR_MAX]);
	pInfo->setSilverDamage( m_SilverDamage );

	pInfo->setFame(m_Fame);
	pInfo->setExp(m_GoalExp);
	pInfo->setGold(m_Gold);
	pInfo->setSight(m_Sight);
	pInfo->setBonus(m_Bonus);
	pInfo->setSkillBonus(m_SkillBonus);

	// by sigi. 2002.8.30
	pInfo->setRank(getRank());
	pInfo->setRankExp(getRankGoalExp());

	pInfo->setCompetence(m_CompetenceShape);
	pInfo->setGuildID(m_GuildID);
	pInfo->setGuildName( getGuildName() );
	pInfo->setGuildMemberRank( getGuildMemberRank() );

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( m_GuildID );
	if ( pUnion == NULL ) pInfo->setUnionID( 0 );
	else pInfo->setUnionID( pUnion->getUnionID() );

	pInfo->setAdvancementLevel( getAdvancementClassLevel() );
	pInfo->setAdvancementGoalExp( getAdvancementClassGoalExp() );

	return pInfo;

	__END_DEBUG
	__END_CATCH
}


//----------------------------------------------------------------------
// Ousters Outlook Information
//----------------------------------------------------------------------
PCOustersInfo3 Ousters::getOustersInfo3 () const 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	m_OustersInfo.setObjectID(m_ObjectID);
	m_OustersInfo.setX(m_X);
	m_OustersInfo.setY(m_Y);
	m_OustersInfo.setDir(m_Dir);
	m_OustersInfo.setCurrentHP(m_HP[ATTR_CURRENT]);
	m_OustersInfo.setMaxHP(m_HP[ATTR_MAX]);
	m_OustersInfo.setAttackSpeed(m_AttackSpeed[ATTR_CURRENT]);
	m_OustersInfo.setAlignment(m_Alignment);
	m_OustersInfo.setGuildID(m_GuildID);

	// by sigi. 2002.9.10
	m_OustersInfo.setRank(getRank());

    m_OustersInfo.setHairColor(m_HairColor);
    m_OustersInfo.setMasterEffectColor(m_MasterEffectColor);

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion( m_GuildID );
	if ( pUnion == NULL ) m_OustersInfo.setUnionID( 0 );
	else m_OustersInfo.setUnionID( pUnion->getUnionID() );

	m_OustersInfo.setAdvancementLevel( getAdvancementClassLevel() );

	return m_OustersInfo;

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
//
// get Extra Info
//
//----------------------------------------------------------------------
ExtraInfo* Ousters::getExtraInfo() const
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	BYTE ItemCount = 0;

	ExtraInfo* pExtraInfo = new ExtraInfo();

	Item* pItem = m_pExtraInventorySlot->getItem();

	if (pItem != NULL) {
	
	//	Item::ItemClass IClass = pItem->getItemClass();

		ExtraSlotInfo* pExtraSlotInfo = new ExtraSlotInfo();
		pItem->makePCItemInfo( *pExtraSlotInfo );

/*		pExtraSlotInfo->setObjectID(pItem->getObjectID());
		pExtraSlotInfo->setItemClass(pItem->getItemClass());
		pExtraSlotInfo->setItemType(pItem->getItemType());
		pExtraSlotInfo->setOptionType(pItem->getOptionTypeList());
		pExtraSlotInfo->setDurability(pItem->getDurability());
		pExtraSlotInfo->setSilver(pItem->getSilver());
		pExtraSlotInfo->setSilver(pItem->getEnchantLevel());
		pExtraSlotInfo->setItemNum(pItem->getNum());

		// 암스밴드라면 Sub 아이템의 추가 정보가 필요하다.
		if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
		{
			OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
			Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pItem)->getInventory();
			BYTE SubItemCount = 0;

			// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
			for (int i = 0; i < pOustersArmsband->getPocketCount(); i++) 
			{
				Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);

				if (pOustersArmsbandItem != NULL) 
				{
					SubItemInfo* pSubItemInfo = new SubItemInfo();
					pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
					pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
					pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
					pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
					pSubItemInfo->setSlotID(i);

					pExtraSlotInfo->addListElement(pSubItemInfo);

					SubItemCount++;
				}
			}

			pExtraSlotInfo->setListNum(SubItemCount);

		}

		// 상의 하의 Main Color 지금은 그냥 0 으로 셋팅 해둔다.
		pExtraSlotInfo->setMainColor(0);*/
	
		pExtraInfo->addListElement(pExtraSlotInfo);

		ItemCount++;

	}

	pExtraInfo->setListNum(ItemCount);

	return pExtraInfo;

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
//
// get Gear Info
//
//----------------------------------------------------------------------
GearInfo* Ousters::getGearInfo() const
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	int ItemCount = 0;

	GearInfo* pGearInfo = new GearInfo();

	for (int i = 0; i < OUSTERS_WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			//Item::ItemClass IClass = pItem->getItemClass();

			GearSlotInfo* pGearSlotInfo = new GearSlotInfo();
			pItem->makePCItemInfo( *pGearSlotInfo );
			pGearSlotInfo->setSlotID(i);
/*
			pGearSlotInfo->setObjectID(pItem->getObjectID());
			pGearSlotInfo->setItemClass(pItem->getItemClass());
			pGearSlotInfo->setItemType(pItem->getItemType());
			pGearSlotInfo->setOptionType(pItem->getOptionTypeList());
			pGearSlotInfo->setDurability(pItem->getDurability());
			pGearSlotInfo->setSilver(pItem->getSilver());
			pGearSlotInfo->setEnchantLevel(pItem->getEnchantLevel());

			// 암스밴드라면 Sub 아이템의 추가 정보가 필요하다.
			if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND)
			{
				// 아이템 인포를 받아온다.
				ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());

				// 포켓의 숫자를 받아온다.
				BYTE PocketNum = ((OustersArmsbandInfo*)pItemInfo)->getPocketCount();

				// 벨트의 인벤토리를 받아온다.
				Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pItem)->getInventory();

				BYTE SubItemCount = 0;

				// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
				for (int i = 0; i < PocketNum ; i++)
				{
					Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
					if (pOustersArmsbandItem != NULL)
					{
						SubItemInfo* pSubItemInfo = new SubItemInfo();
						pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
						pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
						pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
						pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
						pSubItemInfo->setSlotID(i);

						pGearSlotInfo->addListElement(pSubItemInfo);

						SubItemCount++;
					}
				}
				pGearSlotInfo->setListNum(SubItemCount);
			}

			pGearSlotInfo->setSlotID(i);
	
			// 상의 하의 Main Color 지금은 그냥 0 으로 셋팅 해둔다.
			pGearSlotInfo->setMainColor(0);*/
		
			pGearInfo->addListElement(pGearSlotInfo);

			ItemCount++;
		}
	}

	pGearInfo->setListNum(ItemCount);

	return pGearInfo;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get Inventory Info
//////////////////////////////////////////////////////////////////////////////
InventoryInfo* Ousters::getInventoryInfo() const
    
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	BYTE ItemCount = 0;

	InventoryInfo* pInventoryInfo = new InventoryInfo();
	list<Item*> ItemList;
	VolumeHeight_t Height = m_pInventory->getHeight();
	VolumeWidth_t Width = m_pInventory->getWidth();

	for (int j = 0; j < Height; j++) 
	{
		for (int i = 0 ; i < Width ; i ++) 
		{
			if (m_pInventory->hasItem(i, j)) 
			{
				Item* pItem = m_pInventory->getItem(i , j);
				VolumeWidth_t ItemWidth = pItem->getVolumeWidth();
				//Item::ItemClass IClass = pItem->getItemClass();
				list<Item*>::iterator itr = find(ItemList.begin() , ItemList.end() , pItem);

				if (itr == ItemList.end()) 
				{
					ItemList.push_back(pItem);

					// InventorySlotInfo를 구성
					InventorySlotInfo* pInventorySlotInfo = new InventorySlotInfo();
					pItem->makePCItemInfo( *pInventorySlotInfo );
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);
/*
					pInventorySlotInfo->setObjectID(pItem->getObjectID());
					pInventorySlotInfo->setItemClass(pItem->getItemClass());
					pInventorySlotInfo->setItemType(pItem->getItemType());
					pInventorySlotInfo->setOptionType(pItem->getOptionTypeList());
					pInventorySlotInfo->setSilver(pItem->getSilver());
					pInventorySlotInfo->setDurability(pItem->getDurability());
					pInventorySlotInfo->setEnchantLevel(pItem->getEnchantLevel());
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);
					pInventorySlotInfo->setItemNum(pItem->getNum());

					// 암스밴드라면 Sub 아이템의 추가 정보가 필요하다.
					if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
					{
						OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
						Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pItem)->getInventory();

						BYTE SubItemCount = 0;

						// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
						for (int i = 0; i < pOustersArmsband->getPocketCount() ; i++) 
						{
							Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
							if (pOustersArmsbandItem != NULL) 
							{
								SubItemInfo* pSubItemInfo = new SubItemInfo();
								pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
								pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
								pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
								pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
								pSubItemInfo->setSlotID(i);

								pInventorySlotInfo->addListElement(pSubItemInfo);

								SubItemCount++;
							}
						}

						pInventorySlotInfo->setListNum(SubItemCount);
					}

					pInventorySlotInfo->setMainColor(0);*/

					pInventoryInfo->addListElement(pInventorySlotInfo);
					ItemCount++;
					i = i + ItemWidth - 1;
				}
			}
		}
	}

	pInventoryInfo->setListNum(ItemCount);

	return pInventoryInfo;

	__END_DEBUG
	__END_CATCH
}

//----------------------------------------------------------------------
// getSkillInfo
//----------------------------------------------------------------------
void Ousters::sendOustersSkillInfo()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	OustersSkillInfo* pOustersSkillInfo = new OustersSkillInfo();

	BYTE SkillCount = 0;

	// 현재 시간, 남은 캐스팅 타임을 계산하기 위해
	Timeval currentTime;
	getCurrentTime( currentTime );

	unordered_map<SkillType_t, OustersSkillSlot*>::const_iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		OustersSkillSlot* pOustersSkillSlot = itr->second;
		Assert(pOustersSkillSlot != NULL);

		// AttackMelee 등의 기본 공격 기술 정보는 보내주지 않아야 한다.
		if (pOustersSkillSlot->getSkillType() >= SKILL_DOUBLE_IMPACT)
		{
			SubOustersSkillInfo* pSubOustersSkillInfo = new SubOustersSkillInfo();
			pSubOustersSkillInfo->setSkillType(pOustersSkillSlot->getSkillType());
			pSubOustersSkillInfo->setExpLevel(pOustersSkillSlot->getExpLevel());
			pSubOustersSkillInfo->setSkillTurn(pOustersSkillSlot->getInterval());
			pSubOustersSkillInfo->setCastingTime(pOustersSkillSlot->getRemainTurn( currentTime ) );

			pOustersSkillInfo->addListElement(pSubOustersSkillInfo);

			SkillCount++;
		}
	}

	GCSkillInfo gcSkillInfo;
	gcSkillInfo.setPCType(PC_OUSTERS);
	SkillType_t LearnSkillType = g_pSkillInfoManager->getSkillTypeByLevel(SKILL_DOMAIN_OUSTERS , m_Level);

	// 현재 레벨에서 배울 수 있는 기술이 있는지 본다.
	if (LearnSkillType != 0) 
	{
		// 배울 수 있는 기술이 있고 배우지 않은 상태라면 배우라고 알려준다.
		if (hasSkill(LearnSkillType) == NULL) 
		{
			pOustersSkillInfo->setLearnNewSkill(true);
		}
	}

	pOustersSkillInfo->setListNum(SkillCount);

	gcSkillInfo.addListElement(pOustersSkillInfo);

	m_pPlayer->sendPacket(&gcSkillInfo);

	__END_DEBUG
	__END_CATCH
}



////////////////////////////////////////////////////////////////////////////////
//
//
// 기타 함수
//
//
////////////////////////////////////////////////////////////////////////////////
void Ousters::setGold(Gold_t gold)
	
{
	__BEGIN_TRY

    // MAX_MONEY 를 넘어가는 걸 막는다
	// 2003.1.8  by bezz.
	m_Gold = min( (Gold_t)MAX_MONEY, gold );

	__END_CATCH
}

void Ousters::setGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY

	setGold(gold);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "Gold=%ld", m_Gold);
	tinysave(pField);

	__END_CATCH
}

void Ousters::increaseGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// MAX_MONEY 를 넘어가는 걸 막는다
	// 2003.1.8  by bezz.
	if ( m_Gold + gold > MAX_MONEY )
		gold = MAX_MONEY - m_Gold;

	setGold(m_Gold+gold);

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Ousters SET Gold=Gold+%u WHERE NAME='%s'", gold, m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)


	__END_DEBUG
	__END_CATCH
}

void Ousters::decreaseGoldEx(Gold_t gold)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// 0 미만이 되는 걸 막는다. 0 미만이 되면 underflow 되서 난리가 난다.
	// 2003.1.8  by bezz.
	if ( m_Gold < gold )
        gold = m_Gold;
	
	setGold(m_Gold-gold);

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Ousters SET Gold=Gold-%u WHERE NAME='%s'", gold, m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void Ousters::saveSilverDamage(Silver_t damage)
	    
{
	__BEGIN_TRY

	setSilverDamage(damage);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "SilverDamage=%d", m_SilverDamage);
	tinysave(pField);

	__END_CATCH
}

bool Ousters::checkGoldIntegrity()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	bool ret = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT Gold FROM Ousters WHERE NAME='%s'", m_Name.c_str());

		if ( pResult->next() )
		{
			ret = pResult->getInt(1) == m_Gold;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return ret;

	__END_CATCH
}

bool Ousters::checkStashGoldIntegrity()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	bool ret = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT StashGold FROM Ousters WHERE NAME='%s'", m_Name.c_str());

		if ( pResult->next() )
		{
			ret = pResult->getInt(1) == m_StashGold;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return ret;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 소유 아이템 hearbeat
//////////////////////////////////////////////////////////////////////////////
void Ousters::heartbeat(const Timeval& currentTime)
    
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	PlayerCreature::heartbeat( currentTime );

	OustersSkillSlot* pDriftingSoul = hasSkill(SKILL_DRIFTING_SOUL);

	if ( pDriftingSoul != NULL && m_MPRegenTime < currentTime && !isFlag( Effect::EFFECT_CLASS_PLEASURE_EXPLOSION ) )
	{
		SkillLevel_t level = pDriftingSoul->getExpLevel();
		int bonus = 0;

		if ( getMP() < getMP(ATTR_MAX ) )
		{
			if ( level <= 15 ) bonus +=1;
			else if ( level <= 25 ) bonus += 2;
			else if ( level <= 29 ) bonus += 3;
			else if ( level <= 30 ) bonus += 4;

			MP_t oldMP = getMP();
			MP_t newMP = min( (int)getMP(ATTR_MAX), oldMP + bonus );

			if ( oldMP != newMP )
			{
				setMP(newMP);

				GCModifyInformation gcMI;
				gcMI.addShortData(MODIFY_CURRENT_MP, newMP);
				m_pPlayer->sendPacket(&gcMI);
			}
		}

		// 1초 단위로 하트비트 시킨다. 
		m_MPRegenTime.tv_sec = currentTime.tv_sec + 2;
		m_MPRegenTime.tv_usec = currentTime.tv_usec;
	}

	__END_DEBUG
	__END_CATCH
}

void Ousters::getOustersRecord(OUSTERS_RECORD& record) const
	
{
    __BEGIN_TRY

	record.pSTR[0]     = m_STR[0];
	record.pSTR[1]     = m_STR[1];
	record.pSTR[2]     = m_STR[2];

	record.pDEX[0]     = m_DEX[0];
	record.pDEX[1]     = m_DEX[1];
	record.pDEX[2]     = m_DEX[2];

	record.pINT[0]     = m_INT[0];
	record.pINT[1]     = m_INT[1];
	record.pINT[2]     = m_INT[2];

	record.pHP[0]      = m_HP[0];
	record.pHP[1]      = m_HP[1];

	record.pMP[0]      = m_MP[0];
	record.pMP[1]      = m_MP[1];

	record.pDamage[0]  = m_Damage[0];
	record.pDamage[1]  = m_Damage[1];

	record.Rank     = getRank();

	record.Defense     = m_Defense[0];
	record.ToHit       = m_ToHit[0];
	record.Protection  = m_Protection[0];
	record.AttackSpeed = m_AttackSpeed[0];

	__END_CATCH
}

void Ousters::setResurrectZoneIDEx(ZoneID_t id)
	
{
	__BEGIN_TRY

	setResurrectZoneID(id);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "ResurrectZone=%d", id);
	tinysave(pField);


	__END_CATCH
}

void Ousters::saveAlignment(Alignment_t alignment)
	    
{
	__BEGIN_TRY

	setAlignment(alignment);

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "Alignment=%d", alignment);
	tinysave(pField);

	__END_CATCH
}


//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string Ousters::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Ousters("
		//<< "ObjectID:"   << (int)getObjectID()
		<< ",Name:"      << m_Name
		<< ",HairColor:" << (int)m_HairColor
		<< ",STR:"       << (int)m_STR[ATTR_CURRENT] << "/" << (int)m_STR[ATTR_MAX]
		<< ",DEX:"       << (int)m_DEX[ATTR_CURRENT] << "/" << (int)m_DEX[ATTR_MAX]
		<< ",INT:"       << (int)m_INT[ATTR_CURRENT] << "/" << (int)m_INT[ATTR_MAX]
		<< ",HP:"        << (int)m_HP[ATTR_CURRENT] << "/" << (int)m_HP[ATTR_MAX]
		<< ",MP:"        << (int)m_MP[ATTR_CURRENT] << "/" << (int)m_MP[ATTR_MAX]
		<< ",Fame:"      << (int)m_Fame
//		<< ",Exp:"       << (int)m_Exp
//		<< ",ExpOffset:" << (int)m_ExpOffset
		<< ",Rank:"       << (int)getRank()
		<< ",RankGoalExp:" << (int)getRankGoalExp()
		<< ",Level:"     << (int)m_Level
		<< ",Bonus:"     << (int)m_Bonus
		<< ",Gold:"      << (int)m_Gold
		<< ",ZoneID:"    << (int)getZoneID()
		<< ",XCoord:"    << (int)m_X
		<< ",YCoord:"    << (int)m_Y
		<< ",Sight:"     << (int)m_Sight
		<< ")";

	return msg.toString();

	__END_CATCH
}

void Ousters::saveSkills(void) const 
	
{
	__BEGIN_TRY

	unordered_map<SkillType_t, OustersSkillSlot*>::const_iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		OustersSkillSlot* pOustersSkillSlot = itr->second;
		Assert(pOustersSkillSlot != NULL);

		// 기본 공격 스킬이 아니라면...
		if (pOustersSkillSlot->getSkillType() >= SKILL_DOUBLE_IMPACT)
		{
			pOustersSkillSlot->save(m_Name);
		}
	}

	__END_CATCH
}

Sight_t Ousters::getEffectedSight() 
{
	__BEGIN_TRY

	Sight_t sight = Creature::getEffectedSight();

	if ( sight == DEFAULT_SIGHT )
	{
//		if ( isFlag( Effect::EFFECT_CLASS_BLOOD_DRAIN ) )
//		{
//			sight = (Sight_t) 3;
//		}
	}

	return sight;

	__END_CATCH
}

IP_t Ousters::getIP(void) const
{
	Assert(m_pPlayer != NULL);
	Socket* pSocket = m_pPlayer->getSocket();
	Assert(pSocket != NULL);
	return pSocket->getHostIP();
}

void Ousters::saveGears(void) const
    
{
	__BEGIN_TRY

	// 장착하고 있는 아이템들을 저장한다.
	char pField[80];

	for (int i=0; i < Ousters::OUSTERS_WEAR_MAX; i++)
	{
		Item* pItem = m_pWearItem[i];
		if (pItem != NULL)
		{
			Durability_t maxDurability = computeMaxDurability(pItem);
			if (pItem->getDurability() < maxDurability)
			{
				//pItem->save(m_Name, STORAGE_GEAR, 0, i, 0);
				// item저장 최적화. by sigi. 2002.5.13
				sprintf(pField, "Durability=%d", pItem->getDurability());
				pItem->tinysave(pField);
			}
		}
	}

	__END_CATCH
}


void Ousters::saveExps(void) const
    
{
	__BEGIN_TRY

	// 스킬 핸들러에서 쿼리 숫자를 줄이기 위해서 10으로 나누는 부분들은,
	// 서버 다운이 되지 않고, 정상적으로 로그아웃하는 경우에 
	// 세이브를 명시적으로 해주지 않으면 10 이하 올라간 부분은 날아가 버리게 된다.
	// 그러므로 여기서 세이브를 해 준다. 
	Statement* pStmt = NULL;

/*	char silverDam[40];
	if (m_SilverDamage != 0)
	{
		sprintf(silverDam, ",SilverDamage = %d", m_SilverDamage);
	}
	else silverDam[0]='\0'; */

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery( "UPDATE Ousters SET Alignment=%d, Fame=%d, GoalExp=%lu, SilverDamage = %d, `Rank`=%d, RankGoalExp=%lu, AdvancementClass=%u, AdvancementGoalExp=%lu WHERE Name='%s'",
							m_Alignment, m_Fame, m_GoalExp, m_SilverDamage, getRank(), getRankGoalExp(), getAdvancementClassLevel(), getAdvancementClassGoalExp(), m_Name.c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//----------------------------------------------------------------------
// getShapeInfo
//----------------------------------------------------------------------
// login할때 처리를 빨리하기 위해서다.
//----------------------------------------------------------------------
// 일단 32bit로 32가지를 표현하는걸로도 충분하다고 본다.
// 언젠가? over되면 bitset을 써야겠지..
//
// (!) 색깔은 index색값이 아니고 optionType을 넣어서 사용한다.
//     클라이언트에서 옵션으로 색값을 찾아서 쓴다.
//
// colors[1]은 coatColor만 있기 때문이다.
//----------------------------------------------------------------------
/*void Ousters::getShapeInfo (DWORD& flag, Color_t colors[PCOustersInfo::OUSTERS_COLOR_MAX]) const
//	
{
	__BEGIN_DEBUG

	Item* 						pItem;
	//OptionInfo* 				pOptionInfo;
	int							oustersBit;
	int							oustersColor;
	WearPart					Part;

	// 초기화
	flag = 0;

	//-----------------------------------------------------------------
	// 복장
	//-----------------------------------------------------------------
	Part = WEAR_COAT;
	pItem = m_pWearItem[Part];
	oustersBit = 0;
	oustersColor = 0;

	if (pItem!=NULL && m_pRealWearingCheck[Part])
	{
		ItemType_t IType = pItem->getItemType();

		colors[oustersColor] = getItemShapeColor( pItem );

		// itemType을 넣어준다.
		flag = IType;
	} 
	else 
	{
		colors[oustersColor] = 377;
		flag = (m_Sex? 0 : 1);
	}

	__END_DEBUG
}*/


//----------------------------------------------------------------------
// save InitialRank
//----------------------------------------------------------------------
// Rank, RankExp, RankGoalExp의 초기값을 저장한다.
//----------------------------------------------------------------------
void Ousters::saveInitialRank(void)
	
{
	OUSTERS_RECORD prev;
	getOustersRecord(prev);

	int curRank = max(1, (m_Level+3) / 4);
	m_pRank->SET_LEVEL(curRank);

/*	RankExp_t accumExp = 0;

	if (curRank!=1)
	{
		RankEXPInfo* pBeforeExpInfo = g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->getRankEXPInfo(curRank-1);
		accumExp = pBeforeExpInfo->getAccumExp();
	}
	
	RankEXPInfo* pNextExpInfo = g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->getRankEXPInfo(curRank);
	Exp_t NextGoalExp = pNextExpInfo->getGoalExp();

	setRankGoalExp(NextGoalExp);
*/
	char pField[80];
	sprintf(pField, "`Rank`=%d, RankExp=%lu, RankGoalExp=%lu",
					getRank(), getRankExp(), getRankGoalExp());
	tinysave(pField);
	setRankExpSaveCount(0);
}

bool
Ousters::addShape(Item::ItemClass IClass, ItemType_t IType, Color_t color)
{
	bool bisChange = false;

	switch (IClass)
	{
		/*case Item::ITEM_CLASS_OUSTERS_COAT:
		{
			bisChange = true;

			m_OustersInfo.setCoatColor( color );
			m_OustersInfo.setCoatType( IType );
		}
		break;
*/
		default:
			break;
	}

	return bisChange;
}


bool
Ousters::removeShape(Item::ItemClass IClass, bool bSendPacket)
{
    bool bisChange = false;

	switch (IClass)
	{
		/*case Item::ITEM_CLASS_OUSTERS_COAT :
		{
			m_OustersInfo.setCoatColor(377);
			m_OustersInfo.setCoatType( 0 );

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff pkt;
				pkt.setObjectID(getObjectID());
				pkt.setSlotID((SlotID_t)ADDON_COAT);
				m_pZone->broadcastPacket(getX(), getY(), &pkt, this);
			}
		}
		break;
*/
		default :
			return false;
	}

	return bisChange;
}

Color_t 
Ousters::getItemShapeColor(Item* pItem, OptionInfo* pOptionInfo) const
{
	Color_t color;

	if (pItem->isTimeLimitItem())
	{
		color = QUEST_COLOR;
	}
	else if (pItem->isUnique())
	{
		// 유니크는 특정한 색깔로 대체해서 처리한다.
		color = UNIQUE_COLOR;
	}
	// 외부에서 이미 OptionInfo를 찾은 경우
	else if (pOptionInfo != NULL) 
	{
		color = pOptionInfo->getColor();
	}
	// 아니면.. 첫번째 옵션의 색깔을 지정한다.
	else if (pItem->getFirstOptionType() != 0)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getFirstOptionType());
		color = pOptionInfo->getColor();
	}
	else 
	{
		// default 색
		color = 377;
	}

	return color;
}

bool Ousters::canPlayFree()
	
{
	__BEGIN_TRY

	return m_Level <= g_pVariableManager->getVariable(FREE_PLAY_OUSTERS_LEVEL);

	__END_CATCH
}

bool Ousters::satisfySkillRequire( SkillInfo* pSkillInfo )
{
	if ( isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) )
		return false;
	if ( pSkillInfo->getRequireFire() > m_ElementalFire )
		return false;
	if ( pSkillInfo->getRequireWater() > m_ElementalWater )
		return false;
	if ( pSkillInfo->getRequireEarth() > m_ElementalEarth )
		return false;
	if ( pSkillInfo->getRequireWind() > m_ElementalWind )
		return false;
	if ( pSkillInfo->getRequireSum() > getElementalSum() )
		return false;

	if ( pSkillInfo->getRequireWristletElemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_LEFTHAND)
				|| m_pWearItem[WEAR_LEFTHAND]->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET )
			return false;

		OustersWristlet* pWristlet = dynamic_cast<OustersWristlet*>(m_pWearItem[WEAR_LEFTHAND]);
		Assert( pWristlet != NULL );

		if ( pSkillInfo->getRequireWristletElemental() != pWristlet->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone1Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE1)
				|| m_pWearItem[WEAR_STONE1]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE1]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone1Elemental() != pStone->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone2Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE2)
				|| m_pWearItem[WEAR_STONE2]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE2]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone2Elemental() != pStone->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone3Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE3)
				|| m_pWearItem[WEAR_STONE3]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE3]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone3Elemental() != pStone->getElementalType() )
			return false;
	}

	if ( pSkillInfo->getRequireStone4Elemental() != ELEMENTAL_ANY )
	{
		if ( !isRealWearing(WEAR_STONE4)
				|| m_pWearItem[WEAR_STONE4]->getItemClass() != Item::ITEM_CLASS_OUSTERS_STONE )
			return false;

		OustersStone* pStone = dynamic_cast<OustersStone*>(m_pWearItem[WEAR_STONE4]);
		Assert( pStone != NULL );

		if ( pSkillInfo->getRequireStone4Elemental() != pStone->getElementalType() )
			return false;
	}

	return true;
}

SkillBonus_t Ousters::getSkillPointCount( ElementalDomain eDomain )
{
	unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();
	SkillBonus_t ret = 0;

	for ( ; itr != m_SkillSlot.end() ; ++itr )
	{
		OustersSkillSlot* pSlot = itr->second;
		if ( pSlot->getSkillType() < SKILL_DOUBLE_IMPACT ) continue;
		SkillInfo* pInfo = g_pSkillInfoManager->getSkillInfo( pSlot->getSkillType() );
		if ( pInfo == NULL ) continue;
		if ( pInfo->getElementalDomain() == eDomain )
		{
			ret += (pInfo->getSkillPoint() + pInfo->getLevelUpPoint() * (pSlot->getExpLevel()-1));
		}
	}

	cout << (int)eDomain << "에 넣은 스킬포인트 : " << ret << endl;

	return ret;
}

bool Ousters::isPayPlayAvaiable() 
	
{
	__BEGIN_TRY

	if (m_pPlayer==NULL)
		return false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);

#ifdef __CONNECT_BILLING_SYSTEM__
	if (pGamePlayer->isPayPlaying())
	{
		// 완전 무료 사용자. ㅋㅋ
		if (pGamePlayer->getPayType()==PAY_TYPE_FREE)
			return true;

		// 제한된 레벨까지 play가능
		if (m_Level <= g_pVariableManager->getVariable(FREE_PLAY_OUSTERS_LEVEL))
		{
			return true;
		}
	}

	return false;

// 애드빌 빌링을 사용하지 않고 사용자 제한을 하는 경우
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)

	if (!pGamePlayer->isPayPlaying())
	{
		// 제한된 레벨까지 play가능
		if (m_Level <= g_pVariableManager->getVariable(FREE_PLAY_OUSTERS_LEVEL))
		{
			return true;
		}

		return false;
	}

	return true;

#else

	return pGamePlayer->isPayPlaying();

#endif


	__END_CATCH
}

void Ousters::initPetQuestTarget()
{
	int minClass = 1, maxClass = 1;

	if ( getLevel() <= 50 )
	{
		minClass = 6; maxClass = 7;
	}
	else if ( getLevel() <= 60 )
	{
		minClass = 7; maxClass = 8;
	}
	else if ( getLevel() <= 70 )
	{
		minClass = maxClass = 9;
	}
	else if ( getLevel() <= 80 )
	{
		minClass = 9; maxClass = 10;
	}
	else if ( getLevel() <= 90 )
	{
		minClass = maxClass = 10;
	}
	else if ( getLevel() <= 110 )
	{
		minClass = 10; maxClass = 11;
	}
	else if ( getLevel() <= 130 )
	{
		minClass = 11; maxClass = 12;
	}
	else
	{
		minClass = 12; maxClass = 13;
	}

	m_TargetMonster = g_pMonsterInfoManager->getRandomMonsterByClass( minClass, maxClass );
	m_TargetNum = 80;
	m_TimeLimit = 3600;
}

bool Ousters::canLearnSkill(SkillType_t skill)
{
	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(skill);
	if ( pSkillInfo == NULL ) return false;
	// add by Coffee 藤속랗瘻세콘
	/*
	SKILL_DUMMY_DRAKE,							// 382 돠잉옹웨잔(삽)
		SKILL_HYDRO_CONVERGENCE,					// 383 릿북彊좟(彊)
		SKILL_SUMMON_CLAY,							// 384 瀾皐梁뻥(皐)
		HETER_CHAKRAM,								// 385 謳꼈적샘凜(濫却)
	*/
	if (skill == SKILL_DUMMY_DRAKE ||
		skill == SKILL_HYDRO_CONVERGENCE ||
		skill == SKILL_SUMMON_CLAY ||
		skill == SKILL_HETER_CHAKRAM
		)
	{
		unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();
		for ( ; itr != m_SkillSlot.end() ; ++itr )
		{
			if ( itr->first < SKILL_DOUBLE_IMPACT ) continue;
			SkillInfo* pHasSkillInfo = g_pSkillInfoManager->getSkillInfo( itr->first );
			if ( pHasSkillInfo == NULL ) continue;
			if ( pHasSkillInfo->getType() == SKILL_DUMMY_DRAKE ||
				 pHasSkillInfo->getType() == SKILL_HYDRO_CONVERGENCE ||
				 pHasSkillInfo->getType() == SKILL_SUMMON_CLAY ||
				 pHasSkillInfo->getType() == SKILL_HETER_CHAKRAM 
				) 
				return false;
		}
		return true;
	}
	// end by Coffee
	
	if ( pSkillInfo->getLevel() >= 150 )
	{
		unordered_map<SkillType_t, OustersSkillSlot*>::iterator itr = m_SkillSlot.begin();

		for ( ; itr != m_SkillSlot.end() ; ++itr )
		{
			if ( itr->first < SKILL_DOUBLE_IMPACT ) continue;
			SkillInfo* pHasSkillInfo = g_pSkillInfoManager->getSkillInfo( itr->first );
			if ( pHasSkillInfo == NULL ) continue;
			if ( pHasSkillInfo->getLevel() == pSkillInfo->getLevel() ) return false;
		}
	}

	return true;
}
