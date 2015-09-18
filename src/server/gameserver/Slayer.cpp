//////////////////////////////////////////////////////////////////////////////
// Filename    : Slayer.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "Slayer.h"
#include "Player.h"
//#include "LogClient.h"
#include "EffectManager.h"
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>

#include "SkillInfo.h"
#include "ItemInfoManager.h"
#include "ParkingCenter.h"
#include "SkillHandlerManager.h"
#include "SkillDomainInfoManager.h"
#include "ResurrectLocationManager.h"
#include "WarSystem.h"
#include "GamePlayer.h"
#include "PKZoneInfoManager.h"
#include "CastleInfoManager.h"
#include "CastleSkillInfo.h"

#include "OptionInfo.h"
#include "EffectLoaderManager.h"
#include "AbilityBalance.h"
#include "Stash.h"
#include "TradeManager.h"
#include "CreatureUtil.h"
#include "FlagSet.h"
//#include "AttrBalanceInfo.h"
#include "Party.h"
#include "Shape.h"
#include "VariableManager.h"

#include "ItemUtil.h"
#include "PacketUtil.h"
//#include "RankEXPInfo.h"

#include "item/Motorcycle.h"
#include "item/AR.h"
#include "item/SR.h"
#include "item/SG.h"
#include "item/SMG.h"
#include "item/Belt.h"
#include "item/Skull.h"
#include "item/SubInventory.h"

#include "skill/CastleSkillSlot.h"
#include "skill/EffectBless.h"
#include "skill/EffectDancingSword.h"
#include "skill/EffectGhostBlade.h"
#include "skill/EffectChargingPower.h"
#include "skill/EffectPotentialExplosion.h"
#include "skill/EffectParalyze.h"
#include "skill/EffectDoom.h"
#include "skill/EffectProtectionFromPoison.h"
#include "skill/EffectProtectionFromCurse.h"
#include "skill/EffectProtectionFromAcid.h"
#include "EffectGrandMasterSlayer.h"

#include "GCAddEffect.h"
#include "GCRemoveEffect.h"
#include "GCModifyInformation.h"
#include "GCChangeShape.h"
#include "GCTakeOff.h"
#include "GCSkillInfo.h"
#include "GCRealWearingInfo.h"
#include "GCStatusCurrentHP.h"
#include "GCTradeFinish.h"
#include "GCOtherModifyInfo.h"
#include "GCPetStashList.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Rpackets/RCSay.h"
#include "LoginServerManager.h"
#include "Properties.h"
//#include "RankEXPInfo.h"
#include "RaceWarLimiter.h"
#include "TimeLimitItemManager.h"
#include "RankExpTable.h"
#include "SlayerAttrExpTable.h"
#include "ExpFwd.h"

#include "skill/SkillUtil.h"

#include "SystemAvailabilitiesManager.h"
#include "types/ServerType.h"

#include "MonsterInfo.h"
#include "GuildUnion.h"
#include "Store.h"
#include "AdvancementClassExpTable.h"
#include "DynamicZone.h"

#include <map>

const Color_t UNIQUE_COLOR = 0xFFFF;
const Color_t UNIQUE_OPTION = 0xFFFF;

const Color_t QUEST_COLOR = 0xFFFE;
const Color_t QUEST_OPTION = 0xFFFE;

const Attr_t MAX_SLAYER_ATTR = 290;
const Attr_t MAX_SLAYER_SUM = 435;
const Attr_t MAX_SLAYER_ATTR_OLD = 200;
const Attr_t MAX_SLAYER_SUM_OLD = 300;

Slayer::Slayer () 
	throw() 
: PlayerCreature(0,NULL)
{
	__BEGIN_TRY

	m_CClass = CREATURE_CLASS_SLAYER;

	m_Mutex.setName("Slayer");

	// AttackMelee 같은 기본 기술을 집어넣어준다.
	for (int i=0; i<SKILL_DOUBLE_IMPACT; i++)
	{
		SkillSlot* pSkillSlot = new SkillSlot;
		//pSkillSlot = new SkillSlot;	// 2002.1.16  by sigi
		pSkillSlot->setName(m_Name);

		pSkillSlot->setSkillType(i);
		pSkillSlot->setInterval(5);
		pSkillSlot->setExpLevel(1);
		pSkillSlot->setExp(1);
		pSkillSlot->setRunTime();
		addSkill(pSkillSlot);
	}

	for (int i = 0; i < WEAR_MAX; i++) 
		m_pWearItem[i] = NULL;

	// Motorcycle을 Null 로 만든다.
	m_pMotorcycle = NULL;

	for (int i = 0; i < MAX_PHONE_SLOT; i++) 
	{
		m_PhoneSlot[i] = 0;
	}

	// 핫 키를 초기화 한다.
//	for (int i = 0; i < 4; i++) 
//	{
//		m_HotKey[i] = 0;
//	}

	// MP 리젠 시간 초기화
	getCurrentTime(m_MPRegenTime);

	// 경험치 세이브 카운트를 초기화한다.
	m_DomainExpSaveCount = 0;
	m_AttrExpSaveCount   = 0;
	m_SkillExpSaveCount  = 0;
	m_FameSaveCount      = 0;
	m_AlignmentSaveCount = 0;
//	m_RankExpSaveCount   = 0;
	m_Gold				 = 0;

//	m_pRank = NULL;

	__END_CATCH
}

Slayer::~Slayer() 
    throw()
{
	__BEGIN_TRY

	try {
		if (m_pMotorcycle != NULL) 
		{
			//getOffMotorcycle();

			// 이거 IncomingPlayerManager에서 해버리면 문제가 된다..
			// 그래서.. 그냥 오토바이를 없애버리도록 하자. 2002.7.15 by sigi
			if (g_pParkingCenter->hasMotorcycleBox(m_pMotorcycle->getItemID()))
			{
				g_pParkingCenter->deleteMotorcycleBox(m_pMotorcycle->getItemID());
			}

			m_pMotorcycle = NULL;
		}

		// 복장 정보를 생성해둔다. by sigi. 2002.6.18
		DWORD 	flag;
		Color_t color[PCSlayerInfo::SLAYER_COLOR_MAX];
		getShapeInfo (flag, color);

		char pField[128];
		sprintf(pField, "Shape=%ld, HelmetColor=%d, JacketColor=%d, PantsColor=%d, WeaponColor=%d, ShieldColor=%d", 
						flag,
						color[PCSlayerInfo::SLAYER_COLOR_HELMET],
						color[PCSlayerInfo::SLAYER_COLOR_JACKET],
						color[PCSlayerInfo::SLAYER_COLOR_PANTS],
						color[PCSlayerInfo::SLAYER_COLOR_WEAPON],
						color[PCSlayerInfo::SLAYER_COLOR_SHIELD]);

		//cout << "SAVE = " << pField << endl;
			
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

		// 글로벌 파티에서 삭제한다.
		// 일반적인 로그아웃의 경우에는
		// CGLogoutHandler에서 Zone::deleteCreature() 함수를 부르게 되고,
		// 비정상적인 경우라고 해도, 
		// GamePlayer::disconnect()에서 Zone::deleteCreature() 함수를 부르게 되므로,
		// 로컬 파티 및 파티 초대, 트레이드 정보를 걱정할 필요는 없다.
		deleteAllPartyInfo(this);

		// 기술들을 삭제
		map<SkillType_t, SkillSlot*>::iterator itr = m_SkillSlot.begin();
		for (; itr != m_SkillSlot.end(); itr++)
		{
			SkillSlot* pSkillSlot = itr->second;
			SAFE_DELETE(pSkillSlot);
		}

		m_SkillSlot.clear();

//		SAFE_DELETE(m_pRank);

	} catch (Throwable& t) {
		filelog("slayerDestructor.txt", "%s", t.toString().c_str());
		throw;
	} catch (exception& e) {
		filelog("slayerDestructor.txt", "Unknown std::exception");
		throw;
	} catch (...) {
		filelog("slayerDestructor.txt", "Unknown ... exception");
		throw;
	}

	m_bDeriveDestructed = true;

	__END_CATCH
}

// Zone에 종속된 ObjectRegistry를 사용해서, Slayer 와 소유아이템들의
// ObjectID를 할당받는다.
void Slayer::registerObject ()
	throw(Error)
{
	__BEGIN_TRY

	Assert(getZone() != NULL);

	// zone 의 object registery 에 접근한다.
	ObjectRegistry & OR = getZone()->getObjectRegistry();

	__ENTER_CRITICAL_SECTION(OR)

	// 모든 아이템에 OID 가 바뀌므로 시간제한 아이템 매니저에서 OID 맵을 지워줘야 한다.
	if (m_pTimeLimitItemManager != NULL)
		m_pTimeLimitItemManager->clear();

	// 우선 슬레이어의 OID를 등록받는다.
	OR.registerObject_NOLOCKED(this);

	// 인벤토리의 아이템들의 OID를 등록받는다.
	registerInventory(OR);

	// Goods Inventory의 아이템들의 OID를 등록받는다.
	registerGoodsInventory(OR);

	// 장착하고 있는 아이템들의 OID를 등록받는다.
	for (int i = 0; i < WEAR_MAX; i++) 
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

	// 오토바이의 OID를 등록 받는다.
	if (m_pMotorcycle != NULL) 
		OR.registerObject_NOLOCKED(m_pMotorcycle);

	m_Garbage.registerObject(OR);

	for (int i=0; i<MAX_PET_STASH; ++i )
	{
		Item* pItem = getPetStashItem(i);
		if (pItem != NULL ) registerItem(pItem, OR);
	}

	__LEAVE_CRITICAL_SECTION(OR)

	m_SlayerInfo.setObjectID(m_ObjectID);
	m_pStore->updateStoreInfo();

	__END_CATCH
}

// Zone에 종속된 ObjectRegistry를 사용해서, Slayer 와 소유아이템들의
// ObjectID를 할당받는다. 초기에 ItemTrace 를 위해 따로 뺌
void Slayer::registerInitObject ()
	throw(Error)
{
	__BEGIN_TRY

	Assert(getZone() != NULL);

	// zone 의 object registery 에 접근한다.
	ObjectRegistry & OR = getZone()->getObjectRegistry();

	__ENTER_CRITICAL_SECTION(OR)

	// 모든 아이템에 OID 가 바뀌므로 시간제한 아이템 매니저에서 OID 맵을 지워줘야 한다.
	if (m_pTimeLimitItemManager != NULL)
		m_pTimeLimitItemManager->clear();

	// 우선 슬레이어의 OID를 등록받는다.
	OR.registerObject_NOLOCKED(this);

	// 인벤토리의 아이템들의 OID를 등록받는다.
	registerInitInventory(OR);

	// Goods Inventory의 아이템들의 OID를 등록받는다.
	registerGoodsInventory(OR);

	// 장착하고 있는 아이템들의 OID를 등록받는다.
	for (int i = 0; i < WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			// ItemTrace 를 남길 것인지 결정
			pItem->setTraceItem(bTraceLog(pItem ));

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
		pSlotItem->setTraceItem(bTraceLog(pSlotItem ));
		registerItem(pSlotItem, OR);
	}

	// 오토바이의 OID를 등록 받는다.
	if (m_pMotorcycle != NULL) 
		OR.registerObject_NOLOCKED(m_pMotorcycle);

	m_Garbage.registerObject(OR);

	__LEAVE_CRITICAL_SECTION(OR)

	m_SlayerInfo.setObjectID(m_ObjectID);

	__END_CATCH
}


// 시간제한 아이템을 체크한다.
// 모든 아이템이 이미 register 되어있어야 한다.
void Slayer::checkItemTimeLimit() throw(Error)
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

						if (wasteIfTimeLimitExpired(pItem ) )
						{
							m_pInventory->deleteItem(pItem->getObjectID());
							SAFE_DELETE(pItem);
						}
						else
						{
							// 리스트에 아이템이 없으면
							// 같은 아이템을 두번 체크하지 않기 위해서
							// 리스트에다가 아이템을 집어넣는다.
							ItemList.push_back(pItem);
						}

						// 서브 인벤토리일 경우 안에도 찾는다.
						if (pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_SUB_INVENTORY )
						{
							SubInventory* pSubInventoryItem = dynamic_cast<SubInventory*>(pItem);
							Assert(pSubInventoryItem != NULL);
							Inventory* pSubInventory = pSubInventoryItem->getInventory();
							Assert(pSubInventory != NULL);

							list<Item*> SubItemList;

							for (CoordInven_t sy = 0; sy < pSubInventory->getHeight(); ++sy )
							{
								for (CoordInven_t sx = 0; sx < pSubInventory->getWidth(); ++sx )
								{
									Item* pSubItem = pSubInventory->getItem(sx, sy);

									if (pSubItem != NULL )
									{
										// 체크된 아이템의 리스트에서 현재 아이템을 찾는다.
										list<Item*>::iterator itr = find(SubItemList.begin(), SubItemList.end(), pSubItem);

										if (itr == SubItemList.end() )
										{
											if (wasteIfTimeLimitExpired(pSubItem ) )
											{
												pSubInventory->deleteItem(pSubItem->getObjectID());
												SAFE_DELETE(pSubItem);
											}
										}
										else
										{
											// 리스트에 아이템이 없으면
											// 같은 아이템을 두번 체크하지 않기 위해서
											// 리스트에다가 아이템을 집어넣는다.
											SubItemList.push_back(pSubItem);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// 장착하고 있는 것 중에 찾는다.
	{
		for (int i = 0; i < WEAR_MAX; i++) 
		{
			Item* pItem = m_pWearItem[i];

			if (pItem != NULL) 
			{
				bool bCheck = true;

				if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
					bCheck = false;

				if (bCheck) 
				{
					if (wasteIfTimeLimitExpired(pItem ) )
					{
						deleteWearItem((WearPart)i);
						if (i == WEAR_LEFTHAND && isTwohandWeapon(pItem ) )
							deleteWearItem(WEAR_RIGHTHAND);
						SAFE_DELETE(pItem);
					}
				}
			}
		}
	}

	// 마우스에 들고 있는 아이템을 체크한다.
	{
		Item* pSlotItem = m_pExtraInventorySlot->getItem();
		if (pSlotItem != NULL && wasteIfTimeLimitExpired(pSlotItem ) )
		{
			deleteItemFromExtraInventorySlot();
			SAFE_DELETE(pSlotItem);
		}
	}

	// 오토바이를 체크한다.
	// 일단 복잡해서 오토바이는 시간제한 안함
/*	{
		if (m_pMotorcycle != NULL && wasteIfTimeLimitExpired(m_pMotorcycle ) )
		{
		}
	}*/

	__END_CATCH
}

void Slayer::updateEventItemTime(DWORD time ) throw(Error)
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

						updateItemTimeLimit(pItem, time);

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
		for (int i = 0; i < WEAR_MAX; i++) 
		{
			Item* pItem = m_pWearItem[i];

			if (pItem != NULL) 
			{
				bool bCheck = true;

				if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem))
					bCheck = false;

				if (bCheck) 
				{
					updateItemTimeLimit(pItem, time);
				}
			}
		}
	}

	// 마우스에 들고 있는 아이템을 체크한다.
	{
		Item* pSlotItem = m_pExtraInventorySlot->getItem();
		if (pSlotItem != NULL)
		{
			updateItemTimeLimit(pSlotItem, time);
		}
	}

	__END_CATCH
}

void Slayer::loadItem(bool checkTimeLimit )
	throw(InvalidProtocolException, Error)
{
	__BEGIN_TRY

	PlayerCreature::loadItem();

	// 인벤토리를 생성한다. 
	// 생성하기 전에 전에 있던 것은 지워준다.
	SAFE_DELETE(m_pInventory);
	m_pInventory = new Inventory(10, 6);
	m_pInventory->setOwner(getName());

	// 아이템을 로드한다.
	g_pItemLoaderManager->load(this);

	// 구매한 아이템을 로드한다.
	PlayerCreature::loadGoods();

	// 로드한 아이템들을 등록하고...
	registerInitObject();

	// 처음 접속한 사람일 경우 초보자용 아이템세트를 일단 준 다음..
	if(m_pFlagSet->isOn(FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO ) )
	{
		addNewbieItemToInventory(this);
		addNewbieGoldToInventory(this);
		addNewbieItemToGear(this);
		// 주었을 경우 줬다는 플래그를 꺼준다.
		m_pFlagSet->turnOff(FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO);
		m_pFlagSet->save(getName());
	}

	if (checkTimeLimit )
	{
		checkItemTimeLimit();
	}

	// 입고 있는 옷에 따라 능력치를 계산해 준다.
	initAllStat();

	//cout << "Slayer::loadItem() : STR[CURRENT]" << (int)m_STR[ATTR_CURRENT] << endl;
	//cout << "Slayer::loadItem() : STR[MAX]" << (int)m_STR[ATTR_MAX] << endl;
	//cout << "Slayer::loadItem() : STR[BASIC]" << (int)m_STR[ATTR_BASIC] << endl;
	//cout << "Slayer::loadItem() : DEX[CURRENT]" << (int)m_DEX[ATTR_CURRENT] << endl;
	//cout << "Slayer::loadItem() : DEX[MAX]" << (int)m_DEX[ATTR_MAX] << endl;
	//cout << "Slayer::loadItem() : DEX[BASIC]" << (int)m_DEX[ATTR_BASIC] << endl;
	//cout << "Slayer::loadItem() : INT[CURRENT]" << (int)m_INT[ATTR_CURRENT] << endl;
	//cout << "Slayer::loadItem() : INT[MAX]" << (int)m_INT[ATTR_MAX] << endl;
	//cout << "Slayer::loadItem() : INT[BASIC]" << (int)m_INT[ATTR_BASIC] << endl;

	__END_CATCH
}

bool Slayer::load ()
	throw(InvalidProtocolException, Error)
{
	__BEGIN_TRY

	if (!PlayerCreature::load() ) return false;

	for (int i=0; i<SKILL_DOMAIN_VAMPIRE; i++)
	{
		m_SkillDomainLevels[i] = 0;
//		m_SkillDomainExps[i]   = 0;
	}

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	int reward = 0;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Name, AdvancementClass, AdvancementGoalExp, Competence, CompetenceShape, Sex, HairStyle, HairColor, SkinColor, Phone, MasterEffectColor, STR, STRGoalExp, DEX, DEXGoalExp, INTE, INTGoalExp, AdvancedSTR, AdvancedDEX, AdvancedINT, Bonus, Rank, RankGoalExp, CurrentHP, HP, CurrentMP, MP, Fame, Gold, GuildID, BladeLevel, BladeGoalExp, SwordLevel, SwordGoalExp, GunLevel, GunGoalExp, EnchantLevel, EnchantGoalExp, HealLevel, HealGoalExp, ETCLevel, ETCGoalExp, ZoneID, XCoord, YCoord, Sight, GunBonusExp, RifleBonusExp, Alignment, StashGold, StashNum, ResurrectZone, Reward, SMSCharge FROM Slayer WHERE Name = '%s' AND Active = 'ACTIVE'", m_Name.c_str());

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

		m_pAdvancementClass = new AdvancementClass(advLevel, advGoalExp, AdvancementClassExpTable::s_AdvancementClassExpTable);
		if (getAdvancementClassLevel() > 0 ) m_bAdvanced = true;

		int competence = pResult->getInt(++i);
		if (competence >= 4 ) competence = 3;

		setCompetence(competence);
		setCompetenceShape(pResult->getInt(++i));
		setSex(pResult->getString(++i));
//		setMasterEffectColor(pResult->getInt(++i));
		setHairStyle(pResult->getString(++i));
		setHairColor(pResult->getInt(++i));
		setSkinColor(pResult->getInt(++i));
		setPhoneNumber(atoi(pResult->getString(++i)));
		setMasterEffectColor(pResult->getInt(++i));

		m_STR[ATTR_BASIC]   = pResult->getInt(++i);
		m_STR[ATTR_MAX]     = m_STR[ATTR_BASIC];
		m_STR[ATTR_CURRENT] = m_STR[ATTR_BASIC];
//		m_STRExp            = pResult->getInt(++i);
		Exp_t STRGoalExp        = pResult->getInt(++i);

		m_pAttrs[ATTR_KIND_STR] = new Attr(m_STR[ATTR_BASIC], STRGoalExp, SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_STR]);

		m_DEX[ATTR_BASIC]   = pResult->getInt(++i);
		m_DEX[ATTR_MAX]     = m_DEX[ATTR_BASIC];
		m_DEX[ATTR_CURRENT] = m_DEX[ATTR_BASIC];
