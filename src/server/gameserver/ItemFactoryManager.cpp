//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemFactoryManager.cpp 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Item.h"
#include "ItemUtil.h"
#include "Assert1.h"
#include "ItemFactoryManager.h"
#include "ItemInfoManager.h"
#include "StringStream.h"
#include <string.h>

#include "Motorcycle.h"
#include "Potion.h"
#include "Water.h"
#include "HolyWater.h"
#include "Magazine.h"
#include "BombMaterial.h"
#include "ETC.h"
#include "Key.h"
#include "Ring.h"
#include "Bracelet.h"
#include "Necklace.h"
#include "Coat.h"
#include "Trouser.h"
#include "Shoes.h"
#include "Sword.h"
#include "Blade.h"
#include "Shield.h"
#include "Cross.h"
#include "Mace.h"
#include "Glove.h"
#include "Helm.h"
#include "SG.h"
#include "SMG.h"
#include "AR.h"
#include "SR.h"
#include "Bomb.h"
#include "Mine.h"
#include "Belt.h"
#include "LearningItem.h"
#include "Money.h"
#include "Corpse.h"
#include "VampireRing.h"
#include "VampireBracelet.h"
#include "VampireNecklace.h"
#include "VampireCoat.h"
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

#include <map>

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
ItemFactoryManager::ItemFactoryManager () 
	throw()
