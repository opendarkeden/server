//////////////////////////////////////////////////////////////////////////////
// Filename    : Creature.h
// Written By  : reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Object.h"
#include "EffectManager.h"
#include "Assert.h"
#include "Timeval.h"
#include <stdlib.h>
#include <algorithm>
#include <bitset>

//////////////////////////////////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////////////////////////////////

#define DEFAULT_SIGHT			13	// 원래시야
#define DARKNESS_SIGHT			0	// Darkness에 의한 시야
#define YELLOW_POISON_SIGHT		3	// Yellow Poison에 의한 시야
#define LIGHTNESS_SIGHT			13	// Lightness에 의한 시야
#define FLARE_SIGHT				3	// Flare에 의한 시야


const string MoveMode2String [] = 
{
	"MOVE_MODE_WALKING",
	"MOVE_MODE_FLYING",
	"MOVE_MODE_BURROWING"
};

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Zone;
class Player;
class Inventory;
class Stash;
class InventorySlot;
class Party;
class LocalPartyManager;

//////////////////////////////////////////////////////////////////////////////
// Class Creature;
//////////////////////////////////////////////////////////////////////////////

class Creature : public Object 
{
public:
	// Creature를 바로 상속받는 클래스들을 여기에 정의한다.
	enum CreatureClass 
	{ 
		CREATURE_CLASS_SLAYER = 0,	// PC Slayer
		CREATURE_CLASS_VAMPIRE,		// PC Vampire
		CREATURE_CLASS_NPC,			// NPC
		CREATURE_CLASS_MONSTER,		// NPC Slayer, NPC Vampire
		CREATURE_CLASS_OUSTERS,		// PC Ousters
		CREATURE_CLASS_MAX
	};

	// Move Mode
	enum MoveMode 
	{
		MOVE_MODE_WALKING = 0,
		MOVE_MODE_FLYING,
		MOVE_MODE_BURROWING,
		MOVE_MODE_MAX
	};

public:
    Creature(ObjectID_t objectID = 0, Player* pPlayer = NULL) throw();
    virtual ~Creature() throw (Error);

public:
	virtual ObjectClass getObjectClass() const throw() { return OBJECT_CLASS_CREATURE; }
	virtual ObjectPriority getObjectPriority() const throw(Error);
	virtual string toString() const throw() = 0;

public:
	virtual bool load() throw (InvalidProtocolException, Error) = 0; // load from DB
	virtual void save() const throw(Error) = 0; // save to DB
	
public:
	// 크리처에서 플레이어로 접근한다.
	// 현재 크리처에 대해서 isPC()를 체크해보고 true 인 경우에만 호출해야 한다.
	Player* getPlayer() const throw(Error) { Assert(m_pPlayer != NULL); return m_pPlayer; }
	void setPlayer(Player* pPlayer) throw() { m_pPlayer = pPlayer; }

public:
	virtual const string& getName() const throw() = 0;

	virtual CreatureClass getCreatureClass() const throw() = 0;
	virtual string getCreatureClassString() const throw() = 0;

	virtual Race_t getRace() const = 0;

	EffectManager* getEffectManager() const throw() { return m_pEffectManager; }

	bool isSlayer() const throw()  { return getCreatureClass() == CREATURE_CLASS_SLAYER; }
	bool isVampire() const throw() { return getCreatureClass() == CREATURE_CLASS_VAMPIRE; }
	bool isOusters() const throw() { return getCreatureClass() == CREATURE_CLASS_OUSTERS; }
	bool isNPC() const throw()     { return getCreatureClass() == CREATURE_CLASS_NPC; }
	bool isMonster() const throw() { return getCreatureClass() == CREATURE_CLASS_MONSTER; }
	bool isPC() const throw()      { return isSlayer() || isVampire() || isOusters(); }

	bool isGOD() const throw()     { return getCompetence() == GOD; }
	bool isDM() const throw()      { return getCompetence() == DM; }
	bool isHELPER() const throw()  { return getCompetence() == HELPER; }
	bool isPLAYER() const throw()  { return getCompetence() == PLAYER; }

	virtual BYTE getCompetence() const throw() { return PLAYER; }
	virtual BYTE getCompetenceShape() const throw() { return 1; }

	virtual bool isDead() const throw() = 0;
	virtual bool isAlive() const throw() = 0;
	void recoverHP(HP_t recoverAmount) throw();