//		m_DEXExp            = pResult->getInt(++i);
		Exp_t DEXGoalExp        = pResult->getInt(++i);

		m_pAttrs[ATTR_KIND_DEX] = new Attr(m_DEX[ATTR_BASIC], DEXGoalExp, SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_DEX]);
		
		m_INT[ATTR_BASIC]   = pResult->getInt(++i);
		m_INT[ATTR_MAX]     = m_INT[ATTR_BASIC];
		m_INT[ATTR_CURRENT] = m_INT[ATTR_BASIC];
//		m_INTExp            = pResult->getInt(++i);
		Exp_t INTGoalExp        = pResult->getInt(++i);

		m_pAttrs[ATTR_KIND_INT] = new Attr(m_INT[ATTR_BASIC], INTGoalExp, SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_INT]);

		m_AdvancedSTR = pResult->getInt(++i);
		m_AdvancedDEX = pResult->getInt(++i);
		m_AdvancedINT = pResult->getInt(++i);
		m_AdvancedAttrBonus = pResult->getInt(++i);
		
		Rank_t CurRank               = pResult->getInt(++i);
//		RankExp_t RankExp            = pResult->getInt(++i);
		RankExp_t RankGoalExp        = pResult->getInt(++i);

		m_pRank = new Rank(CurRank, RankGoalExp, RankExpTable::s_RankExpTables[RANK_TYPE_SLAYER]);
//		cout << getRankGoalExp() << endl;

		//cout << "Slayer::load() : STR[CURRENT]" << (int)m_STR[ATTR_CURRENT] << endl;
		//cout << "Slayer::load() : STR[MAX]" << (int)m_STR[ATTR_MAX] << endl;
		//cout << "Slayer::load() : STR[BASIC]" << (int)m_STR[ATTR_BASIC] << endl;
		//cout << "Slayer::load() : DEX[CURRENT]" << (int)m_DEX[ATTR_CURRENT] << endl;
		//cout << "Slayer::load() : DEX[MAX]" << (int)m_DEX[ATTR_MAX] << endl;
		//cout << "Slayer::load() : DEX[BASIC]" << (int)m_DEX[ATTR_BASIC] << endl;
		//cout << "Slayer::load() : INT[CURRENT]" << (int)m_INT[ATTR_CURRENT] << endl;
		//cout << "Slayer::load() : INT[MAX]" << (int)m_INT[ATTR_MAX] << endl;
		//cout << "Slayer::load() : INT[BASIC]" << (int)m_INT[ATTR_BASIC] << endl;

		m_HP[ATTR_CURRENT]  = pResult->getInt(++i);
		m_HP[ATTR_MAX]      = pResult->getInt(++i);
		m_HP[ATTR_BASIC]    = 0;

		m_MP[ATTR_CURRENT]  = pResult->getInt(++i);
		m_MP[ATTR_MAX]      = pResult->getInt(++i);
		m_MP[ATTR_BASIC]    = 0;

		setFame(pResult->getInt(++i));
		setGold(pResult->getInt(++i));
		setGuildID(pResult->getInt(++i));
		//setInMagics(pResult->getString(++i));

		setSkillDomainLevel(SKILL_DOMAIN_BLADE,   pResult->getInt(++i));
//		setSkillDomainExp  (SKILL_DOMAIN_BLADE,   pResult->getInt(++i));
		setGoalExp         (SKILL_DOMAIN_BLADE,   pResult->getInt(++i));
		setSkillDomainLevel(SKILL_DOMAIN_SWORD,   pResult->getInt(++i));
//		setSkillDomainExp  (SKILL_DOMAIN_SWORD,   pResult->getInt(++i));
		setGoalExp         (SKILL_DOMAIN_SWORD,   pResult->getInt(++i));
		setSkillDomainLevel(SKILL_DOMAIN_GUN,     pResult->getInt(++i));
//		setSkillDomainExp  (SKILL_DOMAIN_GUN,     pResult->getInt(++i));
		setGoalExp         (SKILL_DOMAIN_GUN,     pResult->getInt(++i));
		//setSkillDomainLevel(SKILL_DOMAIN_RIFLE   , pResult->getInt(++i));
		//setSkillDomainExp(SKILL_DOMAIN_RIFLE   , pResult->getInt(++i));
		//setGoalExp(SKILL_DOMAIN_RIFLE	  , pResult->getInt(++i));
		setSkillDomainLevel(SKILL_DOMAIN_ENCHANT, pResult->getInt(++i));
//		setSkillDomainExp  (SKILL_DOMAIN_ENCHANT, pResult->getInt(++i));
		setGoalExp         (SKILL_DOMAIN_ENCHANT, pResult->getInt(++i));
		setSkillDomainLevel(SKILL_DOMAIN_HEAL,    pResult->getInt(++i));
//		setSkillDomainExp  (SKILL_DOMAIN_HEAL,    pResult->getInt(++i));
		setGoalExp         (SKILL_DOMAIN_HEAL,    pResult->getInt(++i));
		setSkillDomainLevel(SKILL_DOMAIN_ETC,     pResult->getInt(++i));
//		setSkillDomainExp  (SKILL_DOMAIN_ETC,     pResult->getInt(++i));
		setGoalExp         (SKILL_DOMAIN_ETC,     pResult->getInt(++i));

//		setZoneID(pResult->getInt(++i));
		ZoneID_t zoneID = pResult->getInt(++i);
		setX(pResult->getInt(++i));
		setY(pResult->getInt(++i));

		setSight(pResult->getInt(++i));
		setSight(13);
		setGunBonusExp(pResult->getInt(++i));
		setRifleBonusExp(pResult->getInt(++i));
		setAlignment(pResult->getInt(++i));

//		for (int j = 0; j < 4; j++) setHotKey(j, pResult->getInt(++i));

		setStashGold(pResult->getInt(++i));
		setStashNum(pResult->getBYTE(++i));
		setResurrectZoneID(pResult->getInt(++i));

		reward = pResult->getInt(++i);
		setSMSCharge(pResult->getInt(++i));

		// 그냥 다시 계산해버린다. 2002.7.15 by sigi
		// 공식 바뀌면 AbilityBalance.cpp의 computeHP도 수정해야한다.
