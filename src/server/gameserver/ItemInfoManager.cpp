//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemInfoManager.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Exception.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "StringStream.h"

#include "AR.h"
#include "Belt.h"
#include "Blade.h"
#include "Bomb.h"
#include "BombMaterial.h"
#include "Bracelet.h"
#include "Coat.h"
#include "Cross.h"
#include "ETC.h"
#include "Glove.h"
#include "Helm.h"
#include "HolyWater.h"
#include "Potion.h"
#include "Key.h"
#include "LearningItem.h"
#include "Magazine.h"
#include "Mine.h"
#include "Money.h"
#include "Motorcycle.h"
#include "Necklace.h"
#include "Ring.h"
#include "SG.h"
#include "SMG.h"
#include "Shield.h"
#include "Shoes.h"
#include "Sword.h"
#include "SR.h"
#include "Trouser.h"
#include "VampireBracelet.h"
#include "VampireNecklace.h"
#include "VampireRing.h"
#include "Water.h"
#include "VampireCoat.h"
#include "Skull.h"
#include "Mace.h"
#include "Serum.h"
#include "VampireETC.h"
#include "SlayerPortalItem.h"
#include "VampirePortalItem.h"
#include "EventGiftBox.h"
#include "EventStar.h"
#include "VampireEarring.h"
#include "Relic.h"
#include "VampireWeapon.h"
#include "VampireAmulet.h"
#include "QuestItem.h"
#include "EventTree.h"
#include "EventETC.h"
#include "BloodBible.h"
#include "CastleSymbol.h"
#include "CoupleRing.h"
#include "VampireCoupleRing.h"
#include "EventItem.h"
#include "DyePotion.h"
#include "ResurrectItem.h"
#include "MixingItem.h"
#include "OustersArmsband.h"
#include "OustersBoots.h"
#include "OustersChakram.h"
#include "OustersCirclet.h"
#include "OustersCoat.h"
#include "OustersPendent.h"
#include "OustersRing.h"
#include "OustersStone.h"
#include "OustersWristlet.h"
#include "Larva.h"
#include "Pupa.h"
#include "ComposMei.h"
#include "OustersSummonItem.h"
#include "EffectItem.h"
#include "CodeSheet.h"
#include "item/MoonCard.h"
#include "Sweeper.h"
#include "PetItem.h"
#include "PetFood.h"
#include "PetEnchantItem.h"
#include "LuckyBag.h"
#include "SMSItem.h"
#include "CoreZap.h"
#include "TrapItem.h"
#include "WarItem.h"
#include "CarryingReceiver.h"
#include "ShoulderArmor.h"
#include "Dermis.h"
#include "Persona.h"
#include "Fascia.h"
#include "Mitten.h"
#include "SubInventory.h"


#include "Properties.h"

#include "OptionInfo.h"