	void setFlag(Effect::EffectClass Flag) throw() { m_Flag.set(Flag); }
	void removeFlag(Effect::EffectClass Flag) throw() { m_Flag.reset(Flag); }
	bool isFlag(Effect::EffectClass Flag) const throw() { return m_Flag.test(Flag); } 

	bool hasRelicItem() const;

public:
    virtual PhoneNumber_t getPhoneNumber() const throw() { return 0; }

public:
	virtual void act(const Timeval& currentTime) throw(Error) = 0; // for monster & npc

public:

	////////////////////////////////////////////////////////////
	// Creature가 가지고 있는 아이템들 역시 Zone에 등록되어야 한다. 
	// 이를 위해서는 소유 아이템들이 Zone레벨에서 visible해야 하는데, 
	// 그렇지 못하다. 그렇다고, Zone에서 Creature의 소유 아이템들을 
	// iteration 하는 메쏘드를 제공하는 것도 어색하다. 
	// 따라서, Creature에 등록 메쏘드를 두고 여기서 Zone에 접근해서 
	// 스스로를 등록하도록 한 것이다. 
	////////////////////////////////////////////////////////////
	virtual void registerObject() throw(Error) = 0;

	// 크리처에 대한 특정 좌표의 시야 상태를 리턴한다.
	VisionState getVisionState(ZoneCoord_t x, ZoneCoord_t y) throw(Error); 
	VisionState getVisionState(Coord_t x, Coord_t y, Sight_t sight) throw(Error);

	// get/set zone
	Zone* getZone() const throw() { return m_pZone; }
	void setZone(Zone* pZone) throw() { m_pZone = pZone; }

	// get/set zone id
	ZoneID_t getZoneID() const throw();
	void setZoneID(ZoneID_t zoneID) throw(Error);

	// get/set(x,y,dir)
	ZoneCoord_t getX() const throw() { return m_X; }
	void setX(ZoneCoord_t x) throw() { m_X = x; }

	ZoneCoord_t getY() const throw() { return m_Y; }
	void setY(ZoneCoord_t y) throw() { m_Y = y; }

	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }

	ZoneCoord_t getViewportWidth() const throw() { return m_ViewportWidth; }
	ZoneCoord_t getViewportUpperHeight() const throw() { return m_ViewportUpperHeight; }
	ZoneCoord_t getViewportLowerHeight() const throw() { return m_ViewportLowerHeight; }

	////////////////////////////////////////////////////////////
	// *CAUTION*
	// 쿼리 결과를 저장할 때, 2개 이상의 값을 동시에 지정하는 set 메쏘드는 사용하지 말 것!
	//(함수 호출이 뒤에서 부터 이루어진다는 사실을 유념할 것!)
	//  ex> setXY(pResult->getInt(++i), pResult->getInt(++i)); 는 실제로 setXY(y,x)
	//      를 실행하게 된당... -_-;
	////////////////////////////////////////////////////////////
	void setXY(ZoneCoord_t x, ZoneCoord_t y) throw() { m_X = x; m_Y = y; }
	void setXYDir(ZoneCoord_t x, ZoneCoord_t y, Dir_t dir) throw() { m_X = x; m_Y = y; m_Dir = dir; }

	//(nx,ny)로 움직일 수 있는가?
	bool canMove(ZoneCoord_t nx, ZoneCoord_t ny) const throw(Error);
	bool isBlockedByCreature(ZoneCoord_t nx , ZoneCoord_t ny) const throw(Error);

	// get/set sight level
	Sight_t getSight() const throw() { return m_Sight; }
	void setSight(Sight_t sight) throw(Error) { m_Sight = sight; Assert(m_Sight <= maxSight); }

	virtual Sight_t getEffectedSight() throw();

	// get/set/test move mode
	MoveMode getMoveMode() const throw() { return m_MoveMode; }
	void setMoveMode(MoveMode moveMode) throw() { m_MoveMode = moveMode; }

	bool isWalking() const throw() { return m_MoveMode == MOVE_MODE_WALKING; }
	bool isFlying() const throw() { return m_MoveMode == MOVE_MODE_FLYING; }
	bool isBurrowing() const throw() { return m_MoveMode == MOVE_MODE_BURROWING; }
	
	// get distance
	Distance_t getDistance(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2) const throw();

	// P(x1,y1)과 나의 위치사이의 거리를 측정한다.
	Distance_t getDistance(ZoneCoord_t x1, ZoneCoord_t y1) const throw();

	// get/set EffectInfo
	virtual EffectInfo* getEffectInfo() const throw() { return m_pEffectManager->getEffectInfo(); }