//		m_HP[ATTR_MAX]      = m_STR[ATTR_CURRENT]*2;

		try
		{
			setZoneID(zoneID);
		}
		catch (Error& e )
		{
			// 길드 아지트 문제로 본다.
			// 길드 아지트가 한 게임 서버에만 존재하므로 다른 게임서버로 접속할 때 그 아지트로 들어가지 못한다.
			ZONE_COORD ResurrectCoord;
			g_pResurrectLocationManager->getSlayerPosition(12, ResurrectCoord);
			setZoneID(ResurrectCoord.id);
			setX(ResurrectCoord.x);
			setY(ResurrectCoord.y);
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	// zone 의 object registery 에 접근한다.
	ObjectRegistry & OR = getZone()->getObjectRegistry();
	OR.registerObject(this);

/*	if (reward != 0)
	{
		uint MaxExp     = 0;
		uint DomainType = SKILL_DOMAIN_MAX;
		uint sum        = 0;

		for (int i=0; i<SKILL_DOMAIN_VAMPIRE; i++)
		{
			if (MaxExp <= m_SkillDomainExps[i])
			{
				MaxExp     = m_SkillDomainExps[i];
				DomainType = i;
			}

			sum += m_SkillDomainLevels[i];
		}

		bool bSuccess = false;

		switch (DomainType)
		{
			case SKILL_DOMAIN_SWORD:
			case SKILL_DOMAIN_BLADE:
			case SKILL_DOMAIN_GUN:
			case SKILL_DOMAIN_ENCHANT:
			case SKILL_DOMAIN_HEAL:
				bSuccess = true;
				break;
			default:
				bSuccess = false;
				break;
		}

		if (bSuccess)
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("UPDATE Slayer SET Reward = 0 WHERE Name='%s'", m_Name.c_str());
				SAFE_DELETE(pStmt);
			} 
			END_DB(pStmt)

			GCModifyInformation gcModifyInformation;
			
			if (0 <= sum && sum <= 10)
			{
				for (int count=0; count<5; count++)
				{
					setGoalExp(DomainType, 1);
					increaseDomainExp(this, DomainType, 1, gcModifyInformation);
				}

				for (int count=0; count<4; count++)
				{
					m_STRGoalExp = 1; m_DEXGoalExp = 1; m_INTGoalExp = 1;
					divideAttrExp(this, 1, 1, 1, 1, gcModifyInformation, 0);
				}
			}
			else if (11 <= sum && sum <= 20)
			{
				for (int count=0; count<4; count++)
				{
					setGoalExp(DomainType, 1);
					increaseDomainExp(this, DomainType, 1, gcModifyInformation);
				}

				for (int count=0; count<3; count++)
				{
					m_STRGoalExp = 1; m_DEXGoalExp = 1; m_INTGoalExp = 1;
					divideAttrExp(this, 1, 1, 1, 1, gcModifyInformation, 0);
				}
			}
			else if (21 <= sum && sum <= 30)
			{
				for (int count=0; count<2; count++)
				{
					setGoalExp(DomainType, 1);
					increaseDomainExp(this, DomainType, 1, gcModifyInformation);
				}

				for (int count=0; count<2; count++)
				{
					m_STRGoalExp = 1; m_DEXGoalExp = 1; m_INTGoalExp = 1;
					divideAttrExp(this, 1, 1, 1, 1, gcModifyInformation, 0);
				}
			}
			else
			{
				for (int count=0; count<1; count++)
				{
					setGoalExp(DomainType, 1);
					increaseDomainExp(this, DomainType, 1, gcModifyInformation);
				}

				for (int count=0; count<1; count++)
				{
					m_STRGoalExp = 1; m_DEXGoalExp = 1; m_INTGoalExp = 1;
					divideAttrExp(this, 1, 1, 1, 1, gcModifyInformation, 0);
				}
			}
		}
	}
*/
	// Slayer Outlook Information 을 구성한다.
	m_SlayerInfo.setObjectID(m_ObjectID);
    m_SlayerInfo.setName(m_Name);
    m_SlayerInfo.setX(m_X);
    m_SlayerInfo.setY(m_Y);
    m_SlayerInfo.setDir(m_Dir);
    m_SlayerInfo.setSex(m_Sex);
    m_SlayerInfo.setHairStyle(m_HairStyle);

	// 0이나 1 권한을 가지고 있으면
	// 운영자로 스프라이트를 출력해줘야 한다. 
	m_SlayerInfo.setCompetence(m_CompetenceShape);

	// 스킬을 로딩한다.
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT SkillType, SkillLevel, SkillExp, Delay, CastingTime, NextTime FROM SkillSave WHERE OwnerID = '%s'", m_Name.c_str());

		while(pResult->next()) 
		{
			int        i          = 0;
			SkillSlot* pSkillSlot = new SkillSlot();

			pSkillSlot->setName(m_Name);
			pSkillSlot->setSkillType(pResult->getInt(++i));
			pSkillSlot->setExpLevel(pResult->getInt(++i));
			pSkillSlot->setExp (pResult->getInt(++i));

			pSkillSlot->setInterval (pResult->getInt(++i));

			pSkillSlot->setCastingTime (pResult->getInt(++i));
			//pSkillSlot->setRunTime (pResult->getInt(++i));
			pSkillSlot->setRunTime();

			// 이 스킬을 쓸 수 있는지 없는지 체크 한돠..
			// 스킬인포를 받아온다.
			SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo(pSkillSlot->getSkillType());
			Assert(pSkillInfo != NULL);

			// 배우는 레벨보다 지금 현재의 도메인 레벨이 낮으면 당연히 못쓴다.
			if(pSkillInfo->getLevel() > m_SkillDomainLevels[pSkillInfo->getDomainType()] && pSkillInfo->getDomainType() != SKILL_DOMAIN_ETC ) 
			{
				pSkillSlot->setDisable();
			}

			addSkill(pSkillSlot);
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	// 이펙트를 로딩한다.
	g_pEffectLoaderManager->load(this);

	// Rank Bonus 를 로딩한다.
	loadRankBonus();

	// GrandMaster인 경우는 Effect를 붙여준다.
	// by sigi. 2002.11.8
	if (getHighestSkillDomainLevel()>=100
		&& SystemAvailabilitiesManager::getInstance()->isAvailable(SystemAvailabilitiesManager::SYSTEM_GRAND_MASTER_EFFECT ) )
	{
		if (!isFlag(Effect::EFFECT_CLASS_GRAND_MASTER_SLAYER))
		{
			EffectGrandMasterSlayer* pEffect = new EffectGrandMasterSlayer(this);
			pEffect->setDeadline(999999);
			getEffectManager()->addEffect(pEffect);
			setFlag(Effect::EFFECT_CLASS_GRAND_MASTER_SLAYER);
		}
	}


	// 플래그 셋을 로드한다.
	m_pFlagSet->load(getName());

	// Slayer Outlook Information 을 구성한다.
	m_SlayerInfo.setHelmetType(HELMET_NONE);
	m_SlayerInfo.setJacketType(JACKET_BASIC);
	m_SlayerInfo.setPantsType(PANTS_BASIC);
	m_SlayerInfo.setWeaponType(WEAPON_NONE); 
	m_SlayerInfo.setShieldType(SHIELD_NONE); 
	m_SlayerInfo.setMotorcycleType(MOTORCYCLE_NONE);
    m_SlayerInfo.setMasterEffectColor(m_HairColor);
    m_SlayerInfo.setHairColor(m_HairColor);
    m_SlayerInfo.setSkinColor(m_SkinColor);
	m_SlayerInfo.setShoulderType(0);

	m_SlayerInfo.setAdvancementLevel(getAdvancementClassLevel());

	// 잘못된 경험치를 재조정 해준다.
/*	STRBalanceInfo* pSTRInfo = g_pSTRBalanceInfoManager->getSTRBalanceInfo(m_STR[ATTR_BASIC]);

	if (pSTRInfo->getAccumExp() != m_STRExp + m_STRGoalExp) 
	{
		//ofstream file("능력치조정.txt", ios::out | ios::app);
		//file << "NAME:" << m_Name << endl;
		//file << "==STR==" << endl;
		//file << "현재레벨의총경험치 : " << (int)pSTRInfo->getAccumExp() << endl;
		//file << "현재 누적 경험치 : " << (int)m_STRExp << endl;
		//file << "현재 목표 경험치 : " << (int)m_STRGoalExp << endl;
		//file << endl;

		// 현재 목표 경험치가 현재 레벨의 목표 경험치 보다 크다면, 재 설정 해준다.
		if (m_STRGoalExp > pSTRInfo->getGoalExp()) 
		{
			m_STRGoalExp = pSTRInfo->getGoalExp();
		}

		// 이전 레벨의 인포를 받아온다.
		STRBalanceInfo* pBeforeSTRInfo = g_pSTRBalanceInfoManager->getSTRBalanceInfo(m_STR[ATTR_BASIC] - 1);
		// 이전 레벨의 총 경험치 + 목표 경험치 변화량 = 현재 누적 경험치
		m_STRExp = pBeforeSTRInfo->getAccumExp() + (pSTRInfo->getGoalExp() - m_STRGoalExp);

		//file << "수정된 누적 경험치 : " << (int)m_STRExp << endl;
		//file << "수정된 목표 경험치 : " << (int)m_STRGoalExp << endl;

//		StringStream attrsave;
//		attrsave << "STRExp = " << (int)m_STRExp << ", STRGoalExp = " << (int)m_STRGoalExp;
//		tinysave(attrsave.toString());

		// by sigi. 2002.5.15
		char pField[80];
		sprintf(pField, "STRExp=%lu, STRGoalExp=%lu", m_STRExp, m_STRGoalExp);
		tinysave(pField);
		
		//file.close();
	}

	// 잘못된 경험치를 재조정 해준다.
	DEXBalanceInfo* pDEXInfo = g_pDEXBalanceInfoManager->getDEXBalanceInfo(m_DEX[ATTR_BASIC]);

	if (pDEXInfo->getAccumExp() != m_DEXExp + m_DEXGoalExp) 
	{
		//ofstream file("능력치조정.txt", ios::out | ios::app);
		//file << "NAME:" << m_Name << endl;
		//file << "==DEX==" << endl;
		//file << "현재레벨의총경험치 : " << (int)pDEXInfo->getAccumExp() << endl;
		//file << "현재 누적 경험치 : " << (int)m_DEXExp << endl;
		//file << "현재 목표 경험치 : " << (int)m_DEXGoalExp << endl;
		//file << endl;

		// 현재 목표 경험치가 현재 레벨의 목표 경험치 보다 크다면, 재 설정 해준다.
		if (m_DEXGoalExp > pDEXInfo->getGoalExp()) 
		{
			m_DEXGoalExp = pDEXInfo->getGoalExp();
		}

		// 이전 레벨의 인포를 받아온다.
		DEXBalanceInfo* pBeforeDEXInfo = g_pDEXBalanceInfoManager->getDEXBalanceInfo(m_DEX[ATTR_BASIC] - 1);
		// 이전 레벨의 총 경험치 + 목표 경험치 변화량 = 현재 누적 경험치
		m_DEXExp = pBeforeDEXInfo->getAccumExp() + (pDEXInfo->getGoalExp() - m_DEXGoalExp);

		//file << "수정된 누적 경험치 : " << (int)m_DEXExp << endl;
		//file << "수정된 목표 경험치 : " << (int)m_DEXGoalExp << endl;

//		StringStream attrsave;
//		attrsave << "DEXExp = " << (int)m_DEXExp << ", DEXGoalExp = " << (int)m_DEXGoalExp;
//		tinysave(attrsave.toString());

		// by sigi. 2002.5.15
		char pField[80];
		sprintf(pField, "DEXExp=%lu, DEXGoalExp=%lu", m_DEXExp, m_DEXGoalExp);
		tinysave(pField);
		
		//file.close();
	}

	// 잘못된 경험치를 재조정 해준다.
	INTBalanceInfo* pINTInfo = g_pINTBalanceInfoManager->getINTBalanceInfo(m_INT[ATTR_BASIC]);

	if (pINTInfo->getAccumExp() != m_INTExp + m_INTGoalExp) 
	{
		//ofstream file("능력치조정.txt", ios::out | ios::app);
		//file << "NAME:" << m_Name << endl;
		//file << "==INT==" << endl;
		//file << "현재레벨의총경험치 : " << (int)pINTInfo->getAccumExp() << endl;
		//file << "현재 누적 경험치 : " << (int)m_INTExp << endl;
		//file << "현재 목표 경험치 : " << (int)m_INTGoalExp << endl;
		//file << endl;

		// 현재 목표 경험치가 현재 레벨의 목표 경험치 보다 크다면, 재 설정 해준다.
		if (m_INTGoalExp > pINTInfo->getGoalExp()) 
		{
			m_INTGoalExp = pINTInfo->getGoalExp();
		}

		// 이전 레벨의 인포를 받아온다.
		INTBalanceInfo* pBeforeINTInfo = g_pINTBalanceInfoManager->getINTBalanceInfo(m_INT[ATTR_BASIC] - 1);
		// 이전 레벨의 총 경험치 + 목표 경험치 변화량 = 현재 누적 경험치
		m_INTExp = pBeforeINTInfo->getAccumExp() + (pINTInfo->getGoalExp() - m_INTGoalExp);

		//file << "수정된 누적 경험치 : " << (int)m_INTExp << endl;
		//file << "수정된 목표 경험치 : " << (int)m_INTGoalExp << endl;

//		StringStream attrsave;
//		attrsave << "INTExp = " << (int)m_INTExp << ", INTGoalExp = " << (int)m_INTGoalExp;
//		tinysave(attrsave.toString());

		// by sigi. 2002.5.15
		char pField[80];
		sprintf(pField, "INTExp=%lu, INTGoalExp=%lu", m_INTExp, m_INTGoalExp);
		tinysave(pField);
		
		
		//file.close();
	}
*/

	// rank가 0이면 초기값이 설정되지 않았다는 의미이다.
	if (getRank()==0)
	{
		saveInitialRank();
	}

	// 잘못된 경험치를 재조정 해준다.
	// by sigi. 2002.8.31
/*	RankEXPInfo* pRankInfo = g_pRankEXPInfoManager[RANK_TYPE_SLAYER]->getRankEXPInfo(m_Rank);
	
	if (m_Rank>1 && pRankInfo->getAccumExp() != m_RankExp + m_RankGoalExp) 
	{
		//ofstream file("능력치조정.txt", ios::out | ios::app);
		//file << "NAME:" << m_Name << endl;
		//file << "==Rank==" << endl;
		//file << "현재레벨의총경험치 : " << (int)pRankInfo->getAccumExp() << endl;
		//file << "현재 누적 경험치 : " << (int)m_RankExp << endl;
		//file << "현재 목표 경험치 : " << (int)m_RankGoalExp << endl;
		//file << endl;

		// 현재 목표 경험치가 현재 레벨의 목표 경험치 보다 크다면, 재 설정 해준다.
		if (m_RankGoalExp > pRankInfo->getGoalExp()) 
		{
			m_RankGoalExp = pRankInfo->getGoalExp();
		}

		// 이전 레벨의 인포를 받아온다.
		RankEXPInfo* pBeforeRankInfo = g_pRankEXPInfoManager[RANK_TYPE_SLAYER]->getRankEXPInfo(m_Rank - 1);
		// 이전 레벨의 총 경험치 + 목표 경험치 변화량 = 현재 누적 경험치
		m_RankExp = pBeforeRankInfo->getAccumExp() + (pRankInfo->getGoalExp() - m_RankGoalExp);

		//file << "수정된 누적 경험치 : " << (int)m_RankExp << endl;
		//file << "수정된 목표 경험치 : " << (int)m_RankGoalExp << endl;

//		StringStream attrsave;
//		attrsave << "RankExp = " << (int)m_RankExp << ", RankGoalExp = " << (int)m_RankGoalExp;
//		tinysave(attrsave.toString());

		// by sigi. 2002.5.15
		char pField[80];
		sprintf(pField, "RankExp=%lu, RankGoalExp=%lu", m_RankExp, m_RankGoalExp);
		tinysave(pField);
		
		
		//file.close();
	}
*/

	// 잘못된 도메인 경험치를 보정한다.
/*	for (int i = 0; i < SKILL_DOMAIN_ETC; i++) 
	{
		DomainInfo* pDomainInfo = g_pSkillDomainInfoManager->getDomainInfo((SkillDomain)i , m_SkillDomainLevels[i]); 
		Assert(pDomainInfo!=NULL);

		if (pDomainInfo->getAccumExp() != m_SkillDomainExps[i] + m_GoalExp[i] 
			&& m_SkillDomainLevels[i] > 0) 
		{
			//ofstream file("도메인조정.txt", ios::out | ios::app);
			//file << "NAME:" << m_Name << endl;
			//file << "==" << i << "==" << endl;
			//file << "현재레벨의총경험치 : " << (int)pDomainInfo->getAccumExp() << endl;
			//file << "현재 누적 경험치 : " << (int)m_SkillDomainExps[i] << endl;
			//file << "현재 목표 경험치 : " << (int)m_GoalExp[i] << endl;
			//file << endl;

			// 현재 목표 경험치가 현재 레벨의 목표 경험치 보다 크다면, 재 설정 해준다.
			if (m_GoalExp[i] > pDomainInfo->getGoalExp()) 
			{
				m_GoalExp[i] = pDomainInfo->getGoalExp();
			}

			// 이전 레벨의 인포를 받아온다.
			DomainInfo* pBeforeDomainInfo = g_pSkillDomainInfoManager->getDomainInfo((SkillDomain)i , (m_SkillDomainLevels[i] - 1)); 
			// 이전 레벨의 총 경험치 + 목표 경험치 변화량 = 현재 누적 경험치
			m_SkillDomainExps[i] = pBeforeDomainInfo->getAccumExp() + (pDomainInfo->getGoalExp() - m_GoalExp[i]);

			//file << "수정된 누적 경험치 : " << (int)m_SkillDomainExps[i] << endl;
			//file << "수정된 목표 경험치 : " << (int)m_GoalExp[i] << endl;

			//StringStream attrsave;
			// by sigi. 2002.5.15
			char pField[80];
			pField[0] = '\0';

			if (i == SKILL_DOMAIN_BLADE) 
			{
				//attrsave << "BladeExp = " << (int)m_SkillDomainExps[i] << ", BladeGoalExp = " << (int)m_GoalExp[i];
				sprintf(pField, "BladeExp=%lu, BladeGoalExp=%lu", m_SkillDomainExps[i], m_GoalExp[i]);
			} 
			else if (i == SKILL_DOMAIN_SWORD) 
			{
				//attrsave << "SwordExp = " << (int)m_SkillDomainExps[i] << ", SwordGoalExp = " << (int)m_GoalExp[i];
				sprintf(pField, "SwordExp=%lu, SwordGoalExp=%lu", m_SkillDomainExps[i], m_GoalExp[i]);
			} 
			else if (i == SKILL_DOMAIN_GUN) 
			{
				//attrsave << "GunExp = " << (int)m_SkillDomainExps[i] << ", GunGoalExp = " << (int)m_GoalExp[i];
				sprintf(pField, "GunExp=%lu, GunGoalExp=%lu", m_SkillDomainExps[i], m_GoalExp[i]);
			}
			else if (i == SKILL_DOMAIN_HEAL) 
			{
				//attrsave << "HealExp = " << (int)m_SkillDomainExps[i] << ", HealGoalExp = " << (int)m_GoalExp[i];
				sprintf(pField, "HealExp=%lu, HealGoalExp=%lu", m_SkillDomainExps[i], m_GoalExp[i]);
			}
			else if (i == SKILL_DOMAIN_ENCHANT) 
			{
				//attrsave << "EnchantExp = " << (int)m_SkillDomainExps[i] << ", EnchantGoalExp = " << (int)m_GoalExp[i];
				sprintf(pField, "EnchantExp=%lu, EnchantGoalExp=%lu", m_SkillDomainExps[i], m_GoalExp[i]);
			}

			//tinysave(attrsave.toString());
			if (pField[0]!='\0')
				tinysave(pField);

			//file.close();
		}
	}*/

	// 모든 능력치를 로드했기 때문에,
	// 이걸 기본으로 부가 능력치를 초기화한다.
	initAllStat();

	// 전쟁 참가 Flag 체크
	if (RaceWarLimiter::isInPCList(this ) )
	{
		setFlag(Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET);
	}

	if (m_pZone->isHolyLand() 
		&& g_pWarSystem->hasActiveRaceWar()
		&& !isFlag(Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET ))
	{
		ZONE_COORD ResurrectCoord;
		g_pResurrectLocationManager->getPosition(this, ResurrectCoord);
		setZoneID(ResurrectCoord.id);
		setX(ResurrectCoord.x);
		setY(ResurrectCoord.y);
	}

	return true;

	__END_CATCH
}

void Slayer::save () const
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		/*
		// StringStream 안쓰기. by sigi. 2002.5.9
		StringStream sql;
		sql << "UPDATE Slayer SET"
			//<< " Competence = " << (int)m_Competence
			//<< ", HairStyle = '" << HairStyle2String[m_HairStyle]
			//<< "', HairColor = " << (int)m_HairColor
			//<< ", SkinColor = " << (int)m_SkinColor
			//<< ", STR = " << (int)m_STR[ATTR_MAX]
			//<< ", DEX = " << (int)m_DEX[ATTR_MAX]
			//<< ", INTE = " << (int)m_INT[ATTR_MAX]
			//<< ", STRExp = " << m_STRExp
			//<< ", DEXExp = " << m_DEXExp
			//<< ", INTExp = " << m_INTExp
			//<< ", STRExpLevel = " << (int)m_STRExpLevel
			//<< ", DEXExpLevel = " << (int)m_DEXExpLevel
			//<< ", INTExpLevel = " << (int)m_INTExpLevel
			<< " CurrentHP = " << m_HP[ATTR_CURRENT]
			<< ", HP = " << m_HP[ATTR_MAX]
			<< ", CurrentMP = " << m_MP[ATTR_CURRENT]
			<< ", MP = " << m_MP[ATTR_MAX]
			//<< ", Fame = " << m_Fame
			//<< ", Gold = " << m_Gold
			//<< ", GuildID = " << m_GuildID
			//<< ", InMagics = '" << ??? << "'"
			//<< ", BladeLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_BLADE]
			//<< ", BladeExp = " << m_SkillDomainExps[SKILL_DOMAIN_BLADE]
			//<< ", BladeGoalExp = " << m_GoalExp[SKILL_DOMAIN_BLADE]
			//<< ", SwordLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_SWORD]
			//<< ", SwordExp = " << m_SkillDomainExps[SKILL_DOMAIN_SWORD]
			//<< ", SwordGoalExp = " << m_GoalExp[SKILL_DOMAIN_SWORD]
			//<< ", GunLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_GUN]
			//<< ", GunExp = " << m_SkillDomainExps[SKILL_DOMAIN_GUN]
			//<< ", GunGoalExp = " << m_GoalExp[SKILL_DOMAIN_GUN]
			//<< ", RifleLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_RIFLE]
			//<< ", RifleExp = " << m_SkillDomainExps[SKILL_DOMAIN_RIFLE]
			//<< ", RifleGoalExp = " << m_GoalExp[SKILL_DOMAIN_RIFLE]
			//<< ", EnchantLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_ENCHANT]
			//<< ", EnchantExp = " << m_SkillDomainExps[SKILL_DOMAIN_ENCHANT]
			//<< ", EnchantGoalExp = " << m_GoalExp[SKILL_DOMAIN_ENCHANT]
			//<< ", HealLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_HEAL]
			//<< ", HealExp = " << m_SkillDomainExps[SKILL_DOMAIN_HEAL]
			//<< ", HealGoalExp = " << m_GoalExp[SKILL_DOMAIN_HEAL]
			//<< ", ETCLevel = " << (int)m_SkillDomainLevels[SKILL_DOMAIN_ETC]
			//<< ", ETCExp = " << m_SkillDomainExps[SKILL_DOMAIN_ETC]
			//<< ", ETCGoalExp = " << m_GoalExp[SKILL_DOMAIN_ETC]
			//<< ", SubSkills = '" << ??? << "'"
			<< ", ZoneID = " << getZoneID()
			<< ", XCoord = " << (int)m_X
			<< ", YCoord = " << (int)m_Y
			//<< ", Sight = " << (int)m_Sight
			//<< ", GunBonusExp = " << (int)m_GunBonusExp
			//<< ", RifleBonusExp = " << (int)m_GunBonusExp
			<< ", F9 = " << (int)m_HotKey[0]
			<< ", F10 = " << (int)m_HotKey[1]
			<< ", F11 = " << (int)m_HotKey[2]
			<< ", F12 = " << (int)m_HotKey[3]
			<< "  WHERE Name = '" << m_Name << "'";

			pStmt->executeQuery(sql.toString());
		*/

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE Slayer SET CurrentHP=%d, HP=%d, CurrentMP=%d, MP=%d, ZoneID=%d, XCoord=%d, YCoord=%d WHERE Name='%s'",
								m_HP[ATTR_CURRENT], m_HP[ATTR_MAX], m_MP[ATTR_CURRENT], m_MP[ATTR_MAX], getZoneID(), (int)m_X, (int)m_Y, m_Name.c_str());


		// 일반적으로, 아무런 데이타도 바뀌지 않았을 경우
		// #Affected Rows == 0 이다. 그런데, 대부분의 경우
		// 데이타가 약간이라도 바뀌게 된다. 그러나, 안바뀔
		// 가능성도 있다. 따라서, AffectedRows 는 체크되지
		// 않아야 한다.
		//Assert(pStmt->getAffectedRowCount() == 1);

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	/*
	// 인벤토리의 아이템들을 세이브 한다.
	m_pInventory->save(m_Name);
	*/

	// 이펙트를 세이브 한다.
	m_pEffectManager->save(m_Name);

	// 오토바이를 세이브 한다.
	if (m_pMotorcycle != NULL) 
	{
		//m_pMotorcycle->save("", STORAGE_ZONE, m_pZone->getZoneID(), m_X, m_Y);
		// by sigi. 2002.5.15
		char pField[80];

		sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d",
									STORAGE_ZONE, m_pZone->getZoneID(), m_X, m_Y);
		m_pMotorcycle->tinysave(pField);
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

// tinysave
void Slayer::tinysave(const string & field)
    const throw(Error)
{
    __BEGIN_TRY

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Slayer SET %s WHERE NAME='%s'", field.c_str(), m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

    __END_CATCH
}

PhoneNumber_t Slayer::getPhoneSlotNumber(SlotID_t SlotID)
	throw()
{
	__BEGIN_TRY

	Assert(SlotID <= MAX_PHONE_SLOT);

	return m_PhoneSlot[SlotID];

	__END_CATCH
}

void Slayer::setPhoneSlotNumber(SlotID_t SlotID, PhoneNumber_t PhoneNumber)
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_PhoneSlot[SlotID] = PhoneNumber;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

bool Slayer::isSlotByPhoneNumber(PhoneNumber_t PhoneNumber)
	throw()
{
	__BEGIN_TRY

	bool isFind = false;

	for (int i = 0; i < MAX_PHONE_SLOT; i++) 
	{
		if (m_PhoneSlot[i] == PhoneNumber) isFind = true;
	}

	return isFind;

	__END_CATCH
}

SlotID_t Slayer::getSlotWithPhoneNumber(PhoneNumber_t PhoneNumber)
	throw()
{
	__BEGIN_TRY

	for (int i = 0; i < MAX_PHONE_SLOT; i++) {

		if (m_PhoneSlot[i] == PhoneNumber) return i;
	}

	return MAX_PHONE_SLOT;

	__END_CATCH
}

SlotID_t Slayer::findEmptyPhoneSlot()
	throw()
{
	__BEGIN_TRY

	for (int i = 0; i < MAX_PHONE_SLOT; i++) 
	{
		if (m_PhoneSlot[i] == 0) 
		{
			return i;
		}
	}

	return MAX_PHONE_SLOT;

	__END_CATCH
}

bool Slayer::isEmptyPhoneSlot()
	throw()
{
	__BEGIN_TRY

	bool Success = false;

	for (int i = 0; i < MAX_PHONE_SLOT; i++) 
	{
		if (m_PhoneSlot[i] == 0) 
		{
			// 빈 슬랏을 찾았다.
			Success = true;
		}
	}

	return Success;

	__END_CATCH
}

// 특정 Skill이 존재하는지 조사하고 SkillSlot을 리턴한다.
SkillSlot* Slayer::getSkill(SkillType_t SkillType) const
	throw()
{
	__BEGIN_TRY

	map<SkillType_t, SkillSlot*>::const_iterator itr = m_SkillSlot.find(SkillType);
	if (itr != m_SkillSlot.end())
	{
		return itr->second;
	}

	return NULL;

	__END_CATCH
}

// 특정 SkillSlot을 자동으로 빈 슬랏을 찾아 넣는다.
void Slayer::addSkill(SkillSlot* pSkillSlot)
	throw()
{
	__BEGIN_TRY

	SkillType_t SkillType = pSkillSlot->getSkillType();
	switch (SkillType)
	{
		case SKILL_UN_BURROW:
		case SKILL_UN_TRANSFORM:
		case SKILL_UN_INVISIBILITY:
		case SKILL_THROW_HOLY_WATER:
		case SKILL_EAT_CORPSE:
		case SKILL_HOWL:
			filelog("SlayerError.log", "SkillType[%d], %s", SkillType, toString().c_str());
			Assert(false);
			break;
		default:
			break;
	}

	map<SkillType_t, SkillSlot*>::iterator itr = m_SkillSlot.find(pSkillSlot->getSkillType());
	
	if (itr == m_SkillSlot.end())
	{
		m_SkillSlot[pSkillSlot->getSkillType()] = pSkillSlot;
	}
	// 2002.1.16 by sigi
	// 2003.3.30 by Sequoia 조건 추가함
	else
	{
		if (pSkillSlot != itr->second ) SAFE_DELETE(pSkillSlot);
	}

	__END_CATCH
}

// 기술을 배울때만 쓰는 함수이다. 다른 곳에서 쓰면 개 된다.
void Slayer::addSkill(SkillType_t SkillType)
	throw()
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
			filelog("SlayerError.log", "2 SkillType[%d], %s", SkillType, toString().c_str());
			Assert(false);
			break;
		default:
			break;
	}

	map<SkillType_t, SkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);
	
	if (itr == m_SkillSlot.end())
	{
		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Turn_t Delay = pSkillInfo->getMaxDelay();

		SkillSlot* pSkillSlot = new SkillSlot();
		pSkillSlot->setName(m_Name);
		pSkillSlot->setSkillType(SkillType);
		pSkillSlot->setInterval(Delay);
		pSkillSlot->setExpLevel(0);
		pSkillSlot->setExp(1);
		pSkillSlot->setRunTime();
		pSkillSlot->create(m_Name);

		m_SkillSlot[SkillType] = pSkillSlot;
	}

	__END_CATCH
}

