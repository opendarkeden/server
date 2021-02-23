//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDissectionCorpseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDissectionCorpse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Corpse.h"
	#include "Relic.h"
	#include "BloodBible.h"
	#include "MonsterCorpse.h"
	#include "SlayerCorpse.h"
	#include "AlignmentManager.h"
	#include "PCSlayerInfo3.h"
	#include "PCVampireInfo3.h"
	#include "VampireCorpse.h"
	#include "PCVampireInfo3.h"
	#include "PCOustersInfo3.h"
	#include "OustersCorpse.h"
	#include "PCOustersInfo3.h"
	#include "Effect.h"
	#include "EffectRelicTable.h"
	#include "EffectPrecedence.h"
	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "ZoneUtil.h"
	#include "ItemUtil.h"
	#include "RelicUtil.h"
	#include "CreatureUtil.h"
    #include "DB.h"
	#include "CombatInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "ItemInfoManager.h"
	#include "UniqueItemManager.h"
	#include "war/WarSystem.h"
	#include "ShrineInfoManager.h"
	#include "CastleInfoManager.h"
	#include "CastleShrineInfoManager.h"
	#include "StringPool.h"
	#include "PacketUtil.h"
	#include "MonsterInfo.h"
	#include "PetUtil.h"
	#include "PetInfo.h"

	#include "ctf/FlagManager.h"
	#include "EffectFlagInsert.h"
	#include "LevelWarManager.h"
	#include "GQuestManager.h"
	#include "Party.h"

	#include <stdio.h>

	#include "Gpackets/GCRemoveCorpseHead.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCRemoveEffect.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDissectionCorpseHandler::execute (CGDissectionCorpse* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

		Creature*   pCreature = pGamePlayer->getCreature();
		Zone*       pZone     = pCreature->getZone();
		ZoneCoord_t ZoneX     = pPacket->getX();
		ZoneCoord_t ZoneY     = pPacket->getY();

		// 바운드를 넘어가지는 않는지 체크한다.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) 
		{
			return;
		}

		Tile& rTile = pZone->getTile(ZoneX , ZoneY);
        Item* pItem = rTile.getItem();

		// Coma상태라면 루팅 불가. by sigi. 2002.12.10
        // 현재 박쥐 상태라면 리턴
        if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
       	 	|| pCreature->isFlag(Effect::EFFECT_CLASS_PARALYZE)
			|| pCreature->isVampire() && pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
           return;
		
		// 슬레이어인 경우 오토바이 타고 있으면 아이템 루팅 불가 by sigi
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			if (pSlayer->hasRideMotorcycle())
			{
				return;
			}
		}

		// 아우스터즈인 경우 실프 타고 있으면 루팅 불가 by DEW
		if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			if (pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH))
			{
				return;
			}
		}

		// 바닥에 아이템이 없으면 리턴
		// 오브젝트 아이디가 일치하지 않으면 리턴
		// 바닥에 있는 아이템이 시체가 아니면 리턴
		if (pItem == NULL
			|| pItem->getObjectID() != pPacket->getObjectID()
			|| pItem->getItemClass() != Item::ITEM_CLASS_CORPSE)
		{
			return;
		}

		bool bSlayerRelicTable = pItem->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);
		bool bVampireRelicTable = pItem->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);

		// 슬레이어가 슬레이어의 성물보관함을 클릭할 수 없고,
		// 뱀파이어도 뱀파이어의 성물보관함을 클릭할 수 없다.
		if ( (pCreature->isSlayer() && bSlayerRelicTable)
			|| (pCreature->isVampire() && bVampireRelicTable) )
		{
			return;
		}

		// 성단일 경우 전쟁중이 아니라면 클릭할 수 없다.
		// 수호 성단일 경우 수비측에서는 클릭할 수 없다.
		if ( pItem->getItemType() == MONSTER_CORPSE )
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			if ( pMonsterCorpse->getTreasureCount() > 200 )
			{
				// 퀘스트용 시체. 설마 진짜로 200개 루팅되는 몬스터는 없겠지 --;
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				pPC->getGQuestManager()->touchWayPoint(pMonsterCorpse);
				return;
			}

			if ( g_pFlagManager->isFlagPole( pMonsterCorpse ) )
			{
				if ( !g_pFlagManager->hasFlagWar() ) return;
			}
			else if (
					pZone->getLevelWarManager() != NULL &&
					pZone->getLevelWarManager()->isSafe( pMonsterCorpse ) )
			{
				if ( !pZone->getLevelWarManager()->hasWar() ) return;
				else if ( ( pCreature->isSlayer() && pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 0 )
						 || ( pCreature->isVampire() && pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 1 )
						 || ( pCreature->isOusters() && pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 2 ) )
				{
					return;
				}
			}
			else if ( pMonsterCorpse->isShrine() )
			{
				// 보호막이 걸려있으면 못 꺼낸다.
				if ( pMonsterCorpse->isFlag( Effect::EFFECT_CLASS_SHRINE_SHIELD ) )
					return;
					
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC );

				ZoneID_t 	castleZoneID;
				bool		isCastle;

				bool hasWar = false;

				isCastle = g_pCastleInfoManager->getCastleZoneID( pZone->getZoneID() , castleZoneID);

				if ( isCastle && g_pWarSystem->hasCastleActiveWar( castleZoneID ) )
				{
					// 길드전쟁일 경우 처리
					// if ( pItem->getItemClass() != Item::ITEM_CLASS_CASTLE_SYMBOL ) return;

					// 성에서는 방어측일 경우 클릭할 수 없다.
#ifndef __OLD_GUILD_WAR__
#else
					if ( g_pCastleShrineInfoManager->isDefenderOfGuardShrine( pPC, pMonsterCorpse ) )
						return;
#endif

					CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
					if ( pCastleInfo->getRace() != pPC->getRace() )
						return;

					hasWar = true;
				}

				if ( g_pWarSystem->hasActiveRaceWar() )
				{
					// 종족간 전쟁일 경우 처리
					// if ( pItem->getItemClass() != Item::ITEM_CLASS_BLOOD_BIBLE ) return;

					// 성에서는 방어측일 경우 클릭할 수 없다.
					if ( g_pShrineInfoManager->isDefenderOfGuardShrine( pPC, pMonsterCorpse ) )
						return;

					hasWar = true;
				}

				// 전쟁이 암것도 없으면 성단에서 암것도 못 꺼낸다.
				if (!hasWar)
				{
					return;
				}
			}
		}

		// 이까지 왔다면, 상대편 종족의 성물보관함을 클릭한 경우이다.
		// 이 경우, 만약 EffectRelic이 얼만큼 남아 있는지 체크해야 한다.
		EffectRelicTable* pRelicTableEffect = NULL;

		// 성물 보관대 종류에 따라서 붙어있는 Effect를 얻어온다.
		if (bSlayerRelicTable)
		{
			pRelicTableEffect = dynamic_cast<EffectRelicTable*>(
								pItem->getEffectManager().findEffect(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE));
		}
		else if (bVampireRelicTable)
		{
			pRelicTableEffect = dynamic_cast<EffectRelicTable*>(
								pItem->getEffectManager().findEffect(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE));
		}

		// 성물 보관대에서 아이템을 빼어낼 수 있는 시간인가?
		// SafeTime이 되지 않았으면 안된다.
		// LockTime 동안은 안된다.
		if (pRelicTableEffect!=NULL
			&& (!pRelicTableEffect->isSafeTime()
				|| pRelicTableEffect->isLockTime()))
		{
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_TAKE_RELIC_NOW ) );

			pGamePlayer->sendPacket( &gcSystemMessage );
			return;
		}

		// 성향을 체크 해야 한다.
		if (pItem->getItemType() != MONSTER_CORPSE) 
		{
			if ( pPacket->isPet() ) return;
			if ( !pZone->isPKZone() )
			{
				if (pItem->getItemType() == SLAYER_CORPSE && pCreature->isSlayer()) 
				{
					SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);

					PCSlayerInfo3 & rPCSlayerInfo = pSlayerCorpse->getSlayerInfo();

					// 자기 시체가 아니라면
					if (rPCSlayerInfo.getName() != pCreature->getName()) 
					{
						// 악한자의 시체는 보호받지 못한다....
						if (g_pAlignmentManager->getAlignmentType(rPCSlayerInfo.getAlignment()) >= NEUTRAL) 
						{
							Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

							// 성향이 -500 내려간다~
							Alignment_t NewAlignment = max(-10000 , pSlayer->getAlignment() - 500);

							pSlayer->setAlignment(NewAlignment);
							GCModifyInformation gcModifyInformation;
							gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
							pGamePlayer->sendPacket(&gcModifyInformation);
						}
					}
				} 
				else if (pItem->getItemType() == VAMPIRE_CORPSE && pCreature->isVampire()) 
				{
					PCVampireInfo3 & rPCVampireInfo = dynamic_cast<VampireCorpse*>(pItem)->getVampireInfo();

					// 자기 시체가 아니라면
					if (rPCVampireInfo.getName() != pCreature->getName()) 
					{
						// 악한자의 시체는 보호받지 못한다....
						if (g_pAlignmentManager->getAlignmentType(rPCVampireInfo.getAlignment()) >= NEUTRAL) 
						{
							Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

							// 성향이 -500 내려간다~
							Alignment_t NewAlignment = max(-10000 , pVampire->getAlignment() - 500);

							pVampire->setAlignment(NewAlignment);
							GCModifyInformation gcModifyInformation;
							gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
							pGamePlayer->sendPacket(&gcModifyInformation);
						}
					}
				}
				else if (pItem->getItemType() == OUSTERS_CORPSE && pCreature->isOusters()) 
				{
					PCOustersInfo3 & rPCOustersInfo = dynamic_cast<OustersCorpse*>(pItem)->getOustersInfo();

					// 자기 시체가 아니라면
					if (rPCOustersInfo.getName() != pCreature->getName()) 
					{
						// 악한자의 시체는 보호받지 못한다....
						if (g_pAlignmentManager->getAlignmentType(rPCOustersInfo.getAlignment()) >= NEUTRAL) 
						{
							Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

							// 성향이 -500 내려간다~
							Alignment_t NewAlignment = max(-10000 , pOusters->getAlignment() - 500);

							pOusters->setAlignment(NewAlignment);
							GCModifyInformation gcModifyInformation;
							gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
							pGamePlayer->sendPacket(&gcModifyInformation);
						}
					}
				}
			}
		}
		else
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPC != NULL );

			if ( pPacket->isPet() )
			{
				if ( pPC->getPetInfo() == NULL ) return; //(|| pMonsterCorpse->isNextTreasureHead() ) return;
			}

			if ( pMonsterCorpse != NULL && g_pFlagManager->isFlagPole( pMonsterCorpse ) )
			{
				if ( !g_pFlagManager->hasFlagWar() ) return;
				// 같은 종족이면 못 뽑는다..
				if ( g_pFlagManager->getFlagPoleRace( pMonsterCorpse ) == pPC->getRace() )
					return;

				TPOINT tp;
				if ( pPC->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) ) return;
				if ( !pPC->getInventory()->getEmptySlot( 1, 2, tp ) ) return;

				if (
					   pPC->isFlag(Effect::EFFECT_CLASS_CASKET)
					|| pPC->isDead()
					|| pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
					|| pPC->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
					|| pPC->isFlag(Effect::EFFECT_CLASS_TENDRIL)
					|| pPC->isFlag(Effect::EFFECT_CLASS_BLOCK_HEAD)
				) return;

				if (pPC->isSlayer())
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					if (pSlayer->hasRideMotorcycle()) return;
				}

				if ( pPC->isFlag(Effect::EFFECT_CLASS_HIDE)
					|| pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)
					|| pPC->isFlag(Effect::EFFECT_CLASS_FADE_OUT)
					|| pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF)
					|| pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
					|| pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
					|| pPC->isFlag(Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL) ) return;
			}
