//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemLoaderManager.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ItemLoaderManager.h"

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Zone.h"

#include "AR.h"
#include "Belt.h"
#include "Blade.h"
#include "Bomb.h"
#include "BombMaterial.h"
#include "Bracelet.h"
#include "Coat.h"
#include "Cross.h"
#include "Mace.h"
#include "ETC.h"
#include "Glove.h"
#include "Helm.h"
#include "HolyWater.h"
#include "Key.h"
#include "LearningItem.h"
#include "Magazine.h"
#include "Mine.h"
#include "Money.h"
#include "Motorcycle.h"
#include "Necklace.h"
#include "Potion.h"
#include "Ring.h"
#include "SG.h"
#include "SMG.h"
#include "Shield.h"
#include "Shoes.h"
#include "Sword.h"
#include "SR.h"
#include "Trouser.h"
#include "VampireBracelet.h"
#include "VampireCoat.h"
#include "VampireNecklace.h"
#include "VampireRing.h"
#include "Water.h"
#include "Skull.h"
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


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ItemLoaderManager::ItemLoaderManager () 
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ItemLoaderManager::~ItemLoaderManager () 
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ItemLoaderManager::init () 
	throw(Error)
{
	__BEGIN_TRY

	m_pItemLoaders[Item::ITEM_CLASS_AR] = g_pARLoader = new ARLoader();
	m_pItemLoaders[Item::ITEM_CLASS_BELT] = g_pBeltLoader = new BeltLoader();
	m_pItemLoaders[Item::ITEM_CLASS_BLADE] = g_pBladeLoader = new BladeLoader();
	m_pItemLoaders[Item::ITEM_CLASS_BOMB] = g_pBombLoader = new BombLoader();
	m_pItemLoaders[Item::ITEM_CLASS_BOMB_MATERIAL] = g_pBombMaterialLoader = new BombMaterialLoader();
	m_pItemLoaders[Item::ITEM_CLASS_BRACELET] = g_pBraceletLoader = new BraceletLoader();
	m_pItemLoaders[Item::ITEM_CLASS_COAT] = g_pCoatLoader = new CoatLoader();
	m_pItemLoaders[Item::ITEM_CLASS_CROSS] = g_pCrossLoader = new CrossLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MACE] = g_pMaceLoader = new MaceLoader();
	m_pItemLoaders[Item::ITEM_CLASS_ETC] = g_pETCLoader = new ETCLoader();
	m_pItemLoaders[Item::ITEM_CLASS_GLOVE] = g_pGloveLoader = new GloveLoader();
	m_pItemLoaders[Item::ITEM_CLASS_HELM] = g_pHelmLoader = new HelmLoader();
	m_pItemLoaders[Item::ITEM_CLASS_HOLYWATER] = g_pHolyWaterLoader = new HolyWaterLoader();
	m_pItemLoaders[Item::ITEM_CLASS_KEY] = g_pKeyLoader = new KeyLoader();
	m_pItemLoaders[Item::ITEM_CLASS_LEARNINGITEM] = g_pLearningItemLoader = new LearningItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MAGAZINE] = g_pMagazineLoader = new MagazineLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MINE] = g_pMineLoader = new MineLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MONEY] = g_pMoneyLoader = new MoneyLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MOTORCYCLE] = g_pMotorcycleLoader = new MotorcycleLoader();
	m_pItemLoaders[Item::ITEM_CLASS_NECKLACE] = g_pNecklaceLoader = new NecklaceLoader();
	m_pItemLoaders[Item::ITEM_CLASS_POTION] = g_pPotionLoader = new PotionLoader();
	m_pItemLoaders[Item::ITEM_CLASS_RING] = g_pRingLoader = new RingLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SG] = g_pSGLoader = new SGLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SMG] = g_pSMGLoader = new SMGLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SHIELD] = g_pShieldLoader = new ShieldLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SHOES] = g_pShoesLoader = new ShoesLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SWORD] = g_pSwordLoader = new SwordLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SR] = g_pSRLoader = new SRLoader();
	m_pItemLoaders[Item::ITEM_CLASS_TROUSER] = g_pTrouserLoader = new TrouserLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_BRACELET] = g_pVampireBraceletLoader = new VampireBraceletLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_COAT] = g_pVampireCoatLoader = new VampireCoatLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_NECKLACE] = g_pVampireNecklaceLoader = new VampireNecklaceLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_RING] = g_pVampireRingLoader = new VampireRingLoader();
	m_pItemLoaders[Item::ITEM_CLASS_WATER] = g_pWaterLoader = new WaterLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SKULL] = g_pSkullLoader = new SkullLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SERUM] = g_pSerumLoader = new SerumLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_ETC] = g_pVampireETCLoader = new VampireETCLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SLAYER_PORTAL_ITEM] = g_pSlayerPortalItemLoader = new SlayerPortalItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM] = g_pVampirePortalItemLoader = new VampirePortalItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_EVENT_GIFT_BOX] = g_pEventGiftBoxLoader = new EventGiftBoxLoader();
	m_pItemLoaders[Item::ITEM_CLASS_EVENT_STAR] = g_pEventStarLoader = new EventStarLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_EARRING] = g_pVampireEarringLoader = new VampireEarringLoader();
	m_pItemLoaders[Item::ITEM_CLASS_RELIC] = g_pRelicLoader = new RelicLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_WEAPON] = g_pVampireWeaponLoader = new VampireWeaponLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_AMULET] = g_pVampireAmuletLoader = new VampireAmuletLoader();
	m_pItemLoaders[Item::ITEM_CLASS_QUEST_ITEM] = g_pQuestItemLoader = new QuestItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_EVENT_TREE] = g_pEventTreeLoader = new EventTreeLoader();
	m_pItemLoaders[Item::ITEM_CLASS_EVENT_ETC] = g_pEventETCLoader = new EventETCLoader();
	m_pItemLoaders[Item::ITEM_CLASS_BLOOD_BIBLE] = g_pBloodBibleLoader = new BloodBibleLoader();
	m_pItemLoaders[Item::ITEM_CLASS_CASTLE_SYMBOL] = g_pCastleSymbolLoader = new CastleSymbolLoader();
	m_pItemLoaders[Item::ITEM_CLASS_COUPLE_RING] = g_pCoupleRingLoader = new CoupleRingLoader();
	m_pItemLoaders[Item::ITEM_CLASS_VAMPIRE_COUPLE_RING] = g_pVampireCoupleRingLoader = new VampireCoupleRingLoader();
	m_pItemLoaders[Item::ITEM_CLASS_EVENT_ITEM] = g_pEventItemLoader = new EventItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_DYE_POTION] = g_pDyePotionLoader = new DyePotionLoader();
	m_pItemLoaders[Item::ITEM_CLASS_RESURRECT_ITEM] = g_pResurrectItemLoader = new ResurrectItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MIXING_ITEM] = g_pMixingItemLoader = new MixingItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_ARMSBAND] = g_pOustersArmsbandLoader = new OustersArmsbandLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_BOOTS] = g_pOustersBootsLoader = new OustersBootsLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_CHAKRAM] = g_pOustersChakramLoader = new OustersChakramLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_CIRCLET] = g_pOustersCircletLoader = new OustersCircletLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_COAT] = g_pOustersCoatLoader = new OustersCoatLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_PENDENT] = g_pOustersPendentLoader = new OustersPendentLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_RING] = g_pOustersRingLoader = new OustersRingLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_STONE] = g_pOustersStoneLoader = new OustersStoneLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_WRISTLET] = g_pOustersWristletLoader = new OustersWristletLoader();
	m_pItemLoaders[Item::ITEM_CLASS_LARVA] = g_pLarvaLoader = new LarvaLoader();
	m_pItemLoaders[Item::ITEM_CLASS_PUPA] = g_pPupaLoader = new PupaLoader();
	m_pItemLoaders[Item::ITEM_CLASS_COMPOS_MEI] = g_pComposMeiLoader = new ComposMeiLoader();
	m_pItemLoaders[Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM] = g_pOustersSummonItemLoader = new OustersSummonItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_EFFECT_ITEM] = g_pEffectItemLoader = new EffectItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_CODE_SHEET] = g_pCodeSheetLoader = new CodeSheetLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MOON_CARD] = g_pMoonCardLoader = new MoonCardLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SWEEPER] = g_pSweeperLoader = new SweeperLoader();
	m_pItemLoaders[Item::ITEM_CLASS_PET_ITEM] = g_pPetItemLoader = new PetItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_PET_FOOD] = g_pPetFoodLoader = new PetFoodLoader();
	m_pItemLoaders[Item::ITEM_CLASS_PET_ENCHANT_ITEM] = g_pPetEnchantItemLoader = new PetEnchantItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_LUCKY_BAG] = g_pLuckyBagLoader = new LuckyBagLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SMS_ITEM] = g_pSMSItemLoader = new SMSItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_CORE_ZAP] = g_pCoreZapLoader = new CoreZapLoader();
	m_pItemLoaders[Item::ITEM_CLASS_TRAP_ITEM] = g_pTrapItemLoader = new TrapItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_WAR_ITEM] = g_pWarItemLoader = new WarItemLoader();
	m_pItemLoaders[Item::ITEM_CLASS_CARRYING_RECEIVER] = g_pCarryingReceiverLoader = new CarryingReceiverLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SHOULDER_ARMOR] = g_pShoulderArmorLoader = new ShoulderArmorLoader();
	m_pItemLoaders[Item::ITEM_CLASS_DERMIS] = g_pDermisLoader = new DermisLoader();
	m_pItemLoaders[Item::ITEM_CLASS_PERSONA] = g_pPersonaLoader = new PersonaLoader();
	m_pItemLoaders[Item::ITEM_CLASS_FASCIA] = g_pFasciaLoader = new FasciaLoader();
	m_pItemLoaders[Item::ITEM_CLASS_MITTEN] = g_pMittenLoader = new MittenLoader();
	m_pItemLoaders[Item::ITEM_CLASS_SUB_INVENTORY] = g_pSubInventoryLoader = new SubInventoryLoader();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ItemLoaderManager::load (Slayer* pSlayer) 
	throw(Error)
{
	__BEGIN_TRY

	// 모터사이클을 가장 먼저 로딩해야 한다.
	g_pMotorcycleLoader->load(pSlayer);
	g_pSubInventoryLoader->load(pSlayer);

	// 그다음이 벨트이다.
	g_pBeltLoader->load(pSlayer);
	g_pMagazineLoader->load(pSlayer);
	g_pPotionLoader->load(pSlayer);

	g_pARLoader->load(pSlayer);
	g_pBladeLoader->load(pSlayer);
	g_pBombLoader->load(pSlayer);
	g_pBombMaterialLoader->load(pSlayer);
	g_pBraceletLoader->load(pSlayer);
	g_pCoatLoader->load(pSlayer);
	g_pCrossLoader->load(pSlayer);
	g_pMaceLoader->load(pSlayer);
	g_pETCLoader->load(pSlayer);
	g_pGloveLoader->load(pSlayer);
	g_pHelmLoader->load(pSlayer);
	g_pHolyWaterLoader->load(pSlayer);
	g_pKeyLoader->load(pSlayer);
	g_pLearningItemLoader->load(pSlayer);
	g_pMineLoader->load(pSlayer);
	g_pMoneyLoader->load(pSlayer);
	g_pNecklaceLoader->load(pSlayer);
	g_pRingLoader->load(pSlayer);
	g_pSGLoader->load(pSlayer);
	g_pSMGLoader->load(pSlayer);
	g_pShieldLoader->load(pSlayer);
	g_pShoesLoader->load(pSlayer);
	g_pSwordLoader->load(pSlayer);
	g_pSRLoader->load(pSlayer);
	g_pTrouserLoader->load(pSlayer);
	g_pVampireBraceletLoader->load(pSlayer);
	g_pVampireCoatLoader->load(pSlayer);
	g_pVampireNecklaceLoader->load(pSlayer);
	g_pVampireRingLoader->load(pSlayer);
	g_pWaterLoader->load(pSlayer);
	g_pSkullLoader->load(pSlayer);
	g_pSerumLoader->load(pSlayer);
	g_pVampireETCLoader->load(pSlayer);
	g_pSlayerPortalItemLoader->load(pSlayer);
	g_pVampirePortalItemLoader->load(pSlayer);
	g_pEventGiftBoxLoader->load(pSlayer);
	g_pEventStarLoader->load(pSlayer);
	g_pVampireEarringLoader->load(pSlayer);
	g_pRelicLoader->load(pSlayer);
	g_pVampireWeaponLoader->load(pSlayer);
	g_pVampireAmuletLoader->load(pSlayer);
	g_pQuestItemLoader->load(pSlayer);
	g_pEventTreeLoader->load(pSlayer);
	g_pEventETCLoader->load(pSlayer);
	g_pBloodBibleLoader->load(pSlayer);
	g_pCastleSymbolLoader->load(pSlayer);
	g_pCoupleRingLoader->load(pSlayer);
	g_pEventItemLoader->load(pSlayer);
	g_pDyePotionLoader->load(pSlayer);
	g_pResurrectItemLoader->load(pSlayer);
	g_pMixingItemLoader->load(pSlayer);
	g_pEffectItemLoader->load(pSlayer);
	g_pCodeSheetLoader->load(pSlayer);
	g_pMoonCardLoader->load(pSlayer);
	g_pSweeperLoader->load(pSlayer);
	g_pPetItemLoader->load(pSlayer);
	g_pPetFoodLoader->load(pSlayer);
	g_pPetEnchantItemLoader->load(pSlayer);
	g_pLuckyBagLoader->load(pSlayer);
	g_pSMSItemLoader->load(pSlayer);
	g_pCoreZapLoader->load(pSlayer);
	g_pTrapItemLoader->load(pSlayer);
	g_pWarItemLoader->load(pSlayer);
	g_pCarryingReceiverLoader->load(pSlayer);
	g_pShoulderArmorLoader->load(pSlayer);
	g_pDermisLoader->load(pSlayer);
	g_pPersonaLoader->load(pSlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ItemLoaderManager::load (Vampire* pVampire) 
	throw(Error)
{
	__BEGIN_TRY

	// 뱀파이어는 모터사이클이 없으므로, 모터사이클을 로딩할 필요가 없다.
	// 그러나, 벨트는 로딩할 필요가 있다.
	g_pSubInventoryLoader->load(pVampire);
	g_pBeltLoader->load(pVampire);

	g_pARLoader->load(pVampire);
	g_pBladeLoader->load(pVampire);
	g_pBombLoader->load(pVampire);
	g_pBombMaterialLoader->load(pVampire);
	g_pBraceletLoader->load(pVampire);
	g_pCoatLoader->load(pVampire);
	g_pCrossLoader->load(pVampire);
	g_pMaceLoader->load(pVampire);
	g_pETCLoader->load(pVampire);
	g_pGloveLoader->load(pVampire);
	g_pHelmLoader->load(pVampire);
	g_pHolyWaterLoader->load(pVampire);
	g_pKeyLoader->load(pVampire);
	g_pLearningItemLoader->load(pVampire);
	g_pMagazineLoader->load(pVampire);
	g_pMineLoader->load(pVampire);
	g_pMoneyLoader->load(pVampire);
	g_pNecklaceLoader->load(pVampire);
	g_pPotionLoader->load(pVampire);
	g_pRingLoader->load(pVampire);
	g_pSGLoader->load(pVampire);
	g_pSMGLoader->load(pVampire);
	g_pShieldLoader->load(pVampire);
	g_pShoesLoader->load(pVampire);
	g_pSwordLoader->load(pVampire);
	g_pSRLoader->load(pVampire);
	g_pTrouserLoader->load(pVampire);
	g_pVampireBraceletLoader->load(pVampire);
	g_pVampireCoatLoader->load(pVampire);
	g_pVampireNecklaceLoader->load(pVampire);
	g_pVampireRingLoader->load(pVampire);
	g_pWaterLoader->load(pVampire);
	g_pSkullLoader->load(pVampire);
	g_pSerumLoader->load(pVampire);
	g_pVampireETCLoader->load(pVampire);
	g_pSlayerPortalItemLoader->load(pVampire);
	g_pVampirePortalItemLoader->load(pVampire);
	g_pEventGiftBoxLoader->load(pVampire);
	g_pEventStarLoader->load(pVampire);
	g_pVampireEarringLoader->load(pVampire);
	g_pRelicLoader->load(pVampire);
	g_pVampireWeaponLoader->load(pVampire);
	g_pVampireAmuletLoader->load(pVampire);
	g_pQuestItemLoader->load(pVampire);
	g_pEventTreeLoader->load(pVampire);
	g_pEventETCLoader->load(pVampire);
	g_pBloodBibleLoader->load(pVampire);
	g_pCastleSymbolLoader->load(pVampire);
	g_pVampireCoupleRingLoader->load(pVampire);
	g_pEventItemLoader->load(pVampire);
	g_pDyePotionLoader->load(pVampire);
	g_pResurrectItemLoader->load(pVampire);
	g_pMixingItemLoader->load(pVampire);
	g_pEffectItemLoader->load(pVampire);
	g_pCodeSheetLoader->load(pVampire);
	g_pMoonCardLoader->load(pVampire);
	g_pSweeperLoader->load(pVampire);
	g_pPetItemLoader->load(pVampire);
	g_pPetFoodLoader->load(pVampire);
	g_pPetEnchantItemLoader->load(pVampire);
	g_pLuckyBagLoader->load(pVampire);
	g_pSMSItemLoader->load(pVampire);
	g_pCoreZapLoader->load(pVampire);
	g_pTrapItemLoader->load(pVampire);
	g_pWarItemLoader->load(pVampire);
	g_pCarryingReceiverLoader->load(pVampire);
	g_pShoulderArmorLoader->load(pVampire);
	g_pDermisLoader->load(pVampire);
	g_pPersonaLoader->load(pVampire);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ItemLoaderManager::load (Ousters* pOusters) 
	throw(Error)
{
	__BEGIN_TRY

	// 암스밴드는 벨트다.
	// 제일먼저 로딩해야 푸파나 콤포스메이가 들어갈 수 있다.
	g_pSubInventoryLoader->load(pOusters);
	g_pOustersArmsbandLoader->load(pOusters);
	g_pOustersBootsLoader->load(pOusters);
	g_pOustersChakramLoader->load(pOusters);
	g_pOustersCircletLoader->load(pOusters);
	g_pOustersCoatLoader->load(pOusters);
	g_pOustersPendentLoader->load(pOusters);
	g_pOustersRingLoader->load(pOusters);
	g_pOustersStoneLoader->load(pOusters);
	g_pOustersWristletLoader->load(pOusters);
	g_pLarvaLoader->load(pOusters);
	g_pPupaLoader->load(pOusters);
	g_pComposMeiLoader->load(pOusters);
	g_pOustersSummonItemLoader->load(pOusters);
	g_pSkullLoader->load(pOusters);
	g_pQuestItemLoader->load(pOusters);
	g_pEventGiftBoxLoader->load(pOusters);
	g_pEventStarLoader->load(pOusters);
	g_pEventTreeLoader->load(pOusters);
	g_pEventETCLoader->load(pOusters);
	g_pEventItemLoader->load(pOusters);
	g_pDyePotionLoader->load(pOusters);
	g_pResurrectItemLoader->load(pOusters);
	g_pMixingItemLoader->load(pOusters);
	g_pEffectItemLoader->load(pOusters);
	g_pCodeSheetLoader->load(pOusters);
	g_pMoonCardLoader->load(pOusters);
	g_pSweeperLoader->load(pOusters);
	g_pPetItemLoader->load(pOusters);
	g_pPetFoodLoader->load(pOusters);
	g_pPetEnchantItemLoader->load(pOusters);
	g_pLuckyBagLoader->load(pOusters);
	g_pSMSItemLoader->load(pOusters);
	g_pCoreZapLoader->load(pOusters);
	g_pTrapItemLoader->load(pOusters);
	g_pWarItemLoader->load(pOusters);
	g_pFasciaLoader->load(pOusters);
	g_pMittenLoader->load(pOusters);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ItemLoaderManager::load (Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string ItemLoaderManager::toString () const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ItemLoaderManager(";

	for (uint i = 0 ; i < Item::ITEM_CLASS_MAX ; i ++)
	{
		if (m_pItemLoaders[i] == NULL)
		{
			msg << "NULL";
		}
		else
		{
			msg << m_pItemLoaders[i]->getItemClassName();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

ItemLoaderManager* g_pItemLoaderManager = NULL;