// 성지스킬을 지워주는 함수다.
void Slayer::removeCastleSkill(SkillType_t SkillType)
	throw()
{
	__BEGIN_TRY

	// 성지 스킬만 지울 수 있다.
	if (g_pCastleSkillInfoManager->getZoneID(SkillType ) == 0 ) return;

	map<SkillType_t, SkillSlot*>::iterator itr = m_SkillSlot.find(SkillType);
	
	if (itr != m_SkillSlot.end())
	{
		CastleSkillSlot* pCastleSkillSlot = dynamic_cast<CastleSkillSlot*>(itr->second);

		SAFE_DELETE(pCastleSkillSlot);

		m_SkillSlot.erase(itr);
	}

	__END_CATCH
}

// 갖고 있는 모든 성지스킬을 지워주는 함수이다.
void Slayer::removeAllCastleSkill()
	throw()
{
	__BEGIN_TRY

	map<SkillType_t, SkillSlot*>::iterator itr = m_SkillSlot.begin();

	while (itr != m_SkillSlot.end() )
	{
		if (itr->second != NULL )
		{
			SkillSlot* pSkillSlot = itr->second;
			if (g_pCastleSkillInfoManager->getZoneID(pSkillSlot->getSkillType() ) == 0 )
			{
				// 성지스킬이 아니면 다음껄로 넘어간다.
				++itr;
				continue;
			}

			// 성지스킬이면 지워준다. 반복자 사용에 주의
			SAFE_DELETE(pSkillSlot);
			map<SkillType_t, SkillSlot*>::iterator prevItr = itr;
			
			++itr;
			m_SkillSlot.erase(prevItr);
		}
		else
		{
			// 이건 멀까.... Assert 해야 되지 않나 -_-;
			Assert(false);
		}
	}

	__END_CATCH
}

// Slayer::wearItem()
// Item을 장착창에 장착시키고 능력치를 계산한다.
// 이 메소드는 접속할때 Item을 Loading 하면서 쓰는 wearItem이다.
// 이 메소드 안에선 Broadcast를 하지 않는 것이 좋다.
void Slayer::wearItem(WearPart Part, Item* pItem)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pItem != NULL);

	Item::ItemClass IClass    = pItem->getItemClass();
	Item*           pLeft     = NULL;
	Item*           pRight    = NULL;
	Item*           pPrevItem = NULL;
	OptionInfo*     pOptionInfo = NULL;

	// 첫번째 옵션의 색깔을 지정한다.
	if (pItem->getFirstOptionType() != 0)
		pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getFirstOptionType());

	// 현재 기획에서는...능력치가 모자라더라도 아이템을 무조건 사용할 수는
	// 있다. 하지만 아이템에 의한 능력치가 적용이 되지 않는다. 
	// 그러므로 일단 아이템을 해당하는 장착창에다 집어넣는다.
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
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				//pLeft->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
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
				cerr << "양손에 칼과 방패를 들고 있어서, 양손 무기를 장착할 수 없습니다." << endl;
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
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pRight);
				//pRight->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
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
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				//pLeft->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
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
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);
			}
		}
	}
	else
	{
		char pField[80];

		if (isWear(Part))
		{
			pPrevItem = getWearItem(Part);
			// 요구한 아이템을 장착 포인트에 넣는다.
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);

			// 원래 있던 아이템을 마우스 포인터에 달아 준다.
			addItemToExtraInventorySlot(pPrevItem);

			//pPrevItem->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pPrevItem->tinysave(pField);
		}
		else
		{
			// 요구한 아이템을 장착 포인트에 넣는다.
			m_pWearItem[Part] = pItem;
			//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);
		}
	}

	ItemType_t IType = pItem->getItemType();

	// 어떤 무기를 잡고 있다는 정보를 저장한다. 
	// SlayerInfo에 셋팅을 해 놓아야 다음 누군가가 볼때 날려준다.
	Color_t color = getItemShapeColor(pItem, pOptionInfo); 

	switch (IClass)
	{
		case Item::ITEM_CLASS_MACE:
			//m_SlayerInfo.setWeaponType(WEAPON_MACE);
			m_SlayerInfo.setWeaponType(WEAPON_MACE);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_CROSS:
			m_SlayerInfo.setWeaponType(WEAPON_CROSS);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_BLADE:
			m_SlayerInfo.setWeaponType(WEAPON_BLADE);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_AR:
			m_SlayerInfo.setWeaponType(WEAPON_AR);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_SR:
			m_SlayerInfo.setWeaponType(WEAPON_SR);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_SMG:
			m_SlayerInfo.setWeaponType(WEAPON_SMG);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_SG:
			m_SlayerInfo.setWeaponType(WEAPON_SG);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_HELM:
			m_SlayerInfo.setHelmetType(getHelmetType(IType));
			m_SlayerInfo.setHelmetColor(color);
			break;
		case Item::ITEM_CLASS_SHIELD:
			m_SlayerInfo.setShieldType(getShieldType(IType));
			m_SlayerInfo.setShieldColor(color);
			break;
		case Item::ITEM_CLASS_SWORD:
			m_SlayerInfo.setWeaponType(WEAPON_SWORD);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_COAT:
			m_SlayerInfo.setJacketType(getJacketType(IType));
			//cout << "Jacket: ItemType=" << (int)IType << ", JacketType=" << JacketType2String[m_SlayerInfo.getJacketType()] << endl;
			m_SlayerInfo.setJacketColor(color);
			break;
		case Item::ITEM_CLASS_TROUSER:
			m_SlayerInfo.setPantsType(getPantsType(IType));
			//cout << "Pants: ItemType=" << (int)IType << ", PantsType=" << PantsType2String[m_SlayerInfo.getPantsType()] << endl;
			m_SlayerInfo.setPantsColor(color);
			break;
		case Item::ITEM_CLASS_SHOULDER_ARMOR:
			m_SlayerInfo.setShoulderType(getShoulderType(IType));
			//cout << "Pants: ItemType=" << (int)IType << ", PantsType=" << PantsType2String[m_SlayerInfo.getPantsType()] << endl;
			m_SlayerInfo.setShoulderColor(color);
			break;
		default:
			break;
	}

	__END_DEBUG
	__END_CATCH
}

// Slayer::wearItem()
// Item을 장착창에 장착시키고 능력치를 계산한다.
void Slayer::wearItem(WearPart Part)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// 장착 준비중인 아이템을 받아온다.
	Item* pItem = getExtraInventorySlotItem();
	Assert(pItem != NULL);

	Item::ItemClass IClass      = pItem->getItemClass();
	OptionInfo*     pOptionInfo = NULL;
	Item*           pLeft       = NULL;
	Item*           pRight      = NULL;
	Item*           pPrevItem   = NULL;
	GCTakeOff       _GCTakeOff;

	// 첫번째 옵션의 색깔을 지정한다.
	if (pItem->getFirstOptionType() != 0)
		pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getFirstOptionType());


	if (IClass == Item::ITEM_CLASS_SHIELD) Part = WEAR_LEFTHAND;
	if (IClass == Item::ITEM_CLASS_SWORD)  Part = WEAR_RIGHTHAND;

	// 먼저 옷을 입히거나, 벗기기 전에 현재의 능력치를 버퍼에다 저장해 둔다.
	// 이는 나중에 변한 능력치만을 전송하기 위한 것이다.
	SLAYER_RECORD prev;
	getSlayerRecord(prev);

	// 현재 기획에서는...능력치가 모자라더라도 아이템을 무조건 사용할 수는
	// 있다. 하지만 아이템에 의한 능력치가 적용이 되지 않는다. 
	// 그러므로 일단 아이템을 해당하는 장착창에다 집어넣는다.
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
				char pField[80];

				takeOffItem(WEAR_LEFTHAND, false, false);

				// 요구한 아이템을 장착 포인트에 넣고,
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;
				// by sigi. 2002.5.15
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				//pLeft->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
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
			char pField[80];

			// 오른쪽에 아이템을 들고 있을 경우
			if (isWear(WEAR_RIGHTHAND))
			{
				pRight = getWearItem(WEAR_RIGHTHAND);

				takeOffItem(WEAR_RIGHTHAND, false, false);

				// 요구한 아이템을 장착 포인트에 넣는다.
				m_pWearItem[WEAR_RIGHTHAND] = pItem;
				m_pWearItem[WEAR_LEFTHAND]  = pItem;
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);

				// by sigi. 2002.5.15
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pRight);
				//pRight->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
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
				//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
				sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
				pItem->tinysave(pField);

				// 요구한 아이템을 마우스 포인터에서 제거한다.
				deleteItemFromExtraInventorySlot();
				// 원래 있던 아이템을 마우스 포인터에 달아 준다.
				addItemToExtraInventorySlot(pLeft);
				//pLeft->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
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
		char pField[80];

		if (isWear(Part))
		{
			pPrevItem = getWearItem(Part);

			takeOffItem(Part, false, false);
			
			// 요구한 아이템을 장착 포인트에 넣는다.
			m_pWearItem[Part] = pItem;
			// by sigi. 2002.5.15
			//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);

			// 요구한 아이템을 마우스 포인터에서 제거한다.
			deleteItemFromExtraInventorySlot();
			// 원래 있던 아이템을 마우스 포인터에 달아 준다.
			addItemToExtraInventorySlot(pPrevItem);
			//pPrevItem->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pPrevItem->tinysave(pField);
		}
		else
		{
			// 요구한 아이템을 장착 포인트에 넣는다.
			m_pWearItem[Part] = pItem;

			// by sigi. 2002.5.15
			//pItem->save(m_Name, STORAGE_GEAR, 0, Part, 0);
			sprintf(pField, "Storage=%d, X=%d", STORAGE_GEAR, Part);
			pItem->tinysave(pField);
			// 요구한 아이템을 마우스 포인터에서 제거한다.
			deleteItemFromExtraInventorySlot();
		}
	}

	// 일단 입었다고 체크해둔다. 
	// by sigi. 2002.10.31
	m_pRealWearingCheck[Part] = true;

	initAllStat();
	sendRealWearingInfo();
	sendModifyInfo(prev); // 비교 후 달라진 능력치 전송

	//bool bisWeapon = false;
	bool bisChange = false;

	//ItemType_t IType = pItem->getItemType();

	Color_t color = getItemShapeColor(pItem, pOptionInfo); 

	// 함수로 뺐다. by sigi. 2002.10.30
	bisChange = changeShape(pItem, color);
	/*
	// 실제로 입을 수 있으면 복장을 바꿔준다. by sigi. 2002.10.30
	if (m_pRealWearingCheck[Part])
	{
		switch (IClass)
		{
			case Item::ITEM_CLASS_MACE:
				bisWeapon = true;
				bisChange = true;
				//m_SlayerInfo.setWeaponType(WEAPON_MACE);
				m_SlayerInfo.setWeaponType(WEAPON_CROSS);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_CROSS:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_CROSS);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_BLADE:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_BLADE);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_AR:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_AR);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_SR:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_SR);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_SMG:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_SMG);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_SG:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_SG);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_HELM:
				bisChange = true;
				m_SlayerInfo.setHelmetType(getHelmetType(IType));
				m_SlayerInfo.setHelmetColor(color);
				break;
			case Item::ITEM_CLASS_SHIELD:
				bisChange = true;
				m_SlayerInfo.setShieldType(getShieldType(IType));
				m_SlayerInfo.setShieldColor(color);
				break;
			case Item::ITEM_CLASS_SWORD:
				bisWeapon = true;
				bisChange = true;
				m_SlayerInfo.setWeaponType(WEAPON_SWORD);
				m_SlayerInfo.setWeaponColor(color);
				break;
			case Item::ITEM_CLASS_COAT:
				bisChange = true;
				m_SlayerInfo.setJacketType(getJacketType(IType));
				m_SlayerInfo.setJacketColor(color);
				break;
			case Item::ITEM_CLASS_TROUSER:
				bisChange = true;
				m_SlayerInfo.setPantsType(getPantsType(IType));
				m_SlayerInfo.setPantsColor(color);
				break;
			case Item::ITEM_CLASS_RING :
				bisChange = false;
				break;
			case Item::ITEM_CLASS_BRACELET :
				bisChange = false;
				break;
			case Item::ITEM_CLASS_NECKLACE :
				bisChange = false;
				break;
			default:
				break;
		}
	}
	*/

	/*
	if (bisWeapon) 
	{
		// 무기에 Strking이 붙어 있으면...
		EffectManager* pEffectManager = pItem->getEffectManager();
		if (pEffectManager->isEffect(Effect::EFFECT_CLASS_STRIKING)) 
		{
			Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_STRIKING);
			// 현제 시간 체크
			Timeval currentTime;
			getCurrentTime(currentTime);

			// 남은시간 산출하기
			Timeval DeadLine = pEffect->getDeadline();
			Turn_t Duration = DeadLine.tv_sec - currentTime.tv_sec;

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_STRIKING);
			gcAddEffect.setDuration(Duration*10);
			m_pZone->broadcastPacket(m_X, m_Y, &gcAddEffect);
		}
	}
	*/

	// 실제로 입을 수 있으면 복장을 바꿔준다. by sigi. 2002.10.30
	if (m_pRealWearingCheck[Part])
	//if (bisChange) 
	{
		GCChangeShape _GCChangeShape;
		_GCChangeShape.setObjectID(getObjectID());
		_GCChangeShape.setItemClass(IClass);
		_GCChangeShape.setItemType(pItem->getItemType());
		_GCChangeShape.setOptionType(pItem->getFirstOptionType());
		_GCChangeShape.setAttackSpeed(m_AttackSpeed[ATTR_CURRENT]);

		if (color == QUEST_COLOR )
			_GCChangeShape.setFlag(SHAPE_FLAG_QUEST);

		Zone* pZone = m_pZone;
		pZone->broadcastPacket(m_X, m_Y, &_GCChangeShape, this);

		//cout << _GCChangeShape.toString().c_str()  << endl;
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

	__END_DEBUG
	__END_CATCH
}

// Slayer::takeOffItem()
// *NOTE : 임시로 bool 타입의 parameter를 넣어 둔다.
//         코드가 구질구질 해지기 때문에 나중에 바꾸도록 한다.. 필수!
void Slayer::takeOffItem(WearPart Part, bool bAddOnMouse, bool bSendModifyInfo)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	SLAYER_RECORD prev;

	// 장착창에 있는 아이템을 받아온다.
	Item* pItem = m_pWearItem[Part];
	Assert(pItem != NULL);
	Item::ItemClass IClass = pItem->getItemClass();

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
		getSlayerRecord(prev); 
		initAllStat();
		sendRealWearingInfo();
		sendModifyInfo(prev);
	}
	else
	{
		initAllStat();
	}

	// 있어선 안될 체크 -_-; 임시 땜빵
	// 아이템을 마우스 커서에다 달아준당.
	if (bAddOnMouse) 
	{
		addItemToExtraInventorySlot(pItem);

		// 아이템 저장 최적화. by sigi. 2002.5.13
		//pItem->save(m_Name, STORAGE_EXTRASLOT, 0, 0, 0);
		char pField[80];

		if (pItem->isSilverWeapon())
		{
			if (pItem->isGun())
			{
//				Gun* pGun = dynamic_cast<Gun*>(pItem);
				sprintf(pField, "Storage=%d, Durability=%d, BulletCount=%d, Silver=%d", STORAGE_EXTRASLOT, pItem->getDurability(), pItem->getBulletCount(), pItem->getSilver());
			}
			else
			{
				sprintf(pField, "Storage=%d, Durability=%d, Silver=%d", STORAGE_EXTRASLOT, pItem->getDurability(), pItem->getSilver());
			}
		}
		else
		{
			sprintf(pField, "Storage=%d, Durability=%d", STORAGE_EXTRASLOT, pItem->getDurability());
		}

		pItem->tinysave(pField);
	}

	GCTakeOff _GCTakeOff;

	bool bisWeapon = false;
	switch (IClass)
	{
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SMG:
		case Item::ITEM_CLASS_SG:
			bisWeapon = true;
			m_SlayerInfo.setWeaponType(WEAPON_NONE);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_RIGHTHAND);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		case Item::ITEM_CLASS_HELM:
			m_SlayerInfo.setHelmetType(HELMET_NONE);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_HELM);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		case Item::ITEM_CLASS_SHIELD:
			m_SlayerInfo.setShieldType(SHIELD_NONE);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_LEFTHAND);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		case Item::ITEM_CLASS_SWORD:
			bisWeapon = true;
			m_SlayerInfo.setWeaponType(WEAPON_NONE);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_RIGHTHAND);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		case Item::ITEM_CLASS_COAT:
			m_SlayerInfo.setJacketType(JACKET_BASIC);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_COAT);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		case Item::ITEM_CLASS_TROUSER:
			m_SlayerInfo.setPantsType(PANTS_BASIC);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_TROUSER);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		case Item::ITEM_CLASS_SHOULDER_ARMOR:
			m_SlayerInfo.setShoulderType(0);
			_GCTakeOff.setObjectID(getObjectID());
			_GCTakeOff.setSlotID((SlotID_t)ADDON_SHOULDER);
			m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, this);
			break;
		default:
			break;
	}

	/*
	if (bisWeapon) 
	{
		// 무기에 Strking이 붙어 있으면...
		EffectManager* pEffectManager = pItem->getEffectManager();

		if (pEffectManager->isEffect(Effect::EFFECT_CLASS_STRIKING)) 
		{
			GCRemoveEffect removeEffect;
			removeEffect.setObjectID(getObjectID());
			removeEffect.addEffectList(Effect::EFFECT_CLASS_STRIKING);
			m_pZone->broadcastPacket(m_X, m_Y, &removeEffect);
		}
	}
	*/

	if (m_pZone != NULL)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		makeGCOtherModifyInfo(&gcOtherModifyInfo, this, &prev);

		if (gcOtherModifyInfo.getShortCount() != 0 || gcOtherModifyInfo.getLongCount() != 0)
		{
			m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
		}
	}

	__END_DEBUG
	__END_CATCH
}