public :
	// get/set zone
	Zone* getNewZone() const throw() { return m_pNewZone; }
	void setNewZone(Zone* pZone) throw() { m_pNewZone = pZone; }

	// get/set zone id
	ZoneID_t getNewZoneID() const throw();
	//void setNewZoneID(ZoneID_t zoneID) throw(Error);

	// get/set(x,y,dir)
	ZoneCoord_t getNewX() const throw() { return m_NewX; }
	void setNewX(ZoneCoord_t x) throw() { m_NewX = x; }

	ZoneCoord_t getNewY() const throw() { return m_NewY; }
	void setNewY(ZoneCoord_t y) throw() { m_NewY = y; }

	void setNewXY(ZoneCoord_t x, ZoneCoord_t y) throw() { m_NewX = x; m_NewY = y; }

public:
	bool isEffect(Effect::EffectClass EClass) throw (Error);
	void deleteEffect(Effect::EffectClass EClass) throw (Error);
	Effect* findEffect(Effect::EffectClass EClass) const throw (Error);
	void addEffect(Effect* pEffect) throw (Error);

public:
	virtual Level_t getLevel() const throw() = 0;
	virtual Steal_t getHPStealAmount(void) const { return 0; }
	virtual void setHPStealAmount(Steal_t steal) {}

	virtual Steal_t getMPStealAmount(void) const { return 0; }
	virtual void setMPStealAmount(Steal_t steal) {}

	virtual Steal_t getHPStealRatio(void) const { return 0; }
	virtual void setHPStealRatio(Steal_t steal) {}

	virtual Steal_t getMPStealRatio(void) const { return 0; }
	virtual void setMPStealRatio(Steal_t steal) {}

	virtual Regen_t getHPRegen(void) const { return 0; }
	virtual void setHPRegen(Regen_t regen) {}

	virtual Regen_t getMPRegen(void) const { return 0; }
	virtual void setMPRegen(Regen_t regen) {}

	virtual Luck_t getLuck(void) const { return 0; }
	virtual void setLuck(Luck_t luck) {}

	virtual int getCriticalRatio(void) const { return 0; }
	virtual void setCriticalRatio(int ratio) { }

	int getPartyID(void) const { return m_PartyID; }
	void setPartyID(int ID) { m_PartyID = ID; }

	LocalPartyManager* getLocalPartyManager(void) const throw();

	virtual ClanType_t getClanType(void) const { return 0; }
	virtual void setClanType(ClanType_t clan) { }

	Resist_t getResist(uint domain) { return m_Resist[domain]; }
	void setResist(uint domain, Resist_t value) { m_Resist[domain] = value; }

	ObjectID_t getLastTarget() { return m_LastTarget; }
	virtual void setLastTarget(ObjectID_t value) { m_LastTarget = value; }

protected:
	Player*                          m_pPlayer;                  // Player 에 대한 포인터(Mob 과 NPC 일 경우 NULL)
	MoveMode                         m_MoveMode;                 // Move Mode
	Zone*                            m_pZone;                    // 현재 존에 대한 포인터
	ZoneCoord_t                      m_X;                        // 존 x 좌표
	ZoneCoord_t                      m_Y;                        // 존 y 좌표
	Dir_t                            m_Dir;                      // 현재 방향
	ZoneCoord_t                      m_ViewportWidth;            // 뷰 포트 
	ZoneCoord_t                      m_ViewportUpperHeight;      // 뷰 포트
	ZoneCoord_t                      m_ViewportLowerHeight;      // 뷰 포트
	EffectManager*                   m_pEffectManager;           // effect manager point
	bitset<Effect::EFFECT_CLASS_MAX> m_Flag;                     // effect flag
	Sight_t                          m_Sight;                    // current sight
	int                              m_PartyID;                  // partyid
	Resist_t                         m_Resist[MAGIC_DOMAIN_MAX]; // 마법 저항력

	// 새로 들어갈 존, 부활할 존. by sigi. 2002.5.11
	Zone*                            m_pNewZone;           // 현재 존에 대한 포인터
	ZoneCoord_t                      m_NewX;               // 존 x 좌표
	ZoneCoord_t                      m_NewY;               // 존 y 좌표

	// 디버그용
	CreatureClass 					 m_CClass;
	string							 m_Owner;
	bool							 m_bDeriveDestructed;
	int								 m_Value;

	ObjectID_t						 m_LastTarget;

public:
	void setValue(int value) { m_Value = value; }
};

#endif