: m_Factories(NULL) , m_Size(Item::ITEM_CLASS_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// 아이템팩토리배열을 생성한다.
	m_Factories = new ItemFactory*[ m_Size ];
	
	// 팩토리에 대한 포인터들을 NULL 로 초기화한다.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
ItemFactoryManager::~ItemFactoryManager () 
	throw()
{
	__BEGIN_TRY
		
	Assert(m_Factories != NULL);

	// 각각의 아이템팩토리들을 삭제한다.
	for (int i = 0 ; i < m_Size ; i ++) 
		SAFE_DELETE(m_Factories[i]);
	
	// 아이템팩토리배열을 삭제한다.
	SAFE_DELETE_ARRAY(m_Factories);
			
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 정의된 모든 아이템팩토리들을 여기에 추가한다.
//
//////////////////////////////////////////////////////////////////////
void ItemFactoryManager::init ()
	 throw(Error)
{
	__BEGIN_TRY
		
	m_Factories[Item::ITEM_CLASS_MOTORCYCLE] = new MotorcycleFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MOTORCYCLE]->getItemClassName()] = Item::ITEM_CLASS_MOTORCYCLE;

	m_Factories[Item::ITEM_CLASS_POTION] = new PotionFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_POTION]->getItemClassName()] = Item::ITEM_CLASS_POTION;

	m_Factories[Item::ITEM_CLASS_WATER] = new WaterFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_WATER]->getItemClassName()] = Item::ITEM_CLASS_WATER;

	m_Factories[Item::ITEM_CLASS_HOLYWATER] = new HolyWaterFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_HOLYWATER]->getItemClassName()] = Item::ITEM_CLASS_HOLYWATER;

	m_Factories[Item::ITEM_CLASS_MAGAZINE] = new MagazineFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MAGAZINE]->getItemClassName()] = Item::ITEM_CLASS_MAGAZINE;

	m_Factories[Item::ITEM_CLASS_BOMB_MATERIAL] = new BombMaterialFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_BOMB_MATERIAL]->getItemClassName()] = Item::ITEM_CLASS_BOMB_MATERIAL;

	m_Factories[Item::ITEM_CLASS_ETC] = new ETCFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_ETC]->getItemClassName()] = Item::ITEM_CLASS_ETC;

	m_Factories[Item::ITEM_CLASS_KEY] = new KeyFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_KEY]->getItemClassName()] = Item::ITEM_CLASS_KEY;

	m_Factories[Item::ITEM_CLASS_RING] = new RingFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_RING]->getItemClassName()] = Item::ITEM_CLASS_RING;

	m_Factories[Item::ITEM_CLASS_BRACELET] = new BraceletFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_BRACELET]->getItemClassName()] = Item::ITEM_CLASS_BRACELET;

	m_Factories[Item::ITEM_CLASS_NECKLACE] = new NecklaceFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_NECKLACE]->getItemClassName()] = Item::ITEM_CLASS_NECKLACE;

	m_Factories[Item::ITEM_CLASS_COAT] = new CoatFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_COAT]->getItemClassName()] = Item::ITEM_CLASS_COAT;

	m_Factories[Item::ITEM_CLASS_TROUSER] = new TrouserFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_TROUSER]->getItemClassName()] = Item::ITEM_CLASS_TROUSER;

	m_Factories[Item::ITEM_CLASS_SHOES] = new ShoesFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SHOES]->getItemClassName()] = Item::ITEM_CLASS_SHOES;

	m_Factories[Item::ITEM_CLASS_SWORD] = new SwordFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SWORD]->getItemClassName()] = Item::ITEM_CLASS_SWORD;

	m_Factories[Item::ITEM_CLASS_BLADE] = new BladeFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_BLADE]->getItemClassName()] = Item::ITEM_CLASS_BLADE;

	m_Factories[Item::ITEM_CLASS_SHIELD] = new ShieldFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SHIELD]->getItemClassName()] = Item::ITEM_CLASS_SHIELD;

	m_Factories[Item::ITEM_CLASS_CROSS] = new CrossFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_CROSS]->getItemClassName()] = Item::ITEM_CLASS_CROSS;

	m_Factories[Item::ITEM_CLASS_GLOVE] = new GloveFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_GLOVE]->getItemClassName()] = Item::ITEM_CLASS_GLOVE;

	m_Factories[Item::ITEM_CLASS_HELM] = new HelmFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_HELM]->getItemClassName()] = Item::ITEM_CLASS_HELM;

	m_Factories[Item::ITEM_CLASS_SG] = new SGFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SG]->getItemClassName()] = Item::ITEM_CLASS_SG;

	m_Factories[Item::ITEM_CLASS_SMG] = new SMGFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SMG]->getItemClassName()] = Item::ITEM_CLASS_SMG;

	m_Factories[Item::ITEM_CLASS_AR] = new ARFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_AR]->getItemClassName()] = Item::ITEM_CLASS_AR;

	m_Factories[Item::ITEM_CLASS_SR] = new SRFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SR]->getItemClassName()] = Item::ITEM_CLASS_SR;

	m_Factories[Item::ITEM_CLASS_BOMB] = new BombFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_BOMB]->getItemClassName()] = Item::ITEM_CLASS_BOMB;

	m_Factories[Item::ITEM_CLASS_MINE] = new MineFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MINE]->getItemClassName()] = Item::ITEM_CLASS_MINE;

	m_Factories[Item::ITEM_CLASS_BELT] = new BeltFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_BELT]->getItemClassName()] = Item::ITEM_CLASS_BELT;

	m_Factories[Item::ITEM_CLASS_LEARNINGITEM] = new LearningItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_LEARNINGITEM]->getItemClassName()] = Item::ITEM_CLASS_LEARNINGITEM;

	m_Factories[Item::ITEM_CLASS_MONEY] = new MoneyFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MONEY]->getItemClassName()] = Item::ITEM_CLASS_MONEY;

	m_Factories[Item::ITEM_CLASS_CORPSE] = NULL;
	//m_ItemClassMap[m_Factories[Item::ITEM_CLASS_CORPSE]->getItemClassName()] = Item::ITEM_CLASS_CORPSE;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_RING] = new VampireRingFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_RING]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_RING;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_BRACELET] = new VampireBraceletFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_BRACELET]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_BRACELET;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_NECKLACE] = new VampireNecklaceFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_NECKLACE]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_NECKLACE;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_COAT] = new VampireCoatFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_COAT]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_COAT;

	m_Factories[Item::ITEM_CLASS_SKULL] = new SkullFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SKULL]->getItemClassName()] = Item::ITEM_CLASS_SKULL;

	m_Factories[Item::ITEM_CLASS_MACE] = new MaceFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MACE]->getItemClassName()] = Item::ITEM_CLASS_MACE;

	m_Factories[Item::ITEM_CLASS_SERUM] = new SerumFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SERUM]->getItemClassName()] = Item::ITEM_CLASS_SERUM;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_ETC] = new VampireETCFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_ETC]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_ETC;

	m_Factories[Item::ITEM_CLASS_SLAYER_PORTAL_ITEM] = new SlayerPortalItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SLAYER_PORTAL_ITEM]->getItemClassName()] = Item::ITEM_CLASS_SLAYER_PORTAL_ITEM;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM] = new VampirePortalItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM;

	m_Factories[Item::ITEM_CLASS_EVENT_GIFT_BOX] = new EventGiftBoxFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_EVENT_GIFT_BOX]->getItemClassName()] = Item::ITEM_CLASS_EVENT_GIFT_BOX;

	m_Factories[Item::ITEM_CLASS_EVENT_STAR] = new EventStarFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_EVENT_STAR]->getItemClassName()] = Item::ITEM_CLASS_EVENT_STAR;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_EARRING] = new VampireEarringFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_EARRING]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_EARRING;

	m_Factories[Item::ITEM_CLASS_RELIC] = new RelicFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_RELIC]->getItemClassName()] = Item::ITEM_CLASS_RELIC;
	
	m_Factories[Item::ITEM_CLASS_VAMPIRE_WEAPON] = new VampireWeaponFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_WEAPON]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_WEAPON;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_AMULET] = new VampireAmuletFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_AMULET]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_AMULET;

	m_Factories[Item::ITEM_CLASS_QUEST_ITEM] = new QuestItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_QUEST_ITEM]->getItemClassName()] = Item::ITEM_CLASS_QUEST_ITEM;

	m_Factories[Item::ITEM_CLASS_EVENT_TREE] = new EventTreeFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_EVENT_TREE]->getItemClassName()] = Item::ITEM_CLASS_EVENT_TREE;

	m_Factories[Item::ITEM_CLASS_EVENT_ETC] = new EventETCFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_EVENT_ETC]->getItemClassName()] = Item::ITEM_CLASS_EVENT_ETC;

	m_Factories[Item::ITEM_CLASS_BLOOD_BIBLE] = new BloodBibleFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_BLOOD_BIBLE]->getItemClassName()] = Item::ITEM_CLASS_BLOOD_BIBLE;

	m_Factories[Item::ITEM_CLASS_CASTLE_SYMBOL] = new CastleSymbolFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_CASTLE_SYMBOL]->getItemClassName()] = Item::ITEM_CLASS_CASTLE_SYMBOL;

	m_Factories[Item::ITEM_CLASS_COUPLE_RING] = new CoupleRingFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_COUPLE_RING]->getItemClassName()] = Item::ITEM_CLASS_COUPLE_RING;

	m_Factories[Item::ITEM_CLASS_VAMPIRE_COUPLE_RING] = new VampireCoupleRingFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_VAMPIRE_COUPLE_RING]->getItemClassName()] = Item::ITEM_CLASS_VAMPIRE_COUPLE_RING;

	m_Factories[Item::ITEM_CLASS_EVENT_ITEM] = new EventItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_EVENT_ITEM]->getItemClassName()] = Item::ITEM_CLASS_EVENT_ITEM;

	m_Factories[Item::ITEM_CLASS_DYE_POTION] = new DyePotionFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_DYE_POTION]->getItemClassName()] = Item::ITEM_CLASS_DYE_POTION;

	m_Factories[Item::ITEM_CLASS_RESURRECT_ITEM] = new ResurrectItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_RESURRECT_ITEM]->getItemClassName()] = Item::ITEM_CLASS_RESURRECT_ITEM;

	m_Factories[Item::ITEM_CLASS_MIXING_ITEM] = new MixingItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MIXING_ITEM]->getItemClassName()] = Item::ITEM_CLASS_MIXING_ITEM;

	m_Factories[Item::ITEM_CLASS_OUSTERS_ARMSBAND] = new OustersArmsbandFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_ARMSBAND]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_ARMSBAND;

	m_Factories[Item::ITEM_CLASS_OUSTERS_BOOTS] = new OustersBootsFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_BOOTS]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_BOOTS;

	m_Factories[Item::ITEM_CLASS_OUSTERS_CHAKRAM] = new OustersChakramFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_CHAKRAM]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_CHAKRAM;

	m_Factories[Item::ITEM_CLASS_OUSTERS_CIRCLET] = new OustersCircletFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_CIRCLET]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_CIRCLET;

	m_Factories[Item::ITEM_CLASS_OUSTERS_COAT] = new OustersCoatFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_COAT]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_COAT;

	m_Factories[Item::ITEM_CLASS_OUSTERS_PENDENT] = new OustersPendentFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_PENDENT]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_PENDENT;

	m_Factories[Item::ITEM_CLASS_OUSTERS_RING] = new OustersRingFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_RING]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_RING;

	m_Factories[Item::ITEM_CLASS_OUSTERS_STONE] = new OustersStoneFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_STONE]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_STONE;

	m_Factories[Item::ITEM_CLASS_OUSTERS_WRISTLET] = new OustersWristletFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_WRISTLET]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_WRISTLET;

	m_Factories[Item::ITEM_CLASS_LARVA] = new LarvaFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_LARVA]->getItemClassName()] = Item::ITEM_CLASS_LARVA;

	m_Factories[Item::ITEM_CLASS_PUPA] = new PupaFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_PUPA]->getItemClassName()] = Item::ITEM_CLASS_PUPA;

	m_Factories[Item::ITEM_CLASS_COMPOS_MEI] = new ComposMeiFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_COMPOS_MEI]->getItemClassName()] = Item::ITEM_CLASS_COMPOS_MEI;

	m_Factories[Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM] = new OustersSummonItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM]->getItemClassName()] = Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM;

	m_Factories[Item::ITEM_CLASS_EFFECT_ITEM] = new EffectItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_EFFECT_ITEM]->getItemClassName()] = Item::ITEM_CLASS_EFFECT_ITEM;

	m_Factories[Item::ITEM_CLASS_CODE_SHEET] = new CodeSheetFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_CODE_SHEET]->getItemClassName()] = Item::ITEM_CLASS_CODE_SHEET;

	m_Factories[Item::ITEM_CLASS_MOON_CARD] = new MoonCardFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MOON_CARD]->getItemClassName()] = Item::ITEM_CLASS_MOON_CARD;

	m_Factories[Item::ITEM_CLASS_SWEEPER] = new SweeperFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SWEEPER]->getItemClassName()] = Item::ITEM_CLASS_SWEEPER;

	m_Factories[Item::ITEM_CLASS_PET_ITEM] = new PetItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_PET_ITEM]->getItemClassName()] = Item::ITEM_CLASS_PET_ITEM;

	m_Factories[Item::ITEM_CLASS_PET_FOOD] = new PetFoodFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_PET_FOOD]->getItemClassName()] = Item::ITEM_CLASS_PET_FOOD;

	m_Factories[Item::ITEM_CLASS_PET_ENCHANT_ITEM] = new PetEnchantItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_PET_ENCHANT_ITEM]->getItemClassName()] = Item::ITEM_CLASS_PET_ENCHANT_ITEM;

	m_Factories[Item::ITEM_CLASS_LUCKY_BAG] = new LuckyBagFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_LUCKY_BAG]->getItemClassName()] = Item::ITEM_CLASS_LUCKY_BAG;

	m_Factories[Item::ITEM_CLASS_SMS_ITEM] = new SMSItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SMS_ITEM]->getItemClassName()] = Item::ITEM_CLASS_SMS_ITEM;

	m_Factories[Item::ITEM_CLASS_CORE_ZAP] = new CoreZapFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_CORE_ZAP]->getItemClassName()] = Item::ITEM_CLASS_CORE_ZAP;

	m_Factories[Item::ITEM_CLASS_TRAP_ITEM] = new TrapItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_TRAP_ITEM]->getItemClassName()] = Item::ITEM_CLASS_TRAP_ITEM;

	m_Factories[Item::ITEM_CLASS_WAR_ITEM] = new WarItemFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_WAR_ITEM]->getItemClassName()] = Item::ITEM_CLASS_WAR_ITEM;

	m_Factories[Item::ITEM_CLASS_CARRYING_RECEIVER] = new CarryingReceiverFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_CARRYING_RECEIVER]->getItemClassName()] = Item::ITEM_CLASS_CARRYING_RECEIVER;

	m_Factories[Item::ITEM_CLASS_SHOULDER_ARMOR] = new ShoulderArmorFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SHOULDER_ARMOR]->getItemClassName()] = Item::ITEM_CLASS_SHOULDER_ARMOR;

	m_Factories[Item::ITEM_CLASS_DERMIS] = new DermisFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_DERMIS]->getItemClassName()] = Item::ITEM_CLASS_DERMIS;

	m_Factories[Item::ITEM_CLASS_PERSONA] = new PersonaFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_PERSONA]->getItemClassName()] = Item::ITEM_CLASS_PERSONA;

	m_Factories[Item::ITEM_CLASS_FASCIA] = new FasciaFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_FASCIA]->getItemClassName()] = Item::ITEM_CLASS_FASCIA;

	m_Factories[Item::ITEM_CLASS_MITTEN] = new MittenFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_MITTEN]->getItemClassName()] = Item::ITEM_CLASS_MITTEN;

	m_Factories[Item::ITEM_CLASS_SUB_INVENTORY] = new SubInventoryFactory();
	m_ItemClassMap[m_Factories[Item::ITEM_CLASS_SUB_INVENTORY]->getItemClassName()] = Item::ITEM_CLASS_SUB_INVENTORY;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 아이템 클래스로 하위 팩토리 매니져에 있는 createItem을 실행한다.