// destroyGears
// 장착 아이템을 Delete 한다.
void Slayer::destroyGears() 
	throw()
{
	__BEGIN_DEBUG

	for (int j = 0; j < WEAR_MAX; j++) 
	{
		Item* pItem = m_pWearItem[j];
		if (pItem != NULL) 
		{
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
}

bool Slayer::isRealWearing(WearPart part) const
	throw()
{
	__BEGIN_TRY

	if (part >= WEAR_MAX) throw("Slayer::isRealWearing() : invalid wear point!");
	if (m_pWearItem[part] == NULL) return false;
	if (part >= WEAR_ZAP1 && part <= WEAR_ZAP4)
	{
		// 해당 위치에 반지도 있어야 된다.
		if (m_pWearItem[part-WEAR_ZAP1+WEAR_FINGER1]==NULL ) return false;
	}

	return isRealWearing(m_pWearItem[part]);

	__END_CATCH
}

bool Slayer::isRealWearing(Item* pItem) const
	throw()
{
	__BEGIN_TRY

	if (pItem == NULL) return false;
	if (pItem->getDurability() == 0 ) return false;

/*	if (m_pZone != NULL && m_pZone->isDynamicZone() && m_pZone->getDynamicZone()->getTemplateZoneID() == 4003 )
	{
		if (!isSlayerWeapon(pItem->getItemClass() ) ) return false;
	}*/

	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());

	Level_t			ReqAdvancedLevel = pItemInfo->getReqAdvancedLevel();
	if (ReqAdvancedLevel > 0 && (!isAdvanced() || getAdvancementClassLevel() < ReqAdvancedLevel ) ) return false;

	if (pItem->getItemClass() == Item::ITEM_CLASS_SMG || pItem->getItemClass() == Item::ITEM_CLASS_SG )
	{
		if (ReqAdvancedLevel <= 0 && isAdvanced() ) return false;
	}
/*	if (isSlayerWeapon(pItem->getItemClass()) || pItem->getItemClass() == Item::ITEM_CLASS_COAT || pItem->getItemClass() == Item::ITEM_CLASS_TROUSER )
	{
		if (ReqAdvancedLevel <= 0 && isAdvanced() ) return false;
	}*/

	// 시간제한아이템은 레어나 유니크나 무료사용자도 쓸 수 있다....... 2003.5.4
	if (pItem->isTimeLimitItem() )
	{
		Attr_t    ReqGender = pItemInfo->getReqGender();
		if ((m_Sex == MALE && ReqGender == GENDER_FEMALE ) ||
			 (m_Sex == FEMALE && ReqGender == GENDER_MALE ) ) return false;
		return true;
	}

	// 프리미엄 존에서는 유료사용자만 유니크/레어 아이템이 적용된다.
	// 커플링도 유료사용자만 쓸 수 있다. by Sequoia 2003. 3. 5.
	if (getZone()->isPremiumZone()
		&& (pItem->isUnique() || pItem->getOptionTypeSize()>1 || 
			pItem->getItemClass() == Item::ITEM_CLASS_COUPLE_RING || pItem->getItemClass() == Item::ITEM_CLASS_VAMPIRE_COUPLE_RING))
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(getPlayer());
		if (!pGamePlayer->isPayPlaying() 
			&& !pGamePlayer->isPremiumPlay())
		{
			//cout << "Premium Item :" << pItem->getItemClassName().c_str() << endl;
			return false;
		}
	}

	if (isCoupleRing(pItem ) )
	{
		return true;
	}

	Attr_t    ReqSTR    = pItemInfo->getReqSTR();
	Attr_t    ReqDEX    = pItemInfo->getReqDEX();
	Attr_t    ReqINT    = pItemInfo->getReqINT();
	Attr_t    ReqSum    = pItemInfo->getReqSum();
	Attr_t    ReqGender = pItemInfo->getReqGender();

	// 기본 아이템의 능력치 총합 요구치가 300이 넘으면 옵션을 포함한 요구치가 435까지 올라갈 수 있다.
	// 기본 아이템의 요구치가 300 이하일 경우 옵션을 다 포함해도 300을 넘어서는 안 된다.
	// 다른 것들도 마찬가지다. 2003.3.21 by Sequoia
	Attr_t	ReqSumMax	= ((ReqSum > MAX_SLAYER_SUM_OLD ) ? MAX_SLAYER_SUM : MAX_SLAYER_SUM_OLD);
	Attr_t	ReqSTRMax	= ((ReqSTR > MAX_SLAYER_ATTR_OLD ) ? MAX_SLAYER_ATTR : MAX_SLAYER_ATTR_OLD);
	Attr_t	ReqDEXMax	= ((ReqDEX > MAX_SLAYER_ATTR_OLD ) ? MAX_SLAYER_ATTR : MAX_SLAYER_ATTR_OLD);
	Attr_t	ReqINTMax	= ((ReqINT > MAX_SLAYER_ATTR_OLD ) ? MAX_SLAYER_ATTR : MAX_SLAYER_ATTR_OLD);

	// 아이템이 옵션을 가지고 있다면, 
	// 옵션의 종류에 따라서 능력치 제한을 올려준다.
	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	if (!optionTypes.empty())
	{
		// 모든 옵션에 대해서...
		list<OptionType_t>::const_iterator itr;
		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(*itr);

			if (ReqSTR != 0) ReqSTR += (pOptionInfo->getReqSum() * 2);
			if (ReqDEX != 0) ReqDEX += (pOptionInfo->getReqSum() * 2);
			if (ReqINT != 0) ReqINT += (pOptionInfo->getReqSum() * 2);
			if (ReqSum != 0) ReqSum += (pOptionInfo->getReqSum());
		}

		/*
		ReqSTR = max((int)ReqSTR, pOptionInfo->getReqSTR());
		ReqDEX = max((int)ReqDEX, pOptionInfo->getReqDEX());
		ReqINT = max((int)ReqINT, pOptionInfo->getReqINT());
		ReqSum = max((int)ReqSum, pOptionInfo->getReqSum());
		*/
	}

	// 2003.1.6 by Sequoia, Bezz
	// 2003.3.21 위에 정의된 Max값이 최대치로 제한된다.
	ReqSTR = min(ReqSTR, ReqSTRMax);
	ReqDEX = min(ReqDEX, ReqDEXMax);
	ReqINT = min(ReqINT, ReqINTMax);
	ReqSum = min(ReqSum, ReqSumMax);
	
	// 능력치 제한이 하나라도 있다면,
	// 그 능력을 만족시키는지 검사해야 한다.
	Attr_t CSTR = m_STR[ATTR_CURRENT];
	Attr_t CDEX = m_DEX[ATTR_CURRENT];
	Attr_t CINT = m_INT[ATTR_CURRENT];
	Attr_t CSUM = CSTR + CDEX + CINT;

	if (CSTR < ReqSTR
		|| CDEX < ReqDEX
		|| CINT < ReqINT
		|| CSUM < ReqSum
		|| m_Sex == MALE && ReqGender == GENDER_FEMALE
		|| m_Sex == FEMALE && ReqGender == GENDER_MALE) 
	{
		//cout << "Disable: " << pItem->getItemClassName().c_str() << endl;
		return false;
	}

	//cout << "Enable: " << pItem->getItemClassName().c_str() << endl;

	return true;

	__END_CATCH
}

bool Slayer::isRealWearingEx(WearPart part) const
{
	if (part >= WEAR_MAX) return false;
	return m_pRealWearingCheck[part];
}

DWORD Slayer::sendRealWearingInfo(void) const
	throw()
{
	__BEGIN_TRY

	DWORD info = 0;
	DWORD flag = 1;

	for (int i=0; i<WEAR_MAX; i++)
	{
		if (isRealWearing((Slayer::WearPart)i)) info |= flag;
		flag <<= 1;
	}

    GCRealWearingInfo pkt;
    pkt.setInfo(info);
    m_pPlayer->sendPacket(&pkt);

	return info;

	__END_CATCH
}

void Slayer::setMotorcycle(Motorcycle* pMotorcycle)
	throw()
{
	__BEGIN_DEBUG

	// 모터사이클을 셋팅한다.
	m_pMotorcycle = pMotorcycle;

	// SlaeyrInfo에 모토사이클을 타고 있다는 것을 셋팅한다.
	//m_SlayerInfo.setMotorcycleType(MOTORCYCLE1);
	// by sigi.2002.6.22
	m_SlayerInfo.setMotorcycleType(getMotorcycleType(pMotorcycle->getItemType()));

	if (!pMotorcycle->hasOptionType() )
	{
    	m_SlayerInfo.setMotorcycleColor(388);
	}
	else
	{
		OptionType_t option = pMotorcycle->getFirstOptionType();
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(option);

		if (pOptionInfo != NULL )
		{
			m_SlayerInfo.setMotorcycleColor(pOptionInfo->getColor());
		}
		else
		{
	   		m_SlayerInfo.setMotorcycleColor(388);
		}
	}

	__END_DEBUG
}

void Slayer::getOffMotorcycle()
	throw(Error)
{
	__BEGIN_DEBUG
	
	// 모토사이클을 존에 떨어트린다.
	TPOINT pt = m_pZone->addItem((Item*)m_pMotorcycle, m_X, m_Y);

	if (pt.x != -1) 
	{
		//m_pMotorcycle->save("", STORAGE_ZONE, m_pZone->getZoneID(), pt.x, pt.y);

		// 아이템 저장 최적화. by sigi. 2002.5.15
		char pField[80];
		sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d",
									STORAGE_ZONE, m_pZone->getZoneID(), (int)pt.x, (int)pt.y);
		m_pMotorcycle->tinysave(pField);

		MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox(m_pMotorcycle->getItemID());

		if (pMotorcycleBox != NULL) 
		{
			pMotorcycleBox->setZone(m_pZone);
			pMotorcycleBox->setX(pt.x);
			pMotorcycleBox->setY(pt.y);
		} 
		else 
		{
			//cout << "Slayer::getOffMotorcycle() - pMotorcycleBox is NULL" << endl;
			filelog("errorLog.txt", "Slayer::getOffMotorcycle() - No MotorcycleBox: %d", (int)m_pMotorcycle->getItemID());
			//throw Error("오토바이를 벗을려고 하는데 ParkingCenter에 MotorcycleBox가 없습니다.");
		}
	} 
	else 
	{
		// 다른 아이템들이 넘 많이 깔려 있을 경우 그냥 Box자체를 삭제 해준다..
		// 다시 받기를 해야 하겠지? -_-;
		if (g_pParkingCenter->hasMotorcycleBox(m_pMotorcycle->getItemID())) 
		{
			g_pParkingCenter->deleteMotorcycleBox(m_pMotorcycle->getItemID());
		}

	}

	// 슬레이어의 모토사이클을 벗긴다.
	m_pMotorcycle = NULL;

	// 슬레이어가 모토사이클을 타고 있지 않다는 것을 셋팅한다.
	m_SlayerInfo.setMotorcycleType(MOTORCYCLE_NONE);

	__END_DEBUG
}

PCSlayerInfo2* Slayer::getSlayerInfo2 () const
	throw()
{
	__BEGIN_DEBUG

	PCSlayerInfo2* pInfo = new PCSlayerInfo2();

	pInfo->setObjectID(m_ObjectID);
	pInfo->setName(m_Name);
	pInfo->setSex(m_Sex);
	pInfo->setHairStyle(m_HairStyle);
	pInfo->setHairColor(m_HairColor);
	pInfo->setSkinColor(m_SkinColor);
	pInfo->setMasterEffectColor(m_MasterEffectColor);

	//cout << "PCSlayerInfo2: HairStyle = " << HairStyle2String[pInfo->getHairStyle()] << endl;

	//pInfo->setPhoneNumber(m_PhoneNumber);

	// 성향
	pInfo->setAlignment(m_Alignment);

	//cout << "STR[CURRENT]" << (int)m_STR[ATTR_CURRENT] << endl;
	//cout << "STR[MAX]" << (int)m_STR[ATTR_MAX] << endl;
	//cout << "STR[BASIC]" << (int)m_STR[ATTR_BASIC] << endl;
	//cout << "DEX[CURRENT]" << (int)m_DEX[ATTR_CURRENT] << endl;
	//cout << "DEX[MAX]" << (int)m_DEX[ATTR_MAX] << endl;
	//cout << "DEX[BASIC]" << (int)m_DEX[ATTR_BASIC] << endl;
	//cout << "INT[CURRENT]" << (int)m_INT[ATTR_CURRENT] << endl;
	//cout << "INT[MAX]" << (int)m_INT[ATTR_MAX] << endl;
	//cout << "INT[BASIC]" << (int)m_INT[ATTR_BASIC] << endl;

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

	// 능력치 경험치
//	pInfo->setSTRExp(m_STRExp);
//	pInfo->setDEXExp(m_DEXExp);
//	pInfo->setINTExp(m_INTExp);
	pInfo->setSTRExp(getSTRGoalExp());
	pInfo->setDEXExp(getDEXGoalExp());
	pInfo->setINTExp(getINTGoalExp());

	// 계급
	pInfo->setRank(getRank());
	pInfo->setRankExp(getRankGoalExp());

//	cout << getRankGoalExp() << endl;

	pInfo->setHP(m_HP[ATTR_CURRENT] , m_HP[ATTR_MAX]);
	pInfo->setMP(m_MP[ATTR_CURRENT] , m_MP[ATTR_MAX]);
	pInfo->setFame(m_Fame);
	pInfo->setGold(m_Gold);
	pInfo->setSkillDomain(SKILL_DOMAIN_BLADE , m_SkillDomainLevels[SKILL_DOMAIN_BLADE] , m_GoalExp[SKILL_DOMAIN_BLADE]);
	pInfo->setSkillDomain(SKILL_DOMAIN_SWORD , m_SkillDomainLevels[SKILL_DOMAIN_SWORD] , m_GoalExp[SKILL_DOMAIN_SWORD]);
	pInfo->setSkillDomain(SKILL_DOMAIN_GUN , m_SkillDomainLevels[SKILL_DOMAIN_GUN] , m_GoalExp[SKILL_DOMAIN_GUN]);
	pInfo->setSkillDomain(SKILL_DOMAIN_ETC , m_SkillDomainLevels[SKILL_DOMAIN_ETC] , m_GoalExp[SKILL_DOMAIN_ETC]);
	pInfo->setSkillDomain(SKILL_DOMAIN_ENCHANT , m_SkillDomainLevels[SKILL_DOMAIN_ENCHANT] , m_GoalExp[SKILL_DOMAIN_ENCHANT]);
	pInfo->setSkillDomain(SKILL_DOMAIN_HEAL , m_SkillDomainLevels[SKILL_DOMAIN_HEAL] , m_GoalExp[SKILL_DOMAIN_HEAL]);
	pInfo->setSight(m_Sight);

//	for (int i = 0; i < 4; i++) 
//	{
//		pInfo->setHotKey(i, m_HotKey[i]);
//	}

	// 0이나 1 권한을 가지고 있으면
	// 운영자로 스프라이트를 출력해줘야 한다. 
	pInfo->setCompetence(m_CompetenceShape);
	pInfo->setGuildID(m_GuildID);
	pInfo->setGuildName(getGuildName());
	pInfo->setGuildMemberRank(getGuildMemberRank());

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion(m_GuildID);
	if (pUnion == NULL ) pInfo->setUnionID(0);
	else pInfo->setUnionID(pUnion->getUnionID());

	pInfo->setAdvancementLevel(getAdvancementClassLevel());
	pInfo->setAdvancementGoalExp(getAdvancementClassGoalExp());
	pInfo->setAttrBonus(getBonus());

	return pInfo;

	__END_DEBUG
}

PCSlayerInfo3 Slayer::getSlayerInfo3 () const
	throw()
{
	__BEGIN_DEBUG

	// 좌표와 방향은 너무 자주 바뀌기 때문에, 이 함수가 호출될 때에만
	// 지정해준다.
	m_SlayerInfo.setObjectID(m_ObjectID);	// by sigi. 2002.6.5. morph때문에
	m_SlayerInfo.setX(m_X);
	m_SlayerInfo.setY(m_Y);
	m_SlayerInfo.setDir(m_Dir);
	m_SlayerInfo.setCurrentHP(m_HP[ATTR_CURRENT]);
	m_SlayerInfo.setMaxHP(m_HP[ATTR_MAX]);
	m_SlayerInfo.setAlignment(m_Alignment);
	m_SlayerInfo.setGuildID(m_GuildID);

	// 공격 스피드
	m_SlayerInfo.setAttackSpeed(m_AttackSpeed[ATTR_CURRENT]);

	// by sigi. 2002.9.10
	m_SlayerInfo.setRank(getRank());

	// 2003.5.15 염색약용
    m_SlayerInfo.setHairColor(m_HairColor);
    m_SlayerInfo.setSkinColor(m_SkinColor);
	m_SlayerInfo.setMasterEffectColor(m_MasterEffectColor);

	GuildUnion* pUnion = GuildUnionManager::Instance().getGuildUnion(m_GuildID);
	if (pUnion == NULL ) m_SlayerInfo.setUnionID(0);
	else m_SlayerInfo.setUnionID(pUnion->getUnionID());

	m_SlayerInfo.setAdvancementLevel(getAdvancementClassLevel());

	return m_SlayerInfo;

	__END_DEBUG
}

ExtraInfo* Slayer::getExtraInfo() const
	throw()
{
	__BEGIN_DEBUG

	BYTE ItemCount = 0;

	ExtraInfo* pExtraInfo = new ExtraInfo();

	Item* pItem = m_pExtraInventorySlot->getItem();

	if (pItem != NULL) 
	{
		//Item::ItemClass IClass = pItem->getItemClass();

		ExtraSlotInfo* pExtraSlotInfo = new ExtraSlotInfo();
		pItem->makePCItemInfo(*pExtraSlotInfo);

/*
		pExtraSlotInfo->setObjectID(pItem->getObjectID());
		pExtraSlotInfo->setItemClass(pItem->getItemClass());
		pExtraSlotInfo->setItemType(pItem->getItemType());
		pExtraSlotInfo->setOptionType(pItem->getOptionTypeList());
		pExtraSlotInfo->setDurability(pItem->getDurability());
		pExtraSlotInfo->setSilver(pItem->getSilver());
		pExtraSlotInfo->setEnchantLevel(pItem->getEnchantLevel());

		if (IClass == Item::ITEM_CLASS_AR) 
		{
			AR* pAR = dynamic_cast<AR*>(pItem);
			pExtraSlotInfo->setItemNum(pAR->getBulletCount());
		} 
		else if (IClass == Item::ITEM_CLASS_SG) 
		{
			SG* pSG = dynamic_cast<SG*>(pItem);
			pExtraSlotInfo->setItemNum(pSG->getBulletCount());
		} 
		else if (IClass == Item::ITEM_CLASS_SMG) 
		{
			SMG* pSMG = dynamic_cast<SMG*>(pItem);
			pExtraSlotInfo->setItemNum(pSMG->getBulletCount());
		} 
		else if (IClass == Item::ITEM_CLASS_SR) 
		{
			SR* pSR = dynamic_cast<SR*>(pItem);
			pExtraSlotInfo->setItemNum(pSR->getBulletCount());
		} 
		else 
		{
			pExtraSlotInfo->setItemNum(pItem->getNum());
		}

		// 벨트라면 Sub 아이템의 추가 정보가 필요하다.
		if (IClass == Item::ITEM_CLASS_BELT) 
		{
			Belt* pBelt = dynamic_cast<Belt*>(pItem);
			Inventory* pBeltInventory = ((Belt*)pItem)->getInventory();
			BYTE SubItemCount = 0;

			for (int i = 0; i < pBelt->getPocketCount(); i++) 
			{
				Item* pBeltItem = pBeltInventory->getItem(i, 0);

				if (pBeltItem != NULL) 
				{
					SubItemInfo* pSubItemInfo = new SubItemInfo();
					pSubItemInfo->setObjectID(pBeltItem->getObjectID());
					pSubItemInfo->setItemClass(pBeltItem->getItemClass());
					pSubItemInfo->setItemType(pBeltItem->getItemType());
					pSubItemInfo->setItemNum(pBeltItem->getNum());
					pSubItemInfo->setSlotID(i);

					pExtraSlotInfo->addListElement(pSubItemInfo);

					SubItemCount++;
				}
			}

			pExtraSlotInfo->setListNum(SubItemCount);

		}

		// 상의 하의 Main Color 지금은 그냥 0 으로 셋팅 해둔다.
		pExtraSlotInfo->setMainColor(0);
*/	
		pExtraInfo->addListElement(pExtraSlotInfo);

		ItemCount++;
	}

	pExtraInfo->setListNum(ItemCount);

	return pExtraInfo;

	__END_DEBUG

}

