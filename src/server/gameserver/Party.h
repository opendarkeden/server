//////////////////////////////////////////////////////////////////////////////
// Filename    : Party.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PARTY_H__
#define __PARTY_H__

#include "Creature.h"
#include "Mutex.h"
#include "ModifyInfo.h"
#include "Mutex.h"
#include <unordered_map>
#include <list>

// 파티의 최대 크기
const int PARTY_MAX_SIZE = 6;

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Packet;
class GCPartyJoined;
class Creature;
class MonsterCorpse;

//////////////////////////////////////////////////////////////////////////////
// class PartyInviteInfo
//////////////////////////////////////////////////////////////////////////////

class PartyInviteInfo
{
public:
	PartyInviteInfo() { m_HostName = ""; m_GuestName = ""; }
	~PartyInviteInfo() {}

public:
	string getHostName(void) const { return m_HostName; }
	void setHostName(const string& name) { m_HostName = name; }

	string getGuestName(void) const { return m_GuestName; }
	void setGuestName(const string& name) { m_GuestName = name; }

public:
	string toString(void) const ;

protected:
	string m_HostName;
	string m_GuestName;
};


//////////////////////////////////////////////////////////////////////////////
// class PartyInviteInfoManager
//////////////////////////////////////////////////////////////////////////////

class PartyInviteInfoManager
{
public:
	PartyInviteInfoManager() ;
	~PartyInviteInfoManager() ;

public:
	bool hasInviteInfo(const string& HostName) ;
	bool canInvite(Creature* pHost, Creature* pGuest) ;
	bool isInviting(Creature* pHost, Creature* pGuest) ;
	void initInviteInfo(Creature* pHost, Creature* pGuest) ;
	void cancelInvite(Creature* pHost, Creature* pGuest) ;
	void cancelInvite(Creature* pCreature) ;

public:
	bool addInviteInfo(PartyInviteInfo* pInfo) ;
	void deleteInviteInfo(const string& HostName) ;
	PartyInviteInfo* getInviteInfo(const string& HostName) ;

protected:
	unordered_map<string, PartyInviteInfo*> m_InfoMap;
	Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// class Party
//////////////////////////////////////////////////////////////////////////////

class Party
{
public:
	Party(Creature::CreatureClass CClass) ;
	~Party() ;

public:
	int getID(void) const { return m_ID; }
	void setID(int ID) { m_ID = ID; }

	Creature::CreatureClass getCreatureClass(void) const { return m_CreatureClass; }

public:
	Creature* getMember(const string& name) const ;
	void addMember(Creature* pCreature) ;
	void deleteMember(const string& name) ;
	bool hasMember(const string& name) const ;

	// 글로벌 파티 매니저에서만 사용한다.
	// 파티를 해체하기 전에 파티 멤버들의 파티 ID를 0으로 만들고,
	// 로컬 파티 매니저에서 해당 ID를 가진 파티를 삭제한다.
	void destroyParty(void) ;

public:
	// 파티 멤버들에게 패킷을 날린다.
	void broadcastPacket(Packet* pPacket, Creature* pOwner=NULL) ;

	// 새로운 파티원이 추가되었을 때 파티원들에게 날아가는
	// GCPartyJoined 패킷을 구성한다.
	void makeGCPartyJoined(GCPartyJoined* pGCPartyJoined) const ;

public:
	int getSize(void) const ;
	unordered_map<string, Creature*> getMemberMap(void) ;

	// 근접한 거리(8타일) 내에 있는 멤버들의 숫자를 리턴한다.
	int getAdjacentMemberSize(Creature* pLeader) const ;
	int getAdjacentMemberSize_LOCKED(Creature* pLeader) const ;

	// 경험치를 부풀려서 나눈다.
	int shareAttrExp(Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) const ;
	int shareVampireExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const ;
	int shareOustersExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const ;

public:
	void shareRevealer(Creature* pCaster, int Duration) ;
	void shareDetectHidden(Creature* pCaster, int Duration) ;
	void shareDetectInvisibility(Creature* pCaster, int Duration) ;
	void shareExpansion(Creature* pCaster, int Duration, int percent) ;
	void shareActivation(Creature* pCaster, int Duration) ;
	void shareGnomesWhisper(Creature* pCaster, int Duration, int SkillLevel) ;
	void shareHolyArmor(Creature* pCaster, int DefBonus, int SkillLevel) ;
	bool shareWaterElementalHeal(Creature* pCaster, int HealPoint) ;
	void shareGDRLairEnter(Creature* pLeader) ;

