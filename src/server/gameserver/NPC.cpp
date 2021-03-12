//////////////////////////////////////////////////////////////////////////////
// Filename    : NPC.cpp
// Written By  : 김성민
// Description : 
// 원래는 상점 처리 부분이 없었으나, 이 클래스를 상속받아 상점 NPC를 
// 만들기도 좀 그래서, 그냥 NPC 안에다 상점 인터페이스를 집어넣었다.
//////////////////////////////////////////////////////////////////////////////

#include "NPC.h"
#include "ShopRack.h"
#include "mission/QuestInfoManager.h"
#include "mission/RewardClassInfoManager.h"
#include "PlayerCreature.h"
#include "couple/PartnerWaitingManager.h"
#include "Gpackets/GCNPCAskDynamic.h"
#include "CastleInfoManager.h"

//////////////////////////////////////////////////////////////////////////////
// class NPC member methods
//////////////////////////////////////////////////////////////////////////////

NPC::NPC ()
	 
{
	__BEGIN_TRY

	m_pInventory = NULL;

	// 다음 처리받을 턴을 지정한다.
	getCurrentTime(m_NextTurn);
	m_NextTurn.tv_sec  += rand() % 3;
	m_NextTurn.tv_usec += rand() % 1000000;
	if (m_NextTurn.tv_usec >= 1000000) m_NextTurn.tv_sec++;

	// 인벤토리 객체를 생성한다.
	//m_pInventory = new Inventory(5,5);	

	// 상점 진열장 객체를 생성한다.
	m_pRack = new ShopRack[SHOP_RACK_TYPE_MAX];
	Assert(m_pRack != NULL);

	// 상점 시세 변수를 디폴트로 세팅해준다.
	m_MarketCondBuy  = 25;
	m_MarketCondSell = 100;

	// 기본적으로 상점은 일반 상점이다.
	m_ShopType = SHOPTYPE_NORMAL;

	m_ClanType = 0;
		
	// 그냥 의미없는 default.
	// 잘못해서 VisionInfo에서 Sight를 찾는 경우 대비
	// by sigi. 2002.9.6
	m_Sight = 5;

	//m_pQuestBoard = NULL;

	m_pCoupleRegisterManager = NULL;
	m_pCoupleUnregisterManager = NULL;

	m_pQuestInfoManager = NULL;
	m_pRewardClassInfoManager = NULL;

	m_TaxingCastleZoneID = 0;

	__END_CATCH
}

NPC::NPC (const string & name) 
	 
{
	__BEGIN_TRY

	m_Name       = name;
	m_pInventory = NULL;

	// 다음 처리받을 턴을 지정한다.
	getCurrentTime(m_NextTurn);
	m_NextTurn.tv_sec += rand() % 3;
	m_NextTurn.tv_usec += rand() % 1000000;
	if (m_NextTurn.tv_usec >= 1000000) m_NextTurn.tv_sec ++;

	// 인벤토리 객체를 생성한다.
	//m_pInventory = new Inventory(5,5);	

	// 상점 진열장 객체를 생성한다.
	m_pRack = new ShopRack[SHOP_RACK_TYPE_MAX];
	Assert(m_pRack != NULL);

	// 상점 시세 변수를 디폴트로 세팅해준다.
	m_MarketCondBuy  = 25;
	m_MarketCondSell = 100;

	m_pCoupleRegisterManager = NULL;
	m_pCoupleUnregisterManager = NULL;

	m_pQuestInfoManager = NULL;
	m_pRewardClassInfoManager = NULL;

	__END_CATCH
}

NPC::~NPC() 
    
{
	__BEGIN_TRY

	SAFE_DELETE(m_pCoupleUnregisterManager);
	SAFE_DELETE(m_pCoupleRegisterManager);

	SAFE_DELETE(m_pQuestInfoManager);
	SAFE_DELETE(m_pRewardClassInfoManager);

	SAFE_DELETE(m_pInventory);
	SAFE_DELETE_ARRAY(m_pRack); 
	
	__END_CATCH
}

// registerObject()
// Zone에 종속된 ObjectRegistry를 사용해서, 
// NPC 와 소유아이템들의 ObjectID를 할당받는다.
// 현재로는 등록해야 할 것은 NPC 자신의 OID 밖에 없다.
void NPC::registerObject ()
	
