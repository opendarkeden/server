//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReloadTimer.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectReloadTimer.h"
#include "Creature.h"
#include "Slayer.h"
#include "Player.h"
#include "Gpackets/GCReloadOK.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "item/Magazine.h"
#include "item/SG.h"
#include "item/AR.h"
#include "item/SMG.h"
#include "item/SR.h"
#include "item/Belt.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
EffectReloadTimer::EffectReloadTimer(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// EffectReloadTimer::affect()
//////////////////////////////////////////////////////////////////////////////
void EffectReloadTimer::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// EffectReloadTimer::affect()
//////////////////////////////////////////////////////////////////////////////
void EffectReloadTimer::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// EffectReloadTimer::unaffect()
//////////////////////////////////////////////////////////////////////////////
void EffectReloadTimer::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	unaffect((Creature*)m_pTarget);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// EffectReloadTimer::unaffect()
//////////////////////////////////////////////////////////////////////////////
void EffectReloadTimer::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectReloadTimer " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	Slayer*    pSlayer     = dynamic_cast<Slayer*>(pCreature);
	Player*    pPlayer     = pSlayer->getPlayer();
	Item*      pArmsItem   = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	Bullet_t   BulletNum   = 0;
	Item*      pItem       = NULL;
	Item*      pBelt       = NULL;
	Inventory* pInventory  = NULL;
	bool       bSuccess    = false;

	// 일단 성공하든 실패하든 플래그는 제거시킨다.
	pSlayer->removeFlag(Effect::EFFECT_CLASS_RELOAD_TIMER);

	if (pArmsItem != NULL) 
	{
		if (isArmsWeapon(pArmsItem)) 
		{
			if (m_bFromInventory)
			{
				// 인벤토리에서 직접 리로드하는 경우라면,
				// 인벤토리 내부에서 아이템을 찾는다.
				pInventory = pSlayer->getInventory();
				pItem      = pInventory->getItem(m_invenX, m_invenY);
			}
			else
			{
				// 벨트에서 리로드하는 경우라면 
				// 벨트 내부에서 아이템을 찾는다.
				if (pSlayer->isWear(Slayer::WEAR_BELT)) 
				{
					pBelt      = pSlayer->getWearItem(Slayer::WEAR_BELT);
					pInventory =((Belt*)pBelt)->getInventory();
					pItem      = pInventory->getItem(m_SlotID, 0);
				}
			}

			if (pItem == NULL || pInventory == NULL)
			{
				//cout << "EffectReloadTimer : 아이템이 널이거나, 인벤토리가 널입니다." << endl;
				//cout << "EffectReloadTimer " << "unaffect END" << endl;
				return;
			}
	
			ObjectID_t ItemObjectID = pItem->getObjectID();

			// 아이템이 있는지 그 아이템의 ObjectID가 일치하는지 체크한다.
			if (ItemObjectID == m_ObjectID && 
				pItem->getItemClass() == Item::ITEM_CLASS_MAGAZINE)
			{
				BulletNum = reloadArmsItem(pArmsItem, pItem);

				// 리로드가 정상적으로 되었다면 저장해 준다.
				if (BulletNum != 0)
				{
					//pArmsItem->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);

					// 아이템 저장 최적화
					// by sigi. 2002.5.16
//					Gun* pGun = dynamic_cast<Gun*>(pArmsItem);
					char pField[80];
					sprintf(pField, "BulletCount=%d, Silver=%d", pArmsItem->getBulletCount(), pArmsItem->getSilver());
					pArmsItem->tinysave(pField);

					// 탄창의 갯수가 2개 이상이라면...
					if (pItem->getNum() > 1) 
					{
						// 아이템의 갯수를 줄이고,
						// 인벤토리 내부의 총 갯수 및 무게를 줄인다.
						pItem->setNum(pItem->getNum() - 1);
						pInventory->decreaseItemNum();
						pInventory->decreaseWeight(pItem->getWeight());
		
						// 줄어든 아이템의 갯수를 저장한다.
						if (m_bFromInventory) 
						{
							//pItem->save(pSlayer->getName(), STORAGE_INVENTORY, 0, m_invenX, m_invenY);
							// by sigi. 2002.5.16
							sprintf(pField, "Num=%d", pItem->getNum());
							pItem->tinysave(pField);
						}
						else 
						{
							//pItem->save(pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), m_SlotID, 0);
							// by sigi. 2002.5.16
							sprintf(pField, "Num=%d", pItem->getNum());
							pItem->tinysave(pField);
						}
					} 
					// 탄창의 갯수가 1개라면 삭제해줘야 한다.
					else 
					{
						if (m_bFromInventory) pInventory->deleteItem(m_invenX, m_invenY);
						else pInventory->deleteItem(m_SlotID, 0);

						pItem->destroy();
						SAFE_DELETE(pItem);
					}

					bSuccess = true;
				} // if (BulletNum != 0)
			}
		}
	} 

	if (bSuccess)
	{
		GCReloadOK ok;
		ok.setBulletNum(BulletNum);
		pPlayer->sendPacket(&ok);
	}

	//cout << "EffectReloadTimer " << "unaffect END" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectReloadTimer::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string EffectReloadTimer::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectReloadTimer("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH
}