	void shareRankExp(Creature* pLeader, int amount) ;
	void shareAdvancementExp(Creature* pLeader, int amount) ;

	void dissectCorpse(Creature* pDissecter, MonsterCorpse* pCorpse) ;
	void eventPartyCrash() ;

public:
	bool isFamilyPay() const { return m_bFamilyPay; }
	void refreshFamilyPay();

public:
	string toString(void) const ;

protected:
	int                          m_ID;            // 파티 ID
	Creature::CreatureClass      m_CreatureClass; // 파티의 종류
	unordered_map<string, Creature*>  m_MemberMap;     // 파티 멤버
	mutable Mutex                m_Mutex;         // 내부에서 쓰는 락
	bool						 m_bFamilyPay;	  // 패밀리 요금제 적용 파티인가?
};


//////////////////////////////////////////////////////////////////////////////
// class PartyManager
//////////////////////////////////////////////////////////////////////////////

class PartyManager
{
public:
	PartyManager() ;
	virtual ~PartyManager() ;

public:
	virtual bool createParty(int ID, Creature::CreatureClass) ;
	virtual bool addPartyMember(int ID, Creature* pCreature) ;
	virtual bool deletePartyMember(int ID, Creature* pCreature) ;
	virtual Party* getParty(int ID) ;

public:
	virtual string toString(void) const  = 0;

protected:
	unordered_map<int, Party*> m_PartyMap; // 파티 집합
	mutable Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// class LocalPartyManager
//////////////////////////////////////////////////////////////////////////////

class LocalPartyManager : public PartyManager
{
public:
	LocalPartyManager() ;
	virtual ~LocalPartyManager() ;

public:
	void heartbeat(void) ;
	int getAdjacentMemberSize(int PartyID, Creature* pLeader) const ;
	int shareAttrExp(int PartyID, Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) const ;
	int shareVampireExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const ;
	int shareOustersExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) const ;
	void shareRevealer(int PartyID, Creature* pCaster, int Duration) ;
	void shareDetectHidden(int PartyID, Creature* pCaster, int Duration) ;
	void shareDetectInvisibility(int PartyID, Creature* pCaster, int Duration) ;
	void shareExpansion(int PartyID, Creature* pCaster, int Duration, int Percent) ;
	void shareActivation(int PartyID, Creature* pCaster, int Duration) ;
	void shareGnomesWhisper(int PartyID, Creature* pCaster, int Duration, int SkillLevel) ;
	void shareHolyArmor(int PartyID, Creature* pCaster, int DefBonus, int SkillLevel) ;
	bool shareWaterElementalHeal(int PartyID, Creature* pCaster, int HealPoint) ;
	void shareGDRLairEnter(int PartyID, Creature* pLeader) ;
	
	int shareRankExp(int PartyID, Creature* pLeader, int amount) const ;
	int shareAdvancementExp(int PartyID, Creature* pLeader, int amount) const ;

public:
	virtual string toString(void) const ;
};


//////////////////////////////////////////////////////////////////////////////
// class GlobalPartyManager
//////////////////////////////////////////////////////////////////////////////

class GlobalPartyManager : public PartyManager
{
public:
	GlobalPartyManager() ;
	virtual ~GlobalPartyManager() ;

public:
	bool canAddMember(int ID) ;
	virtual bool addPartyMember(int ID, Creature* pCreature) ;
	virtual bool deletePartyMember(int ID, Creature* pCreature) ;
	virtual bool expelPartyMember(int ID, Creature* pExpeller, const string& ExpelleeName) ;

	int registerParty(void) ;

	void refreshFamilyPay(int ID);

public:
	virtual string toString(void) const ;

protected:
	int m_PartyIDRegistry; // 파티 ID 생성자
};

extern GlobalPartyManager* g_pGlobalPartyManager;


//////////////////////////////////////////////////////////////////////////////
// 편의를 위한 전역 함수들...
//////////////////////////////////////////////////////////////////////////////
void deleteAllPartyInfo(Creature* pCreature) ;


#endif
