#include "GameServerItemTest.h"
#include "Item.h"
//#include "LuckInfo.h"
#include "VariableManager.h"
#include "ItemFactoryManager.h"
#include "Vampire.h"
#include "Slayer.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "ItemUtil.h"

void
GameServerItemTest::testLuckPercent()
{
	__BEGIN_TEST_CASE

/*	int luckLevel = 10;
	const LuckInfo& luckInfo = g_pLuckInfoManager->getLuckInfo(luckLevel);

	// 100% --> 100000
	g_pVariableManager->setVariable(ITEM_LUCK_PERCENT, 100);
	int variableLuckRatio = g_pVariableManager->getVariable(ITEM_LUCK_PERCENT);

	CPPUNIT_ASSERT( variableLuckRatio==100 );
	CPPUNIT_ASSERT( luckInfo.getMaxRatio()==100000 );

	// 200% --> 50000
	g_pVariableManager->setVariable(ITEM_LUCK_PERCENT, 200);
	variableLuckRatio = g_pVariableManager->getVariable(ITEM_LUCK_PERCENT);

	CPPUNIT_ASSERT( variableLuckRatio==200 );
	CPPUNIT_ASSERT( luckInfo.getMaxRatio()==50000 );

	// 0% : min이 10%이기 때문에.. 10% --> 10000
	g_pVariableManager->setVariable(ITEM_LUCK_PERCENT, 0);
	variableLuckRatio = g_pVariableManager->getVariable(ITEM_LUCK_PERCENT);

	CPPUNIT_ASSERT( variableLuckRatio==0 );
	CPPUNIT_ASSERT( luckInfo.getMaxRatio()==1000000 );

	// 500% --> 20000
	g_pVariableManager->setVariable(ITEM_LUCK_PERCENT, 500);
	variableLuckRatio = g_pVariableManager->getVariable(ITEM_LUCK_PERCENT);

	CPPUNIT_ASSERT( variableLuckRatio==500 );
	CPPUNIT_ASSERT( luckInfo.getMaxRatio()==20000 );
*/

	__END_TEST_CASE
}


// 아이템 착용 요구능력치가 최대값(ex> 뱀파이어 레벨100)을 넘어가는 거때메
// 요구능력치의 최대값을 제한해버린 것에 대한 테스트 -_-; 2003.1.6
void 
GameServerItemTest::testRequireMaxVampire()
{
	__BEGIN_TEST_CASE

	Item::ItemClass IClass = Item::ITEM_CLASS_VAMPIRE_COAT;
	ItemType_t		IType = 10;								// Level 90
	list<OptionType_t> OTypes; OTypes.push_back( 186 );		// Level 50

	Item* pItem = g_pItemFactoryManager->createItem(IClass, IType, OTypes);

	Vampire* pVampire = new Vampire;
	Zone* pZone = getZoneByZoneID( 11 );
	CPPUNIT_ASSERT( pZone!=NULL );

	pVampire->setZone( pZone );

	pVampire->setLevel( 100 );
	pVampire->setSex( MALE );
		
	CPPUNIT_ASSERT( pVampire->isRealWearing(pItem)==true );

	pVampire->setLevel( 10 );
	CPPUNIT_ASSERT( pVampire->isRealWearing(pItem)==false );

	SAFE_DELETE(pVampire);
	SAFE_DELETE(pItem);

	__END_TEST_CASE
}

void 
GameServerItemTest::testRequireMaxSlayer()
{
	__BEGIN_TEST_CASE

	Item::ItemClass IClass = Item::ITEM_CLASS_COAT;
	ItemType_t		IType = 14;								// SUM 280
	list<OptionType_t> OTypes; OTypes.push_back( 186 );		// SUM 100

	Item* pItem = g_pItemFactoryManager->createItem(IClass, IType, OTypes);

	Slayer* pSlayer = new Slayer;
	Zone* pZone = getZoneByZoneID( 11 );
	CPPUNIT_ASSERT( pZone!=NULL );

	pSlayer->setZone( pZone );

	pSlayer->setSTR( 100, ATTR_CURRENT );
	pSlayer->setDEX( 100, ATTR_CURRENT );
	pSlayer->setINT( 100, ATTR_CURRENT );
	pSlayer->setSex( MALE );
		
	CPPUNIT_ASSERT( pSlayer->isRealWearing(pItem)==true );

	pSlayer->setSTR( 90, ATTR_CURRENT );
	pSlayer->setDEX( 100, ATTR_CURRENT );
	pSlayer->setINT( 100, ATTR_CURRENT );

	CPPUNIT_ASSERT( pSlayer->isRealWearing(pItem)==false );

	SAFE_DELETE(pSlayer);
	SAFE_DELETE(pItem);

	__END_TEST_CASE
}

