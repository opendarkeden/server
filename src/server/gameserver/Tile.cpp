//////////////////////////////////////////////////////////////////////////////
// FileName 	: Tile.cpp
// Written By	: reiot@ewestsoft.com
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include "Tile.h"
#include "Assert.h"
#include "Player.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Sector.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "StringStream.h"
#include <algorithm>

#include "EffectYellowPoison.h"
#include "EffectGreenPoison.h"
#include "EffectDarkness.h"
#include "EffectTryingPosition.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Tile::Tile (WORD wFlags , WORD wOption)
    throw ()
{
	__BEGIN_TRY

	m_wFlags = wFlags;
	m_wOption = wOption;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
Tile::~Tile ()
	throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while (!m_Objects.empty()) 
	{
		Object* pObj = m_Objects.front();
		SAFE_DELETE(pObj);
		m_Objects.pop_front();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 크리처를 리스트에 추가한다. 
//
// return값은 그냥 이동인가(true), Portal을 activate 시킨건가(false)에 대한 값
//////////////////////////////////////////////////////////////////////////////
bool Tile::addCreature (Creature* pCreature, bool bCheckEffect, bool bCheckPortal) 
	throw (GameException , DuplicatedException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	// 크리처의 MoveMode { WALKING | FLYING | BURROWING }을 가지고 온다.
	Creature::MoveMode mode = pCreature->getMoveMode();	

	// 추가하려는 크리처와 같은 MoveMode에 해당하는 곳이 blocking되지 않아야 한다.
	Assert(! isBlocked(mode));

	// 추가하려는 크리처와 같은 MoveMode를 가진 크리처가 타일내에 없어야 한다.
	//Assert(! hasCreature(mode));
	if (hasCreature(mode))
	{
		StringStream msg;

		Creature* pWalkingCreature = getCreature( Creature::MOVE_MODE_WALKING );
		Creature* pFlyingCreature = getCreature( Creature::MOVE_MODE_FLYING );
		Creature* pBurrowingCreature = getCreature( Creature::MOVE_MODE_BURROWING );
		Item* pItem = getItem();

		msg << "TileInfo: ";

		if (pWalkingCreature!=NULL) 
		{
			msg << "Walking(" << pWalkingCreature->toString().c_str() << ") ";
		}
		if (pFlyingCreature!=NULL) 
		{
			msg << "Flying(" << pFlyingCreature->toString().c_str() << ") ";
		}
		if (pBurrowingCreature!=NULL) 
		{
			msg << "Burrowing(" << pBurrowingCreature->toString().c_str() << ") ";
		}
		if (pItem!=NULL) 
		{
			msg << "Item(" << pItem->toString().c_str() << ") ";
		}

		filelog("tileError.txt", "%s", msg.toString().c_str());

		Assert(false);
	}

	// 크리처를 리스트에 집어넣는다.
	addObject(pCreature);

	// 해당하는 크리처 플래그를 켠다.
	FLAG_SET(m_wFlags , TILE_WALKING_CREATURE + mode);

	// 해당하는 blocking 플래그를 켠다.
	FLAG_SET(m_wFlags , TILE_GROUND_BLOCKED + mode);

	Assert(isBlocked(mode));
	Assert(hasCreature(mode));

	if (bCheckPortal)
	{
		// 만약 포탈이 있으면서, 크리처가 PC인 경우.. (몬스터와 NPC는 포탈 이동을 하지 않는다.)
		if (hasPortal() && pCreature->isPC()) 
		{
			Portal* pPortal = getPortal();
			if ( pPortal->activate( pCreature ) ) return false;

/*			if (pCreature->isSlayer()) 
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

				if (pPortal->getPortalClass() != PORTAL_CLASS_MULTI) 
				{
					if (pPortal->getObjectType() == PORTAL_NORMAL || pPortal->getObjectType() == PORTAL_SLAYER 
							|| pPortal->getObjectType() == PORTAL_GUILD || pPortal->getObjectType() == PORTAL_BATTLE)
					{
						// 트리거드 포탈일 경우에는 트리거 조건을 만족시켰을 때만, 
						// portal exception을 던진다.
						if (pPortal->getPortalClass() == PORTAL_CLASS_TRIGGERED)
						{
							if (pPortal->activate(pSlayer)) 
							{
								//throw PortalException();
								// PortalException제거. by sigi. 2002.5.6
								return false;
							}
						}

						else if (!(pSlayer->hasRideMotorcycle() && pPortal->getObjectType() == PORTAL_SLAYER)) 
						{
							if (pPortal->activate(pSlayer))
							{
								//throw PortalException();
								// PortalException제거. by sigi. 2002.5.6
								return false;
							}
						}
					}
				}
			} 
			else if (pCreature->isVampire()) 
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

				if (pPortal->getPortalClass() != PORTAL_CLASS_MULTI) 
				{
					if (pPortal->getObjectType() == PORTAL_NORMAL || pPortal->getObjectType() == PORTAL_VAMPIRE
							|| pPortal->getObjectType() == PORTAL_GUILD || pPortal->getObjectType() == PORTAL_BATTLE)
					{
						// 트리거드 포탈일 경우에는 트리거 조건을 만족시켰을 때만,
						// portal exception을 던진다.
						if (pPortal->getPortalClass() == PORTAL_CLASS_TRIGGERED)
						{
							if (pPortal->activate(pVampire))
							{
								//throw PortalException();
								// PortalException제거. by sigi. 2002.5.6
								return false;
							}
						}
						else
						{
							if (pPortal->activate(pVampire))
							{
								//throw PortalException();
								// PortalException제거. by sigi. 2002.5.6
								return false;
							}
						}
					}
				}
			}
			else if (pCreature->isOusters()) 
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

				if (pPortal->getPortalClass() != PORTAL_CLASS_MULTI) 
				{
					if (pPortal->getObjectType() == PORTAL_NORMAL || pPortal->getObjectType() == PORTAL_OUSTERS
							|| pPortal->getObjectType() == PORTAL_GUILD || pPortal->getObjectType() == PORTAL_BATTLE)
					{
						// 트리거드 포탈일 경우에는 트리거 조건을 만족시켰을 때만,
						// portal exception을 던진다.
						if (pPortal->getPortalClass() == PORTAL_CLASS_TRIGGERED)
						{
							if (pPortal->activate(pOusters))
							{
								//throw PortalException();
								// PortalException제거. by sigi. 2002.5.6
								return false;
							}
						}
						else
						{
							if (pPortal->activate(pOusters))
							{
								//throw PortalException();
								// PortalException제거. by sigi. 2002.5.6
								return false;
							}
						}
					}
				}
			}*/
		}
	}

	// effect 검사.
	if (hasEffect())
	{
		if (bCheckEffect)
		{
			EffectGreenPoison* pEGP = (EffectGreenPoison*)getEffect(Effect::EFFECT_CLASS_GREEN_POISON);
			//if (pCreature->isSlayer() && (pEGP = (EffectGreenPoison*)getEffect(Effect::EFFECT_CLASS_GREEN_POISON)))
			if (pEGP != NULL)
			{
				pEGP->affectCreature(pCreature, true);
			}
			EffectYellowPoison* pEYP = NULL;
			if ( (pCreature->isSlayer() || pCreature->isOusters() ) && (pEYP = (EffectYellowPoison*)getEffect(Effect::EFFECT_CLASS_YELLOW_POISON)))
			{
				pEYP->affectCreature(pCreature, true);
			}
			// 무조건 적용되야 되는 거면 적용시킨다
			else if ( (pEYP = (EffectYellowPoison*)getEffect(Effect::EFFECT_CLASS_YELLOW_POISON)) && pEYP->isForce() )
			{
				pEYP->affectCreature(pCreature, true);
			}

			EffectDarkness* pDarkness = NULL;
			if (pCreature->isSlayer() && (pDarkness = (EffectDarkness*)getEffect(Effect::EFFECT_CLASS_DARKNESS)))
			{
				pDarkness->affectObject(pCreature, true);
			}

			EffectTryingPosition* pTP;
			if ( pCreature->isPC() && (pTP = dynamic_cast<EffectTryingPosition*>(getEffect(Effect::EFFECT_CLASS_TRYING_POSITION))) )
			{
				pTP->affect( pCreature );
			}
		}
	}
	else
	{
		if ( ( pCreature->isOusters() || pCreature->isSlayer() ) && pCreature->isFlag(Effect::EFFECT_CLASS_DARKNESS))
		{
			pCreature->removeFlag(Effect::EFFECT_CLASS_DARKNESS);
		}
	}

	// PortalException제거. by sigi. 2002.5.6
	return true;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 ID를 가진 크리처를 리스트에서 삭제한다.
// 최적화할 필요가 있다. (검색 + 삭제)
//////////////////////////////////////////////////////////////
void Tile::deleteCreature (ObjectID_t creatureID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try 
	{
		// 현재 크리처로 인해 어딘가가 한군데 blocking 되어야 한다.
		Assert(isGroundBlocked() || isAirBlocked() || isUndergroundBlocked());

		// 현재 크리처가 어딘가에 존재해야 한다.
		//Assert(hasWalkingCreature() || hasFlyingCreature() || hasBurrowingCreature());
		Assert(hasCreature());	// by sigi. 2002.5.8

		Creature* pCreature = dynamic_cast<Creature*>(getObject(creatureID));

		// 이펙트가 존재할 경우, 크리처에게서 없엔다.
		/*
		if (hasEffect()) 
		{
			Effect* pEffect = getEffect();
			pEffect->unaffect(pCreature);
		}
		*/

		// NoSuch제거. by sigi. 2002.5.2
		if (pCreature==NULL)
		{
			return;
		}

		if ( hasEffect() )
		{
			EffectTryingPosition* pTP;
			if ( pCreature->isPC() && (pTP = dynamic_cast<EffectTryingPosition*>(getEffect(Effect::EFFECT_CLASS_TRYING_POSITION))) )
			{
				pTP->unaffect( pCreature );
			}
		}


		// 노드를 삭제한다.
		deleteObject(creatureID);

		// 해당하는 크리처 플래그를 끈다.
		FLAG_CLEAR(m_wFlags , TILE_WALKING_CREATURE + pCreature->getMoveMode());
		
		// 해당하는 blocking 플래그를 끈다.
		FLAG_CLEAR(m_wFlags , TILE_GROUND_BLOCKED + pCreature->getMoveMode());
	} 
	catch (Throwable & t) 
	{
		//cerr << "Delete Creature 지롱.." << endl;
		//cerr << t.toString() << endl;
		filelog("tileError.txt", "Tile::deleteCreature - %s", t.toString().c_str());
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 위치(행위)의 크리처를 리스트에서 삭제한다.
//////////////////////////////////////////////////////////////
void Tile::deleteCreature (Creature::MoveMode mode) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	// 현재 크리처로 인해 blocking 되어야 한다.
	Assert(isBlocked(mode));

	// 현재 크리처가 존재해야 한다.
	Assert(hasCreature(mode));

	if ( hasEffect() )
	{
		EffectTryingPosition* pTP;
		Creature* pCreature = getCreature( mode );
		if ( pCreature != NULL && pCreature->isPC() && (pTP = dynamic_cast<EffectTryingPosition*>(getEffect(Effect::EFFECT_CLASS_TRYING_POSITION))) )
		{
			pTP->unaffect( pCreature );
		}
	}

	// 객체를 삭제한다.
	deleteObject(OBJECT_PRIORITY_WALKING_CREATURE + mode);

	// 해당하는 크리처 플래그를 끈다.
	FLAG_CLEAR(m_wFlags , TILE_WALKING_CREATURE + mode);
	
	// 해당하는 blocking 플래그를 끈다.
	FLAG_CLEAR(m_wFlags , TILE_GROUND_BLOCKED + mode);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 ID를 가진 크리처를 리턴한다.
//////////////////////////////////////////////////////////////
Creature* Tile::getCreature (ObjectID_t creatureID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	Assert(hasWalkingCreature() || hasFlyingCreature() || hasBurrowingCreature());

	return (Creature*)(getObject(creatureID));

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 위치(행위)의 크리처를 리턴한다.
//////////////////////////////////////////////////////////////
Creature* Tile::getCreature (Creature::MoveMode mode) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	Assert(hasCreature(mode));
	return (Creature*)getObject(ObjectPriority(OBJECT_PRIORITY_WALKING_CREATURE + mode));

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 아이템을 타일에 추가한다. 이미 아이템이 타일에 있다면 Dup 예외를 던진다.
// (아이템은 타일당 하나다.)
//////////////////////////////////////////////////////////////
void Tile::addItem (Item* pItem) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	Assert(pItem != NULL);

	Assert(! hasItem());
	Assert(! hasBuilding());
	Assert(! hasObstacle());
	Assert(! hasPortal());
/*	
	EffectDarkness* pDarkness;
	if ((pDarkness = getEffect(Effect::EFFECT_CLASS_DARKNESS)))
	{
		pDarkness->affectObject(pItem, false);
	}
*/
	addObject(pItem);

	FLAG_SET(m_wFlags , TILE_ITEM);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 아이템을 타일에서 삭제한다. 어차피 하나밖에 없으므로 특별히 지정할 필요가 없다.
//////////////////////////////////////////////////////////////
void Tile::deleteItem () 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//Assert(hasItem());
	if (!hasItem())
	{
		//cerr << "Tile::hasItem() : 아이템이 없습니다." << endl;
		return;
	}

	deleteObject(OBJECT_PRIORITY_ITEM);

	FLAG_CLEAR(m_wFlags , TILE_ITEM);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 타일의 아이템을 리턴한다. 어차피 하나밖에 없으므로 특별히 지정할 필요가 없다.
//////////////////////////////////////////////////////////////
Item* Tile::getItem () 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	//Assert(hasItem());
	if (!hasItem()) return NULL;

	return (Item*)getObject(OBJECT_PRIORITY_ITEM);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 장애물을 타일에 추가한다.
//////////////////////////////////////////////////////////////
void Tile::addObstacle (Obstacle* pObstacle) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	Assert(pObstacle != NULL);

	// must be empty tile...
	Assert(! hasWalkingCreature());
	Assert(! hasFlyingCreature());
	Assert(! hasBurrowingCreature());
	Assert(! hasEffect());
	Assert(! hasObstacle());
	Assert(! hasItem());
	Assert(! hasBuilding());
	Assert(! hasPortal());
	Assert(! isTerrain());

	FLAG_SET(m_wFlags , TILE_OBSTACLE);

	addObject(pObstacle);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 장애물을 타일에서 삭제한다. 어차피 하나밖에 없으므로 특별히 지정할 필요가 없다.
//////////////////////////////////////////////////////////////
void Tile::deleteObstacle () 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	Assert(hasObstacle());

	deleteObject(OBJECT_PRIORITY_OBSTACLE);

	FLAG_CLEAR(m_wFlags , TILE_OBSTACLE);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 타일의 장애물을 리턴한다. 어차피 하나밖에 없으므로 특별히 지정할 필요가 없다.
//////////////////////////////////////////////////////////////
Obstacle* Tile::getObstacle () 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	Assert(hasObstacle());

	return (Obstacle*)getObject(OBJECT_PRIORITY_OBSTACLE);

	__END_CATCH
}

bool Tile::canAddEffect() 
	throw(Error)
{
	return !(hasObstacle() || hasBuilding() || hasPortal());
}

//////////////////////////////////////////////////////////////
// 마법 효과를 타일에 추가한다.
// 현재 타일에 크리처나 아이템이 존재한다면, 마법의 효과를 그
// 크리처나 아이템에 부여한다.
// 중복되는 마법에 대한 정책이 필요하다.... (같은 마법을 한자리에..)
//////////////////////////////////////////////////////////////
void Tile::addEffect (Effect* pEffect) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	Assert(pEffect != NULL);

	Assert(! hasObstacle());
	Assert(! hasBuilding());
	Assert(! hasPortal());

	addObject(pEffect);
	
	// 여기서 현재 타일에 속한 크리처나 아이템에게 효과를 미친다.
	// pEffect->affectTile();

	FLAG_SET(m_wFlags , TILE_EFFECT);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 ID를 가진 마법 효과를 타일에서 삭제한다. 
// 동시에 현재 타일의 크리처나 아이템에게 부여된 마법 효과 역시
// 삭제해야 한다.
// 마법 효과를 삭제할 때, 다른 마법이 남아있다면 TILE_EFFECT 
// 플래그를 끄지 않아야 한다!
// 최적화할 필요성이 있다.. (search - unaffect - flag clear를 한번에..)
//////////////////////////////////////////////////////////////
void Tile::deleteEffect (ObjectID_t effectID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	if ( !hasEffect() )
	{
		filelog("TileEffectBug.txt", "there is no effect with effect id %d", effectID);
		return;
	}
//	Assert(hasEffect());

	// 마법 효과가 하나 이상일 수 있으므로, deleteObject(OBJECT_PRIORITY_EFFECT) 을 사용할 수 없다.
	deleteObject(effectID);

	// 현재 타일에 미친 영향을 모두 날린다. 즉 크리처와 아이템에 부여된
	// 마법 효과를 복구해야 한다.
	// effect->unaffectTile();

	// 다른 마법이 없다면 플래그를 끈다.
	/*
	try 
	{
		getObject(OBJECT_PRIORITY_EFFECT);	
	} 
	catch (NoSuchElementException) 
	{
		// 마법이 없으므로 끈다.
		FLAG_CLEAR(m_wFlags , TILE_EFFECT);
	}
	*/

	// NoSuch제거. by sigi. 2002.5.2
	if (getObject(OBJECT_PRIORITY_EFFECT)==NULL)
	{
		FLAG_CLEAR(m_wFlags , TILE_EFFECT);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 ID를 가진 마법 효과를 리턴한다.
//////////////////////////////////////////////////////////////
Effect* Tile::getEffect (ObjectID_t effectID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	if (hasEffect() == false) return NULL;
	return (Effect*)getObject(effectID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// EffectClass를 가진 마법 효과를 리턴한다.
//////////////////////////////////////////////////////////////
Effect* Tile::getEffect (Effect::EffectClass effectClass) 
	throw (Error)
{
	__BEGIN_TRY

	if (hasEffect())
	{
		for (slist<Object*>::const_iterator itr = m_Objects.begin() ; 
			itr != m_Objects.end() ; 
			itr ++) 
		{
			Effect* pEffect = NULL;
			if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_EFFECT) 
			{
				if (effectClass == ((Effect*)(*itr))->getEffectClass()) 
				{
					// 그런 id 를 가진 객체를 발견한 경우
					pEffect = dynamic_cast<Effect*>(*itr);
					return pEffect;
				}
			}
		}
	}

	return NULL;

	__END_CATCH
}



//////////////////////////////////////////////////////////////
// 현재 타일을 건물로 설정한다. 
//////////////////////////////////////////////////////////////
void Tile::addBuilding (BuildingID_t buildingID) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(! hasWalkingCreature());
	Assert(! hasFlyingCreature());
	Assert(! hasBurrowingCreature());
	Assert(! hasEffect());
	Assert(! hasObstacle());
	Assert(! hasItem());
	Assert(! hasBuilding());
	Assert(! hasPortal());
	Assert(! isTerrain());

	FLAG_SET(m_wFlags , TILE_BUILDING);

	m_wOption = buildingID;

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 현재 타일에서 건물을 삭제한다. 어차피 하나이므로 특별히 지정할 필요는 없다.
//////////////////////////////////////////////////////////////
void Tile::deleteBuilding () 
	throw (Error)
{
	__BEGIN_TRY

	Assert(hasBuilding());

	FLAG_CLEAR(m_wFlags , TILE_BUILDING);

	m_wOption = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 현재 타일에 해당하는 건물 아이디를 리턴한다.
//////////////////////////////////////////////////////////////
BuildingID_t Tile::getBuilding () const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(hasBuilding());

	return m_wOption;

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 포탈을 타일에 추가한다.
//////////////////////////////////////////////////////////////
void Tile::addPortal (Portal* pPortal) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPortal != NULL);

	// 하늘을 날아다니는 크리처나 땅속에 숨어있는 크리처는 포탈의 영향을 받을 것인가? 말 것인가?
	// 암튼 아무 것도 없는 빈 타일이어야 한다!!!!!!!!!!!!!!!!!!!!
	Assert(!hasWalkingCreature());
	Assert(!hasFlyingCreature());
	Assert(!hasBurrowingCreature());
	Assert(!hasEffect());
	Assert(!hasObstacle());
	Assert(!hasItem());
	Assert(!hasBuilding());
	Assert(!hasPortal());
	Assert(!isTerrain());

	addObject(pPortal);

	FLAG_SET(m_wFlags , TILE_PORTAL);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 포탈을 타일에서 삭제한다. 어차피 하나이므로 특별히 지정할 필요가 없다.
//////////////////////////////////////////////////////////////
void Tile::deletePortal () 
	throw (Error)
{
	__BEGIN_TRY

	Assert(hasPortal());

	deleteObject(OBJECT_PRIORITY_PORTAL);

	FLAG_CLEAR(m_wFlags , TILE_PORTAL);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 포탈 객체를 리턴한다.
//////////////////////////////////////////////////////////////
Portal* Tile::getPortal () const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(hasPortal());

	return (Portal*)getObject(OBJECT_PRIORITY_PORTAL);

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// terrain 을 타일에 추가한다. 
//////////////////////////////////////////////////////////////
void Tile::addTerrain (TerrainID_t terrainID) 
	throw (Error)
{
	__BEGIN_TRY

	// 현재 타일에 m_wOption 을 사용하는 객체인 장애물, 건물, 포탈
	// 등이 있다면 에러당.. 즉 상위에서 체크해줘야 한다.
	Assert(! hasObstacle());
	Assert(! hasBuilding());
	Assert(! hasPortal());

	// Terrain 플래그를 켠다.
	FLAG_SET(m_wFlags , TILE_TERRAIN);

	// 옵션을 Terrain ID 로 설정한다.
	m_wOption = terrainID;

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// terrain 을 타일에서 삭제한다.
//////////////////////////////////////////////////////////////
void Tile::deleteTerrain () 
	throw (Error)
{
	__BEGIN_TRY

	Assert(isTerrain());

	// Terrain 플래그를 켠다.
	FLAG_CLEAR(m_wFlags , TILE_TERRAIN);

	// 옵션을 클리어한다.
	m_wOption = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// terrain 아이디를 리턴한다.
//////////////////////////////////////////////////////////////
TerrainID_t Tile::getTerrain () const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(isTerrain());

	return m_wOption;

	__END_CATCH
}


//////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////
string Tile::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Tile(";
	msg << "Flag:" << m_wFlags;
	msg << "\nObjects:";
	slist<Object*>::const_iterator itr = m_Objects.begin();
	for (; itr != m_Objects.end(); itr++)
	{
		msg << (*itr)->toString() << "\n";
	}

	msg << "TileOption:" << (int)m_wOption;
	msg << ")";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// add object into object list
//////////////////////////////////////////////////////////////
void Tile::addObject (Object* pObject) 
	throw (DuplicatedException)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pObject != NULL);
	Assert(pObject->getObjectID()!= 0);

	slist<Object*>::iterator before = m_Objects.end();
	slist<Object*>::iterator current = m_Objects.begin();

	/*
	// 우선 섹터에 집어넣는다.
	m_pSector->addObject(pObject);
	*/

	for (; current != m_Objects.end() ; before = current , current ++) 
	{
		// 객체 리스트는 내림차순으로 정렬되어 있다.
		// 따라서, 삽입하려는 객체의 ObjectPriority가 현재 iterator가 가리키는
		// 객체의 ObjectPriority보다 작을 때까지 루프를 돌려야 한다.

		if (pObject->getObjectPriority() < (*current)->getObjectPriority()) 
		{
			if (before == m_Objects.end()) 
			{
				// 객체의 타일 우선순위가 가장 작으므로 리스트의 맨 앞에 넣는다.
				m_Objects.push_front(pObject);
			} 
			else 
			{
				// 리스트의 가운데에 넣는다.
				// O(1) insertion
				m_Objects.insert_after(before , pObject);
			}
			return;
		} 
		else if (pObject->getObjectPriority() == (*current)->getObjectPriority()) 
		{
			// effect는 중복될 수 있다.
			if (pObject->getObjectPriority() == OBJECT_PRIORITY_EFFECT)
			{
				if (before == m_Objects.end())
				{
					m_Objects.push_front(pObject);
				}
				else
				{
					m_Objects.insert_after(before , pObject);
				}
				return;
			}
			else
			{	
				cerr << toString() << endl;
				cerr << "겹쳐진 tile priority 값은 = " << (int)pObject->getObjectPriority() << endl;
				cerr << "플래그 값은 = " << m_wFlags << endl;
				filelog("TILEBUG.log", "%s", toString().c_str());
				throw DuplicatedException("tile priority duplicated");
			}
		}
	}

	// 위의 루프에서 적절한 위치를 찾지 못했을 경우는 
	// (1) 리스트에 객체가 하나도 없는 경우, 
	// (2) 리스트의 맨 뒤에 넣어야 되는 경우.. 가 있다.
	if (current == m_Objects.end()) 
	{
		if (before == m_Objects.end())
		{
			// 리스트가 비어 있기 때문에, 리스트의 맨 앞에 넣는다.
			m_Objects.push_front(pObject);
		}
		else
		{
			// OBJECT_PRIORITY가 가장 큰 객체이므로, 리스트의 맨 뒤에 넣는다.
			// O(1) insertion
			m_Objects.insert_after(before , pObject);
		}
	}

	__END_DEBUG
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////
// Delete object from object list
//////////////////////////////////////////////////////////////
void Tile::deleteObject (ObjectID_t objectID) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY

	/*
	// 먼저 섹터에서 삭제한다.
	m_pSector->deleteObject(objectID);
	*/

	slist<Object*>::iterator before = m_Objects.end();
	slist<Object*>::iterator current = m_Objects.begin();

	int i = 0;
	for (; current != m_Objects.end() ; before = current++) 
	{
		if (objectID == (*current)->getObjectID()) 
		{
			// 그런 id 를 가진 객체를 발견한 경우
			if (before == m_Objects.end()) 
			{
				// Delete first node
				m_Objects.pop_front();
			}
			else 
			{
				// O(1) deletion
				m_Objects.erase_after(before);
			}

			return;
		}
		i++;
	}

	Assert(false);
	
	/*
	if (before == m_Objects.end())
	{
		cout << objectID << "아무것두 없당" << endl;
	}
	else
	{
		cout << objectID << " " << (*before)->getObjectID() << endl;
	}
	*/

	// NoSuch제거. by sigi. 2002.5.2
	//throw NoSuchElementException("invalid object id");

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////
// 특정 Tile Priority를 가진 객체를 삭제한다.
//////////////////////////////////////////////////////////////
void Tile::deleteObject (ObjectPriority objectPriority) 
	throw (NoSuchElementException)
{
	__BEGIN_TRY

	slist<Object*>::iterator before = m_Objects.end();
	slist<Object*>::iterator current = m_Objects.begin() ;

	/*
	// 먼저 섹터에서 삭제하자...
	Object* pObject = getObject(objectPriority);
	m_pSector->deleteObject(pObject->getObjectID());
	*/

	for (; current != m_Objects.end() ; before = current ++) 
	{
		if (objectPriority == (*current)->getObjectPriority()) 
		{
			// 그런 tp 를 가진 객체를 발견한 경우
			if (before == m_Objects.end()) 
			{
				// Delete first node
				m_Objects.pop_front();
			} 
			else 
			{
				// O(1) deletion
				m_Objects.erase_after(before);
			}

			return;
		} 
		else if (objectPriority < (*current)->getObjectPriority()) 
		{
			// 리스트가 객체의 tp 의 내림차순으로 정렬되어 있으므로,
			// 찾고자 하는 객체의 tp 보다 현재 iterator의 tp 가 크다면
			// 그런 id 를 가진 객체는 존재하지 않는다.
			// ex> [0] - [3] - [4] 에서 [3]을 iterator가 가리킬 때, 현재 tp 가 2인 경우
			break;
		}
	}

	// NoSuch제거. by sigi. 2002.5.2
	//throw NoSuchElementException("invalid object priority");

	__END_CATCH
}
//////////////////////////////////////////////////////////////
// 현재 타일에서 특정 ID를 가진 오브젝트를 리턴한다.
// 리스트를 모두 검색해야 한다.
//////////////////////////////////////////////////////////////
Object* Tile::getObject (ObjectID_t objectID) const
	throw (NoSuchElementException)
{
	__BEGIN_TRY

	for (slist<Object*>::const_iterator itr = m_Objects.begin(); itr != m_Objects.end() ; itr ++) 
	{
		if (objectID == (*itr)->getObjectID()) 
		{
			// 그런 id 를 가진 객체를 발견한 경우
			return *itr;
		}
	}

	// 그런 id 를 가진 객체는 존재하지 않는다.
	// NoSuch제거. by sigi. 2002.5.2
	//throw NoSuchElementException("invalid object id");

	// warning 때문에.. - -;
	return NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////
// 특정 Tile Priority 를 가진 객체를 리턴한다.
//////////////////////////////////////////////////////////////
Object* Tile::getObject (ObjectPriority objectPriority) const
	throw (NoSuchElementException)
{
	__BEGIN_TRY

	for (slist<Object*>::const_iterator itr = m_Objects.begin() ; itr != m_Objects.end() ; itr ++) 
	{
		if (objectPriority == (*itr)->getObjectPriority()) 
		{
			// 그런 id 를 가진 객체를 발견한 경우
			return *itr;
		} 
		else if (objectPriority < (*itr)->getObjectPriority()) 
		{
			// 리스트가 객체의 tp 의 내림차순으로 정렬되어 있으므로,
			// 찾고자 하는 객체의 tp 보다 현재 iterator의 tp 가 크다면
			// 그런 id 를 가진 객체는 존재하지 않는다.
			// ex> [0] - [3] - [4] 에서 [3]을 iterator가 가리킬 때, 현재 tp 가 2인 경우
			break;
		}
	}

	// NoSuch제거. by sigi. 2002.5.2
	//throw NoSuchElementException("invalid tile priority");
	return NULL;

	__END_CATCH
}