GearInfo* Slayer::getGearInfo() const
	throw()
{
	__BEGIN_DEBUG

	BYTE ItemCount = 0;
	GearInfo* pGearInfo = new GearInfo();

	for (int i = 0; i < WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
//			Item::ItemClass IClass = pItem->getItemClass();

			GearSlotInfo* pGearSlotInfo = new GearSlotInfo();
			pItem->makePCItemInfo(*pGearSlotInfo);

			pGearSlotInfo->setSlotID(i);

/*
			pGearSlotInfo->setObjectID(pItem->getObjectID());
			pGearSlotInfo->setItemClass(pItem->getItemClass());
			pGearSlotInfo->setItemType(pItem->getItemType());
			pGearSlotInfo->setOptionType(pItem->getOptionTypeList());
			pGearSlotInfo->setDurability(pItem->getDurability());
			pGearSlotInfo->setSilver(pItem->getSilver());
			pGearSlotInfo->setEnchantLevel(pItem->getEnchantLevel());

			if (IClass == Item::ITEM_CLASS_AR) 
			{
				AR* pAR = dynamic_cast<AR*>(pItem);
				pGearSlotInfo->setItemNum(pAR->getBulletCount());
			} 
			else if (IClass == Item::ITEM_CLASS_SG) 
			{
				SG* pSG = dynamic_cast<SG*>(pItem);
				pGearSlotInfo->setItemNum(pSG->getBulletCount());
			} 
			else if (IClass == Item::ITEM_CLASS_SMG) 
			{
				SMG* pSMG = dynamic_cast<SMG*>(pItem);
				pGearSlotInfo->setItemNum(pSMG->getBulletCount());
			} 
			else if (IClass == Item::ITEM_CLASS_SR) 
			{
				SR* pSR = dynamic_cast<SR*>(pItem);
				pGearSlotInfo->setItemNum(pSR->getBulletCount());
			} 
			else 
			{
				pGearSlotInfo->setItemNum(pItem->getNum());
			}

			// 벨트라면 Sub 아이템의 추가 정보가 필요하다.
			if (IClass == Item::ITEM_CLASS_BELT) {

				// 아이템 인포를 받아온다.
				ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	
				// 포켓의 숫자를 받아온다.
				BYTE PocketNum = ((BeltInfo*)pItemInfo)->getPocketCount();
	
				// 벨트의 인벤토리를 받아온다.
				Inventory* pBeltInventory = ((Belt*)pItem)->getInventory();
	
				BYTE SubItemCount = 0;
	
				// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
				for (int i = 0; i < PocketNum ; i++) {
	
					Item* pBeltItem = pBeltInventory->getItem(i, 0);
	
					if (pBeltItem != NULL) {
	
						SubItemInfo* pSubItemInfo = new SubItemInfo();
						pSubItemInfo->setObjectID(pBeltItem->getObjectID());
						pSubItemInfo->setItemClass(pBeltItem->getItemClass());
						pSubItemInfo->setItemType(pBeltItem->getItemType());
						pSubItemInfo->setItemNum(pBeltItem->getNum());
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

}

//////////////////////////////////////////////////////////////////////////////
// get Inventory Info
//////////////////////////////////////////////////////////////////////////////
InventoryInfo* Slayer::getInventoryInfo() const throw() {
	__BEGIN_DEBUG

	BYTE ItemCount = 0;

    list<Item*> ItemList;
	InventoryInfo* pInventoryInfo = new InventoryInfo();
	VolumeHeight_t Height = m_pInventory->getHeight();
	VolumeWidth_t Width = m_pInventory->getWidth();

	for (int j = 0; j < Height; j++) {
		for (int i = 0; i < Width; i++) {
			if (m_pInventory->hasItem(i, j)) {
				Item* pItem = m_pInventory->getItem(i, j);
				VolumeWidth_t ItemWidth = pItem->getVolumeWidth();
//				Item::ItemClass IClass = pItem->getItemClass();

				list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

				if (itr == ItemList.end()) {
					// map 에 Item을 등록시켜 놓음,
					// 다음 비교때 같은 아이템인지 확인하기 위하여.
					ItemList.push_back(pItem);

					InventorySlotInfo* pInventorySlotInfo = new InventorySlotInfo();
					pItem->makePCItemInfo(*pInventorySlotInfo);
					pInventorySlotInfo->setInvenX(i);
					pInventorySlotInfo->setInvenY(j);

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
}

RideMotorcycleInfo* Slayer::getRideMotorcycleInfo() const
	throw()
{
	__BEGIN_DEBUG

	RideMotorcycleInfo* pRideMotorcycleInfo = new RideMotorcycleInfo();

	pRideMotorcycleInfo->setObjectID(m_pMotorcycle->getObjectID());
	pRideMotorcycleInfo->setItemType(m_pMotorcycle->getItemType());
	pRideMotorcycleInfo->setOptionType(m_pMotorcycle->getOptionTypeList());
	pRideMotorcycleInfo->setListNum(0);

    m_SlayerInfo.setMotorcycleColor(388);

	return pRideMotorcycleInfo;

	__END_DEBUG
}

void Slayer::sendSlayerSkillInfo()
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try {
		SlayerSkillInfo* pSlayerSkillInfo[SKILL_DOMAIN_VAMPIRE];

		for (int i = 0; i < SKILL_DOMAIN_VAMPIRE; i++) 
		{
			pSlayerSkillInfo[i]=  new SlayerSkillInfo();
			pSlayerSkillInfo[i]->setDomainType((SkillDomainType_t)i);
		}

		BYTE SkillCount[SKILL_DOMAIN_VAMPIRE] = {0,};
		SkillInfo* pSkillInfo = NULL;
		SkillDomainType_t SDomainType = 0;

		// 현재 시간, 남은 캐스팅 타임을 계산하기 위해
		Timeval currentTime;
		getCurrentTime(currentTime);

		map<SkillType_t, SkillSlot*>::const_iterator itr = m_SkillSlot.begin();
		for (; itr != m_SkillSlot.end(); itr++)
		{
			SkillSlot* pSkillSlot = itr->second;
			Assert(pSkillSlot != NULL);

			// 기본 공격 스킬이 아니라면...
			if (pSkillSlot->getSkillType() >= SKILL_DOUBLE_IMPACT)
			{
				// 스킬 인포를 받아온다.
				pSkillInfo = g_pSkillInfoManager->getSkillInfo(pSkillSlot->getSkillType());

				// 스킬인포로 부터 현재 기술의 도메인을 받아온다.
				SDomainType = pSkillInfo->getDomainType();

				// 서브 스킬 인포를 구성한다.
				SubSlayerSkillInfo* pSubSlayerSkillInfo = new SubSlayerSkillInfo();
				pSubSlayerSkillInfo->setSkillType(pSkillSlot->getSkillType());
				pSubSlayerSkillInfo->setSkillExp(pSkillSlot->getExp());
				pSubSlayerSkillInfo->setSkillExpLevel(pSkillSlot->getExpLevel());
				pSubSlayerSkillInfo->setSkillTurn(pSkillSlot->getInterval());

//				cout << pSkillInfo->getName() << "스킬 딜레이 " << pSkillSlot->getInterval() << endl;

				// casting time 항목을 다음 캐스팅까지 남은 시간으로 한다.
				//pSubSlayerSkillInfo->setCastingTime(pSkillSlot->getCastingTime());
				pSubSlayerSkillInfo->setCastingTime(pSkillSlot->getRemainTurn(currentTime ));
				pSubSlayerSkillInfo->setEnable(pSkillSlot->canUse());

				// 슬레이어 스킬인포에 서브 스킬 인포를 추가한다.
				pSlayerSkillInfo[SDomainType]->addListElement(pSubSlayerSkillInfo);
				SkillCount[SDomainType]++;
				pSlayerSkillInfo[SDomainType]->setListNum(SkillCount[SDomainType]);
			}
		}

		pSlayerSkillInfo[SDomainType]->setListNum(SkillCount[SDomainType]);
		GCSkillInfo gcSkillInfo;
		gcSkillInfo.setPCType(PC_SLAYER);

		for (int i = 0; i < SKILL_DOMAIN_VAMPIRE; i++) 
		{
			SkillType_t LearnSkillType = g_pSkillInfoManager->getSkillTypeByLevel(i, m_SkillDomainLevels[i]);

			// 현재 레벨에서 배울 수 있는 기술이 있는지 본다.
			if (LearnSkillType != 0) 
			{
				// 배울 수 있는 기술이 있고 배우지 않은 상태라면 배우라고 알려준다.
				if (hasSkill(LearnSkillType) == NULL) 
				{
					pSlayerSkillInfo[i]->setLearnNewSkill(true);
				}
			}

			if (pSlayerSkillInfo[i]->isLearnNewSkill() || pSlayerSkillInfo[i]->getListNum() > 0) 
			{
				gcSkillInfo.addListElement(pSlayerSkillInfo[i]);
			} 
			else 
			{
				SAFE_DELETE(pSlayerSkillInfo[i]);
			}
		}

		m_pPlayer->sendPacket(&gcSkillInfo);
	} catch (Throwable& t) {
		filelog("slayerBug.log", "%s", t.toString().c_str());
	}


	__END_DEBUG
	__END_CATCH
}


EffectInfo* Slayer::getEffectInfo()
	const throw()
{
	EffectInfo* pEffectInfo = m_pEffectManager->getEffectInfo();
	return pEffectInfo;
}

void Slayer::setGold(Gold_t gold )
	throw()
{
	__BEGIN_TRY

	// MAX_MONEY 를 넘어가는 걸 막는다
	// 2003.1.8  by bezz.
	m_Gold = min((Gold_t)MAX_MONEY, gold);

	__END_CATCH
}

void Slayer::setGoldEx(Gold_t gold)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	setGold(gold);

	/*
	StringStream sql;
	sql << "Gold = " << (int)m_Gold;

	tinysave(sql.toString());
	*/
	char pField[80];
	sprintf(pField, "Gold = %ld", m_Gold);
	tinysave(pField);

	__END_DEBUG
	__END_CATCH
}

void Slayer::increaseGoldEx(Gold_t gold)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// MAX_MONEY 를 넘어가는 걸 막는다
	// 2003.1.8  by bezz.
	if (m_Gold + gold > MAX_MONEY )
		gold = MAX_MONEY - m_Gold;

	setGold(m_Gold+gold);

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Slayer SET Gold=Gold+%u WHERE NAME='%s'", gold, m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)


	__END_DEBUG
	__END_CATCH
}

void Slayer::decreaseGoldEx(Gold_t gold)
	throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// 0 미만이 되는 걸 막는다. 0 미만이 되면 underflow 되서 난리가 난다.
	// 2003.1.8  by bezz.
	if (m_Gold < gold )
		gold = m_Gold;

	setGold(m_Gold-gold);

    Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Slayer SET Gold=Gold-%u WHERE NAME='%s'", gold, m_Name.c_str());
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

bool Slayer::checkGoldIntegrity()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	bool ret = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT Gold FROM Slayer WHERE NAME='%s'", m_Name.c_str());

		if (pResult->next() )
		{
			ret = pResult->getInt(1) == m_Gold;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return ret;

	__END_CATCH
}

bool Slayer::checkStashGoldIntegrity()
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	bool ret = false;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT StashGold FROM Slayer WHERE NAME='%s'", m_Name.c_str());

		if (pResult->next() )
		{
			ret = pResult->getInt(1) == m_StashGold;
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	return ret;

	__END_CATCH
}


void Slayer::heartbeat(const Timeval& currentTime)
    throw()
{
	__BEGIN_DEBUG

/*#ifdef __ACTIVE_QUEST__
	// by sigi. 2002.12.3
	if (m_pQuestManager!=NULL)
	{
		m_pQuestManager->heartbeat();
	}
#endif*/

	PlayerCreature::heartbeat(currentTime);

	// 여기서 Prayer와 Meditation에 관련된 MP 리젠을 해준다.
	// 하트비트 함수를 하나 따로 만들고, 실행시키는 것이 옳겠지만...
	Item* pWeapon = getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pWeapon != NULL)
	{
		Item::ItemClass IClass = pWeapon->getItemClass();

		SkillSlot* pPrayer     = hasSkill(SKILL_PRAYER);
		SkillSlot* pMeditation = hasSkill(SKILL_MEDITATION);

		if (IClass == Item::ITEM_CLASS_CROSS && pPrayer != NULL && pPrayer->canUse() && !isFlag(Effect::EFFECT_CLASS_PLEASURE_EXPLOSION))
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			if (m_MPRegenTime < currentTime)
			{
				MP_t MPMax          = getMP(ATTR_MAX);
				int  MPRegenPercent = 3 + getINT(ATTR_CURRENT)/20;
				MP_t MPQuantity     = max(1, getPercentValue(MPMax, MPRegenPercent));
				MP_t oldMP          = getMP(ATTR_CURRENT);
				MP_t newMP          = min((int)MPMax, (int)(oldMP + MPQuantity));

				if (oldMP != newMP)
				{
					setMP(newMP, ATTR_CURRENT);

					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_MP, newMP);
					m_pPlayer->sendPacket(&gcMI);
				}

				// 5초 단위로 하트비트 시킨다. 
				m_MPRegenTime.tv_sec = currentTime.tv_sec + 5;
				m_MPRegenTime.tv_usec = currentTime.tv_usec;
			}
		}
		else if (IClass == Item::ITEM_CLASS_MACE && pMeditation != NULL && pMeditation->canUse() && !isFlag(Effect::EFFECT_CLASS_PLEASURE_EXPLOSION))
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			if (m_MPRegenTime < currentTime)
			{
				MP_t MPMax          = getMP(ATTR_MAX);
				int  MPRegenPercent = 3 + getINT(ATTR_CURRENT)/20;
				MP_t MPQuantity     = max(1, getPercentValue(MPMax, MPRegenPercent));
				MP_t oldMP          = getMP(ATTR_CURRENT);
				MP_t newMP          = min((int)MPMax, (int)(oldMP + MPQuantity));

				if (oldMP != newMP)
				{
					setMP(newMP, ATTR_CURRENT);

					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_MP, newMP);
					m_pPlayer->sendPacket(&gcMI);
				}

				// 5초 단위로 하트비트시킨다.
				m_MPRegenTime.tv_sec = (currentTime.tv_sec + 5);
				m_MPRegenTime.tv_usec = currentTime.tv_usec;
			}
		}
	}

	/*
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

				list<Item*>::iterator itr = find(ItemList.begin() , ItemList.end() , pItem);

				if (itr == ItemList.end()) 
				{
					ItemList.push_back(pItem);

					//아이템 크기의 다음 위치 부터 검색하기 위함.
					i = i + ItemWidth - 1;
				}
			}
		}
	}

	for (int i = 0; i < WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];

		if (pItem != NULL) 
		{
			if (i == WEAR_RIGHTHAND && isTwohandWeapon(pItem)) continue;
			ItemList.push_back(pItem);
		}
	}

	Item* pSlotItem = m_pExtraInventorySlot->getItem();
	if (pSlotItem != NULL) 
	{
		ItemList.push_back(pSlotItem);
	}

	for (list<Item*>::iterator itr = ItemList.begin(); itr != ItemList.end(); itr++)
	{
		Item* pItem  = (*itr);

		EffectManager* pItemEffectManager = pItem->getEffectManager();
		if (pItemEffectManager != NULL)
		{
			int rvalue = pItemEffectManager->heartbeat();

			// rvalue는 이펙트 매니저 내부에서 삭제된 이펙트의 갯수이다.
			// 이 갯수가 0이 아니라는 말은 삭제된 이펙트가 존재한다는 말이다.
			// 이펙트가 삭제되었으니, 능력치를 새로 계산해 준다.
			// 사실 이 코드는 스트라이킹 때문에 생긴 코드이다.
			// 스트라이킹이 걸리는 주체가 크리쳐가 아니라, 아이템이기 때문에,
			// unaffect될 때 크리쳐의 능력치를 재계산해야 하는데, 할 곳이 마땅하지 않았다.
			// 그래서 궁여지책으로 이 부분에서 능력치를 새로 계산하도록 변경한다.
			// 2002.01.17 - 김성민
			// 이 부분은 스트라이킹 이펙트 자체를 아이템에 붙는 것이 아니라,
			// 크리쳐에 붙는 것으로 변경해 버림으로써 해결해 버렸다.
			// 2002.01.17 -- 김성민
			//if (rvalue != 0)
			//{
			//	SLAYER_RECORD prev;
			//	getSlayerRecord(prev);
			//	initAllStat();
			//	sendRealWearingInfo();
			//	sendModifyInfo(prev);
			//}
		}
	}
	*/

	__END_DEBUG
}

void Slayer::getSlayerRecord(SLAYER_RECORD& record) const
	throw()
{
	__BEGIN_TRY

	record.pSTR[0] = m_STR[0];
	record.pSTR[1] = m_STR[1];
	record.pSTR[2] = m_STR[2];

	record.pDEX[0] = m_DEX[0];
	record.pDEX[1] = m_DEX[1];
	record.pDEX[2] = m_DEX[2];

	record.pINT[0] = m_INT[0];
	record.pINT[1] = m_INT[1];
	record.pINT[2] = m_INT[2];

	record.pHP[0] = m_HP[0];
	record.pHP[1] = m_HP[1];

	record.pMP[0] = m_MP[0];
	record.pMP[1] = m_MP[1];

	record.Rank = getRank();

	record.pDamage[0] = m_Damage[0];
	record.pDamage[1] = m_Damage[1];

	record.Defense     = m_Defense[0];
	record.Protection  = m_Protection[0];
	record.ToHit       = m_ToHit[0];
	record.AttackSpeed = m_AttackSpeed[0];

	__END_CATCH
}

void Slayer::setResurrectZoneIDEx(ZoneID_t id)
	throw()
{
	__BEGIN_TRY

	setResurrectZoneID(id);

	/*
	StringStream sql;
	sql << "ResurrectZone = " << (int)id;
	tinysave(sql.toString());
	*/

	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "ResurrectZone=%d", id);
	tinysave(pField);

	__END_CATCH
}

void Slayer::saveAlignment(Alignment_t alignment)
	throw()
{
	__BEGIN_TRY

	setAlignment(alignment);

	/*
	StringStream sql;
	sql << "Alignment = " << (int)alignment;

	tinysave(sql.toString());
	*/
	// by sigi. 2002.5.15
	char pField[80];
	sprintf(pField, "Alignment=%d", alignment);
	tinysave(pField);
				

	__END_CATCH
}

