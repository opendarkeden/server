//////////////////////////////////////////////////////////////////////////////
// Filename    : EventReloadInfo.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventReloadInfo.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZoneUtil.h"
#include "IncomingPlayerManager.h"
#include "ZonePlayerManager.h"
#include "MasterLairInfoManager.h"
#include "ItemInfoManager.h"
#include "MonsterInfo.h"
#include "LogNameManager.h"
#include "Directive.h"
#include "RankBonusInfo.h"
#include "OptionInfo.h"
#include "WarScheduler.h"
#include "ShrineInfoManager.h"
#include "StringPool.h"
#include "GCSystemMessage.h"
#include "RaceWarLimiter.h"
#include "mission/QuestInfoManager.h"
#include "GoodsInfoManager.h"
#include "SweeperBonusManager.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// class EventReloadInfo member methods
//////////////////////////////////////////////////////////////////////////////

EventReloadInfo::EventReloadInfo(GamePlayer* pGamePlayer, InfoType infoType, int infoValue)
	throw()
: Event(pGamePlayer), m_InfoType(infoType), m_InfoValue(infoValue)
{
}

EventReloadInfo::~EventReloadInfo() 
	throw()
{
}

void EventReloadInfo::activate () 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//(m_pGamePlayer != NULL);//NULL일 수 있다.

	switch (m_InfoType)
	{
		case MASTER_LAIR_INFO :
			g_pMasterLairInfoManager->reload();
		break;

		case MONSTER_INFO :
		{
			// m_InfoValue는 loading할 Monster의 SpriteType이다.
			if (m_InfoValue==0)
			{
				// 전부 다 loading
				g_pMonsterInfoManager->reload(0);
			}
			else
			{
				// SpriteType과 관련된 몬스터들을 알아낸다.
				const vector<MonsterType_t>& monsters = g_pMonsterInfoManager->getMonsterTypeBySprite(m_InfoValue);

				vector<MonsterType_t>::const_iterator itr = monsters.begin();

				for (; itr!=monsters.end(); itr++)
				{
					g_pMonsterInfoManager->reload(*itr);
				}
			}
		}
		break;

		case MONSTER_AI :
			g_pDirectiveSetManager->load();
		break;

		case ZONE_INFO :
			g_pZoneInfoManager->load();
		break;

		case ZONE :
		break;

		case ITEM_INFO :
		{
			// m_InfoValue는 loading할 ItemInfo의 Class이다
			g_pItemInfoManager->getInfoManager((Item::ItemClass)m_InfoValue )->reload();
		}
		break;

		case LOG_USER_INFO :
			LogNameManager::getInstance().init();
		break;

		case RANK_BONUS_INFO :
		{
			g_pRankBonusInfoManager->load();
		}
		break;

		case OPTION_INFO :
		{
			g_pOptionInfoManager->load();
		}
		break;

		case STRING_POOL :
		{
			g_pStringPool->load();
		}
		break;

		case WAR_SCHEDULE_INFO :
		{
			ZoneID_t zoneID = (ZoneID_t)m_InfoValue;

			Zone* pZone = getZoneByZoneID(zoneID);

			if (m_pGamePlayer!=NULL)
			{
				GCSystemMessage gcSystemMessage;

				if (pZone!=NULL)
				{
					WarScheduler* pWarScheduler = pZone->getWarScheduler();

					if (pWarScheduler!=NULL)
					{
						pWarScheduler->load();

//						StringStream msg;
//						msg << "[" << (int)zoneID << "] 성에는 " << pWarScheduler->getSize() << " 개의 전쟁이 준비중입니다.";

						char msg[100];
						sprintf(msg, g_pStringPool->c_str(STRID_WAR_SCHEDULE_INFO ),
										(int)zoneID, pWarScheduler->getSize());
						gcSystemMessage.setMessage(msg);
					}
					else
					{
						gcSystemMessage.setMessage(g_pStringPool->getString(STRID_THIS_ZONE_IS_NOT_CASTLE ));
					}
				}
				else
				{
					gcSystemMessage.setMessage(g_pStringPool->getString(STRID_NO_SUCH_ZONE ));
				}

				m_pGamePlayer->sendPacket(&gcSystemMessage);
			}
		}
		break;

		case BLOOD_BIBLE_OWNER :
		{
			g_pShrineInfoManager->reloadOwner();

			if (m_pGamePlayer!=NULL)
			{
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage(g_pStringPool->getString(STRID_LOAD_BLOOD_BIBLE_OWNER_INFO ));
				m_pGamePlayer->sendPacket(&gcSystemMessage);
			}
		}
		break;

		case RACE_WAR_PC_LIMIT :
			RaceWarLimiter::getInstance()->load();
		break;

/*		case QUEST_INFO:
			g_pQuestInfoManager->load();
			if (m_pGamePlayer!=NULL)
			{
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage("Quest_Info_Loaded");
				m_pGamePlayer->sendPacket(&gcSystemMessage);
			}
		break;*/

		case GOODS_LIST_INFO:
			g_pGoodsInfoManager->load();
			break;

		case SWEEPER_OWNER:
			g_pSweeperBonusManager->reloadOwner(m_InfoValue);
			break;

		default :
		break;
	}

	__END_DEBUG
	__END_CATCH
}

string EventReloadInfo::toString () const 
	throw()
{
	StringStream msg;
	msg << "EventReloadInfo("
		<< ")";
	return msg.toString();
}