{
	__BEGIN_TRY

	Assert(getZone() != NULL);

	ObjectRegistry & OR = getZone()->getObjectRegistry();

	__ENTER_CRITICAL_SECTION(OR)

	OR.registerObject_NOLOCKED(this);

	__LEAVE_CRITICAL_SECTION(OR)

	__END_CATCH
}

// load()
// 이 NPC와 관련된 데이터들을 로드한다.
// 스크립트나, 트리거 등등.
bool NPC::load ()
	
{
	__BEGIN_TRY

	// trigger 를 로딩한다.
	m_TriggerManager.load(m_Name); 

	// AtFirst 컨디션이 있으면, 실행하고 삭제한다.
	if (m_TriggerManager.hasCondition(Condition::CONDITION_AT_FIRST))
	{
		list<Trigger*>&          triggers = m_TriggerManager.getTriggers();
		list<Trigger*>::iterator itr      = triggers.begin();

		for (; itr != triggers.end(); itr++)
		{
			Trigger* pTrigger = *itr;
			if (pTrigger->hasCondition(Condition::CONDITION_AT_FIRST))
			{
				pTrigger->activate(this);
				triggers.erase(itr);
				break;
			}
		}
	}

	return true;

	__END_CATCH
}

// init()
// 데이터들을 초기화하고...존에 NPC를 등록한다.
void NPC::init ()
	
{
	__BEGIN_TRY

	load();
	//registerObject();

	__END_CATCH
}

// act()
// 게임 서버의 메인 루프마다 한번씩 불리는 함수이다.
// AI 코드가 수행되는 메인 함수라 할 수 있다.
void NPC::act(const Timeval& currentTime)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// 현재 시간이 다음 턴보다 크다면, 아직 좀 더 기다려야 한다.
	// 그렇지 않으면, 액션을 취한다.
	if (currentTime < m_NextTurn) return;	

	// 다음 턴을 지정한다.
	// 현재 NPC들은 1초에 1타일만 움직이기 땜시로.. =_=;
	Timeval delay;
	delay.tv_sec  = 0;
	delay.tv_usec = 750000 + rand() % 200000;
	m_NextTurn = m_NextTurn + delay;

	if ( m_pCoupleRegisterManager != NULL ) m_pCoupleRegisterManager->heartbeat();
	if ( m_pCoupleUnregisterManager != NULL ) m_pCoupleUnregisterManager->heartbeat();

	// 트리거를 가지고 있을 경우, 각 트리거들의 조건이 만족되는지 체크한다.
	// 만약 특정 트리거의 모든 조건이 만족한다면, 그 트리거에 해당되는
	// 액션을 실행하고 리턴한다. 왜냐하면, 트리거 역시 액션이므로,
	// 일단 액션은 한 턴에 한번만 실행되기 때문이다. 
	list<Trigger*>&          triggers = m_TriggerManager.getTriggers();
	list<Trigger*>::iterator itr      = triggers.begin();

	for (; itr != triggers.end(); itr++) 
	{
		Trigger* pTrigger = *itr;
		if (pTrigger->isAllSatisfied(Trigger::ACTIVE_TRIGGER , this))
		{
			pTrigger->activate(this);
			return;
		}
	}

	__END_DEBUG
	__END_CATCH
}

// getShopVersion()
// 지정된 종류의 상점의 버전을 리턴한다.
ShopVersion_t NPC::getShopVersion(ShopRackType_t type) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].getVersion();
}

// setShopVersion()
// 지정된 종류의 상점의 버전을 세팅한다.
void NPC::setShopVersion(ShopRackType_t type, ShopVersion_t ver)
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	m_pRack[type].setVersion(ver);
}

// increaseShopVersion()
// 지정된 종류의 상점의 버전을 올린다.
void NPC::increaseShopVersion(ShopRackType_t type)
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	m_pRack[type].increaseVersion();
}

// isExistShopItem()
// 지정된 종류와 인덱스의 아이템이 상점 진열장 안에 존재하는지 리턴한다.
bool NPC::isExistShopItem(ShopRackType_t type, BYTE index) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].isExist(index);
}

// insertShopItem()
// 지정된 종류와 인덱스의 진열장에다가 아이템을 집어넣는다.
void NPC::insertShopItem(ShopRackType_t type, BYTE index, Item* pItem)
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	m_pRack[type].insert(index, pItem);
}