//			else if (
//					pZone->getLevelWarManager() != NULL &&
//					pZone->getLevelWarManager()->isSafe( pMonsterCorpse ) )
//			{
//				if ( !pZone->getLevelWarManager()->hasWar() ) return;
//			}
		}

		Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
		bool bDissectAll = false;

		// 시체에 아이템이 3개 보다 더 많이 들어가 있으면 한 번에 다뽀바낸다. 
		// 펫이 뽑아내는 아이템은 한번에 다 뽑혀나온다.
		// 2003.1.14  by bezz, Sequoia, sigi
		if ( pCorpse->getTreasureCount() > 3 || pPacket->isPet() )
			bDissectAll = true;

		int treasureCount = 0;
		ObjectID_t PetOID = 0;

		if ( pPacket->isPet() ) PetOID = pCreature->getObjectID();

		do // while ( bDissectAll );
		{
			if ( pPacket->isPet() && pCorpse->getItemType() == MONSTER_CORPSE )
			{
				MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				PetInfo* pPetInfo = pPC->getPetInfo();

				if ( pPetInfo == NULL ) break;
				if ( pMonsterCorpse->isNextTreasureHead() && pPetInfo->canCutHead()==0 ) break;
			}

			Item* pTreasure = pCorpse->getTreasure();

			if (pTreasure == NULL)
				break;

			if ( pPacket->isPet() ) pTreasure->setFlag( Effect::EFFECT_CLASS_PET_DISSECT );

			////////////////////////////////////////////////////////////////
			// 2002년 어린이날 이벤트
			// 검은별 아이템은 가족사진 촬영권으로 교환된다.
			// 그러므로 개수가 일정 수준(트랜실베니아7개, 왈라키아 3개)을
			// 넘게 나올 수 없다.
			// 만약 검은별 아이템이 나왔을 경우,
			// 아이템의 숫자를 파악해서, 제한 개수 이상이면 나오지 않도록 한다.
			
			if (pTreasure->getItemClass() == Item::ITEM_CLASS_EVENT_STAR
					&& pTreasure->getItemType() == 0)
			{
				cout << "검은별 출현" << endl;
				Statement* pStmt = NULL;
				Result*    pResult = NULL;

				try
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pResult = pStmt->executeQuery("SELECT ifnull(sum(Num),0) FROM EventStarObject WHERE ItemType=0;");

					if(pResult->getRowCount() != 1)
					{
						SAFE_DELETE(pStmt);
						throw ProtocolException("Fail to load data from DB");
					}

					if(pResult->next())
					{
						int BlackStarNumber = pResult->getInt(1);
						if(BlackStarNumber >= 7)
							cout << "검은별이 10개 넘었습니다" << endl;
						else
						{
							(pZone->getObjectRegistry()).registerObject(pTreasure);

							TPOINT pt = pZone->addItem(pTreasure, ZoneX, ZoneY);
							if (pt.x != -1) 
							{
								if (pItem->getItemType() == MONSTER_CORPSE)
								{
									MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);

									// 몬스터 시체에서 나온 아이템이라면 우선권 이펙트를 붙여주어야 한다.
									// 혹시라도 기존의 이펙트가 있다면 삭제해주고,
									// 새로이 이펙트를 더한다.
									const string& 	HostName 	= pMonsterCorpse->getHostName();
									int 			HostPartyID	= pMonsterCorpse->getHostPartyID();

									bool			isPrecedence = true;
									if ( pTreasure->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pTreasure->getItemType() == 3 )
									{
										isPrecedence = false;
									}

									// by sigi. 2002.12.12
									if (isPrecedence && (!HostName.empty() || HostPartyID!=0))
									{
										EffectPrecedence* pEffectPrecedence = new EffectPrecedence(pTreasure);
										pEffectPrecedence->setDeadline(100);
										pEffectPrecedence->setHostName( HostName );
										pEffectPrecedence->setHostPartyID( HostPartyID );
										EffectManager& rEffectManager = pTreasure->getEffectManager();
										rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
										rEffectManager.addEffect(pEffectPrecedence);
										pTreasure->setFlag(Effect::EFFECT_CLASS_PRECEDENCE);
									}

									// 만약 해골이라면 주위에다가 시체에서 목을 제거하라고 패킷을 날려주어야 한다.
									if (pTreasure->getItemClass() == Item::ITEM_CLASS_SKULL)
									{
										// 목 자르기~~ by sigi
										pMonsterCorpse->removeHead();

										GCRemoveCorpseHead _GCRemoveCorpseHead;
										_GCRemoveCorpseHead.setObjectID(pItem->getObjectID());
										//pZone->broadcastPacket(pt.x, pt.y, &_GCRemoveCorpseHead);
										pZone->broadcastPacket(ZoneX, ZoneY, &_GCRemoveCorpseHead); // 원래 시체 좌표 by sigi

										if ( pCreature->getPartyID() != 0 && HostPartyID == pCreature->getPartyID() )
										{
											Party* pParty = pCreature->getLocalPartyManager()->getParty( pCreature->getPartyID() );
											if ( pParty != NULL )
											{
												pParty->dissectCorpse( pCreature, pMonsterCorpse );
											}
										}
									}
								}

								// 기존의 ItemID를 그대로 유지한다.
								// ItemID가 0이면.. create()할때 다시 ItemID를 받는다.
								// by sigi. 2002.10.28
								pTreasure->create("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y, pTreasure->getItemID());
							}
							else 
							{
								SAFE_DELETE(pTreasure);
							}
						}
					}
					SAFE_DELETE(pStmt);
				} 
				catch(SQLQueryException & sqe)
				{
					SAFE_DELETE(pStmt);
					throw Error(sqe.toString());
				}
			}
			else if ( pTreasure->isFlagItem() )
			{
				// 깃발은 바로 인벤토리로 넣어준다.
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC != NULL );

				Inventory* pInventory = pPC->getInventory();
				Assert( pInventory != NULL );

				TPOINT tp;

				if ( !pInventory->getEmptySlot( pTreasure, tp ) || pCorpse->getItemType() != MONSTER_CORPSE ||
						!g_pFlagManager->getFlag( pPC, dynamic_cast<MonsterCorpse*>(pCorpse) ) )
				{
					// 도로 넣는다.
					pCorpse->addTreasure( pTreasure );

					pCorpse->setFlag( Effect::EFFECT_CLASS_FLAG_INSERT );
					EffectFlagInsert* pFlagEffect = new EffectFlagInsert(pCorpse);
					pCorpse->getEffectManager().addEffect( pFlagEffect );

					GCAddEffect gcAddEffect;
					gcAddEffect.setEffectID( Effect::EFFECT_CLASS_FLAG_INSERT );
					gcAddEffect.setObjectID( pCorpse->getObjectID() );
					gcAddEffect.setDuration( 65535 );

					pCorpse->getZone()->broadcastPacket( pCorpse->getX(), pCorpse->getY(), &gcAddEffect );

					continue;
				}

				pInventory->addItem( pTreasure, tp );

				char pField[80];
				sprintf(pField, "OwnerID='%s', Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, tp.x, tp.y);
				pTreasure->tinysave(pField);
				addSimpleCreatureEffect( pPC, Effect::EFFECT_CLASS_HAS_FLAG );

				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pTreasure, tp.x, tp.y );
				pPC->getPlayer()->sendPacket( &gcCreateItem );
			}
			else
			{
				(pZone->getObjectRegistry()).registerObject(pTreasure);

				TPOINT pt = pZone->addItem(pTreasure, ZoneX, ZoneY, true, 0, PetOID);
				if (pt.x != -1) 
				{
					if (pItem->getItemType() == MONSTER_CORPSE)
					{
						MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);

						if (dissectionRelicItem( pCorpse, pTreasure, pt ))
						{
							// pTreasure가 relicItem인 경우
						}

						treasureCount++;

						if (
							pZone->getLevelWarManager() != NULL &&
							pZone->getLevelWarManager()->isSafe( pMonsterCorpse ) )
						{
							Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( Effect::EFFECT_CLASS_KEEP_SWEEPER );
							if ( pEffect != NULL )
							{
								pEffect->setDeadline(0);

								GCRemoveEffect gcRE;
								gcRE.setObjectID( pMonsterCorpse->getObjectID() );
								gcRE.addEffectList( pEffect->getSendEffectClass() );

								pZone->broadcastPacket( pMonsterCorpse->getX(), pMonsterCorpse->getY(), &gcRE );
							}

							// 뽑으면 존에 뿌려준다.
							char safeRace[15];
							if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 0 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_SLAYER ) );
							}
							else if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 1 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_VAMPIRE ) );
							}
							else if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 2 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_OUSTERS ) );
							}
							else if ( pZone->getLevelWarManager()->getSafeIndex( pMonsterCorpse ) == 3 )
							{
								sprintf( safeRace, g_pStringPool->c_str( STRID_CENTER ) );
							}
							else 
							{
								Assert(false);
							}

							char race[15];
							if ( pCreature->isSlayer() )
							{
								sprintf( race, g_pStringPool->c_str( STRID_SLAYER ) );
							}
							else if ( pCreature->isVampire() )
							{
								sprintf( race, g_pStringPool->c_str( STRID_VAMPIRE ) );
							}
							else if ( pCreature->isOusters() )
							{
								sprintf( race, g_pStringPool->c_str( STRID_OUSTERS ) );
							}
							else
							{
								Assert(false);
							}

							const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pTreasure->getItemType()));

							char msg[100];
							sprintf( msg , g_pStringPool->c_str( STRID_PULL_OUT_SWEEPER ) ,
												safeRace,
												pSweeperInfo->getName().c_str(),
												pCreature->getName().c_str(),
												race
								   				);
							GCSystemMessage gcSystemMessage;
							gcSystemMessage.setMessage( msg );
							pZone->broadcastPacket( &gcSystemMessage );
						}

						// 몬스터 시체에서 나온 아이템이라면 우선권 이펙트를 붙여주어야 한다.
						// 혹시라도 기존의 이펙트가 있다면 삭제해주고,
						// 새로이 이펙트를 더한다.
						// 2003.2.28 기존의 이펙트가 있다면 그냥 둔다. 시체에 가 바닥에 추가될 때
						// 바닥에 있던 아이템이 들어갈 경우에 우선권 이텍트를 붙이지 않기 위해
						if (!bSlayerRelicTable && !bVampireRelicTable)
						{
							const string& 	HostName 	= pMonsterCorpse->getHostName();
							int 			HostPartyID	= pMonsterCorpse->getHostPartyID();

							// by sigi. 2002.12.12
							if ( 
								(!HostName.empty() || HostPartyID!=0)
							// by Sequoia. 2003. 2.28.
							&&	!pTreasure->isFlag(Effect::EFFECT_CLASS_PRECEDENCE)
							)
							{
								EffectPrecedence* pEffectPrecedence = new EffectPrecedence(pTreasure);
								if ( !pTreasure->isQuestItem() )
								{
									// 퀘스트 아이템은 파티원도 못 줍는다.
									pEffectPrecedence->setDeadline(100);
									pEffectPrecedence->setHostPartyID( HostPartyID );
									pEffectPrecedence->setHostName( HostName );
								}
								else
								{
									// 퀘스트 아이템은 없어질때까지 우선권이 안 없어진다.
									pEffectPrecedence->setDeadline(999999);
									pEffectPrecedence->setHostName( pMonsterCorpse->getQuestHostName() );
								}
								EffectManager& rEffectManager = pTreasure->getEffectManager();
								rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
								rEffectManager.addEffect(pEffectPrecedence);
								pTreasure->setFlag(Effect::EFFECT_CLASS_PRECEDENCE);
							}
						}

						// 만약 해골이라면 주위에다가 시체에서 목을 제거하라고 패킷을 날려주어야 한다.
						if (pTreasure->getItemClass() == Item::ITEM_CLASS_SKULL)
						{
							// 목 자르기~~ by sigi
							pMonsterCorpse->removeHead();

							GCRemoveCorpseHead _GCRemoveCorpseHead;
							_GCRemoveCorpseHead.setObjectID(pItem->getObjectID());
							//pZone->broadcastPacket(pt.x, pt.y, &_GCRemoveCorpseHead);
							pZone->broadcastPacket(ZoneX, ZoneY, &_GCRemoveCorpseHead); // 원래 시체 좌표 by sigi

							if ( pCreature->getPartyID() != 0 && pMonsterCorpse->getHostPartyID() == pCreature->getPartyID() )
							{
								Party* pParty = pCreature->getLocalPartyManager()->getParty( pCreature->getPartyID() );
								if ( pParty != NULL )
								{
									pParty->dissectCorpse( pCreature, pMonsterCorpse );
								}
							}
						}
					}

					// DB에 저장한다.
					saveDissectionItem( pCreature, pTreasure, pt.x, pt.y );
				}
				else 
				{
					SAFE_DELETE(pTreasure);
				}
			}
		}
		while ( bDissectAll );

		if (pItem->getItemType() == MONSTER_CORPSE)
		{
			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			// 펫 경험치 주자
			if ( pPacket->isPet() && treasureCount != 0 )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				GCModifyInformation gcMI;
				PetExp_t exp = computePetExp( getPCLevel( pPC ), g_pMonsterInfoManager->getMonsterInfo( pMonsterCorpse->getMonsterType() )->getLevel(), pPC->getPetInfo(), pGamePlayer );
				if ( !increasePetExp( pPC->getPetInfo(), exp, &gcMI ) )
				{
//					cout << "경험치가 바뀌었어요 : " << gcMI.toString() << endl;
					pGamePlayer->sendPacket( &gcMI );
				}
				else
				{
//					cout << "레벨없을 했대요" << endl;
					sendPetInfo( pGamePlayer, true );
				}

				addOlympicStat( pPC, 8, exp );
			}
		}
	} 
	catch (Throwable & t) 
	{
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