void GameServerItemTest::testGiveNewbieItem()
{
	__BEGIN_TEST_CASE

	Slayer* pSlayer = new Slayer;
	Zone* pZone = getZoneByZoneID( 11 );
	CPPUNIT_ASSERT( pZone != NULL );

	pSlayer->setZone( pZone );

	Inventory* pInventory = pSlayer->getInventory();
	
	CPPUNIT_ASSERT( addNewbieItemToInventory( pSlayer ) );
	CPPUNIT_ASSERT( addNewbieGoldToInventory( pSlayer ) );
	CPPUNIT_ASSERT( addNewbieItemToGear( pSlayer ) );

	Item* pItem;

	// 능력치에 따라서 하나를 입기 때문에 NULL체크하는 부분에서
	// Fail이 하나는 뜨게 된다 -_-;
	
	pItem = pInventory->getItem( 2, 3 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_BLADE );
	CPPUNIT_ASSERT( pItem->getItemType()  == 0 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );

	pItem = pInventory->getItem( 4, 3 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_SWORD );
	CPPUNIT_ASSERT( pItem->getItemType()  == 0 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	
	pItem = pInventory->getItem( 0, 3 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_CROSS );
	CPPUNIT_ASSERT( pItem->getItemType()  == 0 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	
	pItem = pInventory->getItem( 0, 0 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_MACE );
	CPPUNIT_ASSERT( pItem->getItemType()  == 0 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	
	pItem = pInventory->getItem( 2, 0 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_AR );
	CPPUNIT_ASSERT( pItem->getItemType()  == 0 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	
	pItem = pInventory->getItem( 4, 0 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_MAGAZINE );
	CPPUNIT_ASSERT( pItem->getItemType()  == 2 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	CPPUNIT_ASSERT( pItem->getNum() == 20 );
	
	pItem = pInventory->getItem( 9, 4 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_POTION );
	CPPUNIT_ASSERT( pItem->getItemType()  == 0 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	CPPUNIT_ASSERT( pItem->getNum() == 9 );
	
	pItem = pInventory->getItem( 9, 5 );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_POTION );
	CPPUNIT_ASSERT( pItem->getItemType()  == 5 );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );
	CPPUNIT_ASSERT( pItem->getNum() == 9 );

	CPPUNIT_ASSERT( pSlayer->getGold() == 500 );

	pItem = pSlayer->getWearItem( Slayer::WEAR_BODY );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_COAT );
	CPPUNIT_ASSERT( pItem->getItemType() == ((pSlayer->getSex()==MALE)?0:1) );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );

	pItem = pSlayer->getWearItem( Slayer::WEAR_LEG );
	CPPUNIT_ASSERT( pItem != NULL );
	CPPUNIT_ASSERT( pItem->getItemClass() == Item::ITEM_CLASS_TROUSER );
	CPPUNIT_ASSERT( pItem->getItemType() == ((pSlayer->getSex()==MALE)?0:1) );
	CPPUNIT_ASSERT( pItem->getOptionTypeSize() == 0 );

	__END_TEST_CASE
}

void GameServerItemTest::testUpgradeItemType()
{
	__BEGIN_TEST_CASE

	Item::ItemClass IClass;

	// Sword: 0~11. 10이 unique
	IClass = Item::ITEM_CLASS_SWORD;
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 0, 1)==1);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 1, 1)==2);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 2, 1)==3);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 3, 1)==4);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 4, 1)==5);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 5, 1)==6);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 6, 1)==7);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 7, 1)==8);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 8, 1)==9);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 9, 1)==11);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 10, 1)==10);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 11, 1)==11);

	// 2단 업글
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 0, 2)==2);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 1, 2)==3);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 2, 2)==4);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 3, 2)==5);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 4, 2)==6);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 5, 2)==7);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 6, 2)==8);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 7, 2)==9);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 8, 2)==10);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 9, 2)==11);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 10, 2)==10);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 11, 2)==11);

	// 3단 업글
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 0, 3)==3);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 1, 3)==4);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 2, 3)==5);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 3, 3)==6);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 4, 3)==7);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 5, 3)==8);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 6, 3)==9);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 7, 3)==11);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 8, 3)==11);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 9, 3)==11);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 10, 3)==10);
	CPPUNIT_ASSERT(getUpgradeItemType(IClass, 11, 3)==11);


	__END_TEST_CASE
}