// removeShopItem()
// 지정된 종류와 인덱스의 진열장에서 아이템을 제거한다.
void NPC::removeShopItem(ShopRackType_t type, BYTE index)
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].remove(index);
}

// getShopItem()
// 지정된 종류와 인덱스의 진열장에 있는 아이템 포인터를 리턴한다.
Item* NPC::getShopItem(ShopRackType_t type, BYTE index) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].get(index);
}

// clearShopItem()
// 진열장을 청소(?)한다.
void NPC::clearShopItem(void)
{
	for (int i=0; i<SHOP_RACK_TYPE_MAX; i++) 
		m_pRack[i].clear();
}

// getFirstEmptySlot()
// 지정된 종류의 진열장에서 제일 앞쪽의 빈 칸을 찾는다.
BYTE NPC::getFirstEmptySlot(ShopRackType_t type) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].getFirstEmptySlot();
}

// getLastEmptySlot()
// 지정된 종류의 진열장에서 제일 뒤쪽의 빈 칸을 찾는다.
BYTE NPC::getLastEmptySlot(ShopRackType_t type) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].getLastEmptySlot();
}

// isFull()
// 지정된 종류의 진열장이 현재 꽉찬 상태인지를 리턴한다.
bool NPC::isFull(ShopRackType_t type) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].isFull();
}

// isEmpty
// 지정된 종류의 진열장이 현재 빈 상태인지를 리턴한다.
bool NPC::isEmpty(ShopRackType_t type) const
{
	Assert(type < SHOP_RACK_TYPE_MAX);
	return m_pRack[type].isEmpty();
}

int NPC::getTaxRatio(PlayerCreature* pPC) const
{
	return g_pCastleInfoManager->getItemTaxRatio(pPC, this);
}

// SimpleQuest by sigi. 2002.12.3
/*bool NPC::regenSimpleQuest() 
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__
	if (m_pQuestBoard==NULL)
	{
		m_pQuestBoard = new QuestBoard();
	}
	else
	{
		m_pQuestBoard->release();
	}

	// 테스트.. 5개만 생성.
	m_pQuestBoard->regenerate( 5 );
#endif

	return true;

	__END_CATCH
}

bool NPC::giveSimpleQuest(Creature* pCreature, QuestID_t qid) 
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__

	if (m_pQuestBoard!=NULL)
	{
		Assert(pCreature!=NULL);

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		Quest* pQuest = m_pQuestBoard->remove( qid );

		// 그런 QuestID는 없다.
		if (pQuest==NULL)
		{
			// cout << "No Such Quest(" << (int)qid << ")" << endl;
			return false;
		}

		m_pQuestBoard->remove( qid );

		pQuest->take( pPC );
		if (pPC->addQuest( pQuest ))
		{
			return true;
		}

		// quest 추가 실패
		SAFE_DELETE(pQuest);
		//cout << "cannot add Quest(" << (int)qid << ")" << endl;
	}

#endif

	return false;

	__END_CATCH
}

void NPC::setSimpleQuestListScript(Script* pScript)
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__
	if (m_pQuestBoard!=NULL)
	{
		Assert(pScript!=NULL);

		m_pQuestBoard->setScript(pScript);
	}

#endif

	__END_CATCH
}
*/
/*
void NPC::sendSimpleQuestListPacket(Creature* pCreature)
	
{
	__BEGIN_TRY

#ifdef __ACTIVE_QUEST__
	if (m_pQuestBoard!=NULL)
	{
		Assert(pCreature!=NULL);
		Assert(pCreature->isPC());

		GCNPCAskDynamic npcAskPacket;
		npcAskPacket.setObjectID( getObjectID() );
		m_pQuestBoard->makeNPCAskPacket(npcAskPacket);

		pCreature->getPlayer()->sendPacket( &npcAskPacket );
	}

#endif

	__END_CATCH
}
*/

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string NPC::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "NPC("
	    << "ObjectID:"    << (int)m_ObjectID
	    << ",SpriteType:" << (int)m_SpriteType
	    << ",Name:"       << m_Name
	    << ",MainColor:"  << (int)m_MainColor
	    << ",SubColor:"   << (int)m_SubColor
	    << ",X:"          << (int)m_X
	    << ",Y:"          << (int)m_Y
	    << ",Sight:"      << (int)m_Sight
	    << m_TriggerManager.toString()
	    << ")";
	return msg.toString();

	__END_CATCH
}