uint Slayer::getSlayerLevel(void) const
	throw()
{
	__BEGIN_TRY

	uint SumAttr = 0, SumDomain = 0;

	SumAttr += m_STR[ATTR_BASIC];
	SumAttr += m_DEX[ATTR_BASIC];
	SumAttr += m_INT[ATTR_BASIC];

	SumDomain += m_SkillDomainLevels[SKILL_DOMAIN_SWORD];
	SumDomain += m_SkillDomainLevels[SKILL_DOMAIN_BLADE];
	SumDomain += m_SkillDomainLevels[SKILL_DOMAIN_GUN];
	SumDomain += m_SkillDomainLevels[SKILL_DOMAIN_HEAL];
	SumDomain += m_SkillDomainLevels[SKILL_DOMAIN_ENCHANT];

	return (uint)(SumAttr/4 + SumDomain/2);

	__END_CATCH
}

string Slayer::toString () const
	throw()
{
	__BEGIN_DEBUG

	StringStream msg;
	msg << "Slayer("
		//<< "ObjectID:"     << (int)getObjectID()
		<< ",Name:"        << m_Name
		<< ",Sex:"         << Sex2String[m_Sex]
		<< ",HairStyle:"   << HairStyle2String[m_HairStyle]
		<< ",HairColor:"   << (int)m_HairColor
		<< ",SkinColor:"   << (int)m_SkinColor
		<< ",Rank:"        << (int)getRank()
//		<< ",RankExp:"     << (int)m_RankExp
		<< ",RankGoalExp:" << (int)getRankGoalExp()
		<< ",STR:"         << (int)m_STR[ATTR_CURRENT] << "/" << (int)m_STR[ATTR_MAX]
		<< ",DEX:"         << (int)m_DEX[ATTR_CURRENT] << "/" << (int)m_DEX[ATTR_MAX]
		<< ",INT:"         << (int)m_INT[ATTR_CURRENT] << "/" << (int)m_INT[ATTR_MAX]
//		<< ",STRExp:"      << (int)m_STRExp
		<< ",STRGoalExp :" << (int)getSTRGoalExp()
//		<< ",DEXExp:"      << (int)m_DEXExp
//		<< ",INTExp:"      << (int)m_INTExp
		<< ",HP:"          << (int)m_HP[ATTR_CURRENT] << "/" << (int)m_HP[ATTR_MAX]
		<< ",MP:"          << (int)m_MP[ATTR_CURRENT] << "/" << (int)m_MP[ATTR_MAX]
		<< ",Fame:"        << (int)m_Fame
		<< ",Gold:"        << (int)m_Gold
		<< ",GuildID:"     << (int)m_GuildID
		<< ",ZoneID:"      << (int)getZoneID()
		<< ",X:"           << (int)m_X
		<< ",Y:"           << (int)m_Y
		<< ",Sight :"      << (int)m_Sight
		<< ")";
	return msg.toString();

	__END_DEBUG
}

SkillLevel_t Slayer::getSkillDomainLevelSum() const 
	throw() 
{ 
	__BEGIN_TRY

	SkillLevel_t sum = 0;
	sum += m_SkillDomainLevels[SKILL_DOMAIN_BLADE];
	sum += m_SkillDomainLevels[SKILL_DOMAIN_SWORD];
	sum += m_SkillDomainLevels[SKILL_DOMAIN_GUN];
	sum += m_SkillDomainLevels[SKILL_DOMAIN_HEAL];
	sum += m_SkillDomainLevels[SKILL_DOMAIN_ENCHANT];
	return sum;

	__END_CATCH
}


SkillLevel_t Slayer::getHighestSkillDomainLevel() const
	throw()
{
	__BEGIN_TRY

	SkillLevel_t highest;

	highest = max(m_SkillDomainLevels[SKILL_DOMAIN_BLADE], m_SkillDomainLevels[SKILL_DOMAIN_SWORD]);
	highest = max(highest, m_SkillDomainLevels[SKILL_DOMAIN_GUN]);
	highest = max(highest, m_SkillDomainLevels[SKILL_DOMAIN_HEAL]);
	highest = max(highest, m_SkillDomainLevels[SKILL_DOMAIN_ENCHANT]);

	return highest;

	__END_CATCH
}

SkillDomainType_t Slayer::getHighestSkillDomain() const
	throw()
{
	__BEGIN_TRY
	
	SkillDomainType_t highest;	

	if (m_SkillDomainLevels[SKILL_DOMAIN_BLADE] > m_SkillDomainLevels[SKILL_DOMAIN_SWORD] )
		highest = SKILL_DOMAIN_BLADE;
	else
		highest = SKILL_DOMAIN_SWORD;

	if (m_SkillDomainLevels[SKILL_DOMAIN_GUN] > m_SkillDomainLevels[highest] )
		highest = SKILL_DOMAIN_GUN;

	if (m_SkillDomainLevels[SKILL_DOMAIN_HEAL] > m_SkillDomainLevels[highest] )
		highest = SKILL_DOMAIN_HEAL;

	if (m_SkillDomainLevels[SKILL_DOMAIN_ENCHANT] > m_SkillDomainLevels[highest] )
		highest = SKILL_DOMAIN_ENCHANT;

	return highest;

	__END_CATCH
}
	
void Slayer::saveSkills(void) const 
	throw(Error)
{
	__BEGIN_TRY

	map<SkillType_t, SkillSlot*>::const_iterator itr = m_SkillSlot.begin();
	for (; itr != m_SkillSlot.end(); itr++)
	{
		SkillSlot* pSkillSlot = itr->second;
		Assert(pSkillSlot != NULL);

		// 기본 공격 스킬이 아니라면...
		if (pSkillSlot->getSkillType() >= SKILL_DOUBLE_IMPACT)
		{
			pSkillSlot->save(m_Name);
		}
	}

	__END_CATCH
}

IP_t Slayer::getIP(void) const
{
	///*
	Assert(m_pPlayer != NULL);
	Socket* pSocket = m_pPlayer->getSocket();
	Assert(pSocket != NULL);
	return pSocket->getHostIP();
	//*/


	/*
	IP_t IP;
	uint Port;

	// UserIPInfo 테이블에서 사용자 IP를 쿼리 한다.
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT IP, Port FROM UserIPInfo WHERE Name='%s'", getName().c_str());

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			return 0;
		}
		else
		{
			pResult->next();
			IP = pResult->getDWORD(1);
			Port = pResult->getDWORD(2);
			//cout << "Requested IP : " << IP   << endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	struct in_addr sa;
	sa.s_addr = IP;
	cout << getName().c_str() << " = " << inet_ntoa(sa) << ":" << Port << endl;

	RCSay dp;
	dp.setName("server");
	dp.setMessage("ok???");
	g_pLoginServerManager->sendPacket(inet_ntoa(sa), Port, &dp);
	g_pLoginServerManager->sendPacket(g_pConfig->getProperty("LoginServerIP") , 9996, &dp);

	return IP;
	*/
}

void Slayer::saveGears(void) const
	throw(Error)
{
	__BEGIN_TRY

	// 장착하고 있는 아이템들을 저장한다.
	char pField[80];

	for (int i=0; i < Slayer::WEAR_MAX; i++) 
	{
		Item* pItem = m_pWearItem[i];
		if (pItem != NULL) 
		{
			Durability_t maxDurability = computeMaxDurability(pItem);
			if (pItem->getDurability() < maxDurability)
			{

				// 무기인 경우는 총알 개수를 저장한다. by sigi. 2002.5.13
				if (i==Slayer::WEAR_RIGHTHAND)	// 체크 빨리 할려고 서비스로. - -;
				{
					if (pItem->isGun())
					{
//						Gun* pGun = dynamic_cast<Gun*>(pItem);

						if (pItem!=NULL)
						{
							//pItem->saveBullet();
							sprintf(pField, "Durability=%d, BulletCount=%d, Silver=%d", pItem->getDurability(), pItem->getBulletCount(), pItem->getSilver());
							pItem->tinysave(pField);
						}
					}
					// 지금 현재 무기는 전부 은도금된다.
					else //if (pItem->isSilverWeapon())
					{
						sprintf(pField, "Durability=%d, Silver=%d", pItem->getDurability(), pItem->getSilver());
						pItem->tinysave(pField);
					}
				}
				else
				{
					//pItem->save(m_Name, STORAGE_GEAR, 0, i, 0);
					// item저장 최적화. by sigi. 2002.5.13
					sprintf(pField, "Durability=%d", pItem->getDurability());
					pItem->tinysave(pField);
				}
			}
		}
	}

	__END_CATCH
}

void Slayer::saveExps(void) const 
	throw(Error)
{
	__BEGIN_TRY

	// 스킬 핸들러에서 쿼리 숫자를 줄이기 위해서 10으로 나누는 부분들은,
	// 서버 다운이 되지 않고, 정상적으로 로그아웃하는 경우에 
	// 세이브를 명시적으로 해주지 않으면 10 이하 올라간 부분은 날아가 버리게 된다.
	// 그러므로 여기서 세이브를 해 준다. 

	/*
	StringStream sql;
	sql << "UPDATE Slayer SET"
		<< " STRExp = " << m_STRExp
		<< ",DEXExp = " << m_DEXExp
		<< ",INTExp = " << m_INTExp
		<< ",STRGoalExp = " << m_STRGoalExp
		<< ",DEXGoalExp = " << m_DEXGoalExp
		<< ",INTGoalExp = " << m_INTGoalExp
		<< ",BladeExp = " << m_SkillDomainExps[SKILL_DOMAIN_BLADE]
		<< ",BladeGoalExp = " << m_GoalExp[SKILL_DOMAIN_BLADE]
		<< ",SwordExp = " << m_SkillDomainExps[SKILL_DOMAIN_SWORD]
		<< ",SwordGoalExp = " << m_GoalExp[SKILL_DOMAIN_SWORD]
		<< ",GunExp = " << m_SkillDomainExps[SKILL_DOMAIN_GUN]
		<< ",GunGoalExp = " << m_GoalExp[SKILL_DOMAIN_GUN]
		<< ",EnchantExp = " << m_SkillDomainExps[SKILL_DOMAIN_ENCHANT]
		<< ",EnchantGoalExp = " << m_GoalExp[SKILL_DOMAIN_ENCHANT]
		<< ",HealExp = " << m_SkillDomainExps[SKILL_DOMAIN_HEAL]
		<< ",HealGoalExp = " << m_GoalExp[SKILL_DOMAIN_HEAL]
		<< ",ETCExp = " << m_SkillDomainExps[SKILL_DOMAIN_ETC]
		<< ",ETCGoalExp = " << m_GoalExp[SKILL_DOMAIN_ETC]
		<< ",Alignment = " << m_Alignment
		<< ",Fame = " << m_Fame
		<< "  WHERE Name = '" << m_Name << "'";
		//pStmt->executeQuery(sql.toString());
	*/

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("UPDATE Slayer SET STRGoalExp=%lu, DEXGoalExp=%lu, INTGoalExp=%lu, BladeGoalExp=%lu, SwordGoalExp=%lu, GunGoalExp=%lu, EnchantGoalExp=%lu, HealGoalExp=%lu, ETCGoalExp=%lu, Alignment=%d, Fame=%ld, Rank=%d, RankGoalExp=%lu, AdvancementClass=%u, AdvancementGoalExp=%lu, AdvancedSTR=%u, AdvancedDEX=%u, AdvancedINT=%u, Bonus=%u WHERE Name='%s'",
								getSTRGoalExp(), getDEXGoalExp(), getINTGoalExp(), m_GoalExp[SKILL_DOMAIN_BLADE], m_GoalExp[SKILL_DOMAIN_SWORD], m_GoalExp[SKILL_DOMAIN_GUN], m_GoalExp[SKILL_DOMAIN_ENCHANT], m_GoalExp[SKILL_DOMAIN_HEAL], m_GoalExp[SKILL_DOMAIN_ETC], m_Alignment, m_Fame, getRank(), getRankGoalExp(), getAdvancementClassLevel(), getAdvancementClassGoalExp(),
								m_AdvancedSTR, m_AdvancedDEX, m_AdvancedINT, m_AdvancedAttrBonus, m_Name.c_str());


		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}

//----------------------------------------------------------------------
// getShapeInfo
//----------------------------------------------------------------------
// 현재 slayer의 복장을 참고로해서 복장flag/color 정보를 만든다.
// login할때 처리를 빨리하기 위해서다.
//----------------------------------------------------------------------
// 일단 32bit로 32가지를 표현하는걸로도 충분하다고 본다.
// 언젠가? over되면 bitset을 써야겠지..
//
// (!) 색깔은 index색값이 아니고 optionType을 넣어서 사용한다.
//     클라이언트에서 옵션으로 색값을 찾아서 쓴다.
//----------------------------------------------------------------------
void Slayer::getShapeInfo (DWORD& flag, Color_t colors[PCSlayerInfo::SLAYER_COLOR_MAX]) const
//	throw()
{
	__BEGIN_DEBUG

	Item* 						pItem;
	//OptionInfo* 				pOptionInfo;
	PCSlayerInfo::SlayerBits 	slayerBit;
	PCSlayerInfo::SlayerColors 	slayerColor;

	WearPart Part;

	// 초기화
	flag = 0;

	//-----------------------------------------------------------------
	// 성별
	//-----------------------------------------------------------------
	slayerBit	= PCSlayerInfo::SLAYER_BIT_SEX;
	flag |= ((m_Sex? 1:0) << slayerBit);

	//-----------------------------------------------------------------
	// HairStyle
	//-----------------------------------------------------------------
	slayerBit 	= PCSlayerInfo::SLAYER_BIT_HAIRSTYLE1;
	flag |= (m_HairStyle << slayerBit);

	//-----------------------------------------------------------------
	// 바지
	//-----------------------------------------------------------------
	Part = WEAR_LEG;
	pItem = m_pWearItem[Part];
	slayerBit	= PCSlayerInfo::SLAYER_BIT_PANTS1;
	slayerColor = PCSlayerInfo::SLAYER_COLOR_PANTS;
	if (pItem!=NULL && m_pRealWearingCheck[Part])
	{
		ItemType_t IType = pItem->getItemType();

		/*
		if (pItem->getOptionType() != 0)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
			colors[slayerColor] = (pOptionInfo==NULL? 377 : pOptionInfo->getColor());
		}
		*/

//		colors[slayerColor] = (pItem->isUnique()? UNIQUE_OPTION : pItem->getFirstOptionType());
		if (pItem->isTimeLimitItem() ) colors[slayerColor] = QUEST_OPTION;
		else if (pItem->isUnique() ) colors[slayerColor] = UNIQUE_OPTION;
		else colors[slayerColor] = pItem->getFirstOptionType();

		flag |= (getPantsType(IType) << slayerBit);
	} 
	else 
	{
		colors[slayerColor] = 0;
		flag |= (PANTS_BASIC << slayerBit);
	}
	//-----------------------------------------------------------------
	// 쟈켓
	//-----------------------------------------------------------------
	Part = WEAR_BODY;
	pItem = m_pWearItem[Part];
	slayerBit	= PCSlayerInfo::SLAYER_BIT_JACKET1;
	slayerColor = PCSlayerInfo::SLAYER_COLOR_JACKET;
	if (pItem!=NULL && m_pRealWearingCheck[Part])
	{
		ItemType_t IType = pItem->getItemType();

		/*
		if (pItem->getOptionType() != 0)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
			colors[slayerColor] = (pOptionInfo==NULL? 377 : pOptionInfo->getColor());
		}
		*/

//		colors[slayerColor] = (pItem->isUnique()? UNIQUE_OPTION : pItem->getFirstOptionType());

		if (pItem->isTimeLimitItem() ) colors[slayerColor] = QUEST_OPTION;
		else if (pItem->isUnique() ) colors[slayerColor] = UNIQUE_OPTION;
		else colors[slayerColor] = pItem->getFirstOptionType();

		flag |= (getJacketType(IType) << slayerBit);
	} 
	else 
	{
		colors[slayerColor] = 0;
		flag |= (JACKET_BASIC << slayerBit);
	}

	//-----------------------------------------------------------------
	// 투구
	//-----------------------------------------------------------------
	Part = WEAR_HEAD;
	pItem = m_pWearItem[Part];
	slayerBit	= PCSlayerInfo::SLAYER_BIT_HELMET1;
	slayerColor = PCSlayerInfo::SLAYER_COLOR_HELMET;
	if (pItem!=NULL && m_pRealWearingCheck[Part])
	{
		ItemType_t IType = pItem->getItemType();

		/*
		if (pItem->getOptionType() != 0)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
			colors[slayerColor] = (pOptionInfo==NULL? 377 : pOptionInfo->getColor());
		}
		*/

//		colors[slayerColor] = (pItem->isUnique()? UNIQUE_OPTION : pItem->getFirstOptionType());

		if (pItem->isTimeLimitItem() ) colors[slayerColor] = QUEST_OPTION;
		else if (pItem->isUnique() ) colors[slayerColor] = UNIQUE_OPTION;
		else colors[slayerColor] = pItem->getFirstOptionType();

		flag |= (getHelmetType(IType) << slayerBit);

	} 
	else 
	{
		colors[slayerColor] = 0;
		// 없다
	}

	//-----------------------------------------------------------------
	// 방패
	//-----------------------------------------------------------------
	Part = WEAR_LEFTHAND;
	pItem = m_pWearItem[Part];
	slayerBit	= PCSlayerInfo::SLAYER_BIT_SHIELD1;
	slayerColor = PCSlayerInfo::SLAYER_COLOR_SHIELD;
	if (pItem!=NULL 
		&& m_pRealWearingCheck[Part]
		&& pItem->getItemClass()==Item::ITEM_CLASS_SHIELD)
	{
		ItemType_t IType = pItem->getItemType();

		/*
		if (pItem->getOptionType() != 0)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
			colors[slayerColor] = (pOptionInfo==NULL? 377 : pOptionInfo->getColor());
		}
		*/

//		colors[slayerColor] = (pItem->isUnique()? UNIQUE_OPTION : pItem->getFirstOptionType());

//		if (pItem->isUnique() ) colors[slayerColor] = UNIQUE_OPTION;
		if (pItem->isTimeLimitItem() ) colors[slayerColor] = QUEST_OPTION;
		else if (pItem->isUnique() ) colors[slayerColor] = UNIQUE_OPTION;
		else colors[slayerColor] = pItem->getFirstOptionType();

		flag |= (getShieldType(IType) << slayerBit);
	} 
	else 
	{
		colors[slayerColor] = 0;
		// 없다
	}

	//-----------------------------------------------------------------
	// 무기
	//-----------------------------------------------------------------
	Part = WEAR_RIGHTHAND;
	pItem = m_pWearItem[Part];
	slayerBit	= PCSlayerInfo::SLAYER_BIT_WEAPON1;
	slayerColor = PCSlayerInfo::SLAYER_COLOR_WEAPON;

	if (pItem!=NULL && m_pRealWearingCheck[Part])
	{
		DWORD weaponType = 0;

		if (pItem->getItemClass()==Item::ITEM_CLASS_SWORD) 		weaponType = WEAPON_SWORD;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_BLADE) weaponType = WEAPON_BLADE;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_SR)	weaponType = WEAPON_SR;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_AR)	weaponType = WEAPON_AR;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_SG)	weaponType = WEAPON_SG;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_SMG)	weaponType = WEAPON_SMG;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_CROSS)	weaponType = WEAPON_CROSS;
		else if (pItem->getItemClass()==Item::ITEM_CLASS_MACE)	weaponType = WEAPON_MACE;//MACE;

		/*
		if (pItem->getOptionType() != 0)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
			colors[slayerColor] = (pOptionInfo==NULL? 377 : pOptionInfo->getColor());
		}
		*/

		//colors[slayerColor] = (pItem->isUnique()? UNIQUE_OPTION : pItem->getFirstOptionType());

		if (pItem->isUnique() ) colors[slayerColor] = UNIQUE_OPTION;
		else if (pItem->isTimeLimitItem() ) colors[slayerColor] = QUEST_OPTION;
		else colors[slayerColor] = pItem->getFirstOptionType();

		flag |= (weaponType << slayerBit);
	}
	else
	{
		colors[slayerColor] = 0;
	}

	__END_DEBUG
}