//
//////////////////////////////////////////////////////////////////////
Item* ItemFactoryManager::createItem (Item::ItemClass IClass, ItemType_t ItemType, const list<OptionType_t>& OptionType) 
	   throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	try 
	{
		// 아이템 아이디가 범위를 넘어섬으로 인해서 Seg.Fault 가 발생하지 않도록.
		// 이런 사용자는 당장 짤라야 한다.
		if (IClass >= m_Size || m_Factories[IClass] == NULL) 
		{
			StringStream msg;
			msg << "item factory [" << (int)IClass << "] not exist.";
			cerr << "ItemFactoryManager::createItem() : NoSuchElementException" << endl;
			filelog("itembug.log", "ItemFactoryManager::createItem() : Invalid Item Class : %d", IClass);
			throw NoSuchElementException(msg.toString());
		}
	} 
	catch (Throwable & t) 
	{
		cerr << t.toString() << endl;
	}


	Item* pItem = m_Factories[IClass]->createItem(ItemType, OptionType);
	
	pItem->setTraceItem(bTraceLog(pItem ));
	pItem->setUnique(g_pItemInfoManager->getItemInfo(IClass, ItemType )->isUnique());
	
	return pItem;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 아이템아이디로 특정 아이템의 이름을 리턴한다.
//
//////////////////////////////////////////////////////////////////////
string ItemFactoryManager::getItemName (Item::ItemClass IClass) 
	   throw()
{
	__BEGIN_TRY

	// 아이템 아이디가 범위를 넘어섬으로 인해서 Seg.Fault 가 발생하지 않도록.
	// 이런 사용자는 당장 짤라야 한다.
	if (IClass >= m_Size || m_Factories[IClass] == NULL) {
		StringStream msg;
		msg << "invaltype item type(" << (int)IClass << ")";
	}

	return m_Factories[IClass]->getItemClassName();
			
	__END_CATCH
}

Item::ItemClass ItemFactoryManager::getItemClassByName(const string & ClassName )
	throw()
{
	__BEGIN_TRY

	map<string, Item::ItemClass>::const_iterator itr = m_ItemClassMap.begin();
	for (; itr != m_ItemClassMap.end(); itr++)
	{
		// 대,소문자를 무시하고, 비교를 수행한다.
		if (strcasecmp(ClassName.c_str(), (itr->first).c_str()) == 0)
		{
			return itr->second;
		}
	}

	return Item::ITEM_CLASS_MAX;

	/*
	map<string, Item::ItemClass>::const_iterator ClassType = m_ItemClassMap.find(ClassName);

    if (ClassType==m_ItemClassMap.end())
	{
		return Item::ITEM_CLASS_RING;
	}
	else
	{
		return ClassType->second;
	}
	*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string ItemFactoryManager::toString () const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ItemFactoryManager(\n";

	for (int i = 0 ; i < m_Size ; i ++)
	{
		msg << "ItemFactories[" << i << "] == ";
		msg	<< (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getItemClassName());
		msg << "\n";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
ItemFactoryManager* g_pItemFactoryManager = NULL;