//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
ItemInfoManager::ItemInfoManager()
	throw()
{
	__BEGIN_TRY

	for (int i = 0 ; i < Item::ITEM_CLASS_MAX ; i ++)
		m_InfoClassManagers[i] = NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////
ItemInfoManager::~ItemInfoManager()
	throw()
{
	__BEGIN_TRY

	for (int i = 0 ; i < Item::ITEM_CLASS_MAX ; i ++) 
	{
		SAFE_DELETE(m_InfoClassManagers[i]);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ItemInfoManager::init()
//////////////////////////////////////////////////////////////////////////////
void ItemInfoManager::init ()
	throw(Error)
{
	__BEGIN_TRY

	// ItemIDSuccessor와 Base를 입력한다.
	m_ItemIDSuccessor = g_pConfig->getPropertyInt("ServerCount");
	m_ItemIDBase      = g_pConfig->getPropertyInt("ServerID");

    cout << "[GAMESERVER] Loading ItemInfoManager..." << endl;
	// initialize GunInfoManager
	g_pARInfoManager = new ARInfoManager ();
	g_pARInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_AR] = g_pARInfoManager;
	AR::initItemIDRegistry();

	// initialize BladeInfoManager
	g_pBeltInfoManager = new BeltInfoManager ();
	g_pBeltInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_BELT] = g_pBeltInfoManager;
	Belt::initItemIDRegistry();

	// initialize CrossInfoManager
	g_pCrossInfoManager = new CrossInfoManager ();
	g_pCrossInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_CROSS] = g_pCrossInfoManager;
	Cross::initItemIDRegistry();

	// initialize BladeInfoManager
	g_pBladeInfoManager = new BladeInfoManager ();
	g_pBladeInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_BLADE] = g_pBladeInfoManager;
	Blade::initItemIDRegistry();

	// initialize BombInfoManager
	g_pBombInfoManager = new BombInfoManager ();
	g_pBombInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_BOMB] = g_pBombInfoManager;
	Bomb::initItemIDRegistry();

	// initialize BombMeterialInfoManager
	g_pBombMaterialInfoManager = new BombMaterialInfoManager ();
	g_pBombMaterialInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_BOMB_MATERIAL] = g_pBombMaterialInfoManager;
	BombMaterial::initItemIDRegistry();

	// initialize BraceletInfoManager
	g_pBraceletInfoManager = new BraceletInfoManager ();
	g_pBraceletInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_BRACELET] = g_pBraceletInfoManager;
	Bracelet::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pCoatInfoManager = new CoatInfoManager ();
	g_pCoatInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_COAT] = g_pCoatInfoManager;
	Coat::initItemIDRegistry();

	// initialize ETCInfoManager
	g_pETCInfoManager = new ETCInfoManager ();
	g_pETCInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_ETC] = g_pETCInfoManager;
	ETC::initItemIDRegistry();

	// initialize GloveInfoManager
	g_pGloveInfoManager = new GloveInfoManager ();
	g_pGloveInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_GLOVE] = g_pGloveInfoManager;
	Glove::initItemIDRegistry();

	// initialize HelmInfoManager
	g_pHelmInfoManager = new HelmInfoManager ();
	g_pHelmInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_HELM] = g_pHelmInfoManager;
	Helm::initItemIDRegistry();

	// initialize HolyWaterInfoManager
	g_pHolyWaterInfoManager = new HolyWaterInfoManager ();
	g_pHolyWaterInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_HOLYWATER] = g_pHolyWaterInfoManager;
	HolyWater::initItemIDRegistry();

	// initialize KeyInfoManager 
	g_pKeyInfoManager = new KeyInfoManager ();
	g_pKeyInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_KEY] = g_pKeyInfoManager;
	Key::initItemIDRegistry();

	// initialize LearningItemInfoManager
	g_pLearningItemInfoManager = new LearningItemInfoManager ();
	g_pLearningItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_LEARNINGITEM] = g_pLearningItemInfoManager;
	LearningItem::initItemIDRegistry();

	// initialize MagazineInfoManager
	g_pMagazineInfoManager = new MagazineInfoManager ();
	g_pMagazineInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MAGAZINE] = g_pMagazineInfoManager;
	Magazine::initItemIDRegistry();

	// initialize MineInfoManager
	g_pMineInfoManager = new MineInfoManager ();
	g_pMineInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MINE] = g_pMineInfoManager;
	Mine::initItemIDRegistry();

	// initialize WaterInfoManager 
	g_pMoneyInfoManager = new MoneyInfoManager ();
	g_pMoneyInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MONEY] = g_pMoneyInfoManager;
	Money::initItemIDRegistry();

	// initialize MotorcycleInfoManager 
	g_pMotorcycleInfoManager = new MotorcycleInfoManager ();
	g_pMotorcycleInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MOTORCYCLE] = g_pMotorcycleInfoManager;
	Motorcycle::initItemIDRegistry();

	// initialize NecklaceInfoManager
	g_pNecklaceInfoManager = new NecklaceInfoManager ();
	g_pNecklaceInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_NECKLACE] = g_pNecklaceInfoManager;
	Necklace::initItemIDRegistry();

	// initialize PotionInfoManager
	g_pPotionInfoManager = new PotionInfoManager();
	g_pPotionInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_POTION] = g_pPotionInfoManager;
	Potion::initItemIDRegistry();

	// initialize RingInfoManager
	g_pRingInfoManager = new RingInfoManager ();
	g_pRingInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_RING] = g_pRingInfoManager;
	Ring::initItemIDRegistry();

	// initialize SGInfoManager
	g_pSGInfoManager = new SGInfoManager ();
	g_pSGInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SG] = g_pSGInfoManager;
	SG::initItemIDRegistry();

	// initialize SMGInfoManager
	g_pSMGInfoManager = new SMGInfoManager ();
	g_pSMGInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SMG] = g_pSMGInfoManager;
	SMG::initItemIDRegistry();

	// initialize ShieldInfoManager
	g_pShieldInfoManager = new ShieldInfoManager ();
	g_pShieldInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SHIELD] = g_pShieldInfoManager;
	Shield::initItemIDRegistry();

	// initialize ShoesInfoManager
	g_pShoesInfoManager = new ShoesInfoManager ();
	g_pShoesInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SHOES] = g_pShoesInfoManager;
	Shoes::initItemIDRegistry();

	// initialize SwordInfoManager
	g_pSwordInfoManager = new SwordInfoManager();
	g_pSwordInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SWORD] = g_pSwordInfoManager;
	Sword::initItemIDRegistry();

	// initialize SRInfoManager
	g_pSRInfoManager = new SRInfoManager ();
	g_pSRInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SR] = g_pSRInfoManager;
	SR::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pTrouserInfoManager = new TrouserInfoManager ();
	g_pTrouserInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_TROUSER] = g_pTrouserInfoManager;
	Trouser::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pVampireBraceletInfoManager = new VampireBraceletInfoManager ();
	g_pVampireBraceletInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_BRACELET] = g_pVampireBraceletInfoManager;
	VampireBracelet::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pVampireNecklaceInfoManager = new VampireNecklaceInfoManager ();
	g_pVampireNecklaceInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_NECKLACE] = g_pVampireNecklaceInfoManager;
	VampireNecklace::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pVampireRingInfoManager = new VampireRingInfoManager ();
	g_pVampireRingInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_RING] = g_pVampireRingInfoManager;
	VampireRing::initItemIDRegistry();

	// initialize WaterInfoManager 
	g_pWaterInfoManager = new WaterInfoManager ();
	g_pWaterInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_WATER] = g_pWaterInfoManager;
	Water::initItemIDRegistry();

	// initialize VampireCoatInfoManager
	g_pVampireCoatInfoManager = new VampireCoatInfoManager ();
	g_pVampireCoatInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_COAT] = g_pVampireCoatInfoManager;
	VampireCoat::initItemIDRegistry();

	// initialize SkullInfoManager
	g_pSkullInfoManager = new SkullInfoManager ();
	g_pSkullInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SKULL] = g_pSkullInfoManager;
	Skull::initItemIDRegistry();

	// initialize MaceInfoManager
	g_pMaceInfoManager = new MaceInfoManager ();
	g_pMaceInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MACE] = g_pMaceInfoManager;
	Mace::initItemIDRegistry();

	// initialize SerumInfoManager
	g_pSerumInfoManager = new SerumInfoManager ();
	g_pSerumInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SERUM] = g_pSerumInfoManager;
	Serum::initItemIDRegistry();

	// initialize VampireETCInfoManager
	g_pVampireETCInfoManager = new VampireETCInfoManager ();
	g_pVampireETCInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_ETC] = g_pVampireETCInfoManager;
	VampireETC::initItemIDRegistry();

	// initialize SlayerPortalItemInfoManager
	g_pSlayerPortalItemInfoManager = new SlayerPortalItemInfoManager ();
	g_pSlayerPortalItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SLAYER_PORTAL_ITEM] = g_pSlayerPortalItemInfoManager;
	SlayerPortalItem::initItemIDRegistry();

	// initialize VampirePortalItemInfoManager
	g_pVampirePortalItemInfoManager = new VampirePortalItemInfoManager ();
	g_pVampirePortalItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM] = g_pVampirePortalItemInfoManager;
	VampirePortalItem::initItemIDRegistry();

	// initialize EventGiftBoxInfoManager
	g_pEventGiftBoxInfoManager = new EventGiftBoxInfoManager ();
	g_pEventGiftBoxInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_EVENT_GIFT_BOX] = g_pEventGiftBoxInfoManager;
	EventGiftBox::initItemIDRegistry();

	// initialize EventStarInfoManager
	g_pEventStarInfoManager = new EventStarInfoManager ();
	g_pEventStarInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_EVENT_STAR] = g_pEventStarInfoManager;
	EventStar::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pVampireEarringInfoManager = new VampireEarringInfoManager ();
	g_pVampireEarringInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_EARRING] = g_pVampireEarringInfoManager;
	VampireEarring::initItemIDRegistry();

	g_pRelicInfoManager = new RelicInfoManager();
	g_pRelicInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_RELIC] = g_pRelicInfoManager;
	Relic::initItemIDRegistry();

	// initialize VampireBraceletInfoManager
	g_pVampireWeaponInfoManager = new VampireWeaponInfoManager ();
	g_pVampireWeaponInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_WEAPON] = g_pVampireWeaponInfoManager;
	VampireWeapon::initItemIDRegistry();

	g_pVampireAmuletInfoManager = new VampireAmuletInfoManager();
	g_pVampireAmuletInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_AMULET] = g_pVampireAmuletInfoManager;
	VampireAmulet::initItemIDRegistry();

	g_pQuestItemInfoManager = new QuestItemInfoManager ();
	g_pQuestItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_QUEST_ITEM] = g_pQuestItemInfoManager;
	QuestItem::initItemIDRegistry();

	g_pEventTreeInfoManager = new EventTreeInfoManager ();
	g_pEventTreeInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_EVENT_TREE] = g_pEventTreeInfoManager;
	EventTree::initItemIDRegistry();

	g_pEventETCInfoManager = new EventETCInfoManager ();
	g_pEventETCInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_EVENT_ETC] = g_pEventETCInfoManager;
	EventETC::initItemIDRegistry();

	g_pBloodBibleInfoManager = new BloodBibleInfoManager ();
	g_pBloodBibleInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_BLOOD_BIBLE] = g_pBloodBibleInfoManager;
	BloodBible::initItemIDRegistry();

	g_pCastleSymbolInfoManager = new CastleSymbolInfoManager ();
	g_pCastleSymbolInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_CASTLE_SYMBOL] = g_pCastleSymbolInfoManager;
	CastleSymbol::initItemIDRegistry();
	
	g_pCoupleRingInfoManager = new CoupleRingInfoManager ();
	g_pCoupleRingInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_COUPLE_RING] = g_pCoupleRingInfoManager;
	CoupleRing::initItemIDRegistry();

	g_pVampireCoupleRingInfoManager = new VampireCoupleRingInfoManager ();
	g_pVampireCoupleRingInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_VAMPIRE_COUPLE_RING] = g_pVampireCoupleRingInfoManager;
	VampireCoupleRing::initItemIDRegistry();

	g_pEventItemInfoManager = new EventItemInfoManager ();
	g_pEventItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_EVENT_ITEM] = g_pEventItemInfoManager;
	EventItem::initItemIDRegistry();

	g_pDyePotionInfoManager = new DyePotionInfoManager ();
	g_pDyePotionInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_DYE_POTION] = g_pDyePotionInfoManager;
	DyePotion::initItemIDRegistry();

	g_pResurrectItemInfoManager = new ResurrectItemInfoManager ();
	g_pResurrectItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_RESURRECT_ITEM] = g_pResurrectItemInfoManager;
	ResurrectItem::initItemIDRegistry();

	g_pMixingItemInfoManager = new MixingItemInfoManager ();
	g_pMixingItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MIXING_ITEM] = g_pMixingItemInfoManager;
	MixingItem::initItemIDRegistry();

	g_pOustersArmsbandInfoManager = new OustersArmsbandInfoManager ();
	g_pOustersArmsbandInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_ARMSBAND] = g_pOustersArmsbandInfoManager;
	OustersArmsband::initItemIDRegistry();

	g_pOustersBootsInfoManager = new OustersBootsInfoManager ();
	g_pOustersBootsInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_BOOTS] = g_pOustersBootsInfoManager;
	OustersBoots::initItemIDRegistry();

	g_pOustersChakramInfoManager = new OustersChakramInfoManager ();
	g_pOustersChakramInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_CHAKRAM] = g_pOustersChakramInfoManager;
	OustersChakram::initItemIDRegistry();

	g_pOustersCircletInfoManager = new OustersCircletInfoManager ();
	g_pOustersCircletInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_CIRCLET] = g_pOustersCircletInfoManager;
	OustersCirclet::initItemIDRegistry();

	g_pOustersCoatInfoManager = new OustersCoatInfoManager ();
	g_pOustersCoatInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_COAT] = g_pOustersCoatInfoManager;
	OustersCoat::initItemIDRegistry();

	g_pOustersPendentInfoManager = new OustersPendentInfoManager ();
	g_pOustersPendentInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_PENDENT] = g_pOustersPendentInfoManager;
	OustersPendent::initItemIDRegistry();

	g_pOustersRingInfoManager = new OustersRingInfoManager ();
	g_pOustersRingInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_RING] = g_pOustersRingInfoManager;
	OustersRing::initItemIDRegistry();

	g_pOustersStoneInfoManager = new OustersStoneInfoManager ();
	g_pOustersStoneInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_STONE] = g_pOustersStoneInfoManager;
	OustersStone::initItemIDRegistry();

	g_pOustersWristletInfoManager = new OustersWristletInfoManager ();
	g_pOustersWristletInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_WRISTLET] = g_pOustersWristletInfoManager;
	OustersWristlet::initItemIDRegistry();

	g_pLarvaInfoManager = new LarvaInfoManager ();
	g_pLarvaInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_LARVA] = g_pLarvaInfoManager;
	Larva::initItemIDRegistry();

	g_pPupaInfoManager = new PupaInfoManager ();
	g_pPupaInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_PUPA] = g_pPupaInfoManager;
	Pupa::initItemIDRegistry();

	g_pComposMeiInfoManager = new ComposMeiInfoManager ();
	g_pComposMeiInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_COMPOS_MEI] = g_pComposMeiInfoManager;
	ComposMei::initItemIDRegistry();

	g_pOustersSummonItemInfoManager = new OustersSummonItemInfoManager ();
	g_pOustersSummonItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM] = g_pOustersSummonItemInfoManager;
	OustersSummonItem::initItemIDRegistry();

	g_pEffectItemInfoManager = new EffectItemInfoManager ();
	g_pEffectItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_EFFECT_ITEM] = g_pEffectItemInfoManager;
	EffectItem::initItemIDRegistry();

	g_pCodeSheetInfoManager = new CodeSheetInfoManager ();
	g_pCodeSheetInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_CODE_SHEET] = g_pCodeSheetInfoManager;
	CodeSheet::initItemIDRegistry();

	g_pMoonCardInfoManager = new MoonCardInfoManager ();
	g_pMoonCardInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MOON_CARD] = g_pMoonCardInfoManager;
	MoonCard::initItemIDRegistry();

	g_pSweeperInfoManager = new SweeperInfoManager ();
	g_pSweeperInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SWEEPER] = g_pSweeperInfoManager;
	Sweeper::initItemIDRegistry();

	g_pPetItemInfoManager = new PetItemInfoManager ();
	g_pPetItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_PET_ITEM] = g_pPetItemInfoManager;
	PetItem::initItemIDRegistry();

	g_pPetFoodInfoManager = new PetFoodInfoManager ();
	g_pPetFoodInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_PET_FOOD] = g_pPetFoodInfoManager;
	PetFood::initItemIDRegistry();

	g_pPetEnchantItemInfoManager = new PetEnchantItemInfoManager ();
	g_pPetEnchantItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_PET_ENCHANT_ITEM] = g_pPetEnchantItemInfoManager;
	PetEnchantItem::initItemIDRegistry();

	g_pLuckyBagInfoManager = new LuckyBagInfoManager ();
	g_pLuckyBagInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_LUCKY_BAG] = g_pLuckyBagInfoManager;
	LuckyBag::initItemIDRegistry();

	g_pSMSItemInfoManager = new SMSItemInfoManager ();
	g_pSMSItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SMS_ITEM] = g_pSMSItemInfoManager;
	SMSItem::initItemIDRegistry();

	g_pCoreZapInfoManager = new CoreZapInfoManager ();
	g_pCoreZapInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_CORE_ZAP] = g_pCoreZapInfoManager;
	CoreZap::initItemIDRegistry();

	g_pTrapItemInfoManager = new TrapItemInfoManager ();
	g_pTrapItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_TRAP_ITEM] = g_pTrapItemInfoManager;
	TrapItem::initItemIDRegistry();

	g_pWarItemInfoManager = new WarItemInfoManager ();
	g_pWarItemInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_WAR_ITEM] = g_pWarItemInfoManager;
	WarItem::initItemIDRegistry();

	g_pCarryingReceiverInfoManager = new CarryingReceiverInfoManager();
	g_pCarryingReceiverInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_CARRYING_RECEIVER] = g_pCarryingReceiverInfoManager;
	CarryingReceiver::initItemIDRegistry();

	g_pShoulderArmorInfoManager = new ShoulderArmorInfoManager();
	g_pShoulderArmorInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SHOULDER_ARMOR] = g_pShoulderArmorInfoManager;
	ShoulderArmor::initItemIDRegistry();

	g_pDermisInfoManager = new DermisInfoManager();
	g_pDermisInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_DERMIS] = g_pDermisInfoManager;
	Dermis::initItemIDRegistry();

	g_pPersonaInfoManager = new PersonaInfoManager();
	g_pPersonaInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_PERSONA] = g_pPersonaInfoManager;
	Persona::initItemIDRegistry();

	g_pFasciaInfoManager = new FasciaInfoManager();
	g_pFasciaInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_FASCIA] = g_pFasciaInfoManager;
	Fascia::initItemIDRegistry();

	g_pMittenInfoManager = new MittenInfoManager();
	g_pMittenInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_MITTEN] = g_pMittenInfoManager;
	Mitten::initItemIDRegistry();

	g_pSubInventoryInfoManager = new SubInventoryInfoManager();
	g_pSubInventoryInfoManager->init();
	m_InfoClassManagers[Item::ITEM_CLASS_SUB_INVENTORY] = g_pSubInventoryInfoManager;
	SubInventory::initItemIDRegistry();
    cout << "[GAMESERVER] ItemInfoManager Loaded." << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get sub info class manager