//----------------------------------------------------------------------
// save InitialRank
//----------------------------------------------------------------------
// Rank, RankExp, RankGoalExp의 초기값을 저장한다.
//----------------------------------------------------------------------
void Slayer::saveInitialRank(void)
	throw()
{
	int maxDomainLevel = getHighestSkillDomainLevel();

	int curRank = max(1, (maxDomainLevel+3) / 4);
	m_pRank->SET_LEVEL(curRank);
/*
	SLAYER_RECORD prev;
	getSlayerRecord(prev);

	RankExp_t accumExp = 0;

	setRank(curRank);

	if (curRank!=1)
	{
		RankEXPInfo* pBeforeExpInfo = g_pRankEXPInfoManager[RANK_TYPE_SLAYER]->getRankEXPInfo(curRank-1);
		accumExp = pBeforeExpInfo->getAccumExp();
	}
	
	RankEXPInfo* pNextExpInfo = g_pRankEXPInfoManager[RANK_TYPE_SLAYER]->getRankEXPInfo(curRank);
	Exp_t NextGoalExp = pNextExpInfo->getGoalExp();

	setRankGoalExp(NextGoalExp);
*/
	char pField[80];
	sprintf(pField, "Rank=%d, RankExp=%lu, RankGoalExp=%lu",
					getRank(), getRankExp(), getRankGoalExp());
	tinysave(pField);
	setRankExpSaveCount(0);

	/*
	sendModifyInfo(prev);

	if (m_pZone != NULL)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		gcOtherModifyInfo.setObjectID(getObjectID());
		gcOtherModifyInfo.addShortData(MODIFY_RANK, curRank);

		m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
	}
	*/
}

Slayer::WearPart 
Slayer::getWearPart(Item::ItemClass IClass) const
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_COAT 		: return WEAR_BODY;
		case Item::ITEM_CLASS_TROUSER 	: return WEAR_LEG;

		case Item::ITEM_CLASS_SWORD 	: 
		case Item::ITEM_CLASS_BLADE 	: 
		case Item::ITEM_CLASS_AR 		: 
		case Item::ITEM_CLASS_SR 		: 
		case Item::ITEM_CLASS_SG 		: 
		case Item::ITEM_CLASS_SMG 		: 
		case Item::ITEM_CLASS_MACE 		: 
		case Item::ITEM_CLASS_CROSS 	: 
			return WEAR_RIGHTHAND;

		case Item::ITEM_CLASS_HELM 		: return WEAR_HEAD;

		case Item::ITEM_CLASS_SHIELD 	: return WEAR_LEFTHAND;

		case Item::ITEM_CLASS_SHOULDER_ARMOR : return WEAR_SHOULDER;

		default :
			  return WEAR_MAX;
	}

	return WEAR_MAX;
}

bool
Slayer::changeShape(Item* pItem, Color_t color, bool bSendPacket)
{
	Item::ItemClass IClass = pItem->getItemClass();
	ItemType_t 		IType  = pItem->getItemType();

	WearPart Part = getWearPart(IClass);

	if (Part==WEAR_MAX)
		return false;

	bool bRealWear = m_pRealWearingCheck[Part];

	if (bRealWear)
		return addShape(IClass, IType, color);

	return removeShape(IClass, bSendPacket);
}

bool
Slayer::addShape(Item::ItemClass IClass, ItemType_t IType, Color_t color)
{
	bool bisWeapon = false;
	bool bisChange = false;

	switch (IClass)
	{
		case Item::ITEM_CLASS_MACE:
			bisWeapon = true;
			bisChange = true;
			//m_SlayerInfo.setWeaponType(WEAPON_MACE);

			m_SlayerInfo.setWeaponType(WEAPON_MACE);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_CROSS:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_CROSS);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_BLADE:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_BLADE);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_AR:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_AR);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_SR:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_SR);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_SMG:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_SMG);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_SG:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_SG);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_HELM:
			bisChange = true;

			m_SlayerInfo.setHelmetType(getHelmetType(IType));
			m_SlayerInfo.setHelmetColor(color);
			break;
		case Item::ITEM_CLASS_SHIELD:
			bisChange = true;

			m_SlayerInfo.setShieldType(getShieldType(IType));
			m_SlayerInfo.setShieldColor(color);
			break;
		case Item::ITEM_CLASS_SWORD:
			bisWeapon = true;
			bisChange = true;

			m_SlayerInfo.setWeaponType(WEAPON_SWORD);
			m_SlayerInfo.setWeaponColor(color);
			break;
		case Item::ITEM_CLASS_COAT:
			bisChange = true;

			m_SlayerInfo.setJacketType(getJacketType(IType));
			m_SlayerInfo.setJacketColor(color);
			break;
		case Item::ITEM_CLASS_TROUSER:
			bisChange = true;

			m_SlayerInfo.setPantsType(getPantsType(IType));
			m_SlayerInfo.setPantsColor(color);
			break;

		case Item::ITEM_CLASS_SHOULDER_ARMOR:
			bisChange = true;

			m_SlayerInfo.setShoulderType(getShoulderType(IType));
			m_SlayerInfo.setShoulderColor(color);
			break;

		default:
			break;
	}

	return bisChange;
}

bool
Slayer::removeShape(Item::ItemClass IClass, bool bSendPacket)
{
	bool bisWeapon = false;

	// 죽을때 아이템 떨어뜨릴때는 자신에게도 패킷을 보내야하기 때문에..
	// parameter로 받는게 좋을텐데 header 안바꿀려고.. -_-;
	// by sigi. 2002.11.7
	Creature* pOwner = (isDead()? NULL : this);

	switch (IClass)
	{
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SMG:
		case Item::ITEM_CLASS_SG:
		{
			bisWeapon = true;
			m_SlayerInfo.setWeaponType(WEAPON_NONE);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_RIGHTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;
			
		case Item::ITEM_CLASS_HELM:
		{
			m_SlayerInfo.setHelmetType(HELMET_NONE);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_HELM);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;

		case Item::ITEM_CLASS_SHIELD:
		{
			m_SlayerInfo.setShieldType(SHIELD_NONE);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_LEFTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;

		case Item::ITEM_CLASS_SWORD:
		{
			bisWeapon = true;
			m_SlayerInfo.setWeaponType(WEAPON_NONE);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_RIGHTHAND);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;

		case Item::ITEM_CLASS_COAT:
		{
			m_SlayerInfo.setJacketType(JACKET_BASIC);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_COAT);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;

		case Item::ITEM_CLASS_TROUSER:
		{
			m_SlayerInfo.setPantsType(PANTS_BASIC);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_TROUSER);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;

		case Item::ITEM_CLASS_SHOULDER_ARMOR:
		{
			m_SlayerInfo.setShoulderType(0);

			if (bSendPacket)	// by sigi. 2002.11.6
			{
				GCTakeOff _GCTakeOff;
				_GCTakeOff.setObjectID(getObjectID());
				_GCTakeOff.setSlotID((SlotID_t)ADDON_TROUSER);
				m_pZone->broadcastPacket(getX(), getY(), &_GCTakeOff, pOwner);
			}
		}
		break;

		default:
			break;
	}

	return bisWeapon;
}

Color_t 
Slayer::getItemShapeColor(Item* pItem, OptionInfo* pOptionInfo) const
{
	Color_t color;

	if (pItem->isTimeLimitItem() )
	{
		// 퀘스트 아이템도 특정한 색깔로 대체해서 처리한다.
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
 

bool Slayer::canPlayFree()
	throw(Error)
{
	__BEGIN_TRY

	return getSkillDomainLevelSum() <= g_pVariableManager->getVariable(FREE_PLAY_SLAYER_DOMAIN_SUM);

	__END_CATCH
}

bool Slayer::isPayPlayAvaiable() 
	throw(Error)
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

		int DomainSUM = getSkillDomainLevelSum();

		// 제한된 도메인합까지 play가능
		if (DomainSUM <= g_pVariableManager->getVariable(FREE_PLAY_SLAYER_DOMAIN_SUM))
		{
			return true;
		}
	}

	return false;

// 애드빌 빌링을 사용하지 않고 사용자 제한을 하는 경우
#elif defined(__PAY_SYSTEM_FREE_LIMIT__)

	if (!pGamePlayer->isPayPlaying())
	{
		int DomainSUM = getSkillDomainLevelSum();

		// 제한된 도메인합까지 play가능
		if (DomainSUM <= g_pVariableManager->getVariable(FREE_PLAY_SLAYER_DOMAIN_SUM))
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

QuestGrade_t Slayer::getQuestGrade() const throw() { return getTotalAttr(ATTR_BASIC ) - getSkillDomainLevel(SKILL_DOMAIN_HEAL)*1.5 - getSkillDomainLevel(SKILL_DOMAIN_ENCHANT)*1.5; }

// 순수 능력치 합이 40 미만이면 초보(Novice) 이다.
bool Slayer::isNovice() const
{
	return (m_STR[ATTR_BASIC] + m_DEX[ATTR_BASIC] + m_INT[ATTR_BASIC] ) <= 40;
}

void Slayer::divideAttrExp(AttrKind kind, Damage_t damage, ModifyInfo& modifyInfo)
{
	SLAYER_RECORD prev;
	getSlayerRecord(prev);

	damage = (Damage_t)getPercentValue(damage, AttrExpTimebandFactor[getZoneTimeband(m_pZone)]);

	if(g_pVariableManager->getExpRatio()>100 && g_pVariableManager->getEventActivate() == 1)
		damage = getPercentValue(damage, g_pVariableManager->getExpRatio());

	// 시간대에 따라 경험치 두배
	if (isAffectExp2X() )
		damage <<= 1;

	if (isFlag(Effect::EFFECT_CLASS_BONUS_EXP ) ) damage *= 2;

	Exp_t MainPoint = max(1, damage * 8 / 10);
	Exp_t SubPoint = max(1, damage / 10);

#ifdef __CHINA_SERVER__

	// 중국쪽은 레벨별로 능력치 경험치 얻는 것이 다르다
	float userExpConst = 1.0;

	SkillLevel_t HighSkillLevel = getHighestSkillDomainLevel();

	if (HighSkillLevel < 50 )
		userExpConst = 1.0;
	else if (HighSkillLevel > 49 && HighSkillLevel < 75 )
		userExpConst = 0.8;
	else if (HighSkillLevel > 74 && HighSkillLevel < 100 )
		userExpConst = 0.6;
	else if (HighSkillLevel > 99 )
		userExpConst = 0.4;

	MainPoint = (Exp_t)(MainPoint*userExpConst);
	SubPoint = (Exp_t)(SubPoint*userExpConst);

#endif

	// 슬레이어 능력치는 도메인 레벨 100이전에는 총합 300으로 제한 된다.(기존처럼 50, 200, 50 으로..)또한 그 이후의 경험치는 누적되지 않는다.
	// 그리고 도메인 레벨 이 100을 넘어서면 다시 능력치 경험치가 누적되어 능력치가 올라가기 시작한다.
	// 도메인 레벨이 100 아래로 도로 떨어졌어도 능력치 총합이 300을 넘었을 경우 300의 제한을 받지 않는다.

	SkillLevel_t	MaxDomainLevel	= getHighestSkillDomainLevel();
	Attr_t			TotalAttr		= getTotalAttr(ATTR_BASIC);
    Attr_t          TotalAttrBound      = 0;        // 능력치 총합 제한
    Attr_t          AttrBound           = 0;        // 단일 능력치 제한
    Attr_t          OneAttrExpBound     = 0;        // 한 개의 능력치에만 경험치 주는 능력치 총합 경계값
	Attr_t			SubAttrMax			= 0;		// 보조 능력치 최대값

	if (MaxDomainLevel <= SLAYER_BOUND_LEVEL && TotalAttr <= SLAYER_BOUND_ATTR_SUM )
	{
		TotalAttrBound  = SLAYER_BOUND_ATTR_SUM;        // 300
		AttrBound       = SLAYER_BOUND_ATTR;            // 200
		OneAttrExpBound = SLAYER_BOUND_ONE_EXP_ATTR;    // 200
		SubAttrMax		= SLAYER_BOUND_SUB_ATTR;		// 50
	}
	else
	{
		TotalAttrBound  = SLAYER_MAX_ATTR_SUM;          // 435
		AttrBound       = SLAYER_MAX_ATTR;              // 295
		OneAttrExpBound = SLAYER_ONE_EXP_ATTR;          // 400
		SubAttrMax		= SLAYER_MAX_SUB_ATTR;			// 70
	}

	Attr* pMainAttr = m_pAttrs[kind];
	Attr* pSubAttrs[2];
	int count = 0;

	bool levelUpSubAttrs[2] = { false, false };

	for (int itr = ATTR_KIND_STR ; itr != ATTR_KIND_MAX ; ++itr )
	{
		if (m_pAttrs[itr] != pMainAttr ) pSubAttrs[count++] = m_pAttrs[itr];
	}

	if (pSubAttrs[0]->getLevel() < pSubAttrs[1]->getLevel() )
	{
		Attr* pTemp;
		SWAP(pSubAttrs[0], pSubAttrs[1], pTemp);
	}

	bool downOtherLevel = TotalAttr >= TotalAttrBound;
	bool upOtherLevel = TotalAttr < OneAttrExpBound;
	bool canLevelUp = pMainAttr->getLevel() < AttrBound;
	bool levelUpMainAttr = pMainAttr->increaseExp(MainPoint, canLevelUp);

	if (levelUpMainAttr && downOtherLevel )
	{
		pSubAttrs[0]->levelDown();
		levelUpSubAttrs[0] = true;
	}

	if (upOtherLevel )
	{
		levelUpSubAttrs[0] = pSubAttrs[0]->increaseExp(SubPoint ) || levelUpSubAttrs[0];
		levelUpSubAttrs[1] = pSubAttrs[1]->increaseExp(SubPoint);
	}
	else
	{
		if (pSubAttrs[0]->getLevel() < SubAttrMax )
			levelUpSubAttrs[0] = pSubAttrs[0]->increaseExp(SubPoint ) || levelUpSubAttrs[0];
		if (pSubAttrs[1]->getLevel() < SubAttrMax )
			levelUpSubAttrs[1] = pSubAttrs[1]->increaseExp(SubPoint ) || levelUpSubAttrs[1];
	}

	if (++m_AttrExpSaveCount > ATTR_EXP_SAVE_PERIOD )
	{
		char pField[256];
		sprintf(pField, "STRGoalExp=%ld, DEXGoalExp=%ld, INTGoalExp=%ld",
							getSTRGoalExp(), getDEXGoalExp(), getINTGoalExp());

		tinysave(pField);

		m_AttrExpSaveCount = 0;
	}

	if (levelUpMainAttr || levelUpSubAttrs[0] || levelUpSubAttrs[1] )
	{
		healCreatureForLevelUp(this, modifyInfo, &prev);
		sendEffectLevelUp(this);
		if (g_pVariableManager->isNewbieTransportToGuild() ) checkNewbieTransportToGuild(this);

		char pField[256];
		sprintf(pField, "STR=%d, DEX=%d, INTE=%d, STRGoalExp=%ld, DEXGoalExp=%ld, INTGoalExp=%ld",
//							getSTR(ATTR_BASIC), getDEX(ATTR_BASIC), getINT(ATTR_BASIC), getSTRGoalExp(), getDEXGoalExp(), getINTGoalExp();
							m_pAttrs[ATTR_KIND_STR]->getLevel(),
							m_pAttrs[ATTR_KIND_DEX]->getLevel(),
							m_pAttrs[ATTR_KIND_INT]->getLevel(),
							getSTRGoalExp(), getDEXGoalExp(), getINTGoalExp());

		tinysave(pField);
	}

	modifyInfo.addLongData(MODIFY_STR_EXP, getSTRGoalExp());
	modifyInfo.addLongData(MODIFY_DEX_EXP, getDEXGoalExp());
	modifyInfo.addLongData(MODIFY_INT_EXP, getINTGoalExp());
}

void Slayer::setLastTarget(ObjectID_t value )
{
	if (getPet() != NULL && value != getLastTarget() )
	{
		GCOtherModifyInfo gcOMI;
		gcOMI.setObjectID(getObjectID());
		gcOMI.addLongData(MODIFY_LAST_TARGET, value);

		m_pZone->broadcastPacket(getX(), getY(), &gcOMI, this);

		GCModifyInformation gcMI;
		gcMI.addLongData(MODIFY_LAST_TARGET, value);

		getPlayer()->sendPacket(&gcMI);
	}

	Creature::setLastTarget(value);
}

void Slayer::initPetQuestTarget()
{
	QuestGrade_t grade = getQuestGrade();

	int minClass = 1, maxClass = 1;

	if (grade <= 60 )
	{
		minClass = maxClass = 2;
	}
	else if (grade <= 95 )
	{
		minClass = maxClass = 3;
	}
	else if (grade <= 130 )
	{
		minClass = 4; maxClass = 5;
	}
	else if (grade <= 170 )
	{
		minClass = maxClass = 6;
	}
	else if (grade <= 210 )
	{
		minClass = maxClass = 7;
	}
	else if (grade <= 240 )
	{
		minClass = 7; maxClass = 8;
	}
	else if (grade <= 270 )
	{
		minClass = 8; maxClass = 9;
	}
	else if (grade <= 290 )
	{
		minClass = 9; maxClass = 10;
	}
	else if (grade <= 300 )
	{
		minClass = maxClass = 10;
	}
	else if (grade <= 320 )
	{
		minClass = 10; maxClass = 11;
	}
	else if (grade <= 360 )
	{
		minClass = 10; maxClass = 11;
	}
	else
	{
		minClass = 11; maxClass = 12;
	}

	m_TargetMonster = g_pMonsterInfoManager->getRandomMonsterByClass(minClass, maxClass);
	m_TargetNum = 80;
	m_TimeLimit = 3600;
}