//////////////////////////////////////////////////////////////////////////////
InfoClassManager* ItemInfoManager::getInfoManager (Item::ItemClass Class) const
	throw(Error)
{
	__BEGIN_TRY

	Assert(Class < Item::ITEM_CLASS_MAX);
	Assert(m_InfoClassManagers[Class] != NULL);

	return m_InfoClassManagers[Class];

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get item info
//////////////////////////////////////////////////////////////////////////////
ItemInfo* ItemInfoManager::getItemInfo (Item::ItemClass Class, ItemType_t ItemType) const 
	throw(Error)
{
	__BEGIN_TRY

	Assert(Class < Item::ITEM_CLASS_MAX);
	Assert(m_InfoClassManagers[Class] != NULL);

	return m_InfoClassManagers[Class]->getItemInfo(ItemType);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get #item-info
//////////////////////////////////////////////////////////////////////////////
uint ItemInfoManager::getItemCount (Item::ItemClass Class) const 
	throw(Error)
{
	__BEGIN_TRY

	Assert(Class < Item::ITEM_CLASS_MAX);
	Assert(m_InfoClassManagers[Class] != NULL);

	return m_InfoClassManagers[Class]->getInfoCount();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get possible item type vector for specific item class
//////////////////////////////////////////////////////////////////////////////
vector<ItemType_t> ItemInfoManager::getPossibleItemTypes(Item::ItemClass IClass, uint minLevel, uint maxLevel) throw() {
	__BEGIN_TRY

	Assert(IClass < Item::ITEM_CLASS_MAX);
	Assert(m_InfoClassManagers[IClass] != NULL);

	vector<ItemType_t> result;
	uint               ItemCount = m_InfoClassManagers[IClass]->getInfoCount();

	for (ItemType_t i=0; i<ItemCount; i++) {
		ItemInfo* pItemInfo = m_InfoClassManagers[IClass]->getItemInfo(i);
		Assert(pItemInfo != NULL);

		uint itemLevel = pItemInfo->getItemLevel();

		// 현재 지정된 아이템의 레벨이 min 레벨보다 높고,
		// max 레벨보다 낮다면, 아이템 타입을 벡터에다 더한다.
		if (minLevel <= itemLevel && itemLevel <= maxLevel)
			result.push_back(i);
	}

	return result;

	__END_CATCH
}

bool ItemInfoManager::isPossibleItem(Item::ItemClass IClass, ItemType_t IType, const list<OptionType_t>& OType) 
	throw()
{
	__BEGIN_TRY

	Assert(IClass < Item::ITEM_CLASS_MAX);
	Assert(m_InfoClassManagers[IClass] != NULL);

	if (IType < m_InfoClassManagers[IClass]->getInfoCount())
	{
		if (!OType.empty())
		{
			try
			{
				//cout << "IM::getOptionInfo(" << (int)OType << ")" << endl;
				//cout << "IM::getOptionInfo(" << getOptionTypeToString(OType).c_str() << ")" << endl;
				list<OptionType_t>::const_iterator itr = OType.begin();
				for (; itr!=OType.end(); itr++) {
					OptionType_t optionType = *itr;

					if (g_pOptionInfoManager->getOptionInfo(optionType)==NULL)
						return false;
				}

				return true;
			}
			catch (NoSuchElementException& nsee)
			{
				cout << nsee.toString().c_str() << endl;
				return false;
			}
		}
		else
			return true;
	}
	
	return false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string ItemInfoManager::toString () const throw() {
	__BEGIN_TRY

	StringStream msg;
	msg << "ItemInfoManager(";

	for (uint i = 0; i < Item::ITEM_CLASS_MAX ; i ++)
	{
		if (m_InfoClassManagers[i] == NULL) msg << "NULL";
		else msg << m_InfoClassManagers[i]->toString();
	}

	msg << ")";
	return msg.toString();

	__END_CATCH
}

// global variable declaration
ItemInfoManager* g_pItemInfoManager = NULL;
